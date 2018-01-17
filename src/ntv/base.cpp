#include <nob/ntv/base.hpp>
#include <nob/program.hpp>
#include <nob/hash.hpp>
#include <nob/log.hpp>

namespace nob {
	namespace ntv {
		template <typename T>
		func_t *_fn_tab_find(uintptr_t nodes, uint64_t hash) {
			if (!nodes) {
				return nullptr;
			}
			for (auto n = reinterpret_cast<T **>(nodes)[hash % 0x100]; n; n = n->next()) {
				for (uint8_t i = 0; i < n->length(); ++i) {
					if (n->hash(i) == hash) {
						return &n->funcs[i];
					}
				}
			}
			log("nob::ntv::func_table_t::find(", std::hex, hash, std::dec, "): not found!");
			return nullptr;
		}

		func_t *func_table_t::find(uint64_t hash) const {
			struct node_t {
				node_t *nxt;
				func_t funcs[7];
				uint32_t len;
				uint64_t hashes[7];

				node_t *next() const {
					return nxt;
				}

				uint32_t length() const {
					return len;
				}

				uint64_t hash(uint8_t ix) const {
					return hashes[ix];
				}
			};

			struct node_1290_t {
				uint64_t nxt1;
				uint64_t nxt2;
				func_t funcs[7];
				uint32_t len1;
				uint32_t len2;
				uint64_t hashes;

				node_1290_t *next() const {
					volatile uintptr_t result;
					volatile auto v5 = reinterpret_cast<uintptr_t>(&nxt1);
					volatile uint64_t c = 2;
					volatile auto v13 = v5 ^ nxt2;
					volatile auto v14 = (char *)&result - v5;
					do {
						*(uint32_t*)&v14[v5] = v13 ^ *(uint32_t*)v5;
						v5 += 4;
						--c;
					} while (c);
					return reinterpret_cast<node_1290_t *>(result);
				}

				uint32_t length() const {
					return ((uintptr_t)&len1) ^ len1 ^ len2;
				}

				uint64_t hash(uint8_t ix) const {
					volatile uintptr_t n_addr = 16 * ix + reinterpret_cast<uintptr_t>(&nxt1) + 0x54;
					volatile uint64_t c = 2;
					volatile uint64_t n_result;
					volatile auto v11 = (char *)&n_result - n_addr;
					volatile auto v10 = n_addr ^ *(uint32_t *)(n_addr + 8);
					do {
						*(uint32_t *)&v11[n_addr] = v10 ^ *(uint32_t *)(n_addr);
						n_addr += 4;
						--c;
					} while (c);
					return n_result;
				}
			};

			return
				program::version < 1290 ?
				_fn_tab_find<node_t>(_nodes, hash) :
				_fn_tab_find<node_1290_t>(_nodes, hash)
			;
		}

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
				log("nob::ntv::global_table::_segments: not found!");
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
				log("nob::ntv::func_table::_nodes: not found!");
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
