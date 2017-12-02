#pragma once

#include "ntv.hpp"
#include "hash.hpp"
#include "script.hpp"

#include <array>
#include <string>
#include <vector>

namespace nob {
	class model_info : public hasher {
		public:
			using hasher::hasher;

			constexpr model_info(const hasher &hr) : hasher(hr.hash()) {}

			operator hash_t() const {
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
				return ntv::STREAMING::HAS_MODEL_LOADED(hash());
			}

			bool is_vehicle() const {
				return ntv::STREAMING::IS_MODEL_A_VEHICLE(hash());
			}
	};

	class model : public model_info {
		public:
			using model_info::model_info;

			constexpr model(const model_info &mi) : model_info(mi) {}

			~model() {
				free();
			}

			operator hash_t() const {
				if (!*this) {
					return 0;
				}
				if (is_loaded()) {
					return hash();
				}
				ntv::STREAMING::REQUEST_MODEL(hash());
				if (!is_loaded()) {
					auto h = hash();
					wait([h]()->bool {
						return ntv::STREAMING::HAS_MODEL_LOADED(h);
					});
				}
				return hash();
			}

			void free() const {
				if (hash() && is_loaded()) {
					ntv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash());
				}
			}
	};
} /* nob */
