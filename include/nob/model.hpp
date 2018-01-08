#pragma once

#include "ntv.hpp"
#include "hash.hpp"
#include "script.hpp"

#include <array>
#include <string>
#include <vector>

namespace nob {
	class model : public hasher {
		public:
			using hasher::hasher;

			constexpr model(const hasher &hr) : hasher(hr.hash()) {}

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

			std::string src_str() const = delete;

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

			const model &load() const {
				assert(*this);

				ntv::STREAMING::REQUEST_MODEL(hash());
				if (!is_loaded()) {
					auto h = hash();
					wait([h]()->bool {
						return ntv::STREAMING::HAS_MODEL_LOADED(h);
					});
				}
				return *this;
			}

			void free() const {
				ntv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash());
			}
	};
} /* nob */
