#include <nob.hpp>
#include <nob/hack.hpp>

#include <memory>
#include <cstring>
#include <iostream>
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

using c = nob::ui::component;

nob::ui::menu ia_menu("Nob Tester", c::list("Interaction Menu", {
	c::list("UI", {
		c::action("info", []() {
			nob::ui::info("you know!");
		}),
		c::action("tip", []() {
			nob::ui::tip("~b~~h~dog~h~~s~ killed ~r~~h~cat");
		}),
		c::action("message", []() {
			nob::ui::message(
				"CHAR_MARTIN",
				"馬丁",
				"~r~你們休想取代我！"
			);
		})
	}),
	c::list("Vehicle", {
		c::list("Spawn", [](c::list li) {
			/*for (auto mn : nob::model::vehicles) {
				li->components.push_back(c::action(mn, [mn]() {
					auto veh = nob::vehicle(mn, nob::player::body().pos({0, 5, 0}));
					veh.place_on_ground();
				}));
			}*/

			nob::vehicle::unlock_banned_vehicles();
			for (auto mn : nob::model::banned_vehicles) {
				li->components.push_back(c::action(nob::i18n::get(mn), [mn]() {
					auto veh = nob::vehicle(mn, nob::player::body().pos({0, 5, 0}));
					veh.place_on_ground();
					veh.set_best_mods();
				}));
			}

			li->on_show = nullptr;
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

nob::initer main_initer([]() {
	nob::world::clean_npcs();
	nob::world::clear_black_fog();
	nob::ui::disable_interaction_menu();
	nob::ui::disable_story_features();
	nob::ui::disable_wheel_slowmo();

	if (nob::ntv::CAM::IS_SCREEN_FADED_OUT()) {
		nob::wait(nob::ntv::CAM::IS_SCREEN_FADING_IN);
	}
});
