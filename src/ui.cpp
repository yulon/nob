#include <nob.hpp>
#include <nob/ntv.hpp>
#include <nob/hack.hpp>

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
				auto &cur = this->_list_stack.top();
				if (cur.li->on_show) {
					cur.li->on_show(cur.li);
				}

				_t = task([this]() {
					nob::ntv::CONTROLS::DISABLE_CONTROL_ACTION(0, (int)nob::ntv::eControl::FrontendPauseAlternate, true);

					//////////////////////////////////////////////////////////////////////////

					g2d::wait_texture_dict_valid("CommonMenu");

					float x = 0.0155f;
					float y = 0.015f;
					float w = 0.25f;
					float h = 0.1f;
					g2d::sprite("CommonMenu", "interaction_bgd", x, y, w, h);
					g2d::text(x, y + ((h - g2d::calc_text_height(0.9f)) / 2), w, this->_tit, 0.9f, 255, 255, 255, 255, 1);

					auto &cur = this->_list_stack.top();
					auto sz = cur.li->components.size();

					y += h;
					h = 0.0345f;
					g2d::rect(x, y, w, h);
					g2d::text(x + 0.006f, y + ((h - g2d::calc_text_height(0.355f)) / 2), w, cur.li->name, 0.355f, 100, 179, 211, 255, 0);

					if (sz) {
						y += h;
						g2d::sprite("CommonMenu", "gradient_bgd", x, y, w, sz * h);

						for (size_t i = 0; i < sz; ++i) {
							uint8_t r, g, b;

							if (i == cur.si) {
								g2d::sprite("CommonMenu", "gradient_nav", x, y, w, h);
								r = g = b = 0;
							} else {
								r = g = b = 255;
							}

							g2d::text(x + 0.006f, y + ((h - g2d::calc_text_height(0.355f)) / 2), w, cur.li->components[i]->name, 0.355f, r, g, b, 255, 0);

							y += h;
						}

						if (!cur.li->components[cur.si]->desc.empty()) {
							h = 0.005;
							//blank

							y += h;
							h = 0.003f;
							g2d::rect(x, y, w, h);

							y += h;
							y = y - 0.0015f;
							h = 0.0315f * 1;
							g2d::sprite("CommonMenu", "gradient_bgd", x, y, w, h);

							g2d::text(x + 0.006f, y + ((h - g2d::calc_text_height(0.355f)) / 2), w, cur.li->components[cur.si]->desc, 0.355f, 255, 255, 255, 255, 0);
						}
					}
				});

				_kl = keyboard::listener([this](int code, bool down)->bool {
					switch (code) {
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
								auto &cur = this->_list_stack.top();
								if (cur.si < cur.li->components.size() - 1) {
									++cur.si;
								}
							}
							return false;

						case VK_UP:
							if (down && this->_list_stack.top().si) {
								--this->_list_stack.top().si;
							}
							return false;

						case VK_RETURN:
							if (down) {
								auto &cur = this->_list_stack.top();
								auto cur_it = cur.li->components[cur.si];
								if (cur_it.type == typeid(component::action)) {
									cur_it.to_action()->handler();
								} else if (cur_it.type == typeid(component::list)) {
									this->_list_stack.push({cur_it.to_list(), 0});

									auto &cur = this->_list_stack.top();
									if (cur.li->on_show) {
										cur.li->on_show(cur.li);
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
