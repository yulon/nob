#pragma once

#include "ntv.hpp"
#include "entity.hpp"

#include <string>

namespace nob {
	inline std::string i18n(const std::string &ll_name) {
		return ntv::UI::_GET_LABEL_TEXT(ll_name.c_str());
	}
} /* nob */
