//#include <nob/input.hpp>
#include <nob/ntv/base.hpp>
#include <nob/script.hpp>
#include <nob/vector.hpp>

#include <windows.h>
#include <windowsx.h>

#include <cstdio>

namespace nob {

namespace _kl {
void send(int, bool);
void reset();
} // namespace _kl

namespace _hkl {
void reset();
}

extern vector2_i _mouse_pos;

namespace window {

HWND _handle = nullptr;

HWND native_handle() {
	if (_handle) {
		return _handle;
	}
	_handle = FindWindowW(L"grcWindow", L"Grand Theft Auto V");
	if (!_handle) {
		return nullptr;
	}
	DWORD pid;
	GetWindowThreadProcessId(_handle, &pid);
	if (pid != GetCurrentProcessId()) {
		_handle = nullptr;
		return nullptr;
	}
	return _handle;
}

WNDPROC _old_proc = nullptr;

LRESULT CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (*ntv::game_state == ntv::game_state_t::playing) {
		switch (uMsg) {
		case WM_MOUSEMOVE:
			_mouse_pos.x = GET_X_LPARAM(lParam);
			_mouse_pos.y = GET_Y_LPARAM(lParam);
			break;

		case WM_LBUTTONDOWN:
			_kl::send(VK_LBUTTON, true);
			break;

		case WM_LBUTTONUP:
			_kl::send(VK_LBUTTON, false);
			break;

		case WM_RBUTTONDOWN:
			_kl::send(VK_RBUTTON, true);
			break;

		case WM_RBUTTONUP:
			_kl::send(VK_RBUTTON, false);
			break;

		case WM_MBUTTONDOWN:
			_kl::send(VK_MBUTTON, true);
			break;

		case WM_MBUTTONUP:
			_kl::send(VK_MBUTTON, false);
			break;

		case WM_MOUSEWHEEL: {
			auto val = (short)HIWORD(wParam);
			if (val < 0) {
				_kl::send(WM_MOUSEWHEEL, true);
			} else if (val > 0) {
				_kl::send(WM_MOUSEWHEEL, false);
			}
			break;
		}

		case WM_KEYDOWN:
			_kl::send(static_cast<int>(wParam), true);
			break;

		case WM_KEYUP:
			_kl::send(static_cast<int>(wParam), false);
			break;

		case WM_ACTIVATE:

			if (!wParam) {
				_kl::reset();
				_kl::reset();
				_hkl::reset();
			}
		}
	}
	return CallWindowProcW(_old_proc, hWnd, uMsg, wParam, lParam);
}

on_load _hook_proc([]() {
	if (_old_proc) {
		return;
	}
	if (!native_handle()) {
		return;
	}
	_old_proc =
		(WNDPROC)SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)&_proc);
});

void _unhook_proc() {
	if (!_old_proc) {
		return;
	}
	SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)_old_proc);
}

} // namespace window

} // namespace nob
