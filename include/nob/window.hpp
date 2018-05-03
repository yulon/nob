#pragma once

#include <windows.h>

namespace nob {
	namespace window {
		HWND native_handle();

		inline bool is_visible() {
			auto h = native_handle();
			return h && IsWindowVisible(h);
		}
	}
}
