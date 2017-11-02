#pragma once

#include "ntv.hpp"
#include "vector.hpp"
#include "script.hpp"

namespace nob {
	namespace world {
		inline float get_ground_height(const vector3 &coords, bool load_scene = true) {
			float height;
			ntv::GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &height, 0);
			if (load_scene) {
				while (height == 0.0f) {
					ntv::STREAMING::LOAD_SCENE(coords.x, coords.y, coords.z);
					wait(1000);
					ntv::GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &height, 0);
				}
			}
			return height;
		}

		inline vector3 get_ground_pos(const vector3 &coords, bool load_scene = true) {
			return {coords.x, coords.y, get_ground_height(coords, load_scene)};
		}

		void no_mans_island(bool toggle = true);

		inline void clear_black_fog() {
			ntv::UI::_SET_MINIMAP_REVEALED(true);
		}

		inline void emp(bool toggle) {
			ntv::GRAPHICS::_SET_BLACKOUT(toggle);
		}

		inline void clean_pickups() {
			nob::ntv::PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("pickup_controller", 8);
			nob::ntv::GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("pickup_controller");
		}
	}
} /* nob */
