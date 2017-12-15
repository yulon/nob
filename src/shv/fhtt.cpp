#include <nob/shv/fhtt.hpp>

namespace nob {
	namespace shv {
		const std::array<uint64_t, 5851> _fhtt_key_list {
			#include "fhtt/key_list.inc"
		};

		const std::unordered_map<uint16_t, const std::unordered_map<uint64_t, uint64_t>> fhtt {
			{
				1180,
				{
					#include "fhtt/1180.inc"
				}
			},
			{
				1103,
				{
					#include "fhtt/1103.inc"
				}
			}
		};
	} /* shv */
} /* nob */
