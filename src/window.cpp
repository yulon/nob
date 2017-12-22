#include <nob/keyboard.hpp>

#include <windows.h>

#include <cstdio>
#include <queue>
#include <iostream>

namespace nob {
	namespace keyboard {
		extern bool _downs[120];
		extern std::list<std::function<bool(int, bool)>> _listeners;
	} /* keyboard */

	extern std::queue<std::function<void()>> _input_events;

	namespace window {
		HWND _handle = ([]()->HWND {
			#ifdef DEBUG
				AllocConsole();
				freopen("conout$", "w+t", stdout);
				freopen("conout$", "w+t", stderr);
				freopen("conout$", "w+t", stderr);
			#endif

			auto wnd = FindWindowW(L"grcWindow", L"Grand Theft Auto V");
			if (wnd) {
				DWORD pid;
				GetWindowThreadProcessId(wnd, &pid);
				if (pid == GetCurrentProcessId()) {
					return wnd;
				}
			}
			return nullptr;
		})();

		WNDPROC _old_proc = nullptr;

		LRESULT CALLBACK _proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
			switch (uMsg) {
				case WM_KEYDOWN:
					if (!keyboard::_downs[wParam]) {
						keyboard::_downs[wParam] = true;
						_input_events.push([wParam]() {
							for (auto &listener : keyboard::_listeners) {
								if (!listener(wParam, true)) {
									return;
								}
							}
						});
					}
					break;
				case WM_KEYUP:
					keyboard::_downs[wParam] = false;
					_input_events.push([wParam]() {
						for (auto &listener : keyboard::_listeners) {
							if (!listener(wParam, false)) {
								return;
							}
						}
					});
			}
			return CallWindowProcW(_old_proc, hWnd, uMsg, wParam, lParam);
		}

		void _hook_proc() {
			if (!_old_proc) {
				_old_proc = (WNDPROC)SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)&_proc);
			}
		}

		void _unhook_proc() {
			if (_old_proc) {
				SetWindowLongPtrW(_handle, GWLP_WNDPROC, (LONG_PTR)_old_proc);
			}
		}
	} /* window */
} /* nob */
