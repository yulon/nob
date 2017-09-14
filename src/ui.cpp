#include <nob.hpp>
#include <nob/ntv.hpp>
#include <nob/hack.hpp>

namespace nob {
	namespace ui {
		uintptr_t _dcw_ft;

		void disable_story_features(bool toggle) {
			if (toggle && !has_frame_task(_dcw_ft)) {
				_dcw_ft = add_frame_task([]() {
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::MultiplayerInfo, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::CharacterWheel, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterMichael, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterFranklin, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterTrevor, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SelectCharacterMultiplayer, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::SpecialAbilityPC, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::Phone, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::CinematicSlowMo, true);
					ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::ctrls::VehicleSlowMoUpDown, true);
				});
			} else {
				del_frame_task(_dcw_ft);
			}
		}

		void _wsm_detour() {}

		hack::hook<void> _wsm_hook(&_wsm_detour);

		uintptr_t _wsm_fp = 0;

		void disable_wheel_slowmo(bool toggle) {
			if (!_wsm_fp) {
				_wsm_fp = call_onmt([]()->uintptr_t {
					return hack::mem_match({
						// Reference from https://www.unknowncheats.me/forum/grand-theft-auto-v/181752-weapon-wheel-slowmotion.html
						0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x20,
						0x33, 0xC0, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x83, 0xFA, 0x01,
						0x75, 1111, 0x38, 0x05, 1111, 1111, 1111, 1111, 0x0F, 0x45,
						0xF8
					});
				});
				if (!_wsm_fp) {
					return;
				}
			}
			if (toggle) {
				_wsm_hook.install(_wsm_fp);
			} else {
				_wsm_hook.uninstall();
			}
		}
	} /* ui */
} /* nob */
