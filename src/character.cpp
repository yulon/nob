#include <nob/object.hpp>
#include <nob/ntv.hpp>

#include <unordered_map>

namespace nob {
	struct _chr_data {
		entity fk_chute;
		character::motion_state_t lst_mo = character::motion_state_t::null;
		bool aiming = false;
		vector3 aim_cords;
	};

	std::unordered_map<int, _chr_data> _chr_data_map;

	void character::del() {
		_chr_data_map.erase(_ntv_hdl);
		ntv::PED::DELETE_PED(&_ntv_hdl);
	}

	void character::free() {
		_chr_data_map.erase(_ntv_hdl);
		ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&_ntv_hdl);
	}

	void character::go_to(const vector3 &target, float speed) {
		if (ntv::PED::GET_PED_PARACHUTE_STATE(_ntv_hdl) == 2) {
			ntv::AI::TASK_PARACHUTE_TO_TARGET(_ntv_hdl, target.x, target.y, target.z);
			return;
		}

		auto &data = _chr_data_map[_ntv_hdl];

		if (data.aiming) {
			ntv::AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(
				_ntv_hdl,
				target.x, target.y, target.z,
				data.aim_cords.x, data.aim_cords.y, data.aim_cords.z,
				speed,
				false, 2.0f, 0.5f, true, 0, 0,
				hash("FIRING_PATTERN_FULL_AUTO")
			);
		} else {
			ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
				_ntv_hdl,
				target.x, target.y, target.z,
				speed,
				-1, 0, 0
			);
		}

		if (speed == speed_run) {
			ntv::AI::SET_PED_DESIRED_MOVE_BLEND_RATIO(_ntv_hdl, 2.0f);
		} else {
			ntv::AI::SET_PED_DESIRED_MOVE_BLEND_RATIO(_ntv_hdl, speed);
		}
	}

	void character::aim(const vector3 &coords) {
		if (is_in_vehicle()) {
			auto wpn_grp = arm::weapon_group(current_weapon());
			if (!wpn_grp || wpn_grp == "GROUP_UNARMED") {
				ntv::AI::TASK_VEHICLE_AIM_AT_COORD(_ntv_hdl, coords.x, coords.y, coords.z);
			}
			return;
		}
		ntv::AI::TASK_AIM_GUN_AT_COORD(_ntv_hdl, coords.x, coords.y, coords.z, -1, false, false);

		auto &data = _chr_data_map[_ntv_hdl];
		data.aiming = true;
		data.aim_cords = coords;
	}

	void character::stop_aim() {
		ntv::AI::CLEAR_PED_TASKS(_ntv_hdl);

		_chr_data_map[_ntv_hdl].aiming = false;
	}

	void character::shoot() {
		vector3 target;

		auto &data = _chr_data_map[_ntv_hdl];
		if (data.aiming) {
			target = data.aim_cords;
		} else {
			target = pos({0, 1000, 0});
		}

		auto chr_pos = pos();

		nob::ntv::GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(
			chr_pos.x, chr_pos.y, chr_pos.z,
			target.x, target.y, target.z, 0, false, current_weapon().hash(),
			_ntv_hdl, true, false, 1000.0f
		);
	}

	void character::auto_shoot() {
		vector3 target;

		auto &data = _chr_data_map[_ntv_hdl];
		if (data.aiming) {
			target = data.aim_cords;
		} else {
			target = pos({0, 1000, 0});
		}

		if (is_in_vehicle()) {
			/*if (!arm::weapon_group(current_weapon())) {
				ntv::VEHICLE::SET_VEHICLE_SHOOT_AT_TARGET(_ntv_hdl, ntv::PED::GET_VEHICLE_PED_IS_IN(_ntv_hdl, false), coords.x, coords.y, coords.z);
				return;
			}*/
			ntv::AI::TASK_VEHICLE_SHOOT_AT_COORD(_ntv_hdl, target.x, target.y, target.z, 1.0f);
			return;
		}
		ntv::AI::TASK_SHOOT_AT_COORD(_ntv_hdl, target.x, target.y, target.z, -1, hash("FIRING_PATTERN_FULL_AUTO"));
	}

	void character::show_fake_parachute(bool toggle) {
		auto &data = _chr_data_map[_ntv_hdl];

		if (toggle) {
			if (data.fk_chute) {
				return;
			}
			auto cods = pos({0, 0, 2});
			data.fk_chute = ntv::OBJECT::CREATE_OBJECT_NO_OFFSET(model(0x73268708), cods.x, cods.y, cods.z, false, true, true);
			ntv::ENTITY::SET_ENTITY_COLLISION(data.fk_chute, false, false);
			ntv::ENTITY::ATTACH_ENTITY_TO_ENTITY(
				data.fk_chute, _ntv_hdl,
				nob::ntv::PED::GET_PED_BONE_INDEX(_ntv_hdl, 0xE0FD),
				3.6, 0, 0, 0, 90.0f, 0, false, false, false, true, 0, true
			);
		} else {
			data.fk_chute.del();
		}
	}

	void character::movement(const movement_t &mm) {
		entity::movement(mm);

		auto &data = _chr_data_map[_ntv_hdl];

		if (mm.motion_state == motion_state_t::parachuting) {
			if (data.lst_mo != motion_state_t::parachuting) {
				show_fake_parachute();
				still();
				data.lst_mo = motion_state_t::parachuting;
			}
			return;
		} else if (data.lst_mo == motion_state_t::parachuting) {
			show_fake_parachute(false);
		}

		switch (mm.motion_state) {
			case motion_state_t::still:
				if (data.lst_mo != motion_state_t::still) {
					still();
				}
				break;
			case motion_state_t::jumping:
				if (data.lst_mo != motion_state_t::jumping) {
					jump();
				}
				break;
			case motion_state_t::walking:
				go(speed_walk);
				break;
			case motion_state_t::runing:
				go(speed_run);
				break;
			case motion_state_t::sprinting:
				go(speed_sprint);
				break;
			case motion_state_t::skydiving:
				if (data.lst_mo != motion_state_t::skydiving) {
					skydive();
				}
				break;
			case motion_state_t::climbing:
				climb();
				break;
			case motion_state_t::climbing_ladder:
				climb_ladder();
				break;
			default:
				break;
		}

		data.lst_mo = mm.motion_state;
	}
} /* nob */
