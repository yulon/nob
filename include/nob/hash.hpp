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

	class hasher {
		public:
			const hash_t hash;

			constexpr hasher(hash_t h = 0) : hash(h), _str(nullptr) {}
			constexpr hasher(const char *str) : hash(nob::hash(str)), _str(str) {}
			hasher(const std::string &str) : hasher(str.c_str()) {}

			const char *src_str() const {
				if (!_str && hash && ntv::STREAMING::IS_MODEL_A_VEHICLE(hash)) {
					const_cast<char *&>(_str) = const_cast<char *>(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash));
				}
				return _str;
			}

		private:
			const char *_str;
	};
}
