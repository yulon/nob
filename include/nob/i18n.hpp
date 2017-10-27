#pragma once

#include "ntv.hpp"
#include "object.hpp"

#include <string>

namespace nob {
	namespace i18n {
		inline std::string get(const std::string &n) {
			return ntv::UI::_GET_LABEL_TEXT(n.c_str());
		}
		inline std::string get_vehicle_mod_type(const vehicle &v, int mod_type) {
			return ntv::VEHICLE::GET_MOD_SLOT_NAME(v->native_handle(), mod_type);
		}
		inline std::string get_vehicle_mod(const vehicle &v, int mod_type, int mod) {
			return ntv::VEHICLE::GET_MOD_TEXT_LABEL(v->native_handle(), mod_type, mod);
		}
	} /* i18n */
} /* nob */
