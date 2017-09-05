#pragma once

#include "nob/shv/main.hpp"
#include "nob/shv/natives.hpp"

#include <string>
#include <functional>
#include <vector>
#include <array>

namespace nob {
	void on_first_frame();
	uintptr_t add_frame_task(const std::function<void()> &handler);
	void del_frame_task(uintptr_t id, bool wait_ran = true);
	void wait(size_t ms);
	inline void wait_next_frame() { wait(0); }
	void wait(const std::function<bool()> &cond);

	////////////////////////////////////////////////////////////////////////////

	struct vector3 {
		float x, y, z;
	};

	namespace world {
		inline float get_ground_height(const vector3 &coords) {
			shv::STREAMING::LOAD_SCENE(coords.x, coords.y, coords.z);

			float height;
			do {
				wait(1000);
				shv::GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &height, 0);
			} while (height == 0);

			return height;
		}
	}

	class model {
		public:
			DWORD shv_model;

			model(std::string name) : shv_model(shv::GAMEPLAY::GET_HASH_KEY((char *)name.c_str())) {
				if (shv::STREAMING::IS_MODEL_IN_CDIMAGE(shv_model) && shv::STREAMING::IS_MODEL_VALID(shv_model)) {
					shv::STREAMING::REQUEST_MODEL(shv_model);
					do {
						wait_next_frame();
					} while (!shv::STREAMING::HAS_MODEL_LOADED(shv_model));
				}
			}

			void free() {
				shv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(shv_model);
			}

			////////////////////////////////////////////////////////////////////

			static const std::array<const char *, 696> characters;
			static const std::array<const char *, 696> characters_des;
			static const std::array<const char *, 400> vehicles;
			static std::vector<std::string> mp_vehicles;
	};

	class character {
		public:
			shv::Ped shv_ped;

			character(model m, const vector3 &coords) : shv_ped(shv::PED::CREATE_PED(4, m.shv_model, coords.x, coords.y, world::get_ground_height(coords) + 1, 0.0f, FALSE, TRUE)) {}
			character(shv::Ped ped) : shv_ped(ped) {}

			void free() {
				shv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&shv_ped);
			}

			bool is_dead() {
				return shv::ENTITY::IS_ENTITY_DEAD(shv_ped);
			}

			vector3 pos(const vector3 &rcs_offset = {0, 0, 0}) const {
				auto co = shv::ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(shv_ped, rcs_offset.x, rcs_offset.y, rcs_offset.z);
				return {co.x, co.y, co.z};
			}

			void move(const vector3 &coords) {
				shv::ENTITY::SET_ENTITY_COORDS(shv_ped, coords.x, coords.y, world::get_ground_height(coords) + 1, TRUE, TRUE, TRUE, TRUE);
			}

			void set_random_component() {
				shv::PED::SET_PED_RANDOM_COMPONENT_VARIATION(shv_ped, FALSE);
			}

			void set_default_component() {
				shv::PED::SET_PED_DEFAULT_COMPONENT_VARIATION(shv_ped);
			}

			void set_last_component() {
				for (int i = 0; i < 10; i++) {
					for (int d = 9; d >= 0; d--) {
						for (int t = 9; t >= 0; t--) {
							if (shv::PED::IS_PED_COMPONENT_VARIATION_VALID(shv_ped, i, d, t)) {
								shv::PED::SET_PED_COMPONENT_VARIATION(shv_ped, i, d, t, 0);
								break;
							}
						}
					}
				}
			}

			vector3 get_rotation() const {
				auto ro = shv::ENTITY::GET_ENTITY_ROTATION(shv_ped, 2);
				return {ro.x, ro.y, ro.z};
			}

			void set_rotation(const vector3 &ro) {
				shv::ENTITY::SET_ENTITY_ROTATION(shv_ped, ro.x, ro.y, ro.z, 2, TRUE);
			}
	};

	namespace player {
		extern shv::Player shv_player;

		inline character controlling() {
			return shv::PLAYER::PLAYER_PED_ID();
		}

		inline void control(character chr) {
			shv::PLAYER::CHANGE_PLAYER_PED(shv_player, chr.shv_ped, TRUE, TRUE);
		}

		inline void swicth(character chr) {
			auto old_chr = controlling();
			auto old_chr_coords = old_chr.pos({ 0, 0, 0 });
			auto chr_coords = chr.pos({ 0, 0, 0 });

			int st = shv::STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(old_chr_coords.x, old_chr_coords.y, old_chr_coords.z, chr_coords.x, chr_coords.y, chr_coords.z);
			shv::STREAMING::START_PLAYER_SWITCH(old_chr.shv_ped, chr.shv_ped, 0, st);

			wait(1000);

			if (!shv::ENTITY::IS_ENTITY_DEAD(chr.shv_ped)) {
				control(chr);
				shv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&old_chr.shv_ped);
			}
		}
	}

	class vehicle {
		public:
			shv::Vehicle shv_vehicle;

			vehicle(model m, const vector3 &coords) : shv_vehicle(shv::VEHICLE::CREATE_VEHICLE(m.shv_model, coords.x, coords.y, coords.z, 0.0, FALSE, TRUE)) {}

			void free() {
				shv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&shv_vehicle);
			}

			void place_on_ground() {
				shv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(shv_vehicle);
			}

			////////////////////////////////////////////////////////////////////

			static void unlock_mp_vehicles();
	};
}
