#include <nob/keyboard.hpp>
#include <nob/script.hpp>

#include <windows.h>
#include <atomic>
#include <cstring>

namespace nob {
	namespace keyboard {
		std::atomic<bool> _downs[120];

		initer _initer([]() {
			for (size_t i = 0; i < 120; ++i) {
				_downs[i] = false;
			}
		});

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

		void _send(int code, bool down) {
			auto old_state = keyboard::_downs[code].exchange(down);
			if (old_state == down) {
				return;
			}
			size_t ffc = this_script::first_frame_count;
			go([ffc, code, down]() {
				if (ffc != this_script::first_frame_count) {
					return;
				}
				for (auto &listener : keyboard::_listeners) {
					if (!listener(code, down)) {
						return;
					}
				}
			});
		}
	} /* keyboard */
} /* nob */
