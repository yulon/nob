#pragma once

#include "ntv.hpp"
#include "vector.hpp"
#include "entity.hpp"
#include "gc.hpp"

#include <string>

namespace nob {
	namespace map {
		static constexpr float x_min = -3500.0f;
		static constexpr float x_max = 4250.0f;

		static constexpr float y_min = -4170.0f;
		static constexpr float y_max = 8034.0f;

		static constexpr float width = 7750.0f;
		static constexpr float height = 12204.0f;

		static constexpr vector2 center { 375.0f, 1932.0f };
		static constexpr vector2 radius { 3875.0f, 6102.0f };

		inline void clear_black_fog() {
			ntv::UI::_SET_MINIMAP_REVEALED(true);
		}

		class marker {
			public:
				static marker from_player() {
					return ntv::UI::GET_MAIN_PLAYER_BLIP_ID();
				}

				static marker from_entity(entity e) {
					return ntv::UI::GET_BLIP_FROM_ENTITY(e);
				}

				static void remove_all_from_graphic(int g) {
					for (auto b = ntv::UI::GET_FIRST_BLIP_INFO_ID(g); b; b = ntv::UI::GET_NEXT_BLIP_INFO_ID(g)) {
						ntv::UI::REMOVE_BLIP(&b);
					}
				}

				static void force_remove(bool toggle = true) {
					ntv::GAMEPLAY::SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(toggle);
				}

				static void remove_missions() {
					force_remove(true);

					nob::map::marker::remove_all_from_graphic(66);
					for (size_t i = 76; i < 81; ++i) {
						nob::map::marker::remove_all_from_graphic(i);
					}
					for (size_t i = 86; i < 90; ++i) {
						nob::map::marker::remove_all_from_graphic(i);
					}
					nob::map::marker::remove_all_from_graphic(149);
					nob::map::marker::remove_all_from_graphic(205);
					for (size_t i = 208; i < 212; ++i) {
						nob::map::marker::remove_all_from_graphic(i);
					}
					for (size_t i = 314; i < 317; ++i) {
						nob::map::marker::remove_all_from_graphic(i);
					}
					nob::map::marker::remove_all_from_graphic(350);
					nob::map::marker::remove_all_from_graphic(352);
					for (size_t i = 356; i < 361; ++i) {
						nob::map::marker::remove_all_from_graphic(i);
					}
					nob::map::marker::remove_all_from_graphic(363);
					for (size_t i = 369; i < 390; ++i) {
						nob::map::marker::remove_all_from_graphic(i);
					}
					for (size_t i = 400; i < 406; ++i) {
						nob::map::marker::remove_all_from_graphic(i);
					}
					nob::map::marker::remove_all_from_graphic(456);
				}

				marker(int native_handle = 0) : _h(native_handle) {}

				marker(const vector3 &pos) : _h(ntv::UI::ADD_BLIP_FOR_COORD(pos.x, pos.y, pos.z)) {
					if (_h) {
						auto h = _h;
						gc::delegate(*this, [h]() mutable {
							if (ntv::UI::DOES_BLIP_EXIST(h)) {
								ntv::UI::REMOVE_BLIP(&h);
							}
						});
					}
				}

				marker(std::initializer_list<float> pos) : marker(vector3(pos)) {}

				marker(const vector3 &pos, float radius) : _h(ntv::UI::ADD_BLIP_FOR_RADIUS(pos.x, pos.y, pos.z, radius)) {
					if (_h) {
						auto h = _h;
						gc::delegate(*this, [h]() mutable {
							if (ntv::UI::DOES_BLIP_EXIST(h)) {
								ntv::UI::REMOVE_BLIP(&h);
							}
						});
					}
				}

				marker(entity e) : _h(ntv::UI::ADD_BLIP_FOR_ENTITY(e)) {
					if (_h) {
						auto h = _h;
						gc::delegate(*this, [h]() mutable {
							if (ntv::UI::DOES_BLIP_EXIST(h)) {
								ntv::UI::REMOVE_BLIP(&h);
							}
						});
					}
				}

				int native_handle() const {
					return _h;
				}

				operator int() const {
					return native_handle();
				}

				operator bool() const {
					return _h && ntv::UI::DOES_BLIP_EXIST(_h);
				}

				void del() {
					if (_h) {
						gc::free(*this);
						_h = 0;
					}
				}

				void graphic(int g) {
					ntv::UI::SET_BLIP_SPRITE(_h, g);
				}

				int graphic() const {
					return ntv::UI::GET_BLIP_SPRITE(_h);
				}

				void radius(float r) {
					ntv::UI::SET_BLIP_SCALE(_h, r);
				}

				void move(const vector3 &coords) {
					ntv::UI::SET_BLIP_COORDS(_h, coords.x, coords.y, coords.z);
				}

				vector3 pos() const {
					return ntv::UI::GET_BLIP_COORDS(_h);
				}

				enum class color_t : int {
					white = 0,
					red,
					green,
					blue,
					orange = 17,
					purple = 19,
					grey,
					brown,
					pink = 23,
					dark_green = 25,
					dark_purple = 27,
					dark_blue = 29
				};

				void color(color_t clr) {
					ntv::UI::SET_BLIP_COLOUR(_h, static_cast<int>(clr));
				}

				color_t color() const {
					return static_cast<color_t>(ntv::UI::GET_BLIP_COLOUR(_h));
				}

				void keep_track(bool toggle = true) {
					ntv::UI::SET_BLIP_AS_SHORT_RANGE(_h, !toggle);
				}

				bool is_keep_track() const {
					return !ntv::UI::IS_BLIP_SHORT_RANGE(_h);
				}

				bool is_on_minimap() const {
					return ntv::UI::IS_BLIP_ON_MINIMAP(_h);
				}

				void nav(bool toggle = true) {
					ntv::UI::SET_BLIP_ROUTE(_h, toggle);
				}

				void nav_color(color_t clr) {
					ntv::UI::SET_BLIP_ROUTE_COLOUR(_h, static_cast<int>(clr));
				}

			private:
				int _h;
		};
	}
}
