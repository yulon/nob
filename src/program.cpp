#include <nob/program.hpp>

#include <rua/process.hpp>

#include <windows.h>
#include <psapi.h>
#include <winver.h>

#include <memory>

namespace nob {
	rua::bin_ref game_code = rua::process::from_this().mem_ref();

	uint16_t game_build = ([]()->uint16_t {
		WCHAR path[MAX_PATH];
		GetModuleFileNameExW(GetCurrentProcess(), GetModuleHandleW(nullptr), path, MAX_PATH);

		DWORD sz, h;
		sz = GetFileVersionInfoSizeW(path, &h);
		if(sz == 0) {
			return 0;
		}

		std::unique_ptr<uint8_t> data(new uint8_t[sz + 1]);
		if (!GetFileVersionInfoW(path, 0, sz, reinterpret_cast<LPVOID>(data.get()))) {
			return 0;
		}

		VS_FIXEDFILEINFO *buf;
		UINT len;
		if (!VerQueryValueW(reinterpret_cast<LPCVOID>(data.get()), L"\\", reinterpret_cast<LPVOID *>(&buf), &len)) {
			return 0;
		}

		return HIWORD(buf->dwProductVersionLS);
	})();
}
