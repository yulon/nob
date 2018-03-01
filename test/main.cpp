#include <nob.hpp>

#include <rua/hook.hpp>
#include <rua/observer.hpp>

#include "../../steam_id_getter/include/steam_id_getter.hpp"

#include <cstring>
#include <cstdlib>

#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

float high_speed = 0.0f;

nob::task print_pos([]() {
	auto pb = nob::player::body();
	auto pos = pb.pos();
	std::stringstream ss;
	ss << pos.str() << ", " << pb.rotation().str() << ", " << high_speed;
	nob::g2d::text(0, 0.93, 1, ss.str().c_str(), 0.4, 255, 255, 255, 255, 1, true);
});

nob::task speed_log([]() {
	static auto lst_tp = std::chrono::steady_clock::time_point::min();
	static nob::vector3 lst_pos {0, 0, 0};
	auto pb = nob::player::body();
	if (!pb.is_in_vehicle()) {
		auto tp = std::chrono::steady_clock::now();
		auto pos = pb.pos();
		if (lst_pos.z) {
			auto dis = pos.distance(lst_pos);
			auto speed = 1000.0f / std::chrono::duration_cast<std::chrono::milliseconds>(tp - lst_tp).count() * dis;
			if (speed > high_speed) {
				high_speed = speed;
			}
		}
		lst_tp = tp;
		lst_pos = pos;
	}
	nob::sleep(5000);
});

nob::first_task unlock_vehs(nob::unlock_banned_vehicles);
/*
nob::first_task blk([]() {

	while (*nob::ntv::game_state != nob::ntv::game_state_t::playing) {
		nob::yield();
	}
	nob::sleep(2000);
	nob::ui::loading_screen();
	nob::sleep(10000);
	nob::ui::loading_screen(false);
});
*/
using namespace nob::ui;

void add_veh(list &li, const nob::model &m) {
	li->items.emplace_back(action(nob::i18n::get(m.name()), m.name(), [m]() {
		auto veh = nob::vehicle(m, nob::player::body().pos({0, 5, 0}));
		veh.place_on_ground();
		veh.set_best_mods();
		veh.invincible();
	}));
}

nob::ui::menu ia_menu("Nob Tester", list("Interaction Menu", {
	list("Vehicle", {
		list("Spawn", [](list li) {
			list super("Super"), plane("Plane"), heli("Helicopter"), other("Other");

			for (nob::model m : nob::base_vehicles) {
				switch (nob::vehicle::get_class_from_model(m)) {
					case nob::vehicle::class_t::super:
						add_veh(super, m);
						break;
					case nob::vehicle::class_t::plane:
						add_veh(plane, m);
						break;
					case nob::vehicle::class_t::helicopter:
						add_veh(heli, m);
						break;
					default:
						add_veh(other, m);
				}
			}

			for (nob::model m : nob::dlc_vehicles()) {
				switch (nob::vehicle::get_class_from_model(m)) {
					case nob::vehicle::class_t::super:
						add_veh(super, m);
						break;
					case nob::vehicle::class_t::plane:
						add_veh(plane, m);
						break;
					case nob::vehicle::class_t::helicopter:
						add_veh(heli, m);
						break;
					default:
						add_veh(other, m);
				}
			}

			li->items = { std::move(super), std::move(plane), std::move(heli), std::move(other) };

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
			nob::player::body().clear_armed();
		}),
		list("Get", [](list li) {
			for (auto &wpn : nob::arm::weapons) {
				if (wpn == "WEAPON_UNARMED") {
					continue;
				}
				li->items.emplace_back(action(std::string(wpn.src_str()).substr(7), [&wpn]() {
					auto pb = nob::player::body();
					auto wpn_grp = nob::arm::weapon_group(wpn);

					if (wpn_grp != "GROUP_THROWN") {
						pb.add_weapon(wpn);
					}

					if (wpn_grp == "GROUP_MELEE") {
						return;
					}

					pb.weapon_ammo(wpn, pb.weapon_ammo_max(wpn));
				}));
			}
		})
	}),
	list("Player", {
		action("Print Postion", []() {
			auto pos = nob::player::body().pos();
			nob::log("{ ", pos.x, ", ", pos.y, ", ", pos.z, " }");
		}),
		flag("Direct Move", [](bool val) {
			static nob::key_listener kl;
			static nob::task tsks[6];

			auto pb = nob::player::body();
			if (val) {
				nob::ntv::ENTITY::FREEZE_ENTITY_POSITION(pb, true);
				kl = nob::key_listener([](int code, bool down)->bool {
					static float m = 1.0f;
					static auto cmd = [](bool down, size_t ti, nob::vector3 (*dest)(nob::vector3)) {
						if (down) {
							if (!tsks[ti]) {
								tsks[ti] = nob::task([dest]() {
									auto pb = nob::player::body();
									auto rot = nob::ntv::CAM::GET_GAMEPLAY_CAM_ROT(0);
									pb.rotation(rot);
									pb.move(dest(rot));
								});
							}
						} else if (tsks[ti]) {
							tsks[ti].del();
						}
					};
					switch (code) {
						case 'W': {
							cmd(down, 0, [](nob::vector3 cam_rot)->nob::vector3 {
								return nob::player::body().pos() + m * cam_rot.rotation_to_direction();
							});
							return false;
						}
						case 'S': {
							cmd(down, 1, [](nob::vector3 cam_rot)->nob::vector3 {
								return nob::player::body().pos() + (-m * cam_rot.rotation_to_direction());
							});
							return false;
						}
						case 'A': {
							cmd(down, 2, [](nob::vector3 cam_rot)->nob::vector3 {
								cam_rot.z += 90.0f;
								return nob::player::body().pos() + m * cam_rot.rotation_to_direction();
							});
							return false;
						}
						case 'D': {
							cmd(down, 3, [](nob::vector3 cam_rot)->nob::vector3 {
								cam_rot.z -= 90.0f;
								return nob::player::body().pos() + m * cam_rot.rotation_to_direction();
							});
							return false;
						}
						case VK_SPACE: {
							cmd(down, 4, [](nob::vector3)->nob::vector3 {
								auto pos = nob::player::body().pos();
								pos.z += 5.0f;
								return pos;
							});
							return false;
						}
						case 'F': {
							cmd(down, 5, [](nob::vector3)->nob::vector3 {
								auto pos = nob::player::body().pos();
								pos.z -= 3.0f;
								return pos;
							});
							return false;
						}
						case VK_SHIFT: {
							if (down) {
								m = 20.0f;
							} else {
								m = 1.0f;
							}
							return false;
						}
						default:
							return true;
					}
				});
			} else {
				kl.del();
				for (size_t i = 0; i < 6; ++i) {
					if (tsks[i]) {
						tsks[i].del();
					}
				}
				nob::ntv::ENTITY::FREEZE_ENTITY_POSITION(pb, false);
			}
		}),
		flag("Invincible", [](bool val) {
			nob::player::invincible(val);
		}),
		flag("Auto Get Parachute in Plane", [](bool val) {
			nob::player::auto_get_parachute_in_plane(val);
		}),
		action("Clear High Speed", []() {
			high_speed = 0.0f;
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
		action("Clear Tasks", []() {
			nob::ntv::AI::CLEAR_PED_TASKS(nob::player::body());
		}),
		action("Clear Tasks Force", []() {
			nob::ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(nob::player::body());
		}),
		action("Hook Function", []() {
			static rua::hooked<nob::ntv::func_t> hkd;
			nob::log(hkd.hook(
				nob::ntv::AI::TASK_PLAY_ANIM_ADVANCED.target(),
				[](nob::ntv::call_context_t &cc) {
					nob::log(cc.arg<char *>(1), ", ", cc.arg<char *>(2));
					hkd(cc);
				}
			));
		}),
		action("Make Nodes", []() {
			std::fstream f("wpn_nodes.inc", f.binary | f.trunc | f.in | f.out);
			if (!f.is_open()) {
				nob::log("failed to open");
			}

			std::mt19937_64 rd_ng(20180129);
			std::uniform_real_distribution<float> dis_x(nob::map::x_min, nob::map::x_max);
			std::uniform_real_distribution<float> dis_y(nob::map::y_min, nob::map::y_max);

			for (size_t i = 0; i < 2000; ++i) {
				nob::vector2 pos{dis_x(rd_ng), dis_y(rd_ng)};
				auto mkr = nob::map::marker({pos.x, pos.y, 100.0f});
				mkr.graphic(357);
				mkr.keep_track(false);
				f << "{ " << pos.x << ", " << pos.y << " }," << std::endl;
			}

			/*auto pb = nob::player::body();
			for (size_t x = 0; x < static_cast<size_t>(nob::map::width) / 800 - 1; ++x) {
				for (size_t y = 0; y < static_cast<size_t>(nob::map::height) / 800 - 1; ++y) {
					nob::vector3 ct {nob::map::x_min + 400.0f + x * 800.0f, nob::map::y_min + 400.0f + x * 800.0f, 900.0f};
					pb.move(ct);
					nob::sleep(500);

					bool ctn = false;

					while (!nob::world::ground_height(ct)) {
						if (ct.z <= 0) {
							ctn = true;
							break;
						}

						ct.z -= 200;
						pb.move(ct);
						nob::sleep(500);
					}

					if (ctn) {
						continue;
					}

					for (size_t i = 0; i < 3; ++i) {
						nob::ntv::Vector3 pos;
						int id;
						nob::ntv::PATHFIND::GET_RANDOM_VEHICLE_NODE(ct.x, ct.y, ct.z, 400.0f, false, false, false, &pos, &id);
						auto mkr = nob::map::marker({pos.x, pos.y, pos.z});
						mkr.graphic(357);
						mkr.keep_track(false);
						f << "{ " << pos.x << ", " << pos.y << ", " << pos.z << " }," << std::endl;
					}
				}
			}

			std::fstream f("veh_nodes.inc", f.binary | f.trunc | f.in | f.out);
			if (!f.is_open()) {
				nob::log("failed to open");
			}

			std::vector<nob::vector3> nodes {
				#include "../../gtabr/veh_nodes_500.inc"
			};

			for (size_t i = 0; i < nodes.size(); ++i) {
				auto pos = nodes[i];
				if (
					i > 0
					&& nodes[i].x == nodes[i-1].x
					&& nodes[i].y == nodes[i-1].y
					&& nodes[i].z == nodes[i-1].z
				) {
					continue;
				}
				auto mkr = nob::map::marker(pos);
				mkr.graphic(357);
				mkr.keep_track(false);
				f << "{ " << pos.x << ", " << pos.y << ", " << pos.z << " }," << std::endl;
			}*/
		}),
		action("Other", []() {
			//nob::log(nob::ntv::SCRIPT::GET_THIS_SCRIPT_NAME());

			//nob::log(nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(2, static_cast<int>(nob::hotkey_t::InteractionMenu), 1));
			//nob::log(nob::ntv::CONTROLS::_0x80C2FD58D720C801(2, static_cast<int>(nob::hotkey_t::InteractionMenu), 0));

			nob::ntv::PED::SET_PED_TO_RAGDOLL(nob::player::body(), -1, -1, 0, false, false, false);
			nob::sleep(5000);
			nob::ntv::PED::RESET_PED_RAGDOLL_TIMER(nob::player::body());
			nob::ntv::PLAYER::SET_PLAYER_CONTROL(0, true, 0);
			nob::ntv::GAMEPLAY::_RESET_LOCALPLAYER_STATE();

/*
			nob::task([]() {
				if (
					nob::ntv::CONTROLS::IS_CONTROL_PRESSED(0, (int)nob::hotkey_t::FrontendDown) ||
					nob::ntv::CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, (int)nob::hotkey_t::FrontendDown)
				) {
					nob::log("n ", nob::ntv::GAMEPLAY::GET_FRAME_COUNT());
					nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::hotkey_t::FrontendDown, true);
				}
			});

			nob::sleep(5000);
			nob::log("\n");
			nob::log("{ \"E\", \"", nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, 51, 0), "\" }");
			nob::log("{ \"enter\", \"", nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, 201, 0), "\" }");
			nob::log("{ \"esc\", \"", nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, 202, 0), "\" }");
			nob::log("{ \"space\", \"", nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, 55, 0), "\" }");
			nob::log("{ \"alt\", \"", nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, 19, 0), "\" }");
			nob::log("{ \"insert\", \"", nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, 121, 0), "\" }");
			nob::log("{ \"insert\", \"", nob::ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, 121, 0), "\" }");

			nob::player::damage_modifier(0);

			static auto pb = nob::player::body();
			//auto pos = pb.pos({0, 5, 0});


			//pb.ammo("AMMO_PISTOL", 101);
			pb.add_weapon("WEAPON_PISTOL");
			nob::ntv::WEAPON::SET_PED_INFINITE_AMMO(pb, true, nob::hash("WEAPON_PISTOL"));
			//
			//nob::log(pb.ammo("AMMO_PISTOL"));
			static auto veh = nob::vehicle("kuruma", pb.pos({0, 15, 0}));
			//pb.into_vehicle(veh, 0);
			//static auto chr = nob::character("mp_m_freemode_01", nob::world::ground_pos(pb.pos({0, 5, 0})), true);

			static nob::task tsk([]() {
				static int s;
				if (rua::set_when_changing(s, pb.trying_to_enter_vehicle_seat())) {
					nob::log(s);
				}
			});

			pb.get_in_vehicle(veh, 2);

			//veh.invincible();

			nob::task([]() {
				nob::ntv::PLAYER::RESET_PLAYER_STAMINA(0);
			});

			nob::ntv::OBJECT::CREATE_AMBIENT_PICKUP((nob::hash_t)nob::ntv::ePickupType::WeaponRPG, pos.x, pos.y, pos.z, 0, 0, nob::arm::get_model("AMMO_RIFLE").load(), 1, 0);



			nob::sleep(5000);
			for (size_t i = 0; i < 25; ++i) {
				nob::character("mp_m_freemode_01", veh.pos({ -1.7f, -19.0f + i * 1.0f, -3.05f }), true);
				nob::character("mp_m_freemode_01", veh.pos({ -0.7f, -19.0f + i * 1.0f, -3.05f }), true);
				nob::character("mp_m_freemode_01", veh.pos({ 0.7f, -19.0f + i * 1.0f, -3.05f }), true);
				nob::character("mp_m_freemode_01", veh.pos({ 1.7f, -19.0f + i * 1.0f, -3.05f }), true);
				nob::yield();
			}
			nob::log("done");

			auto veh = pb.current_vehicle();
			nob::log(veh.get_model().name(), ": { ", veh.pos().str(), ", ", veh.rotation().str(), " }");

			for (auto &n : nodes) {
				auto mkr = nob::map::marker(n);
				mkr.graphic(357);
				mkr.keep_track(false);
			}


			nob::player::switch_body(chr);
			nob::ntv::PED::SET_PED_ENABLE_WEAPON_BLOCKING(chr, false);

			static auto g = nob::character::group("nob_111");
			static auto g2 = nob::character::group("nob_222");
			g.add(pb);
			g.add(chr);
			//g.like(g2);

			auto veh = nob::vehicle("KURUMA", pb.pos({0, 15, 0}));
			chr.into_vehicle(veh, -1);


			nob::ntv::PED::SET_PED_TO_RAGDOLL(pb, -1, -1, 0, false, false, false);
			nob::sleep(5000);
			nob::ntv::PED::RESET_PED_RAGDOLL_TIMER(pb);
			nob::ntv::PED::SET_PED_TO_RAGDOLL(pb, 0, -1, 0, false, false, false);

			if (!nob::ntv::STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core")) {
				nob::ntv::STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
				nob::sleep([]()->bool {
					return nob::ntv::STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core");
				});
			}
nob::ntv::GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("core");
			nob::ntv::GRAPHICS::START_PARTICLE_FX_LOOPED_AT_COORD("fire_script_petrol_trail_glow", pos.x, pos.y, pos.z, 0.f, 0.f, 0, 1, 0, 0, 0, 0);

			nob::ntv::FIRE::ADD_OWNED_EXPLOSION(
				pb, pos.x, pos.y, pos.z, (int)nob::ntv::eExplosionType::Flare,
				0, true, false, 0
			);

			for (size_t i = 0; i < nob::ntv::script_list->size; ++i) {
				if (nob::ntv::script_list->nodes[i].hash == nob::hash("friends_debug_controller")) {
					nob::log("!!!!!!!!!!!!!!!!!!");

					nob::log(nob::ntv::script_list->nodes[i].script);
					nob::log((nob::ntv::script_list->nodes[i].script ? nob::ntv::script_list->nodes[i].script->is_valid() : false));

					if (!nob::ntv::SCRIPT::HAS_SCRIPT_LOADED("friends_debug_controller")) {
						nob::ntv::SCRIPT::REQUEST_SCRIPT("friends_debug_controller");
						while (!nob::ntv::SCRIPT::HAS_SCRIPT_LOADED("friends_debug_controller")) {
							nob::yield();
						}
					}

					nob::log("!~~~~~~~~~~~~~~~~");

					nob::log(nob::ntv::script_list->nodes[i].script->code_length);

					nob::ntv::script_list->nodes[i].script->code_pages[0] = reinterpret_cast<uintptr_t>(&xxx2);

					nob::ntv::SYSTEM::START_NEW_SCRIPT("friends_debug_controller", 4096);
					break;
				}
			}

			nob::ntv::VEHICLE::DISABLE_VEHICLE_WEAPON(true, 0xca46f87d, pb.current_vehicle(), pb);


			auto n = "p_parachute_s_idlefast";
			nob::ntv::AI::TASK_PLAY_ANIM(pb, d, n, 8.0f, 0.0f, -1, 9, 0, 0, 0, 0);
			nob::sleep(5000);
			nob::ntv::AI::STOP_ANIM_TASK(pb, d, n, 0);//*/
			//auto veh = pb.current_vehicle();
			///*


			//auto pos = pb.pos({0, 20, 0});
			//nob::ntv::GRAPHICS::DRAW_LIGHT_WITH_RANGE(pos.x, pos.y, pos.z, 255, 0, 0, 10, 10);
			//nob::player::disable_automatic_respawn();
			//nob::sleep(10000);
			//pb.resurrect();
			//nob::ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(pb);
		})
	}),
	list("World", {
		flag("No Man's Island", [](bool val) {
			nob::world::no_mans_island(val);
		}),
		flag("Snowy", [](bool val) {
			nob::world::snowy(val);
		}),
		action("Load All Buildings", []() {
			nob::world::load_all_ilps_ex();
			nob::world::lock_all_doors(false);
		}),
		action("Clean Pickups", []() {
			nob::world::clean_pickups();
		})
	}),
	list("UI", {
		action("Pops", []() {
			nob::ui::info("you know!");

			nob::ui::tip("~b~~h~dog~h~~s~ killed ~r~~h~cat");

			nob::ui::message(
				"CHAR_MARTIN",
				"Martin",
				"~r~I'm a legend!"
			);

			ia_menu.toggle();
		}),
		flag("Banner", [](bool val) {
			if (val) {
				nob::ui::banner("~r~~h~wasted", "you are noob.");
			} else {
				nob::ui::clear_banner();
			}
		}),
		flag("Button Bar", [](bool val) {
			if (val) {
				nob::ui::button_bar({
					{ "first", { nob::hotkey_t::FrontendCancel } },
					{ "second", { nob::hotkey_t::FrontendUp, nob::hotkey_t::FrontendDown } }
				});
			} else {
				nob::ui::clear_button_bar();
			}
		}),
		flag("Show Cursor", [](bool val) {
			if (val) {
				nob::ui::show_cursor();
			} else {
				nob::ui::hide_cursor();
			}
		}),
		flag("Disable Story Features", [](bool val) {
			nob::ui::disable_sp_features(val);
		}),
		flag("Enable MP Frontend Menu", [](bool val) {
			nob::ui::enable_mp_frontend_menu(val);
		}),
		flag("Disable Wheel Slowmo", [](bool val) {
			nob::ui::disable_wheel_slowmo(val);
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

nob::hotkey_listener ia_menu_open_hotkey(
	nob::hotkey_t::InteractionMenu,
	[](nob::hotkey_t, bool down)->bool {
		if (down) {
			ia_menu.open();

			// Because menu's internal hotkey_listener will cancel bubble for hotkey_t::InteractionMenu,
			// so need ia_menu_close_hotkey override it.
			static nob::hotkey_listener ia_menu_close_hotkey;
			ia_menu_close_hotkey = nob::hotkey_listener(
				nob::hotkey_t::InteractionMenu,
				[](nob::hotkey_t, bool down)->bool {
					if (down) {
						ia_menu_close_hotkey.del();
						if (ia_menu.is_opened()) {
							ia_menu.close();
							return false;
						}
					}
					return true; // Bubble to ia_menu_open_hotkey.
				}
			);
		}
		return false;
	},
	true
);
