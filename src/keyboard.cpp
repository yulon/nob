#include <nob/keyboard.hpp>

#include <windows.h>

#include <list>
#include <cstring>

namespace nob {
	namespace keyboard {
		bool _downs[120];
		class _downs_initer_t {
			public:
				_downs_initer_t() {
					memset(_downs, 0, 120 * sizeof(bool));
				}
		} _downs_initer;

		std::list<std::function<bool(int, bool)>> _listeners;

		listener::listener(const std::function<bool(int, bool)> &listener) : _null(false) {
			_listeners.push_front(listener);
			_it = _listeners.begin();
		}

		listener::listener(listener &&src) {
			if (src._null) {
				_null = true;
			} else {
				_null = false;
				_it = src._it;

				src._null = true;
			}
		}

		const listener &listener::operator=(listener &&src) {
			if (!_null) {
				_listeners.erase(_it);
				_null = true;
			}
			if (!src._null) {
				_null = false;
				_it = src._it;

				src._null = true;
			}
			return *this;
		}

		void listener::del() {
			if (_null) {
				return;
			}
			_null = true;

			_listeners.erase(_it);
		}

		bool is_down(int code) {
			return _downs[code];
		}
	} /* keyboard */
} /* nob */
