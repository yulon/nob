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
			constexpr model() : hasher(), _tslc(0) {}

			constexpr model(std::nullptr_t) : hasher(), _tslc(0) {}

			constexpr model(hash_t h) : hasher(h), _tslc(0) {}

			constexpr model(const char *c_str) : hasher(c_str), _tslc(0) {}

			model(const std::string &str) : hasher(str), _tslc(0) {}

			constexpr model(const hasher &hr) : hasher(hr), _tslc(0) {}

			constexpr model(const model &src) : hasher(static_cast<const hasher &>(src)), _tslc(0) {}

			model &operator=(const model &src) {
				free();
				static_cast<hasher &>(*this) = src;
				return *this;
			}

			model(model &&src) : hasher(src), _tslc(src._tslc) {
				if (src._tslc == this_script::load_count) {
					src._tslc = 0;
				}
			}

			model &operator=(model &&src) {
				free();
				static_cast<hasher &>(*this) = static_cast<const hasher &>(src);
				if (src._tslc == this_script::load_count) {
					_tslc = src._tslc;
					src._tslc = 0;
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

			model &load() {
				assert(*this);

				if (_tslc == this_script::load_count) {
					return *this;
				}

				start:

				if (gc::try_ref(*this)) {
					assert(is_loaded());

					_tslc = this_script::load_count;
					return *this;
				}

				auto h = hash();
				ntv::STREAMING::REQUEST_MODEL(h);

				auto cur_lc = this_script::load_count;

				while (!is_loaded()) {
					yield();
					if (cur_lc != this_script::load_count) {
						goto start;
					}
				}

				_tslc = cur_lc;

				gc::delegate(*this, [h]() {
					if (ntv::STREAMING::HAS_MODEL_LOADED(h)) {
						ntv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(h);
					}
				});

				return *this;
			}

			void free() {
				if (_tslc && _tslc == this_script::load_count) {
					gc::free(*this);
					_tslc = 0;
				}
			}

		private:
			size_t _tslc;
	};
} /* nob */
