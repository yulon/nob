#include <nob/program.hpp>
#include <nob/log.hpp>

namespace nob {
	HMODULE this_dll;

	namespace this_script {
		void _create();
		void _destroy();
	}
} /* nob */

BOOL APIENTRY DllMain(HMODULE hinstDLL, DWORD fdwReason, LPVOID) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hinstDLL);
			nob::this_dll = hinstDLL;
			nob::this_script::_create();
			break;
		case DLL_PROCESS_DETACH:
			nob::this_script::_destroy();
	}
	return TRUE;
}
