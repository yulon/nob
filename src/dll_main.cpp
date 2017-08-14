#include <nob/shv/main.hpp>

namespace nob {
	namespace shv {
		void _load();
		void _free();
	} /* shv */
	void _entry_point();
} /* nob */

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			nob::shv::_load();
			nob::shv::scriptRegister(hInstance, nob::_entry_point);
			break;
		case DLL_PROCESS_DETACH:
			//nob::shv::scriptUnregister(hInstance);
			//nob::shv::free();
			break;
	}
	return TRUE;
}
