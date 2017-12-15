#include <nob/shv/fhtt.hpp>

namespace nob {
	namespace shv {
		const std::unordered_map<uint16_t, const std::unordered_map<uint64_t, uint64_t> &> fhtt {
			{ 1180, _fhtt_1180 },
			{ 1103, _fhtt_1103 },
		};
	} /* shv */
} /* nob */
