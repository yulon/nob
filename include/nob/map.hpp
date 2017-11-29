#pragma once

#include "ntv.hpp"
#include "vector.hpp"
#include "object.hpp"

#include <string>

namespace nob {
	namespace map {
		inline void clear_black_fog() {
			ntv::UI::_SET_MINIMAP_REVEALED(true);
		}

		class icon {
			public:
				icon(const vector3 &pos) : _ntv_hdl(ntv::UI::ADD_BLIP_FOR_COORD(pos.x, pos.y, pos.z)) {}

				icon(const vector3 &pos, float radius) : _ntv_hdl(ntv::UI::ADD_BLIP_FOR_RADIUS(pos.x, pos.y, pos.z, radius)) {}

				icon(entity e) : _ntv_hdl(ntv::UI::ADD_BLIP_FOR_ENTITY(e)) {}

				icon(int ntv_hdl = 0) : _ntv_hdl(ntv_hdl) {}

				int native_handle() {
					return _ntv_hdl;
				}

				operator int() {
					return native_handle();
				}

				operator bool() {
					return _ntv_hdl && ntv::UI::DOES_BLIP_EXIST(_ntv_hdl);
				}

				void pos(const vector3 &coords) {
					ntv::UI::SET_BLIP_COORDS(_ntv_hdl, coords.x, coords.y, coords.z);
				}

				vector3 pos() {
					auto v3 = ntv::UI::GET_BLIP_COORDS(_ntv_hdl);
					return {v3.x, v3.y, v3.z};
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
					ntv::UI::SET_BLIP_COLOUR(_ntv_hdl, static_cast<int>(clr));
				}

				color_t color() {
					return static_cast<color_t>(ntv::UI::GET_BLIP_COLOUR(_ntv_hdl));
				}

				void keep_track(bool toggle = true) {
					ntv::UI::SET_BLIP_AS_SHORT_RANGE(_ntv_hdl, toggle);
				}

				bool is_keep_track() {
					return ntv::UI::IS_BLIP_SHORT_RANGE(_ntv_hdl);
				}

				bool is_on_minimap() {
					return ntv::UI::IS_BLIP_ON_MINIMAP(_ntv_hdl);
				}

				void nav(bool toggle = true) {
					ntv::UI::SET_BLIP_ROUTE(_ntv_hdl, toggle);
				}

				void nav_color(color_t clr) {
					ntv::UI::SET_BLIP_ROUTE_COLOUR(_ntv_hdl, static_cast<int>(clr));
				}

			private:
				int _ntv_hdl;
		};
	}
}
