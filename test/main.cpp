#include <nob.hpp>

#include <cstring>
#include <cstdlib>

size_t fps = 0;
size_t fps_count = 0;

nob::task fps_zeroing([]() {
	nob::wait(1000);
	fps = fps_count;
	fps_count = 0;
});

nob::task fps_output([]() {
	++fps_count;
	char str_buf[5];
	itoa(fps, str_buf, 10);
	nob::g2d::text(0, 0.9, 1, str_buf, 0.85, 255, 255, 255, 255, 1, true);
});

using namespace nob::ui;

nob::initer disable_ntv_ia_menu([]() {
	disable_interaction_menu();
});

menu ia_menu("Nob Tester", list("Interaction Menu", {
	list("Vehicle", {
		list("Spawn", [](list li) {
			for (auto mn : nob::model::vehicles) {
				li->items.emplace_back(action(nob::i18n::get(mn), mn, [mn]() {
					auto veh = nob::vehicle(mn, nob::player::body().pos({0, 5, 0}));
					veh.place_on_ground();
					veh.set_best_mods();
					veh.invincible();
				}));
			}

			nob::vehicle::unlock_banned_vehicles();
			for (auto mn : nob::model::banned_vehicles) {
				li->items.emplace_back(action(nob::i18n::get(mn), mn, [mn]() {
					auto veh = nob::vehicle(mn, nob::player::body().pos({0, 5, 0}));
					veh.place_on_ground();
					veh.set_best_mods();
					veh.invincible();
				}));
			}

			li->on_show = nullptr;
		})
	}),
	list("Player", {
		flag("Invincible", [](bool val) {
			nob::player::body().invincible(val);
		}),
		flag("Auto Get Parachute in Plane", [](bool val) {
			nob::ntv::PLAYER::SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(0, val);
		}),
		action("State Capturer", []() {
			/*auto plr_chr = nob::player::body();
			auto pos = plr_chr.pos();
			auto chr = nob::character("s_m_m_movalien_01", nob::world::get_ground_pos({pos.x + 5, pos.y, pos.z + 10}), true);
			auto old_h = std::make_shared<float>(nob::ntv::ENTITY::GET_ENTITY_HEADING(plr_chr.native_handle()));

			nob::task([chr, plr_chr, old_h]() mutable {
				//if (!nob::ntv::AI::IS_PED_STILL(plr_chr.native_handle())) {
					float h = nob::ntv::ENTITY::GET_ENTITY_HEADING(plr_chr.native_handle());
					if (h != *old_h) {
						auto pos = plr_chr.pos({0, 10, 0});
						chr.face({pos.x + 5, pos.y, pos.x}, h);
						*old_h = h;
					}
				//}
			});

			plr_chr.on_motion([](nob::character::motion_state ms) {
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
			disable_story_features(val);
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
