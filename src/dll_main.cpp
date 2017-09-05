#include <nob/shv/main.hpp>
#include <atomic>

namespace nob {
	namespace shv {
		bool _init();
	} /* shv */
	void _script_entry_point();
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			if (!nob::shv::_init()) {
				return FALSE;
			}
			nob::shv::scriptRegister(hinstDLL, nob::_script_entry_point);
			break;
		case DLL_PROCESS_DETACH:
			#ifndef DEBUG
				nob::shv::scriptUnregister(hinstDLL);
			#endif
			break;
	}
	return TRUE;
}
