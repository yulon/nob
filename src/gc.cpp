#include <nob/gc.hpp>
#include <nob/script.hpp>

namespace nob {
	namespace gc {
		std::unordered_map<std::type_index, std::unordered_map<hash_t, _info_t>> _map;

		on_load _initer([]() {
			if (_map.size()) {
				_map.clear();
			}
		});

		on_unload _exiter([]() {
			for (auto &pr : _map) {
				for (auto &sub_map_pr : pr.second) {
					sub_map_pr.second.free();
				}
			}
		});
	}
}
