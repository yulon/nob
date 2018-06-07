#include <nob/ui.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>
#include <nob/input.hpp>

#include <minhook.hpp>

#include <thread>
#include <string>
#include <unordered_map>

namespace nob {
	namespace ui {
		void disable_sp_features(bool toggle) {
			static hotkey_listener hk_bkr;

			if (toggle) {
				if (!hk_bkr) {
					hk_bkr = {
						hotkey_t::MultiplayerInfo,
						hotkey_t::CharacterWheel,
						hotkey_t::SelectCharacterMichael,
						hotkey_t::SelectCharacterFranklin,
						hotkey_t::SelectCharacterTrevor,
						hotkey_t::SelectCharacterMultiplayer,
						hotkey_t::SpecialAbilityPC,
						hotkey_t::Phone,
						hotkey_t::CinematicSlowMo,
						hotkey_t::VehicleSlowMoUpDown
					};

					ntv::MOBILE::DESTROY_MOBILE_PHONE();
				}
			} else {
				hk_bkr.del();
			}
		}

		void disable_wheel_slowmo(bool toggle) {
			static void (*sf)() = nullptr;
			static minhook<void (*)()> hkd;

			if (toggle) {
				if (!sf) {
					chan<void (*)()> ch;

					std::thread([ch]() mutable {
						auto mr = game_code.match({
							// Reference from https://www.unknowncheats.me/forum/grand-theft-auto-v/181752-weapon-wheel-slowmotion.html
							0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x20,
							0x33, 0xC0, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x83, 0xFA, 0x01,
							0x75, 1111, 0x38, 0x05, 1111, 1111, 1111, 1111, 0x0F, 0x45,
							0xF8
						});
						if (!mr) {
							ch << nullptr;
							return;
						}
						ch << game_code.base() + mr.pos;
					}).detach();

					ch >> sf;

					if (!sf) {
						return;
					}
				}
				if (!hkd) {
					hkd.install(sf, []() {});
				}
			} else {
				hkd.uninstall();
			}
		}

		namespace { namespace _menu {
			std::shared_ptr<menu::_data_t> cur(nullptr);
			task draw_tsk;
			hotkey_listener hk_lnr, hk_bkr;
			g2d::texture_dict cm_td("CommonMenu");
			on_load reset(menu::close_any);

			static inline void del_res() {
				draw_tsk.del();
				hk_lnr.del();
				hk_bkr.del();
				cm_td.free();
				cur.reset();
			}
		}}

		bool menu::is_opened() const {
			return this->_data.get() && _menu::cur.get() && _menu::cur.get() == this->_data.get();
		}

		bool menu::is_any_opened() {
			return _menu::cur.get();
		}

		void menu::open() {
			if (is_any_opened()) {
				return;
			}

			_menu::cur = this->_data;

			auto cur_li = _menu::cur->_li_stack.top();
			if (cur_li->on_show) {
				cur_li->on_show(cur_li);
				cur_li->fix();
			}

			if (_menu::draw_tsk) {
				return;
			}

			_menu::cm_td.load();

			_menu::draw_tsk = task([]() {
				float x = padding.left;
				float y = padding.top;
				float w = width();
				float text_w = w - 2 * item_padding_left;
				float h = title_bg_height;
				_menu::cm_td.draw("interaction_bgd", x, y, w, h);
				g2d::draw_text(x, y + ((h - title_font_height) / 2), text_w, _menu::cur->_tit, title_font_size, 255, 255, 255, 255, 1);

				auto &cur_li = _menu::cur->_li_stack.top();
				auto sz = cur_li->items.size();

				y += h;
				h = item_height;
				g2d::draw_rect(x, y, w, h);
				g2d::draw_text(x + item_padding_left, y + ((h - font_height) / 2.0f), text_w, cur_li->name, font_size, 100, 179, 211, 255, 0);

				if (sz) {
					size_t len;
					if (sz < 11) {
						len = sz;
					} else {
						g2d::draw_text(
							x - item_padding_left, y + ((h - font_height) / 2.0f), w,
							std::to_string(cur_li->selected + 1) + " / " + std::to_string(sz),
							font_size, 255, 255, 255, 255, 2
						);

						len = 10;
					}

					size_t end = cur_li->page_top + len;

					y += h;
					_menu::cm_td.draw("gradient_bgd", x, y, w, len * h);

					for (size_t i = cur_li->page_top; i < sz && i < end; ++i) {
						uint8_t r, g, b;

						if (i == cur_li->selected) {
							r = g = b = 0;

							_menu::cm_td.draw("gradient_nav", x, y, w, h);

							if (cur_li->items[i].type_is<flag>()) {
								auto flg_val = cur_li->items[i].to<flag>()->value;
								if (flg_val) {
									_menu::cm_td.draw("shop_box_tickb", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
								} else {
									_menu::cm_td.draw("shop_box_blankb", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
								}
							}
						} else {
							r = g = b = 255;

							if (cur_li->items[i].type_is<flag>()) {
								auto flg_val = cur_li->items[i].to<flag>()->value;
								if (flg_val) {
									_menu::cm_td.draw("shop_box_tick", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
								} else {
									_menu::cm_td.draw("shop_box_blank", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
								}
							}
						}

						g2d::draw_text(x + item_padding_left, y + ((h - font_height) / 2.0f), text_w, cur_li->items[i]->name, font_size, r, g, b, 255, 0);

						y += h;
					}

					if (sz < 11) {
						h = 0.005f;
					} else {
						y += 0.001f;
						g2d::draw_rect(x, y, w, h, 0, 0, 0, 200);
						_menu::cm_td.draw("shop_arrows_upanddown", x + ((w - icon_width) / 2.0f), y + ((h - icon_height) / 2.0f), icon_width, icon_height);
						y += h;

						h = 0.0025f;
					}

					if (!cur_li->items[cur_li->selected]->desc.empty()) {
						y += h;
						h = 0.003f;
						g2d::draw_rect(x, y, w, h);

						y += h;
						y = y - 0.0015f;
						h = item_height * 2.f;
						_menu::cm_td.draw("gradient_bgd", x, y, w, h, 0.0f, 200);

						g2d::draw_text(x + item_padding_left, y + ((item_height - font_height) / 2), text_w, cur_li->items[cur_li->selected]->desc, font_size, 255, 255, 255, 255, 0);
					}
				}
			});

			_menu::hk_bkr = hotkey_listener(
				{
					hotkey_t::InteractionMenu,
					hotkey_t::Phone,
					hotkey_t::FrontendPauseAlternate
				},
				[](hotkey_t hk, bool)->bool {
					if (hk == hotkey_t::InteractionMenu) {
						return true;
					}
					return false;
				},
				true
			);

			_menu::hk_lnr = hotkey_listener(
				{
					hotkey_t::FrontendCancel,
					hotkey_t::FrontendDown,
					hotkey_t::FrontendUp,
					hotkey_t::FrontendAccept
				},
				[](hotkey_t hk, bool down)->bool {
					if (!down) {
						if (!_menu::cur.get() && hk == hotkey_t::FrontendCancel) {
							_menu::hk_lnr.del();
							_menu::hk_bkr.del();
						}
						return false;
					}
					ntv::AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
					switch (hk) {
						case hotkey_t::FrontendCancel:
							if (_menu::cur->_li_stack.size() > 1) {
								_menu::cur->_li_stack.pop();
							} else if (_menu::cur->_can_cls) {
								_menu::draw_tsk.del();
								_menu::cm_td.free();
								_menu::cur.reset();
							}
							break;

						case hotkey_t::FrontendDown:
							_menu::cur->_li_stack.top()->next();
							break;

						case hotkey_t::FrontendUp:
							_menu::cur->_li_stack.top()->prev();
							break;

						case hotkey_t::FrontendAccept: {
							auto cur_li = _menu::cur->_li_stack.top();
							if (cur_li->items.size()) {
								auto cur_it = cur_li->items[cur_li->selected];

								if (cur_it.type_is<action>()) {
									auto a = cur_it.to<action>();
									if (a->handler) {
										a->handler();
									}
								} else

								if (cur_it.type_is<list>()) {
									cur_li = cur_it.to<list>();
									if (cur_li->on_show) {
										cur_li->on_show(cur_li);
										cur_li->fix();
									}
									_menu::cur->_li_stack.push(cur_li);
								} else

								if (cur_it.type_is<flag>()) {
									auto flg = cur_it.to<flag>();
									flg->value = !flg->value;
									if (flg->on_change) {
										flg->on_change(flg->value);
									}
								}
							}
							break;
						}

						default:
							break;
					}
					return false;
				}
			);

			ntv::AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
		}

		void menu::close() {
			if (!is_opened()) {
				return;
			}
			_menu::del_res();
		}

		void menu::close_any() {
			if (!is_any_opened()) {
				return;
			}
			_menu::del_res();
		}

		namespace { namespace _bnr {
			int sf;
			task draw_tsk;
			on_load reset;
			on_unload free;
		}}

		void banner(const std::string &title, const std::string &sub_title) {
			if (!_bnr::sf) {
				_bnr::sf = ntv::GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");
				while (!ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_bnr::sf)) {
					yield();
				}
			}
			if (!_bnr::reset) {
				_bnr::reset = on_load([]() {
					_bnr::sf = 0;
					if (_bnr::draw_tsk) {
						_bnr::draw_tsk.del();
					}
				});
			}
			if (!_bnr::free) {
				_bnr::free = on_unload([]() {
					if (_bnr::sf && ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_bnr::sf)) {
						ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&_bnr::sf);
					}
				});
			}

			ntv::GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(_bnr::sf, "CLEAR_ALL");

			ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_bnr::sf, "SHOW_SHARD_WASTED_MP_MESSAGE");

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(title.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(sub_title.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(100);
			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(true);
			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(true);

			ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

			ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_bnr::sf, "TRANSITION_UP");
			ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

			if (_bnr::draw_tsk) {
				return;
			}
			_bnr::draw_tsk = task([]() {
				ntv::GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(_bnr::sf, 255, 255, 255, 255, 0);
			});
		}

		void clear_banner() {
			if (_bnr::sf) {
				if (ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_bnr::sf)) {
					ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_bnr::sf, "TRANSITION_OUT");
					ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
					sleep(500);
					ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&_bnr::sf);
				}
				_bnr::sf = 0;
			}
			if (_bnr::draw_tsk) {
				_bnr::draw_tsk.del();
			}
			_bnr::reset.del();
			_bnr::free.del();
		}

		namespace { namespace _btn_bar {
			int sf;
			std::vector<std::pair<std::string, std::vector<hotkey_t>>> data;
			task draw_tsk;
			on_load reset;
			on_unload free;
		}}

		void button_bar(std::vector<std::pair<std::string, std::vector<hotkey_t>>> buttons) {
			if (!_btn_bar::sf) {
				_btn_bar::sf = ntv::GRAPHICS::REQUEST_SCALEFORM_MOVIE_INSTANCE("instructional_buttons");
				while (!ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_btn_bar::sf)) {
					yield();
				}
				ntv::GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(_btn_bar::sf, "CLEAR_ALL");

				ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_btn_bar::sf, "TOGGLE_MOUSE_BUTTONS");
				ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(false);
				ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

				ntv::GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(_btn_bar::sf, "CREATE_CONTAINER");
			}
			if (!_btn_bar::reset) {
				_btn_bar::reset = on_load([]() {
					_btn_bar::sf = 0;
					if (_btn_bar::draw_tsk) {
						_btn_bar::draw_tsk.del();
					}
					if (_btn_bar::data.size()) {
						_btn_bar::data.clear();
					}
				});
			}
			if (!_btn_bar::free) {
				_btn_bar::free = on_unload([]() {
					if (_btn_bar::sf && ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_btn_bar::sf)) {
						ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&_btn_bar::sf);
					}
				});
			}

			_btn_bar::data = std::move(buttons);

			if (_btn_bar::draw_tsk) {
				return;
			}
			_btn_bar::draw_tsk = task([]() {
				for (size_t i = 0; i < _btn_bar::data.size(); ++i) {
					auto &pr = _btn_bar::data[_btn_bar::data.size() - 1 - i];
					ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_btn_bar::sf, "SET_DATA_SLOT");
					ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(i);
					for (auto it = pr.second.rbegin(); it != pr.second.rend(); ++it) {
						ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_BUTTON_NAME(
							ntv::CONTROLS::GET_CONTROL_INSTRUCTIONAL_BUTTON(0, static_cast<int>(*it), 0)
						);
						//ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(false);
						//ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(358);
					}
					ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING(pr.first.c_str());
					ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				}
				ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_btn_bar::sf, "DRAW_INSTRUCTIONAL_BUTTONS");
				ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(-1);
				ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

				ntv::GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(_btn_bar::sf, 255, 255, 255, 255, 0);
			});
		}

		void clear_button_bar() {
			if (_btn_bar::sf) {
				if (ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_btn_bar::sf)) {
					ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&_btn_bar::sf);
				}
				_btn_bar::sf = 0;
			}
			if (_btn_bar::draw_tsk) {
				_btn_bar::draw_tsk.del();
			}
			_bnr::reset.del();
			_bnr::free.del();
		}

		bool _fm_opened = false;

		void enable_mp_frontend_menu(bool toggle) {
			static hotkey_listener hk_lnr;

			if (toggle) {
				if (hk_lnr) {
					return;
				}
				hk_lnr = hotkey_listener(
					{
						hotkey_t::FrontendPause,
						hotkey_t::FrontendPauseAlternate
					},
					[](hotkey_t, bool down)->bool {
						if (!down) {
							if (_fm_opened) {
								return false;
							}
							_fm_opened = true;
							ntv::UI::ACTIVATE_FRONTEND_MENU(-1171018317, false, -1);
							while (!ntv::UI::IS_PAUSE_MENU_ACTIVE()) {
								yield();
							}
							while (ntv::UI::IS_PAUSE_MENU_ACTIVE()) {
								yield();
							}
							_fm_opened = false;
						}
						return false;
					},
					true
				);
			} else if (hk_lnr) {
				hk_lnr.del();
			}
		}

		static task _cursor_tsk;

		void show_cursor(cursor_icon_t ico) {
			ntv::UI::_SET_CURSOR_SPRITE(static_cast<int>(ico));
			if (!_cursor_tsk) {
				_cursor_tsk = task(ntv::UI::_SHOW_CURSOR_THIS_FRAME);
			}
		}

		void hide_cursor() {
			if (_cursor_tsk) {
				_cursor_tsk.del();
			}
		}

		namespace { namespace _stpl {
			struct data_t {
				vector3 pos;
				g2d::texture_dict td;
			};

			std::unordered_map<int, data_t> map;

			task draw_tsk;
			on_load reset;
			on_unload free;
		}}

		void stats_panel::reset(
			const vector3 &pos,
			const std::string &title,
			const std::string &desc,
			const std::string &tex_dct,
			const std::string &tex,
			const std::array<std::pair<std::string, int>, 4> &items
		) {
			if (!_sf) {
				_sf = ntv::GRAPHICS::REQUEST_SCALEFORM_MOVIE("mp_car_stats_01");
				assert(_sf);

				_stpl::map.emplace(_sf, _stpl::data_t{pos, tex_dct});

				while (!ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_sf)) {
					yield();
				}
			}

			ntv::GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(_sf, "CLEAR_ALL");

			ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_sf, "SET_VEHICLE_INFOR_AND_STATS");

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(title.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			memcpy((char *)title.data(), "12\0", 3);

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(desc.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			auto &td = _stpl::map[_sf].td;
			if (td.name() != tex_dct) {
				td = tex_dct;
			}
			td.load();

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(tex_dct.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(tex.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(items[0].first.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(items[1].first.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(items[2].first.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(items[3].first.c_str());
			ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(items[0].second);
			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(items[1].second);
			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(items[2].second);
			ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(items[3].second);

			ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

			if (_stpl::draw_tsk) {
				return;
			}

			_stpl::draw_tsk = task([]() {
				/*auto rot_z = ntv::CAM::GET_GAMEPLAY_CAM_ROT(0).z + 180.f;
				if (rot_z > 180.f) {
					rot_z = -180.f + (rot_z - 180.f);
				} else if (rot_z < -180.f) {
					rot_z = 180.f - (-180.f - rot_z);
				}*/
				for (auto &pr : _stpl::map) {
					ntv::GRAPHICS::_DRAW_SCALEFORM_MOVIE_3D_NON_ADDITIVE(
						pr.first,
						pr.second.pos.x, pr.second.pos.y, pr.second.pos.z + 5.f,
						0.f, 0.f, 0.f,
						0.f,
						1.f, 0.f, 10.f, 10.f, 10.f, 0.f
					);
				}
			});

			_stpl::reset = on_load([]() {
				_stpl::map.clear();
				_stpl::draw_tsk.del();
				_stpl::reset.del();
				_stpl::free.del();
			});

			_stpl::free = on_unload([]() {
				for (auto &pr : _stpl::map) {
					if (ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(pr.first)) {
						auto sf = pr.first;
						ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&sf);
					}
				}
				_stpl::map.clear();
			});
		}

		void stats_panel::reset() {
			if (!_sf) {
				return;
			}
			auto it = _stpl::map.find(_sf);
			if (it != _stpl::map.end()) {
				if (ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_sf)) {
					ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&_sf);
				}
				_stpl::map.erase(it);
				if (_stpl::map.empty()) {
					_stpl::draw_tsk.del();
					_stpl::reset.del();
					_stpl::free.del();
				}
			}
			_sf = 0;
		}
	} /* ui */
} /* nob */
