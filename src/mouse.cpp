#include <nob/mouse.hpp>
#include <nob/script.hpp>
#include <nob/ntv.hpp>
#include <nob/screen.hpp>

#include <windows.h>

#include <map>
#include <queue>
#include <cstring>

namespace nob {
	extern std::queue<std::function<void()>> _inputs;

	namespace mouse {
		bool _downs[3];
		initer _clear_downs([]() {
			memset(&_downs, 0, 3 * sizeof(bool));
		});

		vector2_i _coords;

		std::unique_ptr<std::list<std::shared_ptr<std::function<bool(int, bool)>>>> _listeners;

		listener::listener() {
			if (!_listeners) {
				_listeners.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
			}
			_it = _listeners->end();
		}

		listener::listener(std::function<bool(int, bool)> listener) {
			if (!_listeners) {
				_listeners.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
			}
			_listeners->emplace_front(std::make_shared<std::function<bool(int, bool)>>(std::move(listener)));
			_it = _listeners->begin();
		}

		listener::listener(listener &&src) : _it(src._it) {
			if (src._it != _listeners->end()) {
				src._it = _listeners->end();
			}
		}

		listener &listener::operator=(listener &&src) {
			del();
			if (src._it != _listeners->end()) {
				_it = src._it;
				src._it = _listeners->end();
			}
			return *this;
		}

		listener::operator bool() const {
			return _listeners && _it != _listeners->end();
		}

		void listener::del() {
			if (!*this) {
				return;
			}
			_listeners->erase(_it);
			_it = _listeners->end();
		}

		vector2 coords() {
			auto rez = screen::resolution();
			return { static_cast<float>(_coords.x) / rez.x, static_cast<float>(_coords.y) / rez.y };
		}

		vector2_i coords_i() {
			return _coords;
		}

		bool is_down(int button) {
			return _downs[button];
		}

		void _send(int button, bool down) {
			if (button < 3) {
				if (down == _downs[button]) {
					return;
				}
				_downs[button] = down;
			}
			if (!_listeners) {
				return;
			}
			_inputs.push([button, down]() {
				std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
				for (auto &hdr_sp : *_listeners) {
					qu.emplace(hdr_sp);
				}
				while (qu.size()) {
					auto hdr_sp = qu.front().lock();
					qu.pop();
					if (hdr_sp) {
						if (!(*hdr_sp)(button, down)) {
							return;
						}
					}
				}
			});
		}

		void _reset() {
			for (size_t i = 0; i < 3; ++i) {
				if (_downs[i]) {
					_send(i, false);
				}
			}
		}
	} /* mouse */
} /* nob */
