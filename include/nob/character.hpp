#pragma once

#include "ntv.hpp"
#include "model.hpp"
#include "vector.hpp"

namespace nob {
	class character {
		public:
			ntv::Ped ntv_ped;

			character(model m, const vector3 &coords, bool player_shadow = false) : ntv_ped(ntv::PED::CREATE_PED(4, m.ntv_model, coords.x, coords.y, coords.z, 0.0f, false, true)) {
				if (player_shadow) {
					ntv::PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ntv_ped, true);
					ntv::PED::SET_PED_FLEE_ATTRIBUTES(ntv_ped, 0, 0);
					ntv::PED::SET_PED_COMBAT_ATTRIBUTES(ntv_ped, 292, true);
					ntv::PED::SET_PED_DIES_INSTANTLY_IN_WATER(ntv_ped, false);
					ntv::PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(ntv_ped, 1); // Blocks ragdolling when shot.
					ntv::WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(ntv_ped, false);
				}
				ntv::PED::SET_PED_CONFIG_FLAG(ntv_ped, 281, true); // PED_FLAG_NO_WRITHE
			}

			character(ntv::Ped ped) : ntv_ped(ped) {}

			void del() {
				ntv::PED::DELETE_PED(&ntv_ped);
			}

			void remove() {
				ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ntv_ped);
			}

			bool is_dead() {
				return ntv::ENTITY::IS_ENTITY_DEAD(ntv_ped);
			}

			void resurrect() {
				ntv::ENTITY::SET_ENTITY_HEALTH(ntv_ped, ntv::ENTITY::GET_ENTITY_MAX_HEALTH(ntv_ped));
				ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(ntv_ped);
				ntv::ENTITY::SET_ENTITY_COLLISION(ntv_ped, true, true);
			}

			vector3 pos(const vector3 &rcs_offset = {0, 0, 0}) const {
				auto co = ntv::ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ntv_ped, rcs_offset.x, rcs_offset.y, rcs_offset.z);
				return {co.x, co.y, co.z};
			}

			void move(const vector3 &coords) {
				ntv::ENTITY::SET_ENTITY_COORDS(ntv_ped, coords.x, coords.y, coords.z, true, true, true, true);
			}

			void set_random_outfit() {
				ntv::PED::SET_PED_RANDOM_COMPONENT_VARIATION(ntv_ped, false);
			}

			void set_default_outfit() {
				ntv::PED::SET_PED_DEFAULT_COMPONENT_VARIATION(ntv_ped);
			}

			void set_last_outfit() {
				for (int i = 0; i < 12; i++) {
					for (int d = ntv::PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ntv_ped, i) - 1; d >= 0; d--) {
						for (int t = ntv::PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ntv_ped, i, d) - 1; t >= 0; t--) {
							if (ntv::PED::IS_PED_COMPONENT_VARIATION_VALID(ntv_ped, i, d, t)) {
								ntv::PED::SET_PED_COMPONENT_VARIATION(ntv_ped, i, d, t, 0);
								break;
							}
						}
					}
				}
			}

			vector3 get_rotation() const {
				auto ro = ntv::ENTITY::GET_ENTITY_ROTATION(ntv_ped, 2);
				return {ro.x, ro.y, ro.z};
			}

			void set_rotation(const vector3 &ro) {
				ntv::ENTITY::SET_ENTITY_ROTATION(ntv_ped, ro.x, ro.y, ro.z, 2, true);
			}
	};
} /* nob */
