#include <nob/shv/fhtt.hpp>

namespace nob {
	namespace shv {
		const std::unordered_map<uint16_t, const std::unordered_map<uint64_t, uint64_t>> fhtt {
			{
				1290,
				{
					#include "fhtt/1290.inc"
				}
			},
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
