#include <nob/object.hpp>
#include <nob/ntv.hpp>

#include <unordered_map>

namespace nob {
	struct _chr_data {
		entity fk_chute;
		character::motion_state_t lst_mo = character::motion_state_t::null;
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
