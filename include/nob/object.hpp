#pragma once

#include "ntv.hpp"
#include "model.hpp"
#include "vector.hpp"
#include "hash.hpp"
#include "weapon.hpp"
#include "script.hpp"

#include <iostream>

namespace nob {
	class entity {
		public:
			entity() = default;

			entity(int e) : _ntv_hdl(e) {}

			int native_handle() const {
				return _ntv_hdl;
			}

			void del() {
				ntv::ENTITY::DELETE_ENTITY(&_ntv_hdl);
			}

			void free() {
				ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&_ntv_hdl);
			}

			bool is_dead() const {
				return ntv::ENTITY::IS_ENTITY_DEAD(_ntv_hdl);
			}

			bool is_exist() const {
				return ntv::ENTITY::DOES_ENTITY_EXIST(_ntv_hdl);
			}

			operator bool() const {
				return _ntv_hdl && is_exist();
			}

			vector3 pos(const vector3 &rcs_offset = {0, 0, 0}) const {
				auto co = ntv::ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(_ntv_hdl, rcs_offset.x, rcs_offset.y, rcs_offset.z);
				return {co.x, co.y, co.z};
			}

			void move(const vector3 &coords) {
				ntv::ENTITY::SET_ENTITY_COORDS(_ntv_hdl, coords.x, coords.y, coords.z, true, true, true, true);
			}

			vector3 rotation() const {
				auto ro = ntv::ENTITY::GET_ENTITY_ROTATION(_ntv_hdl, 2);
				return {ro.x, ro.y, ro.z};
			}

			void rotation(const vector3 &ro) {
				ntv::ENTITY::SET_ENTITY_ROTATION(_ntv_hdl, ro.x, ro.y, ro.z, 2, true);
			}

			vector4 quaternion() const {
				vector4 quat;
				ntv::ENTITY::GET_ENTITY_QUATERNION(_ntv_hdl, &quat.x, &quat.y, &quat.z, &quat.w);
				return quat;
			}

			void quaternion(const vector4 &quat) {
				ntv::ENTITY::SET_ENTITY_QUATERNION(_ntv_hdl, quat.x, quat.y, quat.z, quat.w);
			}

			int alpha() const {
				return ntv::ENTITY::GET_ENTITY_ALPHA(_ntv_hdl);
			}

			void alpha(int alpha) {
				ntv::ENTITY::SET_ENTITY_ALPHA(_ntv_hdl, alpha, true);
			}

			void reset_alpha() {
				ntv::ENTITY::RESET_ENTITY_ALPHA(_ntv_hdl);
			}

			void invincible(bool toggle = true) {
				ntv::ENTITY::SET_ENTITY_INVINCIBLE(_ntv_hdl, toggle);
			}

		protected:
			int _ntv_hdl;
	};

	class character : public entity {
		public:
			enum class motion_state : uint8_t {
				null = 0,
				still,
				walking,
				runing,
				sprinting,
				jumping,
				falling,
				skydiving,
				parachuting,
				climbing
			};

			static constexpr float speed_walk = 1.0f;
			static constexpr float speed_run = 1.2f;
			static constexpr float speed_sprint = 3.0f;

			////////////////////////////////////////////////////////////////////

			character() {}

			character(const model &m, const vector3 &coords, bool player_shadow = false) :
				entity(ntv::PED::CREATE_PED(4, m.native_handle(), coords.x, coords.y, coords.z, 0.0f, false, true))
			{
				if (player_shadow) {
					ntv::PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(_ntv_hdl, true);
					ntv::PED::SET_PED_FLEE_ATTRIBUTES(_ntv_hdl, 0, 0);
					ntv::PED::SET_PED_COMBAT_ATTRIBUTES(_ntv_hdl, 292, true);
					ntv::PED::SET_PED_DIES_INSTANTLY_IN_WATER(_ntv_hdl, false);
					ntv::PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(_ntv_hdl, 1); // Blocks ragdolling when shot.
					ntv::WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(_ntv_hdl, false);
				}
				ntv::PED::SET_PED_CONFIG_FLAG(_ntv_hdl, 281, true); // PED_FLAG_NO_WRITHE
			}

			character(ntv::Ped ped) : entity(ped) {}

			void del() {
				ntv::PED::DELETE_PED(&_ntv_hdl);
			}

			void resurrect() {
				ntv::ENTITY::SET_ENTITY_HEALTH(_ntv_hdl, ntv::ENTITY::GET_ENTITY_MAX_HEALTH(_ntv_hdl));
				ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(_ntv_hdl);
				ntv::ENTITY::SET_ENTITY_COLLISION(_ntv_hdl, true, true);
			}

			void set_random_outfit() {
				ntv::PED::SET_PED_RANDOM_COMPONENT_VARIATION(_ntv_hdl, false);
			}

			void set_default_outfit() {
				ntv::PED::SET_PED_DEFAULT_COMPONENT_VARIATION(_ntv_hdl);
			}

			void set_last_outfit() {
				for (int i = 0; i < 12; i++) {
					for (int d = ntv::PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(_ntv_hdl, i) - 1; d >= 0; d--) {
						for (int t = ntv::PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(_ntv_hdl, i, d) - 1; t >= 0; t--) {
							if (ntv::PED::IS_PED_COMPONENT_VARIATION_VALID(_ntv_hdl, i, d, t)) {
								ntv::PED::SET_PED_COMPONENT_VARIATION(_ntv_hdl, i, d, t, 0);
								break;
							}
						}
					}
				}
			}

			void still() {
				ntv::AI::TASK_STAND_STILL(_ntv_hdl, -1);
			}

			void jump() {
				ntv::AI::TASK_JUMP(_ntv_hdl, false, false, false);
			}

			void go_to(const vector3 &target, float speed) {
				if (get_motion_state() == character::motion_state::parachuting) {
					ntv::AI::TASK_PARACHUTE_TO_TARGET(_ntv_hdl, target.x, target.y, target.z);
					return;
				}

				ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
					_ntv_hdl,
					target.x, target.y, target.z,
					speed,
					-1, 0, 0
				);
				if (speed == character::speed_run) {
					ntv::AI::SET_PED_DESIRED_MOVE_BLEND_RATIO(_ntv_hdl, 2.0f);
				} else {
					ntv::AI::SET_PED_DESIRED_MOVE_BLEND_RATIO(_ntv_hdl, speed);
				}
			}

			void equip_parachute() {
				if (!ntv::WEAPON::GET_IS_PED_GADGET_EQUIPPED(_ntv_hdl, 0xFBAB5776)) {
					ntv::WEAPON::SET_PED_GADGET(_ntv_hdl, 0xFBAB5776, true);
				}
			}

			void open_parachute() {
				equip_parachute();
				ntv::PED::FORCE_PED_TO_OPEN_PARACHUTE(_ntv_hdl);
			}

			void leave_vehicle(bool jump = false) {
				auto veh = ntv::PED::GET_VEHICLE_PED_IS_IN(_ntv_hdl, false);
				if (veh) {
					int flag;
					if (!jump) {
						flag = 0;
					} else {
						flag = 4160;
					}
					ntv::AI::TASK_LEAVE_VEHICLE(_ntv_hdl, veh, flag);
				}
			}

			character::motion_state get_motion_state() const {
				auto ps = ntv::PED::GET_PED_PARACHUTE_STATE(_ntv_hdl);
				if (ps == 1 || ps == 2) {
					return character::motion_state::parachuting;
				}

				if (nob::ntv::PED::IS_PED_IN_PARACHUTE_FREE_FALL(_ntv_hdl)) {
					return character::motion_state::skydiving;
				}

				if (nob::ntv::PED::IS_PED_FALLING(_ntv_hdl)) {
					return character::motion_state::falling;
				}

				if (nob::ntv::PED::IS_PED_JUMPING(_ntv_hdl)) {
					/*if (nob::ntv::AI::IS_PED_WALKING(_ntv_hdl)) {

					} else if (nob::ntv::AI::IS_PED_RUNNING(_ntv_hdl)) {

					} else if (nob::ntv::AI::IS_PED_SPRINTING(_ntv_hdl)) {

					}*/
					return character::motion_state::jumping;
				}

				if (nob::ntv::PED::IS_PED_CLIMBING(_ntv_hdl)) {
					return character::motion_state::climbing;
				}

				if (nob::ntv::AI::IS_PED_STILL(_ntv_hdl)) {
					return character::motion_state::still;
				}

				if (nob::ntv::AI::IS_PED_WALKING(_ntv_hdl)) {
					return character::motion_state::walking;
				}

				if (nob::ntv::AI::IS_PED_RUNNING(_ntv_hdl)) {
					return character::motion_state::runing;
				}

				if (nob::ntv::AI::IS_PED_SPRINTING(_ntv_hdl)) {
					return character::motion_state::sprinting;
				}

				return character::motion_state::null;
			}

			void add_weapon(const hasher &weapon) {
				ntv::WEAPON::GIVE_WEAPON_TO_PED(_ntv_hdl, weapon.hash, 0, false, true);
			}

			void add_weapon_in_pack(const hasher &weapon) {
				ntv::WEAPON::GIVE_WEAPON_TO_PED(_ntv_hdl, weapon.hash, 0, false, false);
			}

			void rm_weapon(const hasher &weapon) {
				ntv::WEAPON::REMOVE_WEAPON_FROM_PED(_ntv_hdl, weapon.hash);
			}

			void rm_all_weapons() {
				ntv::WEAPON::REMOVE_ALL_PED_WEAPONS(_ntv_hdl, true);
			}

			void switch_weapon(const hasher &weapon) {
				ntv::WEAPON::SET_CURRENT_PED_WEAPON(_ntv_hdl, weapon.hash, true);
			}

			bool is_current_weapon(const hasher &weapon) {
				hash_t h;
				ntv::WEAPON::GET_CURRENT_PED_WEAPON(_ntv_hdl, &h, true);
				return h == weapon.hash;
			}

			hasher current_weapon() {
				return ntv::WEAPON::GET_SELECTED_PED_WEAPON(_ntv_hdl);
			}

			bool has_weapon_in_pack(const hasher &weapon) {
				return ntv::WEAPON::HAS_PED_GOT_WEAPON(_ntv_hdl, weapon.hash, false);
			}

			bool has_weapon(const hasher &weapon) {
				return is_current_weapon(weapon.hash) ? true : has_weapon_in_pack(weapon);
			}

			void using_weapon(const hasher &weapon) {
				if (is_current_weapon(weapon.hash)) {
					return;
				}
				if (has_weapon_in_pack(weapon.hash)) {
					switch_weapon(weapon.hash);
					return;
				}
				add_weapon(weapon.hash);
			}

			static constexpr int infinite_ammo = -1;

			void ammo(const hasher &ammo_type, int n) {
				ntv::WEAPON::SET_PED_AMMO_BY_TYPE(_ntv_hdl, ammo_type.hash, n);
			}

			int ammo(const hasher &ammo_type) {
				return ntv::WEAPON::GET_PED_AMMO_BY_TYPE(_ntv_hdl, ammo_type.hash);
			}

			hasher ammo_type(const hasher &weapon) {
				return ntv::WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(_ntv_hdl, weapon.hash);
			}

			int max_ammo(const hasher &weapon) {
				int n;
				ntv::WEAPON::GET_MAX_AMMO(_ntv_hdl, weapon.hash, &n);
				return n;
			}

			void print_weapon_info() {
				auto cur_wpn = current_weapon();
				if (cur_wpn == "WEAPON_UNARMED") {
					std::cout << "unarmed!" << std::endl;
					return;
				}

				std::cout << "weapon " << std::hex << cur_wpn.hash << std::endl
					<< "  ammo type: " << ammo_type(cur_wpn).hash << std::endl;
					/*auto info = weapon_info(cur_wpn);
					if (info.valid) {
						std::cout
						<< "  damage: " << info.damage / 255.0f << std::endl
						<< "  speed: " << info.speed / 255.0f << std::endl
						<< "  capacity: " << info.capacity / 255.0f << std::endl
						<< "  accuracy: " << info.accuracy / 255.0f << std::endl
						<< "  range: " << info.range / 255.0f << std::endl;
					}*/
			}
	};

	namespace player {
		constexpr int native_handle() {
			return 0;
		}

		inline character body() {
			return ntv::PLAYER::PLAYER_PED_ID();
		}

		inline void change_body(character chr) {
			ntv::PLAYER::CHANGE_PLAYER_PED(native_handle(), chr.native_handle(), true, true);
		}

		inline void switch_body(character chr) {
			auto old_chr = body();
			auto old_chr_coords = old_chr.pos({ 0, 0, 0 });
			auto chr_coords = chr.pos({ 0, 0, 0 });

			int st = ntv::STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(old_chr_coords.x, old_chr_coords.y, old_chr_coords.z, chr_coords.x, chr_coords.y, chr_coords.z);
			ntv::STREAMING::START_PLAYER_SWITCH(old_chr.native_handle(), chr.native_handle(), 0, st);

			wait(1000);

			if (ntv::ENTITY::DOES_ENTITY_EXIST(chr.native_handle()) && !ntv::ENTITY::IS_ENTITY_DEAD(chr.native_handle())) {
				change_body(chr);
				old_chr.free();
			}
		}

		inline void auto_get_parachute_in_plane(bool toggle = true) {
			nob::ntv::PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(0, toggle);
		}
	}

	class vehicle : public entity {
		public:
			static void unlock_banned_vehicles();

			////////////////////////////////////////////////////////////////////

			vehicle() {}

			vehicle(const model &m, const vector3 &coords, float heading = 0.0f) :
				entity(ntv::VEHICLE::CREATE_VEHICLE(m.native_handle(), coords.x, coords.y, coords.z, heading, false, true))
			{
				ntv::VEHICLE::SET_VEHICLE_MOD_KIT(_ntv_hdl, 0);
			}

			void del() {
				ntv::VEHICLE::DELETE_VEHICLE(&_ntv_hdl);
			}

			void remove() {
				ntv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&_ntv_hdl);
			}

			void place_on_ground() {
				ntv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_ntv_hdl);
			}

			static constexpr int mod_type_sum = 50;

			int mod_sum(int mod_type) {
				return ntv::VEHICLE::GET_NUM_VEHICLE_MODS(_ntv_hdl, mod_type);
			}

			void mod(int mod_type, int mod) {
				ntv::VEHICLE::SET_VEHICLE_MOD(_ntv_hdl, mod_type, mod, true);
			}

			void mod(int mod_type) {
				ntv::VEHICLE::GET_VEHICLE_MOD(_ntv_hdl, mod_type);
			}

			void set_best_mods() {
				for (int i = 0; i < mod_type_sum; i++) {
					if (i == 15 || i == 23 || i == 24) {
						continue;
					}

					auto n = mod_sum(i);
					if (n > 0) {
						mod(i, n - 1);
					}
				}
			}

			bool is_playing_radio() {
				return ntv::AUDIO::_IS_VEHICLE_RADIO_LOUD(_ntv_hdl);
			}

			std::string get_radio_station() {
				if (ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(ntv::PLAYER::PLAYER_PED_ID(), _ntv_hdl) && is_playing_radio()) {
					return ntv::AUDIO::GET_PLAYER_RADIO_STATION_NAME();
				}
				return nullptr;
			}

			void set_radio_station(const std::string &radio_station = nullptr) {
				if (radio_station.empty()) {
					if (is_playing_radio()) {
						ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(_ntv_hdl, false);
					}
					return;
				}
				if (!is_playing_radio()) {
					ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(_ntv_hdl, true);
				}
				ntv::AUDIO::SET_VEH_RADIO_STATION(_ntv_hdl, radio_station.c_str());
			}

			static constexpr float min_engine_health = -4000.0f;
			static constexpr float max_engine_health = 1000.0f;

			/*
				-4000: Engine is destroyed
				0 and below: Engine catches fire and health rapidly declines
				300: Engine is smoking and losing functionality
				1000: Engine is perfect
			*/

			float engine_health() {
				return ntv::VEHICLE::GET_VEHICLE_ENGINE_HEALTH(_ntv_hdl);
			}

			void engine_health(float v) {
				ntv::VEHICLE::SET_VEHICLE_ENGINE_HEALTH(_ntv_hdl, v);
			}

			static constexpr float min_petrol_tank_health = -4000.0f;
			static constexpr float max_petrol_tank_health = 1000.0f;

			/*
				1000 is max health
				Begins leaking gas at around 650 health
				-999.90002441406 appears to be minimum health, although nothing special occurs
			*/

			float petrol_tank_health() {
				return ntv::VEHICLE::GET_VEHICLE_PETROL_TANK_HEALTH(_ntv_hdl);
			}

			void petrol_tank_health(float v) {
				ntv::VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(_ntv_hdl, v);
			}

			void explode() {
				ntv::VEHICLE::EXPLODE_VEHICLE(_ntv_hdl, true, false);
			}

			void catches_fire() {
				ntv::VEHICLE::EXPLODE_VEHICLE(_ntv_hdl, false, false);
			}

			bool has(character chr) {
				return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(chr.native_handle(), _ntv_hdl);
			}

			character passenger(int seat) {
				return ntv::VEHICLE::GET_PED_IN_VEHICLE_SEAT(_ntv_hdl, seat);
			}

			bool has_passenger(int seat) {
				return !ntv::VEHICLE::IS_VEHICLE_SEAT_FREE(_ntv_hdl, seat);
			}

			int max_passengers() {
				return ntv::VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(_ntv_hdl);
			}

			void disable_crash_damage(bool toggle = true) {
				ntv::VEHICLE::SET_VEHICLE_STRONG(_ntv_hdl, toggle);
			}
	};
} /* nob */
