#pragma once

#include "ntv/base.hpp"
#include "script.hpp"

namespace nob {
	template <typename T>
	class loader {
		public:
			template <typename... A>
			constexpr loader(A&&... a) : _res(std::forward<A>(a)...), _owned(0) {}

			constexpr loader(loader &src) :
				loader(static_cast<const loader &>(src))
			{}

			constexpr loader(const loader &src) :
				_res(src._res),
				_owned(0)
			{}

			loader &operator=(const loader &src) {
				free();
				_res = src._res;
				return *this;
			}

			loader(loader &&src) :
				_res(std::move(src._res)),
				_owned(src._owned)
			{
				if (src._owned) {
					src._owned = 0;
				}
			}

			loader &operator=(loader &&src) {
				free();
				_res = std::move(src._res);
				if (src._owned) {
					_owned = src._owned;
					src._owned = 0;
				}
				return *this;
			}

			~loader() {
				free();
			}

			const T &load() {
				if (_res.is_loaded()) {
					return _res;
				}
				_res.load();
				_owned = this_script::first_frame_count;
				return _res;
			}

			operator const T &() {
				return load();
			}

			operator typename T::native_handle_t() {
				return load().native_handle();
			}

			void free() {
				if (_owned) {
					if (!in_task()) {
						return;
					}
					if (
						*ntv::game_state == ntv::game_state_t::playing &&
						_owned == this_script::first_frame_count &&
						_res.is_loaded()
					) {
						_res.free();
					}
					_owned = 0;
				}
			}

			void detach() {
				if (_owned) {
					_owned = 0;
				}
			}

		private:
			T _res;
			size_t _owned;
	};
} /* nob */
