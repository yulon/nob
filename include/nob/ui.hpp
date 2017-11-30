#pragma once

#include "ntv.hpp"
#include "g2d.hpp"
#include "vector.hpp"
#include "script.hpp"
#include "keyboard.hpp"

#include <tmd/shared_obj.hpp>

#include <string>
#include <functional>
#include <vector>
#include <stack>
#include <initializer_list>

namespace nob {
	namespace ui {
		inline vector2_i resolution() {
			vector2_i v2;
			ntv::GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&v2.x, &v2.y);
			return v2;
		}

		static constexpr float aspect_ratio = 9.0f / 16.0f;

		class item;

		struct item_s {
			std::string name;
			std::string desc;
		};

		struct action_s : item_s {
			std::function<void()> handler;
		};

		class action : public tmd::shared_obj<action_s> {
			public:
				action() {}

				action(
					const std::string &name,
					const std::string &desc,
					const std::function<void()> &handler
				) {
					alloc();
					_m->name = name;
					_m->desc = desc;
					_m->handler = handler;
				}

				action(
					const std::string &name,
					const std::function<void()> &handler
				) {
					alloc();
					_m->name = name;
					_m->handler = handler;
				}
		};

		class list;

		struct list_s : item_s {
			std::vector<item> items;
			std::function<void(list)> on_show;
			size_t page_top = 0;
			size_t selected = 0;

			void fix() {
				if (selected >= items.size()) {
					selected = 0;
				}
				if (items.size() > 10) {
					if (page_top > selected) {
						page_top = selected;
					} else if (selected - page_top > 9) {
						auto min_start = selected - 9;
						if (page_top < min_start) {
							page_top = min_start;
						}
					}
				}
			}

			void next() {
				if (items.size()) {
					if (selected < items.size() - 1) {
						++selected;
					} else {
						selected = 0;
					}
					fix();
				}
			}

			void prev() {
				if (items.size()) {
					if (selected) {
						--selected;
					} else {
						selected = items.size() - 1;
					}
					fix();
				}
			}
		};

		class list : public tmd::shared_obj<list_s> {
			public:
				list() {}

				list(
					const std::string &name,
					const std::string &desc,
					std::initializer_list<item> items,
					const std::function<void(list)> &on_show
				) {
					alloc();
					_m->name = name;
					_m->desc = desc;
					_m->items = std::vector<item>(items);
					_m->on_show = on_show;
				}

				list(
					const std::string &name,
					const std::string &desc,
					std::initializer_list<item> items
				) {
					alloc();
					_m->name = name;
					_m->desc = desc;
					_m->items = std::vector<item>(items);
				}

				list(
					const std::string &name,
					std::initializer_list<item> items
				) {
					alloc();
					_m->name = name;
					_m->items = std::vector<item>(items);
				}

				list(
					const std::string &name,
					const std::string &desc,
					const std::function<void(list)> &on_show
				) {
					alloc();
					_m->name = name;
					_m->desc = desc;
					_m->on_show = on_show;
				}

				list(
					const std::string &name,
					const std::function<void(list)> &on_show
				) {
					alloc();
					_m->name = name;
					_m->on_show = on_show;
				}
		};

		struct flag_s : item_s {
			bool value;
			std::function<void(bool)> on_change;
		};

		class flag : public tmd::shared_obj<flag_s> {
			public:
				flag() {}

				flag(
					const std::string &name,
					const std::string &desc,
					bool value,
					const std::function<void(bool)> &on_change
				) {
					alloc();
					_m->name = name;
					_m->desc = desc;
					_m->value = value;
					_m->on_change = on_change;
				}

				flag(
					const std::string &name,
					bool value,
					const std::function<void(bool)> &on_change
				) {
					alloc();
					_m->name = name;
					_m->value = value;
					_m->on_change = on_change;
				}

				flag(
					const std::string &name,
					const std::function<void(bool)> &on_change
				) {
					alloc();
					_m->name = name;
					_m->value = false;
					_m->on_change = on_change;
				}
		};

		class item : public tmd::dynamic_shared_obj<item_s> {
			public:
				item() {}

				item(
					const std::string &name,
					const std::string &desc
				) {
					alloc();
					_m->name = name;
					_m->desc = desc;
				}

				item(
					const std::string &name
				) {
					alloc();
					_m->name = name;
				}

				item(const action &it) : item(it.cast_with_type<item>()) {}
				item(const list &it) : item(it.cast_with_type<item>()) {}
				item(const flag &it) : item(it.cast_with_type<item>()) {}
		};

		class menu {
			public:
				menu(const std::string &title, const list &li) : _tit(title) {
					_list_stack.push(li);
				}

				void toggle();

				////////////////////////////////////////////////////////////////

				static float width() {
					auto sr = resolution();
					return 432.0f / 1080.0f * sr.y / sr.x;
				}

				static constexpr float left = 29.0f / 1920.0f;
				static constexpr float top = 17.0f / 1080.0f;
				static constexpr float title_bg_height = 0.1f;
				static constexpr float title_font_size = 0.9f;
				static constexpr float title_font_height = g2d::calc_text_height(title_font_size);
				static constexpr float font_size = 0.355f;
				static constexpr float font_height = g2d::calc_text_height(font_size);
				static constexpr float margin = 11.0f / 1920.0f;
				static constexpr float item_height = 37.0f / 1080.0f;
				static constexpr float icon_height = item_height / 0.77f;
				static constexpr float icon_width = icon_height * aspect_ratio;

			private:
				std::string _tit;
				std::stack<list> _list_stack;
				task _tsk;
				keyboard::listener _kl;
		};

		void disable_interaction_menu(bool toggle = true);

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

		inline void info_this_frame(const std::string &content) {
			ntv::UI::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(content.c_str());
			ntv::UI::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
		}

		inline void info(const std::string &content, float duration = 1.0f) {
			task([content]() {
				info_this_frame(content);
			}, duration * 15000);
		};

		void banner(const std::string &text);
		void clear_banner();

		void disable_sp_features(bool toggle = true);
		void disable_wheel_slowmo(bool toggle = true);

		namespace hud {
			inline void display(bool toggle = true) {
				ntv::UI::DISPLAY_HUD(toggle);
			}

			inline bool is_display() {
				return !ntv::UI::IS_HUD_HIDDEN();
			}
		}

		namespace minimap {
			inline void display(bool toggle = true) {
				ntv::UI::DISPLAY_RADAR(toggle);
			}

			inline bool is_display() {
				return !ntv::UI::IS_RADAR_HIDDEN();
			}

			enum class range_t : uint8_t {
				normal,
				mp_big,
				full
			};

			inline void range(range_t r) {
				switch (r) {
					case range_t::normal:
						ntv::UI::_SET_RADAR_BIGMAP_ENABLED(false, false);
						break;
					case range_t::mp_big:
						ntv::UI::_SET_RADAR_BIGMAP_ENABLED(true, false);
						break;
					case range_t::full:
						ntv::UI::_SET_RADAR_BIGMAP_ENABLED(true, true);
				}
			}

			inline void full_screen(bool toggle = true) {
				ntv::UI::_SET_MAP_FULL_SCREEN(toggle);
			}
		}
	} /* ui */
} /* nob */
