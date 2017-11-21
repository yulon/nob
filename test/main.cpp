#include <nob.hpp>

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

template<typename HRC>
void add_vehs(list &li, const HRC &hrc) {
	for (auto &hr : hrc) {
		li->items.emplace_back(action(nob::i18n::get(hr.src_str()), hr.src_str(), [&hr]() {
			auto veh = nob::vehicle(hr, nob::player::body().pos({0, 5, 0}));
			veh.place_on_ground();
			veh.set_best_mods();
			veh.invincible();
		}));
	}
}

nob::ui::menu ia_menu("Nob Tester", list("Interaction Menu", {
	list("Vehicle", {
		list("Spawn", [](list li) {
			add_vehs(li, nob::model::vehicles);

			nob::vehicle::unlock_banned_vehicles();
			add_vehs(li, nob::model::banned_vehicles);

			li->on_show = nullptr;
		})
	}),
	list("Weapon", {
		action("Print Current Weapon Info", []() {
			nob::player::body().print_weapon_info();
		}),
		action("Get All Weapons", []() {
			nob::player::body().add_all_weapons();
		}),
		action("Remove All Weapons", []() {
			nob::player::body().rm_all_weapons();
		}),
		list("Get a Weapon", [](list li) {
			for (auto &wpn : nob::arm::weapons) {
				if (wpn == "WEAPON_UNARMED") {
					continue;
				}
				li->items.emplace_back(action(std::string(wpn.src_str()).substr(7), [&wpn]() {
					auto pb = nob::player::body();
					auto wpn_grp = nob::arm::weapon_group(wpn);

					if (wpn_grp == "GROUP_THROWN") {
						pb.thrown_weapon(wpn, pb.max_ammo(wpn));
						return;
					}

					pb.add_weapon(wpn);

					if (wpn_grp == "GROUP_MELEE") {
						return;
					}

					pb.ammo(pb.ammo_type(wpn), pb.max_ammo(wpn));
				}));
			}
		})
	}),
	list("Player", {
		flag("Invincible", [](bool val) {
			auto pb = nob::player::body();
			pb.invincible(val);
			/*auto addr = nob::shv::getScriptHandleBaseAddress(pb.native_handle());
			if (addr) {
				std::cout << addr << std::endl;
				*(DWORD *)(addr + 0x188) |= (1 << 9);
			}*/
		}),
		flag("Auto Get Parachute in Plane", [](bool val) {
			nob::player::auto_get_parachute_in_plane(val);
		}),
		action("Other", []() {
			//auto cods = nob::world::load_ilp(nob::world::ilp::stab_city_on_fire);
			//nob::ntv::PLAYER::START_PLAYER_TELEPORT(nob::player::native_handle(), cods.x, cods.y, cods.z, 0, true, true, true);

			nob::world::load_all_ilps();
			nob::world::lock_all_doors(false);

			//auto pb = nob::player::body();
			//auto pb_nh = pb.native_handle();

			//nob::ntv::PED::SET_PED_CAN_RAGDOLL(pb_nh, true);
			//nob::ntv::PED::_RESET_PED_RAGDOLL_BLOCKING_FLAGS(pb_nh, 2);
			//nob::ntv::PED::_RESET_PED_RAGDOLL_BLOCKING_FLAGS(pb_nh, 4);

			//for (size_t i = 1; i <= 26; ++i) {
				//nob::ntv::PED::_RESET_PED_RAGDOLL_BLOCKING_FLAGS(pb_nh, i);
			//}


			//nob::ntv::PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(nob::player::native_handle(), 0);
			/*
			auto pos = pb.pos();
			auto chr = nob::character("s_m_m_movalien_01", nob::world::get_ground_pos({pos.x + 5, pos.y, pos.z + 10}), true);
			auto old_h = std::make_shared<float>(nob::ntv::ENTITY::GET_ENTITY_HEADING(pb.native_handle()));

			nob::task([chr, pb, old_h]() mutable {
				//if (!nob::ntv::AI::IS_PED_STILL(pb.native_handle())) {
					float h = nob::ntv::ENTITY::GET_ENTITY_HEADING(pb.native_handle());
					if (h != *old_h) {
						auto pos = pb.pos({0, 10, 0});
						chr.face({pos.x + 5, pos.y, pos.x}, h);
						*old_h = h;
					}
				//}
			});

			pb.on_motion([](nob::character::motion_state ms) {
				switch (ms) {
					case nob::character::motion_state::still:
						std::cout << "still" << std::endl << std::endl;
						break;
					case nob::character::motion_state::jumping:
						std::cout << "jumping" << std::endl;
						break;
					case nob::character::motion_state::walking:
						std::cout << "walking" << std::endl;
						break;
					case nob::character::motion_state::runing:
						std::cout << "runing" << std::endl;
						break;
					case nob::character::motion_state::sprinting:
						std::cout << "sprinting" << std::endl;
						break;
					case nob::character::motion_state::falling:
						std::cout << "falling" << std::endl;
						break;
					case nob::character::motion_state::skydiving:
						std::cout << "skydiving" << std::endl;
						break;
					case nob::character::motion_state::parachuting:
						std::cout << "parachuting" << std::endl;
						break;
					case nob::character::motion_state::climbing:
						std::cout << "climbing" << std::endl;
						break;
					case nob::character::motion_state::null:
						std::cout << "null" << std::endl;
						break;
				}
			});*/
		})
	}),
	list("World", {
		flag("No Man's Island", [](bool val) {
			nob::world::no_mans_island(val);
		}),
		action("Clear Black Fog", []() {
			nob::world::clear_black_fog();
		}),
		action("Clean Pickups", []() {
			nob::world::clean_pickups();
		})
	}),
	list("UI", {
		flag("Disable Story Features", [](bool val) {
			disable_sp_features(val);
		}),
		flag("Disable Wheel Slowmo", [](bool val) {
			disable_wheel_slowmo(val);
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
