#include <nob.hpp>

#include <memory>
#include <cstring>

size_t fps;
size_t fps_count;

void nob::main() {
	shv::UI::_SET_MINIMAP_REVEALED(TRUE);

	wait(10000);

	auto krm_m = model("KURUMA2");
	auto krm = vehicle(krm_m, player::controlling().pos({0, 10, 0}));
	krm.place_on_ground();
	wait_next_frame();
	krm_m.free();

	fps = 0;
	fps_count = 0;

	add_frame_task([]() {
		++fps_count;
	});

	add_frame_task([]() {
		wait(1000);
		fps = fps_count;
		fps_count = 0;
	});

	add_frame_task([]() {
		shv::UI::SET_TEXT_FONT(1);
		shv::UI::SET_TEXT_SCALE(0.85, 0.85);
		shv::UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		shv::UI::SET_TEXT_WRAP(0.0, 1.0);
		shv::UI::SET_TEXT_CENTRE(TRUE);
		shv::UI::SET_TEXT_DROPSHADOW(5, 0, 0, 0, 255);
		shv::UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);

		char str_buf[5];
		itoa(fps, str_buf, 10);

		shv::UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT((char *)"STRING");
		shv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str_buf);
		shv::UI::END_TEXT_COMMAND_DISPLAY_TEXT(0.5, 0.9);
	});
}
