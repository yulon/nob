#include <nob.hpp>
#include <nob/hack.hpp>

#include <windows.h>
#include <psapi.h>

namespace nob {
	namespace hack {
		uintptr_t mem_match(const uint8_t *mem_addr, size_t mem_len, const std::vector<uint16_t> &pattern, bool ret_gap_addr) {
			for (size_t i = 0; i < mem_len; i++) {
				size_t j;
				int gap_off = -1;
				for (j = 0; i + j < mem_len && j < pattern.size(); j++) {
					if (pattern[j] > 256) {
						if (gap_off == -1) {
							gap_off = j;
						}
						continue;
					}
					if (pattern[j] != mem_addr[i + j]) {
						break;
					}
				}
				if (j == pattern.size()) {
					if (ret_gap_addr) {
						return reinterpret_cast<uintptr_t>(mem_addr) + i + reinterpret_cast<uintptr_t>((gap_off == -1 ? j : gap_off));
					}
					return reinterpret_cast<uintptr_t>(mem_addr) + i;
				}
			}
			return 0;
		}

		uintptr_t mem_match(const std::vector<uint16_t> &pattern, bool ret_gap_addr) {
			MODULEINFO mi;
			GetModuleInformation(GetCurrentProcess(), GetModuleHandle(nullptr), &mi, sizeof(MODULEINFO));
			return mem_match(reinterpret_cast<const uint8_t *>(mi.lpBaseOfDll), mi.SizeOfImage, pattern, ret_gap_addr);
		}

		std::atomic<size_t> _hooking_count(0);
	} /* hack */
} /* nob */
