#include <nob.hpp>

#include <minhook.hpp>
#include <rua/observer.hpp>

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
	nob::g2d::draw_text(0, 0.93, 1, ss.str().c_str(), 0.4, 255, 255, 255, 255, 1, true);
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

nob::on_load_task unlock_vehs(nob::unlock_banned_vehicles);
/*
nob::on_load_task blk([]() {
	nob::player::switch_scene(nob::vector3{0, 0, 75});

	while (*nob::ntv::game_state != nob::ntv::game_state_t::playing) {
		nob::yield();
	}

	nob::player::switch_scene_finish();
});
//*/

using namespace nob::ui;

void add_veh(list &li, const nob::model &m) {
	li->items.emplace_back(action(nob::i18n(m.display_name_for_vehicle()), m.name(), [m]() {
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
		}),
		list("Last", [](list li) {
			li->items.clear();

			auto veh = nob::player::body().last_vehicle();

			li->items.emplace_back(list("Mod", [veh](list li) mutable {
				for (int i = 0; i < veh.mod_type_sum; ++i) {
					if (!veh.mod_sum(i)) {
						continue;
					}
					auto mod_type_name = nob::i18n(veh.mod_type_name(i));
					li->items.emplace_back(list(mod_type_name, [veh, i](list li) mutable {
						for (int j = -1; j < veh.mod_sum(i); ++j) {
							auto mod_name = nob::i18n(veh.mod_name(i, j));
							li->items.emplace_back(action(mod_name, [veh, i, j]() mutable {
								veh.mod(i, j);
							}));
						}
						li->on_show = nullptr;
					}));
				}
				li->on_show = nullptr;
			}));
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
				auto di = nob::arm::display_info(wpn);
				li->items.emplace_back(action(nob::i18n(di.name), nob::i18n(di.desc), [&wpn]() {
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
									pb.move(dest(rot));
									pb.rotation(rot);
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
					if (pb.is_in_vehicle()) {
						nob::character::movement_t mm;
						static_cast<nob::entity::movement_t &>(mm) = pb.current_vehicle().movement();
						mm.motion_state = nob::character::motion_state_t::null;
						rec.emplace(mm);
					} else {
						rec.emplace(pb.movement());
					}
				});
			} else {
				if (tsk) {
					tsk.del();
					nob::ui::tip("record done!");
					return;
				}
				nob::yield();
				nob::task([pb]() mutable {
					if (rec.size()) {
						if (pb.is_in_vehicle()) {
							pb.current_vehicle().movement(rec.front());
							pb.current_vehicle().action(32);
						} else {
							static_cast<nob::entity &>(pb).movement(rec.front());
						}
						rec.pop();
					} else {
						if (pb.is_in_vehicle()) {
							//pb.current_vehicle().physics_collidable(true);
						} else {
							nob::ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(pb);
						}
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
			static minhook<nob::ntv::func_t> hkd;
			nob::log(hkd.install(
				nob::ntv::AI::TASK_PLAY_ANIM_ADVANCED.target(),
				[](nob::ntv::call_context_t &cc) {
					nob::log(cc.arg<char *>(1), ", ", cc.arg<char *>(2));
					hkd.original(cc);
				}
			));
		}),
		action("Make Nodes", []() {
			std::fstream f("wpn_nodes.inc", std::ios_base::binary | std::ios_base::trunc | std::ios_base::in | std::ios_base::out);
			if (!f.is_open()) {
				nob::log("failed to open");
			}

			std::mt19937_64 rd_ng(20180129);
			std::uniform_real_distribution<float> dis_x(nob::map::x_min, nob::map::x_max);
			std::uniform_real_distribution<float> dis_y(nob::map::y_min, nob::map::y_max);

			auto pb = nob::player::body();

			for (size_t i = 0; i < 2000; ++i) {
				nob::vector3 pos{dis_x(rd_ng), dis_y(rd_ng), 1000.f};

				bool ctn = false;
				auto h = nob::world::ground_height(pos);
				while (!h) {
					if (pos.z <= 0) {
						ctn = true;
						break;
					}
					pos.z -= 200;
					pb.move(pos);

					nob::sleep(500);
					h = nob::world::ground_height(pos);
				}
				if (ctn) {
					continue;
				}

				float wh;
				nob::ntv::WATER::GET_WATER_HEIGHT_NO_WAVES(pos.x, pos.y, pos.z, &wh);
				if (wh > h) {
					continue;
				}

				auto mkr = nob::map::marker(pos);
				mkr.graphic(357);
				mkr.keep_track(false);
				f << "{ " << pos.x << ", " << pos.y << ", " << pos.z << " }," << std::endl;
			}

			/*
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
			static auto pb = nob::player::body();

			nob::ui::tip(nob::ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(nob::hash("WEAPON_RPG")));
			nob::ui::tip(nob::i18n("WTD_SNIP_RIF"));


/*			nob::ntv::STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
			while (!nob::ntv::STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core")) {
				nob::yield();
			}
			nob::ntv::GRAPHICS::_USE_PARTICLE_FX_ASSET_NEXT_CALL("core");// scr_rcbarry1 scr_alien_charging scr_alien_impact scr_alien_teleport scr_alien_disintegrate
			//nob::task([]() {
				auto pos = pb.pos();
				auto h = nob::ntv::GRAPHICS::START_PARTICLE_FX_LOOPED_AT_COORD("veh_light_amber", pos.x, pos.y, pos.z, 0.f, 0.f, 0.f, 0.5f, 0, 0, 0, 0);
			//});

			nob::ntv::GRAPHICS::_SET_PARTICLE_FX_LOOPED_RANGE(h, 5000.f);

			for (size_t i = 0; i < nob::ntv::script_list->size; ++i) {
				if (nob::ntv::script_list->scripts[i]) {
					nob::log("scr: ", nob::ntv::script_list->scripts[i].hash);
					for (size_t j = 0; j < nob::ntv::script_list->scripts[i].info->local_count; ++j) {
						if (nob::ntv::script_list->scripts[i].info->local_pages[j]) {
							nob::log("  ", nob::ntv::script_list->scripts[i].info->local_pages[j]);
						}
					}
					nob::log("=============================");
				}
				nob::yield();
			}
			//nob::ntv::AUDIO::_FORCE_VEHICLE_ENGINE_AUDIO(pb.last_vehicle(), "ADDER");
			//nob::ntv::VEHICLE::SET_VEHICLE_FORWARD_SPEED(pb.last_vehicle(), 5.f);

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

			nob::ntv::FIRE::ADD_OWNED_EXPLOSION(
				pb, pos.x, pos.y, pos.z, (int)nob::ntv::eExplosionType::Flare,
				0, true, false, 0
			);



			nob::ntv::VEHICLE::DISABLE_VEHICLE_WEAPON(true, 0xca46f87d, pb.current_vehicle(), pb);

			//auto pos = pb.pos({0, 20, 0});
			//nob::ntv::GRAPHICS::DRAW_LIGHT_WITH_RANGE(pos.x, pos.y, pos.z, 255, 0, 0, 10, 10);
			//nob::player::disable_automatic_respawn();
			//nob::sleep(10000);
			//pb.resurrect();
			//nob::ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(pb);*/
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

			nob::ui::menu::close_any();
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
			ia_menu.toggle();
		}
		return false;
	},
	true
)/*,
veh(
	{
		nob::hotkey_t::VehicleMoveUp,
		nob::hotkey_t::VehicleMoveUpOnly,
		nob::hotkey_t::VehicleSlowMoUpOnly
	},
	[](nob::hotkey_t hk, bool down)->bool {
		if (down) {
			switch (hk) {
				case nob::hotkey_t::VehicleAccelerate:
					nob::log("VehicleAccelerate");
					break;
				case nob::hotkey_t::VehicleBrake:
					nob::log("VehicleBrake");
					break;
				case nob::hotkey_t::VehicleDuck:
					nob::log("VehicleDuck");
					break;
				default:
					break;
			}
		}
		return false;
	},
	false
)*/;
