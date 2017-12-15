#pragma once

#include <array>
#include <unordered_map>

namespace nob {
	namespace shv {
		extern const std::array<uint64_t, 5851> _fhtt_key_list;
		extern const std::unordered_map<uint16_t, const std::unordered_map<uint64_t, uint64_t>> fhtt;
	} /* shv */
} /* nob */
