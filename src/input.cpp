#include <nob/input.hpp>
#include <nob/ntv.hpp>
#include <nob/screen.hpp>
#include <nob/script.hpp>

#include <windows.h>

#include <cassert>
#include <cstring>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace nob {

std::queue<std::function<void()>> _inputs;

namespace _kl {

std::unordered_set<int> downs;

on_load _clear_downs([]() { downs.clear(); });

std::unique_ptr<std::list<std::shared_ptr<std::function<bool(int, bool)>>>>
	lnr_li;

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
	if (!lnr_li) {
		return;
	}
	_inputs.push([code, down]() {
		std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
		for (auto &lnr_sp : *lnr_li) {
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
	if (lnr_li) {
		for (auto code : downs) {
			_inputs.push([code]() {
				std::queue<std::weak_ptr<std::function<bool(int, bool)>>> qu;
				for (auto &lnr_sp : *lnr_li) {
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

} // namespace _kl

key_listener::key_listener() {
	if (!_kl::lnr_li) {
		_kl::lnr_li.reset(
			new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
	}
	_lnr_it = _kl::lnr_li->end();
}

key_listener::key_listener(std::function<bool(int, bool)> key_listener) {
	if (!_kl::lnr_li) {
		_kl::lnr_li.reset(
			new std::list<std::shared_ptr<std::function<bool(int, bool)>>>);
	}
	_kl::lnr_li->emplace_front(std::make_shared<std::function<bool(int, bool)>>(
		std::move(key_listener)));
	_lnr_it = _kl::lnr_li->begin();
}

key_listener::key_listener(key_listener &&src) : _lnr_it(src._lnr_it) {
	if (src._lnr_it != _kl::lnr_li->end()) {
		src._lnr_it = _kl::lnr_li->end();
	}
}

key_listener &key_listener::operator=(key_listener &&src) {
	del();
	if (src._lnr_it != _kl::lnr_li->end()) {
		_lnr_it = src._lnr_it;
		src._lnr_it = _kl::lnr_li->end();
	}
	return *this;
}

key_listener::operator bool() const {
	return _kl::lnr_li && _lnr_it != _kl::lnr_li->end();
}

void key_listener::del() {
	if (!*this || !_kl::lnr_li) {
		return;
	}
	_kl::lnr_li->erase(_lnr_it);
	_lnr_it = _kl::lnr_li->end();
}

bool is_key_down(int code) {
	auto it = _kl::downs.find(code);
	if (it != _kl::downs.end()) {
		return true;
	}
	return false;
}

// const char *key_code_to_str(int code);

namespace ui {
extern bool _fm_opened;
}

namespace _hkl {

std::unordered_set<int> downs;

on_load clear_downs([]() { downs.clear(); });

std::unique_ptr<std::unordered_map<
	int,
	std::list<std::shared_ptr<std::function<bool(hotkey_t, bool)>>>>>
	lnr_li_map;
std::unique_ptr<std::unordered_map<int, size_t>> blk_map;

void handle(int hk_val, bool down) {
	auto it = _hkl::lnr_li_map->find(hk_val);
	if (it == _hkl::lnr_li_map->end()) {
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
				return;
			}
		}
	}
}

void go_handle(int hk_val, bool down) {
	go([hk_val, down]() { handle(hk_val, down); });
}

void recv() {
	if (!lnr_li_map || ui::_fm_opened) {
		return;
	}
	for (auto &pr : *lnr_li_map) {
		auto it = downs.find(pr.first);
		if (ntv::CONTROLS::IS_CONTROL_PRESSED(0, pr.first) ||
			ntv::CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, pr.first)) {
			if (it == downs.end()) {
				downs.emplace(pr.first);
				go_handle(pr.first, true);
			}
		} else if (it != downs.end()) {
			downs.erase(it);
			go_handle(pr.first, false);
		}
	}
}

void prevent_defaults() {
	if (!blk_map || ui::_fm_opened) {
		return;
	}
	for (auto &pr : *blk_map) {
		if (pr.second) {
			ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, pr.first, true);
		}
	}
}

void reset() {
	for (auto hk_val : downs) {
		_inputs.emplace([hk_val]() { handle(hk_val, false); });
	}
	downs.clear();
}

} // namespace _hkl

hotkey_listener::hotkey_listener(
	std::initializer_list<hotkey_t> hks,
	std::function<bool(hotkey_t, bool)> lnr,
	bool is_prevent_default) :
	_pd(is_prevent_default) {
	assert(hks.size() && (lnr || is_prevent_default));

	if (!_hkl::lnr_li_map) {
		_hkl::lnr_li_map.reset(
			new std::unordered_map<
				int,
				std::list<
					std::shared_ptr<std::function<bool(hotkey_t, bool)>>>>);
	}

	if (!_hkl::blk_map) {
		_hkl::blk_map.reset(new std::unordered_map<int, size_t>);
	}

	std::shared_ptr<std::function<bool(hotkey_t, bool)>> lnr_sp;
	if (lnr) {
		lnr_sp = std::make_shared<std::function<bool(hotkey_t, bool)>>(
			std::move(lnr));
	}

	for (auto hk : hks) {
		auto hk_val = static_cast<int>(hk);
		_hks.emplace_back(hk_val);

		if (lnr_sp.get()) {
			auto &lnrs = (*_hkl::lnr_li_map)[hk_val];
			lnrs.emplace_front(lnr_sp);
			_lnr_its.emplace_back(lnrs.begin());
		}

		if (is_prevent_default) {
			auto it = _hkl::blk_map->find(hk_val);
			if (it == _hkl::blk_map->end()) {
				(*_hkl::blk_map)[hk_val] = 1;
			} else {
				++it->second;
			}
		}
	}
}

hotkey_listener::hotkey_listener(hotkey_listener &&src) :
	_hks(std::move(src._hks)),
	_lnr_its(std::move(src._lnr_its)),
	_pd(src._pd) {}

hotkey_listener &hotkey_listener::operator=(hotkey_listener &&src) {
	del();
	_hks = std::move(src._hks);
	_lnr_its = std::move(src._lnr_its);
	_pd = src._pd;
	return *this;
}

hotkey_listener::operator bool() const {
	return _hkl::lnr_li_map && _hkl::blk_map && _hks.size();
}

void hotkey_listener::prevent_default(bool toggle) {
	if (!*this) {
		return;
	}
	if (toggle) {
		if (_pd) {
			return;
		}
		for (size_t i = 0; i < _hks.size(); ++i) {
			auto it = _hkl::blk_map->find(_hks[i]);
			if (it == _hkl::blk_map->end()) {
				(*_hkl::blk_map)[_hks[i]] = 1;
			} else {
				++it->second;
			}
		}
	} else if (_pd) {
		for (size_t i = 0; i < _hks.size(); ++i) {
			--(*_hkl::blk_map)[_hks[i]];
		}
	}
}

void hotkey_listener::del() {
	if (!*this || !_hkl::lnr_li_map || !_hkl::blk_map) {
		return;
	}
	for (size_t i = 0; i < _hks.size(); ++i) {
		if (_lnr_its.size()) {
			(*_hkl::lnr_li_map)[_hks[i]].erase(_lnr_its[i]);
		}
		if (_pd) {
			--(*_hkl::blk_map)[_hks[i]];
		}
	}
	_hks.clear();
	_lnr_its.clear();
}

bool is_hotkey_down(hotkey_t hk) {
	return ntv::CONTROLS::IS_CONTROL_PRESSED(0, static_cast<int>(hk)) ||
		   ntv::CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, static_cast<int>(hk));
}

vector2_i _mouse_pos;

vector2 mouse_pos() {
	auto rez = screen::resolution();
	return {static_cast<float>(_mouse_pos.x) / rez.x,
			static_cast<float>(_mouse_pos.y) / rez.y};
}

vector2_i mouse_pos_i() {
	return _mouse_pos;
}

} // namespace nob
