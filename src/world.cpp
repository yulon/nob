#include <nob/script.hpp>
#include <nob/ntv.hpp>
#include <nob/object.hpp>

#include <nob/shv/main.hpp>

namespace nob {
	namespace world {
		/*
			Reference from
				http://gtaforums.com/topic/858699-completely-clean-world/
				https://github.com/codecat/quinMP/blob/master/StrawberryPie/Scripts/CleanWorld.cpp
		*/
		void no_mans_island(bool toggle) {
			static task tsk;
			if (toggle) {
				if (!tsk) {
					tsk = task([]() {
						ntv::VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::VEHICLE::_0xD4B8E3D1917BC86B(false);
						ntv::VEHICLE::_SET_SOME_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);

						ntv::PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
						ntv::PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);

						ntv::DECISIONEVENT::SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME();
						ntv::DECISIONEVENT::SUPPRESS_AGITATION_EVENTS_NEXT_FRAME();

						ntv::VEHICLE::DELETE_ALL_TRAINS();
						ntv::PLAYER::SET_MAX_WANTED_LEVEL(0);

						ntv::VEHICLE::SET_GARBAGE_TRUCKS(false);
						ntv::VEHICLE::SET_RANDOM_BOATS(false);
						ntv::VEHICLE::SET_RANDOM_TRAINS(false);

						ntv::VEHICLE::SET_NUMBER_OF_PARKED_VEHICLES(-1);
						ntv::VEHICLE::SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(false);
						ntv::VEHICLE::SET_FAR_DRAW_VEHICLES(false);
						ntv::VEHICLE::_DISPLAY_DISTANT_VEHICLES(false);

						if (ntv::GAMEPLAY::IS_STUNT_JUMP_IN_PROGRESS()) {
							ntv::GAMEPLAY::CANCEL_STUNT_JUMP();
						}

						if (ntv::GAMEPLAY::GET_MISSION_FLAG()) {
							ntv::GAMEPLAY::SET_MISSION_FLAG(false);
						}

						if (ntv::GAMEPLAY::GET_RANDOM_EVENT_FLAG()) {
							ntv::GAMEPLAY::SET_RANDOM_EVENT_FLAG(false);
						}

						if (ntv::CUTSCENE::IS_CUTSCENE_ACTIVE()) {
							ntv::CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
						}

						ntv::AUDIO::_FORCE_AMBIENT_SIREN(false);
						ntv::AUDIO::STOP_ALL_ALARMS(true);
					});

					auto pos = player::body()->pos();
					ntv::GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING(pos.x, pos.y, pos.z, 1000, false, false, false, false);
					ntv::AUDIO::_DISABLE_POLICE_REPORTS();
					ntv::AUDIO::_FORCE_AMBIENT_SIREN(false);
					for (size_t i = 1; i < 16; ++i) {
						ntv::GAMEPLAY::ENABLE_DISPATCH_SERVICE(i, false);
					}
					ntv::PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0);
					ntv::PED::SET_CREATE_RANDOM_COPS(false);

					ntv::AUDIO::SET_AUDIO_FLAG("LoadMPData", true);
					ntv::AUDIO::SET_AUDIO_FLAG("DisableBarks", true);
					ntv::AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", true);
					ntv::AUDIO::SET_AUDIO_FLAG("PoliceScannerDisabled", true);
					ntv::AUDIO::SET_AUDIO_FLAG("OnlyAllowScriptTriggerPoliceScanner", true);

					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_SCRIPT_INCREASE_STL"), 100, 1);
					ntv::STATS::STAT_SET_INT(ntv::GAMEPLAY::GET_HASH_KEY("MP0_NO_MORE_TUTORIALS"), 1, 1);
				}
			} else {
				tsk.del();
			}
		}
	} /* world */
} /* nob */
