#pragma once

#include "ntv.hpp"
#include "object.hpp"

#include <string>

namespace nob {
	namespace i18n {
		inline std::string get(const std::string &ll_name) {
			return ntv::UI::_GET_LABEL_TEXT(ll_name.c_str());
		}

		inline std::string get_vehicle_mod_type(vehicle veh, int mod_type) {
			return ntv::VEHICLE::GET_MOD_SLOT_NAME(veh, mod_type);
		}

		inline std::string get_vehicle_mod(vehicle veh, int mod_type, int mod) {
			return ntv::VEHICLE::GET_MOD_TEXT_LABEL(veh, mod_type, mod);
		}
	} /* i18n */
} /* nob */
