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
			if (!_ft) {
				_ft = task([this]() {
					g2d::wait_texture_dict_valid("CommonMenu");

					float x = 0.0155f;
					float y = 0.015f;
					float w = 0.25f;
					float h = 0.1f;
					g2d::sprite("CommonMenu", "interaction_bgd", x, y, w, h);
					g2d::text(x, y + ((h - g2d::calc_text_height(0.9f)) / 2), w, this->_tit, 0.9f, 255, 255, 255, 255, 1);

					y += h;
					h = 0.0345f;
					g2d::rect(x, y, w, h);
					g2d::text(x + 0.01f, y + ((h - g2d::calc_text_height(0.426f)) / 2), w, this->_top_list->name, 0.426f, 100, 179, 211, 255, 0);

					auto sz = this->_top_list->components.size();
					if (sz) {
						y += h;
						g2d::sprite("CommonMenu", "gradient_bgd", x, y, w, sz * h);
	
						for (size_t i = 0; i < sz; ++i) {
							g2d::text(x + 0.01f, y + ((h - g2d::calc_text_height(0.426f)) / 2), w, this->_top_list->components[i]->name, 0.426f, 255, 255, 255, 255, 0);
							y += h;
						}
	
						if (!this->_top_list->components[this->_selecting.top()]->desc.empty()) {
							h = 0.005;
							//blank
	
							y += h;
							h = 0.003f;
							g2d::rect(x, y, w, h);
	
							y += h;
							y = y - 0.0015f;
							h = 0.0315f * 2;
							g2d::sprite("CommonMenu", "gradient_bgd", x, y, w, h);
						}
					}
				});
			} else {
				_ft.del();
			}
		}
	} /* ui */
} /* nob */
