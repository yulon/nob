#pragma once

#include "ntv.hpp"
#include "entity.hpp"

#include <string>

namespace nob {
	inline std::string i18n(const std::string &display_text) {
		if (display_text.empty()) {
			return "";
		}
		auto loc_c = ntv::UI::_GET_LABEL_TEXT(display_text.c_str());
		if (!loc_c) {
			return display_text;
		}
		std::string loc(loc_c);
		if (loc == "NULL") {
			return display_text;
		}
		return loc;
	}

	inline std::string i18n(const char *display_text) {
		if (!display_text) {
			return "";
		}
		return i18n(std::string(display_text));
	}
} /* nob */
