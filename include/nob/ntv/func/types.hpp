#pragma once

#include "../vars.hpp"
#include "../../program.hpp"
#include "../../shv/fhtt.hpp"

#ifdef NOB_USING_SHV_CALL
	#include "../../shv/main.hpp"

	namespace nob {
		namespace shv {
			template<typename...>
			inline void nativePushs() {}

			template<typename A, typename ...O>
			inline void nativePushs(A a, O ...o) {
				nativePush64(ntv::argument_cast<A>(a));
				nativePushs<O...>(o...);
			}

			template<typename R>
			inline R typedNativeCall() {
				return *reinterpret_cast<R *>(shv::nativeCall());
			}

			template<>
			inline void typedNativeCall<void>() {
				shv::nativeCall();
			}
		}
	}
#endif

namespace nob {
	namespace ntv {
		// Reference from http://www.dev-c.com/gtav/scripthookv/

		typedef unsigned int Void;
		typedef unsigned int Any;
		typedef unsigned int uint;
		typedef unsigned int Hash;
		typedef int Entity;
		typedef int Player;
		typedef int FireId;
		typedef int Ped;
		typedef int Vehicle;
		typedef int Cam;
		typedef int CarGenerator;
		typedef int Group;
		typedef int Train;
		typedef int Pickup;
		typedef int Object;
		typedef int Weapon;
		typedef int Interior;
		typedef int Blip;
		typedef int Texture;
		typedef int TextureDict;
		typedef int CoverPoint;
		typedef int Camera;
		typedef int TaskSequence;
		typedef int ColourIndex;
		typedef int Sphere;
		typedef int ScrHandle;

		#pragma pack(push, 1)
			struct Vector3 {
				float x;
				unsigned int _paddingx;
				float y;
				unsigned int _paddingy;
				float z;
				unsigned int _paddingz;
			};
		#pragma pack(pop)

		////////////////////////////////////////////////////////////////////////////

		class lazy_func_t {
			public:
				constexpr lazy_func_t() : _f(nullptr), _h(0), _shv_h(0) {}
				constexpr lazy_func_t(func_t func) : _f(func), _h(0), _shv_h(0) {}
				constexpr lazy_func_t(uint64_t hash, bool is_like_shv_hash = false) :
					_f(nullptr), _h(is_like_shv_hash ? 0 : hash), _shv_h(is_like_shv_hash ? hash : 0)
				{}

				void operator()(call_context_t &ctx) {
					#ifdef NOB_USING_SHV_CALL
						if (_shv_h) {
							shv::nativeInit(_shv_h);
							for (size_t i = 0; i < ctx.args_length; ++i) {
								shv::nativePush64(ctx.args_ptr[i]);
							}
							ctx.result_ptr = shv::nativeCall();
							return;
						}
					#endif

					if (!target()) {
						return;
					}

					_f(ctx);

					#ifdef DEBUG
						if (ctx._unk) {
							std::cout << "nob::ntv::lazy_func_t[" << std::hex << _h << "]: could call failed!" << std::endl;
						}
					#endif
				}

				func_t target() {
					if (!_f) {
						if (!_h) {
							if (!_shv_h) {
								return nullptr;
							}
							auto sub_map_it = shv::fhtt.find(program::version);
							if (sub_map_it == shv::fhtt.end()) {
								return nullptr;
							}
							auto it = sub_map_it->second.find(_shv_h);
							if (it == sub_map_it->second.end()) {
								return nullptr;
							}
							_h = it->second;
							if (!_h) {
								return nullptr;
							}
						}
						_f = func_table[_h];
						if (!_f) {
							return nullptr;
						}
					}
					return _f;
				}

			protected:
				func_t _f;
				uint64_t _h;
				uint64_t _shv_h;
		};

		class buffered_call_context_t : public call_context_t {
			public:
				buffered_call_context_t() {
					args_ptr = _buffer;
					result_ptr = _buffer + 32;
					_unk = 0;
				}

			private:
				uintptr_t _buffer[64];
		};

		template <typename>
		class typed_lazy_func_t;

		template <typename R, typename ...A>
		class typed_lazy_func_t<R(A...)> : public lazy_func_t {
			public:
				constexpr typed_lazy_func_t() : lazy_func_t() {}
				constexpr typed_lazy_func_t(func_t func) : lazy_func_t(func) {}
				constexpr typed_lazy_func_t(uint64_t hash, bool is_like_shv_hash = false) : lazy_func_t(hash, is_like_shv_hash) {}

				R operator()(A ...args) {
					#ifdef NOB_USING_SHV_CALL
						if (_shv_h) {
							shv::nativeInit(_shv_h);
							shv::nativePushs<A...>(args...);
							return shv::typedNativeCall<R>();
						}
					#endif

					buffered_call_context_t ctx;
					ctx.set_args<A...>(args...);
					lazy_func_t::operator()(ctx);
					return ctx.result<R>();
				}
		};
	} /* ntv */
} /* nob */
