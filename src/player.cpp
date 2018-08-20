#include <nob/player.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>
#include <nob/ntv.hpp>
#include <nob/hash.hpp>
#include <nob/log.hpp>

#include <minhook.hpp>

#include <rua/macros.hpp>

namespace nob {
	namespace player {
		void invincible(bool toggle) {
			static nob::task tsk;
			if (toggle) {
				if (tsk) {
					return;
				}
				tsk = nob::task([]() {
					nob::player::body().invincible(true);
					nob::sleep(5000);
				});
			} else {
				if (tsk) {
					tsk.del();
				}
				nob::player::body().invincible(false);
			}
		}

		void full_stats_for_everyone(bool toggle) {
			ntv::STATS::STAT_SET_INT(hash("MP0_SCRIPT_INCREASE_STAM"), 100, 1);
			ntv::STATS::STAT_SET_INT(hash("MP0_SCRIPT_INCREASE_STRN"), 100, 1);
			ntv::STATS::STAT_SET_INT(hash("MP0_SCRIPT_INCREASE_LUNG"), 100, 1);
			ntv::STATS::STAT_SET_INT(hash("MP0_SCRIPT_INCREASE_DRIV"), 100, 1);
			ntv::STATS::STAT_SET_INT(hash("MP0_SCRIPT_INCREASE_FLY"), 100, 1);
			ntv::STATS::STAT_SET_INT(hash("MP0_SCRIPT_INCREASE_SHO"), 100, 1);
			ntv::STATS::STAT_SET_INT(hash("MP0_SCRIPT_INCREASE_STL"), 100, 1);
			ntv::STATS::STAT_SET_INT(hash("MP0_NO_MORE_TUTORIALS"), 1, 1);

			static rua::bin_view::match_result_t mr;
			static rua::bin_view::find_result_t fr;

			RUA_ONCE_CODE({
				chan<bool> ch;
				std::thread([ch]() mutable {
					mr = game_code.match({
						0x75, 0x3F, 0x33, 0xC9, 0xE8, 1111, 1111, 1111, 1111, 0x84, 0xC0, 0x75, 0x16
					});
					if (!mr) {
						log("nob::player::full_stats_for_everyone: 'mr' not found!");
					}

					fr = game_code.find({
						0x83, 0xC8, 0xFF, 0x48, 0x85, 0xC9, 0x74, 0x04
					});
					if (!fr) {
						log("nob::player::full_stats_for_everyone: 'fr' not found!");
					}

					ch << true;
				}).detach();
				ch.get();
			})

			if (mr) {
				static minhook<uintptr_t (*)()> fst_hk, sec_hk;

				if (toggle) {
					static auto fst_ptr = game_code.base() + mr.pos + 4;
					static auto sec_ptr = fst_ptr + 11;
					static auto detour = []()->uintptr_t { return 0; };
					fst_hk.install(fst_ptr, detour);
					sec_hk.install(sec_ptr, detour);
				} else {
					fst_hk.uninstall();
					sec_hk.uninstall();
				}
			}

			if (fr) {
				static minhook<uintptr_t (*)()> hk;

				if (toggle) {
					hk.install(game_code.base() + mr.pos - 4, []()->uintptr_t { return 3; });
				} else {
					hk.uninstall();
				}
			}
		}
	}
}
