#include <nob/window.hpp>
#include <nob/script.hpp>
#include <nob/shv.hpp>
#include <nob/log.hpp>

#include <rua/strenc.hpp>

#include <windows.h>

#include <thread>

namespace nob {
	namespace ntv {
		bool _find_addrs();
	}

	namespace this_script {
		void _shv_main();
		void _ysc_main();
		bool _exclusive_main();
	}

	namespace shv {
		bool _init();
	}

	#ifdef NDEBUG
		#define _NOB_CALL_INIT_FN(_f) \
			if (!_f()) { \
				MessageBoxW(0, rua::u8_to_u16(log.str()).c_str(), L"ERRORS", MB_OK | MB_ICONERROR); \
				exit(1); \
				return; \
			}
	#else
		#define _NOB_CALL_INIT_FN(_f) _f()
	#endif

	void _main(HMODULE hinstDLL) {
		std::thread([hinstDLL]() {
			for (auto wnd = window::native_handle(); !wnd; wnd = window::native_handle()) {
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}

			log.alloc_console();

			_NOB_CALL_INIT_FN(ntv::_find_addrs);

			tasks.init();
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

	namespace window {
		void _unhook_proc();
	}
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			nob::_main(hinstDLL);
			break;
		case DLL_PROCESS_DETACH:
			nob::window::_unhook_proc();

			#ifdef DEBUG
				if (nob::this_script::mode == nob::this_script::mode_t::shv) {
					nob::shv::scriptUnregister(hinstDLL);
				}
			#endif
	}
	return TRUE;
}
