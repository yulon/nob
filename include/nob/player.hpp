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

		inline void disable_control(bool toggle = true) {
			ntv::PLAYER::SET_PLAYER_CONTROL(body(), !toggle, 0);
		}

		inline void switch_scene(character chr) {
			disable_control();
			ntv::STREAMING::START_PLAYER_SWITCH(body(), chr, 8, 2);
			while (ntv::STREAMING::GET_PLAYER_SWITCH_STATE() < 3) {
				sleep(1000);
			}
			auto pos = chr.pos();
			ntv::STREAMING::NEW_LOAD_SCENE_START_SPHERE(pos.x, pos.y, pos.z, 100.0f, 0);
			while (!ntv::STREAMING::IS_NEW_LOAD_SCENE_LOADED()) {
				sleep(1000);
			}
		}

		static character _switch_scene_chr;

		inline void switch_scene(const vector3 &pos) {
			_switch_scene_chr = character("a_c_chop", pos);
			_switch_scene_chr.alpha(0);
			_switch_scene_chr.collidable(false);
			_switch_scene_chr.freeze_pos();
			switch_scene(_switch_scene_chr);
		}

		inline void switch_scene_finish() {
			/*auto vVar6 = ntv::CAM::GET_CAM_COORD(0);
			auto vVar11 = ntv::CAM::GET_CAM_ROT(0, 2);
			auto fVar12 = ntv::CAM::GET_CAM_FOV(0);
			auto uVar13 = ntv::CAM::GET_CAM_FAR_CLIP(0);
			ntv::STREAMING::SET_PLAYER_SWITCH_OUTRO(vVar6.x, vVar6.y, vVar6.z, vVar11.x, vVar11.y, vVar11.z, fVar12, uVar13, 2);*/
			while (ntv::STREAMING::GET_PLAYER_SWITCH_STATE() != 8) {
				sleep(1000);
			}
			ntv::GRAPHICS::_START_SCREEN_EFFECT("CamPushInNeutral", 0, false);
			sleep(400);
			ntv::STREAMING::NEW_LOAD_SCENE_STOP();
			ntv::STREAMING::STOP_PLAYER_SWITCH();
			disable_control(false);
			if (_switch_scene_chr) {
				_switch_scene_chr.del();
			}
		}

		inline void auto_get_parachute_in_plane(bool toggle = true) {
			ntv::PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(0, toggle);
		}

		void invincible(bool toggle = true);

		void full_stats_for_everyone(bool toggle = true);

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

		inline void health_recharge_multiplier(float val) {
			ntv::PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(0, val);
		}

		inline void health_perception_multiplier(float val) {
			ntv::PLAYER::SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(0, val);
		}
	}
}
