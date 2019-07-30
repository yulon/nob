#include <nob/ntv/fhtt.hpp>
#include <nob/program.hpp>

#include <array>

namespace nob { namespace ntv {

const std::unordered_map<uint64_t, uint64_t> _fhtt_1103{
#include "fhtt/1103.inc"
};

const std::unordered_map<uint64_t, uint64_t> _fhtt_1180{
#include "fhtt/1180.inc"
};

const std::unordered_map<uint64_t, uint64_t> _fhtt_1290{
#include "fhtt/1290.inc"
};

const std::unordered_map<uint64_t, uint64_t> _fhtt_1365{
#include "fhtt/1365.inc"
};

const std::unordered_map<uint64_t, uint64_t> _fhtt_1493{
#include "fhtt/1493.inc"
};

const std::unordered_map<uint64_t, uint64_t> _fhtt_1604{
#include "fhtt/1604.inc"
};

const std::unordered_map<uint64_t, uint64_t> _fhtt_1737{
#include "fhtt/1737.inc"
};

const std::map<uint16_t, const std::unordered_map<uint64_t, uint64_t> &>
	fhtt_map{{1737, _fhtt_1737},
			 {1604, _fhtt_1604},
			 {1493, _fhtt_1493},
			 {1365, _fhtt_1365},
			 {1290, _fhtt_1290},
			 {1180, _fhtt_1180},
			 {1103, _fhtt_1103}};

const std::unordered_map<uint64_t, uint64_t> *fhtt = nullptr;

}} // namespace nob::ntv
