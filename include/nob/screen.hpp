#pragma once

#include "ntv.hpp"
#include "vector.hpp"
#include "entity.hpp"
#include "player.hpp"

#include <array>
#include <utility>

namespace nob {
	namespace screen {
		inline vector2_i resolution() {
			vector2_i v2;
			ntv::GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&v2.x, &v2.y);
			return v2;
		}

		inline void night_vision(bool toggle = true) {
			ntv::GRAPHICS::SET_NIGHTVISION(toggle);
		}

		inline bool is_night_vision_active() {
			return ntv::GRAPHICS::_IS_NIGHTVISION_ACTIVE();
		}

		inline void thermal_vision(bool toggle = true) {
			ntv::GRAPHICS::SET_SEETHROUGH(toggle);
		}

		inline bool is_thermal_vision_active() {
			return ntv::GRAPHICS::_IS_SEETHROUGH_ACTIVE();
		}

		static constexpr std::array<const char *, 83> filters {{
			"SwitchHUDIn",
			"SwitchHUDOut",
			"FocusIn",
			"FocusOut",
			"MinigameEndNeutral",
			"MinigameEndTrevor",
			"MinigameEndFranklin",
			"MinigameEndMichael",
			"MinigameTransitionOut",
			"MinigameTransitionIn",
			"SwitchShortNeutralIn",
			"SwitchShortFranklinIn",
			"SwitchShortTrevorIn",
			"SwitchShortMichaelIn",
			"SwitchOpenMichaelIn",
			"SwitchOpenFranklinIn",
			"SwitchOpenTrevorIn",
			"SwitchHUDMichaelOut",
			"SwitchHUDFranklinOut",
			"SwitchHUDTrevorOut",
			"SwitchShortFranklinMid",
			"SwitchShortMichaelMid",
			"SwitchShortTrevorMid",
			"DeathFailOut",
			"CamPushInNeutral",
			"CamPushInFranklin",
			"CamPushInMichael",
			"CamPushInTrevor",
			"SwitchOpenMichaelIn",
			"SwitchSceneFranklin",
			"SwitchSceneTrevor",
			"SwitchSceneMichael",
			"SwitchSceneNeutral",
			"MP_Celeb_Win",
			"MP_Celeb_Win_Out",
			"MP_Celeb_Lose",
			"MP_Celeb_Lose_Out",
			"DeathFailNeutralIn",
			"DeathFailMPDark",
			"DeathFailMPIn",
			"MP_Celeb_Preload_Fade",
			"PeyoteEndOut",
			"PeyoteEndIn",
			"PeyoteIn",
			"PeyoteOut",
			"MP_race_crash",
			"SuccessFranklin",
			"SuccessTrevor",
			"SuccessMichael",
			"DrugsMichaelAliensFightIn",
			"DrugsMichaelAliensFight",
			"DrugsMichaelAliensFightOut",
			"DrugsTrevorClownsFightIn",
			"DrugsTrevorClownsFight",
			"DrugsTrevorClownsFightOut",
			"HeistCelebPass",
			"HeistCelebPassBW",
			"HeistCelebEnd",
			"HeistCelebToast",
			"MenuMGHeistIn",
			"MenuMGTournamentIn",
			"MenuMGSelectionIn",
			"ChopVision",
			"DMT_flight_intro",
			"DMT_flight",
			"DrugsDrivingIn",
			"DrugsDrivingOut",
			"SwitchOpenNeutralFIB5",
			"HeistLocate",
			"MP_job_load",
			"RaceTurbo",
			"MP_intro_logo",
			"HeistTripSkipFade",
			"MenuMGHeistOut",
			"MP_corona_switch",
			"MenuMGSelectionTint",
			"SuccessNeutral",
			"ExplosionJosh3",
			"SniperOverlay",
			"RampageOut",
			"Rampage",
			"Dont_tazeme_bro",
			"DeathFailOut"
		}};

		inline void filter(const char *name, bool toggle = true) {
			if (toggle) {
				ntv::GRAPHICS::_START_SCREEN_EFFECT(name, 0, false);
			} else {
				ntv::GRAPHICS::_STOP_SCREEN_EFFECT(name);
			}
		}

		inline bool is_filter_active(const char *name) {
			return ntv::GRAPHICS::_GET_SCREEN_EFFECT_IS_ACTIVE(name);
		}

		inline void stop_all_filters() {
			ntv::GRAPHICS::_STOP_ALL_SCREEN_EFFECTS();
		}

		inline vector3 center_point_world_pos(float distance = 500.0f) {
			return vector3(ntv::CAM::GET_GAMEPLAY_CAM_COORD()) + distance * vector3(ntv::CAM::GET_GAMEPLAY_CAM_ROT(0)).rotation_to_direction();
		}

		inline std::pair<vector3, entity> center_point_world_collided_pos() {
			vector3 cam_pos = ntv::CAM::GET_GAMEPLAY_CAM_COORD();
			vector3 fwd = cam_pos + 500.0f * vector3(ntv::CAM::GET_GAMEPLAY_CAM_ROT(0)).rotation_to_direction();
			auto ray = ntv::WORLDPROBE::_START_SHAPE_TEST_RAY(cam_pos.x, cam_pos.y, cam_pos.z, fwd.x, fwd.y, fwd.z, -1, player::body(), 7);
			bool hit;
			ntv::Vector3 pos;
			ntv::Vector3 surface_normal;
			ntv::Entity ety = 0;
			ntv::WORLDPROBE::GET_SHAPE_TEST_RESULT(ray, &hit, &pos, &surface_normal, &ety);
			return {pos, ety};
		}

		inline vector2 coords_from_world_pos(const vector3 &wp) {
			vector2 sc;
			ntv::GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(wp.x, wp.y, wp.z, &sc.x, &sc.y);
			return sc;
		}
	} /* screen */
} /* nob */
