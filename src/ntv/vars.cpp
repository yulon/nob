#include <nob/ntv.hpp>

#include <tmd/bin.hpp>

namespace nob {
	extern tmd::bin _main_mdu_mem;

	namespace ntv {
		global_table_t global_table;

		script_list_t *script_list = reinterpret_cast<script_list_t *>(_main_mdu_mem.match_rel_ptr({
			// Reference from https://github.com/zorg93/EnableMpCars-GTAV
			0x48, 0x03, 0x15, 1111, 1111, 1111, 1111, 0x4C, 0x23, 0xC2,
			0x49, 0x8B, 0x08
		}));

		func_table_t func_table;
	} /* ntv */
} /* nob */
