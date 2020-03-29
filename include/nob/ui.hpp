#pragma once

#include "g2d.hpp"
#include "input.hpp"
#include "ntv.hpp"
#include "screen.hpp"
#include "script.hpp"
#include "vector.hpp"

#include <rua/interface_ptr.hpp>

#include <array>
#include <cassert>
#include <functional>
#include <initializer_list>
#include <memory>
#include <stack>
#include <string>
#include <utility>
#include <vector>

namespace nob { namespace ui {

static constexpr float aspect_ratio = 9.0f / 16.0f;

static constexpr vector2 margin2_size{29.0f / 1920.0f, 17.0f / 1080.0f};

static constexpr struct {
	float left, top, right, bottom;
} padding{margin2_size.x,
		  margin2_size.y,
		  1.0f - margin2_size.x,
		  1.0f - margin2_size.y};

struct item {
	std::string name;
	std::string desc;

	item(std::string name = "", std::string desc = "") :
		name(std::move(name)), desc(std::move(desc)) {}
};

using item_i = rua::interface_ptr<item>;

struct action : item {
	std::function<void()> handler;

	action(std::string name, std::string desc, std::function<void()> handler) :
		item(std::move(name), std::move(desc)), handler(std::move(handler)) {}

	action(std::string name, std::function<void()> handler) :
		item(std::move(name)), handler(std::move(handler)) {}
};

struct list : item {
	std::vector<item_i> items;
	std::function<void(list &)> on_show;
	size_t page_top = 0;
	size_t selected = 0;

	list(
		std::string name,
		std::string desc,
		std::vector<item_i> items,
		std::function<void(list &)> on_show = nullptr) :
		item(std::move(name), std::move(desc)),
		items(std::move(items)),
		on_show(std::move(on_show)) {}

	list(std::string name, std::vector<item_i> items) :
		list(std::move(name), "", std::vector<item_i>(items), nullptr) {}

	list(
		std::string name,
		std::string desc,
		std::function<void(list &)> on_show) :
		list(
			std::move(name),
			std::move(desc),
			std::vector<item_i>(),
			std::move(on_show)) {}

	list(std::string name, std::function<void(list &)> on_show) :
		list(std::move(name), "", std::vector<item_i>(), std::move(on_show)) {}

	list(std::string name) :
		list(std::move(name), "", std::vector<item_i>(), nullptr) {}

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

using list_i = rua::interface_ptr<list>;

struct flag : item {
	bool value;
	std::function<void(bool)> on_change;

	flag(
		std::string name,
		std::string desc,
		bool value,
		std::function<void(bool)> on_change) :
		item(std::move(name), std::move(desc)),
		value(value),
		on_change(std::move(on_change)) {}

	flag(std::string name, bool value, std::function<void(bool)> on_change) :
		item(std::move(name)), value(value), on_change(std::move(on_change)) {}

	flag(
		std::string name,
		std::string desc,
		std::function<void(bool)> on_change) :
		item(std::move(name), std::move(desc)),
		value(false),
		on_change(std::move(on_change)) {}

	flag(std::string name, std::function<void(bool)> on_change) :
		item(std::move(name)), value(false), on_change(std::move(on_change)) {}
};

class menu {
public:
	menu() = default;

	menu(std::string title, list_i li, bool can_be_close = true) :
		_data(std::make_shared<_data_t>()) {
		auto pos = title.find(',');
		if (pos == std::string::npos) {
			_data->_tit = std::move(title);
		} else {
			_data->_tit_td = title.substr(0, pos);
			_data->_tit = title.substr(pos + 1);
		}
		_data->_can_cls = can_be_close;
		_data->_li_stack.push(std::move(li));
	}

	operator bool() const {
		return _data && _data->_li_stack.size();
	}

	void open();

	void close();

	static void close_any();

	bool is_opened() const;

	static bool is_any_opened();

	void toggle() {
		if (is_opened()) {
			close();
		} else {
			open();
		}
	}

	////////////////////////////////////////////////////////////////

	static float width(vector2_i screen_resolution) {
		return 432.0f / 1080.0f * screen_resolution.y / screen_resolution.x;
	}

	static float width() {
		return width(screen::resolution());
	}

	static constexpr float title_bg_height = 0.1f;
	static constexpr float title_font_size = 0.9f;
	static constexpr float title_font_height =
		g2d::calc_text_height(title_font_size);
	static constexpr float font_size = 0.355f;
	static constexpr float font_height = g2d::calc_text_height(font_size);
	static constexpr float item_padding_left = 11.0f / 1920.0f;
	static constexpr float item_height = 37.0f / 1080.0f;
	static constexpr float icon_height = item_height / 0.77f;
	static constexpr float icon_width = icon_height * aspect_ratio;

	struct _data_t {
		std::string _tit;
		g2d::texture_dict _tit_td;
		std::stack<list_i> _li_stack;
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
	// 4
	// 5
	// 6
	right_jumping_arrow = 7,
	rp,
	money
};

inline void message(
	const std::string &pic,
	const std::string &sender,
	const std::string &content,
	float duration = 1.0f,
	msg_icon subject_icon = msg_icon::none,
	msg_icon sender_icon = msg_icon::none,
	const std::string &sender_tag = "",
	const std::string &subject = "") {
	ntv::UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(content.c_str());
	ntv::UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2(
		pic.c_str(),
		pic.c_str(),
		false,
		(int)sender_icon,
		sender.c_str(),
		subject.c_str(),
		duration,
		sender_tag.c_str(),
		(int)subject_icon,
		0);
	ntv::UI::_DRAW_NOTIFICATION(false, false);
}

inline void help(const std::string &content, int dur = 15000) {
	static task tsk;
	static std::string cnt;
	if (dur <= 0) {
		if (tsk) {
			tsk.del();
		}
		if (!dur) {
			ntv::UI::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(content.c_str());
			ntv::UI::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
		}
		return;
	}
	cnt = content;
	if (tsk) {
		tsk.reset_duration(dur);
	} else {
		tsk = task(
			[]() {
				ntv::UI::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
				ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(cnt.c_str());
				ntv::UI::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
			},
			dur);
	}
};

inline void clear_help() {
	help("", -1);
}

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

inline void hide_lower_right(bool toggle = true) {
	static task draw_tsk;
	if (toggle) {
		if (!draw_tsk) {
			draw_tsk = task([]() {
				for (int i = 6; i < 10; ++i) {
					ntv::UI::HIDE_HUD_COMPONENT_THIS_FRAME(i);
				}
			});
		}
	} else if (draw_tsk) {
		draw_tsk.del();
	}
}
} // namespace hud

namespace minimap {
inline void display(bool toggle = true) {
	ntv::UI::DISPLAY_RADAR(toggle);
}

inline bool is_display() {
	return !ntv::UI::IS_RADAR_HIDDEN();
}

enum class range_t : uint8_t { normal, mp_big, full };

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
} // namespace minimap

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

enum class prompt_type_t : int { loading = 0, mp_saving = 4, saving = 6 };

inline void
prompt(const std::string &info, prompt_type_t type = prompt_type_t::loading) {
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

class stats_panel {
public:
	constexpr stats_panel() : _sf(0) {}

	stats_panel(
		const vector3 &pos,
		const std::string &title,
		const std::string &desc,
		const std::string &tex_dct,
		const std::string &tex,
		const std::array<std::pair<std::string, int>, 4> &items) :
		_sf(0) {
		reset(pos, title, desc, tex_dct, tex, items);
	}

	~stats_panel() {
		reset();
	}

	void reset(
		const vector3 &pos,
		const std::string &title,
		const std::string &desc,
		const std::string &tex_dct,
		const std::string &tex,
		const std::array<std::pair<std::string, int>, 4> &items);

	void reset();

private:
	int _sf;
};

}} // namespace nob::ui
