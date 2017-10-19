#pragma once

#include "ntv.hpp"

namespace nob {
	namespace vision {
		inline void night(bool toggle) {
			ntv::GRAPHICS::SET_NIGHTVISION(toggle);
		}

		inline bool is_night_active() {
			return ntv::GRAPHICS::_IS_NIGHTVISION_ACTIVE();
		}

		inline void heat(bool toggle) {
			ntv::GRAPHICS::SET_SEETHROUGH(toggle);
		}

		inline bool is_heat_active() {
			return ntv::GRAPHICS::_IS_SEETHROUGH_ACTIVE();
		}
	} /* vision */
} /* nob */
