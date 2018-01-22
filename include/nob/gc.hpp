#pragma once

#include "hash.hpp"
#include "script.hpp"

#include <unordered_map>
#include <typeindex>
#include <type_traits>
#include <functional>

namespace nob {
	namespace gc {
		extern std::unordered_map<std::type_index, std::unordered_map<hash_t, std::function<void()>>> _map;

		template <typename T>
		inline void delegate(const T &obj, std::function<void()> free) {
			assert(in_task());

			_map[typeid(T)][hash(obj.native_handle())] = free;
		}

		template <typename T>
		inline bool try_free(const T &obj) {
			if (this_script::exiting) {
				return false;
			}

			assert(in_task());

			auto &sub_map = _map[typeid(T)];
			auto it = sub_map.find(hash(obj.native_handle()));
			if (it == sub_map.end()) {
				return false;
			}
			it->second();
			sub_map.erase(it);
			return true;
		}

		template <typename T>
		inline void undelegate(const T &obj) {
			if (this_script::exiting) {
				return;
			}

			assert(in_task());

			_map[typeid(T)].erase(hash(obj.native_handle()));
		}
	};
}
