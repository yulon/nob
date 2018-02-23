//#include <nob/input.hpp>
#include <nob/script.hpp>
#include <nob/ntv/base.hpp>
#include <nob/vector.hpp>

#include <windows.h>
#include <windowsx.h>

#include <cstdio>

namespace nob {
	namespace _kl {
		void send(int, bool);
		void reset();
	}

	namespace _ml {
		void send(int, bool);
		void reset();
		extern vector2_i pos;
	}

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
						_ml::pos.x = GET_X_LPARAM(lParam);
						_ml::pos.y = GET_Y_LPARAM(lParam);
						break;

					case WM_LBUTTONDOWN:
						_ml::send(0, true);
						break;

					case WM_LBUTTONUP:
						_ml::send(0, false);
						break;

					case WM_RBUTTONDOWN:
						_ml::send(1, true);
						break;

					case WM_RBUTTONUP:
						_ml::send(1, false);
						break;

					case WM_MBUTTONDOWN:
						_ml::send(2, true);
						break;

					case WM_MBUTTONUP:
						_ml::send(2, false);
						break;

					case WM_MOUSEWHEEL: {
						auto val = (short)HIWORD(wParam);
						if (val < 0) {
							_ml::send(3, true);
						} else if (val > 0) {
							_ml::send(3, false);
						}
						break;
					}

					case WM_KEYDOWN:
						_kl::send(wParam, true);
						break;

					case WM_KEYUP:
						_kl::send(wParam, false);
						break;

					case WM_ACTIVATE:
						if (!wParam) {
							_ml::reset();
							_kl::reset();
						}
				}
			}
			return CallWindowProcW(_old_proc, hWnd, uMsg, wParam, lParam);
		}

		initer _hook_proc([]() {
			if (_old_proc) {
				return;
			}
			if (!native_handle()) {
				return;
			}
			_old_proc = (WNDPROC)SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)&_proc);
		});

		exiter _unhook_proc([]() {
			if (!_old_proc) {
				return;
			}
			SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)_old_proc);
		});
	} /* window */
} /* nob */
