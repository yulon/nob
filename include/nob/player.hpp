#pragma once

#include "ntv.hpp"
#include "character.hpp"
#include "script.hpp"

namespace nob {
	namespace player {
		extern ntv::Player ntv_player;

		inline character body() {
			return ntv::PLAYER::PLAYER_PED_ID();
		}

		inline void change_body(character chr) {
			ntv::PLAYER::CHANGE_PLAYER_PED(ntv_player, chr.ntv_ped, true, true);
		}

		inline void switch_body(character chr) {
			auto old_chr = body();
			auto old_chr_coords = old_chr.pos({ 0, 0, 0 });
			auto chr_coords = chr.pos({ 0, 0, 0 });

			int st = ntv::STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(old_chr_coords.x, old_chr_coords.y, old_chr_coords.z, chr_coords.x, chr_coords.y, chr_coords.z);
			ntv::STREAMING::START_PLAYER_SWITCH(old_chr.ntv_ped, chr.ntv_ped, 0, st);

			wait(1000);

			if (ntv::ENTITY::DOES_ENTITY_EXIST(chr.ntv_ped) && !ntv::ENTITY::IS_ENTITY_DEAD(chr.ntv_ped)) {
				change_body(chr);
				old_chr.remove();
			}
		}
	}
} /* nob */
