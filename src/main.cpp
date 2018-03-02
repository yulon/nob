#include <nob/window.hpp>
#include <nob/script.hpp>
#include <nob/ntv/base.hpp>
#include <nob/shv.hpp>
#include <nob/log.hpp>

#include <rua/strenc.hpp>

#include <windows.h>

#include <thread>
#include <atomic>

namespace nob {
	namespace ntv {
		bool _find_addrs();
	}

	namespace this_script {
		void _shv_main();
		void _ysc_main();
		bool _hook_main();
		bool _td_main();

		void _exit();
		extern std::atomic<bool> _exited;
	}

	namespace shv {
		bool _init();
	}

	#ifdef NDEBUG
		#define _NOB_CALL_INIT_FN(_f) \
			if (!_f()) { \
				MessageBoxW(0, rua::u8_to_u16(log.str()).c_str(), L"ERRORS", MB_OK | MB_ICONERROR); \
				this_script::exiting = true; \
				exit(1); \
				return; \
			}
	#else
		#define _NOB_CALL_INIT_FN(_f) _f()
	#endif

	void _main(HMODULE hinstDLL) {
		std::thread([hinstDLL]() {
			while (!window::native_handle()) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			while (!IsWindowVisible(window::native_handle())) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			log.alloc_console();

			_NOB_CALL_INIT_FN(ntv::_find_addrs);

			if (shv::_init()) {
				this_script::mode = this_script::mode_t::shv;
				shv::scriptRegister(hinstDLL, this_script::_shv_main);
				return;
			}

			if (ntv::game_state) {
				auto &gs = reinterpret_cast<uint8_t &>(*ntv::game_state);
				while (gs && gs < 5) {
					std::this_thread::sleep_for(std::chrono::milliseconds(500));
				}
			}

			if (this_script::_td_main()) {
				this_script::mode = this_script::mode_t::sub_thread;
				return;
			}

			this_script::mode = this_script::mode_t::main_thread;
			_NOB_CALL_INIT_FN(this_script::_hook_main);
		}).detach();
	}

	void _exit(HMODULE hinstDLL) {
		if (this_script::exiting) {
			return;
		}

		this_script::exiting = true;

		for (;;) {
			if (!IsWindowVisible(window::native_handle())) {
				return;
			}
			if (this_script::_exited) {
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		if (this_script::mode == this_script::mode_t::shv) {
			shv::scriptUnregister(hinstDLL);
			return;
		}
	}
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			nob::_main(hinstDLL);
			break;
		case DLL_PROCESS_DETACH:
			nob::_exit(hinstDLL);
	}
	return TRUE;
}
