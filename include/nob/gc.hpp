#pragma once

#include "hash.hpp"
#include "script.hpp"

#include <unordered_map>
#include <typeindex>
#include <type_traits>
#include <functional>

namespace nob {
	namespace gc {
		struct _res_info {
			size_t ref_count = 0;
			std::function<void()> free;
		};

		extern std::unordered_map<std::type_index, std::unordered_map<hash_t, _res_info>> _map;

		template <typename T>
		inline void track(const T &obj, std::function<void()> free) {
			assert(in_task());

			auto &res_info = _map[typeid(T)][hash(obj.native_handle())];
			++res_info.ref_count;
			res_info.free = free;
		}

		template <typename T>
		inline bool try_ref_inc(const T &obj) {
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
		inline bool try_ref_dec(const T &obj) {
			if (!in_task()) {
				return false;
			}

			auto &sub_map = _map[typeid(T)];
			auto it = sub_map.find(hash(obj.native_handle()));
			if (it == sub_map.end()) {
				return false;
			}
			if (!--it->second.ref_count) {
				it->second.free();
				sub_map.erase(it);
			}
			return true;
		}

		template <typename T>
		inline void untrack(const T &obj) {
			if (!in_task()) {
				return;
			}

			_map[typeid(T)].erase(hash(obj.native_handle()));
		}

		template <typename T>
		inline void untrack_onec(const T &obj) {
			if (!in_task()) {
				return;
			}

			auto &sub_map = _map[typeid(T)];
			auto it = sub_map.find(hash(obj.native_handle()));
			if (it == sub_map.end()) {
				return;
			}
			--it->second.ref_count;
		}
	};
}
