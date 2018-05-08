#include <nob/script.hpp>
#include <nob/program.hpp>
#include <nob/window.hpp>
#include <nob/ntv.hpp>
#include <nob/shv.hpp>
#include <nob/dx.hpp>
#include <nob/log.hpp>

namespace nob {
	HMODULE this_dll;

	namespace ntv {
		bool _pre_init();
		bool _init();
	}

	namespace shv {
		bool _init();
	}

	namespace this_script {
		void _shv_main();
		void _create_from_td();
		extern std::atomic<bool> _exited;
	}

	#ifdef NDEBUG
		#define _NOB_CALL_INIT_FN(_f) \
			if (!_f()) { \
				MessageBoxW(0, rua::u8_to_w(log.str()).c_str(), L"ERRORS", MB_OK | MB_ICONERROR); \
				_exited = true; \
				exit(1); \
				return; \
			}
	#else
		#define _NOB_CALL_INIT_FN(_f) _f()
	#endif

	#define _NOB_NEW_TD(_f) CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(static_cast<void(*)()>( _f )), nullptr, 0, nullptr);

	void _init() {
		ntv::_pre_init();

		_NOB_NEW_TD([]() {
			while (!window::is_visible()) {
				Sleep(100);
			}

			log.alloc_console();

			if (dx::on_render::count()) {
				_NOB_NEW_TD(&dx::on_render::_init);
			}

			_NOB_CALL_INIT_FN(ntv::_init);

			if (shv::_init()) {
				this_script::mode = this_script::mode_t::shv;
				shv::scriptRegister(this_dll, this_script::_shv_main);
				return;
			}

			_NOB_CALL_INIT_FN(this_script::_create_from_td);
		});
	}

	void _exit() {
		this_script::exiting = true;

		for (;;) {
			if (!IsWindowVisible(window::native_handle())) {
				return;
			}
			if (this_script::_exited) {
				break;
			}
			Sleep(100);
		}

		dx::on_render::_uninit();

		if (this_script::mode == this_script::mode_t::shv) {
			shv::scriptUnregister(this_dll);
		}
	}
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hinstDLL);
			nob::this_dll = hinstDLL;
			nob::_init();
			break;
		case DLL_PROCESS_DETACH:
			nob::_exit();
	}
	return TRUE;
}
