#include <nob/object.hpp>
#include <nob/ntv.hpp>

#include <unordered_map>

namespace nob {
	struct _chr_data {
		entity fk_chute = 0;
		character::motion_state_t lst_mds = character::motion_state_t::null;
		bool going = false, aiming = false, shooting = false;
		float go_speed; vector3 go_dest;
		vector3 focus{0, 0, 0};
	};

	std::unordered_map<int, _chr_data> _chr_data_map;

	void character::del() {
		_chr_data_map.erase(_h);
		ntv::PED::DELETE_PED(&_h);
	}

	void character::free() {
		_chr_data_map.erase(_h);
		ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&_h);
	}

	static bool _is_new_mds(int h, character::motion_state_t now) {
		auto &data = _chr_data_map[h];

		if (data.lst_mds == now) {
			return false;
		}

		switch (data.lst_mds) {
			case character::motion_state_t::walking:
			case character::motion_state_t::runing:
			case character::motion_state_t::sprinting:
				data.going = false;
				break;
			case character::motion_state_t::climbing_ladder:
			case character::motion_state_t::covering:
			case character::motion_state_t::paralysing:
				ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(h);
				break;
			case character::motion_state_t::parachuting:
				if (data.fk_chute) {
					data.fk_chute.del();
					data.fk_chute = 0;
				} else {
					ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(h);
				}
				break;
			default:
				break;
		}

		data.lst_mds = now;
		return true;
	}

	void character::stop_motion_command() {
		_is_new_mds(_h, character::motion_state_t::null);
		auto &data = _chr_data_map[_h];
		if (data.aiming) {
			data.aiming = false;
		}
		if (data.shooting) {
			data.shooting = false;
		}
		ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(_h);
	}

	void character::still() {
		if (!_is_new_mds(_h, character::motion_state_t::still)) {
			return;
		}
		ntv::AI::TASK_STAND_STILL(_h, -1);
	}

	void character::jump() {
		if (!_is_new_mds(_h, character::motion_state_t::jumping)) {
			return;
		}
		ntv::AI::TASK_JUMP(_h, false, false, false);
	}

	void character::climb() {
		_is_new_mds(_h, character::motion_state_t::climbing);
		ntv::AI::TASK_CLIMB(_h, false);
	}

	void character::climb_ladder() {
		if (!_is_new_mds(_h, character::motion_state_t::climbing_ladder)) {
			return;
		}
		ntv::AI::TASK_CLIMB_LADDER(_h, 0);
	}

	void character::cover() {
		if (!_is_new_mds(_h, character::motion_state_t::covering)) {
			return;
		}
		ntv::AI::TASK_STAY_IN_COVER(_h);
	}

	void character::paralysis() {
		if (!_is_new_mds(_h, character::motion_state_t::paralysing)) {
			return;
		}
		ntv::PED::SET_PED_TO_RAGDOLL(_h, -1, -1, 0, false, false, false);
	}

	void character::skydive() {
		if (!_is_new_mds(_h, character::motion_state_t::skydiving)) {
			return;
		}
		ntv::AI::TASK_SKY_DIVE(_h);
	}

	void character::go_to(const vector3 &dest, float speed) {
		auto &data = _chr_data_map[_h];

		if (data.going) {
			bool is_new;
			if (speed < character::speed_run) {
				is_new = _is_new_mds(_h, character::motion_state_t::walking);
			} else if (speed < character::speed_sprint) {
				is_new = _is_new_mds(_h, character::motion_state_t::runing);
			} else {
				is_new = _is_new_mds(_h, character::motion_state_t::sprinting);
			}
			if (
				!is_new &&
				speed == data.go_speed &&
				dest.x == data.go_dest.x && dest.y == data.go_dest.y && dest.z == data.go_dest.z
				) {
				return;
			}
		} else {
			data.going = true;
		}

		data.go_speed = speed;
		data.go_dest = dest;

		if (data.shooting) {
			return;
		}
		if (data.aiming) {
			aim();
			return;
		}
		ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
			_h,
			dest.x, dest.y, dest.z,
			speed,
			-1, 0, 0
		);
	}

	void character::look() {
		/*auto &data = _chr_data_map[_h];
		data.focus = coords;
		if (data.shooting) {
			shoot();
			return;
		}
		if (data.aiming) {
			aim();
			return;
		}
		ntv::AI::TASK_LOOK_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, -1, 0, 2);*/
	}

	void character::focus(const vector3 &coords) {
		_chr_data_map[_h].focus = coords;
	}

	void character::aim(bool toggle) {
		auto &data = _chr_data_map[_h];

		if (toggle) {
			data.aiming = true;
			if (data.shooting) {
				shoot();
				return;
			}
			if (is_in_vehicle()) {
				auto wpn_grp = arm::weapon_group(current_weapon());
				if (!wpn_grp || wpn_grp == "GROUP_UNARMED") {
					ntv::AI::TASK_VEHICLE_AIM_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z);
				}
				return;
			}
			if (data.going) {
				ntv::AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(
					_h,
					data.go_dest.x, data.go_dest.y, data.go_dest.z,
					data.focus.x, data.focus.y, data.focus.z,
					data.go_speed,
					false, 2.0f, 0.5f, true, 0, 0,
					hash("FIRING_PATTERN_FULL_AUTO")
				);
				return;
			}
			ntv::AI::TASK_AIM_GUN_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, -1, false, false);
		} else if (data.aiming) {
			data.aiming = false;
			if (data.shooting) {
				return;
			}
			if (data.going) {
				ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
					_h,
					data.go_dest.x, data.go_dest.y, data.go_dest.z,
					data.go_speed,
					-1, 0, 0
				);
				return;
			}
			ntv::AI::CLEAR_PED_TASKS(_h);
		}
	}

	void character::shoot(bool toggle) {
		auto &data = _chr_data_map[_h];

		if (toggle) {
			data.shooting = true;
			if (is_in_vehicle()) {
				/*if (!arm::weapon_group(current_weapon())) {
					ntv::VEHICLE::SET_VEHICLE_SHOOT_AT_TARGET(_h, ntv::PED::GET_VEHICLE_PED_IS_IN(_h, false), coords.x, coords.y, coords.z);
					return;
				}*/
				ntv::AI::TASK_VEHICLE_SHOOT_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, 1.0f);
				return;
			}
			ntv::AI::TASK_SHOOT_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, -1, hash("FIRING_PATTERN_FULL_AUTO"));
		} else if (data.shooting) {
			data.shooting = false;
			if (data.aiming) {
				aim();
				return;
			}
			if (data.going) {
				ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
					_h,
					data.go_dest.x, data.go_dest.y, data.go_dest.z,
					data.go_speed,
					-1, 0, 0
				);
				return;
			}
			ntv::AI::CLEAR_PED_TASKS(_h);
		}
	}

	void character::shoot_once() {
		/*vector3 dest;

		auto &data = _chr_data_map[_h];
		if (data.aiming) {
			dest = data.focus;
		} else {
			dest = pos({0, 1000, 0});
		}

		auto h = current_weapon().hash();

		if (!ntv::WEAPON::HAS_WEAPON_ASSET_LOADED(h)) {
			ntv::WEAPON::REQUEST_WEAPON_ASSET(h, 31, 0);
			sleep([h]()->bool {
				return ntv::STREAMING::HAS_MODEL_LOADED(h);
			});
		}

		auto chr_pos = pos();

		ntv::GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(
			chr_pos.x, chr_pos.y, chr_pos.z,
			dest.x, dest.y, dest.z, 0, false, h,
			_h, true, false, 1000.0f
		);*/
	}

	void character::open_parachute() {
		if (!_is_new_mds(_h, character::motion_state_t::parachuting)) {
			return;
		}
		add_parachute_pack();
		ntv::PED::FORCE_PED_TO_OPEN_PARACHUTE(_h);
	}

	void character::open_fake_parachute() {
		if (!_is_new_mds(_h, character::motion_state_t::parachuting)) {
			return;
		}
		auto &data = _chr_data_map[_h];
		if (data.fk_chute) {
			return;
		}
		auto cods = pos({0, 0, 2});
		data.fk_chute = entity(0x73268708, cods);
		ntv::ENTITY::SET_ENTITY_COLLISION(data.fk_chute, false, false);
		ntv::ENTITY::ATTACH_ENTITY_TO_ENTITY(
			data.fk_chute, _h,
			nob::ntv::PED::GET_PED_BONE_INDEX(_h, 0xE0FD),
			3.6, 0, 0, 0, 90.0f, 0, false, false, false, true, 0, true
		);
		ntv::AI::TASK_STAND_STILL(_h, -1);
	}

	void character::movement(const movement_t &mm) {
		entity::movement(mm);

		switch (mm.motion_state) {
			case motion_state_t::still:
				still();
				break;
			case motion_state_t::jumping:
				jump();
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
				skydive();
				break;
			case motion_state_t::climbing:
				climb();
				break;
			case motion_state_t::climbing_ladder:
				climb_ladder();
				break;
			case motion_state_t::parachuting:
				open_fake_parachute();
				break;
			case motion_state_t::covering:
				cover();
				break;
			default:
				break;
		}
	}
} /* nob */
