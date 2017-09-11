#include <nob.hpp>

namespace nob {
	namespace ui {
		uintptr_t _dcw_ft;

		void disable_story_features(bool toggle) {
			if (toggle && !has_frame_task(_dcw_ft)) {
				_dcw_ft = add_frame_task([]() {
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::MultiplayerInfo, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::CharacterWheel, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterMichael, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterFranklin, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterTrevor, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterMultiplayer, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SpecialAbilityPC, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::Phone, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::CinematicSlowMo, TRUE);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::VehicleSlowMoUpDown, TRUE);
				});
			} else {
				del_frame_task(_dcw_ft);
			}
		}
	} /* ui */
} /* nob */
