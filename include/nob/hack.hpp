#pragma once

#include <MinHook.h>

#include <vector>
#include <atomic>
#include <cassert>

namespace nob {
	namespace hack {
		uintptr_t mem_match(const uint8_t *mem_addr, size_t mem_len, const std::vector<uint16_t> &pattern, bool ret_gap_addr = false);
		uintptr_t mem_match(const std::vector<uint16_t> &pattern, bool ret_gap_addr = false);

		template <typename T>
		T *find_const_ptr(const std::vector<uint16_t> &logged_ptr_code) {
			auto addr = mem_match(logged_ptr_code, true);
			if (!addr) {
				return 0;
			}
			return reinterpret_cast<T *>(addr + 4 + *(uint32_t *)addr);
		}

		extern std::atomic<size_t> _hooking_count;

		template <typename>
		class detour_func_t;

		template <typename R, typename ...A>
		class detour_func_t<R(A...)>;

		template <typename>
		class hooking_func_t;

		template <typename R, typename ...A>
		class hooking_func_t<R(A...)> {
			public:
				constexpr hooking_func_t() : _t(nullptr) {}

				hooking_func_t(hooking_func_t<R(A...)> &&src) : _t(src._t), _o(src._o) { src._t = nullptr; }

				const hooking_func_t<R(A...)> &operator=(hooking_func_t<R(A...)> &&src) {
					if (_t) {
						MH_DisableHook(_t);
						MH_RemoveHook(_t);
					}
					if (src._t) {
						_t = src._t;
						_o = src._o;

						src._t = nullptr;
					} else if (_t) {
						_t = nullptr;
						if (!--_hooking_count) {
							MH_Uninitialize();
						}
					}
					return *this;
				}

				~hooking_func_t() {
					unhook();
				}

				R operator()(A ...a) {
					if (_stdcall) {
						return (*reinterpret_cast<R (__stdcall *)(A...)>(_o))(a...);
					}
					return (*reinterpret_cast<R (*)(A...)>(_o))(a...);
				}

				void unhook() {
					if (_t) {
						MH_DisableHook(_t);
						MH_RemoveHook(_t);
						_t = nullptr;
						if (!--_hooking_count) {
							MH_Uninitialize();
						}
					}
				}

				operator bool() {
					return _t;
				}

			private:
				LPVOID _t, _o;
				bool _stdcall;

				hooking_func_t(LPVOID target, LPVOID detour_func, bool stdcall) : _t(target), _stdcall(stdcall) {
					if (++_hooking_count == 1) {
						MH_Initialize();
					}
					MH_CreateHook(target, detour_func, &_o);
					MH_EnableHook(target);
				}

				friend detour_func_t<R(A...)>;
		};

		template <typename R, typename ...A>
		class detour_func_t<R(A...)> {
			public:
				detour_func_t() :
					_d([](A...)->R {
						return (R)0;
					}),
					_stdcall(false)
				{}

				detour_func_t(R(*func)(A...), bool stdcall = false) : _d(func), _stdcall(stdcall) {}

				hooking_func_t<R(A...)> hook(R(*target)(A...)) {
					return hooking_func_t<R(A...)>(reinterpret_cast<LPVOID>(target), reinterpret_cast<LPVOID>(_d), _stdcall);
				}

				hooking_func_t<R(A...)> hook(uintptr_t target) {
					return hook(reinterpret_cast<R(*)(A...)>(target));
				}

			private:
				R(*_d)(A...);
				bool _stdcall;
		};
	} /* hack */
} /* nob */
