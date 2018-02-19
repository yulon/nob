#include <nob/ntv/base.hpp>
#include <nob/program.hpp>
#include <nob/hash.hpp>
#include <nob/log.hpp>

namespace nob {
	namespace ntv {
		thread_t::thread_t() {
			int i;
			for (i = 0; i < pool->count && (*pool)[i]->context.id; ++i);
			if (i == pool->count) {
				return;
			}

			reset((*fake_script_hash_count)++, nullptr, 0);

			context.id = (*id_count)++;
			(*pool)[i] = this;

			script_executor->add(this);
		}

		thread_t::state_t thread_t::reset(uint32_t fake_script_hash, uintptr_t *, uint32_t) {
			memset(&context, 0, sizeof(context));

			context.state = state_t::idle;
			context.fake_script_hash = fake_script_hash;
			context._munk1 = -1;
			context._munk2 = -1;

			context._set1 = 1;

			// zero out gtathread bits
			_init(this);

			network_flag = true;
			can_remove_blips_from_other_scripts = false;

			exit_msg = "Normal exit";

			return context.state;
		}

		thread_t::state_t thread_t::join(uint32_t){
			auto old = *base_thread_t::current;
			*base_thread_t::current = this;
			if (context.state != state_t::killed) {
				script_main();
			}
			*base_thread_t::current = old;
			return context.state;
		}

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

		func_t call_context_t::res_fixer;

		func_table_t func_table;

		full_call_context_t _dft_call_ctx;

		uintptr_t (*get_entity_addr)(int handle);

		base_script_executor_t *script_executor;

		uint32_t *fake_script_hash_count;

		base_thread_t **base_thread_t::current;

		container_t<thread_t *> *thread_t::pool;

		uint32_t *thread_t::id_count;

		void (*thread_t::_init)(thread_t *);

		thread_t::state_t (*thread_t::_tick)(thread_t *, uint32_t ops_to_execute);

		void (*thread_t::_kill)(thread_t *);

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

			call_context_t::res_fixer = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L104
				0x83, 0x79, 0x18, 1111, 0x48, 0x8B, 0xD1, 0x74, 0x4A, 0xFF, 0x4A, 0x18
			}).data();

			if (!call_context_t::res_fixer) {
				log("nob::ntv::call_context_t::res_fixer: not found!");
				finded = false;
			}

			func_table._nodes =
				program::version < 1290 ?
				program::code.match_rel_ptr({
					// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L389
					0x76, 0x61, 0x49, 0x8B, 0x7A, 0x40, 0x48, 0x8D, 0x0D, 1111, 1111, 1111, 1111
				}) :
				program::code.match_rel_ptr({
					// Reference from https://www.unknowncheats.me/forum/1932632-post1648.html
					0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8D, 0x1D, 1111, 1111, 1111, 1111, 0x4C, 0x8D, 0x05
				})
			;

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
				// Reference from https://github.com/MockbaTheBorg/GTALuaF/blob/master/PHP/patternsGTA.txt#L10
				0x83, 0x3D, 1111, 1111, 1111, 1111, 1111, 0x8A, 0xD9, 0x74, 0x0A
			});

			if (!game_state) {
				log("nob::ntv::game_state: not found!");
				finded = false;
			}

			get_entity_addr = program::code.match_rel_ptr({
				// Reference from http://gtaforums.com/topic/903092-gta-5-get-entity-address/
				0xE8, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0xD8, 0x48, 0x85, 0xC0, 0x74, 0x2E, 0x48, 0x83, 0x3D
			});

			if (!get_entity_addr) {
				log("nob::ntv::get_entity_addr: not found!");
				//finded = false;
			}

			if (program::version >= 757) {

				if (program::version >= 1290) {
					thread_t::id_count = program::code.match_rel_ptr({
						0x8B, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0x05, 1111, 1111, 1111, 1111, 0xFF, 0xC2
					});
				} else {
					thread_t::id_count = program::code.match_rel_ptr({
						0x89, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0x0C, 0xD8
					});
				}

				if (!thread_t::id_count) {
					log("nob::ntv::thread_t::id_count: not found!");
					//finded = false;
				}

				fake_script_hash_count = program::code.match_rel_ptr({
					0xFF, 0x0D, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0xF9
				});

				if (!fake_script_hash_count) {
					log("nob::ntv::fake_script_hash_count: not found!");
					//finded = false;
				}

			} else {

				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L381

				auto addr = program::code.match({
					0xFF, 0x40, 0x5C, 0x8B, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B
				}).data();

				if (addr) {
					thread_t::id_count = rua::bin_ref(addr).match_rel_ptr({
						0xFF, 0x40, 0x5C, 0x8B, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B
					});
					addr = addr - 9;
					fake_script_hash_count = (addr + *addr.to<int32_t *>() + 4);
				} else {
					thread_t::id_count = nullptr;
					fake_script_hash_count = nullptr;
					log("nob::ntv::thread_t::id_count: not found!");
					log("nob::ntv::fake_script_hash_count: not found!");
					//finded = false;
				}
			}

			script_executor = program::code.match_rel_ptr({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L393
				0x74, 0x17, 0x48, 0x8B, 0xC8, 0xE8, 1111, 1111, 1111, 1111, 0x48, 0x8D, 0x0D, 1111, 1111, 1111, 1111
			}, 1);

			if (!script_executor) {
				log("nob::ntv::script_executor: not found!");
				//finded = false;
			}

			uintptr_t module_tls = *(uintptr_t *)__readgsqword(88);

			base_thread_t::current = program::code.match_ptr({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L379
				1111, 1111, 1111, 1111, 0x48, 0x8B, 0x04, 0xD0, 0x4A, 0x8B, 0x14, 0x00, 0x48, 0x8B, 0x01, 0xF3, 0x44, 0x0F, 0x2C, 0x42, 0x20
			}) + module_tls;

			if (!base_thread_t::current) {
				log("nob::ntv::base_thread_t::current: not found!");
				//finded = false;
			}

			thread_t::pool = program::code.match_rel_ptr({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L357
				0x48, 0x8B, 0xC8, 0xEB, 0x03, 0x48, 0x8B, 0xCB, 0x48, 0x8B, 0x05, 1111, 1111, 1111, 1111
			});

			if (!thread_t::pool) {
				log("nob::ntv::thread_t::pool: not found!");
				//finded = false;
			}

			thread_t::_init = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L77
				0x83, 0x89, 0x38, 0x01, 0x00, 0x00, 0xFF, 0x83, 0xA1, 0x50, 0x01, 0x00, 0x00, 0xF0
			}).data();

			if (!thread_t::_init) {
				log("nob::ntv::thread_t::_init: not found!");
				//finded = false;
			}

			thread_t::_tick = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L40
				0x80, 0xB9, 0x46, 0x01, 0x00, 0x00, 0x00, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x74, 0x05
			}).data();

			if (!thread_t::_tick) {
				log("nob::ntv::thread_t::_tick: not found!");
				//finded = false;
			}

			thread_t::_kill = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L50
				0x48, 0x83, 0xEC, 0x20, 0x48, 0x83, 0xB9, 0x10, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8B, 0xD9, 0x74, 0x14
			}).data();

			if (!thread_t::_kill) {
				log("nob::ntv::thread_t::_kill: not found!");
				//finded = false;
			}

			return finded;
		}
	} /* ntv */
} /* nob */
