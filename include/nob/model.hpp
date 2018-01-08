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
				assert(hash());

				return ntv::STREAMING::HAS_MODEL_LOADED(hash());
			}

			bool is_vehicle() const {
				assert(hash());

				return ntv::STREAMING::IS_MODEL_A_VEHICLE(hash());
			}
	};

	class model : public model_info {
		public:
			constexpr model(hash_t h = 0) : model_info(h), _loader(0) {}

			constexpr model(const char *c_str) : model_info(c_str), _loader(0) {}

			model(const std::string &str) : model_info(str.c_str()), _loader(0) {}

			constexpr model(const model_info &mi) : model_info(mi), _loader(0) {}

			constexpr model(const model &m) :
				model_info(static_cast<const model_info &>(m)),
				_loader(0)
			{}

			model &operator=(const model &m) {
				free();
				static_cast<model_info &>(*this) = static_cast<const model_info &>(m);
				return *this;
			}

			model(model &&m) :
				model_info(static_cast<const model_info &>(m)),
				_loader(m._loader)
			{
				if (m._loader) {
					m._loader = 0;
				}
			}

			model &operator=(model &&m) {
				free();
				static_cast<model_info &>(*this) = static_cast<const model_info &>(m);
				if (m._loader) {
					_loader = m._loader;
					m._loader = 0;
				}
				return *this;
			}

			~model() {
				free();
			}

			hash_t load() {
				assert(hash());

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
				_loader = this_script::first_frame_count;
				return hash();
			}

			operator hash_t() {
				return load();
			}

			void free() {
				if (_loader) {
					if (!in_task()) {
						return;
					}

					if (
						*ntv::game_state == ntv::game_state_t::playing &&
						_loader == this_script::first_frame_count &&
						is_loaded()
					) {
						ntv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash());
					}
					_loader = 0;
				}
			}

			void detach() {
				if (_loader) {
					_loader = 0;
				}
			}

		private:
			size_t _loader;
	};
} /* nob */
