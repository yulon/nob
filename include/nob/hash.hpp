#pragma once

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
			constexpr hasher(hash_t h = 0) : _h(h), _str(nullptr) {}
			constexpr hasher(const char *c_str) : _h(nob::hash(c_str)), _str(c_str) {}
			hasher(const std::string &str) : hasher(str.c_str()) {}

			constexpr hash_t hash() const {
				return _h;
			}

			const char *src_c_str() const;

			std::string src_str() const {
				return src_c_str();
			}

			bool operator==(const hasher &hr) const {
				return _h == hr._h;
			}

			bool operator!=(const hasher &hr) const {
				return _h != hr._h;
			}

			operator bool() const {
				return _h;
			}

		private:
			hash_t _h;
			const char *_str;
	};

	class cpp_hash {
		public:
			constexpr size_t operator()(const hasher &hr) {
				return static_cast<size_t>(hr.hash());
			}
	};
}
