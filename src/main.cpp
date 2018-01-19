#include <nob/window.hpp>
#include <nob/script.hpp>
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
		bool _exclusive_main();

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
			for (
				bool ok = window::native_handle() && IsWindowVisible(window::native_handle());
				!ok;
				ok = window::native_handle() && IsWindowVisible(window::native_handle())
			) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			log.alloc_console();

			_NOB_CALL_INIT_FN(ntv::_find_addrs);

			tasks.bind_this_thread();
			tasks.add_back([]() {
				tasks.exit();
			});

			if (shv::_init()) {
				this_script::mode = this_script::mode_t::shv;
				shv::scriptRegister(hinstDLL, this_script::_shv_main);
				return;
			}

			this_script::mode = this_script::mode_t::exclusive;
			_NOB_CALL_INIT_FN(this_script::_exclusive_main);

		}).detach();
	}

	void _exit(HMODULE hinstDLL) {
		if (!this_script::exiting) {
			this_script::exiting = true;
			for (
				bool exited = !IsWindowVisible(window::native_handle()) || this_script::_exited;
				!exited;
				exited = !IsWindowVisible(window::native_handle()) || this_script::_exited
			) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
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
