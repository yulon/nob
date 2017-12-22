#pragma once

#include "../program.hpp"
#include "../shv/fhtt.hpp"

#ifdef NOB_USING_SHV_CALL
	#include "../shv/main.hpp"

	namespace nob {
		namespace shv {
			template<typename...>
			inline void nativePushs() {}

			template<typename A, typename... O>
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

#include <cstdint>
#include <cassert>
#include <array>
#include <cstring>
#include <iostream>

namespace nob {
	namespace ntv {
		// Reference from https://github.com/zorg93/EnableMpCars-GTAV

		class global_table_t {
			public:
				global_table_t();

				uint64_t &operator[](uint32_t hash) {
					assert(*this);

					return _base_addr[hash >> 18 & 0x3F][hash & 0x3FFFF];
				}

				uint64_t operator[](uint32_t hash) const {
					return (*const_cast<global_table_t *>(this))[hash];
				}

				operator bool() const {
					return _base_addr && *_base_addr;
				}

			private:
				uint64_t **_base_addr;
		};

		extern global_table_t global_table;

		struct script_t {
			uintptr_t _unk1[2];
			uint8_t **page_offset;
			alignas(uintptr_t) uint32_t length;
			alignas(uintptr_t) uint32_t local_count;
			alignas(uintptr_t) uint32_t native_count;
			int64_t *local_offset;
			uintptr_t _unk2;
			int64_t *native_offset;
			uintptr_t _unk3[2];
			alignas(uintptr_t) uint32_t name_hash;
			char *name;
			char **strings_offset;
			alignas(uintptr_t) uint32_t string_size;
			uintptr_t _unk4;

			bool is_valid() const {
				return length;
			}

			size_t page_count() const {
				return (length + 0x3FFF) >> 14;
			}

			size_t page_size(size_t page) const {
				return (page == page_count() - 1) ? length & 0x3FFF : 0x4000;
			}

			uintptr_t page_base(size_t page) const {
				return reinterpret_cast<uintptr_t>(page_offset[page]);
			}

			uintptr_t base() const {
				return reinterpret_cast<uintptr_t>(page_offset[0]);
			}

			size_t size() const {
				return (page_count() - 1) * 0x4000 + (length & 0x3FFF);
			}

			size_t page_from_addr(uintptr_t addr) const {
				return (addr - base()) / 0x4000;
			}

			uintptr_t code_off(size_t addr) const {
				auto page = page_from_addr(addr);
				return addr - page_base(page) + (page << 14);
			}

			uint8_t *code_off_addr(size_t off) const {
				return &page_offset[off >> 14][off & 0x3FFF];
			}

			char *get_string(size_t str_pos) const {
				return str_pos >= string_size ? NULL : &strings_offset[str_pos >> 14][str_pos & 0x3FFF];
			}
		};

		struct script_list_t {
			struct node_t {
				script_t *script;
				int _unk;
				uint32_t hash;
			};

			node_t *nodes;
			uint8_t _unk[16];
			uint32_t size;

			node_t *find(const char *name) const;
		};

		extern script_list_t *script_list;

		////////////////////////////////////////////////////////////////////////////

		// Reference from https://github.com/ivanmeler/OpenVHook

		struct call_context_t;

		typedef void (__cdecl *func_t)(call_context_t &);

		struct call_context_t {
			uintptr_t *result_ptr;
			uint32_t arg_count;
			uintptr_t *args_ptr;
			uint32_t res_count;
			uintptr_t res_cache[32 * 24];

			static func_t fix_res_fn;

			////////////////////////////////////////////////////////////////////////

			template <typename T>
			void set_arg(size_t i, T v) {
				reinterpret_cast<tmd::unsafe_ptr *>(args_ptr)[i] = v;
			}

			template <typename T>
			T arg(size_t i) const {
				return *reinterpret_cast<T *>(&args_ptr[i]);
			}

			template<size_t>
			void _set_args() {}

			template<size_t i, typename A, typename... O>
			void _set_args(A a, O ...o) {
				set_arg<A>(i, a);
				_set_args<i + 1, O...>(o...);
			}

			template<typename... A>
			void set_args(A... a) {
				arg_count = sizeof...(A);
				_set_args<0, A...>(a...);
				res_count = 0;
			}

			template <typename T>
			void set_result(T v) {
				*reinterpret_cast<T *>(result_ptr) = v;
			}

			template <typename T>
			T result() const {
				return *reinterpret_cast<T *>(result_ptr);
			}

			void fix_res() {
				if (res_count) {
					if (fix_res_fn) {
						fix_res_fn(*this);
					}
					#ifdef DEBUG
						else {
							std::cout << "nob::ntv::call_context_t::fix_res_fn: is null!" << std::endl;
							return;
						}
					#endif
				}
			}

			void print(const std::string &mark = "") {
				if (!mark.empty()) {
					std::cout << mark << std::endl;
				}

				std::cout
				<< "args_ptr: " << args_ptr << std::endl
				<< "arg_count: " << arg_count << std::endl
				<< "result_ptr: " << result_ptr << std::endl
				<< "res_count: " << res_count << std::endl;
			}
		};

		template <>
		inline void call_context_t::result<void>() const {}

		static func_t nullfunc = nullptr;

		class func_table_t {
			public:
				struct node_t {
					node_t *nxt;
					func_t funcs[7];
					uint32_t len;
					uint64_t hashes[7];

					node_t *next() const {
						return nxt;
					}

					uint32_t length() const {
						return len;
					}

					uint64_t hash(uint8_t ix) const {
						return hashes[ix];
					}
				};

				struct node_1290_t {
					uint64_t nxt1;
					uint64_t nxt2;
					func_t funcs[7];
					uint32_t len1;
					uint32_t len2;
					uint64_t hashes;

					node_1290_t *next() const {
						uintptr_t result;
						auto v5 = reinterpret_cast<uintptr_t>(&nxt1);
						uint64_t v12 = 2;
						auto v13 = v5 ^ nxt2;
						auto v14 = (char *)&result - v5;
						do {
							*(uint32_t*)&v14[v5] = v13 ^ *(uint32_t*)v5;
							v5 += 4;
							--v12;
						} while (v12);
						return reinterpret_cast<node_1290_t *>(result);
					}

					uint32_t length() const {
						return ((uintptr_t)&len1) ^ len1 ^ len2;
					}

					uint64_t hash(uint8_t ix) const {
						uintptr_t n_addr = 16 * ix + reinterpret_cast<uintptr_t>(&nxt1) + 0x54;
						uint64_t v8 = 2;
						uint64_t n_result;
						auto v11 = (char *)&n_result - n_addr;
						auto v10 = n_addr ^ *(uint32_t *)(n_addr + 8);
						do {
							*(uint32_t *)&v11[n_addr] = v10 ^ *(uint32_t *)(n_addr);
							n_addr += 4;
							--v8;
						} while (v8);
						return n_result;
					}
				};

				func_table_t();

				func_t &operator[](uint64_t hash) const {
					return program::version < 1290 ? _get<node_t>(hash) : _get<node_1290_t>(hash);
				}

				operator bool() const {
					return _nodes;
				}

			private:
				uintptr_t _nodes;

				template <typename T>
				func_t &_get(uint64_t hash) const {
					if (!_nodes) {
						return nullfunc;
					}
					for (auto n = reinterpret_cast<T **>(_nodes)[hash & 0xFF]; n; n = n->next()) {
						for (uint8_t i = 0; i < n->length(); ++i) {
							if (n->hash(i) == hash) {
								return n->funcs[i];
							}
						}
					}
					return nullfunc;
				}
		};

		extern func_table_t func_table;

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
							for (size_t i = 0; i < ctx.arg_count; ++i) {
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

					ctx.fix_res();
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

		class full_call_context_t : public call_context_t {
			public:
				full_call_context_t() {
					args_ptr = _stack;
					result_ptr = _stack + 32;
				}

			private:
				uintptr_t _stack[64];
		};

		extern full_call_context_t _dft_call_ctx;

		template <typename>
		class typed_lazy_func_t;

		template <typename R, typename... A>
		class typed_lazy_func_t<R(A...)> : public lazy_func_t {
			public:
				constexpr typed_lazy_func_t() : lazy_func_t() {}
				constexpr typed_lazy_func_t(func_t func) : lazy_func_t(func) {}
				constexpr typed_lazy_func_t(uint64_t hash, bool is_like_shv_hash = false) : lazy_func_t(hash, is_like_shv_hash) {}

				R operator()(A... args) {
					#ifdef NOB_USING_SHV_CALL
						if (_shv_h) {
							shv::nativeInit(_shv_h);
							shv::nativePushs<A...>(args...);
							return shv::typedNativeCall<R>();
						}
					#endif

					_dft_call_ctx.set_args<A...>(args...);
					lazy_func_t::operator()(_dft_call_ctx);
					return _dft_call_ctx.result<R>();
				}
		};

		////////////////////////////////////////////////////////////////////////

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

		struct Vector3 {
			alignas(uintptr_t) float x, y, z;
		};
	} /* ntv */
} /* nob */
