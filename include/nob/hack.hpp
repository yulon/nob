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

		template <typename T, typename ...A>
		class hook;

		template <typename T, typename ...A>
		class hook<T(A...)> {
			public:
				hook(T(*detour)(A...)) : _detour(reinterpret_cast<LPVOID>(detour)) {}

				~hook() {
					if (_target) {
						uninstall();
					}
				}

				void install(T(*target)(A...)) {
					if (++_hooking_count == 1) {
						MH_Initialize();
					}
					_target = reinterpret_cast<LPVOID>(target);
					MH_CreateHook(_target, _detour, &_original);
					MH_EnableHook(_target);
				}

				void install(uintptr_t target) {
					install(reinterpret_cast<T(*)(A...)>(target));
				}

				void call(A... a) {
					(*reinterpret_cast<T (*)(A...)>(_original))(a...);
				}

				void uninstall() {
					MH_DisableHook(_target);
					MH_RemoveHook(_target);
					_target = nullptr;
					if (!--_hooking_count) {
						MH_Uninitialize();
					}
				}

			private:
				LPVOID _target, _detour, _original;
		};
	} /* hack */
} /* nob */