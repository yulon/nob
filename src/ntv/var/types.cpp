#include <nob/ntv.hpp>

#include <tmd/bin.hpp>

namespace nob {
	extern tmd::bin_view _main_mdu_mem;

	namespace ntv {
		global_table_t::global_table_t() : _base_addr(_main_mdu_mem.match_rel_ptr({
			// Reference from https://github.com/zorg93/EnableMpCars-GTAV
			0x4C, 0x8D, 0x05, 1111, 1111, 1111, 1111, 0x4D, 0x8B, 0x08,
			0x4D, 0x85, 0xC9, 0x74, 0x11
		}).to<uint64_t **>()) {}

		script_list_t::node_t *script_list_t::find(const char *name) const {
			assert(nodes);

			int hash = ntv::GAMEPLAY::GET_HASH_KEY(name);
			for (int i = 0; i < size; i++) {
				if (nodes[i].hash == hash) {
					return &nodes[i];
				}
			}
			return nullptr;
		}

		func_table_t::func_table_t() : _nodes(_main_mdu_mem.match_rel_ptr({
			// Reference from https://github.com/ivanmeler/OpenVHook
			0x76, 0x61, 0x49, 0x8B, 0x7A, 0x40, 0x48, 0x8D, 0x0D, 1111, 1111, 1111, 1111
		}).to<func_table_t::node_t **>()) {}
	} /* ntv */
} /* nob */
