#include <nob.hpp>
#include <nob/hack.hpp>

#include <memory>
#include <cstring>

size_t fps;
size_t fps_count;

void nob::main() {
	world::no_man();
	world::clear_black_fog();
	ui::disable_story_features();
	ui::disable_wheel_slowmo();
	vehicle::unlock_banned_vehicles();

	if (ntv::CAM::IS_SCREEN_FADED_OUT()) {
		wait(ntv::CAM::IS_SCREEN_FADING_IN);
	}

	auto plr_chr = player::controlling();

	ntv::ENTITY::SET_ENTITY_INVINCIBLE(plr_chr.ntv_ped, TRUE);

	auto veh = vehicle("MOLOTOK", plr_chr.pos({0, 10, 0}));
	veh.place_on_ground();
	veh.set_best_mod();

	if (ntv::func_table) {
		auto f = ntv::func_table[0xC20B73867395D06D]; //ntv::ENTITY::SET_ENTITY_INVINCIBLE(veh.ntv_vehicle, TRUE);
		if (f) {
			auto p = new uintptr_t[16]{(uintptr_t)veh.ntv_vehicle, 1};
			ntv::func_table_t::node_t::call_context_t cc = {
				p,
				2,
				p,
				0
			};
			f(&cc);
			delete p;
		}
	}

	ui::info("you know!");

	ui::tip("~b~dog~s~ killed ~r~cat");

	ui::message(
		"CHAR_MARTIN",
		"馬丁",
		"~r~你們休想取代我！"
	);

	fps = 0;
	fps_count = 0;

	add_frame_task([]() {
		wait(1000);
		fps = fps_count;
		fps_count = 0;
	});

	add_frame_task([]() {
		++fps_count;
		char str_buf[5];
		itoa(fps, str_buf, 10);
		g2d::text(0, 0.9, 1, str_buf, 0.85, 255, 255, 255, 255, 1, true);
	});
}
