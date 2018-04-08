#include <nob/world.hpp>
#include <nob/player.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>
#include <nob/gc.hpp>
#include <nob/log.hpp>

#include <cstring>

namespace nob {
	namespace world {
		// Reference from https://pastebin.com/Tvg2PRHU
		const std::array<const char *, 45> _scenario_groups {{
			"ALAMO_PLANES",
			"ARMENIAN_CATS",
			"ARMY_GUARD",
			"ARMY_HELI",
			"ATTRACT_PAP",
			"BLIMP",
			"CHINESE2_HILLBILLIES",
			"Chinese2_Lunch",
			"Cinema_Downtown",
			"Cinema_Morningwood",
			"Cinema_Textile",
			"City_Banks",
			"Countryside_Banks",
			"DEALERSHIP",
			"FIB_GROUP_1",
			"FIB_GROUP_2",
			"GRAPESEED_PLANES",
			"Grapeseed_Planes",
			"KORTZ_SECURITY",
			"LOST_BIKERS",
			"LOST_BIKERS",
			"LOST_BIKERS",
			"LSA_Planes",
			"MOVIE_STUDIO_SECURITY",
			"MOVIE_STUDIO_SECURITY",
			"MP_POLICE",
			"Observatory_Bikers",
			"POLICE_POUND1",
			"POLICE_POUND2",
			"POLICE_POUND3",
			"POLICE_POUND4",
			"POLICE_POUND5",
			"PRISON_TOWERS",
			"QUARRY",
			"Rampage1",
			"SANDY_PLANES",
			"SCRAP_SECURITY",
			"SEW_MACHINE",
			"SOLOMON_GATE",
			"Triathlon_1",
			"Triathlon_1_Start",
			"Triathlon_2",
			"Triathlon_2_Start",
			"Triathlon_3",
			"Triathlon_3_Start"
		}};

		const std::array<const char *, 28> _scenario_types {{
			"WORLD_MOUNTAIN_LION_REST",
			"WORLD_MOUNTAIN_LION_WANDER",
			"DRIVE",
			"WORLD_VEHICLE_POLICE_BIKE",
			"WORLD_VEHICLE_POLICE_CAR",
			"WORLD_VEHICLE_POLICE_NEXT_TO_CAR",
			"WORLD_VEHICLE_DRIVE_SOLO",
			"WORLD_VEHICLE_BIKER",
			"WORLD_VEHICLE_DRIVE_PASSENGERS",
			"WORLD_VEHICLE_SALTON_DIRT_BIKE",
			"WORLD_VEHICLE_BICYCLE_MOUNTAIN",
			"PROP_HUMAN_SEAT_CHAIR",
			"WORLD_VEHICLE_ATTRACTOR",
			"WORLD_HUMAN_LEANING",
			"WORLD_HUMAN_HANG_OUT_STREET",
			"WORLD_HUMAN_DRINKING",
			"WORLD_HUMAN_SMOKING",
			"WORLD_HUMAN_GUARD_STAND",
			"WORLD_HUMAN_CLIPBOARD",
			"WORLD_HUMAN_HIKER",
			"WORLD_VEHICLE_EMPTY",
			"WORLD_VEHICLE_BIKE_OFF_ROAD_RACE",
			"WORLD_HUMAN_PAPARAZZI",
			"WORLD_VEHICLE_PARK_PERPENDICULAR_NOSE_IN",
			"WORLD_VEHICLE_PARK_PARALLEL",
			"WORLD_VEHICLE_CONSTRUCTION_SOLO",
			"WORLD_VEHICLE_CONSTRUCTION_PASSENGERS",
			"WORLD_VEHICLE_TRUCK_LOGS"
		}};

		/*
			Reference from
				http://gtaforums.com/topic/858699-completely-clean-world/
				https://github.com/codecat/quinMP/blob/master/StrawberryPie/Scripts/CleanWorld.cpp
		*/
		void no_mans_island(bool toggle) {
			static task tsk;

			static initer reset([]() {
				if (tsk) {
					tsk.del();
				}
			});

			struct gc_id_t {
				static constexpr bool native_handle() {
					return true;
				}
			};

			if (toggle) {
				if (tsk) {
					return;
				}

				tsk = task([]() {
					ntv::VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
					ntv::VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
					ntv::VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
					ntv::VEHICLE::_SET_SOMETHING_MULTIPLIER_THIS_FRAME(false);
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

					ntv::AUDIO::_FORCE_AMBIENT_SIREN(false);
					ntv::AUDIO::STOP_ALL_ALARMS(true);
				});

				auto pos = player::body().pos();

				ntv::GAMEPLAY::_CLEAR_AREA_OF_EVERYTHING(pos.x, pos.y, pos.z, 1000, false, false, false, false);

				ntv::AUDIO::_DISABLE_POLICE_REPORTS();

				for (size_t i = 1; i < 16; ++i) {
					ntv::GAMEPLAY::ENABLE_DISPATCH_SERVICE(i, false);
				}

				ntv::PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0f);

				ntv::PED::SET_CREATE_RANDOM_COPS(false);

				ntv::AUDIO::SET_AUDIO_FLAG("LoadMPData", true);
				ntv::AUDIO::SET_AUDIO_FLAG("DisableBarks", true);
				ntv::AUDIO::SET_AUDIO_FLAG("DisableFlightMusic", true);
				ntv::AUDIO::SET_AUDIO_FLAG("PoliceScannerDisabled", true);
				ntv::AUDIO::SET_AUDIO_FLAG("OnlyAllowScriptTriggerPoliceScanner", true);

				for (auto sg : _scenario_groups) {
					ntv::AI::SET_SCENARIO_GROUP_ENABLED(sg, false);
				}

				if (!gc::is_delegated(gc_id_t())) {
					auto h = ntv::PED::ADD_SCENARIO_BLOCKING_AREA(-7000.0f, -7000.0f, -100.0f, 7000.0f, 7000.0f, 315.0f, 0, 1, 1, 1);
					gc::delegate(gc_id_t(), [h]() {
						ntv::PED::REMOVE_SCENARIO_BLOCKING_AREA(h, 0);
					});
				}

				for (auto st : _scenario_types) {
					ntv::AI::SET_SCENARIO_TYPE_ENABLED(st, false);
				}

			} else {
				tsk.del();
				gc::free(gc_id_t());
			}
		}

		void disable_ambient_missions(bool toggle) {
			static task tsk;

			static initer reset([]() {
				if (tsk) {
					tsk.del();
				}
			});

			if (toggle) {
				if (!tsk) {
					return;
				}
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
			} else {
				tsk.del();
			}
		}

		const std::array<door_info_t, 487> doors {{
			#include "world/doors.inc"
		}};

		vector3 load_ilp(ilp i, bool toggle) {
			switch (i) {
				case ilp::bahama_mamas:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1388.0013427734375f, -618.419677734375f, 30.819599151611328f), false);
						ntv::STREAMING::REQUEST_IPL("v_bahama");
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1388.0013427734375f, -618.419677734375f, 30.819599151611328f), true);
						ntv::STREAMING::REMOVE_IPL("v_bahama");
					}
					return {-1388.0013427734375, -618.419677734375, 30.819599151611328};

				case ilp::chopshop: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(479.0567932128906f, -1316.8253173828125f, 28.2038f);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_chopshop");
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						//ntv::OBJECT::_DOOR_CONTROL(-664582244, 482.8112f, -1311.953f, 29.35057f, true, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-190780785, 484.5652f, -1315.574f, 30.20331f, true, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_chopshop");
					}
					return {484.5652f, -1315.574f, 30.20331f};
				}

				case ilp::cluckin_bell:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission1");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission2");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission3");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_onmission4");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_offmission");
					} else {
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission1");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission2");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission3");
						ntv::STREAMING::REMOVE_IPL("CS1_02_cf_onmission4");
						ntv::STREAMING::REQUEST_IPL("CS1_02_cf_offmission");
					}
					return {0, 0, 0};

				case ilp::comedy_club:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-447.4833068847656f, 280.3197021484375f, 77.52149963378906f), false);
						ntv::STREAMING::REQUEST_IPL("v_comedy");
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-447.4833068847656f, 280.3197021484375f, 77.52149963378906f), true);
						ntv::STREAMING::REMOVE_IPL("v_comedy");
					}
					return {-447.4833068847656f, 280.3197021484375f, 77.52149963378906f};

				case ilp::fame_or_shame_stadium:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("sp1_10_fake_interior");
						ntv::STREAMING::REMOVE_IPL("sp1_10_fake_interior_lod");
						ntv::STREAMING::REQUEST_IPL("sp1_10_real_interior");
						ntv::STREAMING::REQUEST_IPL("sp1_10_real_interior_lod");
					} else {
						ntv::STREAMING::REMOVE_IPL("sp1_10_real_interior");
						ntv::STREAMING::REMOVE_IPL("sp1_10_real_interior_lod");
						ntv::STREAMING::REQUEST_IPL("sp1_10_fake_interior");
						ntv::STREAMING::REQUEST_IPL("sp1_10_fake_interior_lod");
					}
					return {0, 0, 0};

				case ilp::fib_lobby:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("FIBlobby");
						ntv::STREAMING::REMOVE_IPL("FIBlobbyfake");
						//ntv::OBJECT::_DOOR_CONTROL(-1517873911, 106.3793f, -742.6982f, 46.51962f, false, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-90456267, 105.7607f, -746.646f, 46.18266f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::STREAMING::REQUEST_IPL("FIBlobbyfake");
						ntv::STREAMING::REMOVE_IPL("FIBlobby");
						//ntv::OBJECT::_DOOR_CONTROL(-1517873911, 106.3793f, -742.6982f, 46.51962f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-90456267, 105.7607f, -746.646f, 46.18266f, true, 0.0f, 0.0f, 0.0f);
					}
					return {105.7607f, -746.646f, 46.18266f};

				case ilp::foundry: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1087.1951904296875f, -1988.4449462890625f, 28.649f);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_foundry");
						//ntv::OBJECT::_DOOR_CONTROL(-1428622127, 1083.547f, -1975.435f, 31.62222f, true, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1428622127, 1085.307f, -2018.561f, 41.62894f, true, 0.0f, 0.0f, 1.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_foundry");
					}
					return {1085.307f, -2018.561f, 41.62894f};
				}

				case ilp::floyds_house:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("vb_30_crimetape");
						//ntv::OBJECT::_DOOR_CONTROL(-607040053, -1149.709f, -1521.088f, 10.78267f, false, 0.0f, 0.0f, 0.0f);
					}
					return {-1149.709f, -1521.088f, 10.78267f};

				case ilp::epsilon: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(245.15640258789062f, 370.21099853515625f, 104.73819732666016f);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_epsilonism");
						//ntv::OBJECT::_DOOR_CONTROL(-1230442770, 241.3621f, 361.0471f, 105.8883f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_epsilonism");
						//ntv::OBJECT::_DOOR_CONTROL(-1230442770, 241.3621f, 361.0471f, 105.8883f, true, 0.0f, 0.0f, 0.0f);
					}
					return {241.3621f, 361.0471f, 105.8883f};
				}

				case ilp::hospital_normal:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("RC12B_Destroyed");
						ntv::STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
						ntv::STREAMING::REMOVE_IPL("RC12B_Default");
						ntv::STREAMING::REMOVE_IPL("RC12B_Fixed");
						ntv::STREAMING::REQUEST_IPL("RC12B_Default");//state 1 normal
					}
					return {0, 0, 0};

				case ilp::hospital_destroyed:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("RC12B_Destroyed");
						ntv::STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
						ntv::STREAMING::REMOVE_IPL("RC12B_Default");
						ntv::STREAMING::REMOVE_IPL("RC12B_Fixed");
						ntv::STREAMING::REQUEST_IPL("RC12B_Destroyed");//state 3 1of2
						ntv::STREAMING::REQUEST_IPL("RC12B_HospitalInterior");//state 3 2of2 Destroyed Interior
					}
					return {0, 0, 0};

				case ilp::hospital_boarded_up:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("RC12B_Destroyed");
						ntv::STREAMING::REMOVE_IPL("RC12B_HospitalInterior");
						ntv::STREAMING::REMOVE_IPL("RC12B_Default");
						ntv::STREAMING::REMOVE_IPL("RC12B_Fixed");
						ntv::STREAMING::REQUEST_IPL("RC12B_Fixed");//state 2 boarded up
					}
					return {0, 0, 0};

				case ilp::janitor:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("v_janitor");
						//ntv::OBJECT::_DOOR_CONTROL(486670049, -107.5373f, -9.018099f, 70.67085f, false, 0.0f, 0.0f, 0.0f);
					}
					return {-107.5373f, -9.018099f, 70.67085f};

				case ilp::jewel_store:
					if (toggle) {
						auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-630.4f, -236.7f, 40.0f);
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("post_hiest_unload");
						ntv::STREAMING::REMOVE_IPL("jewel2fake");
						ntv::STREAMING::REMOVE_IPL("bh1_16_refurb");
						//ntv::OBJECT::_DOOR_CONTROL(9467943, -630.4265f, -238.4375f, 38.20653f, true, 0.0f, 0.0f, 1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1425919976, -631.9554f, -236.3333f, 38.20653f, true, 0.0f, 0.0f, -1.0f);
					}
					return {-631.9554f, -236.3333f, 38.20653f};

				case ilp::lab:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(3522.84521484375f, 3707.96533203125f, 19.9918f), false);
						ntv::STREAMING::REQUEST_IPL("v_lab");
						//ntv::OBJECT::_DOOR_CONTROL(-1081024910, 3620.843f, 3751.527f, 27.69009f, false, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1081024910, 3627.713f, 3746.716f, 27.69009f, false, 0.0f, 0.0f, -1.0f);
						//elevator coords 3540.65f, 3675.77f, 28.12f
						//elevator2 coords 3540.65f, 3675.77f, 20.12f
					}
					return {3627.713f, 3746.716f, 27.69009f};

				case ilp::life_invader:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("facelobby");  // lifeinvader
						ntv::STREAMING::REMOVE_IPL("facelobbyfake");
						//ntv::OBJECT::_DOOR_CONTROL(-340230128, -1042.518, -240.6915, 38.11796, true, 0.0f, 0.0f, -1.0f);
					} else {
						ntv::STREAMING::REMOVE_IPL("facelobby");  // lifeinvader
						ntv::STREAMING::REQUEST_IPL("facelobbyfake");
						//ntv::OBJECT::_DOOR_CONTROL(-340230128, -1042.518, -240.6915, 38.11796, true, 0.0f, 0.0f, 0.0f);
					}
					return {-1042.518f, -240.6915f, 38.11796f};

				case ilp::Lesters_house:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1274.933837890625f, -1714.7255859375f, 53.77149963378906f), false);
						ntv::STREAMING::REQUEST_IPL("v_lesters");
						//ntv::OBJECT::_DOOR_CONTROL(1145337974, 1273.816f, -1720.697f, 54.92143f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1274.933837890625f, -1714.7255859375f, 53.77149963378906f), false);
						ntv::STREAMING::REMOVE_IPL("v_lesters");
						//ntv::OBJECT::_DOOR_CONTROL(1145337974, 1273.816f, -1720.697f, 54.92143f, true, 0.0f, 0.0f, 0.0f);
					}
					return {1273.816f, -1720.697f, 54.92143f};

				case ilp::lesters_factory:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REMOVE_IPL("id2_14_during1");
						ntv::STREAMING::REMOVE_IPL("id2_14_during2");
						ntv::STREAMING::REMOVE_IPL("id2_14_on_fire");
						ntv::STREAMING::REMOVE_IPL("id2_14_post_no_int");
						ntv::STREAMING::REMOVE_IPL("id2_14_pre_no_int");
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REQUEST_IPL("id2_14_during1");
						//ntv::OBJECT::_DOOR_CONTROL(826072862, 717.0f, -975.0f, 25.0f, false, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(763780711, 719.0f, -975.0f, 25.0f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REMOVE_IPL("id2_14_during1");
						ntv::STREAMING::REMOVE_IPL("id2_14_during2");
						ntv::STREAMING::REMOVE_IPL("id2_14_on_fire");
						ntv::STREAMING::REMOVE_IPL("id2_14_post_no_int");
						ntv::STREAMING::REMOVE_IPL("id2_14_during_door");
						ntv::STREAMING::REQUEST_IPL("id2_14_post_no_int");
					}
					return {719.0f, -975.0f, 25.0f};

				case ilp::morgue:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-447.4833068847656f, 280.3197021484375f, 77.52149963378906f), false);
						ntv::STREAMING::REQUEST_IPL("Coroner_Int_on");
						ntv::STREAMING::REMOVE_IPL("Coroner_Int_off");
						//teleport coords 275.1f,  -1360.6f,  24.5f
						//teleport2 coords 240.8f, -1379.5f, 33.74f
					}
					return {-447.4833068847656f, 280.3197021484375f, 77.52149963378906f};

				case ilp::o_neil_ranch:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("farm_burnt");
						ntv::STREAMING::REMOVE_IPL("farm_burnt_lod");
						ntv::STREAMING::REMOVE_IPL("farm_burnt_props");
						ntv::STREAMING::REMOVE_IPL("farmint_cap");
						ntv::STREAMING::REMOVE_IPL("farmint_cap_lod");
						ntv::STREAMING::REQUEST_IPL("farm");
						ntv::STREAMING::REQUEST_IPL("farmint");
						ntv::STREAMING::REQUEST_IPL("farm_lod");
						ntv::STREAMING::REQUEST_IPL("farm_props");
					} else {
						ntv::STREAMING::REMOVE_IPL("farm");
						ntv::STREAMING::REMOVE_IPL("farmint");
						ntv::STREAMING::REMOVE_IPL("farm_lod");
						ntv::STREAMING::REMOVE_IPL("farm_props");
						ntv::STREAMING::REQUEST_IPL("farm_burnt");
						ntv::STREAMING::REQUEST_IPL("farm_burnt_lod");
						ntv::STREAMING::REQUEST_IPL("farm_burnt_props");
						ntv::STREAMING::REQUEST_IPL("farmint_cap");
						ntv::STREAMING::REQUEST_IPL("farmint_cap_lod");
					}
					return {0, 0, 0};

				case ilp::psycheoffice:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1906.7857666015625f, -573.7576293945312f, 19.077299118041992f), false);
						ntv::STREAMING::REQUEST_IPL("v_psycheoffice");
					}
					return {-1906.7857666015625f, -573.7576293945312f, 19.077299118041992f};

				case ilp::ranch: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1399.9730224609375f, 1148.755859375f, 113.33360290527344f);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::INTERIOR::_LOAD_INTERIOR(intr);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						////ntv::OBJECT::_DOOR_CONTROL(1504256620, 1395.92f, 1142.904f, 114.7902f, true, 0.0f, 0.0f, 1.0f);
						////ntv::OBJECT::_DOOR_CONTROL(-52575179, 1390.666f, 1133.317f, 114.4808f, true, 0.0f, 0.0f, -1.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
					}
					return {1399.9730224609375, 1148.755859375, 113.33360290527344};
				}

				case ilp::rogers_salvage_and_scrap: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-598.6378784179688f, -1608.3985595703125f, 26.010799407958984f);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_recycle");
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -608.7289f, -1610.315f, 27.15894f, false, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -611.32f, -1610.089f, 27.15894f, false, 0.0f, 0.0f, 1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -592.9376f, -1631.577f, 27.15931f, false, 0.0f, 0.0f, -1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -592.7109f, -1628.986f, 27.15931f, false, 0.0f, 0.0f, 1.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_recycle");
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -608.7289f, -1610.315f, 27.15894f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -611.32f, -1610.089f, 27.15894f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1099436502, -592.9376f, -1631.577f, 27.15931f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1627599682, -592.7109f, -1628.986f, 27.15931f, true, 0.0f, 0.0f, 0.0f);
					}
					return {-592.7109f, -1628.986f, 27.15931f};
				}

				case ilp::sheriff_office_paleto:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-444.89068603515625f, 6013.5869140625f, 30.7164f), false);
						ntv::INTERIOR::CAP_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-444.89068603515625f, 6013.5869140625f, 30.7164f), false);
						ntv::STREAMING::REQUEST_IPL("v_sheriff2");
						ntv::STREAMING::REMOVE_IPL("cs1_16_sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -444.4985f, 6017.06f, 31.86633f, false, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -442.66f, 6015.222f, 31.86633f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-444.89068603515625f, 6013.5869140625f, 30.7164f), true);
						ntv::STREAMING::REMOVE_IPL("v_sheriff2");
						ntv::STREAMING::REQUEST_IPL("cs1_16_sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -444.4985f, 6017.06f, 31.86633f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(-1501157055, -442.66f, 6015.222f, 31.86633f, true, 0.0f, 0.0f, 0.0f);
					}
					return {-442.66f, 6015.222f, 31.86633f};

				case ilp::sheriff_office_sandy_shores: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1854.2537841796875f, 3686.738525390625f, 33.2671012878418f);
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_sheriff");
						ntv::STREAMING::REMOVE_IPL("sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1765048490, 1855.685f, 3683.93f, 34.59282f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_sheriff");
						ntv::STREAMING::REQUEST_IPL("sheriff_cap");
						//ntv::OBJECT::_DOOR_CONTROL(-1765048490, 1855.685f, 3683.93f, 34.59282f, true, 0.0f, 0.0f, 0.0f);
					}
					return {1855.685f, 3683.93f, 34.59282f};
				}

				case ilp::simeons_showroom:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("v_carshowroom");
						ntv::STREAMING::REMOVE_IPL("shutter_open");
						ntv::STREAMING::REMOVE_IPL("shutter_closed");
						ntv::STREAMING::REMOVE_IPL("shr_int");
						ntv::STREAMING::REMOVE_IPL("csr_inMission");
						ntv::STREAMING::REMOVE_IPL("fakeint");
						ntv::STREAMING::REQUEST_IPL("shr_int");
					} else {
						ntv::STREAMING::REMOVE_IPL("v_carshowroom");
						ntv::STREAMING::REMOVE_IPL("shutter_open");
						ntv::STREAMING::REMOVE_IPL("shutter_closed");
						ntv::STREAMING::REMOVE_IPL("shr_int");
						ntv::STREAMING::REMOVE_IPL("csr_inMission");
						ntv::STREAMING::REMOVE_IPL("fakeint");
						ntv::STREAMING::REQUEST_IPL("fakeint");
					}
					return {0.f, 0.f, 0.f};

				case ilp::slaughter_house: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(982.2329711914062f, -2160.381591796875f, 28.4761f);
					if (toggle) {
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_abattoir");
						//ntv::OBJECT::_DOOR_CONTROL(-1468417022, 962.9084f, -2105.813f, 32.52716f, true, 0.0f, 0.0f, 1.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1755793225, 962.0066f, -2183.816f, 31.06194f, true, 0.0f, 0.0f, 1.0f);
						ntv::INTERIOR::UNPIN_INTERIOR(intr);
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						//ntv::OBJECT::_DOOR_CONTROL(-1468417022, 962.9084f, -2105.813f, 32.52716f, true, 0.0f, 0.0f, 0.0f);
						//ntv::OBJECT::_DOOR_CONTROL(1755793225, 962.0066f, -2183.816f, 31.06194f, true, 0.0f, 0.0f, 0.0f);
						ntv::STREAMING::REMOVE_IPL("v_abattoir");
					}
					return {962.0066f, -2183.816f, 31.06194f};
				}

				case ilp::solomons_office:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-1005.663208f, -478.3460998535156f, 49.0265f), false);
						ntv::STREAMING::REQUEST_IPL("v_58_sol_office");
					}
					return {-1005.663208f, -478.3460998535156f, 49.0265f};

				case ilp::stab_city:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REMOVE_IPL("des_methtrailer");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp1");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp2");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp3");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkA_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkB_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkC_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkD_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkE_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REQUEST_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("methtrailer_grp1");
					}
					return {0, 0, 0};

				case ilp::stab_city_burnt:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REMOVE_IPL("des_methtrailer");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp1");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp2");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp3");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkA_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkB_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkC_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkD_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkE_grp2");
						ntv::STREAMING::REQUEST_IPL("des_methtrailer");
						ntv::STREAMING::REQUEST_IPL("methtrailer_grp3");
					}
					return {0, 0, 0};

				case ilp::stab_city_on_fire:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkA_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerA_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkB_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerB_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkC_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerC_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkD_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerD_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp1");
						ntv::STREAMING::REMOVE_IPL("trailerparkE_grp2");
						ntv::STREAMING::REMOVE_IPL("occl_trailerE_grp1");
						ntv::STREAMING::REMOVE_IPL("des_methtrailer");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp1");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp2");
						ntv::STREAMING::REMOVE_IPL("methtrailer_grp3");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REMOVE_IPL("occl_meth_grp1");
						ntv::STREAMING::REQUEST_IPL("trailerparkA_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkB_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkC_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkD_grp2");
						ntv::STREAMING::REQUEST_IPL("trailerparkE_grp2");
						ntv::STREAMING::REQUEST_IPL("des_methtrailer");
						ntv::STREAMING::REQUEST_IPL("methtrailer_grp2");
					}
					return {0, 0, 0};

				case ilp::trevors_trailer:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("TrevorsTrailerTrash");
						ntv::STREAMING::REMOVE_IPL("TrevorsTrailerTidy");
						ntv::STREAMING::REMOVE_IPL("TrevorsTrailer");
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(1973.0f, 3815.0f, 34.0f), false);
						ntv::STREAMING::REQUEST_IPL("TrevorsTrailerTidy");
						//ntv::OBJECT::_DOOR_CONTROL(132154435, 1972.769f, 3815.366f, 33.66326f, false, 0.0f, 0.0f, 0.0f);
					}
					return {1972.769f, 3815.366f, 33.66326f};

				case ilp::tequl_la_la: {
					auto intr = ntv::INTERIOR::GET_INTERIOR_AT_COORDS(-556.5089111328125f, 286.318115234375f, 81.1763f);
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(intr, false);
						ntv::INTERIOR::CAP_INTERIOR(intr, false);
						ntv::STREAMING::REQUEST_IPL("v_rockclub");
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -565.1712f, 276.6259f, 83.28626f, false, 0.0f, 0.0f, 0.0f);// front door
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -561.2866f, 293.5044f, 87.77851f, false, 0.0f, 0.0f, 0.0f);// back door
					} else {
						ntv::INTERIOR::CAP_INTERIOR(intr, true);
						ntv::STREAMING::REMOVE_IPL("v_rockclub");
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -565.1712f, 276.6259f, 83.28626f, true, 0.0f, 0.0f, 0.0f);// front door
						//ntv::OBJECT::_DOOR_CONTROL(993120320, -561.2866f, 293.5044f, 87.77851f, true, 0.0f, 0.0f, 0.0f);// back door
					}
					return {-561.2866f, 293.5044f, 87.77851f};
				}

				case ilp::torture:
					if (toggle) {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(147.43299865722656f, -2201.370361328125f, 3.688f), false);
						ntv::STREAMING::REQUEST_IPL("v_torture");
						//ntv::OBJECT::_DOOR_CONTROL(464151082, 134.3954f, -2204.097f, 7.514325f, false, 0.0f, 0.0f, 0.0f);
					} else {
						ntv::INTERIOR::DISABLE_INTERIOR(ntv::INTERIOR::GET_INTERIOR_AT_COORDS(147.43299865722656f, -2201.370361328125f, 3.688f), false);
						ntv::STREAMING::REMOVE_IPL("v_torture");
						//ntv::OBJECT::_DOOR_CONTROL(464151082, 134.3954f, -2204.097f, 7.514325f, true, 0.0f, 0.0f, 0.0f);
					}
					return {134.3954f, -2204.097f, 7.514325f};

				case ilp::mp_lost_safe_house:
					if (toggle) {
						ntv::STREAMING::REMOVE_IPL("hei_bi_hw1_13_door");
						ntv::STREAMING::REQUEST_IPL("bkr_bi_hw1_13_int");
					}
					return {984.1552f, -95.3662f, 75.9326f};

				case ilp::mp_yacht:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Bar");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Bedrm");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Bridge");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_DistantLights");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_enginrm");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_LODLights");
						ntv::STREAMING::REQUEST_IPL("hei_yacht_heist_Lounge");
						ntv::AUDIO::SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT("AZL_HEI_AIRCRAFT_CARRIER", true, true);
					}
					return {-2062.79f, -1025.98f, 3.06146f};

				case ilp::mp_heist_carrier:
					if (toggle) {
						ntv::STREAMING::REQUEST_IPL("hei_carrier");
						ntv::STREAMING::REQUEST_IPL("hei_carrier_DistantLights");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int1");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int2");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int3");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int4");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int5");
						ntv::STREAMING::REQUEST_IPL("hei_Carrier_int6");
						ntv::STREAMING::REQUEST_IPL("hei_carrier_LODLights");
						ntv::AUDIO::SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT("AZL_DLC_HEI_MILO_YACHT_ZONES", true, true);
					}
					return {3068.94f, -4721.21f, 15.2614f};
			}
			return {0.0f, 0.0f, 0.0f};
		}

		void snowy(bool toggle) {
			static uint8_t block_code_bak[20];

			static uint8_t *block_code_addr = ([]()->uint8_t *{
				chan<uint8_t *> ch;

				std::thread([ch]() mutable {
					auto mpos = game_code.match({
						// Reference from http://gtaforums.com/topic/902339-enable-snowy-map-in-single-player/
						0x74, 0x25, 0xB9, 0x40, 0x00, 0x00, 0x00, 0xE8, 1111, 1111, 1111, 1111, 0x84, 0xC0
					});

					if (mpos == rua::nullpos) {
						log("nob::world::snowy::block_code_addr: not found!");
						ch << nullptr;
					}

					auto bca = game_code.base() + mpos;
					VirtualProtect(bca, 20, PAGE_EXECUTE_READWRITE, nullptr);
					memcpy(&block_code_bak, bca, 20);
					ch << bca;

				}).detach();

				return ch.get();
			})();

			static initer reset([]() {
				if (block_code_addr && *block_code_addr == 0x90) {
					memcpy(block_code_addr, &block_code_bak, 20);
				}
			});

			struct gc_id_t {
				static constexpr bool native_handle() {
					return true;
				}
			};

			if (toggle) {
				if (!block_code_addr) {
					return;
				}

				if (*block_code_addr == 0x74) {
					memset(block_code_addr, 0x90, 20);
				}

				ntv::GRAPHICS::_SET_FORCE_PED_FOOTSTEPS_TRACKS(true);
				ntv::GRAPHICS::_SET_FORCE_VEHICLE_TRAILS(true);

				ntv::STREAMING::REQUEST_NAMED_PTFX_ASSET("core_snow");
				while (!ntv::STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core_snow")) {
					yield();
				}
				ntv::GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("core_snow");

				ntv::AUDIO::REQUEST_SCRIPT_AUDIO_BANK("ICE_FOOTSTEPS", true);
				ntv::AUDIO::REQUEST_SCRIPT_AUDIO_BANK("SNOW_FOOTSTEPS", true);

				gc::delegate(gc_id_t(), []() {
					if (*block_code_addr == 0x90) {
						memcpy(block_code_addr, &block_code_bak, 20);
					}

					ntv::GRAPHICS::_SET_FORCE_PED_FOOTSTEPS_TRACKS(false);
					ntv::GRAPHICS::_SET_FORCE_VEHICLE_TRAILS(false);

					if (ntv::STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core_snow")) {
						ntv::STREAMING::_REMOVE_NAMED_PTFX_ASSET("core_snow");
					}

					ntv::AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("ICE_FOOTSTEPS");
					ntv::AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK("SNOW_FOOTSTEPS");
				});

			} else if (block_code_addr) {
				gc::free(gc_id_t());
			}
		}

		namespace pickup {
			const std::array<info_t, 76> healths {{
				#include "world/pickup/healths.inc"
			}};

			const std::array<info_t, 19> armours {{
				#include "world/pickup/armours.inc"
			}};

			const std::array<info_t, 45> petrolcans {{
				#include "world/pickup/petrolcans.inc"
			}};
		}
	} /* world */
} /* nob */
