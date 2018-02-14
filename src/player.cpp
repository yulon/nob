#include <nob/player.hpp>

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
	}
}
