#pragma once

#include "ntv.hpp"
#include "hash.hpp"
#include "script.hpp"
#include "gc.hpp"

#include <array>
#include <string>
#include <vector>

namespace nob {
	class model : private hasher {
		public:
			constexpr model() : hasher(), _loaded(0) {}

			constexpr model(std::nullptr_t) : hasher(), _loaded(0) {}

			constexpr model(hash_t h) : hasher(h), _loaded(0) {}

			constexpr model(const char *c_str) : hasher(c_str), _loaded(0) {}

			model(const std::string &str) : hasher(str), _loaded(0) {}

			constexpr model(const hasher &hr) : hasher(hr), _loaded(0) {}

			constexpr model(const model &src) : hasher(static_cast<const hasher &>(src)), _loaded(0) {}

			model &operator=(const model &src) {
				free();
				static_cast<hasher &>(*this) = static_cast<const hasher &>(src);
				return *this;
			}

			constexpr model(model &&src) : hasher(static_cast<const hasher &>(src)), _loaded(src._loaded) {
				if (src._loaded == this_script::gameplay_id) {
					src._loaded = 0;
				}
			}

			model &operator=(model &&src) {
				free();
				static_cast<hasher &>(*this) = static_cast<const hasher &>(src);
				if (src._loaded == this_script::gameplay_id) {
					_loaded = src._loaded;
					src._loaded = 0;
				}
				return *this;
			}

			~model() {
				free();
			}

			using native_handle_t = hash_t;

			native_handle_t native_handle() const {
				return hash();
			}

			operator native_handle_t() const {
				return hash();
			}

			operator bool() const {
				return hash() && ntv::STREAMING::IS_MODEL_IN_CDIMAGE(hash()) && ntv::STREAMING::IS_MODEL_VALID(hash());
			}

			std::string name() const {
				return hasher::src_str();
			}

			bool is_loaded() const {
				assert(*this);

				return ntv::STREAMING::HAS_MODEL_LOADED(hash());
			}

			bool is_vehicle() const {
				assert(*this);

				return ntv::STREAMING::IS_MODEL_A_VEHICLE(hash());
			}

			const model &load() {
				assert(*this);

				start:

				if (is_loaded()) {
					return *this;
				}

				auto h = hash();
				ntv::STREAMING::REQUEST_MODEL(h);

				auto cur_gpid = this_script::gameplay_id.load();

				while (!is_loaded()) {
					yield();
					if (cur_gpid != this_script::gameplay_id) {
						goto start;
					}
				}

				_loaded = cur_gpid;

				gc::delegate(*this, [h]() {
					ntv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(h);
				});

				return *this;
			}

			void free() {
				if (_loaded == this_script::gameplay_id) {
					gc::try_free(*this);
					_loaded = 0;
				}
			}

		private:
			size_t _loaded;
	};
} /* nob */
