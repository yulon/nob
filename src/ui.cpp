#include <nob/ui.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>

#include <rua/hook.hpp>
#include <rua/hook.inc>

#include <thread>
#include <sstream>

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
			static rua::hooked<void (*)()> hkd;

			if (toggle) {
				if (!sf) {
					chan<void (*)()> ch;

					std::thread([ch]() mutable {
						ch << program::code.match({
							// Reference from https://www.unknowncheats.me/forum/grand-theft-auto-v/181752-weapon-wheel-slowmotion.html
							0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x20,
							0x33, 0xC0, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x83, 0xFA, 0x01,
							0x75, 1111, 0x38, 0x05, 1111, 1111, 1111, 1111, 0x0F, 0x45,
							0xF8
						}).base();
					}).detach();

					ch >> sf;

					if (!sf) {
						return;
					}
				}
				if (!hkd) {
					hkd.hook(sf, []() {});
				}
			} else {
				hkd.unhook();
			}
		}

		namespace _menu {
			std::shared_ptr<menu::_data_t> cur(nullptr);
			task draw_tsk;
			hotkey_listener hk_lnr, hk_bkr;
			g2d::texture_dict cm_td("CommonMenu");
			initer reset(menu::close_any);

			static inline void del_res() {
				draw_tsk.del();
				hk_lnr.del();
				hk_bkr.del();
				cm_td.free();
				cur.reset();
			}
		}

		bool menu::is_opened() const {
			return this->_data.get() && _menu::cur.get() && _menu::cur.get() == this->_data.get();
		}

		bool menu::is_opened_any() {
			return _menu::cur.get();
		}

		void menu::open() {
			if (is_opened()) {
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
				float x = padding_x;
				float y = padding_y;
				float w = width();
				float h = title_bg_height;
				_menu::cm_td.draw("interaction_bgd", x, y, w, h);
				g2d::text(x, y + ((h - title_font_height) / 2), w, _menu::cur->_tit, title_font_size, 255, 255, 255, 255, 1);

				auto &cur_li = _menu::cur->_li_stack.top();
				auto sz = cur_li->items.size();

				y += h;
				h = item_height;
				g2d::rect(x, y, w, h);
				g2d::text(x + margin, y + ((h - font_height) / 2.0f), w, cur_li->name, font_size, 100, 179, 211, 255, 0);

				if (sz) {
					size_t len;
					if (sz < 11) {
						len = sz;
					} else {
						std::stringstream ss;
						ss << cur_li->selected + 1 << " / " << sz;
						g2d::text(x - margin, y + ((h - font_height) / 2.0f), w, ss.str(), font_size, 255, 255, 255, 255, 2);

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

						g2d::text(x + margin, y + ((h - font_height) / 2.0f), w, cur_li->items[i]->name, font_size, r, g, b, 255, 0);

						y += h;
					}

					if (sz < 11) {
						h = 0.005f;
					} else {
						y += 0.001f;
						g2d::rect(x, y, w, h, 0, 0, 0, 200);
						_menu::cm_td.draw("shop_arrows_upanddown", x + ((w - icon_width) / 2.0f), y + ((h - icon_height) / 2.0f), icon_width, icon_height);
						y += h;

						h = 0.0025f;
					}

					if (!cur_li->items[cur_li->selected]->desc.empty()) {
						y += h;
						h = 0.003f;
						g2d::rect(x, y, w, h);

						y += h;
						y = y - 0.0015f;
						h = item_height * 1.0f;
						_menu::cm_td.draw("gradient_bgd", x, y, w, h, 0.0f, 200);

						g2d::text(x + margin, y + ((h - font_height) / 2), w, cur_li->items[cur_li->selected]->desc, font_size, 255, 255, 255, 255, 0);
					}
				}
			});

			_menu::hk_bkr = hotkey_listener(
				{
					hotkey_t::InteractionMenu,
					hotkey_t::Phone,
					hotkey_t::FrontendPauseAlternate,
					hotkey_t::MeleeAttackLight
				},
				[](hotkey_t, bool)->bool {
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
					switch (hk) {
						case hotkey_t::FrontendCancel:
							if (down) {
								if (_menu::cur->_li_stack.size() > 1) {
									_menu::cur->_li_stack.pop();
								} else if (_menu::cur->_can_cls) {
									close_any();
								}
							}
							break;

						case hotkey_t::FrontendDown:
							if (down) {
								_menu::cur->_li_stack.top()->next();
							}
							break;

						case hotkey_t::FrontendUp:
							if (down) {
								_menu::cur->_li_stack.top()->prev();
							}
							break;

						case hotkey_t::FrontendAccept:
							if (down) {
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
							}
							break;

						default:
							break;
					}
					return false;
				}
			);
		}

		void menu::close() {
			if (!is_opened()) {
				return;
			}
			_menu::del_res();
		}

		void menu::close_any() {
			if (!is_opened_any()) {
				return;
			}
			_menu::del_res();
		}

		int _bnr_sf;
		task _bnr_tsk;

		initer _reset_bnr_sf([]() {
			_bnr_sf = 0;
			if (_bnr_tsk) {
				_bnr_tsk.del();
			}
		});

		void banner(const std::string &text) {
			clear_banner();

			_bnr_tsk = task([text]() {
				if (!_bnr_sf) {
					_bnr_sf = ntv::GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");
					while (!ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_bnr_sf)) {
						yield();
					}

					ntv::GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(_bnr_sf, "SHOW_MISSION_PASSED_MESSAGE");
					if (text.empty()) {
						ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("M_FB4P3_P");
					} else {
						ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
						ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
					}

					ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
					ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("M_FB4P3");
					ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
					ntv::GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(100);
					ntv::GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(true);
					ntv::GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0);
					ntv::GRAPHICS::_ADD_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(true);
					ntv::GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				}
				nob::ntv::GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(_bnr_sf, 255, 255, 255, 255, 0);
			});
		}

		void clear_banner() {
			if (_bnr_tsk) {
				_bnr_tsk.del();
			}
			if (_bnr_sf) {
				if (ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_bnr_sf)) {
					ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&_bnr_sf);
				}
				_bnr_sf = 0;
			}
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

		namespace hud {
			void hide_lower_right(bool toggle) {
				static task tsk;
				if (toggle) {
					if (!tsk) {
						tsk = task([]() {
							for (int i = 6; i < 10; ++i) {
								ntv::UI::HIDE_HUD_COMPONENT_THIS_FRAME(i);
							}
						});
					}
				} else if (tsk) {
					tsk.del();
				}
			}
		}

		task _cursor_tsk;

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
	} /* ui */
} /* nob */
