#include <nob.hpp>
#include <nob/shv/main.hpp>

#include <windows.h>

namespace nob {
	namespace this_script {
		bool asi_mode = false;
		void _main();
	} /* this_script */

	HMODULE _this_module;

	namespace window {
		void _unhook_proc();
	} /* window */
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			if (nob::shv::valid) {
				nob::this_script::asi_mode = true;
				nob::shv::scriptRegister(hinstDLL, nob::this_script::_main);
			} else {
				return FALSE;
			}
			nob::_this_module = hinstDLL;
			break;
		case DLL_PROCESS_DETACH:
			nob::window::_unhook_proc();

			#ifdef DEBUG
				if (nob::this_script::asi_mode) {
					nob::shv::scriptUnregister(hinstDLL);
				}
			#endif
	}
	return TRUE;
}
