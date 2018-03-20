#pragma once

#include <array>
#include <map>
#include <unordered_map>

namespace nob {
	namespace ntv {
		extern const std::map<uint16_t, const std::unordered_map<uint64_t, uint64_t> &> fhtt_map;
		extern const std::unordered_map<uint64_t, uint64_t> *fhtt;
	}
}
