#pragma once

#include "ntv.hpp"
#include "g2d.hpp"
#include "screen.hpp"
#include "vector.hpp"
#include "script.hpp"
#include "input.hpp"

#include <rua/obj.hpp>

#include <string>
#include <functional>
#include <vector>
#include <stack>
#include <initializer_list>
#include <utility>

namespace nob {
	namespace ui {
		static constexpr float aspect_ratio = 9.0f / 16.0f;
		static constexpr vector2 padding_size { 29.0f / 1920.0f, 17.0f / 1080.0f };
		static constexpr struct { float left, top, right, bottom; } padding {
			padding_size.x, padding_size.y, 1.0f - padding_size.x, 1.0f - padding_size.y
		};

		struct _item {
			std::string name;
			std::string desc;

			_item(
				std::string name = "",
				std::string desc = ""
			) : name(std::move(name)), desc(std::move(desc)) {}
		};

		using item = rua::itf<_item>;

		struct _action : _item {
			std::function<void()> handler;

			_action(
				std::string name,
				std::string desc,
				std::function<void()> handler
			) : _item(std::move(name), std::move(desc)), handler(std::move(handler)) {}

			_action(
				std::string name,
				std::function<void()> handler
			) : _item(std::move(name)), handler(std::move(handler)) {}
		};

		using action = rua::obj<_action>;

		class list;

		struct _list : _item {
			std::vector<item> items;
			std::function<void(list)> on_show;
			size_t page_top = 0;
			size_t selected = 0;

			_list(
				std::string name,
				std::string desc,
				std::vector<item> items,
				std::function<void(list)> on_show
			) : _item(std::move(name), std::move(desc)), items(std::move(items)), on_show(std::move(on_show)) {}

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

		class list : public rua::obj<_list> {
			public:
				constexpr list(std::nullptr_t) : rua::obj<_list>(nullptr) {}

				list(
					std::string name,
					std::string desc,
					std::vector<item> items,
					std::function<void(list)> on_show = nullptr
				) : rua::obj<_list>(std::move(name), std::move(desc), std::move(items), std::move(on_show)) {}

				list(
					std::string name,
					std::string desc,
					std::initializer_list<item> items,
					std::function<void(list)> on_show = nullptr
				) : list(std::move(name), std::move(desc), std::vector<item>(items), std::move(on_show)) {}

				list(
					std::string name,
					std::initializer_list<item> items
				) : list(std::move(name), "", std::vector<item>(items), nullptr) {}

				list(
					std::string name,
					std::string desc,
					std::function<void(list)> on_show
				) : list(std::move(name), std::move(desc), std::vector<item>(), std::move(on_show)) {}

				list(
					std::string name,
					std::function<void(list)> on_show
				) : list(std::move(name), "", std::vector<item>(), std::move(on_show)) {}

				list(
					std::string name
				) : list(std::move(name), "", std::vector<item>(), nullptr) {}
		};

		struct _flag : _item {
			bool value;
			std::function<void(bool)> on_change;

			_flag(
				std::string name,
				std::string desc,
				bool value,
				std::function<void(bool)> on_change
			) : _item(std::move(name), std::move(desc)), value(value), on_change(std::move(on_change)) {}

			_flag(
				std::string name,
				bool value,
				std::function<void(bool)> on_change
			) : _item(std::move(name)), value(value), on_change(std::move(on_change)) {}

			_flag(
				std::string name,
				std::string desc,
				std::function<void(bool)> on_change
			) : _item(std::move(name), std::move(desc)), value(false), on_change(std::move(on_change)) {}

			_flag(
				std::string name,
				std::function<void(bool)> on_change
			) : _item(std::move(name)), value(false), on_change(std::move(on_change)) {}
		};

		using flag = rua::obj<_flag>;

		class menu {
			public:
				menu() = default;

				menu(
					const std::string &title,
					const list &li,
					bool can_be_close = true
				) : _data(std::make_shared<_data_t>()) {
					_data->_tit = title;
					_data->_can_cls = can_be_close;
					_data->_li_stack.push(li);
				}

				operator bool() const {
					return _data && _data->_li_stack.size();
				}

				void open();

				void close();

				static void close_any();

				bool is_opened() const;

				static bool is_opened_any();

				void toggle() {
					if (is_opened()) {
						close();
					} else {
						open();
					}
				}

				void weak_open() {
					if (is_opened_any()) {
						return;
					}
					open();
				}

				void weak_toggle() {
					if (is_opened()) {
						close();
					} else if (!is_opened_any()) {
						open();
					}
				}

				////////////////////////////////////////////////////////////////

				static float width() {
					auto sr = screen::resolution();
					return 432.0f / 1080.0f * sr.y / sr.x;
				}

				static constexpr float title_bg_height = 0.1f;
				static constexpr float title_font_size = 0.9f;
				static constexpr float title_font_height = g2d::calc_text_height(title_font_size);
				static constexpr float font_size = 0.355f;
				static constexpr float font_height = g2d::calc_text_height(font_size);
				static constexpr float margin = 11.0f / 1920.0f;
				static constexpr float item_height = 37.0f / 1080.0f;
				static constexpr float icon_height = item_height / 0.77f;
				static constexpr float icon_width = icon_height * aspect_ratio;

				struct _data_t {
					std::string _tit;
					std::stack<list> _li_stack;
					bool _can_cls;
				};

			private:
				std::shared_ptr<_data_t> _data;
		};

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

		inline void info(const std::string &content, float dur = 1.0f) {
			task([content]() {
				info_this_frame(content);
			}, dur * 15000);
		};

		void banner(const std::string &title, const std::string &sub_title = "");
		void clear_banner();

		void button_bar(std::vector<std::pair<std::string, std::vector<hotkey_t>>>);
		void clear_button_bar();

		void disable_sp_features(bool toggle = true);
		void disable_wheel_slowmo(bool toggle = true);

		namespace hud {
			inline void display(bool toggle = true) {
				ntv::UI::DISPLAY_HUD(toggle);
			}

			inline bool is_display() {
				return !ntv::UI::IS_HUD_HIDDEN();
			}

			void hide_lower_right(bool toggle = true);
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

		void enable_mp_frontend_menu(bool toggle = true);

		inline void loading_screen(bool toggle = true, int fade_duration = 500) {
			if (toggle) {
				ntv::CAM::DO_SCREEN_FADE_OUT(fade_duration);
			} else {
				ntv::CAM::DO_SCREEN_FADE_IN(fade_duration);
			}
		}

		inline bool loading_screen_faded_in() {
			return ntv::CAM::IS_SCREEN_FADED_OUT();
		}

		inline bool loading_screen_faded_out() {
			return ntv::CAM::IS_SCREEN_FADED_IN();
		}

		inline bool loading_screen_fading_in() {
			return ntv::CAM::IS_SCREEN_FADING_OUT();
		}

		inline bool loading_screen_fading_out() {
			return ntv::CAM::IS_SCREEN_FADING_IN();
		}

		enum class prompt_type_t : int {
			loading = 0,
			mp_saving = 4,
			saving = 6
		};

		inline void prompt(const std::string &info, prompt_type_t type = prompt_type_t::loading) {
			ntv::UI::_BEGIN_TEXT_COMMAND_BUSY_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(info.c_str());
			ntv::UI::_END_TEXT_COMMAND_BUSY_STRING(static_cast<int>(type));
		}

		inline void clear_prompt() {
			ntv::UI::_REMOVE_LOADING_PROMPT();
		}

		enum class cursor_icon_t : int {
			none = 0,
			normal = 1,
			transparent_normal = 2,
			pre_grab = 3,
			grab = 4,
			middle_finger = 5,
			left_arrow = 6,
			right_arrow = 7,
			up_arrow = 8,
			down_arrow = 9,
			horizontal_expand = 10,
			add = 11,
			remove = 12
		};

		void show_cursor(cursor_icon_t ico = cursor_icon_t::normal);
		void hide_cursor();
	} /* ui */
} /* nob */
