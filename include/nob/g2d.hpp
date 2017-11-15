#pragma once

#include "ntv.hpp"
#include "script.hpp"

#include <string>

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
				texture_dict() : _name(nullptr) {}

				texture_dict(const char *name) : _name(name) {
					ntv::GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(_name, false);
					if (!ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(_name)) {
						wait([name]()->bool {
							return ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(name);
						});
					}
				}

				texture_dict(const std::string &name) : texture_dict(name.c_str()) {}

				texture_dict(const texture_dict &) = delete;

				texture_dict &operator=(const texture_dict &) = delete;

				texture_dict(texture_dict &&src) : _name(src._name) {
					if (src._name) {
						src._name = nullptr;
					}
				}

				texture_dict &operator=(texture_dict &&src) {
					free();
					if (src._name) {
						_name = src._name;
						src._name = nullptr;
					}
					return *this;
				}

				void free() {
					if (_name) {
						ntv::GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(_name);
						_name = nullptr;
					}
				}

				~texture_dict() {
					free();
				}

				operator bool() const {
					return _name;
				}

				const char *native_handle() const {
					return _name;
				}

				void draw(const char *texture_name, float x, float y, float width, float height, uint8_t a = 255) {
					ntv::GRAPHICS::DRAW_SPRITE(_name, texture_name, (x + (width / 2)), (y + (height / 2)), width, height, 0.0f, 255, 255, 255, a);
				}

			private:
				const char *_name;
		};
	} /* g2d */
} /* nob */
