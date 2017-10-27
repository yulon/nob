#pragma once

#include "ntv.hpp"
#include "model.hpp"
#include "vector.hpp"
#include "script.hpp"

#include <tmd/shared_obj.hpp>

namespace nob {
	class entity_c {
		public:
			int native_handle() const {
				return _ntv_hdl;
			}

			void del() {
				ntv::ENTITY::DELETE_ENTITY(&_ntv_hdl);
			}

			void free() {
				ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&_ntv_hdl);
			}

			bool is_dead() {
				return ntv::ENTITY::IS_ENTITY_DEAD(_ntv_hdl);
			}

			vector3 pos(const vector3 &rcs_offset = {0, 0, 0}) const {
				auto co = ntv::ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(_ntv_hdl, rcs_offset.x, rcs_offset.y, rcs_offset.z);
				return {co.x, co.y, co.z};
			}

			void move(const vector3 &coords) {
				ntv::ENTITY::SET_ENTITY_COORDS(_ntv_hdl, coords.x, coords.y, coords.z, true, true, true, true);
			}

			vector3 get_rotation() const {
				auto ro = ntv::ENTITY::GET_ENTITY_ROTATION(_ntv_hdl, 2);
				return {ro.x, ro.y, ro.z};
			}

			void set_rotation(const vector3 &ro) {
				ntv::ENTITY::SET_ENTITY_ROTATION(_ntv_hdl, ro.x, ro.y, ro.z, 2, true);
			}

		protected:
			int _ntv_hdl;
	};

	template <typename SO>
	class character_c : public entity_c { friend SO;
		public:
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
				if (_run) {
					_run.del();
				}
				ntv::AI::TASK_STAND_STILL(_ntv_hdl, -1);
			}

			void run(float speed = SO::speed_walk) {
				_run_speed = speed;

				if (!_run) {
					_run = task([this]() {
						ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
							_ntv_hdl,
							_face.x, _face.y, _face.z,
							_run_speed,
							-1, 0, 0
						);
					});
				}
			}

			void face(vector3 co, float heading) {
				_face = co;
				if (ntv::PED::IS_PED_JUMPING(_ntv_hdl)) {
					ntv::ENTITY::SET_ENTITY_HEADING(_ntv_hdl, heading);
				}
			}

			void jump() {
				if (_run) {
					_run.del();
				}
				ntv::AI::TASK_JUMP(_ntv_hdl, false, false, false);
			}

		private:
			task _run;
			float _run_speed;
			vector3 _face;
	};

	class character : public tmd::shared_obj<character_c<character>> {
		public:
			enum class motion_state : uint8_t {
				still,
				walking,
				runing,
				sprinting,
				jumping,
				falling
			};

			static constexpr float speed_walk = 1.0f;
			static constexpr float speed_run = 1.2f;
			static constexpr float speed_sprint = 3.0f;

			////////////////////////////////////////////////////////////////////

			character() {}

			character(model m, const vector3 &coords, bool player_shadow = false) {
				alloc();

				_m->_ntv_hdl = ntv::PED::CREATE_PED(4, m.ntv_model, coords.x, coords.y, coords.z, 0.0f, false, true);

				if (player_shadow) {
					ntv::PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(_m->_ntv_hdl, true);
					ntv::PED::SET_PED_FLEE_ATTRIBUTES(_m->_ntv_hdl, 0, 0);
					ntv::PED::SET_PED_COMBAT_ATTRIBUTES(_m->_ntv_hdl, 292, true);
					ntv::PED::SET_PED_DIES_INSTANTLY_IN_WATER(_m->_ntv_hdl, false);
					ntv::PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(_m->_ntv_hdl, 1); // Blocks ragdolling when shot.
					ntv::WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(_m->_ntv_hdl, false);
				}
				ntv::PED::SET_PED_CONFIG_FLAG(_m->_ntv_hdl, 281, true); // PED_FLAG_NO_WRITHE
			}

			character(ntv::Ped ped) {
				alloc();
				_m->_ntv_hdl = ped;
			}
	};

	namespace player {
		constexpr int native_handle() {
			return 0;
		}

		inline character body() {
			return ntv::PLAYER::PLAYER_PED_ID();
		}

		inline void change_body(const character &chr) {
			ntv::PLAYER::CHANGE_PLAYER_PED(native_handle(), chr->native_handle(), true, true);
		}

		inline void switch_body(const character &chr) {
			auto old_chr = body();
			auto old_chr_coords = old_chr->pos({ 0, 0, 0 });
			auto chr_coords = chr->pos({ 0, 0, 0 });

			int st = ntv::STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(old_chr_coords.x, old_chr_coords.y, old_chr_coords.z, chr_coords.x, chr_coords.y, chr_coords.z);
			ntv::STREAMING::START_PLAYER_SWITCH(old_chr->native_handle(), chr->native_handle(), 0, st);

			wait(1000);

			if (ntv::ENTITY::DOES_ENTITY_EXIST(chr->native_handle()) && !ntv::ENTITY::IS_ENTITY_DEAD(chr->native_handle())) {
				change_body(chr);
				old_chr->free();
			}
		}
	}

	template <typename SO>
	class vehicle_c : public entity_c { friend SO;
		public:
			void del() {
				ntv::VEHICLE::DELETE_VEHICLE(&_ntv_hdl);
			}

			void remove() {
				ntv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&_ntv_hdl);
			}

			void place_on_ground() {
				ntv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_ntv_hdl);
			}

			constexpr int get_mod_type_sum() {
				return 50;
			}

			int get_mod_sum(int mod_type) {
				return ntv::VEHICLE::GET_NUM_VEHICLE_MODS(_ntv_hdl, mod_type);
			}

			void set_mod(int mod_type, int mod) {
				ntv::VEHICLE::SET_VEHICLE_MOD(_ntv_hdl, mod_type, mod, true);
			}

			void get_mod(int mod_type) {
				ntv::VEHICLE::GET_VEHICLE_MOD(_ntv_hdl, mod_type);
			}

			void set_best_mods() {
				for (int i = 0; i < get_mod_type_sum(); i++) {
					auto n = get_mod_sum(i);
					if (n > 0) {
						ntv::VEHICLE::SET_VEHICLE_MOD(_ntv_hdl, i, n - 1, false);
					}
				}
			}

			bool has(const character &chr) {
				return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(chr->native_handle(), _ntv_hdl);
			}

			bool is_playing_radio() {
				return ntv::AUDIO::_IS_VEHICLE_RADIO_LOUD(_ntv_hdl);
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
						ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(_ntv_hdl, false);
					}
					return;
				}
				if (!is_playing_radio()) {
					ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(_ntv_hdl, true);
				}
				ntv::AUDIO::SET_VEH_RADIO_STATION(_ntv_hdl, radio_station.c_str());
			}
	};

	class vehicle : public tmd::shared_obj<vehicle_c<vehicle>> {
		public:
			static void unlock_banned_vehicles();

			////////////////////////////////////////////////////////////////////

			vehicle() {}

			vehicle(model m, const vector3 &coords, float heading = 0.0f) {
				alloc();
				_m->_ntv_hdl = ntv::VEHICLE::CREATE_VEHICLE(m.ntv_model, coords.x, coords.y, coords.z, heading, false, true);
				ntv::VEHICLE::SET_VEHICLE_MOD_KIT(_m->_ntv_hdl, 0);
			}
	};
} /* nob */
