#include <nob/ntv/fhtt.hpp>
#include <nob/program.hpp>

namespace nob {
	namespace ntv {
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

		const std::unordered_map<uint64_t, uint64_t> *const cur_fhtt_ptr = ([]()->const std::unordered_map<uint64_t, uint64_t> * {
			auto cur_fhtt_it = fhtt.find(program::version);
			if (cur_fhtt_it == fhtt.end()) {
				return nullptr;
			}
			return &cur_fhtt_it->second;
		})();
	}
}
