#include <nob/ntv/base.hpp>
#include <nob/ntv/fhtt.hpp>
#include <nob/program.hpp>
#include <nob/hash.hpp>
#include <nob/log.hpp>

namespace nob {
	namespace ntv {
		std::recursive_mutex _scr_td_mtx;

		script_thread_t::script_thread_t(void (*on_frame)(), void (*on_orig_kill)()) : script_thread_t() {
			if (
				!pool ||
				!id_count ||
				!script_context_pool ||
				!fake_script_hash_count ||
				!tls_off
			) {
				return;
			}

			while (!*pool) {
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}

			for (size_t i = 0; i < pool->count; ++i) {
				if (!(*pool)[i]->context.id) {
					_on_frame = on_frame;
					_on_orig_kill = on_orig_kill;
					vtable = &_vtab_impl;

					_vtab_impl.reset = [](script_thread_t *td, uint32_t fake_script_hash, uintptr_t *, uint32_t)->state_t {
						memset(&td->context, 0, sizeof(script_thread_t::context_t));

						td->context.state = state_t::idle;
						td->context.fake_script_hash = fake_script_hash;
						td->context._munk1 = -1;
						td->context._munk2 = -1;

						td->context._set1 = 1;

						if (init_gta_data) {
							init_gta_data(td);
						} else {
							memset(
								&td->script_hash_str, 0,
								reinterpret_cast<uintptr_t>(&td->can_remove_blips_from_other_scripts) -
								reinterpret_cast<uintptr_t>(&td->script_hash_str)
								+ 8
							);
						}

						td->network_flag = true;
						td->can_remove_blips_from_other_scripts = false;

						td->exit_msg = "Normal exit";

						return td->context.state;
					};

					_vtab_impl.join = [](script_thread_t *td, uint32_t)->state_t {
						std::scoped_lock<std::recursive_mutex> lock(_scr_td_mtx);

						if (td->context.state != state_t::killed) {
							if (!td->script_context) {
								script_context_pool->alloc(td);
							}

							auto cur = script_thread_t::current();
							script_thread_t::current() = td;
							td->_on_frame();
							script_thread_t::current() = cur;
						}

						return td->context.state;
					};

					if (default_tick) {
						_vtab_impl.tick = default_tick;
					} else {
						_vtab_impl.tick = [](script_thread_t *td, uint32_t ops_to_execute)->state_t {
							return td->vtable->join(td, ops_to_execute);
						};
					}

					_vtab_impl.kill = [](script_thread_t *td) {
						if (td->_on_orig_kill) {
							td->_on_orig_kill();
						}
					};

					_vtab_impl._dtor = [](script_thread_t *td) {
						log("nob::ntv::script_thread_t: delete ", td, " by native!");
					};

					auto fake_script_hash = ++(*fake_script_hash_count);

					_vtab_impl.reset(this, fake_script_hash, nullptr, 0);

					if (!context.stack_size) {
						stack = new uint8_t[2048];
						context.stack_size = 2048;
					}

					if (!*id_count) {
						++(*id_count);
					}
					context.id = (*id_count)++;

					_orig_owner = (*pool)[i];
					(*pool)[i] = this;

					return;
				}
			}
		}

		void script_thread_t::kill() {
			std::scoped_lock<std::recursive_mutex> lock(_scr_td_mtx);

			if (context.state == state_t::killed) {
				return;
			}

			if (default_kill) {
				default_kill(this);
			} else {
				context.state = state_t::killed;
				if (script_context) {
					script_context_pool->dealloc(this);
				}
			}

			for (int i = 0; i < pool->count; ++i) {
				if ((*pool)[i] == this) {
					(*pool)[i] = _orig_owner;
					_orig_owner = nullptr;
					break;
				}
			}

			if (stack) {
				delete[] stack;
				stack = nullptr;
				context.stack_size = 0;
			}
		};

		namespace _fn_tab {
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

			template <typename T>
			func_t *find(const func_table_t::list_t *lis, uint64_t hash) {
				if (!lis) {
					return nullptr;
				}
				for (auto n = reinterpret_cast<T * const *>(lis)[hash % func_table_t::lists_size]; n; n = n->next()) {
					for (uint8_t i = 0; i < n->length(); ++i) {
						if (n->hash(i) == hash) {
							return &n->funcs[i];
						}
					}
				}
				log("nob::ntv::func_table_t::find(", std::hex, hash, std::dec, "): not found!");
				return nullptr;
			}

			template <typename T>
			size_t size(const func_table_t::list_t *lis) {
				if (!lis) {
					return 0;
				}
				size_t c = 0;
				for (size_t i = 0; i < func_table_t::lists_size; ++i) {
					for (auto n = reinterpret_cast<T * const *>(lis)[i]; n; n = n->next()) {
						for (uint8_t j = 0; j < n->length(); ++j) {
							++c;
						}
					}
				}
				return c;
			}

			template <typename T>
			void inc_it(const func_table_t::list_t *lis, uint8_t &li_ix, func_table_t::list_t::node_t *&node, uint8_t &fn_ix) {
				assert(node);

				auto n = reinterpret_cast<T *>(node);
				if (++fn_ix < n->length()) {
					return;
				}

				for (n = n->next(); n; n = n->next()) {
					for (uint8_t i = 0; i < n->length(); ++i) {
						node = reinterpret_cast<func_table_t::list_t::node_t *>(n);
						fn_ix = i;
						return;
					}
				}

				for (size_t i = static_cast<size_t>(li_ix) + 1; i < func_table_t::lists_size; ++i) {
					for (n = reinterpret_cast<T * const *>(lis)[i]; n; n = n->next()) {
						for (uint8_t j = 0; j < n->length(); ++j) {
							li_ix = i;
							node = reinterpret_cast<func_table_t::list_t::node_t *>(n);
							fn_ix = j;
							return;
						}
					}
				}

				li_ix = 0;
				node = nullptr;
				fn_ix = 0;
			}

			template <typename T>
			void begin_it(const func_table_t::list_t *lis, uint8_t &li_ix, func_table_t::list_t::node_t *&node, uint8_t &fn_ix) {
				for (size_t i = 0; i < func_table_t::lists_size; ++i) {
					for (auto n = reinterpret_cast<T * const *>(lis)[i]; n; n = n->next()) {
						for (uint8_t j = 0; j < n->length(); ++j) {
							li_ix = i;
							node = reinterpret_cast<func_table_t::list_t::node_t *>(n);
							fn_ix = j;
							return;
						}
					}
				}

				li_ix = 0;
				node = nullptr;
				fn_ix = 0;
			}
		}

		func_t *func_table_t::find(uint64_t hash) const {
			return
				program::version < 1290 ?
				_fn_tab::find<_fn_tab::node_t>(lists, hash) :
				_fn_tab::find<_fn_tab::node_1290_t>(lists, hash)
			;
		}

		size_t func_table_t::size() const {
			return
				program::version < 1290 ?
				_fn_tab::size<_fn_tab::node_t>(lists) :
				_fn_tab::size<_fn_tab::node_1290_t>(lists)
			;
		}

		std::pair<uint64_t, func_t &> func_table_t::iterator::operator*() const {
			return
				program::version < 1290 ?
				std::pair<uint64_t, func_t &>(
					reinterpret_cast<_fn_tab::node_t *>(_node)->hash(_fn_ix),
					reinterpret_cast<_fn_tab::node_t *>(_node)->funcs[_fn_ix]
				) :
				std::pair<uint64_t, func_t &>(
					reinterpret_cast<_fn_tab::node_1290_t *>(_node)->hash(_fn_ix),
					reinterpret_cast<_fn_tab::node_1290_t *>(_node)->funcs[_fn_ix]
				)
			;
		}

		func_table_t::iterator &func_table_t::iterator::operator++() {
			if (program::version < 1290) {
				_fn_tab::inc_it<_fn_tab::node_t>(_lis, _li_ix, _node, _fn_ix);
			} else {
				_fn_tab::inc_it<_fn_tab::node_1290_t>(_lis, _li_ix, _node, _fn_ix);
			}
			return *this;
		}

		func_table_t::iterator func_table_t::begin() const {
			iterator it(lists);
			if (program::version < 1290) {
				_fn_tab::begin_it<_fn_tab::node_t>(lists, it._li_ix, it._node, it._fn_ix);
			} else {
				_fn_tab::begin_it<_fn_tab::node_1290_t>(lists, it._li_ix, it._node, it._fn_ix);
			}
			return it;
		}

		global_table_t global_table;

		script_list_t *script_list;

		game_state_t *game_state;

		func_t call_context_t::res_fixer;

		func_table_t *func_table = nullptr;

		full_call_context_t _dft_call_ctx;

		entity_instance_map_t **entity_instance_map;

		script_context_pool_t *script_context_pool;

		uint32_t *fake_script_hash_count;

		uint32_t script_thread_t::tls_off;

		container_t<script_thread_t *> *script_thread_t::pool;

		uint32_t *script_thread_t::id_count;

		void (*script_thread_t::init_gta_data)(script_thread_t *);

		script_thread_t::state_t (*script_thread_t::default_tick)(script_thread_t *, uint32_t ops_to_execute) = nullptr;

		void (*script_thread_t::default_kill)(script_thread_t *) = nullptr;

		bool _init() {
			auto finded = true;

			auto fhtt_it = fhtt_map.find(program::version);
			if (fhtt_it != fhtt_map.end()) {
				fhtt = &fhtt_it->second;
			} else {
				log("nob::ntv::fhtt: not found!");
				fhtt = &fhtt_map.rbegin()->second;
				//finded = false;
			}

			auto mrs = program::code.match_sub({
				// Reference from https://github.com/zorg93/EnableMpCars-GTAV
				0x4C, 0x8D, 0x05, 1111, 1111, 1111, 1111, 0x4D, 0x8B, 0x08,
				0x4D, 0x85, 0xC9, 0x74, 0x11
			});

			if (mrs.empty() || !(global_table._segments = mrs[0].derelative<int32_t>())) {
				log("nob::ntv::global_table::_segments: not found!");
				finded = false;
			}

			call_context_t::res_fixer = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L104
				0x83, 0x79, 0x18, 1111, 0x48, 0x8B, 0xD1, 0x74, 0x4A, 0xFF, 0x4A, 0x18
			}).base();

			if (!call_context_t::res_fixer) {
				log("nob::ntv::call_context_t::res_fixer: not found!");
				finded = false;
			}

			if (program::version >= 1365) {
				mrs = program::code.match_sub({
					// Reference from https://www.unknowncheats.me/forum/2061818-post2131.html
					0x76, 1111, 1111, 0x8b, 1111, 1111, 0x48, 0x8d, 0x0d, 1111, 1111, 1111, 1111, 1111, 0x8b, 1111, 1111, 1111
				});

				if (mrs.empty() || !(func_table = mrs[2].derelative<int32_t>())) {
					log("nob::ntv::func_table: not found!");
					finded = false;
				}

			} else {
				if (program::version >= 1290) {
					mrs = program::code.match_sub({
						// Reference from https://www.unknowncheats.me/forum/1932632-post1648.html
						0x40, 0x53, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8D, 0x1D, 1111, 1111, 1111, 1111, 0x4C, 0x8D, 0x05
					});
				} else {
					mrs = program::code.match_sub({
						// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L389
						0x76, 0x61, 0x49, 0x8B, 0x7A, 0x40, 0x48, 0x8D, 0x0D, 1111, 1111, 1111, 1111
					});
				}

				if (mrs.empty() || !(func_table = mrs[0].derelative<int32_t>())) {
					log("nob::ntv::func_table: not found!");
					finded = false;
				}
			}

			mrs = program::code.match_sub({
				// Reference from https://github.com/zorg93/EnableMpCars-GTAV
				0x48, 0x03, 0x15, 1111, 1111, 1111, 1111, 0x4C, 0x23, 0xC2,
				0x49, 0x8B, 0x08
			});

			if (mrs.empty() || !(script_list = mrs[0].derelative<int32_t>())) {
				log("nob::ntv::script_list: not found!");
				finded = false;
			}

			mrs = program::code.match_sub({
				// Reference from https://github.com/MockbaTheBorg/GTALuaF/blob/master/PHP/patternsGTA.txt#L10
				0x83, 0x3D, 1111, 1111, 1111, 1111, 1111, 0x8A, 0xD9, 0x74, 0x0A
			});

			if (mrs.empty() || !(game_state = rua::unsafe_ptr(mrs[0].derelative<int32_t>().value()++))) {
				log("nob::ntv::game_state: not found!");
				finded = false;
			}

			mrs = program::code.match_sub({
				// Reference from https://github.com/JLFSL/FiveMultiplayer/blob/dev/Client/Core/MemoryAccess.h#L23
				0x4C, 0x8B, 0x05, 1111, 1111, 1111, 1111, 0x49, 0x2B, 0x00
			});

			if (mrs.empty() || !(entity_instance_map = mrs[0].derelative<int32_t>())) {
				log("nob::ntv::entity_instance_map: not found!");
				//finded = false;
			}

			if (program::version >= 757) {

				if (program::version >= 1290) {
					mrs = program::code.match_sub({
						0x8B, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0x05, 1111, 1111, 1111, 1111, 0xFF, 0xC2
					});
				} else {
					mrs = program::code.match_sub({
						0x89, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0x0C, 0xD8
					});
				}

				if (mrs.empty() || !(script_thread_t::id_count = mrs[0].derelative<int32_t>())) {
					log("nob::ntv::script_thread_t::id_count: not found!");
					//finded = false;
				}

				mrs = program::code.match_sub({
					0xFF, 0x0D, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0xF9
				});

				if (mrs.empty() || !(fake_script_hash_count = mrs[0].derelative<int32_t>())) {
					log("nob::ntv::fake_script_hash_count: not found!");
					//finded = false;
				}

			} else {

				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L381

				auto mr = program::code.match({
					0xFF, 0x40, 0x5C, 0x8B, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B
				});

				if (mr) {
					script_thread_t::id_count = mr.match_sub({
						0xFF, 0x40, 0x5C, 0x8B, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B
					})[0].derelative<int32_t>();
					fake_script_hash_count = mr.derelative<int32_t>(-9);
				} else {
					script_thread_t::id_count = nullptr;
					fake_script_hash_count = nullptr;
					log("nob::ntv::script_thread_t::id_count: not found!");
					log("nob::ntv::fake_script_hash_count: not found!");
					//finded = false;
				}
			}

			/*auto code_block_1 = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/ScriptHandlerMgr.cpp#L33
				0x80, 0x78, 0x32, 0x00, 0x75, 0x34, 0xB1, 0x01, 0xE8
			});
			if (code_block_1) {
				rua::unsafe_ptr addr = code_block_1.base().value() + 4;
				VirtualProtect(addr, 2, PAGE_EXECUTE_READWRITE, nullptr);
				*(addr).to<uint8_t *>() = 0xEB;
			} else {
				log("nob::ntv::_find_addrs::code_block_1: not found!");
			}*/

			mrs = program::code.match_sub({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L393
				0x74, 0x17, 0x48, 0x8B, 0xC8, 0xE8, 1111, 1111, 1111, 1111, 0x48, 0x8D, 0x0D, 1111, 1111, 1111, 1111
			});

			if (mrs.empty() || !(script_context_pool = mrs[1].derelative<int32_t>())) {
				log("nob::ntv::script_context_pool: not found!");
				//finded = false;
			}

			auto mr = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L379
				1111, 1111, 1111, 1111, 0x48, 0x8B, 0x04, 0xD0, 0x4A, 0x8B, 0x14, 0x00, 0x48, 0x8B, 0x01, 0xF3, 0x44, 0x0F, 0x2C, 0x42, 0x20
			});

			if (!mr || !(script_thread_t::tls_off = mr.get<int32_t>())) {
				log("nob::ntv::script_thread_t::tls_off: not found!");
				//finded = false;
			}

			mrs = program::code.match_sub({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L357
				0x48, 0x8B, 0xC8, 0xEB, 0x03, 0x48, 0x8B, 0xCB, 0x48, 0x8B, 0x05, 1111, 1111, 1111, 1111
			});

			if (mrs.empty() || !(script_thread_t::pool = mrs[0].derelative<int32_t>())) {
				log("nob::ntv::script_thread_t::pool: not found!");
				//finded = false;
			}

			script_thread_t::init_gta_data = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L77
				0x83, 0x89, 0x38, 0x01, 0x00, 0x00, 0xFF, 0x83, 0xA1, 0x50, 0x01, 0x00, 0x00, 0xF0
			}).base();

			if (!script_thread_t::init_gta_data) {
				log("nob::ntv::script_thread_t::init_gta_data: not found!");
				//finded = false;
			}

			mr = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L40
				0x80, 0xB9, 0x46, 0x01, 0x00, 0x00, 0x00, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x74, 0x05
			});

			if (mr) {
				script_thread_t::default_tick = rua::unsafe_ptr(mr.base().value() - 0xF);
			} else {
				log("nob::ntv::script_thread_t::default_tick: not found!");
				//finded = false;
			}

			mr = program::code.match({
				// Reference from https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L50
				0x48, 0x83, 0xEC, 0x20, 0x48, 0x83, 0xB9, 0x10, 0x01, 0x00, 0x00, 0x00, 0x48, 0x8B, 0xD9, 0x74, 0x14
			});

			if (mr) {
				script_thread_t::default_kill = rua::unsafe_ptr(mr.base().value() - 6);
			} else {
				log("nob::ntv::script_thread_t::default_kill: not found!");
				//finded = false;
			}

			return finded;
		}
	} /* ntv */
} /* nob */
