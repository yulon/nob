#pragma once

#include "ntv.hpp"
#include "script.hpp"

#include <string>
#include <cassert>

namespace nob {
	namespace g2d {
		inline void text(
			float x, float y, float width,
			const std::string &str,
			float size,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a,
			uint8_t align = 0,
			bool outline = false
		) {
			float nx;
			if (align) {
				nx = x + width / 2;
			} else {
				nx = x;
			}

			ntv::UI::SET_TEXT_FONT(0);
			ntv::UI::SET_TEXT_SCALE(1.0f, size);
			ntv::UI::SET_TEXT_COLOUR(r, g, b, a);
			ntv::UI::SET_TEXT_WRAP(x, x + width);
			switch (align) {
				case 1:
					ntv::UI::SET_TEXT_CENTRE(true);
					break;
				case 2:
					ntv::UI::SET_TEXT_RIGHT_JUSTIFY(true);
			}
			if (outline) ntv::UI::SET_TEXT_OUTLINE();

			ntv::UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str.c_str());
			ntv::UI::END_TEXT_COMMAND_DISPLAY_TEXT(nx, y);
		}

		constexpr float calc_text_height(float size) {
			return (((((38.0f + 42.0f) / 0.9f) / 105.0f) * 0.1f) * size);
		}

		inline void rect(
			float x, float y, float width, float height,
			uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255
		) {
			ntv::GRAPHICS::DRAW_RECT((x + (width / 2)), (y + (height / 2)), width, height, r, g, b, a);
		}

		class texture_dict {
			public:
				texture_dict() = default;

				texture_dict(std::nullptr_t) : texture_dict() {}

				texture_dict(const char *name) : _name(name) {}

				texture_dict(const std::string &name) : texture_dict(name.c_str()) {}

				const std::string &name() const {
					return _name;
				}

				using native_handle_t = const char *;

				native_handle_t native_handle() const {
					return _name.c_str();
				}

				operator bool() const {
					return _name.length();
				}

				bool is_loaded() const {
					assert(*this);

					return ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(_name.c_str());
				}

				const texture_dict &load() const {
					assert(*this);

					ntv::GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(_name.c_str(), false);
					return *this;
				}

				void free() const {
					ntv::GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(_name.c_str());
				}

				void draw(const char *texture_name, float x, float y, float width, float height, uint8_t a = 255) const {
					ntv::GRAPHICS::DRAW_SPRITE(_name.c_str(), texture_name, (x + (width / 2)), (y + (height / 2)), width, height, 0.0f, 255, 255, 255, a);
				}

			private:
				std::string _name;
		};
	} /* g2d */
} /* nob */
