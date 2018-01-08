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
				texture_dict() : _loader(0) {}

				texture_dict(std::nullptr_t) : texture_dict() {}

				texture_dict(const char *name) : _name(name), _loader(0) {}

				texture_dict(const std::string &name) : texture_dict(name.c_str()) {}

				texture_dict(const texture_dict &src) : _name(src._name), _loader(0) {};

				texture_dict &operator=(const texture_dict &src) {
					free();
					_name = src._name;
					return *this;
				};

				texture_dict(texture_dict &&src) : _name(std::move(src._name)), _loader(src._loader) {
					if (src._loader) {
						src._loader = 0;
					}
				}

				texture_dict &operator=(texture_dict &&src) {
					free();
					_name = std::move(src._name);
					if (src._loader) {
						_loader = src._loader;
						src._loader = 0;
					}
					return *this;
				}

				~texture_dict() {
					free();
				}

				bool is_loaded() const {
					assert(_name.length());

					return ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(_name.c_str());
				}

				const char *load() {
					assert(_name.length());

					if (is_loaded()) {
						return _name.c_str();
					}
					ntv::GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(_name.c_str(), false);
					if (!is_loaded()) {
						auto n = _name.c_str();
						wait([n]()->bool {
							return ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(n);
						});
					}
					_loader = this_script::first_frame_count;
					return _name.c_str();
				}

				void free() {
					if (_loader) {
						if (!in_task()) {
							return;
						}

						if (
							*ntv::game_state == ntv::game_state_t::playing &&
							_loader == this_script::first_frame_count &&
							is_loaded()
						) {
							ntv::GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(_name.c_str());
						}
						_loader = 0;
					}
				}

				void detach() {
					if (_loader) {
						_loader = 0;
					}
				}

				void draw(const char *texture_name, float x, float y, float width, float height, uint8_t a = 255) {
					ntv::GRAPHICS::DRAW_SPRITE(load(), texture_name, (x + (width / 2)), (y + (height / 2)), width, height, 0.0f, 255, 255, 255, a);
				}

			private:
				std::string _name;
				size_t _loader;
		};
	} /* g2d */
} /* nob */
