#pragma once

#include "ntv.hpp"
#include "model.hpp"
#include "vector.hpp"
#include "character.hpp"
#include "player.hpp"

namespace nob {
	class vehicle {
		public:
			ntv::Vehicle ntv_vehicle;

			vehicle(model m, const vector3 &coords, float heading = 0.0f) : ntv_vehicle(ntv::VEHICLE::CREATE_VEHICLE(m.ntv_model, coords.x, coords.y, coords.z, heading, false, true)) {
				ntv::VEHICLE::SET_VEHICLE_MOD_KIT(ntv_vehicle, 0);
			}

			void del() {
				ntv::VEHICLE::DELETE_VEHICLE(&ntv_vehicle);
			}

			void remove() {
				ntv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&ntv_vehicle);
			}

			void place_on_ground() {
				ntv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(ntv_vehicle);
			}

			constexpr int get_mod_type_sum() {
				return 50;
			}

			int get_mod_sum(int mod_type) {
				return ntv::VEHICLE::GET_NUM_VEHICLE_MODS(ntv_vehicle, mod_type);
			}

			void set_mod(int mod_type, int mod) {
				ntv::VEHICLE::SET_VEHICLE_MOD(ntv_vehicle, mod_type, mod, true);
			}

			void get_mod(int mod_type) {
				ntv::VEHICLE::GET_VEHICLE_MOD(ntv_vehicle, mod_type);
			}

			void set_best_mods() {
				for (int i = 0; i < get_mod_type_sum(); i++) {
					auto n = get_mod_sum(i);
					if (n > 0) {
						ntv::VEHICLE::SET_VEHICLE_MOD(ntv_vehicle, i, n - 1, false);
					}
				}
			}

			bool has(const character &chr) {
				return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(chr.ntv_ped, ntv_vehicle);
			}

			bool is_playing_radio() {
				return ntv::AUDIO::_IS_VEHICLE_RADIO_LOUD(ntv_vehicle);
			}

			std::string get_radio_station() {
				if (has(player::body()) && is_playing_radio()) {
					return ntv::AUDIO::GET_PLAYER_RADIO_STATION_NAME();
				}
				return nullptr;
			}

			void set_radio_station(const std::string &radio_station = nullptr) {
				if (radio_station.empty()) {
					if (is_playing_radio()) {
						ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(ntv_vehicle, false);
					}
					return;
				}
				if (!is_playing_radio()) {
					ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(ntv_vehicle, true);
				}
				ntv::AUDIO::SET_VEH_RADIO_STATION(ntv_vehicle, radio_station.c_str());
			}

			////////////////////////////////////////////////////////////////////

			static void unlock_banned_vehicles();
	};
} /* nob */
