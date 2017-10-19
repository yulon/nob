#pragma once

#include "ntv.hpp"

#include <string>

namespace nob {
	namespace i18n {
		inline std::string get(const std::string &n) {
			return ntv::UI::_GET_LABEL_TEXT(n.c_str());
		}
		inline std::string get_vehicle_mod_type(vehicle v, int mod_type) {
			return ntv::VEHICLE::GET_MOD_SLOT_NAME(v.ntv_vehicle, mod_type);
		}
		inline std::string get_vehicle_mod(vehicle v, int mod_type, int mod) {
			return ntv::VEHICLE::GET_MOD_TEXT_LABEL(v.ntv_vehicle, mod_type, mod);
		}
	} /* i18n */
} /* nob */
