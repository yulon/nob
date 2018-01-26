#pragma once

#include "entity.hpp"

namespace nob {
	namespace player {
		constexpr int native_handle() {
			return 0;
		}

		inline character body() {
			return ntv::PLAYER::PLAYER_PED_ID();
		}

		inline void change_body(character chr) {
			ntv::PLAYER::CHANGE_PLAYER_PED(0, chr, true, true);
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

		inline entity aiming_entity() {
			int e;
			ntv::PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(0, &e);
			return entity(e);
		}

		inline void damage_modifier(float val) {
			ntv::PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(0, val);
			ntv::PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(0, val);
			ntv::PLAYER::SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(0, val);
		}
	}
}
