#include <nob/hash.hpp>
#include <nob/ntv.hpp>

#include <string>

namespace nob {
	const char *hasher::src_c_str() const {
		if (!_str && _h && ntv::STREAMING::IS_MODEL_A_VEHICLE(_h)) {
			return ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(_h);
		}
		return _str;
	}
}
