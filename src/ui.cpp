#include <nob/ui.hpp>
#include <nob/program.hpp>

#include <tmd/hook.hpp>
#include <tmd/hook.inc>

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
			static tmd::hook<void (*)()> hk;

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
				if (!hk) {
					hk.assign(sf, []() {});
				}
			} else {
				hk.unhook();
			}
		}

		void menu::toggle() {
			if (!_tsk) {
				auto cur_li = _list_stack.top();
				if (cur_li->on_show) {
					cur_li->on_show(cur_li);
					cur_li->fix();
				}

				_tsk = task([this]() {
					nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::ntv::eControl::FrontendPauseAlternate, true);
					nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::ntv::eControl::Phone, true);

					//////////////////////////////////////////////////////////////////////////

					g2d::texture_dict cm_td("CommonMenu");

					float x = left;
					float y = top;
					float w = width();
					float h = title_bg_height;
					cm_td.draw("interaction_bgd", x, y, w, h);
					g2d::text(x, y + ((h - title_font_height) / 2), w, _tit, title_font_size, 255, 255, 255, 255, 1);

					auto &cur_li = _list_stack.top();
					auto sz = cur_li->items.size();

					y += h;
					h = item_height;
					g2d::rect(x, y, w, h);
					g2d::text(x + margin, y + ((h - font_height) / 2.0f), w, cur_li->name, font_size, 100, 179, 211, 255, 0);

					if (sz) {
						size_t len;
						if (sz < 10) {
							len = sz;
						} else {
							std::stringstream ss;
							ss << cur_li->selected + 1 << " / " << sz;
							g2d::text(x - margin, y + ((h - font_height) / 2.0f), w, ss.str(), font_size, 255, 255, 255, 255, 2);

							len = 10;
						}

						size_t end = cur_li->page_top + len;

						y += h;
						cm_td.draw("gradient_bgd", x, y, w, len * h);

						for (size_t i = cur_li->page_top; i < sz && i < end; ++i) {
							uint8_t r, g, b;

							if (i == cur_li->selected) {
								r = g = b = 0;

								cm_td.draw("gradient_nav", x, y, w, h);

								if (cur_li->items[i].type_is<flag>()) {
									auto flg_val = cur_li->items[i].cast<flag>()->value;
									if (flg_val) {
										cm_td.draw("shop_box_tickb", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
									} else {
										cm_td.draw("shop_box_blankb", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
									}
								}
							} else {
								r = g = b = 255;

								if (cur_li->items[i].type_is<flag>()) {
									auto flg_val = cur_li->items[i].cast<flag>()->value;
									if (flg_val) {
										cm_td.draw("shop_box_tick", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
									} else {
										cm_td.draw("shop_box_blank", x + w - icon_width, y + ((h - icon_height) / 2.0f), icon_width, icon_height);
									}
								}
							}

							g2d::text(x + margin, y + ((h - font_height) / 2.0f), w, cur_li->items[i]->name, font_size, r, g, b, 255, 0);

							y += h;
						}

						if (sz < 10) {
							h = 0.005f;
						} else {
							y += 0.001f;
							g2d::rect(x, y, w, h, 0, 0, 0, 200);
							cm_td.draw("shop_arrows_upanddown", x + ((w - icon_width) / 2.0f), y + ((h - icon_height) / 2.0f), icon_width, icon_height);
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
							cm_td.draw("gradient_bgd", x, y, w, h, 200);

							g2d::text(x + margin, y + ((h - font_height) / 2), w, cur_li->items[cur_li->selected]->desc, font_size, 255, 255, 255, 255, 0);
						}
					}
				});

				_kl = keyboard::listener([this](int code, bool down)->bool {
					switch (code) {
						case VK_BACK:
						case VK_ESCAPE:
							if (down) {
								if (_list_stack.size() > 1) {
									_list_stack.pop();
								} else {
									toggle();

									static task det;
									if (det) {
										det.reset_dol(1000);
									} else {
										det = task([]() {
											nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::ntv::eControl::FrontendPauseAlternate, true);
										}, 1000);
									}
								}
							}
							return false;

						case VK_DOWN:
							if (down) {
								_list_stack.top()->next();
							}
							return false;

						case VK_UP:
							if (down) {
								_list_stack.top()->prev();
							}
							return false;

						case VK_RETURN:
							if (down) {
								auto cur_li = _list_stack.top();
								if (cur_li->items.size()) {
									auto cur_it = cur_li->items[cur_li->selected];

									if (cur_it.type_is<action>()) {
										auto a = cur_it.cast<action>();
										if (a->handler) {
											a->handler();
										}
									} else

									if (cur_it.type_is<list>()) {
										cur_li = cur_it.cast<list>();
										if (cur_li->on_show) {
											cur_li->on_show(cur_li);
											cur_li->fix();
										}
										_list_stack.push(cur_li);
									} else

									if (cur_it.type_is<flag>()) {
										auto flg = cur_it.cast<flag>();
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

			} else {
				_tsk.del();
				_kl.del();
			}
		}

		void disable_interaction_menu(bool toggle) {
			static nob::task tsk;
			if (toggle) {
				if (!tsk) {
					tsk = task([]() {
						ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)ntv::eControl::InteractionMenu, true);
					});
				}
			} else {
				tsk.del();
			}
		}

		int _bnr_sf;
		task _bnr_tsk;

		void banner(const std::string &text) {
			clear_banner();

			_bnr_tsk = task([text]() {
				if (!_bnr_sf) {
					_bnr_sf = ntv::GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");
					if (!ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_bnr_sf)) {
						wait([]()->bool {
							return ntv::GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(_bnr_sf);
						});
					}

					ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION(_bnr_sf, "SHOW_MISSION_PASSED_MESSAGE");
					if (text.empty()) {
						ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("M_FB4P3_P");
					} else {
						ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
						ntv::UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
					}

					ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
					ntv::GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("M_FB4P3");
					ntv::GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
					ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(100);
					ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(true);
					ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_INT(0);
					ntv::GRAPHICS::_PUSH_SCALEFORM_MOVIE_FUNCTION_PARAMETER_BOOL(true);
					ntv::GRAPHICS::_POP_SCALEFORM_MOVIE_FUNCTION_VOID();
				}
				nob::ntv::GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(_bnr_sf, 255, 255, 255, 255, 0);
			});
		}

		void clear_banner() {
			if (_bnr_tsk) {
				_bnr_tsk.del();
			}
			if (_bnr_sf) {
				ntv::GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&_bnr_sf);
				_bnr_sf = 0;
			}
		}
	} /* ui */
} /* nob */
