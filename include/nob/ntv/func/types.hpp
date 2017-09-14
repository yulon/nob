#include "../vars.hpp"

#include "../../shv/fhtt.hpp"

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
		typedef struct
		{
			float x;
			unsigned int _paddingx;
			float y;
			unsigned int _paddingy;
			float z;
			unsigned int _paddingz;
		} Vector3;
		#pragma pack(pop)

		////////////////////////////////////////////////////////////////////////////

		template <uint8_t N>
		class nt_lazy_func_t {
			public:
				nt_lazy_func_t() : _f(nullptr), _h(0) {}
				nt_lazy_func_t(func_t func) : _f(func), _h(0) {}
				nt_lazy_func_t(uint64_t hash, bool is_like_shv_hash = false) : _f(nullptr), _h(hash), _tr(is_like_shv_hash) {}

				uintptr_t operator()(std::array<uintptr_t, N> args) {
					if (!target()) {
						return 0;
					}

					call_context_t ctx;
					uintptr_t result;

					ctx.args_len = N;
					if (N) {
						ctx.args = args.data();
						ctx.result = args;
					} else {
						ctx.args = &result;
						ctx.result = &result;
					}

					_f(&ctx);

					return ctx.result[0];
				}

				func_t target() {
					if (!_f) {
						if (_h) {
							if (_tr) {
								_tr = false;
								auto pair = shv::func_hash_tr_tab.find(_h);
								if (pair == shv::func_hash_tr_tab.end()) {
									_h = 0;
									return 0;
								}
								_h = pair->second;
							}

							_f = func_table[_h];
							if (!_f) {
								_h = 0;
								return 0;
							}
						} else {
							return 0;
						}
					}
					return _f;
				}

			private:
				func_t _f;
				uint64_t _h;
				bool _tr;
		};

		template <typename R, typename... A>
		class lazy_func_t;

		template <typename R, typename... A>
		class lazy_func_t<R(A...)> : public nt_lazy_func_t<sizeof...(A)> {
			public:
				lazy_func_t() : nt_lazy_func_t<sizeof...(A)>() {}
				lazy_func_t(func_t func) : nt_lazy_func_t<sizeof...(A)>(func) {}
				lazy_func_t(uint64_t hash, bool is_like_shv_hash = false) : nt_lazy_func_t<sizeof...(A)>(hash, is_like_shv_hash) {}

				R operator()(A... args) {
					return static_cast<R>(nt_lazy_func_t<sizeof...(A)>::operator()({static_cast<uintptr_t>(args)...}));
				}
		};

		template <typename... A>
		class lazy_func_t<void(A...)> : public nt_lazy_func_t<sizeof...(A)> {
			public:
				lazy_func_t() : nt_lazy_func_t<sizeof...(A)>() {}
				lazy_func_t(func_t func) : nt_lazy_func_t<sizeof...(A)>(func) {}
				lazy_func_t(uint64_t hash, bool is_like_shv_hash = false) : nt_lazy_func_t<sizeof...(A)>(hash, is_like_shv_hash) {}

				void operator()(A... args) {
					nt_lazy_func_t<sizeof...(A)>::operator()({static_cast<uintptr_t>(args)...});
				}
		};
	} /* ntv */
} /* nob */
