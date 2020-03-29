#pragma once

#include <nob/log.hpp>

#include <rua/bit.hpp>
#include <rua/macros.hpp>
#include <rua/memory.hpp>

#include <windows.h>

#include <mutex>

namespace nob {

inline void _disable_ws2_func(const char *name) {
	static auto ws2_dll = GetModuleHandleW(L"ws2_32.dll");

	auto fp = GetProcAddress(ws2_dll, name);
	if (!fp) {
		log("nob::_disable_ws2_func: ", name, "() not found!");
		return;
	}

	auto is_writable = rua::mem_chmod(fp, 3);
	if (!is_writable) {
		log("nob::_disable_ws2_func: set ",
			name,
			"() memory protection failed!");
		return;
	}

	if (rua::bit_as<uint16_t>(fp) != 0xC031) {
		rua::bit_as<uint16_t>(fp) = 0xC031;
	}
	if (rua::bit_as<uint8_t>(fp, 2) != 0xC3) {
		rua::bit_as<uint8_t>(fp, 2) = 0xC3;
	}
}

inline void _disable_ws2() RUA_ONCE_CODE({
	_disable_ws2_func("send");
	_disable_ws2_func("recv");
})

} // namespace nob
