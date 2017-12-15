#include <nob/hash.hpp>
#include <nob/program.hpp>

namespace nob {
	namespace ntv {
		global_table_t::global_table_t() : _base_addr(program::code.match_rel_ptr({
			// Reference from https://github.com/zorg93/EnableMpCars-GTAV
			0x4C, 0x8D, 0x05, 1111, 1111, 1111, 1111, 0x4D, 0x8B, 0x08,
			0x4D, 0x85, 0xC9, 0x74, 0x11
		})) {}

		script_list_t::node_t *script_list_t::find(const char *name) const {
			assert(nodes);

			auto h = hash(name);
			for (size_t i = 0; i < size; i++) {
				if (nodes[i].hash == h) {
					return &nodes[i];
				}
			}
			return nullptr;
		}

		func_table_t::func_table_t() : _nodes(
			program::version < 1290 ?
			program::code.match_rel_ptr({
				// Reference from https://github.com/ivanmeler/OpenVHook
				0x76, 0x61, 0x49, 0x8B, 0x7A, 0x40, 0x48, 0x8D, 0x0D, 1111, 1111, 1111, 1111
			}) :
			program::code.match_rel_ptr({
				// Reference from https://www.unknowncheats.me/forum/1932632-post1648.html
				0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8D, 0x1D, 1111, 1111, 1111, 1111, 0x4C, 0x8D, 0x05
			})
		) {}
	} /* ntv */
} /* nob */
