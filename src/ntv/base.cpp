#include <nob/ntv/base.hpp>
#include <nob/program.hpp>
#include <nob/hash.hpp>
#include <nob/log.hpp>

namespace nob {
	namespace ntv {
		global_table_t global_table;

		script_list_t *script_list;

		game_state_t *game_state;

		func_t call_context_t::fix_res_fn;

		func_table_t func_table;

		full_call_context_t _dft_call_ctx;

		uintptr_t (*get_entity_addr)(int handle);

		bool _find_addrs() {
			auto finded = true;

			global_table._segments = program::code.match_rel_ptr({
				// Reference from https://github.com/zorg93/EnableMpCars-GTAV
				0x4C, 0x8D, 0x05, 1111, 1111, 1111, 1111, 0x4D, 0x8B, 0x08,
				0x4D, 0x85, 0xC9, 0x74, 0x11
			});

			if (!global_table._segments) {
				log("nob::ntv::global_table_t::_segments: not found!");
				finded = false;
			}

			call_context_t::fix_res_fn = program::code.match({
				// Reference from https://github.com/ivanmeler/OpenVHook
				0x83, 0x79, 0x18, 1111, 0x48, 0x8B, 0xD1, 0x74, 0x4A, 0xFF, 0x4A, 0x18
			}).data();

			if (!call_context_t::fix_res_fn) {
				log("nob::ntv::call_context_t::fix_res_fn: not found!");
				finded = false;
			}

			func_table._nodes =
				program::version < 1290 ?
				program::code.match_rel_ptr({
					// Reference from https://github.com/ivanmeler/OpenVHook
					0x76, 0x61, 0x49, 0x8B, 0x7A, 0x40, 0x48, 0x8D, 0x0D, 1111, 1111, 1111, 1111
				}) :
				program::code.match_rel_ptr({
					// Reference from https://www.unknowncheats.me/forum/1932632-post1648.html
					0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8D, 0x1D, 1111, 1111, 1111, 1111, 0x4C, 0x8D, 0x05
				});

			if (!func_table._nodes) {
				log("nob::ntv::func_table_t::_nodes: not found!");
				finded = false;
			}

			script_list = program::code.match_rel_ptr({
				// Reference from https://github.com/zorg93/EnableMpCars-GTAV
				0x48, 0x03, 0x15, 1111, 1111, 1111, 1111, 0x4C, 0x23, 0xC2,
				0x49, 0x8B, 0x08
			});

			if (!script_list) {
				log("nob::ntv::script_list: not found!");
				finded = false;
			}

			game_state = ++program::code.match_rel_ptr({
				// Reference from https://github.com/ivanmeler/OpenVHook
				0x83, 0x3D, 1111, 1111, 1111, 1111, 1111, 0x8A, 0xD9, 0x74, 0x0A
			});

			if (!game_state) {
				log("nob::ntv::script_list: not found!");
				finded = false;
			}

			get_entity_addr = program::code.match_rel_ptr({
				// Reference from http://gtaforums.com/topic/903092-gta-5-get-entity-address/
				0xE8, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0xD8, 0x48, 0x85, 0xC0, 0x74, 0x2E, 0x48, 0x83, 0x3D
			});

			if (!get_entity_addr) {
				log("nob::ntv::get_entity_addr: not found!");
				finded = false;
			}

			return finded;
		}
	} /* ntv */
} /* nob */
