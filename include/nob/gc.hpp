#pragma once

#include "hash.hpp"
#include "script.hpp"

#include <unordered_map>
#include <typeindex>
#include <type_traits>
#include <functional>

namespace nob {
	namespace gc {
		struct _info_t {
			size_t ref_count = 0;
			std::function<void()> free;
		};
		extern std::unordered_map<std::type_index, std::unordered_map<hash_t, _info_t>> _map;

		template <typename T>
		inline void delegate(const T &obj, std::function<void()> free) {
			assert(in_task());

			auto &info = _map[typeid(T)][hash(obj.native_handle())];
			++info.ref_count;
			info.free = free;
		}

		template <typename T>
		inline bool try_ref(const T &obj) {
			assert(in_task());

			auto &sub_map = _map[typeid(T)];
			auto it = sub_map.find(hash(obj.native_handle()));
			if (it == sub_map.end()) {
				return false;
			}
			++it->second.ref_count;
			return true;
		}

		template <typename T>
		inline bool is_delegated(const T &obj) {
			assert(in_task());

			auto &sub_map = _map[typeid(T)];
			auto it = sub_map.find(hash(obj.native_handle()));
			if (it == sub_map.end()) {
				return false;
			}
			return true;
		}

		template <typename T>
		inline void free(const T &obj) {
			if (this_script::exiting) {
				return;
			}

			assert(in_task());

			auto &sub_map = _map[typeid(T)];
			auto it = sub_map.find(hash(obj.native_handle()));
			if (it == sub_map.end()) {
				return;
			}
			if (!--it->second.ref_count) {
				it->second.free();
				sub_map.erase(it);
			}
			return;
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
