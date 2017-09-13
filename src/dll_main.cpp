#include <nob/shv/main.hpp>

namespace nob {
	void _main();
	bool _asi_mode = false;
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			if (nob::shv::valid) {
				nob::_asi_mode = true;
				nob::shv::scriptRegister(hinstDLL, nob::_main);
				return TRUE;
			}
			return FALSE;
			break;
		case DLL_PROCESS_DETACH:
			#ifndef DEBUG
				if (nob::_asi_mode) {
					nob::shv::scriptUnregister(hinstDLL);
					return TRUE;
				}
			#endif
			break;
	}
	return TRUE;
}
