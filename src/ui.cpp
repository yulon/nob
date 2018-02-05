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
			static task tsk;

			if (toggle) {
				if (!tsk) {
					tsk = task([]() {
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::MultiplayerInfo, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::CharacterWheel, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::SelectCharacterMichael, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::SelectCharacterFranklin, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::SelectCharacterTrevor, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::SelectCharacterMultiplayer, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::SpecialAbilityPC, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::Phone, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::CinematicSlowMo, true);
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::VehicleSlowMoUpDown, true);
					});

					ntv::MOBILE::DESTROY_MOBILE_PHONE();
				}
			} else {
				tsk.del();
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
						}).data();
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
			keyboard::blocker kb_bkr;
			keyboard::listener kb_lnr;
			g2d::texture_dict cm_td("CommonMenu");
			initer reset(menu::close_any);
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
				float x = left;
				float y = top;
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
						_menu::cm_td.draw("gradient_bgd", x, y, w, h, 200);

						g2d::text(x + margin, y + ((h - font_height) / 2), w, cur_li->items[cur_li->selected]->desc, font_size, 255, 255, 255, 255, 0);
					}
				}
			});

			_menu::kb_bkr = {
				keyboard::block_t::interaction_menu,
				keyboard::block_t::phone,
				keyboard::block_t::frontend_menu_esc
			};

			_menu::kb_lnr = keyboard::listener([](int code, bool down)->bool {
				switch (code) {
					case VK_BACK:
						if (down) {
							if (_menu::cur->_li_stack.size() > 1) {
								_menu::cur->_li_stack.pop();
							} else if (_menu::cur->_edchk) {
								close_any();
							}
						}
						return false;

					case VK_ESCAPE:
						if (down) {
							if (_menu::cur->_li_stack.size() > 1) {
								_menu::cur->_li_stack.pop();
							} else if (_menu::cur->_edchk) {
								static keyboard::listener esc_uper;
								if (esc_uper) {
									return false;
								}
								esc_uper = keyboard::listener([](int code, bool down)->bool {
									if (code == VK_ESCAPE && !down) {
										close_any();
										esc_uper.del();
									}
									return false;
								});
							}
						}
						return false;

					case VK_DOWN:
						if (down) {
							_menu::cur->_li_stack.top()->next();
						}
						return false;

					case VK_UP:
						if (down) {
							_menu::cur->_li_stack.top()->prev();
						}
						return false;

					case VK_RETURN:
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
						return false;
				}
				return true;
			});
		}

		void menu::close() {
			if (!is_opened()) {
				return;
			}
			_menu::draw_tsk.del();
			_menu::kb_lnr.del();
			_menu::kb_bkr.del();
			_menu::cm_td.free();
			_menu::cur.reset();
		}

		void menu::close_any() {
			if (!is_opened_any()) {
				return;
			}
			_menu::draw_tsk.del();
			_menu::kb_lnr.del();
			_menu::kb_bkr.del();
			_menu::cm_td.free();
			_menu::cur.reset();
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

		bool _fm_pause = true;

		void takeover_frontend_menu(bool toggle) {
			static keyboard::blocker kb_bkr;
			static keyboard::listener kb_lnr;
			if (toggle) {
				if (kb_bkr) {
					return;
				}
				kb_bkr = {
					keyboard::block_t::frontend_menu_esc,
					keyboard::block_t::frontend_menu_pause
				};
				kb_lnr = keyboard::listener([](int code, bool down)->bool {
					switch (code) {
						case 'P':
						case VK_ESCAPE:
							if (down) {
								static keyboard::listener kb_bk_all;
								if (kb_bk_all) {
									return false;
								}
								kb_bk_all = keyboard::listener([](int code, bool down)->bool {
									if (code == 'P' && down && ntv::UI::IS_PAUSE_MENU_ACTIVE()) {
										ntv::UI::SET_FRONTEND_ACTIVE(false);
									}
									return false;
								});
								ntv::UI::ACTIVATE_FRONTEND_MENU(-1171018317, _fm_pause, -1);
								while (!ntv::UI::IS_PAUSE_MENU_ACTIVE()) {
									yield();
								}
								task([]() {
									if (!ntv::UI::IS_PAUSE_MENU_ACTIVE()) {
										kb_bk_all.del();
										this_task::del();
									}
								});
							}
							return false;
						default:
							return true;
					}
					return true;
				});
			} else if (kb_bkr) {
				kb_lnr.del();
				kb_bkr.del();
			}
		}

		void frontend_menu_cant_be_pause_game(bool toggle) {
			_fm_pause = !toggle;
			if (toggle) {
				takeover_frontend_menu(true);
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
	} /* ui */
} /* nob */
