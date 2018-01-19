#include <nob/object.hpp>
#include <nob/ntv.hpp>
#include <nob/script.hpp>

#include <unordered_map>
#include <cassert>

namespace nob {
	std::unordered_map<int, entity> _ety_map;

	void entity::_gc_mk() const {
		assert(in_task());

		if (_h) {
			_ety_map[_h] = *this;
		}
	}

	void entity::_gc_unmk() const {
		if (!this_script::exiting) {
			_ety_map.erase(_h);
		}
	}

	initer _ety_initer([]() {
		if (_ety_map.size()) {
			_ety_map.clear();
		}
	});

	exiter _ety_exiter([]() {
		for (auto &it : _ety_map) {
			if (it.second) {
				if (it.second.is_character()) {
					character(it.second).del();
				} else if (it.second.is_vehicle()) {
					vehicle(it.second).del();
				} else {
					it.second.del();
				}
			}
		}
	});
}
