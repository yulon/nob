#include <nob/keyboard.hpp>
#include <nob/script.hpp>
#include <nob/ntv/base.hpp>

#include <windows.h>

#include <cstdio>

namespace nob {
	namespace keyboard {
		void _send(int, bool);
	} /* keyboard */

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
			switch (uMsg) {
				case WM_KEYDOWN:
					if (*ntv::game_state != ntv::game_state_t::playing) {
						break;
					}
					keyboard::_send(wParam, true);
					break;
				case WM_KEYUP:
					if (*ntv::game_state != ntv::game_state_t::playing) {
						break;
					}
					keyboard::_send(wParam, false);
			}
			return CallWindowProcW(_old_proc, hWnd, uMsg, wParam, lParam);
		}

		void _hook_proc() {
			if (_old_proc) {
				return;
			}
			if (!native_handle()) {
				return;
			}
			_old_proc = (WNDPROC)SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)&_proc);
		}

		initer _initer(_hook_proc);

		void _unhook_proc() {
			if (!_old_proc) {
				return;
			}
			SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)_old_proc);
		}
	} /* window */
} /* nob */
