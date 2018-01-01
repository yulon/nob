#include <nob/script.hpp>
#include <nob/shv.hpp>

#include <windows.h>

#include <thread>

namespace nob {
	namespace this_script {
		void _shv_main();
		void _ysc_main();
		void _exclusive_main();
	} /* this_script */

	namespace window {
		void _unhook_proc();
	} /* window */
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			if (nob::shv::valid) {
				nob::this_script::mode = nob::this_script::mode_t::shv;
				nob::shv::scriptRegister(hinstDLL, nob::this_script::_shv_main);
			} else {
				nob::this_script::mode = nob::this_script::mode_t::exclusive;
				std::thread(nob::this_script::_exclusive_main).detach();
			}
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
