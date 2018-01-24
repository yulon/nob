#pragma once

#include "ntv.hpp"
#include "vector.hpp"
#include "script.hpp"
#include "hash.hpp"
#include "map.hpp"

#include <array>

namespace nob {
	namespace world {
		inline float get_ground_height(const vector3 &coords, bool load_scene = true) {
			float height;
			ntv::GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &height, 0);
			if (load_scene) {
				while (height == 0.0f) {
					ntv::STREAMING::LOAD_SCENE(coords.x, coords.y, coords.z);
					sleep(1000);
					ntv::GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &height, 0);
				}
			}
			return height;
		}

		inline vector3 get_ground_pos(const vector3 &coords, bool load_scene = true) {
			return {coords.x, coords.y, get_ground_height(coords, load_scene)};
		}

		void no_mans_island(bool toggle = true);

		void disable_sp_features(bool toggle = true);

		inline void emp(bool toggle) {
			ntv::GRAPHICS::_SET_BLACKOUT(toggle);
		}

		inline void clean_pickups() {
			ntv::PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME("pickup_controller", 8);
			ntv::GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("pickup_controller");
		}

		enum class ilp : uint8_t {
			bahama_mamas = 0, // must teleport in
			chopshop,
			cluckin_bell,
			comedy_club, // must teleport in
			fame_or_shame_stadium,
			fib_lobby,
			foundry,
			floyds_house,
			epsilon,
			hospital_normal,
			hospital_destroyed,
			hospital_boarded_up,
			janitor,
			jewel_store,
			lab,
			life_invader,
			Lesters_house,
			lesters_factory,
			morgue, // must teleport in
			o_neil_ranch,
			psycheoffice, // must teleport in
			ranch, // must teleport in
			rogers_salvage_and_scrap, // doors will lock if you leave area
			sheriff_office_paleto,
			sheriff_office_sandy_shores,
			simeons_showroom,
			slaughter_house, // doors will lock if you leave area
			solomons_office,
			stab_city,
			stab_city_on_fire,
			stab_city_burnt,
			trevors_trailer,
			tequl_la_la,
			torture,
			mp_lost_safe_house, // need load_mp_map()
			mp_yacht, // need load_mp_map()
			mp_heist_carrier // need load_mp_map()
		};

		vector3 load_ilp(ilp i, bool toggle = true);

		inline void load_mp_map() {
			ntv::GAMEPLAY::_USE_FREEMODE_MAP_BEHAVIOR(true);
			ntv::DLC2::_LOAD_MP_DLC_MAPS();
		}

		inline void load_ilp_with_marker(ilp i) {
			auto pos = load_ilp(i);
			if (pos.x == 0 && pos.y == 0 && pos.z == 0) {
				return;
			}
			auto mkr = map::marker(pos);
			switch (i) {
				case ilp::mp_yacht:
					mkr.graphic(455);
					break;
				case ilp::mp_heist_carrier:
					mkr.graphic(462);
					break;
				default:
					mkr.graphic(40);
			}
			mkr.keep_track(false);
		}

		inline void load_all_ilps() {
			load_mp_map();

			for (size_t i = 0; i < static_cast<size_t>(ilp::hospital_destroyed); ++i) {
				load_ilp_with_marker(static_cast<ilp>(i));
			}

			for (size_t i = static_cast<size_t>(ilp::janitor); i < static_cast<size_t>(ilp::stab_city); ++i) {
				load_ilp_with_marker(static_cast<ilp>(i));
			}

			load_ilp(ilp::stab_city_on_fire);

			for (size_t i = static_cast<size_t>(ilp::trevors_trailer); i < static_cast<size_t>(ilp::mp_lost_safe_house); ++i) {
				load_ilp_with_marker(static_cast<ilp>(i));
			}

			load_ilp_with_marker(ilp::mp_yacht);
			load_ilp_with_marker(ilp::mp_heist_carrier);
		}

		struct door {
			hasher type;
			vector3 coords;
		};

		extern const std::array<door, 487> doors;

		inline void lock_door(const door &dr, bool toggle = true) {
			ntv::OBJECT::_DOOR_CONTROL(dr.type, dr.coords.x, dr.coords.y, dr.coords.z, toggle, 0.0f, 0.0f, -1.0f);
		}

		inline void lock_all_doors(bool toggle = true) {
			for (auto &dr : doors) {
				lock_door(dr, toggle);
			}
		}

		void snowy(bool toggle = true);
	}
} /* nob */
