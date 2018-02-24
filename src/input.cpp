#include <nob/input.hpp>
#include <nob/script.hpp>
#include <nob/ntv.hpp>
#include <nob/screen.hpp>

#include <windows.h>

#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cstring>

namespace nob {
	std::queue<std::function<void()>> _inputs;

	namespace _kl {
		std::unordered_set<int> downs;

		initer _clear_downs([]() {
			downs.clear();
		});

		std::unique_ptr<std::list<std::shared_ptr<std::function<bool(int, bool)>>>> li;

		void send(int code, bool down) {
			auto it = downs.find(code);
			if (down) {
				if (it != downs.end()) {
					return;
				}
				downs.emplace(code);
			} else {
				if (it != downs.end()) {
					downs.erase(it);
				}
			}
			if (!li) {
				return;
			}
			_inputs.push([code, down]() {
				std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
				for (auto &lnr_sp : *li) {
					qu.emplace(lnr_sp);
				}
				while (qu.size()) {
					auto lnr_sp = qu.front().lock();
					qu.pop();
					if (lnr_sp) {
						if (!(*lnr_sp)(code, down)) {
							return;
						}
					}
				}
			});
		}

		void reset() {
			if (li) {
				for (auto code : downs) {
					_inputs.push([code]() {
						std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
						for (auto &lnr_sp : *li) {
							qu.emplace(lnr_sp);
						}
						while (qu.size()) {
							auto lnr_sp = qu.front().lock();
							qu.pop();
							if (lnr_sp) {
								if (!(*lnr_sp)(code, false)) {
									return;
								}
							}
						}
					});
				}
			}
			downs.clear();
		}
	}

	key_listener::key_listener() {
		if (!_kl::li) {
			_kl::li.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
		}
		_lnr_it = _kl::li->end();
	}

	key_listener::key_listener(std::function<bool(int, bool)> key_listener) {
		if (!_kl::li) {
			_kl::li.reset(new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
		}
		_kl::li->emplace_front(std::make_shared<std::function<bool(int, bool)>>(std::move(key_listener)));
		_lnr_it = _kl::li->begin();
	}

	key_listener::key_listener(key_listener &&src) : _lnr_it(src._lnr_it) {
		if (src._lnr_it != _kl::li->end()) {
			src._lnr_it = _kl::li->end();
		}
	}

	key_listener &key_listener::operator=(key_listener &&src) {
		del();
		if (src._lnr_it != _kl::li->end()) {
			_lnr_it = src._lnr_it;
			src._lnr_it = _kl::li->end();
		}
		return *this;
	}

	key_listener::operator bool() const {
		return _kl::li && _lnr_it != _kl::li->end();
	}

	void key_listener::del() {
		if (!*this) {
			return;
		}
		_kl::li->erase(_lnr_it);
		_lnr_it = _kl::li->end();
	}

	bool is_key_down(int code) {
		auto it = _kl::downs.find(code);
		if (it != _kl::downs.end()) {
			return true;
		}
		return false;
	}

	//const char *key_code_to_str(int code);

	namespace _hkl {
		std::unordered_map<int, bool /* is_prevent_default */> downs;
		std::unique_ptr<std::unordered_map<int, std::list<std::shared_ptr<std::function<bool(hotkey_t, bool)>>>>> map;

		void recv() {
			if (!_hkl::map) {
				return;
			}
			for (auto &pr : *_hkl::map) {
				bool down;
				auto it = downs.find(pr.first);
				if (ntv::CONTROLS::IS_CONTROL_PRESSED(0, pr.first) || ntv::CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, pr.first)) {
					if (it != downs.end()) {
						if (it->second) {
							ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, pr.first, true);
						}
						continue;
					}
					downs[pr.first] = false;
					down = true;
				} else if (it != downs.end()) {
					downs.erase(it);
					down = false;
				} else {
					continue;
				}
				auto hk_val = pr.first;
				go([hk_val, down]() {
					auto it = _hkl::map->find(hk_val);
					if (it == _hkl::map->end()) {
						return;
					}
					std::queue<std::weak_ptr<std::function<bool(hotkey_t, bool)>>> qu;
					for (auto &lnr_sp : it->second) {
						qu.emplace(lnr_sp);
					}
					while (qu.size()) {
						auto lnr_sp = qu.front().lock();
						qu.pop();
						if (lnr_sp) {
							if (!(*lnr_sp)(static_cast<hotkey_t>(hk_val), down)) {
								if (down) {
									downs[hk_val] = true;
									ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, hk_val, true);
								}
								return;
							}
						}
					}
				});
			}
		}
	}

	hotkey_listener::hotkey_listener(std::initializer_list<hotkey_t> hks, std::function<bool(hotkey_t, bool)> lnr) {
		if (!hks.size()) {
			return;
		}
		if (!_hkl::map) {
			_hkl::map.reset(new std::unordered_map<int, std::list<std::shared_ptr<std::function<bool(hotkey_t, bool)>>>>);
		}
		std::shared_ptr<std::function<bool(hotkey_t, bool)>> lnr_sp(
			std::make_shared<std::function<bool(hotkey_t, bool)>>(
				lnr ?
				std::move(lnr) :
				[](hotkey_t, bool)->bool {
					return false;
				}
			)
		);
		for (auto hk : hks) {
			auto b = static_cast<int>(hk);
			_hks.emplace_back(b);
			auto &lnrs = (*_hkl::map)[b];
			lnrs.emplace_back(lnr_sp);
			_lnr_its.emplace_back(--lnrs.end());
		}
	}

	hotkey_listener::hotkey_listener(hotkey_t hk, std::function<bool(hotkey_t, bool)> lnr) : hotkey_listener({hk}, lnr) {}

	hotkey_listener::hotkey_listener(hotkey_listener &&src) : _hks(std::move(src._hks)), _lnr_its(std::move(src._lnr_its)) {}

	hotkey_listener &hotkey_listener::operator=(hotkey_listener &&src) {
		del();
		_hks = std::move(src._hks);
		_lnr_its = std::move(src._lnr_its);
		return *this;
	}

	hotkey_listener::operator bool() const {
		return _hkl::map && _hks.size();
	}

	void hotkey_listener::del() {
		if (!*this) {
			return;
		}
		for (size_t i = 0; i < _hks.size(); ++i) {
			auto it = _hkl::map->find(_hks[i]);
			if (it != _hkl::map->end()) {
				it->second.erase(_lnr_its[i]);
				if (it->second.empty()) {
					_hkl::map->erase(it);
				}
			}
		}
		_hks.clear();
		_lnr_its.clear();
	}

	vector2_i _mouse_pos;

	vector2 mouse_pos() {
		auto rez = screen::resolution();
		return { static_cast<float>(_mouse_pos.x) / rez.x, static_cast<float>(_mouse_pos.y) / rez.y };
	}

	vector2_i mouse_pos_i() {
		return _mouse_pos;
	}

} /* nob */
