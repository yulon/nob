#include <nob/ntv.hpp>
#include <nob/hack.hpp>

namespace nob {
	namespace ntv {
		global_table_t::global_table_t() : _base_addr(hack::find_const_ptr<uint64_t *>({
			// Reference from https://github.com/zorg93/EnableMpCars-GTAV
			0x4C, 0x8D, 0x05, 1111, 1111, 1111, 1111, 0x4D, 0x8B, 0x08,
			0x4D, 0x85, 0xC9, 0x74, 0x11
		})) {}

		script_list_t::node_t *script_list_t::find(const char *name) const {
			#ifdef DEBUG
				assert(nodes);
			#endif
			int hash = ntv::GAMEPLAY::GET_HASH_KEY(name);
			for (int i = 0; i < size; i++) {
				if (nodes[i].hash == hash) {
					return &nodes[i];
				}
			}
			return nullptr;
		}

		func_table_t::func_table_t() : _nodes(hack::find_const_ptr<func_table_t::node_t *>({
			// Reference from https://github.com/ivanmeler/OpenVHook
			0x76, 0x61, 0x49, 0x8B, 0x7A, 0x40, 0x48, 0x8D, 0x0D
		})) {}
	} /* ntv */
} /* nob */
