#pragma once

#include "nob/ntv.hpp"

#include <string>
#include <functional>
#include <vector>
#include <array>
#include <cstring>
#include <thread>

namespace nob {
	void main();
	extern std::thread::id main_thread_id;

	uintptr_t add_frame_task(const std::function<void()> &handler);
	void del_frame_task(uintptr_t id, bool wait_ran = true);
	bool has_frame_task(uintptr_t id);

	void wait(size_t ms);
	inline void wait_next_frame() { wait(0);}
	void wait(const std::function<bool()> &cond);

	// Call on non-main thread
	uintptr_t call_onmt(const std::function<uintptr_t()> &);

	////////////////////////////////////////////////////////////////////////////

	struct vector3 {
		float x, y, z;
	};

	namespace world {
		inline float get_ground_height(const vector3 &coords, bool load_scene = true) {
			float height;
			ntv::GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &height, 0);
			if (load_scene) {
				while (height == 0.0f) {
					ntv::STREAMING::LOAD_SCENE(coords.x, coords.y, coords.z);
					wait(1000);
					ntv::GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, coords.z, &height, 0);
				}
			}
			return height;
		}

		inline vector3 get_ground_pos(const vector3 &coords, bool load_scene = true) {
			return {coords.x, coords.y, get_ground_height(coords, load_scene)};
		}

		void no_man(bool toggle = true);

		inline void clear_black_fog() {
			ntv::UI::_SET_MINIMAP_REVEALED(true);
		}
	}

	class model {
		public:
			uint32_t ntv_model;

			model(const char *name) : ntv_model(ntv::GAMEPLAY::GET_HASH_KEY(name)) {
				if (ntv::STREAMING::IS_MODEL_IN_CDIMAGE(ntv_model) && ntv::STREAMING::IS_MODEL_VALID(ntv_model)) {
					ntv::STREAMING::REQUEST_MODEL(ntv_model);
					do {
						wait_next_frame();
					} while (!ntv::STREAMING::HAS_MODEL_LOADED(ntv_model));
				}
			}

			model(const std::string &name) : model(name.c_str()) {}

			~model() {
				ntv::STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ntv_model);
			}

			////////////////////////////////////////////////////////////////////

			static const std::array<const char *, 696> characters;
			static const std::array<const char *, 696> characters_desc;
			static const std::array<const char *, 400> vehicles;
			static std::vector<std::string> banned_vehicles;
	};

	class character {
		public:
			ntv::Ped ntv_ped;

			character(model m, const vector3 &coords, bool no_brain = false) : ntv_ped(ntv::PED::CREATE_PED(4, m.ntv_model, coords.x, coords.y, coords.z, 0.0f, false, true)) {
				if (no_brain) {
					ntv::PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ntv_ped, true);
					ntv::PED::SET_PED_FLEE_ATTRIBUTES(ntv_ped, 0, 0);
					ntv::PED::SET_PED_COMBAT_ATTRIBUTES(ntv_ped, 292, true);
				}
			}

			character(ntv::Ped ped) : ntv_ped(ped) {}

			void free() {
				ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ntv_ped);
			}

			bool is_dead() {
				return ntv::ENTITY::IS_ENTITY_DEAD(ntv_ped);
			}

			vector3 pos(const vector3 &rcs_offset = {0, 0, 0}) const {
				auto co = ntv::ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ntv_ped, rcs_offset.x, rcs_offset.y, rcs_offset.z);
				return {co.x, co.y, co.z};
			}

			void move(const vector3 &coords) {
				ntv::ENTITY::SET_ENTITY_COORDS(ntv_ped, coords.x, coords.y, coords.z, true, true, true, true);
			}

			void set_random_outfit() {
				ntv::PED::SET_PED_RANDOM_COMPONENT_VARIATION(ntv_ped, false);
			}

			void set_default_outfit() {
				ntv::PED::SET_PED_DEFAULT_COMPONENT_VARIATION(ntv_ped);
			}

			void set_last_outfit() {
				for (int i = 0; i < 12; i++) {
					for (int d = ntv::PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ntv_ped, i) - 1; d >= 0; d--) {
						for (int t = ntv::PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ntv_ped, i, d) - 1; t >= 0; t--) {
							if (ntv::PED::IS_PED_COMPONENT_VARIATION_VALID(ntv_ped, i, d, t)) {
								ntv::PED::SET_PED_COMPONENT_VARIATION(ntv_ped, i, d, t, 0);
								break;
							}
						}
					}
				}
			}

			vector3 get_rotation() const {
				auto ro = ntv::ENTITY::GET_ENTITY_ROTATION(ntv_ped, 2);
				return {ro.x, ro.y, ro.z};
			}

			void set_rotation(const vector3 &ro) {
				ntv::ENTITY::SET_ENTITY_ROTATION(ntv_ped, ro.x, ro.y, ro.z, 2, true);
			}

			void show_name(const std::string &name, const std::string &tag = "") {
				auto id = ntv::UI::_CREATE_MP_GAMER_TAG(ntv_ped, name.c_str(), true, true, tag.c_str(), 0);
				ntv::UI::SET_MP_GAMER_TAG_VISIBILITY(id, 0, true);
			}
	};

	namespace player {
		extern ntv::Player ntv_player;

		inline character controlling() {
			return ntv::PLAYER::PLAYER_PED_ID();
		}

		inline void control(character chr) {
			ntv::PLAYER::CHANGE_PLAYER_PED(ntv_player, chr.ntv_ped, true, true);
		}

		inline void possession(character chr) {
			auto old_chr = controlling();
			auto old_chr_coords = old_chr.pos({ 0, 0, 0 });
			auto chr_coords = chr.pos({ 0, 0, 0 });

			int st = ntv::STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(old_chr_coords.x, old_chr_coords.y, old_chr_coords.z, chr_coords.x, chr_coords.y, chr_coords.z);
			ntv::STREAMING::START_PLAYER_SWITCH(old_chr.ntv_ped, chr.ntv_ped, 0, st);

			wait(1000);

			if (!ntv::ENTITY::IS_ENTITY_DEAD(chr.ntv_ped)) {
				control(chr);
				ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&old_chr.ntv_ped);
			}
		}
	}

	class vehicle {
		public:
			ntv::Vehicle ntv_vehicle;

			vehicle(model m, const vector3 &coords) : ntv_vehicle(ntv::VEHICLE::CREATE_VEHICLE(m.ntv_model, coords.x, coords.y, coords.z, 0.0, false, true)) {
				ntv::VEHICLE::SET_VEHICLE_MOD_KIT(ntv_vehicle, 0);
			}

			void free() {
				ntv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&ntv_vehicle);
			}

			void place_on_ground() {
				ntv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(ntv_vehicle);
			}

			int get_mod_type_total() {
				return 50;
			}

			int get_mod_total(int mod_type) {
				return ntv::VEHICLE::GET_NUM_VEHICLE_MODS(ntv_vehicle, mod_type);
			}

			void set_mod(int mod_type, int mod) {
				ntv::VEHICLE::SET_VEHICLE_MOD(ntv_vehicle, mod_type, mod, true);
			}

			void get_mod(int mod_type) {
				ntv::VEHICLE::GET_VEHICLE_MOD(ntv_vehicle, mod_type);
			}

			void set_best_mod() {
				for (size_t i = 0; i < 50; i++) {
					auto n = get_mod_total(i);
					if (n > 0) {
						ntv::VEHICLE::SET_VEHICLE_MOD(ntv_vehicle, i, n - 1, false);
					}
				}
			}

			////////////////////////////////////////////////////////////////////

			static void unlock_banned_vehicles();
	};

	namespace g2d {
		inline void text(
			float x, float y, float height,
			const char *str,
			float scale,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a,
			uint8_t align = 0,
			bool outline = false
		) {
			float nx;
			if (align) {
				nx = x + height / 2;
			} else {
				nx = x;
			}

			ntv::UI::SET_TEXT_FONT(0);
			ntv::UI::SET_TEXT_SCALE(scale, scale);
			ntv::UI::SET_TEXT_COLOUR(r, g, b, a);
			ntv::UI::SET_TEXT_WRAP(x, x + height);
			switch (align) {
				case 1:
					ntv::UI::SET_TEXT_CENTRE(true);
					break;
				case 2:
					ntv::UI::SET_TEXT_RIGHT_JUSTIFY(true);
			}
			if (outline) ntv::UI::SET_TEXT_OUTLINE();
			ntv::UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);

			ntv::UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str);
			ntv::UI::END_TEXT_COMMAND_DISPLAY_TEXT(nx, y);
		}

		inline void text(
			float x, float y, float height,
			const std::string &str,
			float scale,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a,
			uint8_t align = 0,
			bool outline = false
		) {
			text(x, y, height, str.c_str(), scale, r, g, b, a, align, outline);
		}

		inline void rect(
			float x, float y, float width, float height,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a
		) {
			ntv::GRAPHICS::DRAW_RECT((x + (width * 0.5f)), (y + (height * 0.5f)), width, height, r, g, b, a);
		}
	} /* g2d */

	namespace ui {
		struct component {
			std::string name;
			std::string desc;
		};

		struct item : public component {
			std::function<void()> action;
		};

		struct list : public component {
			std::vector<item> items;
			size_t selected = 0;
		};

		struct option_list : public list {
			std::function<void()> on_select;
		};

		void open_menu(const std::string &title, const list &);
		void close_menu();

		////////////////////////////////////////////////////////////////////////

		inline void tip(const std::string &content) {
			ntv::UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(content.c_str());
			ntv::UI::_DRAW_NOTIFICATION(false, false);
		}

		enum class msg_icon : int {
			none,
			chat_box,
			email,
			add_friend_request,
			//4
			//5
			//6
			right_jumping_arrow = 7,
			rp,
			money
		};

		inline void message(
			const std::string &pic,
			const std::string &sender,
			const std::string &content,
			float duration = 1.0f,
			msg_icon subject_icon = msg_icon::none, msg_icon sender_icon = msg_icon::none,
			const std::string &sender_tag = "",
			const std::string &subject = ""
		) {
			ntv::UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(content.c_str());
			ntv::UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2(pic.c_str(), pic.c_str(), false, (int)sender_icon, sender.c_str(), subject.c_str(), duration, sender_tag.c_str(), (int)subject_icon, 0);
			ntv::UI::_DRAW_NOTIFICATION(false, false);
		}

		////////////////////////////////////////////////////////////////////////

		inline void info_this_frame(const std::string &content) {
			ntv::UI::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(content.c_str());
			ntv::UI::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
		}

		inline void info(const std::string &content, float duration = 1.0f) {
			auto ft = add_frame_task([content]() {
				info_this_frame(content);
			});
			auto ft2 = new uintptr_t;
			*ft2 = add_frame_task([ft, ft2, duration]() {
				wait(duration * 15000);
				del_frame_task(ft);
				del_frame_task(*ft2);
				delete ft2;
			});
		};

		////////////////////////////////////////////////////////////////////////

		void disable_story_features(bool toggle = true);
		void disable_wheel_slowmo(bool toggle = true);
	} /* ui */

	namespace i18n {
		inline std::string get(const char *n) {
			return ntv::UI::_GET_LABEL_TEXT(n);
		}
		inline std::string get(const std::string &n) {
			return ntv::UI::_GET_LABEL_TEXT(n.c_str());
		}
		inline std::string get_vehicle_mod_type(vehicle v, int mod_type) {
			return ntv::VEHICLE::GET_MOD_SLOT_NAME(v.ntv_vehicle, mod_type);
		}
		inline std::string get_vehicle_mod(vehicle v, int mod_type, int mod) {
			return ntv::VEHICLE::GET_MOD_TEXT_LABEL(v.ntv_vehicle, mod_type, mod);
		}
	} /* i18n */
}
