#include <nob.hpp>

#include <rua/hook.hpp>

#include <cstring>
#include <cstdlib>

#include <sstream>
#include <iostream>

nob::task print_pos([]() {
	auto pos = nob::player::body().pos();
	std::stringstream ss;
	ss << "X: " << pos.x << ", Y: " << pos.y << ", Z: " << pos.z;
	nob::g2d::text(0, 0.93, 1, ss.str(), 0.6, 255, 255, 255, 255, 1, true);
});

nob::initer disable_ntv_ia_menu([]() {
	nob::ui::disable_interaction_menu();
});

using namespace nob::ui;

template<typename C>
void add_vehs(list &li, const C &c) {
	for (auto &mi : c) {
		li->items.emplace_back(action(nob::i18n::get(mi.name()), mi.name(), [&mi]() {
			auto veh = nob::vehicle(mi, nob::player::body().pos({0, 5, 0}));
			veh.place_on_ground();
			veh.set_best_mods();
			veh.invincible();
		}));
	}
}

nob::ui::menu ia_menu("Nob Tester", list("Interaction Menu", {
	list("Vehicle", {
		list("Spawn", [](list li) {
			add_vehs(li, nob::vehicles);

			nob::vehicle::unlock_banned_vehicles();
			add_vehs(li, nob::banned_vehicles);

			li->on_show = nullptr;
		})
	}),
	list("Weapon", {
		action("Print Current Info", []() {
			nob::player::body().print_weapon_info();
		}),
		action("Get All", []() {
			nob::player::body().add_all_weapons();
		}),
		action("Remove All", []() {
			nob::player::body().rm_all_weapons();
		}),
		list("Get", [](list li) {
			for (auto &wpn : nob::arm::weapons) {
				if (wpn == "WEAPON_UNARMED") {
					continue;
				}
				li->items.emplace_back(action(std::string(wpn.src_str()).substr(7), [&wpn]() {
					auto pb = nob::player::body();
					auto wpn_grp = nob::arm::weapon_group(wpn);

					if (wpn_grp == "GROUP_THROWN") {
						pb.thrown_weapon(wpn, pb.weapon_max_ammo(wpn));
						return;
					}

					pb.add_weapon(wpn);

					if (wpn_grp == "GROUP_MELEE") {
						return;
					}

					pb.ammo(pb.weapon_ammo_type(wpn), pb.weapon_max_ammo(wpn));
				}));
			}
		})
	}),
	list("Player", {
		flag("Invincible", [](bool val) {
			auto pb = nob::player::body();
			pb.invincible(val);
			/*auto addr = nob::shv::getScriptHandleBaseAddress(pb);
			if (addr) {
				nob::log(addr);
				*(DWORD *)(addr + 0x188) |= (1 << 9);
			}*/
		}),
		flag("Auto Get Parachute in Plane", [](bool val) {
			nob::player::auto_get_parachute_in_plane(val);
		}),
		action("Record", []() {
			auto pb = nob::player::body();
			static std::queue<nob::character::movement_t> rec;
			static nob::task tsk;
			if (rec.empty()) {
				nob::ui::tip("record start!");
				tsk = nob::task([pb]() {
					rec.emplace(pb.movement());
				});
			} else {
				if (tsk) {
					tsk.del();
					nob::ui::tip("record done!");
					return;
				}
				nob::task([pb]() mutable {
					if (rec.size()) {
						pb.movement(rec.front());
						rec.pop();
					} else {
						nob::ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(pb);
						nob::ui::tip("end!");
						nob::this_task::del();
					}
				});
			}
		}),
		action("Other -1", []() {
			auto pb = nob::player::body();
			auto pos = pb.pos({0, 0, 0});
			auto p = nob::ntv::OBJECT::CREATE_OBJECT_NO_OFFSET(nob::model(0x73268708), pos.x, pos.y, pos.z, false, true, true);
			nob::ntv::ENTITY::SET_ENTITY_COLLISION(p, false, false);
			nob::ntv::ENTITY::ATTACH_ENTITY_TO_ENTITY(p, pb, nob::ntv::PED::GET_PED_BONE_INDEX(pb, 0xE0FD), 3.7, 0, 0, 0, 90.0f, 0, false, false, false, true, 0, true);
			nob::wait(10000);
			nob::ntv::ENTITY::DELETE_ENTITY(&p);
		}),
		action("Other 0", []() {
			auto pb = nob::player::body();
			pb.add_parachute_pack();
			pb.move(pb.pos({0, 0, 1000}));
		}),
		action("Other", []() {

/*			for (size_t i = 0; i < nob::ntv::script_list->size; ++i) {
				if (nob::ntv::script_list->nodes[i].hash == nob::hash("friends_debug_controller")) {
					nob::log("!!!!!!!!!!!!!!!!!!");

					nob::log(nob::ntv::script_list->nodes[i].script);
					nob::log((nob::ntv::script_list->nodes[i].script ? nob::ntv::script_list->nodes[i].script->is_valid() : false));

					if (!nob::ntv::SCRIPT::HAS_SCRIPT_LOADED("friends_debug_controller")) {
						nob::ntv::SCRIPT::REQUEST_SCRIPT("friends_debug_controller");
						while (!nob::ntv::SCRIPT::HAS_SCRIPT_LOADED("friends_debug_controller")) {
							nob::wait_next_frame();
						}
					}

					nob::log("!~~~~~~~~~~~~~~~~");

					nob::log(nob::ntv::script_list->nodes[i].script->code_length);

					nob::ntv::script_list->nodes[i].script->code_page[0] = reinterpret_cast<uintptr_t>(&xxx2);

					nob::ntv::SYSTEM::START_NEW_SCRIPT("friends_debug_controller", 4096);
					break;
				}
			}
			auto pb = nob::player::body();
			nob::ntv::PED::_0x39D55A620FCB6A3A(
				pb,
				0,
				18,
				0
			);
			auto chr = nob::character("mp_m_freemode_01", nob::world::get_ground_pos(pb.pos({0, 5, 0})), true);
			nob::ntv::PED::_0x39D55A620FCB6A3A(
				chr,
				0,
				119,
				0
			);
			nob::task([pb]() {
				nob::ntv::Vector3 v3;
				if (nob::ntv::WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(pb, &v3)) {
					//nob::wait_next_frame();
					nob::log(&v3, ": ", v3.x, ", ", v3.y, ", ", v3.z);
					//nob::log(v3._paddingx, ", ", v3._paddingy, ", ", v3._paddingz, "=======================");
				}
			});
			nob::ntv::VEHICLE::DISABLE_VEHICLE_WEAPON(true, 0xca46f87d, pb.current_vehicle(), pb);
			auto d = "skydive@parachute@chute";
			nob::ntv::STREAMING::REQUEST_ANIM_DICT(d);
			if (!nob::ntv::STREAMING::HAS_ANIM_DICT_LOADED(d)) {
				nob::wait([d]()->bool {
					return nob::ntv::STREAMING::HAS_ANIM_DICT_LOADED(d);
				});
			}



			auto chr = nob::character("s_m_m_movalien_01", nob::world::get_ground_pos(pb.pos({0, 5, 0})), true);
			chr.add_weapon("WEAPON_PISTOL");
			chr.switch_weapon("WEAPON_PISTOL");
			chr.aim(chr.pos({20, 20, 0}));
			chr.go();

			auto n = "p_parachute_s_idlefast";
			nob::ntv::AI::TASK_PLAY_ANIM(pb, d, n, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
			nob::wait(5000);
			nob::ntv::AI::STOP_ANIM_TASK(pb, d, n, 0);//*/
			//auto veh = pb.current_vehicle();
			///*


			//auto pos = pb.pos({0, 20, 0});
			//nob::ntv::GRAPHICS::DRAW_LIGHT_WITH_RANGE(pos.x, pos.y, pos.z, 255, 0, 0, 10, 10);
			//nob::player::disable_automatic_respawn();
			//nob::wait(10000);
			//pb.resurrect();
			//nob::ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(pb);


			/*
			static rua::hook<nob::ntv::func_t> hkk;

			auto sf = nob::ntv::WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD.target();
			if (sf) {
				nob::log("hook");
				hkk.assign(sf, [](nob::ntv::call_context_t &cc) {
					auto begin = *cc.result_ptr;
					hkk.orig_fn(std::ref(cc));
					if (!cc.result<bool>()) {
						return;
					}
					nob::log("=======================");
					nob::log(begin);
					//begin.print();
					//nob::log("-----------------------");
					nob::log(*cc.result_ptr);
					//cc.print();
					nob::log("=======================");
				});
			}//*/

			/*static nob::character::group g("_xxxxxxxxddd");

			auto veh = nob::vehicle("TAXI", nob::player::body().pos({0, 10, 0}));

			auto chr = nob::character("s_m_m_movalien_01", nob::world::get_ground_pos(pb.pos({0, 5, 0})), true);
			chr.into_vehicle(veh, -1);
			//auto chr2 = nob::character("s_m_m_movalien_01", nob::world::get_ground_pos(pb.pos({0, 5, 0})), true);
			//chr2.into_vehicle(veh, 7);



			g.add(pb);
			g.add(chr);
			//g.add(chr2);

			nob::ntv::VEHICLE::SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(veh, false);*/
			//nob::ntv::VEHICLE::SET_VEHICLE_IS_STOLEN(veh, true);
			//nob::ntv::VEHICLE::SET_VEHICLE_DOORS_LOCKED(veh, 1);

			//nob::wait(1000);

			//chr.switch_weapon("WEAPON_MICROSMG");
			//chr.ammo_no_consumption();
			//chr.shoot(pos);

			//nob::ntv::AI::TASK_AIM_GUN_AT_COORD(chr, pos.x, pos.y, pos.z, -1, true, true);
			//nob::ntv::AI::TASK_VEHICLE_AIM_AT_COORD(chr, pos.x, pos.y, pos.z);

			//auto cods = nob::world::load_ilp(nob::world::ilp::stab_city_on_fire);
			//nob::ntv::PLAYER::START_PLAYER_TELEPORT(nob::player::native_handle(), cods.x, cods.y, cods.z, 0, true, true, true);

			//nob::world::load_all_ilps();
			//nob::world::lock_all_doors(false);

			//nob::ntv::PED::SET_PED_CAN_RAGDOLL(pb_nh, true);
			//nob::ntv::PED::_RESET_PED_RAGDOLL_BLOCKING_FLAGS(pb_nh, 2);
			//nob::ntv::PED::_RESET_PED_RAGDOLL_BLOCKING_FLAGS(pb_nh, 4);

			//for (size_t i = 1; i <= 26; ++i) {
				//nob::ntv::PED::_RESET_PED_RAGDOLL_BLOCKING_FLAGS(pb_nh, i);
			//}
		})
	}),
	list("World", {
		flag("No Man's Island", [](bool val) {
			nob::world::no_mans_island(val);
		}),
		flag("Snowy", [](bool val) {
			nob::world::snowy(val);
		}),
		action("Clean Pickups", []() {
			nob::world::clean_pickups();
		})
	}),
	list("UI", {
		flag("Disable Story Features", [](bool val) {
			nob::ui::disable_sp_features(val);
		}),
		flag("Disable Wheel Slowmo", [](bool val) {
			nob::ui::disable_wheel_slowmo(val);
		}),
		action("Pops", []() {
			nob::ui::info("you know!");

			nob::ui::tip("~b~~h~dog~h~~s~ killed ~r~~h~cat");

			nob::ui::message(
				"CHAR_MARTIN",
				"馬丁",
				"~r~你們休想取代我！"
			);

			ia_menu.toggle();
		})
	}),
	list("Map", {
		action("Clear Black Fog", []() {
			nob::map::clear_black_fog();
		})
	}),
	list("Screen", {
		flag("Thermal Vision", [](bool val) {
			nob::screen::thermal_vision(val);
		}),
		flag("Night Vision", [](bool val) {
			nob::screen::night_vision(val);
		}),
		list("Filters", [](list li) {
			for (auto name : nob::screen::filters) {
				li->items.emplace_back(flag(name, [name](bool val) {
					nob::screen::filter(name, val);
				}));
			}
		})
	}),
	list("Script", {
		action("Terminate Unimportant Scripts", []() {
			nob::terminate_unimportant_scripts();
		})
	})
}));

nob::keyboard::listener ia_menu_hotkey([](int code, bool down)->bool {
	if (code == 'M') {
		if (down) {
			ia_menu.toggle();
		}
		return false;
	}
	return true;
});
