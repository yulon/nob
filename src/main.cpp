#include <nob/dx.hpp>
#include <nob/log.hpp>
#include <nob/ntv.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>
#include <nob/shv.hpp>
#include <nob/window.hpp>

#include <rua/string.hpp>
#include <rua/thread.hpp>

namespace nob {

HMODULE this_dll;

namespace ntv {

void _pre_init();
bool _init();

} // namespace ntv

namespace shv {

bool _init();

}

namespace this_script {

void WINAPI _shv_main();
bool _create_from_td();
extern std::atomic<bool> _is_exited;

} // namespace this_script

namespace window {

void _unhook_proc();

}

#ifdef NDEBUG
#define _NOB_CALL_INIT_FN(_f)                                                  \
	if (!_f()) {                                                               \
		MessageBoxW(                                                           \
			0,                                                                 \
			rua::u8_to_w(log.str()).c_str(),                                   \
			L"ERRORS",                                                         \
			MB_OK | MB_ICONERROR);                                             \
		this_script::_is_exited = true;                                        \
		exit(1);                                                               \
		return;                                                                \
	}
#else
#define _NOB_CALL_INIT_FN(_f) _f()
#endif

void _init() {
	ntv::_pre_init();

	rua::thread([]() {
		while (!window::is_visible()) {
			Sleep(100);
		}

		log.alloc_console();

		if (dx::on_render::count()) {
			rua::thread{dx::on_render::_init};
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
	this_script::is_exiting = true;

	for (;;) {
		if (!IsWindowVisible(window::native_handle())) {
			return;
		}
		if (this_script::_is_exited) {
			break;
		}
		Sleep(100);
	}

	dx::on_render::_uninit();
	window::_unhook_proc();

	if (this_script::mode == this_script::mode_t::shv) {
		shv::scriptUnregister(this_dll);
	}
}

} // namespace nob

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
