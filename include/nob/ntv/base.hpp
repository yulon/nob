#pragma once

#include "../hash.hpp"
#include "../log.hpp"
#include "fhtt.hpp"

#include <rua/unsafe_ptr.hpp>

#ifdef NOB_USING_SHV_CALL
	#include "../shv.hpp"

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

#include <intrin.h>

#include <cstdint>
#include <cassert>
#include <array>
#include <cstring>
#include <thread>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <functional>

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

		#ifndef _NOB_NTV_VEC3
			#define _NOB_NTV_VEC3
			struct Vector3 {
				alignas(uintptr_t) float x, y, z;
			};
		#endif

		////////////////////////////////////////////////////////////////////////

		template <typename T>
		inline void wait_for_valid(const T &t) {
			while (!t) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}

		////////////////////////////////////////////////////////////////////////

		// Reference from https://github.com/zorg93/EnableMpCars-GTAV

		static uint64_t _bad_g;

		class global_table_t {
			public:
				uint64_t **_segments;

				operator bool() const {
					return _segments;
				}

				uint64_t &operator[](size_t off) {
					if (!*this) {
						return _bad_g;
					}
					if (!*_segments) {
						log("nob::ntv::global_table_t::_segments: not allocated!");
						return _bad_g;
					}
					return _segments[off / 0x40000 % 0x40][off % 0x40000];
				}
		};

		extern global_table_t global_table;

		struct script_list_t {
			struct script_t {
				struct info_t {
					uintptr_t _unk1[2];
					uintptr_t *code_pages;
					alignas(uintptr_t) uint32_t code_length;
					alignas(uintptr_t) uint32_t local_count;
					alignas(uintptr_t) uint32_t native_count;
					uintptr_t *local_pages;
					uintptr_t _unk2;
					uintptr_t *native_pages;
					uintptr_t _unk3[2];
					alignas(uintptr_t) uint32_t name_hash;
					const char *name;
					const char **str_pool_pages;
					alignas(uintptr_t) uint32_t str_pool_length;
					uintptr_t _unk4;

					static constexpr size_t max_page_length = 0x4000;

					size_t code_pages_count() const {
						return (code_length - 1) / max_page_length + 1;
					}

					size_t code_page_length(size_t page_ix) const {
						return (page_ix == code_pages_count() - 1) ? code_length % max_page_length : max_page_length;
					}

					size_t code_off(size_t page_ix, uintptr_t addr) const {
						return addr - code_pages[page_ix] + page_ix * max_page_length;
					}

					size_t code_off(uintptr_t addr) const {
						for (size_t i = 0; i < code_pages_count(); ++i) {
							auto diff = addr - code_pages[i];
							if (diff < max_page_length) {
								return diff + i * max_page_length;
							}
						}
						return 0;
					}

					uintptr_t code_addr(size_t off) const {
						return code_pages[off / max_page_length] + off % max_page_length;
					}

					const char *str_addr(size_t off) const {
						return &str_pool_pages[off / max_page_length][off % max_page_length];
					}
				};

				info_t *info;
				uint32_t _unk;
				uint32_t hash;

				operator bool() const {
					return info && info->code_length;
				}
			};

			script_t *scripts;
			uintptr_t _unk[2];
			uint32_t size;

			operator bool() const {
				return scripts;
			}

			script_t *find(const char *name) const {
				if (*this) {
					auto h = hash(name);
					for (size_t i = 0; i < size; i++) {
						if (scripts[i].hash == h) {
							return &scripts[i];
						}
					}
				}
				log("nob::ntv::script_list_t::find(", name, "): not found!");
				return nullptr;
			}
		};

		extern script_list_t *script_list;

		////////////////////////////////////////////////////////////////////////////

		// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/

		enum class game_state_t : uint8_t {
			playing = 0,
			preloading = 1,
			preload_blocking = 3,
			mode_menu = 5,
			loading = 6,
			reloading_archive = 8
		};

		extern game_state_t *game_state;

		extern uint32_t *fake_script_hash_count;

		template<typename T>
		class container_t {
			public:
				T *data;
				uint16_t count;
				uint16_t size;

				T &operator[](uint16_t index) {
					return data[index];
				}

				operator bool() const {
					return data;
				}
		};

		class script_thread_t {
			public:
				enum class state_t : uint32_t {
					idle,
					running,
					killed,
					unk1,
					unk2
				};

				static container_t<script_thread_t *> *pool;

				static uint32_t tls_off;

				static script_thread_t *&current() {
					return *reinterpret_cast<script_thread_t **>(*(uintptr_t *)__readgsqword(88) + tls_off);
				}

				static uint32_t *id_count;

				static void (*init_gta_data)(script_thread_t *);

				// known: call 'join()'.
				static state_t (*default_tick)(script_thread_t *, uint32_t ops_to_execute);

				// known: set 'context.state' to 'state_t::killed', and dealloc 'script_context'.
				static void (*default_kill)(script_thread_t *);

				struct vtable_t {
					void (*_dtor)(script_thread_t *);

					state_t (*reset)(script_thread_t *, uint32_t script_hash, uintptr_t *args, uint32_t arg_count);
					state_t (*join)(script_thread_t *, uint32_t ops_to_execute);
					state_t (*tick)(script_thread_t *, uint32_t ops_to_execute);
					void (*kill)(script_thread_t *);
				};

				// size should be 168
				struct context_t {
					uint32_t id;
					uint32_t fake_script_hash; // + 4 (program id)
					state_t state; // + 8
					uint32_t ip; // + 12
					uint32_t frame_sp; //
					uint32_t sp; // + 20, aka + 28
					uint32_t timer1; // + 24
					uint32_t timer2; // + 28
					uint32_t timer3; // + 32, aka + 40
					uint32_t _munk1;
					uint32_t _munk2;
					uint32_t _f2c;
					uint32_t _f30;
					uint32_t _f34;
					uint32_t _f38;
					uint32_t _f3c;
					uint32_t _f40;
					uint32_t _f44;
					uint32_t _f48;
					uint32_t _f4c;
					uint32_t stack_size; // should be +88 aka +80; stack size?

					uint32_t pad1;
					uint32_t pad2;
					uint32_t pad3;

					uint32_t _set1;

					uint8_t pad[68];
				};

				RUA_STATIC_ASSERT(sizeof(context_t) == 168);

				////////////////////////////////////////////////////////////////

				// rage thread class base
				vtable_t *vtable;
				context_t context;
				uint8_t *stack;
				uintptr_t pad;
				uintptr_t pad2;
				const char *exit_msg;

				// gta thread class base
				char script_hash_str[16]; // 208
				char unk[48];
				void *script_context; // 272
				char unk2[40];
				char flag1;
				char network_flag;
				uint16_t unk3;
				char unk4[12];
				uint8_t can_remove_blips_from_other_scripts;
				char unk5[7];

				////////////////////////////////////////////////////////////////

				script_thread_t() : stack(nullptr), script_context(nullptr), _orig_owner(nullptr) {
					context.state = state_t::killed;
					context.stack_size = 0;
				}

				script_thread_t(void (*on_frame)());

				~script_thread_t() {
					kill();
				}

				void kill();

				void set_name(const char *name) {
					std::stringstream ss;
					ss << std::hex << std::setw(8) << std::setfill('0') << hash(name);
					strcpy(script_hash_str, ss.str().c_str());
				}

				operator bool() const {
					return context.state != state_t::killed;
				}

			private:
				uintptr_t _nob_thread_class_pad[10];

				script_thread_t *_orig_owner;
				void (*_on_frame)();
				vtable_t _vtab_impl;
		};

		class script_context_pool_t {
			public:
				struct vtable_t {
					void (*_dtor)(script_context_pool_t *);

					uintptr_t othr[9];
					void (*alloc)(script_context_pool_t *, script_thread_t *);
					void (*dealloc)(script_context_pool_t *, script_thread_t *);
				};

				vtable_t *vtable;

				void alloc(script_thread_t *td) {
					vtable->alloc(this, td);
				}

				void dealloc(script_thread_t *td) {
					vtable->dealloc(this, td);
				}
		};

		extern script_context_pool_t *script_context_pool;

		struct call_context_t;

		typedef void (__cdecl *func_t)(call_context_t &);

		struct call_context_t {
			static constexpr size_t arg_count_max = 32;
			static func_t res_fixer;

			uintptr_t *result_ptr;
			uint32_t arg_count;
			uintptr_t *args_ptr;
			uint32_t res_count;
			Vector3 res_cache[arg_count_max];

			template <typename T>
			void set_arg(size_t i, T v) {
				reinterpret_cast<rua::unsafe_ptr *>(args_ptr)[i] = v;
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
					res_fixer(*this);
				}
			}

			void print(const std::string &mark = "") {
				if (!mark.empty()) {
					log(mark);
				}

				log(
					"args_ptr: ", args_ptr, "\n",
					"arg_count: ", arg_count, "\n",
					"result_ptr: ", result_ptr, "\n",
					"res_count: ", res_count
				);
			}
		};

		template <>
		inline void call_context_t::result<void>() const {}

		class func_table_t {
			public:
				uintptr_t _nodes;

				func_t *find(uint64_t hash) const;

				func_t operator[](uint64_t hash) const {
					auto fp = find(hash);
					if (fp) {
						return *fp;
					}
					log("nob::ntv::func_table_t[", std::hex, hash, std::dec, "]: is null!");
					return nullptr;
				}

				operator bool() const {
					return _nodes;
				}
		};

		extern func_table_t func_table;

		////////////////////////////////////////////////////////////////////////////

		class lazy_func_t {
			public:
				constexpr lazy_func_t() : _f(nullptr), _h(0), _1st_h(0) {}
				constexpr lazy_func_t(func_t func) : _f(func), _h(0), _1st_h(0) {}
				constexpr lazy_func_t(uint64_t hash, bool is_first_hash = true) :
					_f(nullptr), _h(is_first_hash ? 0 : hash), _1st_h(is_first_hash ? hash : 0)
				{}

				void operator()(call_context_t &ctx) {
					#ifdef NOB_USING_SHV_CALL
						if (_1st_h) {
							shv::nativeInit(_1st_h);
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
					if (_f) {
						return _f;
					}
					if (_h) {
						_f = func_table[_h];
						if (_f) {
							return _f;
						}
					} else if (_1st_h && cur_fhtt_ptr) {
						auto it = cur_fhtt_ptr->find(_1st_h);
						if (it != cur_fhtt_ptr->end() && it->second) {
							_h = it->second;
							_f = func_table[_h];
							if (_f) {
								return _f;
							}
						}
					}
					log("nob::ntv::lazy_func_t(", std::hex, _1st_h, "->", _h, std::dec, "): not found!");
					return nullptr;
				}

			protected:
				func_t _f;
				uint64_t _h;
				uint64_t _1st_h;
		};

		class full_call_context_t : public call_context_t {
			public:
				full_call_context_t() {
					args_ptr = _stack;
					result_ptr = _stack + arg_count_max;
				}

			private:
				uintptr_t _stack[2 * arg_count_max];
		};

		extern full_call_context_t _dft_call_ctx;

		template <typename>
		class typed_lazy_func_t;

		template <typename R, typename... A>
		class typed_lazy_func_t<R(A...)> : public lazy_func_t {
			public:
				constexpr typed_lazy_func_t() : lazy_func_t() {}
				constexpr typed_lazy_func_t(func_t func) : lazy_func_t(func) {}
				constexpr typed_lazy_func_t(uint64_t hash, bool is_first_hash = true) : lazy_func_t(hash, is_first_hash) {}

				R operator()(A... args) {
					#ifdef NOB_USING_SHV_CALL
						if (_1st_h) {
							shv::nativeInit(_1st_h);
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

		extern uintptr_t (*get_entity_addr)(int handle);
	} /* ntv */
} /* nob */
