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
				}));
			}

			nob::vehicle::unlock_banned_vehicles();
			for (auto mn : nob::model::banned_vehicles) {
				li->items.emplace_back(action(nob::i18n::get(mn), mn, [mn]() {
					auto veh = nob::vehicle(mn, nob::player::body().pos({0, 5, 0}));
					veh.place_on_ground();
					veh.set_best_mods();
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
