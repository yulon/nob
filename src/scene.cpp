#include <nob/ntv.hpp>
#include <nob/script.hpp>

namespace nob {
	namespace scene {
		void like_mp(bool toggle) {
			static task tsk;

			if (toggle) {
				if (!tsk) {
					// Reference from https://github.com/codecat/quinMP/blob/master/StrawberryPie/Scripts/CleanWorld.cpp

					tsk = task([]() {
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
					});

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
	}
}
