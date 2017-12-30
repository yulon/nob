#include <nob/script.hpp>
#include <nob/shv.hpp>

#include <windows.h>

#include <thread>

namespace nob {
	namespace this_script {
		void _main();
		void _main2();
	} /* this_script */

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
				std::thread(nob::this_script::_main2).detach();
			}
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
