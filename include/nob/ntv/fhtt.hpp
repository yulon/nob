#pragma once

#include <array>
#include <unordered_map>

namespace nob {
	namespace ntv {
		extern const std::unordered_map<uint16_t, const std::unordered_map<uint64_t, uint64_t>> fhtt;
		extern const std::unordered_map<uint64_t, uint64_t> *const cur_fhtt_ptr;
	}
}
