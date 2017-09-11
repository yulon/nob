#include <nob.hpp>

namespace nob {
	namespace world {
		uintptr_t _no_man_ft;

		void no_man(bool toggle) {
			if (toggle && !has_frame_task(_no_man_ft)) {
				_no_man_ft = add_frame_task([]() {
					ntv::VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);
					ntv::VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);
					ntv::VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);
					ntv::VEHICLE::_0xD4B8E3D1917BC86B(0);
					ntv::VEHICLE::_SET_SOME_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);

					ntv::PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0);
					ntv::PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0, 0);

					ntv::DECISIONEVENT::SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME();
					ntv::DECISIONEVENT::SUPPRESS_AGITATION_EVENTS_NEXT_FRAME();

					ntv::VEHICLE::DELETE_ALL_TRAINS();
					ntv::PLAYER::SET_MAX_WANTED_LEVEL(0);

					ntv::VEHICLE::SET_GARBAGE_TRUCKS(FALSE);
					ntv::VEHICLE::SET_RANDOM_BOATS(FALSE);
					ntv::VEHICLE::SET_RANDOM_TRAINS(FALSE);
				});
				auto pos = player::controlling().pos();
				ntv::GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING(pos.x, pos.y, pos.z, 1000, FALSE, FALSE, FALSE, FALSE);
				ntv::AUDIO::_DISABLE_POLICE_REPORTS();
				ntv::AUDIO::_FORCE_AMBIENT_SIREN(FALSE);
			} else {
				del_frame_task(_no_man_ft);
			}
		}
	} /* world */
} /* nob */
