#pragma once

#include "ntv.hpp"
#include "script.hpp"
#include "gc.hpp"

#include <string>
#include <cassert>

namespace nob {
	namespace g2d {
		inline void draw_text(
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

		inline void draw_rect(
			float x, float y, float width, float height,
			uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255
		) {
			ntv::GRAPHICS::DRAW_RECT((x + (width / 2)), (y + (height / 2)), width, height, r, g, b, a);
		}

		class texture_dict {
			public:
				texture_dict() : _name(""), _loaded(0) {}

				texture_dict(std::nullptr_t) : texture_dict() {}

				texture_dict(const char *name) : _name(name), _loaded(0) {}

				texture_dict(std::string name) : _name(std::move(name)), _loaded(0) {}

				texture_dict(const texture_dict &src) : _name(src._name), _loaded(0) {}

				~texture_dict() {
					free();
				}

				texture_dict &operator=(const texture_dict &src) {
					free();
					_name = src._name;
					return *this;
				}

				texture_dict(texture_dict &&src) : _name(std::move(src._name)), _loaded(src._loaded) {
					if (src._loaded == this_script::load_count) {
						src._loaded = 0;
					}
				}

				texture_dict &operator=(texture_dict &&src) {
					free();
					_name = std::move(src._name);
					if (src._loaded == this_script::load_count) {
						_loaded = src._loaded;
						src._loaded = 0;
					}
					return *this;
				}

				const std::string &name() const {
					return _name;
				}

				using native_handle_t = const char *;

				native_handle_t native_handle() const {
					return _name.c_str();
				}

				operator native_handle_t() const {
					return native_handle();
				}

				operator bool() const {
					return _name.length();
				}

				bool is_loaded() const {
					assert(*this);

					return ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(_name.c_str());
				}

				texture_dict &load() {
					assert(*this);

					if (_loaded == this_script::load_count) {
						return *this;
					}

					start:

					if (gc::try_ref(*this)) {
						assert(is_loaded());

						_loaded = this_script::load_count;
						return *this;
					}

					ntv::GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(_name.c_str(), false);

					auto cur_lc = this_script::load_count;

					while (!is_loaded()) {
						yield();
						if (cur_lc != this_script::load_count) {
							goto start;
						}
					}

					_loaded = cur_lc;

					auto n = _name;
					gc::delegate(*this, [n]() {
						if (ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(n.c_str())) {
							ntv::GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(n.c_str());
						}
					});

					return *this;
				}

				void free() {
					if (_loaded == this_script::load_count) {
						gc::free(*this);
						_loaded = 0;
					}
				}

				void draw(
					const char *texture_name,
					float x, float y, float width, float height,
					float heading = 0.0f,
					uint8_t alpha = 255, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255
				) const {
					ntv::GRAPHICS::DRAW_SPRITE(native_handle(), texture_name, (x + (width / 2)), (y + (height / 2)), width, height, heading, r, g, b, alpha);
				}

			private:
				std::string _name;
				size_t _loaded;
		};
	} /* g2d */
} /* nob */
