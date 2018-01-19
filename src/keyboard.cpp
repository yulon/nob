#include <nob/keyboard.hpp>
#include <nob/script.hpp>

#include <windows.h>

#include <atomic>
#include <memory>
#include <cstring>

namespace nob {
	namespace keyboard {
		std::atomic<bool> _downs[120];

		initer _initer([]() {
			for (size_t i = 0; i < 120; ++i) {
				_downs[i] = false;
			}
		});

		std::unique_ptr<std::list<std::function<bool(int, bool)>>> _listeners;

		listener::listener() {
			if (!_listeners) {
				_listeners.reset(new std::list<std::function<bool(int, bool)>>);
			}
			_it = _listeners->end();
		}

		listener::listener(std::function<bool(int, bool)> listener) {
			if (!_listeners) {
				_listeners.reset(new std::list<std::function<bool(int, bool)>>);
			}
			_listeners->emplace_front(std::move(listener));
			_it = _listeners->begin();
		}

		listener::listener(listener &&src) : _it(src._it) {
			if (src._it != _listeners->end()) {
				src._it = _listeners->end();
			}
		}

		const listener &listener::operator=(listener &&src) {
			del();
			if (src._it != _listeners->end()) {
				_it = src._it;
				src._it = _listeners->end();
			}
			return *this;
		}

		void listener::del() {
			if (_it == _listeners->end()) {
				return;
			}
			_listeners->erase(_it);
			_it = _listeners->end();
		}

		bool is_down(int code) {
			return _downs[code];
		}

		void _send(int code, bool down) {
			auto old_state = keyboard::_downs[code].exchange(down);
			if (old_state == down) {
				return;
			}
			size_t ffc = this_script::gameplay_id;
			go([ffc, code, down]() {
				if (ffc != this_script::gameplay_id) {
					return;
				}
				for (auto &listener : *_listeners) {
					if (!listener(code, down)) {
						return;
					}
				}
			});
		}
	} /* keyboard */
} /* nob */
