#include <nob/input.hpp>
#include <nob/script.hpp>
#include <nob/ntv.hpp>
#include <nob/screen.hpp>

#include <windows.h>

#include <map>
#include <queue>
#include <cstring>

namespace nob {
	std::queue<std::function<void()>> _inputs;

	namespace _kl {
		bool downs[120];

		initer _clear_downs([]() {
			memset(&downs, 0, 120 * sizeof(bool));
		});

		std::unique_ptr<std::list<std::shared_ptr<std::function<bool(int, bool)>>>> li;

		void send(int code, bool down) {
			if (down == downs[code]) {
				return;
			}
			downs[code] = down;

			if (!li) {
				return;
			}
			_inputs.push([code, down]() {
				std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
				for (auto &hdr_sp : *li) {
					qu.emplace(hdr_sp);
				}
				while (qu.size()) {
					auto hdr_sp = qu.front().lock();
					qu.pop();
					if (hdr_sp) {
						if (!(*hdr_sp)(code, down)) {
							return;
						}
					}
				}
			});
		}

		void reset() {
			for (size_t i = 0; i < 120; ++i) {
				if (downs[i]) {
					send(i, false);
				}
			}
		}
	}

	key_listener::key_listener() {
		if (!_kl::li) {
			_kl::li.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
		}
		_it = _kl::li->end();
	}

	key_listener::key_listener(std::function<bool(int, bool)> key_listener) {
		if (!_kl::li) {
			_kl::li.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
		}
		_kl::li->emplace_front(std::make_shared<std::function<bool(int, bool)>>(std::move(key_listener)));
		_it = _kl::li->begin();
	}

	key_listener::key_listener(key_listener &&src) : _it(src._it) {
		if (src._it != _kl::li->end()) {
			src._it = _kl::li->end();
		}
	}

	key_listener &key_listener::operator=(key_listener &&src) {
		del();
		if (src._it != _kl::li->end()) {
			_it = src._it;
			src._it = _kl::li->end();
		}
		return *this;
	}

	key_listener::operator bool() const {
		return _kl::li && _it != _kl::li->end();
	}

	void key_listener::del() {
		if (!*this) {
			return;
		}
		_kl::li->erase(_it);
		_it = _kl::li->end();
	}

	bool is_key_down(int code) {
		return _kl::downs[code];
	}

	namespace _hkbr {
		std::unique_ptr<std::map<int, size_t>> map;
		task tsk;
	}

	hotkey_blocker::hotkey_blocker(std::initializer_list<hotkey_t> hks) {
		if (!hks.size()) {
			return;
		}
		if (!_hkbr::map) {
			_hkbr::map.reset(new std::map<int, size_t>);
		}
		for (auto hk : hks) {
			auto b = static_cast<int>(hk);
			_hks.emplace_back(b);
			auto it = _hkbr::map->find(b);
			if (it == _hkbr::map->end()) {
				_hkbr::map->emplace(b, 1);
			} else {
				++it->second;
			}
		}
		if (!_hkbr::tsk) {
			_hkbr::tsk = task([]() {
				for (auto &pr : *_hkbr::map) {
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, pr.first, true);
				}
			});
		}
	}

	hotkey_blocker::hotkey_blocker(hotkey_t hk) : hotkey_blocker({hk}) {}

	hotkey_blocker::hotkey_blocker(hotkey_blocker &&src) : _hks(std::move(src._hks)) {}

	hotkey_blocker &hotkey_blocker::operator=(hotkey_blocker &&src) {
		del();
		_hks = std::move(src._hks);
		return *this;
	}

	hotkey_blocker::operator bool() const {
		return _hkbr::map && _hks.size();
	}

	void hotkey_blocker::del() {
		if (!*this) {
			return;
		}
		for (auto hk : _hks) {
			auto it = _hkbr::map->find(hk);
			if (it != _hkbr::map->end() && !--it->second) {
				_hkbr::map->erase(it);
			}
		}
		if (_hkbr::map->empty() && !this_script::exiting) {
			_hkbr::tsk.del();
		}
		_hks.clear();
	}

	////////////////////////////////////////////////////////////////////////////

	namespace _ml {
		bool downs[3];

		initer clear_downs([]() {
			memset(&downs, 0, 3 * sizeof(bool));
		});

		vector2_i pos;

		std::unique_ptr<std::list<std::shared_ptr<std::function<bool(int, bool)>>>> li;

		void send(int button, bool down) {
			if (button < 3) {
				if (down == _ml::downs[button]) {
					return;
				}
				_ml::downs[button] = down;
			}
			if (!_ml::li) {
				return;
			}
			_inputs.push([button, down]() {
				std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
				for (auto &hdr_sp : *_ml::li) {
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

		void reset() {
			for (size_t i = 0; i < 3; ++i) {
				if (downs[i]) {
					send(i, false);
				}
			}
		}
	}

	mouse_listener::mouse_listener() {
		if (!_ml::li) {
			_ml::li.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
		}
		_it = _ml::li->end();
	}

	mouse_listener::mouse_listener(std::function<bool(int, bool)> mouse_listener) {
		if (!_ml::li) {
			_ml::li.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
		}
		_ml::li->emplace_front(std::make_shared<std::function<bool(int, bool)>>(std::move(mouse_listener)));
		_it = _ml::li->begin();
	}

	mouse_listener::mouse_listener(mouse_listener &&src) : _it(src._it) {
		if (src._it != _ml::li->end()) {
			src._it = _ml::li->end();
		}
	}

	mouse_listener &mouse_listener::operator=(mouse_listener &&src) {
		del();
		if (src._it != _ml::li->end()) {
			_it = src._it;
			src._it = _ml::li->end();
		}
		return *this;
	}

	mouse_listener::operator bool() const {
		return _ml::li && _it != _ml::li->end();
	}

	void mouse_listener::del() {
		if (!*this) {
			return;
		}
		_ml::li->erase(_it);
		_it = _ml::li->end();
	}

	vector2 mouse_pos() {
		auto rez = screen::resolution();
		return { static_cast<float>(_ml::pos.x) / rez.x, static_cast<float>(_ml::pos.y) / rez.y };
	}

	vector2_i mouse_pos_i() {
		return _ml::pos;
	}

	bool is_mouse_botton_down(int button) {
		return _ml::downs[button];
	}
} /* nob */
