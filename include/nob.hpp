#pragma once

#include "nob/ntv.hpp"

#include <string>
#include <functional>
#include <vector>
#include <array>
#include <cstring>
#include <thread>
#include <stack>
#include <initializer_list>
#include <typeinfo>
#include <list>
#include <memory>
#include <iostream>

#define _NOB_SHARED_OBJ(T) \
		prototype *operator->() { \
			return _this.get(); \
		} \
		\
		std::shared_ptr<prototype> get() { \
			return _this; \
		} \
		\
		T(const T &src) : _this(src._this) {} \
		\
		T(T &&src) : _this(std::move(src._this)) {} \
		\
		const T &operator=(const T &src) { \
			_this = src._this; \
			return *this; \
		} \
		\
		const T &operator=(T &&src) { \
			_this = std::move(src._this); \
			return *this; \
		} \
		\
		T(const std::shared_ptr<prototype> &ptr) : _this(ptr) {} \
		\
		T(std::shared_ptr<prototype> &&ptr) : _this(std::move(ptr)) {} \
		\
		const T &operator=(const std::shared_ptr<prototype> &ptr) { \
			_this = ptr; \
			return *this; \
		} \
		\
		const T &operator=(std::shared_ptr<prototype> &&ptr) { \
			_this = std::move(ptr); \
			return *this; \
		} \
		\
	private: \
		std::shared_ptr<prototype> _this;

namespace nob {
	namespace this_script {
		extern std::thread::id thread_id;
		extern bool running;
		extern bool asi_mode;
	} /* this_script */

	void wait(size_t ms);
	inline void wait_next_frame() { wait(0); }
	void wait(const std::function<bool()> &cond);

	void wait_s(size_t ms);
	inline void wait_next_frame_s() { wait_s(0); }
	void wait_s(const std::function<bool()> &cond);

	class task {
		public:
			task(const std::function<void()> &);

			task(const std::function<void(task)> &);

			operator bool() const;

			void del();

			////////////////////////////////////////////////////////////////////

			struct _info; _info *_inf; constexpr task(_info *p = nullptr) : _inf(p) {}
	};

	task this_task();

	class initer {
		public:
			initer(const std::function<void()> &);
			initer(const std::function<void(initer)> &);
	};

	// Call on non-main thread
	uintptr_t call_onmt(const std::function<uintptr_t()> &);

	namespace keyboard {
		class listener {
			public:
				listener() : _null(true) {}

				listener(const std::function<bool(int code, bool down)> &);

				listener(listener &&);

				const listener &operator=(listener &&);

				~listener() {
					del();
				}

				void del();

			private:
				std::list<std::function<bool(int, bool)>>::iterator _it;
				bool _null;
		};

		bool is_down(int code);
	} /* keyboard */

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

		void clean_npcs(bool toggle = true);

		inline void clear_black_fog() {
			ntv::UI::_SET_MINIMAP_REVEALED(true);
		}

		inline void emp(bool toggle) {
			ntv::GRAPHICS::_SET_BLACKOUT(toggle);
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

			character(model m, const vector3 &coords, bool player_shadow = false) : ntv_ped(ntv::PED::CREATE_PED(4, m.ntv_model, coords.x, coords.y, coords.z, 0.0f, false, true)) {
				if (player_shadow) {
					ntv::PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ntv_ped, true);
					ntv::PED::SET_PED_FLEE_ATTRIBUTES(ntv_ped, 0, 0);
					ntv::PED::SET_PED_COMBAT_ATTRIBUTES(ntv_ped, 292, true);
					ntv::PED::SET_PED_DIES_INSTANTLY_IN_WATER(ntv_ped, false);
					ntv::PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(ntv_ped, 1); // Blocks ragdolling when shot.
					ntv::WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(ntv_ped, false);
				}
				ntv::PED::SET_PED_CONFIG_FLAG(ntv_ped, 281, true); // PED_FLAG_NO_WRITHE
			}

			character(ntv::Ped ped) : ntv_ped(ped) {}

			void del() {
				ntv::PED::DELETE_PED(&ntv_ped);
			}

			void remove() {
				ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ntv_ped);
			}

			bool is_dead() {
				return ntv::ENTITY::IS_ENTITY_DEAD(ntv_ped);
			}

			void resurrect() {
				ntv::ENTITY::SET_ENTITY_HEALTH(ntv_ped, ntv::ENTITY::GET_ENTITY_MAX_HEALTH(ntv_ped));
				ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(ntv_ped);
				ntv::ENTITY::SET_ENTITY_COLLISION(ntv_ped, true, true);
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
	};

	namespace player {
		extern ntv::Player ntv_player;

		inline character body() {
			return ntv::PLAYER::PLAYER_PED_ID();
		}

		inline void change_body(character chr) {
			ntv::PLAYER::CHANGE_PLAYER_PED(ntv_player, chr.ntv_ped, true, true);
		}

		inline void switch_body(character chr) {
			auto old_chr = body();
			auto old_chr_coords = old_chr.pos({ 0, 0, 0 });
			auto chr_coords = chr.pos({ 0, 0, 0 });

			int st = ntv::STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(old_chr_coords.x, old_chr_coords.y, old_chr_coords.z, chr_coords.x, chr_coords.y, chr_coords.z);
			ntv::STREAMING::START_PLAYER_SWITCH(old_chr.ntv_ped, chr.ntv_ped, 0, st);

			wait(1000);

			if (ntv::ENTITY::DOES_ENTITY_EXIST(chr.ntv_ped) && !ntv::ENTITY::IS_ENTITY_DEAD(chr.ntv_ped)) {
				change_body(chr);
				old_chr.remove();
			}
		}
	}

	class vehicle {
		public:
			ntv::Vehicle ntv_vehicle;

			vehicle(model m, const vector3 &coords, float heading = 0.0f) : ntv_vehicle(ntv::VEHICLE::CREATE_VEHICLE(m.ntv_model, coords.x, coords.y, coords.z, heading, false, true)) {
				ntv::VEHICLE::SET_VEHICLE_MOD_KIT(ntv_vehicle, 0);
			}

			void del() {
				ntv::VEHICLE::DELETE_VEHICLE(&ntv_vehicle);
			}

			void remove() {
				ntv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&ntv_vehicle);
			}

			void place_on_ground() {
				ntv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(ntv_vehicle);
			}

			int get_mod_type_sum() {
				return 50;
			}

			int get_mod_sum(int mod_type) {
				return ntv::VEHICLE::GET_NUM_VEHICLE_MODS(ntv_vehicle, mod_type);
			}

			void set_mod(int mod_type, int mod) {
				ntv::VEHICLE::SET_VEHICLE_MOD(ntv_vehicle, mod_type, mod, true);
			}

			void get_mod(int mod_type) {
				ntv::VEHICLE::GET_VEHICLE_MOD(ntv_vehicle, mod_type);
			}

			void set_best_mods() {
				for (int i = 0; i < get_mod_type_sum(); i++) {
					auto n = get_mod_sum(i);
					if (n > 0) {
						ntv::VEHICLE::SET_VEHICLE_MOD(ntv_vehicle, i, n - 1, false);
					}
				}
			}

			bool has(const character &chr) {
				return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(chr.ntv_ped, ntv_vehicle);
			}

			bool is_playing_radio() {
				return ntv::AUDIO::_IS_VEHICLE_RADIO_LOUD(ntv_vehicle);
			}

			std::string get_radio_station() {
				if (has(player::body()) && is_playing_radio()) {
					return ntv::AUDIO::GET_PLAYER_RADIO_STATION_NAME();
				}
				return nullptr;
			}

			void set_radio_station(const std::string &radio_station = nullptr) {
				if (radio_station.empty()) {
					if (is_playing_radio()) {
						ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(ntv_vehicle, false);
					}
					return;
				}
				if (!is_playing_radio()) {
					ntv::AUDIO::SET_VEHICLE_RADIO_LOUD(ntv_vehicle, true);
				}
				ntv::AUDIO::SET_VEH_RADIO_STATION(ntv_vehicle, radio_station.c_str());
			}

			////////////////////////////////////////////////////////////////////

			static void unlock_banned_vehicles();
	};

	namespace g2d {
		inline void text(
			float x, float y, float width,
			const std::string &str,
			float size,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a,
			uint8_t align = 0,
			bool outline = false
		) {
			float nx;
			if (align) {
				nx = x + width / 2;
			} else {
				nx = x;
			}

			ntv::UI::SET_TEXT_FONT(0);
			ntv::UI::SET_TEXT_SCALE(1.0f, size);
			ntv::UI::SET_TEXT_COLOUR(r, g, b, a);
			ntv::UI::SET_TEXT_WRAP(x, x + width);
			switch (align) {
				case 1:
					ntv::UI::SET_TEXT_CENTRE(true);
					break;
				case 2:
					ntv::UI::SET_TEXT_RIGHT_JUSTIFY(true);
			}
			if (outline) ntv::UI::SET_TEXT_OUTLINE();

			ntv::UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(str.c_str());
			ntv::UI::END_TEXT_COMMAND_DISPLAY_TEXT(nx, y);
		}

		constexpr float calc_text_height(float size) {
			return (((((38.0f + 42.0f) / 0.9f) / 105.0f) * 0.1f) * size);
		}

		inline void rect(
			float x, float y, float width, float height,
			uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 255
		) {
			ntv::GRAPHICS::DRAW_RECT((x + (width / 2)), (y + (height / 2)), width, height, r, g, b, a);
		}

		inline void wait_texture_dict_valid(const char *texture_dict) {
			if (!ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture_dict)) {
				ntv::GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(texture_dict, false);
				wait([texture_dict]()->bool {
					return ntv::GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(texture_dict);
				});
			}
		}

		inline void sprite(const char *texture_dict, const char *texture_name, float x, float y, float width, float height, uint8_t a = 255) {
			ntv::GRAPHICS::DRAW_SPRITE(texture_dict, texture_name, (x + (width / 2)), (y + (height / 2)), width, height, 0.0f, 255, 255, 255, a);
		}
	} /* g2d */

	namespace ui {
		class component {
			public:
				class base {
					public:
						struct prototype {
							std::string name;
							std::string desc;
						};

						base(
							const std::string &name,
							const std::string &desc = ""
						) : _this(std::make_shared<prototype>()) {
							_this->name = name;
							_this->desc = desc;
						}

						_NOB_SHARED_OBJ(base)
				};

				class action {
					public:
						struct prototype : base::prototype {
							std::function<void()> handler;
						};

						action(
							const std::string &name,
							const std::function<void()> &handler,
							const std::string &desc = ""
						) : _this(std::make_shared<prototype>()) {
							_this->name = name;
							_this->desc = desc;
							_this->handler = handler;
						}

						_NOB_SHARED_OBJ(action)
				};

				class list {
					public:
						struct prototype : base::prototype {
							std::vector<component> components;
							std::function<void(list)> on_show;
							size_t selected;
							size_t start;

							void fix_start() {
								auto sz = components.size();
								if (sz > 10) {
									if (start > selected) {
										start = selected;
									} else if (selected - start > 9) {
										auto min_start = selected - 9;
										if (start < min_start) {
											start = min_start;
										}
									}
								}
							}

							void down() {
								if (selected < components.size() - 1) {
									++selected;
								} else {
									selected = 0;
								}
								fix_start();
							}

							void up() {
								if (selected) {
									--selected;
								} else {
									selected = components.size() - 1;
								}
								fix_start();
							}
						};

						list() : _this(std::make_shared<prototype>()) {
							_this->selected = 0;
							_this->start = 0;
						}

						list(
							const std::string &name,
							std::vector<component> &&cmpts,
							const std::function<void(list)> &on_show,
							const std::string &desc
						) : list() {
							_this->name = name;
							_this->desc = desc;
							_this->components = std::move(cmpts);
							_this->on_show = on_show;
						}

						list(
							const std::string &name,
							const std::string &desc,
							std::vector<component> &&cmpts
						) : list() {
							_this->name = name;
							_this->desc = desc;
							_this->components = std::move(cmpts);
						}

						list(
							const std::string &name,
							std::vector<component> &&cmpts
						) : list() {
							_this->name = name;
							_this->components = std::move(cmpts);
						}

						list(
							const std::string &name,
							const std::string &desc,
							const std::function<void(list)> &on_show
						) : list() {
							_this->name = name;
							_this->desc = desc;
							_this->on_show = on_show;
						}

						list(
							const std::string &name,
							const std::function<void(list)> &on_show
						) : list() {
							_this->name = name;
							_this->on_show = on_show;
						}

						_NOB_SHARED_OBJ(list)
				};

				const std::type_info &type;

				component(base c) : type(typeid(base)), _base_pp(c.get()) {}

				component(action c) : type(typeid(action)), _base_pp(std::static_pointer_cast<base::prototype>(c.get())) {}

				component(list c) : type(typeid(list)), _base_pp(std::static_pointer_cast<base::prototype>(c.get())) {}

				base::prototype *operator->() {
					return _base_pp.get();
				}

				base to_base() {
					assert(type == typeid(base));

					return _base_pp;
				}

				action to_action() {
					assert(type == typeid(action));

					return std::static_pointer_cast<action::prototype>(_base_pp);
				}

				list to_list() {
					assert(type == typeid(list));

					return std::static_pointer_cast<list::prototype>(_base_pp);
				}

			private:
				std::shared_ptr<base::prototype> _base_pp;
		};

		class menu {
			public:
				menu(const std::string &title, const component::list &li) : _tit(title) {
					_list_stack.push(li);
				}

				void toggle();

			private:
				std::string _tit;
				std::stack<component::list> _list_stack;
				task _t;
				keyboard::listener _kl;
		};

		inline void disable_interaction_menu(bool toggle = true) {
			static nob::task t;
			if (toggle) {
				if (!t) {
					t = task([]() {
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::InteractionMenu, true);
					});
				}
			} else {
				t.del();
			}
		}

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
			task ft([content]() {
				info_this_frame(content);
			});
			task ft2([ft, duration]() mutable {
				wait(duration * 15000);
				ft.del();
				this_task().del();
			});
		};

		////////////////////////////////////////////////////////////////////////

		void disable_story_features(bool toggle = true);
		void disable_wheel_slowmo(bool toggle = true);
	} /* ui */

	namespace vision {
		inline void night(bool toggle) {
			nob::ntv::GRAPHICS::SET_NIGHTVISION(toggle);
		}

		inline bool is_night_active() {
			return nob::ntv::GRAPHICS::_IS_NIGHTVISION_ACTIVE();
		}

		inline void heat(bool toggle) {
			nob::ntv::GRAPHICS::SET_SEETHROUGH(toggle);
		}

		inline bool is_heat_active() {
			return nob::ntv::GRAPHICS::_IS_SEETHROUGH_ACTIVE();
		}
	} /* vision */

	namespace i18n {
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
} /* nob */
