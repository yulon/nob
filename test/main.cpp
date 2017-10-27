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
					auto veh = nob::vehicle(mn, nob::player::body()->pos({0, 5, 0}));
					veh->place_on_ground();
					veh->set_best_mods();
				}));
			}

			nob::vehicle::unlock_banned_vehicles();
			for (auto mn : nob::model::banned_vehicles) {
				li->items.emplace_back(action(nob::i18n::get(mn), mn, [mn]() {
					auto veh = nob::vehicle(mn, nob::player::body()->pos({0, 5, 0}));
					veh->place_on_ground();
					veh->set_best_mods();
				}));
			}

			li->on_show = nullptr;
		})
	}),
	list("World", {
		flag("Clean NPCs", [](bool val) {
			nob::world::clean_npcs(val);
		}),
		action("Clear Black Fog", []() {
			nob::world::clear_black_fog();
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
			info("you know!");

			tip("~b~~h~dog~h~~s~ killed ~r~~h~cat");

			message(
				"CHAR_MARTIN",
				"馬丁",
				"~r~你們休想取代我！"
			);

			ia_menu.toggle();
		})
	}),
	list("Other", {
		action("Char", []() {
			auto plr_chr = nob::player::body();
			auto pos = plr_chr->pos();
			auto chr = nob::character("s_m_m_movalien_01", nob::world::get_ground_pos({pos.x + 5, pos.y, pos.z + 10}), true);
			auto old_h = std::make_shared<float>(nob::ntv::ENTITY::GET_ENTITY_HEADING(plr_chr->native_handle()));

			nob::task([chr, plr_chr, old_h]() mutable {
				//if (!nob::ntv::AI::IS_PED_STILL(plr_chr->native_handle())) {
					float h = nob::ntv::ENTITY::GET_ENTITY_HEADING(plr_chr->native_handle());
					if (h != *old_h) {
						auto pos = plr_chr->pos({0, 10, 0});
						chr->face({pos.x + 5, pos.y, pos.x}, h);
						*old_h = h;
					}
				//}
			});

			nob::task([chr, plr_chr]() mutable {
				if (nob::ntv::AI::IS_PED_STILL(plr_chr->native_handle())) {
					std::cout << std::endl << "IS_PED_STILL" << std::endl;
					chr->still();
					nob::wait([plr_chr]()->bool {
						return !nob::ntv::AI::IS_PED_STILL(plr_chr->native_handle());
					});
					return;
				}

				if (nob::ntv::PED::IS_PED_JUMPING(plr_chr->native_handle())) {
					chr->jump();
					nob::wait([plr_chr]()->bool {
						return !nob::ntv::PED::IS_PED_JUMPING(plr_chr->native_handle());
					});
					/*auto check_still = nob::task([plr_chr, chr](nob::task tt) mutable {
						auto pos = plr_chr->pos();
						nob::wait_next_frame();
						auto new_pos = plr_chr->pos();
						if (
							static_cast<int>(new_pos.x) == static_cast<int>(pos.x) &&
							static_cast<int>(new_pos.y) == static_cast<int>(pos.y) &&
							static_cast<int>(new_pos.z) == static_cast<int>(pos.z)
						) {
							chr->still();
							tt.del();
							return;
						}
					});*/
					if (nob::ntv::AI::IS_PED_WALKING(plr_chr->native_handle())) {
						nob::wait([plr_chr]()->bool {
							return !nob::ntv::AI::IS_PED_WALKING(plr_chr->native_handle());
						});
					} else if (nob::ntv::AI::IS_PED_RUNNING(plr_chr->native_handle())) {
						nob::wait([plr_chr]()->bool {
							return !nob::ntv::AI::IS_PED_RUNNING(plr_chr->native_handle());
						});
					} else if (nob::ntv::AI::IS_PED_SPRINTING(plr_chr->native_handle())) {
						nob::wait([plr_chr]()->bool {
							return !nob::ntv::AI::IS_PED_SPRINTING(plr_chr->native_handle());
						});
					}
					return;
				}

				if (nob::ntv::AI::IS_PED_WALKING(plr_chr->native_handle())) {
					chr->run(nob::character::speed_walk);
					return;
				} else if (nob::ntv::AI::IS_PED_RUNNING(plr_chr->native_handle())) {
					chr->run(nob::character::speed_run);
					return;
				} else if (nob::ntv::AI::IS_PED_SPRINTING(plr_chr->native_handle())) {
					chr->run(nob::character::speed_sprint);
					return;
				}
			});
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
