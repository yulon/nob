#pragma once

#include "ntv.hpp"
#include "model.hpp"
#include "vector.hpp"
#include "hash.hpp"
#include "arm.hpp"
#include "script.hpp"
#include "gc.hpp"
#include "log.hpp"

namespace nob {
	class entity {
		public:
			entity(int native_handle = 0) : _h(native_handle) {}

			entity(model m, const vector3 &coords, bool dynamic = true) :
				entity(ntv::OBJECT::CREATE_OBJECT_NO_OFFSET(m.load(), coords.x, coords.y, coords.z, false, false, dynamic))
			{
				if (!_h) {
					return;
				}

				auto h = _h;
				gc::track(*this, [h]() mutable {
					ntv::ENTITY::DELETE_ENTITY(&h);
				});
			}

			int native_handle() const {
				return _h;
			}

			operator int() const {
				return native_handle();
			}

			void del() {
				gc::untrack(*this);
				ntv::ENTITY::DELETE_ENTITY(&_h);
			}

			void free() {
				gc::untrack(*this);
				ntv::ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&_h);
			}

			bool is_dead() const {
				return ntv::ENTITY::IS_ENTITY_DEAD(_h);
			}

			bool is_exist() const {
				return ntv::ENTITY::DOES_ENTITY_EXIST(_h);
			}

			operator bool() const {
				return _h && is_exist();
			}

			vector3 pos(const vector3 &rcs_offset) const {
				auto co = ntv::ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(_h, rcs_offset.x, rcs_offset.y, rcs_offset.z);
				return {co.x, co.y, co.z};
			}

			vector3 pos() const {
				auto co = ntv::ENTITY::GET_ENTITY_COORDS(_h, true);
				return {co.x, co.y, co.z};
			}

			void move(const vector3 &coords) {
				ntv::ENTITY::SET_ENTITY_COORDS_NO_OFFSET(_h, coords.x, coords.y, coords.z, true, true, true);
			}

			vector3 rotation() const {
				auto ro = ntv::ENTITY::GET_ENTITY_ROTATION(_h, 2);
				return {ro.x, ro.y, ro.z};
			}

			void rotation(const vector3 &ro) {
				ntv::ENTITY::SET_ENTITY_ROTATION(_h, ro.x, ro.y, ro.z, 2, true);
			}

			vector4 quaternion() const {
				vector4 quat;
				ntv::ENTITY::GET_ENTITY_QUATERNION(_h, &quat.x, &quat.y, &quat.z, &quat.w);
				return quat;
			}

			void quaternion(const vector4 &quat) {
				ntv::ENTITY::SET_ENTITY_QUATERNION(_h, quat.x, quat.y, quat.z, quat.w);
			}

			vector3 velocity() const {
				auto ve = ntv::ENTITY::GET_ENTITY_VELOCITY(_h);
				return {ve.x, ve.y, ve.z};
			}

			void velocity(const vector3 &ve) {
				ntv::ENTITY::SET_ENTITY_VELOCITY(_h, ve.x, ve.y, ve.z);
			}

			struct movement_t {
				vector3 pos;
				vector4 quaternion;
				vector3 velocity;
			};

			movement_t movement() const {
				return {pos(), quaternion(), velocity()};
			}

			void movement(const movement_t &mm) {
				move(mm.pos);
				quaternion(mm.quaternion);
				velocity(mm.velocity);
			}

			int alpha() const {
				return ntv::ENTITY::GET_ENTITY_ALPHA(_h);
			}

			void alpha(int alpha) {
				ntv::ENTITY::SET_ENTITY_ALPHA(_h, alpha, true);
			}

			void reset_alpha() {
				ntv::ENTITY::RESET_ENTITY_ALPHA(_h);
			}

			void invincible(bool toggle = true) {
				ntv::ENTITY::SET_ENTITY_INVINCIBLE(_h, toggle);
			}

			model get_model() const {
				return static_cast<hash_t>(ntv::ENTITY::GET_ENTITY_MODEL(_h));
			}

			bool is_character() const {
				return ntv::ENTITY::IS_ENTITY_A_PED(_h);
			}

			bool is_vehicle() const {
				return ntv::ENTITY::IS_ENTITY_A_VEHICLE(_h);
			}

			bool is_trivial() const {
				return ntv::ENTITY::IS_ENTITY_AN_OBJECT(_h);
			}

			bool is_on_screen() const {
				return ntv::ENTITY::IS_ENTITY_ON_SCREEN(_h);
			}

			float health() {
				return ntv::ENTITY::GET_ENTITY_HEALTH(_h);
			}

			float max_health() {
				return ntv::ENTITY::GET_ENTITY_MAX_HEALTH(_h);
			}

			void health(int v) {
				ntv::ENTITY::SET_ENTITY_HEALTH(_h, v);
			}

		protected:
			int _h;

			void _gc_mk() const;
			void _gc_unmk() const;
	};

	class vehicle;

	class character : public entity {
		public:
			character(int native_handle = 0) : entity(native_handle) {}

			character(model m, const vector3 &coords, bool player_body = false) :
				entity(ntv::PED::CREATE_PED(4, m.load(), coords.x, coords.y, coords.z, 0.0f, false, false))
			{
				if (!_h) {
					return;
				}

				auto h = _h;
				gc::track(*this, [h]() mutable {
					if (h == ntv::PLAYER::PLAYER_PED_ID()) {
						return;
					}
					ntv::PED::DELETE_PED(&h);
				});

				if (player_body) {
					ntv::PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(_h, true);
					ntv::PED::SET_PED_FLEE_ATTRIBUTES(_h, 0, 0);
					ntv::PED::SET_PED_COMBAT_ATTRIBUTES(_h, 292, true);
					ntv::PED::SET_PED_DIES_INSTANTLY_IN_WATER(_h, false);
					ntv::PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(_h, 1); // Blocks ragdolling when shot.
					ntv::WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(_h, false);
					ntv::PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(_h, false);
				}
				ntv::PED::SET_PED_CONFIG_FLAG(_h, 281, true); // PED_FLAG_NO_WRITHE
			}

			void del();

			void free();

			void resurrect() {
				ntv::ENTITY::SET_ENTITY_HEALTH(_h, ntv::ENTITY::GET_ENTITY_MAX_HEALTH(_h));
				ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(_h);
				ntv::ENTITY::SET_ENTITY_COLLISION(_h, true, true);
			}

			void set_random_outfit() {
				ntv::PED::SET_PED_RANDOM_COMPONENT_VARIATION(_h, false);
			}

			void set_default_outfit() {
				ntv::PED::SET_PED_DEFAULT_COMPONENT_VARIATION(_h);
			}

			void set_last_outfit() {
				for (int i = 0; i < 12; i++) {
					for (int d = ntv::PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(_h, i) - 1; d >= 0; d--) {
						for (int t = ntv::PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(_h, i, d) - 1; t >= 0; t--) {
							if (ntv::PED::IS_PED_COMPONENT_VARIATION_VALID(_h, i, d, t)) {
								ntv::PED::SET_PED_COMPONENT_VARIATION(_h, i, d, t, 0);
								break;
							}
						}
					}
				}
			}

			void still();

			void jump();

			void climb();

			void climb_ladder();

			static constexpr float speed_walk = 1.0f;
			static constexpr float speed_run = 1.2f;
			static constexpr float speed_sprint = 3.0f;

			void go_to(const vector3 &target, float speed = speed_sprint);

			void go(float speed = speed_sprint) {
				go_to(pos({0, 10, 0}), speed);
			}

			void skydive();

			void add_parachute_pack() {
				if (!has_weapon_in_pack(nob::hash("GADGET_PARACHUTE"))) {
					add_weapon(nob::hash("GADGET_PARACHUTE"));
				}
			}

			void open_parachute();

			void open_fake_parachute();

			void stop_motion_command();

			inline void into_vehicle(vehicle veh, int seat);

			void leave_vehicle(bool jump = false) {
				auto veh = ntv::PED::GET_VEHICLE_PED_IS_IN(_h, false);
				if (veh) {
					int flag;
					if (!jump) {
						flag = 0;
					} else {
						flag = 4160;
					}
					ntv::AI::TASK_LEAVE_VEHICLE(_h, veh, flag);
				}
			}

			bool is_in_vehicle() {
				return ntv::PED::IS_PED_IN_ANY_VEHICLE(_h, false);
			}

			bool is_get_in_vehicle() {
				return ntv::PED::IS_PED_IN_ANY_VEHICLE(_h, true);
			}

			inline vehicle current_vehicle();

			inline vehicle last_vehicle();

			inline vehicle trying_to_enter_vehicle();

			inline int trying_to_enter_vehicle_seat();

			enum class motion_state_t : uint8_t {
				null = 0,
				still,
				walking,
				runing,
				sprinting,
				jumping,
				falling,
				skydiving,
				parachuting,
				climbing,
				climbing_ladder,
				covering,
				paralysing
			};

			motion_state_t motion_state() const {
				auto ps = ntv::PED::GET_PED_PARACHUTE_STATE(_h);
				if (ps == 1 || ps == 2) {
					return motion_state_t::parachuting;
				}

				if (ntv::PED::IS_PED_IN_PARACHUTE_FREE_FALL(_h)) {
					return motion_state_t::skydiving;
				}

				if (ntv::PED::IS_PED_FALLING(_h)) {
					return motion_state_t::falling;
				}

				if (ntv::PED::IS_PED_JUMPING(_h)) {
					/*if (ntv::AI::IS_PED_WALKING(_h)) {

					} else if (ntv::AI::IS_PED_RUNNING(_h)) {

					} else if (ntv::AI::IS_PED_SPRINTING(_h)) {

					}*/
					return motion_state_t::jumping;
				}

				if (ntv::AI::GET_IS_TASK_ACTIVE(_h, 1)) { // CTaskClimbLadder
					return motion_state_t::climbing_ladder;
				}

				if (ntv::PED::IS_PED_CLIMBING(_h)) {
					return motion_state_t::climbing;
				}

				if (ntv::PED::IS_PED_IN_COVER(_h, 0)) {
					return motion_state_t::covering;
				}

				if (
					ntv::PED::IS_PED_RAGDOLL(_h) ||
					ntv::PED::IS_PED_RUNNING_RAGDOLL_TASK(_h) ||
					ntv::AI::GET_IS_TASK_ACTIVE(_h, 125) || // CTaskHitWall
					ntv::AI::GET_IS_TASK_ACTIVE(_h, 387) || // CTaskAnimatedHitByExplosion
					ntv::AI::GET_IS_TASK_ACTIVE(_h, 95) // CTaskCarReactToVehicleCollisionGetOut
				) {
					return motion_state_t::paralysing;
				}

				if (ntv::AI::IS_PED_STILL(_h)) {
					return motion_state_t::still;
				}

				if (ntv::AI::IS_PED_WALKING(_h)) {
					return motion_state_t::walking;
				}

				if (ntv::AI::IS_PED_RUNNING(_h)) {
					return motion_state_t::runing;
				}

				if (ntv::AI::IS_PED_SPRINTING(_h)) {
					return motion_state_t::sprinting;
				}

				return motion_state_t::null;
			}

			struct movement_t : public entity::movement_t {
				motion_state_t motion_state;
			};

			movement_t movement() const {
				/*movement_t mm;
				static_cast<entity::movement_t &>(mm) = entity::movement();
				mm.motion_state = motion_state();
				return mm;*/
				return {entity::movement(), motion_state()};
			}

			void movement(const movement_t &);

			void add_weapon(const hasher &wpn) {
				ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, wpn.hash(), 0, false, false);
			}

			void rm_weapon(const hasher &wpn) {
				ntv::WEAPON::REMOVE_WEAPON_FROM_PED(_h, wpn.hash());
			}

			void add_all_weapons() {
				for (auto &wpn : arm::weapons) {
					if (wpn == "WEAPON_UNARMED") {
						continue;
					}

					auto wpn_grp = arm::weapon_group(wpn);

					if (wpn_grp == "GROUP_THROWN") {
						thrown_weapon(wpn.hash(), weapon_max_ammo(wpn));
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
				ntv::WEAPON::REMOVE_ALL_PED_WEAPONS(_h, true);
			}

			void switch_weapon(const hasher &wpn) {
				if (is_current_weapon(wpn)) {
					return;
				}
				if (is_in_vehicle()) {
					ntv::WEAPON::SET_CURRENT_PED_VEHICLE_WEAPON(_h, wpn.hash());
					if (!is_current_weapon(wpn) && arm::weapon_group(wpn).hash() != 0) {
						ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, wpn.hash(), 0, false, true);
					}
					return;
				}
				if (!has_weapon_in_pack(wpn)) {
					ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, wpn.hash(), 0, false, true);
					return;
				}
				ntv::WEAPON::SET_CURRENT_PED_WEAPON(_h, wpn.hash(), true);
			}

			hasher current_weapon() {
				hash_t h;
				if (is_in_vehicle()) {
					ntv::WEAPON::GET_CURRENT_PED_VEHICLE_WEAPON(_h, &h);
				} else {
					ntv::WEAPON::GET_CURRENT_PED_WEAPON(_h, &h, true);
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
				return ntv::WEAPON::HAS_PED_GOT_WEAPON(_h, wpn.hash(), false);
			}

			bool has_weapon(const hasher &wpn) {
				return is_current_weapon(wpn.hash()) ? true : has_weapon_in_pack(wpn);
			}

			void ammo(const hasher &type, int total) {
				ntv::WEAPON::SET_PED_AMMO_BY_TYPE(_h, type, total);
			}

			int ammo(const hasher &type) {
				return ntv::WEAPON::GET_PED_AMMO_BY_TYPE(_h, type.hash());
			}

			void add_ammo(const hasher &type, int count) {
				ammo(type, ammo(type) + count);
			}

			void ammo_no_consumption(bool toggle = true) {
				ntv::WEAPON::SET_PED_INFINITE_AMMO_CLIP(_h, toggle);
			}

			hasher weapon_ammo_type(const hasher &wpn) {
				return ntv::WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(_h, wpn.hash());
			}

			int weapon_max_ammo(const hasher &wpn) {
				int total;
				ntv::WEAPON::GET_MAX_AMMO(_h, wpn.hash(), &total);
				return total;
			}

			void thrown_weapon(const hasher &thr_wpn, int total) {
				if (!has_weapon(thr_wpn)) {
					ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, thr_wpn, total, false, false);
					return;
				}
				ammo(weapon_ammo_type(thr_wpn), total);
			}

			int thrown_weapon(const hasher &thr_wpn) {
				return ntv::WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(_h, thr_wpn.hash());
			}

			void add_thrown_weapon(const hasher &thr_wpn, int count) {
				ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, thr_wpn, count, false, false);
			}

			void print_weapon_info() {
				#ifdef DEBUG
					auto cur_wpn = current_weapon();
					if (cur_wpn == "WEAPON_UNARMED") {
						log("unarmed!");
						return;
					}

					std::stringstream ss;

					ss << "weapon ";
					for (auto &hr : arm::weapons) {
						if (hr == cur_wpn) {
							ss << hr.src_c_str() << " ";
							break;
						}
					}
					if (is_in_vehicle()) {
						for (auto &hr : arm::vehicle_weapons) {
							if (hr == cur_wpn) {
								ss << hr.src_c_str() << " ";
								break;
							}
						}
					}
					ss << std::hex << cur_wpn.hash() << std::endl;

					auto grp = arm::weapon_group(cur_wpn);
					ss << "  group: ";
					for (auto &hr : arm::weapon_groups) {
						if (hr == grp) {
							ss << hr.src_c_str() << " ";
							break;
						}
					}
					ss << grp.hash() << std::endl;

					auto amm_ty = weapon_ammo_type(cur_wpn);
					ss << "  ammo type: ";
					for (auto &hr : arm::ammo_types) {
						if (hr == amm_ty) {
							ss << hr.src_c_str() << " ";
							break;
						}
					}
					ss << amm_ty.hash();

					auto info = arm::weapon_info(cur_wpn);
					if (info.valid) {
						ss << std::endl
						<< "  damage: " << info.damage / 255.0f << std::endl
						<< "  speed: " << info.speed / 255.0f << std::endl
						<< "  capacity: " << info.capacity / 255.0f << std::endl
						<< "  accuracy: " << info.accuracy / 255.0f << std::endl
						<< "  range: " << info.range / 255.0f;
					}

					log(ss.str());
				#endif
			}

			void look();

			void stop_look() {
				ntv::AI::TASK_CLEAR_LOOK_AT(_h);
			}

			void focus(const vector3 &coords);

			void aim(bool toggle = true);

			void shoot(bool toggle = true);

			void shoot_once();

			void cover();

			void paralysis();

			////////////////////////////////////////////////////////////////////

			class group {
				public:
					group(const std::string &name) : _n(name), _h(0) {}

					~group() {
						del();
					}

					void del() {
						if (_h) {
							if (!in_task()) {
								return;
							}
							ntv::PED::REMOVE_RELATIONSHIP_GROUP(_h);
							_h = 0;
						}
					}

					operator hash_t() const {
						return _h;
					}

					void add(character chr);

					void rm(character chr) {
						ntv::PED::SET_PED_RELATIONSHIP_GROUP_HASH(chr, ntv::PED::GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(chr));
					}

					void cant_be_damaged(entity e, bool toggle = true) {
						ntv::ENTITY::SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(e, !toggle, _h);
					}

					void hate(const group &target) {
						ntv::PED::SET_RELATIONSHIP_BETWEEN_GROUPS(2, _h, target);
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

			sleep(1000);

			if (ntv::ENTITY::DOES_ENTITY_EXIST(chr) && !ntv::ENTITY::IS_ENTITY_DEAD(chr)) {
				change_body(chr);
				old_chr.free();
			}
		}

		inline void auto_get_parachute_in_plane(bool toggle = true) {
			ntv::PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(0, toggle);
		}

		inline void disable_automatic_respawn() {
			ntv::GAMEPLAY::SET_FADE_OUT_AFTER_DEATH(false);
			ntv::GAMEPLAY::SET_FADE_OUT_AFTER_ARREST(false);
			ntv::GAMEPLAY::SET_FADE_IN_AFTER_DEATH_ARREST(false);
			ntv::GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(true);
		}

		inline void clear_state() {
			ntv::GAMEPLAY::_RESET_LOCALPLAYER_STATE();
		}
	}

	class vehicle : public entity {
		public:
			vehicle(int native_handle = 0) : entity(native_handle) {}

			vehicle(model m, const vector3 &coords, float heading = 0.0f) :
				entity(ntv::VEHICLE::CREATE_VEHICLE(m.load(), coords.x, coords.y, coords.z, heading, false, false))
			{
				if (!_h) {
					return;
				}

				auto h = _h;
				gc::track(*this, [h]() mutable {
					ntv::VEHICLE::DELETE_VEHICLE(&h);
				});

				ntv::VEHICLE::SET_VEHICLE_MOD_KIT(_h, 0);
			}

			void del() {
				gc::untrack(*this);

				ntv::VEHICLE::DELETE_VEHICLE(&_h);
			}

			void free() {
				gc::untrack(*this);

				ntv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&_h);
			}

			void place_on_ground() {
				ntv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_h);
			}

			static constexpr int mod_type_sum = 50;

			int mod_sum(int mod_type) {
				return ntv::VEHICLE::GET_NUM_VEHICLE_MODS(_h, mod_type);
			}

			void mod(int mod_type, int mod) {
				ntv::VEHICLE::SET_VEHICLE_MOD(_h, mod_type, mod, true);
			}

			void mod(int mod_type) {
				ntv::VEHICLE::GET_VEHICLE_MOD(_h, mod_type);
			}

			void set_best_mods() {
				for (int i = 1; i < mod_type_sum; ++i) {
					if (i == 14 || i == 15 || i == 23 || i == 24 || i == 48) {
						continue;
					}

					auto n = mod_sum(i);
					if (n > 0) {
						mod(i, n - 1);
					}
				}
			}

			bool is_playing_radio() {
				return ntv::AUDIO::_IS_VEHICLE_RADIO_LOUD(_h);
			}

			std::string radio_station() {
				if (ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(ntv::PLAYER::PLAYER_PED_ID(), _h) && is_playing_radio()) {
					return ntv::AUDIO::GET_PLAYER_RADIO_STATION_NAME();
				}
				return "";
			}

			void radio_station(const std::string &rs = nullptr) {
				if (rs.empty()) {
					if (is_playing_radio()) {
						ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(_h, false);
					}
					return;
				}
				if (!is_playing_radio()) {
					ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(_h, true);
				}
				ntv::AUDIO::SET_VEH_RADIO_STATION(_h, rs.c_str());
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
				return ntv::VEHICLE::GET_VEHICLE_ENGINE_HEALTH(_h);
			}

			void engine_health(float v) {
				ntv::VEHICLE::SET_VEHICLE_ENGINE_HEALTH(_h, v);
			}

			static constexpr float min_petrol_tank_health = -4000.0f;
			static constexpr float max_petrol_tank_health = 1000.0f;

			/*
				1000 is max health
				Begins leaking gas at around 650 health
				-999.90002441406 appears to be minimum health, although nothing special occurs
			*/

			float petrol_tank_health() {
				return ntv::VEHICLE::GET_VEHICLE_PETROL_TANK_HEALTH(_h);
			}

			void petrol_tank_health(float v) {
				ntv::VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(_h, v);
			}

			void explode() {
				ntv::VEHICLE::EXPLODE_VEHICLE(_h, true, false);
			}

			void catches_fire() {
				ntv::VEHICLE::EXPLODE_VEHICLE(_h, false, false);
			}

			bool has(character chr) {
				return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(chr, _h);
			}

			character passenger(int seat) {
				return ntv::VEHICLE::GET_PED_IN_VEHICLE_SEAT(_h, seat);
			}

			bool has_passenger(int seat) {
				return !ntv::VEHICLE::IS_VEHICLE_SEAT_FREE(_h, seat);
			}

			int max_passengers() {
				return ntv::VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(_h);
			}

			void disable_crash_damage(bool toggle = true) {
				ntv::VEHICLE::SET_VEHICLE_STRONG(_h, toggle);
			}

			void action(int ac) {
				ntv::AI::TASK_VEHICLE_TEMP_ACTION(passenger(-1), _h, ac, -1);
			}

			enum class klass_t : int {
				none = -1,
				compact,
				sedan,
				suv,
				coupe,
				muscle,
				sport_classic,
				sport,
				super,
				motorcycle,
				off_road,
				industrial,
				utility,
				van,
				cycle,
				boat,
				helicopter,
				plane,
				service,
				emergency,
				military,
				commercial,
				train
			};

			static klass_t klass(const model &mi) {
				if (!mi.is_vehicle()) {
					return klass_t::none;
				}
				return static_cast<klass_t>(ntv::VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(mi));
			}

			klass_t klass() const {
				return static_cast<klass_t>(ntv::VEHICLE::GET_VEHICLE_CLASS(_h));
			}

			bool is_armed() {
				return ntv::VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(_h);
			}
	};

	inline void character::into_vehicle(vehicle veh, int seat) {
		ntv::PED::SET_PED_INTO_VEHICLE(_h, veh, seat);
	}

	inline vehicle character::current_vehicle() {
		return ntv::PED::GET_VEHICLE_PED_IS_IN(_h, false);
	}

	inline vehicle character::last_vehicle() {
		return ntv::PED::GET_VEHICLE_PED_IS_IN(_h, true);
	}

	inline vehicle character::trying_to_enter_vehicle() {
		return ntv::PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(_h);
	}

	inline int character::trying_to_enter_vehicle_seat() {
		return ntv::PED::GET_SEAT_PED_IS_TRYING_TO_ENTER(_h);
	}

	class plane : public vehicle {
		public:
			using vehicle::vehicle;

			enum class landing_gear_state : int {
				deployed = 0,
				closing,
				opening,
				retracted
			};

			void landing_gear(landing_gear_state state) {
				ntv::VEHICLE::CONTROL_LANDING_GEAR(_h, static_cast<int>(state));
			}

			landing_gear_state landing_gear() {
				return static_cast<landing_gear_state>(ntv::VEHICLE::GET_LANDING_GEAR_STATE(_h));
			}

			bool has_landing_gear() {
				return ntv::VEHICLE::_VEHICLE_HAS_LANDING_GEAR(_h);
			}
	};

	////////////////////////////////////////////////////////////////////////////

	// These data from ScriptHookV/NativeTrainer

	static constexpr std::array<hasher, 696> characters {{
		"player_zero", "player_one", "player_two", "a_c_boar", "a_c_chimp", "a_c_cow", "a_c_coyote", "a_c_deer", "a_c_fish", "a_c_hen",
		"a_c_cat_01", "a_c_chickenhawk", "a_c_cormorant", "a_c_crow", "a_c_dolphin", "a_c_humpback", "a_c_killerwhale", "a_c_pigeon", "a_c_seagull", "a_c_sharkhammer",
		"a_c_pig", "a_c_rat", "a_c_rhesus", "a_c_chop", "a_c_husky", "a_c_mtlion", "a_c_retriever", "a_c_sharktiger", "a_c_shepherd", "s_m_m_movalien_01",
		"a_f_m_beach_01", "a_f_m_bevhills_01", "a_f_m_bevhills_02", "a_f_m_bodybuild_01", "a_f_m_business_02", "a_f_m_downtown_01", "a_f_m_eastsa_01", "a_f_m_eastsa_02", "a_f_m_fatbla_01", "a_f_m_fatcult_01",
		"a_f_m_fatwhite_01", "a_f_m_ktown_01", "a_f_m_ktown_02", "a_f_m_prolhost_01", "a_f_m_salton_01", "a_f_m_skidrow_01", "a_f_m_soucentmc_01", "a_f_m_soucent_01", "a_f_m_soucent_02", "a_f_m_tourist_01",
		"a_f_m_trampbeac_01", "a_f_m_tramp_01", "a_f_o_genstreet_01", "a_f_o_indian_01", "a_f_o_ktown_01", "a_f_o_salton_01", "a_f_o_soucent_01", "a_f_o_soucent_02", "a_f_y_beach_01", "a_f_y_bevhills_01",
		"a_f_y_bevhills_02", "a_f_y_bevhills_03", "a_f_y_bevhills_04", "a_f_y_business_01", "a_f_y_business_02", "a_f_y_business_03", "a_f_y_business_04", "a_f_y_eastsa_01", "a_f_y_eastsa_02", "a_f_y_eastsa_03",
		"a_f_y_epsilon_01", "a_f_y_fitness_01", "a_f_y_fitness_02", "a_f_y_genhot_01", "a_f_y_golfer_01", "a_f_y_hiker_01", "a_f_y_hippie_01", "a_f_y_hipster_01", "a_f_y_hipster_02", "a_f_y_hipster_03",
		"a_f_y_hipster_04", "a_f_y_indian_01", "a_f_y_juggalo_01", "a_f_y_runner_01", "a_f_y_rurmeth_01", "a_f_y_scdressy_01", "a_f_y_skater_01", "a_f_y_soucent_01", "a_f_y_soucent_02", "a_f_y_soucent_03",
		"a_f_y_tennis_01", "a_f_y_topless_01", "a_f_y_tourist_01", "a_f_y_tourist_02", "a_f_y_vinewood_01", "a_f_y_vinewood_02", "a_f_y_vinewood_03", "a_f_y_vinewood_04", "a_f_y_yoga_01", "a_m_m_acult_01",
		"a_m_m_afriamer_01", "a_m_m_beach_01", "a_m_m_beach_02", "a_m_m_bevhills_01", "a_m_m_bevhills_02", "a_m_m_business_01", "a_m_m_eastsa_01", "a_m_m_eastsa_02", "a_m_m_farmer_01", "a_m_m_fatlatin_01",
		"a_m_m_genfat_01", "a_m_m_genfat_02", "a_m_m_golfer_01", "a_m_m_hasjew_01", "a_m_m_hillbilly_01", "a_m_m_hillbilly_02", "a_m_m_indian_01", "a_m_m_ktown_01", "a_m_m_malibu_01", "a_m_m_mexcntry_01",
		"a_m_m_mexlabor_01", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_m_prolhost_01", "a_m_m_rurmeth_01", "a_m_m_salton_01", "a_m_m_salton_02", "a_m_m_salton_03", "a_m_m_salton_04",
		"a_m_m_skater_01", "a_m_m_skidrow_01", "a_m_m_socenlat_01", "a_m_m_soucent_01", "a_m_m_soucent_02", "a_m_m_soucent_03", "a_m_m_soucent_04", "a_m_m_stlat_02", "a_m_m_tennis_01", "a_m_m_tourist_01",
		"a_m_m_trampbeac_01", "a_m_m_tramp_01", "a_m_m_tranvest_01", "a_m_m_tranvest_02", "a_m_o_acult_01", "a_m_o_acult_02", "a_m_o_beach_01", "a_m_o_genstreet_01", "a_m_o_ktown_01", "a_m_o_salton_01",
		"a_m_o_soucent_01", "a_m_o_soucent_02", "a_m_o_soucent_03", "a_m_o_tramp_01", "a_m_y_acult_01", "a_m_y_acult_02", "a_m_y_beachvesp_01", "a_m_y_beachvesp_02", "a_m_y_beach_01", "a_m_y_beach_02",
		"a_m_y_beach_03", "a_m_y_bevhills_01", "a_m_y_bevhills_02", "a_m_y_breakdance_01", "a_m_y_busicas_01", "a_m_y_business_01", "a_m_y_business_02", "a_m_y_business_03", "a_m_y_cyclist_01", "a_m_y_dhill_01",
		"a_m_y_downtown_01", "a_m_y_eastsa_01", "a_m_y_eastsa_02", "a_m_y_epsilon_01", "a_m_y_epsilon_02", "a_m_y_gay_01", "a_m_y_gay_02", "a_m_y_genstreet_01", "a_m_y_genstreet_02", "a_m_y_golfer_01",
		"a_m_y_hasjew_01", "a_m_y_hiker_01", "a_m_y_hippy_01", "a_m_y_hipster_01", "a_m_y_hipster_02", "a_m_y_hipster_03", "a_m_y_indian_01", "a_m_y_jetski_01", "a_m_y_juggalo_01", "a_m_y_ktown_01",
		"a_m_y_ktown_02", "a_m_y_latino_01", "a_m_y_methhead_01", "a_m_y_mexthug_01", "a_m_y_motox_01", "a_m_y_motox_02", "a_m_y_musclbeac_01", "a_m_y_musclbeac_02", "a_m_y_polynesian_01", "a_m_y_roadcyc_01",
		"a_m_y_runner_01", "a_m_y_runner_02", "a_m_y_salton_01", "a_m_y_skater_01", "a_m_y_skater_02", "a_m_y_soucent_01", "a_m_y_soucent_02", "a_m_y_soucent_03", "a_m_y_soucent_04", "a_m_y_stbla_01",
		"a_m_y_stbla_02", "a_m_y_stlat_01", "a_m_y_stwhi_01", "a_m_y_stwhi_02", "a_m_y_sunbathe_01", "a_m_y_surfer_01", "a_m_y_vindouche_01", "a_m_y_vinewood_01", "a_m_y_vinewood_02", "a_m_y_vinewood_03",
		"a_m_y_vinewood_04", "a_m_y_yoga_01", "u_m_y_proldriver_01", "u_m_y_rsranger_01", "u_m_y_sbike", "u_m_y_staggrm_01", "u_m_y_tattoo_01", "csb_abigail", "csb_anita", "csb_anton",
		"csb_ballasog", "csb_bride", "csb_burgerdrug", "csb_car3guy1", "csb_car3guy2", "csb_chef", "csb_chin_goon", "csb_cletus", "csb_cop", "csb_customer",
		"csb_denise_friend", "csb_fos_rep", "csb_g", "csb_groom", "csb_grove_str_dlr", "csb_hao", "csb_hugh", "csb_imran", "csb_janitor", "csb_maude",
		"csb_mweather", "csb_ortega", "csb_oscar", "csb_porndudes", "csb_porndudes_p", "csb_prologuedriver", "csb_prolsec", "csb_ramp_gang", "csb_ramp_hic", "csb_ramp_hipster",
		"csb_ramp_marine", "csb_ramp_mex", "csb_reporter", "csb_roccopelosi", "csb_screen_writer", "csb_stripper_01", "csb_stripper_02", "csb_tonya", "csb_trafficwarden", "cs_amandatownley",
		"cs_andreas", "cs_ashley", "cs_bankman", "cs_barry", "cs_barry_p", "cs_beverly", "cs_beverly_p", "cs_brad", "cs_bradcadaver", "cs_carbuyer",
		"cs_casey", "cs_chengsr", "cs_chrisformage", "cs_clay", "cs_dale", "cs_davenorton", "cs_debra", "cs_denise", "cs_devin", "cs_dom",
		"cs_dreyfuss", "cs_drfriedlander", "cs_fabien", "cs_fbisuit_01", "cs_floyd", "cs_guadalope", "cs_gurk", "cs_hunter", "cs_janet", "cs_jewelass",
		"cs_jimmyboston", "cs_jimmydisanto", "cs_joeminuteman", "cs_johnnyklebitz", "cs_josef", "cs_josh", "cs_lamardavis", "cs_lazlow", "cs_lestercrest", "cs_lifeinvad_01",
		"cs_magenta", "cs_manuel", "cs_marnie", "cs_martinmadrazo", "cs_maryann", "cs_michelle", "cs_milton", "cs_molly", "cs_movpremf_01", "cs_movpremmale",
		"cs_mrk", "cs_mrsphillips", "cs_mrs_thornhill", "cs_natalia", "cs_nervousron", "cs_nigel", "cs_old_man1a", "cs_old_man2", "cs_omega", "cs_orleans",
		"cs_paper", "cs_paper_p", "cs_patricia", "cs_priest", "cs_prolsec_02", "cs_russiandrunk", "cs_siemonyetarian", "cs_solomon", "cs_stevehains", "cs_stretch",
		"cs_tanisha", "cs_taocheng", "cs_taostranslator", "cs_tenniscoach", "cs_terry", "cs_tom", "cs_tomepsilon", "cs_tracydisanto", "cs_wade", "cs_zimbor",
		"g_f_y_ballas_01", "g_f_y_families_01", "g_f_y_lost_01", "g_f_y_vagos_01", "g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_m_armlieut_01", "g_m_m_chemwork_01", "g_m_m_chemwork_01_p", "g_m_m_chiboss_01",
		"g_m_m_chiboss_01_p", "g_m_m_chicold_01", "g_m_m_chicold_01_p", "g_m_m_chigoon_01", "g_m_m_chigoon_01_p", "g_m_m_chigoon_02", "g_m_m_korboss_01", "g_m_m_mexboss_01", "g_m_m_mexboss_02", "g_m_y_armgoon_02",
		"g_m_y_azteca_01", "g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_m_y_korean_01", "g_m_y_korean_02", "g_m_y_korlieut_01",
		"g_m_y_lost_01", "g_m_y_lost_02", "g_m_y_lost_03", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_mexgoon_02", "g_m_y_mexgoon_03", "g_m_y_mexgoon_03_p", "g_m_y_pologoon_01", "g_m_y_pologoon_01_p",
		"g_m_y_pologoon_02", "g_m_y_pologoon_02_p", "g_m_y_salvaboss_01", "g_m_y_salvagoon_01", "g_m_y_salvagoon_02", "g_m_y_salvagoon_03", "g_m_y_salvagoon_03_p", "g_m_y_strpunk_01", "g_m_y_strpunk_02", "hc_driver",
		"hc_gunman", "hc_hacker", "ig_abigail", "ig_amandatownley", "ig_andreas", "ig_ashley", "ig_ballasog", "ig_bankman", "ig_barry", "ig_barry_p",
		"ig_bestmen", "ig_beverly", "ig_beverly_p", "ig_brad", "ig_bride", "ig_car3guy1", "ig_car3guy2", "ig_casey", "ig_chef", "ig_chengsr",
		"ig_chrisformage", "ig_clay", "ig_claypain", "ig_cletus", "ig_dale", "ig_davenorton", "ig_denise", "ig_devin", "ig_dom", "ig_dreyfuss",
		"ig_drfriedlander", "ig_fabien", "ig_fbisuit_01", "ig_floyd", "ig_groom", "ig_hao", "ig_hunter", "ig_janet", "ig_jay_norris", "ig_jewelass",
		"ig_jimmyboston", "ig_jimmydisanto", "ig_joeminuteman", "ig_johnnyklebitz", "ig_josef", "ig_josh", "ig_kerrymcintosh", "ig_lamardavis", "ig_lazlow", "ig_lestercrest",
		"ig_lifeinvad_01", "ig_lifeinvad_02", "ig_magenta", "ig_manuel", "ig_marnie", "ig_maryann", "ig_maude", "ig_michelle", "ig_milton", "ig_molly",
		"ig_mrk", "ig_mrsphillips", "ig_mrs_thornhill", "ig_natalia", "ig_nervousron", "ig_nigel", "ig_old_man1a", "ig_old_man2", "ig_omega", "ig_oneil",
		"ig_orleans", "ig_ortega", "ig_paper", "ig_patricia", "ig_priest", "ig_prolsec_02", "ig_ramp_gang", "ig_ramp_hic", "ig_ramp_hipster", "ig_ramp_mex",
		"ig_roccopelosi", "ig_russiandrunk", "ig_screen_writer", "ig_siemonyetarian", "ig_solomon", "ig_stevehains", "ig_stretch", "ig_talina", "ig_tanisha", "ig_taocheng",
		"ig_taostranslator", "ig_taostranslator_p", "ig_tenniscoach", "ig_terry", "ig_tomepsilon", "ig_tonya", "ig_tracydisanto", "ig_trafficwarden", "ig_tylerdix", "ig_wade",
		"ig_zimbor", "mp_f_deadhooker", "mp_f_freemode_01", "mp_f_misty_01", "mp_f_stripperlite", "mp_g_m_pros_01", "mp_headtargets", "mp_m_claude_01", "mp_m_exarmy_01", "mp_m_famdd_01",
		"mp_m_fibsec_01", "mp_m_freemode_01", "mp_m_marston_01", "mp_m_niko_01", "mp_m_shopkeep_01", "mp_s_m_armoured_01", "", "", "", "",
		"", "s_f_m_fembarber", "s_f_m_maid_01", "s_f_m_shop_high", "s_f_m_sweatshop_01", "s_f_y_airhostess_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_f_y_cop_01", "s_f_y_factory_01",
		"s_f_y_hooker_01", "s_f_y_hooker_02", "s_f_y_hooker_03", "s_f_y_migrant_01", "s_f_y_movprem_01", "s_f_y_ranger_01", "s_f_y_scrubs_01", "s_f_y_sheriff_01", "s_f_y_shop_low", "s_f_y_shop_mid",
		"s_f_y_stripperlite", "s_f_y_stripper_01", "s_f_y_stripper_02", "s_f_y_sweatshop_01", "s_m_m_ammucountry", "s_m_m_armoured_01", "s_m_m_armoured_02", "s_m_m_autoshop_01", "s_m_m_autoshop_02", "s_m_m_bouncer_01",
		"s_m_m_chemsec_01", "s_m_m_ciasec_01", "s_m_m_cntrybar_01", "s_m_m_dockwork_01", "s_m_m_doctor_01", "s_m_m_fiboffice_01", "s_m_m_fiboffice_02", "s_m_m_gaffer_01", "s_m_m_gardener_01", "s_m_m_gentransport",
		"s_m_m_hairdress_01", "s_m_m_highsec_01", "s_m_m_highsec_02", "s_m_m_janitor", "s_m_m_lathandy_01", "s_m_m_lifeinvad_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_m_m_mariachi_01", "s_m_m_marine_01",
		"s_m_m_marine_02", "s_m_m_migrant_01", "u_m_y_zombie_01", "s_m_m_movprem_01", "s_m_m_movspace_01", "s_m_m_paramedic_01", "s_m_m_pilot_01", "s_m_m_pilot_02", "s_m_m_postal_01", "s_m_m_postal_02",
		"s_m_m_prisguard_01", "s_m_m_scientist_01", "s_m_m_security_01", "s_m_m_snowcop_01", "s_m_m_strperf_01", "s_m_m_strpreach_01", "s_m_m_strvend_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_m_ups_02",
		"s_m_o_busker_01", "s_m_y_airworker", "s_m_y_ammucity_01", "s_m_y_armymech_01", "s_m_y_autopsy_01", "s_m_y_barman_01", "s_m_y_baywatch_01", "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_y_busboy_01",
		"s_m_y_chef_01", "s_m_y_clown_01", "s_m_y_construct_01", "s_m_y_construct_02", "s_m_y_cop_01", "s_m_y_dealer_01", "s_m_y_devinsec_01", "s_m_y_dockwork_01", "s_m_y_doorman_01", "s_m_y_dwservice_01",
		"s_m_y_dwservice_02", "s_m_y_factory_01", "s_m_y_fireman_01", "s_m_y_garbage", "s_m_y_grip_01", "s_m_y_hwaycop_01", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03", "s_m_y_mime",
		"s_m_y_pestcont_01", "s_m_y_pilot_01", "s_m_y_prismuscl_01", "s_m_y_prisoner_01", "s_m_y_ranger_01", "s_m_y_robber_01", "s_m_y_sheriff_01", "s_m_y_shop_mask", "s_m_y_strvend_01", "s_m_y_swat_01",
		"s_m_y_uscg_01", "s_m_y_valet_01", "s_m_y_waiter_01", "s_m_y_winclean_01", "s_m_y_xmech_01", "s_m_y_xmech_02", "u_f_m_corpse_01", "u_f_m_miranda", "u_f_m_promourn_01", "u_f_o_moviestar",
		"u_f_o_prolhost_01", "u_f_y_bikerchic", "u_f_y_comjane", "u_f_y_corpse_01", "u_f_y_corpse_02", "u_f_y_hotposh_01", "u_f_y_jewelass_01", "u_f_y_mistress", "u_f_y_poppymich", "u_f_y_princess",
		"u_f_y_spyactress", "u_m_m_aldinapoli", "u_m_m_bankman", "u_m_m_bikehire_01", "u_m_m_fibarchitect", "u_m_m_filmdirector", "u_m_m_glenstank_01", "u_m_m_griff_01", "u_m_m_jesus_01", "u_m_m_jewelsec_01",
		"u_m_m_jewelthief", "u_m_m_markfost", "u_m_m_partytarget", "u_m_m_prolsec_01", "u_m_m_promourn_01", "u_m_m_rivalpap", "u_m_m_spyactor", "u_m_m_willyfist", "u_m_o_finguru_01", "u_m_o_taphillbilly",
		"u_m_o_tramp_01", "u_m_y_abner", "u_m_y_antonb", "u_m_y_babyd", "u_m_y_baygor", "u_m_y_burgerdrug_01", "u_m_y_chip", "u_m_y_cyclist_01", "u_m_y_fibmugger_01", "u_m_y_guido_01",
		"u_m_y_gunvend_01", "u_m_y_hippie_01", "u_m_y_imporage", "u_m_y_justin", "u_m_y_mani", "u_m_y_militarybum", "u_m_y_paparazzi", "u_m_y_party_01", "u_m_y_pogo_01", "u_m_y_prisoner_01",
		"ig_benny", "ig_g", "ig_vagspeak", "mp_m_g_vagfun_01", "mp_m_boatstaff_01", "mp_f_boatstaff_01"
	}};

	static constexpr std::array<const char *, 696> characters_desc {{
		"MICHAEL", "FRANKLIN", "TREVOR", "BOAR", "CHIMP", "COW", "COYOTE", "DEER", "FISH", "HEN",
		"CAT", "HAWK", "CORMORANT", "CROW", "DOLPHIN", "HUMPBACK", "WHALE", "PIGEON", "SEAGULL", "SHARKHAMMER" ,
		"PIG", "RAT", "RHESUS", "CHOP", "HUSKY", "MTLION", "RETRIEVER", "SHARKTIGER", "SHEPHERD", "ALIEN",
		"BEACH", "BEVHILLS", "BEVHILLS", "BODYBUILD", "BUSINESS", "DOWNTOWN", "EASTSA", "EASTSA", "FATBLA", "FATCULT",
		"FATWHITE", "KTOWN", "KTOWN", "PROLHOST", "SALTON", "SKIDROW", "SOUCENTMC", "SOUCENT", "SOUCENT", "TOURIST",
		"TRAMPBEAC", "TRAMP", "GENSTREET", "INDIAN", "KTOWN", "SALTON", "SOUCENT", "SOUCENT", "BEACH", "BEVHILLS",
		"BEVHILLS", "BEVHILLS", "BEVHILLS", "BUSINESS", "BUSINESS", "BUSINESS", "BUSINESS", "EASTSA", "EASTSA", "EASTSA",
		"EPSILON", "FITNESS", "FITNESS", "GENHOT", "GOLFER", "HIKER", "HIPPIE", "HIPSTER", "HIPSTER", "HIPSTER",
		"HIPSTER", "INDIAN", "JUGGALO", "RUNNER", "RURMETH", "SCDRESSY", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT",
		"TENNIS", "TOPLESS", "TOURIST", "TOURIST", "VINEWOOD", "VINEWOOD", "VINEWOOD", "VINEWOOD", "YOGA", "ACULT",
		"AFRIAMER", "BEACH", "BEACH", "BEVHILLS", "BEVHILLS", "BUSINESS", "EASTSA", "EASTSA", "FARMER", "FATLATIN",
		"GENFAT", "GENFAT", "GOLFER", "HASJEW", "HILLBILLY", "HILLBILLY", "INDIAN", "KTOWN", "MALIBU", "MEXCNTRY",
		"MEXLABOR", "OG_BOSS", "PAPARAZZI", "POLYNESIAN", "PROLHOST", "RURMETH", "SALTON", "SALTON", "SALTON", "SALTON",
		"SKATER", "SKIDROW", "SOCENLAT", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STLAT", "TENNIS", "TOURIST",
		"TRAMPBEAC", "TRAMP", "TRANVEST", "TRANVEST", "ACULT", "ACULT", "BEACH", "GENSTREET", "KTOWN", "SALTON",
		"SOUCENT", "SOUCENT", "SOUCENT", "TRAMP", "ACULT", "ACULT", "BEACHVESP", "BEACHVESP", "BEACH", "BEACH",
		"BEACH", "BEVHILLS", "BEVHILLS", "BREAKDANCE", "BUSICAS", "BUSINESS", "BUSINESS", "BUSINESS", "CYCLIST", "DHILL",
		"DOWNTOWN", "EASTSA", "EASTSA", "EPSILON", "EPSILON", "GAY", "GAY", "GENSTREET", "GENSTREET", "GOLFER",
		"HASJEW", "HIKER", "HIPPY", "HIPSTER", "HIPSTER", "HIPSTER", "INDIAN", "JETSKI", "JUGGALO", "KTOWN",
		"KTOWN", "LATINO", "METHHEAD", "MEXTHUG", "MOTOX", "MOTOX", "MUSCLBEAC", "MUSCLBEAC", "POLYNESIAN", "ROADCYC",
		"RUNNER", "RUNNER", "SALTON", "SKATER", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STBLA",
		"STBLA", "STLAT", "STWHI", "STWHI", "SUNBATHE", "SURFER", "VINDOUCHE", "VINEWOOD", "VINEWOOD", "VINEWOOD",
		"VINEWOOD", "YOGA", "PROLDRIVER", "RSRANGER", "SBIKE", "STAGGRM", "TATTOO", "ABIGAIL", "ANITA", "ANTON",
		"BALLASOG", "BRIDE", "BURGERDRUG", "CAR3GUY1", "CAR3GUY2", "CHEF", "CHIN_GOON", "CLETUS", "COP", "CUSTOMER",
		"DENISE_FRIEND", "FOS_REP", "G", "GROOM", "DLR", "HAO", "HUGH", "IMRAN", "JANITOR", "MAUDE",
		"MWEATHER", "ORTEGA", "OSCAR", "PORNDUDES", "PORNDUDES_P", "PROLOGUEDRIVER", "PROLSEC", "GANG", "HIC", "HIPSTER",
		"MARINE", "MEX", "REPORTER", "ROCCOPELOSI", "SCREEN_WRITER", "STRIPPER", "STRIPPER", "TONYA", "TRAFFICWARDEN", "AMANDATOWNLEY",
		"ANDREAS", "ASHLEY", "BANKMAN", "BARRY", "BARRY_P", "BEVERLY", "BEVERLY_P", "BRAD", "BRADCADAVER", "CARBUYER",
		"CASEY", "CHENGSR", "CHRISFORMAGE", "CLAY", "DALE", "DAVENORTON", "DEBRA", "DENISE", "DEVIN", "DOM",
		"DREYFUSS", "DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GUADALOPE", "GURK", "HUNTER", "JANET", "JEWELASS",
		"JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST", "LIFEINVAD",
		"MAGENTA", "MANUEL", "MARNIE", "MARTINMADRAZO", "MARYANN", "MICHELLE", "MILTON", "MOLLY", "MOVPREMF", "MOVPREMMALE",
		"MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ORLEANS",
		"PAPER", "PAPER_P", "PATRICIA", "PRIEST", "PROLSEC", "RUSSIANDRUNK", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH",
		"TANISHA", "TAOCHENG", "TAOSTRANSLATOR", "TENNISCOACH", "TERRY", "TOM", "TOMEPSILON", "TRACYDISANTO", "WADE", "ZIMBOR",
		"BALLAS", "FAMILIES", "LOST", "VAGOS", "ARMBOSS", "ARMGOON", "ARMLIEUT", "CHEMWORK", "CHEMWORK_P", "CHIBOSS",
		"CHIBOSS_P", "CHICOLD", "CHICOLD_P", "CHIGOON", "CHIGOON_P", "CHIGOON", "KORBOSS", "MEXBOSS", "MEXBOSS", "ARMGOON",
		"AZTECA", "BALLAEAST", "BALLAORIG", "BALLASOUT", "FAMCA", "FAMDNF", "FAMFOR", "KOREAN", "KOREAN", "KORLIEUT",
		"LOST", "LOST", "LOST", "MEXGANG", "MEXGOON", "MEXGOON", "MEXGOON", "MEXGOON_P", "POLOGOON", "POLOGOON_P",
		"POLOGOON", "POLOGOON_P", "SALVABOSS", "SALVAGOON", "SALVAGOON", "SALVAGOON", "SALVAGOON_P", "STRPUNK", "STRPUNK", "HC_DRIVER",
		"HC_GUNMAN", "HC_HACKER", "ABIGAIL", "AMANDATOWNLEY", "ANDREAS", "ASHLEY", "BALLASOG", "BANKMAN", "BARRY", "BARRY_P",
		"BESTMEN", "BEVERLY", "BEVERLY_P", "BRAD", "BRIDE", "CAR3GUY1", "CAR3GUY2", "CASEY", "CHEF", "CHENGSR",
		"CHRISFORMAGE", "CLAY", "CLAYPAIN", "CLETUS", "DALE", "DAVENORTON", "DENISE", "DEVIN", "DOM", "DREYFUSS",
		"DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GROOM", "HAO", "HUNTER", "JANET", "JAY_NORRIS", "JEWELASS",
		"JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "KERRYMCINTOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST",
		"LIFEINVAD", "LIFEINVAD", "MAGENTA", "MANUEL", "MARNIE", "MARYANN", "MAUDE", "MICHELLE", "MILTON", "MOLLY",
		"MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ONEIL",
		"ORLEANS", "ORTEGA", "PAPER", "PATRICIA", "PRIEST", "PROLSEC", "GANG", "HIC", "HIPSTER", "MEX",
		"ROCCOPELOSI", "RUSSIANDRUNK", "SCREEN_WRITER", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH", "TALINA", "TANISHA", "TAOCHENG",
		"TAOSTRANSLATOR", "TAOSTRANSLATOR_P", "TENNISCOACH", "TERRY", "TOMEPSILON", "TONYA", "TRACYDISANTO", "TRAFFICWARDEN", "TYLERDIX", "WADE",
		"ZIMBOR", "DEADHOOKER", "FREEMODE", "MISTY", "STRIPPERLITE", "PROS", "MP_HEADTARGETS", "CLAUDE", "EXARMY", "FAMDD",
		"FIBSEC", "FREEMODE", "MARSTON", "NIKO", "SHOPKEEP", "ARMOURED", "NONE", "NONE", "NONE", "NONE",
		"NONE", "FEMBARBER", "MAID", "SHOP_HIGH", "SWEATSHOP", "AIRHOSTESS", "BARTENDER", "BAYWATCH", "COP", "FACTORY",
		"HOOKER", "HOOKER", "HOOKER", "MIGRANT", "MOVPREM", "RANGER", "SCRUBS", "SHERIFF", "SHOP_LOW", "SHOP_MID",
		"STRIPPERLITE", "STRIPPER", "STRIPPER", "SWEATSHOP", "AMMUCOUNTRY", "ARMOURED", "ARMOURED", "AUTOSHOP", "AUTOSHOP", "BOUNCER",
		"CHEMSEC", "CIASEC", "CNTRYBAR", "DOCKWORK", "DOCTOR", "FIBOFFICE", "FIBOFFICE", "GAFFER", "GARDENER", "GENTRANSPORT",
		"HAIRDRESS", "HIGHSEC", "HIGHSEC", "JANITOR", "LATHANDY", "LIFEINVAD", "LINECOOK", "LSMETRO", "MARIACHI", "MARINE",
		"MARINE", "MIGRANT", "ZOMBIE", "MOVPREM", "MOVSPACE", "PARAMEDIC", "PILOT", "PILOT", "POSTAL", "POSTAL",
		"PRISGUARD", "SCIENTIST", "SECURITY", "SNOWCOP", "STRPERF", "STRPREACH", "STRVEND", "TRUCKER", "UPS", "UPS",
		"BUSKER", "AIRWORKER", "AMMUCITY", "ARMYMECH", "AUTOPSY", "BARMAN", "BAYWATCH", "BLACKOPS", "BLACKOPS", "BUSBOY",
		"CHEF", "CLOWN", "CONSTRUCT", "CONSTRUCT", "COP", "DEALER", "DEVINSEC", "DOCKWORK", "DOORMAN", "DWSERVICE",
		"DWSERVICE", "FACTORY", "FIREMAN", "GARBAGE", "GRIP", "HWAYCOP", "MARINE", "MARINE", "MARINE", "MIME",
		"PESTCONT", "PILOT", "PRISMUSCL", "PRISONER", "RANGER", "ROBBER", "SHERIFF", "SHOP_MASK", "STRVEND", "SWAT",
		"USCG", "VALET", "WAITER", "WINCLEAN", "XMECH", "XMECH", "CORPSE", "MIRANDA", "PROMOURN", "MOVIESTAR",
		"PROLHOST", "BIKERCHIC", "COMJANE", "CORPSE", "CORPSE", "HOTPOSH", "JEWELASS", "MISTRESS", "POPPYMICH", "PRINCESS",
		"SPYACTRESS", "ALDINAPOLI", "BANKMAN", "BIKEHIRE", "FIBARCHITECT", "FILMDIRECTOR", "GLENSTANK", "GRIFF", "JESUS", "JEWELSEC",
		"JEWELTHIEF", "MARKFOST", "PARTYTARGET", "PROLSEC", "PROMOURN", "RIVALPAP", "SPYACTOR", "WILLYFIST", "FINGURU", "TAPHILLBILLY",
		"TRAMP", "ABNER", "ANTONB", "BABYD", "BAYGOR", "BURGERDRUG", "CHIP", "CYCLIST", "FIBMUGGER", "GUIDO",
		"GUNVEND", "HIPPIE", "IMPORAGE", "JUSTIN", "MANI", "MILITARYBUM", "PAPARAZZI", "PARTY", "POGO", "PRISONER",
		"BENNY", "G", "VAGSPEAK", "VAGFUN", "BOATSTAFF", "FEMBOATSTAFF"
	}};

	static constexpr std::array<hasher, 304> base_vehicles {{
		"NINEF", "NINEF2", "BLISTA", "ASEA", "ASEA2", "BOATTRAILER", "BUS", "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2",
		"SUNTRAP", "COACH", "AIRBUS", "ASTEROPE", "AIRTUG", "AMBULANCE", "BARRACKS", "BARRACKS2", "BALLER", "BALLER2",
		"BJXL", "BANSHEE", "BENSON", "BFINJECTION", "BIFF", "BLAZER", "BLAZER2", "BLAZER3", "BISON", "BISON2",
		"BISON3", "BOXVILLE", "BOXVILLE2", "BOXVILLE3", "BOBCATXL", "BODHI2", "BUCCANEER", "BUFFALO", "BUFFALO2", "BULLDOZER",
		"BULLET", "BLIMP", "BURRITO", "BURRITO2", "BURRITO3", "BURRITO4", "BURRITO5", "CAVALCADE", "CAVALCADE2", "POLICET",
		"GBURRITO", "CABLECAR", "CADDY", "CADDY2", "CAMPER", "CARBONIZZARE", "CHEETAH", "COMET2", "COGCABRIO", "COQUETTE",
		"CUTTER", "GRESLEY", "DILETTANTE", "DILETTANTE2", "DUNE", "DUNE2", "HOTKNIFE", "DLOADER", "DUBSTA", "DUBSTA2",
		"DUMP", "RUBBLE", "DOCKTUG", "DOMINATOR", "EMPEROR", "EMPEROR2", "EMPEROR3", "ENTITYXF", "EXEMPLAR", "ELEGY2",
		"F620", "FBI", "FBI2", "FELON", "FELON2", "FELTZER2", "FIRETRUK", "FLATBED", "FORKLIFT", "FQ2",
		"FUSILADE", "FUGITIVE", "FUTO", "GRANGER", "GAUNTLET", "HABANERO", "HAULER", "HANDLER", "INFERNUS", "INGOT",
		"INTRUDER", "ISSI2", "JACKAL", "JOURNEY", "JB700", "KHAMELION", "LANDSTALKER", "LGUARD", "MANANA", "MESA",
		"MESA2", "MESA3", "CRUSADER", "MINIVAN", "MIXER", "MIXER2", "MONROE", "MOWER", "MULE", "MULE2",
		"ORACLE", "ORACLE2", "PACKER", "PATRIOT", "PBUS", "PENUMBRA", "PEYOTE", "PHANTOM", "PHOENIX", "PICADOR",
		"POUNDER", "POLICE", "POLICE4", "POLICE2", "POLICE3", "POLICEOLD1", "POLICEOLD2", "PONY", "PONY2", "PRAIRIE",
		"PRANGER", "PREMIER", "PRIMO", "PROPTRAILER", "RANCHERXL", "RANCHERXL2", "RAPIDGT", "RAPIDGT2", "RADI", "RATLOADER",
		"REBEL", "REGINA", "REBEL2", "RENTALBUS", "RUMPO", "RUMPO2", "RHINO", "RIOT", "RIPLEY", "ROCOTO",
		"ROMERO", "SABREGT", "SADLER", "SADLER2", "SANDKING", "SANDKING2", "SCHAFTER2", "SCHWARZER", "SCRAP", "SEMINOLE",
		"SENTINEL", "SENTINEL2", "ZION", "ZION2", "SERRANO", "SHERIFF", "SHERIFF2", "SPEEDO", "SPEEDO2", "STANIER",
		"STINGER", "STINGERGT", "STOCKADE", "STOCKADE3", "STRATUM", "SULTAN", "SUPERD", "SURANO", "SURFER", "SURFER2",
		"SURGE", "TACO", "TAILGATER", "TAXI", "TRASH", "TRACTOR", "TRACTOR2", "TRACTOR3", "GRAINTRAILER", "BALETRAILER",
		"TIPTRUCK", "TIPTRUCK2", "TORNADO", "TORNADO2", "TORNADO3", "TORNADO4", "TOURBUS", "TOWTRUCK", "TOWTRUCK2", "UTILLITRUCK",
		"UTILLITRUCK2", "UTILLITRUCK3", "WASHINGTON", "STRETCH", "YOUGA", "ZTYPE", "SANCHEZ", "SANCHEZ2", "SCORCHER", "TRIBIKE",
		"TRIBIKE2", "TRIBIKE3", "FIXTER", "CRUISER", "BMX", "POLICEB", "AKUMA", "CARBONRS", "BAGGER", "BATI",
		"BATI2", "RUFFIAN", "DAEMON", "DOUBLE", "PCJ", "VADER", "VIGERO", "FAGGIO2", "HEXER", "ANNIHILATOR",
		"BUZZARD", "BUZZARD2", "CARGOBOB2", "CARGOBOB3", "SKYLIFT", "POLMAV", "MAVERICK", "NEMESIS", "FROGGER", "FROGGER2",
		"CUBAN800", "DUSTER", "STUNT", "MAMMATUS", "JET", "SHAMAL", "LUXOR", "TITAN", "LAZER", "CARGOPLANE",
		"SQUALO", "MARQUIS", "DINGHY2", "JETMAX", "PREDATOR", "SEASHARK2", "SUBMERSIBLE", "TRAILERS", "TRAILERS2", "TRAILERS3",
		"TVTRAILER", "RAKETRAILER", "TANKER", "TRAILERLOGS", "TR2", "TR3", "TR4", "TRFLAT", "TRAILERSMALL", "VELUM",
		"ADDER", "VOLTIC", "VACCA", "FUROREGT", "BTYPE", "DOMINATOR2", "SUBMERSIBLE2", "RATLOADER2", "BUCCANEER2", "VOODOO",
		"CARGOBOB4", "COGNOSCENTI", "COGNOSCENTI2", "DINGHY4", "NIGHTSHADE", "SEASHARK3", "SPEEDER2", "SUPERVOLITO", "SUPERVOLITO2", "TORO2",
		"TROPIC2", "VALKYRIE2", "VERLIERER2", "BTYPE3"
	}};

	const std::vector<hasher> &dlc_vehicles();

	void unlock_banned_vehicles();

	const std::vector<hasher> &banned_vehicles();
} /* nob */
