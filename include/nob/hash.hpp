#pragma once

#include "ntv.hpp"

#include <string>

namespace nob {
	typedef unsigned int hash_t;

	static inline constexpr hash_t hash(const char *str) {
		hash_t h = 0;

		for (size_t i = 0; str[i] != 0; ++i) {
			h += (str[i] > 64 && str[i] < 91 ? str[i] + 32 : str[i]);
			h += (h << 10);
			h ^= (h >> 6);
		}

		h += (h << 3);
		h ^= (h >> 11);
		h += (h << 15);

		return h;
	}

	static inline hash_t hash(const std::string &str) {
		return hash(str.c_str());
	}

	class hasher {
		public:
			const hash_t hash;

			constexpr hasher(hash_t h = 0) : hash(h), _str(nullptr) {}
			constexpr hasher(const char *c_str) : hash(nob::hash(c_str)), _str(c_str) {}
			hasher(const std::string &str) : hasher(str.c_str()) {}

			const char *src_c_str() const {
				if (!_str && hash && ntv::STREAMING::IS_MODEL_A_VEHICLE(hash)) {
					return ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash);
				}
				return _str;
			}

			std::string src_str() const {
				return src_c_str();
			}

			bool operator==(const hasher &hr) const {
				return hash == hr.hash;
			}

			bool operator!=(const hasher &hr) const {
				return hash != hr.hash;
			}

			operator bool() const {
				return hash;
			}

		private:
			const char *_str;
	};

	class cpp_hash {
		public:
			constexpr size_t operator()(const hasher &hr) {
				return static_cast<size_t>(hr.hash);
			}
	};
}
