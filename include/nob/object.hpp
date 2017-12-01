#pragma once

#include "ntv.hpp"
#include "model.hpp"
#include "vector.hpp"
#include "hash.hpp"
#include "arm.hpp"
#include "script.hpp"

#include <iostream>

namespace nob {
	class entity {
		public:
			entity(int ntv_hdl = 0) : _ntv_hdl(ntv_hdl) {}

			int native_handle() const {
				return _ntv_hdl;
			}

			operator int() const {
				return native_handle();
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

			nob::model model() {
				return static_cast<hash_t>(ntv::ENTITY::GET_ENTITY_MODEL(_ntv_hdl));
			}

		protected:
			int _ntv_hdl;
	};

	class vehicle;

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

			using entity::entity;

			character(nob::model m, const vector3 &coords, bool player_body = false) :
				entity(ntv::PED::CREATE_PED(4, m, coords.x, coords.y, coords.z, 0.0f, false, true))
			{
				if (player_body) {
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
				if (get_motion_state() == motion_state::parachuting) {
					ntv::AI::TASK_PARACHUTE_TO_TARGET(_ntv_hdl, target.x, target.y, target.z);
					return;
				}

				ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
					_ntv_hdl,
					target.x, target.y, target.z,
					speed,
					-1, 0, 0
				);
				if (speed == speed_run) {
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

			inline void into_vehicle(vehicle veh, int seat);

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

			bool is_in_vehicle() {
				return ntv::PED::IS_PED_IN_ANY_VEHICLE(_ntv_hdl, false);
			}

			bool is_get_in_vehicle() {
				return ntv::PED::IS_PED_IN_ANY_VEHICLE(_ntv_hdl, true);
			}

			inline vehicle current_vehicle();

			inline vehicle last_vehicle();

			inline vehicle trying_to_enter_vehicle();

			inline int trying_to_enter_vehicle_seat();

			motion_state get_motion_state() const {
				auto ps = ntv::PED::GET_PED_PARACHUTE_STATE(_ntv_hdl);
				if (ps == 1 || ps == 2) {
					return motion_state::parachuting;
				}

				if (nob::ntv::PED::IS_PED_IN_PARACHUTE_FREE_FALL(_ntv_hdl)) {
					return motion_state::skydiving;
				}

				if (nob::ntv::PED::IS_PED_FALLING(_ntv_hdl)) {
					return motion_state::falling;
				}

				if (nob::ntv::PED::IS_PED_JUMPING(_ntv_hdl)) {
					/*if (nob::ntv::AI::IS_PED_WALKING(_ntv_hdl)) {

					} else if (nob::ntv::AI::IS_PED_RUNNING(_ntv_hdl)) {

					} else if (nob::ntv::AI::IS_PED_SPRINTING(_ntv_hdl)) {

					}*/
					return motion_state::jumping;
				}

				if (nob::ntv::PED::IS_PED_CLIMBING(_ntv_hdl)) {
					return motion_state::climbing;
				}

				if (nob::ntv::AI::IS_PED_STILL(_ntv_hdl)) {
					return motion_state::still;
				}

				if (nob::ntv::AI::IS_PED_WALKING(_ntv_hdl)) {
					return motion_state::walking;
				}

				if (nob::ntv::AI::IS_PED_RUNNING(_ntv_hdl)) {
					return motion_state::runing;
				}

				if (nob::ntv::AI::IS_PED_SPRINTING(_ntv_hdl)) {
					return motion_state::sprinting;
				}

				return motion_state::null;
			}

			void add_weapon(const hasher &wpn) {
				ntv::WEAPON::GIVE_WEAPON_TO_PED(_ntv_hdl, wpn.hash(), 0, false, false);
			}

			void rm_weapon(const hasher &wpn) {
				ntv::WEAPON::REMOVE_WEAPON_FROM_PED(_ntv_hdl, wpn.hash());
			}

			void add_all_weapons() {
				for (auto &wpn : nob::arm::weapons) {
					if (wpn == "WEAPON_UNARMED") {
						continue;
					}

					auto wpn_grp = nob::arm::weapon_group(wpn);

					if (wpn_grp == "GROUP_THROWN") {
						thrown_weapon(wpn, weapon_max_ammo(wpn));
						continue;
					}

					add_weapon(wpn);

					if (wpn_grp == "GROUP_MELEE") {
						continue;
					}

					ammo(weapon_ammo_type(wpn), weapon_max_ammo(wpn));
				}
			}

			void rm_all_weapons() {
				ntv::WEAPON::REMOVE_ALL_PED_WEAPONS(_ntv_hdl, true);
			}

			void switch_weapon(const hasher &wpn) {
				if (is_current_weapon(wpn)) {
					return;
				}
				if (is_in_vehicle()) {
					ntv::WEAPON::SET_CURRENT_PED_VEHICLE_WEAPON(_ntv_hdl, wpn.hash());
					if (!is_current_weapon(wpn) && arm::weapon_group(wpn).hash() != 0) {
						ntv::WEAPON::GIVE_WEAPON_TO_PED(_ntv_hdl, wpn.hash(), 0, false, true);
					}
					return;
				}
				if (!has_weapon_in_pack(wpn)) {
					ntv::WEAPON::GIVE_WEAPON_TO_PED(_ntv_hdl, wpn.hash(), 0, false, true);
					return;
				}
				ntv::WEAPON::SET_CURRENT_PED_WEAPON(_ntv_hdl, wpn.hash(), true);
			}

			hasher current_weapon() {
				hash_t h;
				if (is_in_vehicle()) {
					ntv::WEAPON::GET_CURRENT_PED_VEHICLE_WEAPON(_ntv_hdl, &h);
				} else {
					ntv::WEAPON::GET_CURRENT_PED_WEAPON(_ntv_hdl, &h, true);
				}
				return h;
			}

			bool is_current_weapon(const hasher &wpn) {
				return current_weapon() == wpn;
			}

			void unarmed() {
				switch_weapon("WEAPON_UNARMED");
			}

			bool is_unarmed() {
				return is_current_weapon("WEAPON_UNARMED");
			}

			bool has_weapon_in_pack(const hasher &wpn) {
				return ntv::WEAPON::HAS_PED_GOT_WEAPON(_ntv_hdl, wpn.hash(), false);
			}

			bool has_weapon(const hasher &wpn) {
				return is_current_weapon(wpn.hash()) ? true : has_weapon_in_pack(wpn);
			}

			void ammo(const hasher &type, int total) {
				ntv::WEAPON::SET_PED_AMMO_BY_TYPE(_ntv_hdl, type.hash(), total);
			}

			int ammo(const hasher &type) {
				return ntv::WEAPON::GET_PED_AMMO_BY_TYPE(_ntv_hdl, type.hash());
			}

			void add_ammo(const hasher &type, int count) {
				ammo(type, ammo(type) + count);
			}

			void ammo_no_consumption(bool toggle = true) {
				nob::ntv::WEAPON::SET_PED_INFINITE_AMMO_CLIP(_ntv_hdl, toggle);
			}

			hasher weapon_ammo_type(const hasher &wpn) {
				return ntv::WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(_ntv_hdl, wpn.hash());
			}

			int weapon_max_ammo(const hasher &wpn) {
				int total;
				ntv::WEAPON::GET_MAX_AMMO(_ntv_hdl, wpn.hash(), &total);
				return total;
			}

			void thrown_weapon(const hasher &thr_wpn, int total) {
				if (!has_weapon(thr_wpn)) {
					ntv::WEAPON::GIVE_WEAPON_TO_PED(_ntv_hdl, thr_wpn.hash(), total, false, false);
					return;
				}
				ammo(weapon_ammo_type(thr_wpn), total);
			}

			int thrown_weapon(const hasher &thr_wpn) {
				return ntv::WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(_ntv_hdl, thr_wpn.hash());
			}

			void add_thrown_weapon(const hasher &thr_wpn, int count) {
				ntv::WEAPON::GIVE_WEAPON_TO_PED(_ntv_hdl, thr_wpn.hash(), count, false, false);
			}

			void print_weapon_info() {
				auto cur_wpn = current_weapon();
				if (cur_wpn == "WEAPON_UNARMED") {
					std::cout << "unarmed!" << std::endl;
					return;
				}

				std::cout << "weapon " << std::hex << cur_wpn.hash() << std::endl;

				auto grp = arm::weapon_group(cur_wpn);
				std::cout << "  group: ";
				for (auto &hr : arm::weapon_groups) {
					if (hr == grp) {
						std::cout << hr.src_c_str();
						break;
					}
				}
				std::cout << " " << grp.hash();
				std::cout << std::endl;

				auto amm_ty = weapon_ammo_type(cur_wpn);
				std::cout << "  ammo type: ";
				for (auto &hr : arm::ammo_types) {
					if (hr == amm_ty) {
						std::cout << hr.src_c_str();
						break;
					}
				}
				std::cout << " " << amm_ty.hash();
				std::cout << std::endl;

				auto info = arm::weapon_info(cur_wpn);
				if (info.valid) {
					std::cout
					<< "  damage: " << info.damage / 255.0f << std::endl
					<< "  speed: " << info.speed / 255.0f << std::endl
					<< "  capacity: " << info.capacity / 255.0f << std::endl
					<< "  accuracy: " << info.accuracy / 255.0f << std::endl
					<< "  range: " << info.range / 255.0f << std::endl;
				}
			}

			void aim(const vector3 &coords) {
				if (is_in_vehicle()) {
					auto wpn_grp = arm::weapon_group(current_weapon());
					if (!wpn_grp || wpn_grp == "GROUP_UNARMED") {
						ntv::AI::TASK_VEHICLE_AIM_AT_COORD(_ntv_hdl, coords.x, coords.y, coords.z);
					}
					return;
				}
				ntv::AI::TASK_AIM_GUN_AT_COORD(_ntv_hdl, coords.x, coords.y, coords.z, -1, false, false);
			}

			void shoot(const vector3 &coords) {
				if (is_in_vehicle()) {
					/*if (!arm::weapon_group(current_weapon())) {
						ntv::VEHICLE::SET_VEHICLE_SHOOT_AT_TARGET(_ntv_hdl, ntv::PED::GET_VEHICLE_PED_IS_IN(_ntv_hdl, false), coords.x, coords.y, coords.z);
						return;
					}*/
					ntv::AI::TASK_VEHICLE_SHOOT_AT_COORD(_ntv_hdl, coords.x, coords.y, coords.z, 1.0f);
					return;
				}
				ntv::AI::TASK_SHOOT_AT_COORD(_ntv_hdl, coords.x, coords.y, coords.z, -1, nob::hash("FIRING_PATTERN_FULL_AUTO"));
			}

			////////////////////////////////////////////////////////////////////

			class group {
				public:
					group(const std::string &name) : _n(name), _h(0) {}

					~group() {
						if (_h) {
							ntv::PED::REMOVE_RELATIONSHIP_GROUP(_h);
							_h = 0;
						}
					}

					void add(character chr) {
						if (!_h) {
							ntv::PED::ADD_RELATIONSHIP_GROUP(_n.c_str(), &_h);
						}
						ntv::PED::SET_PED_RELATIONSHIP_GROUP_HASH(chr, _h);
					}

					void rm(character chr) {
						ntv::PED::SET_PED_RELATIONSHIP_GROUP_HASH(chr, ntv::PED::GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(chr));
					}

				private:
					std::string _n;
					hash_t _h;
			};
	};

	namespace player {
		constexpr int native_handle() {
			return 0;
		}

		inline character body() {
			return ntv::PLAYER::PLAYER_PED_ID();
		}

		inline void change_body(character chr) {
			ntv::PLAYER::CHANGE_PLAYER_PED(native_handle(), chr, true, true);
		}

		inline void switch_body(character chr) {
			auto old_chr = body();
			auto old_chr_coords = old_chr.pos({ 0, 0, 0 });
			auto chr_coords = chr.pos({ 0, 0, 0 });

			int st = ntv::STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(old_chr_coords.x, old_chr_coords.y, old_chr_coords.z, chr_coords.x, chr_coords.y, chr_coords.z);
			ntv::STREAMING::START_PLAYER_SWITCH(old_chr, chr, 0, st);

			wait(1000);

			if (ntv::ENTITY::DOES_ENTITY_EXIST(chr) && !ntv::ENTITY::IS_ENTITY_DEAD(chr)) {
				change_body(chr);
				old_chr.free();
			}
		}

		inline void auto_get_parachute_in_plane(bool toggle = true) {
			nob::ntv::PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(0, toggle);
		}

		inline void disable_automatic_respawn() {
			ntv::GAMEPLAY::SET_FADE_OUT_AFTER_DEATH(false);
			ntv::GAMEPLAY::SET_FADE_OUT_AFTER_ARREST(false);
			ntv::GAMEPLAY::SET_FADE_IN_AFTER_DEATH_ARREST(false);
			ntv::GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(true);
		}

		inline void clear_state() {
			nob::ntv::GAMEPLAY::_RESET_LOCALPLAYER_STATE();
		}
	}

	class vehicle : public entity {
		public:
			static void unlock_banned_vehicles();

			////////////////////////////////////////////////////////////////////

			using entity::entity;

			vehicle(nob::model m, const vector3 &coords, float heading = 0.0f) :
				entity(ntv::VEHICLE::CREATE_VEHICLE(m, coords.x, coords.y, coords.z, heading, false, true))
			{
				ntv::VEHICLE::SET_VEHICLE_MOD_KIT(_ntv_hdl, 0);
			}

			void del() {
				ntv::VEHICLE::DELETE_VEHICLE(&_ntv_hdl);
			}

			void rm() {
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
				return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(chr, _ntv_hdl);
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

			void action(int ac) {
				ntv::AI::TASK_VEHICLE_TEMP_ACTION(passenger(-1), _ntv_hdl, ac, -1);
			}
	};

	inline void character::into_vehicle(vehicle veh, int seat) {
		ntv::PED::SET_PED_INTO_VEHICLE(_ntv_hdl, veh, seat);
	}

	inline vehicle character::current_vehicle() {
		return ntv::PED::GET_VEHICLE_PED_IS_IN(_ntv_hdl, false);
	}

	inline vehicle character::last_vehicle() {
		return ntv::PED::GET_VEHICLE_PED_IS_IN(_ntv_hdl, true);
	}

	inline vehicle character::trying_to_enter_vehicle() {
		return ntv::PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(_ntv_hdl);
	}

	inline int character::trying_to_enter_vehicle_seat() {
		return ntv::PED::GET_SEAT_PED_IS_TRYING_TO_ENTER(_ntv_hdl);
	}
} /* nob */
