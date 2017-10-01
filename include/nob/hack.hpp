#pragma once

#include <MinHook.h>

#include <vector>
#include <atomic>

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
				constexpr hooking_func_t() : _ptr(nullptr) {}

				hooking_func_t(hooking_func_t<R(A...)> &&src) : _ptr(src._ptr), _fn(src._fn) { src._ptr = nullptr; }

				const hooking_func_t<R(A...)> &operator=(hooking_func_t<R(A...)> &&src) {
					if (_ptr) {
						MH_DisableHook(_ptr);
						MH_RemoveHook(_ptr);
					}
					if (src._ptr) {
						_ptr = src._ptr;
						_fn = src._fn;

						src._ptr = nullptr;
					} else if (_ptr) {
						_ptr = nullptr;
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
					return (*reinterpret_cast<R (*)(A...)>(_fn))(a...);
				}

				void unhook() {
					if (_ptr) {
						MH_DisableHook(_ptr);
						MH_RemoveHook(_ptr);
						_ptr = nullptr;
						if (!--_hooking_count) {
							MH_Uninitialize();
						}
					}
				}

				operator bool() {
					return _ptr;
				}

			private:
				LPVOID _ptr, _fn;
				hooking_func_t(LPVOID pre_hook_func, LPVOID detour_func) : _ptr(pre_hook_func) {
					if (++_hooking_count == 1) {
						MH_Initialize();
					}
					MH_CreateHook(pre_hook_func, detour_func, &_fn);
					MH_EnableHook(pre_hook_func);
				}
				friend detour_func_t<R(A...)>;
		};

		template <typename R, typename ...A>
		class detour_func_t<R(A...)> {
			public:
				detour_func_t(R(*func)(A...)) : _stdfn(func) {}

				hooking_func_t<R(A...)> install(R(*target)(A...)) {
					hooking_func_t<R(A...)> r(reinterpret_cast<LPVOID>(target), reinterpret_cast<LPVOID>(_stdfn));
					return r;
				}

				hooking_func_t<R(A...)> install(uintptr_t target) {
					return install(reinterpret_cast<R(*)(A...)>(target));
				}

			private:
				R(*_stdfn)(A...);
		};
	} /* hack */
} /* nob */
