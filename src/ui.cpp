#include <nob.hpp>
#include <nob/ntv.hpp>
#include <nob/hack.hpp>

#include <sstream>

namespace nob {
	namespace ui {
		void disable_story_features(bool toggle) {
			static task t;

			if (toggle) {
				if (!t) {
					t = task([]() {
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
				}
			} else {
				t.del();
			}
		}

		void disable_wheel_slowmo(bool toggle) {
			static uintptr_t sf = 0;
			static hack::detour_func_t<void()> df;
			static hack::hooking_func_t<void()> hf;

			if (!sf) {
				sf = call_onmt([]()->uintptr_t {
					return hack::mem_match({
						// Reference from https://www.unknowncheats.me/forum/grand-theft-auto-v/181752-weapon-wheel-slowmotion.html
						0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x20,
						0x33, 0xC0, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x83, 0xFA, 0x01,
						0x75, 1111, 0x38, 0x05, 1111, 1111, 1111, 1111, 0x0F, 0x45,
						0xF8
					});
				});
				if (!sf) {
					return;
				}
			}
			if (toggle) {
				if (!hf) {
					hf = df.hook(sf);
				}
			} else {
				hf.unhook();
			}
		}

		void menu::toggle() {
			if (!_t) {
				auto cur_li = this->_list_stack.top();
				if (cur_li->on_show) {
					cur_li->on_show(cur_li);
					cur_li->fix();
				}

				_t = task([this]() {
					nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::ntv::eControl::FrontendPauseAlternate, true);
					nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::ntv::eControl::Phone, true);

					//////////////////////////////////////////////////////////////////////////

					g2d::wait_texture_dict_valid("CommonMenu");

					float x = left();
					float y = top();
					float w = width();
					float h = title_bg_height();
					g2d::sprite("CommonMenu", "interaction_bgd", x, y, w, h);
					g2d::text(x, y + ((h - title_font_height()) / 2), w, this->_tit, title_font_size(), 255, 255, 255, 255, 1);

					auto cur_li = this->_list_stack.top();
					auto sz = cur_li->items.size();

					y += h;
					h = item_height();
					g2d::rect(x, y, w, h);
					g2d::text(x + margin(), y + ((h - font_height()) / 2.0f), w, cur_li->name, font_size(), 100, 179, 211, 255, 0);

					if (sz) {
						size_t len;
						if (sz < 10) {
							len = sz;
						} else {
							std::stringstream ss;
							ss << cur_li->selected + 1 << " / " << sz;
							g2d::text(x - margin(), y + ((h - font_height()) / 2.0f), w, ss.str(), font_size(), 255, 255, 255, 255, 2);

							len = 10;
						}

						size_t end = cur_li->page_top + len;

						y += h;
						g2d::sprite("CommonMenu", "gradient_bgd", x, y, w, len * h);

						for (size_t i = cur_li->page_top; i < sz && i < end; ++i) {
							uint8_t r, g, b;

							if (i == cur_li->selected) {
								r = g = b = 0;

								g2d::sprite("CommonMenu", "gradient_nav", x, y, w, h);

								if (cur_li->items[i].type_is<flag>()) {
									auto flg_val = cur_li->items[i].cast<flag>()->value;
									if (flg_val) {
										g2d::sprite("CommonMenu", "shop_box_tickb", x + w - icon_width(), y + ((h - icon_height()) / 2.0f), icon_width(), icon_height());
									} else {
										g2d::sprite("CommonMenu", "shop_box_blankb", x + w - icon_width(), y + ((h - icon_height()) / 2.0f), icon_width(), icon_height());
									}
								}
							} else {
								r = g = b = 255;

								if (cur_li->items[i].type_is<flag>()) {
									auto flg_val = cur_li->items[i].cast<flag>()->value;
									if (flg_val) {
										g2d::sprite("CommonMenu", "shop_box_tick", x + w - icon_width(), y + ((h - icon_height()) / 2.0f), icon_width(), icon_height());
									} else {
										g2d::sprite("CommonMenu", "shop_box_blank", x + w - icon_width(), y + ((h - icon_height()) / 2.0f), icon_width(), icon_height());
									}
								}
							}

							g2d::text(x + margin(), y + ((h - font_height()) / 2.0f), w, cur_li->items[i]->name, font_size(), r, g, b, 255, 0);

							y += h;
						}

						if (sz < 10) {
							h = 0.005f;
						} else {
							y += 0.001f;
							g2d::rect(x, y, w, h, 0, 0, 0, 200);
							g2d::sprite("CommonMenu", "shop_arrows_upanddown", x + ((w - icon_width()) / 2.0f), y + ((h - icon_height()) / 2.0f), icon_width(), icon_height());
							y += h;

							h = 0.0025f;
						}

						if (!cur_li->items[cur_li->selected]->desc.empty()) {
							y += h;
							h = 0.003f;
							g2d::rect(x, y, w, h);

							y += h;
							y = y - 0.0015f;
							h = item_height() * 1.0f;
							g2d::sprite("CommonMenu", "gradient_bgd", x, y, w, h, 200);

							g2d::text(x + margin(), y + ((h - font_height()) / 2), w, cur_li->items[cur_li->selected]->desc, font_size(), 255, 255, 255, 255, 0);
						}
					}
				});

				_kl = keyboard::listener([this](int code, bool down)->bool {
					switch (code) {
						case VK_BACK:
						case VK_ESCAPE:
							if (down) {
								if (this->_list_stack.size() > 1) {
									this->_list_stack.pop();
								} else {
									this->toggle();

									static task det;
									static size_t det_i;
									if (det) {
										det_i = 150;
									} else {
										det = task([](task tt) {
											for (det_i = 0; det_i < 150; ++det_i) {
												nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::ntv::eControl::FrontendPauseAlternate, true);
												wait_next_frame();
											}
											tt.del();
										});
									}
								}
							}
							return false;

						case VK_DOWN:
							if (down) {
								this->_list_stack.top()->next();
							}
							return false;

						case VK_UP:
							if (down) {
								this->_list_stack.top()->prev();
							}
							return false;

						case VK_RETURN:
							if (down) {
								auto cur_li = this->_list_stack.top();
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
										this->_list_stack.push(cur_li);
										if (cur_li->on_show) {
											cur_li->on_show(cur_li);
											cur_li->fix();
										}
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
				_t.del();
				_kl.del();
			}
		}
	} /* ui */
} /* nob */
