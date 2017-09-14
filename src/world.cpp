#include <nob.hpp>
#include <nob/shv/main.hpp>

namespace nob {
	namespace world {
		uintptr_t _no_man_ft;

		void no_man(bool toggle) {
			if (toggle) {
				if (!has_frame_task(_no_man_ft)) {
					_no_man_ft = add_frame_task([]() {
						ntv::VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);
						ntv::VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);
						ntv::VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);
						ntv::VEHICLE::_0xD4B8E3D1917BC86B(false);
						ntv::VEHICLE::_SET_SOME_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0);
	
						ntv::PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0);
						ntv::PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0, 0);
	
						ntv::DECISIONEVENT::SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME();
						ntv::DECISIONEVENT::SUPPRESS_AGITATION_EVENTS_NEXT_FRAME();
	
						ntv::VEHICLE::DELETE_ALL_TRAINS();
						ntv::PLAYER::SET_MAX_WANTED_LEVEL(0);
	
						ntv::VEHICLE::SET_GARBAGE_TRUCKS(false);
						ntv::VEHICLE::SET_RANDOM_BOATS(false);
						ntv::VEHICLE::SET_RANDOM_TRAINS(false);

						int a[10];
						int c = shv::worldGetAllPeds(a, 10);
						for (int i = 0; i < c; ++i) {
							ntv::PED::DELETE_PED((ntv::Ped *)&a[i]);
						}
					});
					auto pos = player::controlling().pos();
					ntv::GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING(pos.x, pos.y, pos.z, 1000, false, false, false, false);
					ntv::AUDIO::_DISABLE_POLICE_REPORTS();
					ntv::AUDIO::_FORCE_AMBIENT_SIREN(false);
					for (size_t i = 1; i < 16; ++i) {
						ntv::GAMEPLAY::ENABLE_DISPATCH_SERVICE(i, false);
					}
					ntv::PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0);
					ntv::PED::SET_CREATE_RANDOM_COPS(false);
				}
			} else {
				del_frame_task(_no_man_ft);
			}
		}
	} /* world */
} /* nob */
