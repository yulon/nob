#include <nob/keyboard.hpp>
#include <nob/script.hpp>
#include <nob/ntv.hpp>

#include <windows.h>

#include <map>
#include <queue>
#include <cstring>

namespace nob {
	namespace keyboard {
		bool _downs[120], _downs_shadow[120];

		initer _clear_downs([]() {
			memset(&_downs, 0, 120 * sizeof(bool));
			memset(&_downs_shadow, 0, 120 * sizeof(bool));
		});

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

		bool is_down(int code) {
			return _downs_shadow[code];
		}

		void _send(int code, bool down) {
			if (down == _downs[code]) {
				return;
			}
			_downs[code] = down;
			size_t cgpid = this_script::gameplay_id;
			go([cgpid, code, down]() {
				if (cgpid != this_script::gameplay_id) {
					return;
				}
				_downs_shadow[code] = down;
				std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
				for (auto &hdr_sp : *_listeners) {
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

		std::unique_ptr<std::map<int, size_t>> _bkr_map;
		task _bkr_tsk;

		blocker::blocker(std::initializer_list<block_t> blks) {
			if (!blks.size()) {
				return;
			}
			if (!_bkr_map) {
				_bkr_map.reset(new std::map<int, size_t>);
			}
			for (auto blk : blks) {
				auto b = static_cast<int>(blk);
				_blks.emplace_back(b);
				auto it = _bkr_map->find(b);
				if (it == _bkr_map->end()) {
					_bkr_map->emplace(b, 1);
				} else {
					++it->second;
				}
			}
			if (!_bkr_tsk) {
				_bkr_tsk = task([]() {
					for (auto &pr : *_bkr_map) {
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, pr.first, true);
					}
				});
			}
		}

		blocker::blocker(block_t blk) : blocker({blk}) {}

		blocker::blocker(blocker &&src) : _blks(std::move(src._blks)) {}

		blocker &blocker::operator=(blocker &&src) {
			del();
			_blks = std::move(src._blks);
			return *this;
		}

		blocker::operator bool() const {
			return _bkr_map && _blks.size();
		}

		void blocker::del() {
			if (!*this) {
				return;
			}
			for (auto blk : _blks) {
				auto it = _bkr_map->find(blk);
				if (it != _bkr_map->end() && !--it->second) {
					_bkr_map->erase(it);
				}
			}
			if (_bkr_map->empty() && !this_script::exiting) {
				_bkr_tsk.del();
			}
			_blks.clear();
		}
	} /* keyboard */
} /* nob */
