#include <nob/hash.hpp>
#include <nob/log.hpp>
#include <nob/ntv/base.hpp>
#include <nob/ntv/fhtt.hpp>
#include <nob/program.hpp>
#include <nob/window.hpp>

#include <rua/memory.hpp>
#include <rua/observer.hpp>
#include <rua/process.hpp>

namespace nob { namespace ntv {

std::recursive_mutex _scr_td_mtx;

script_thread_t::script_thread_t(void (*on_frame)(), void (*on_orig_kill)()) :
	script_thread_t() {
	if (!pool || !id_count || !script_context_pool || !fake_script_hash_count ||
		!tls_off) {
		return;
	}

	while (!*pool) {
		Sleep(100);
	}

	for (uint16_t i = 0; i < pool->count; ++i) {
		if (!(*pool)[i]->context.id) {
			_on_frame = on_frame;
			_on_orig_kill = on_orig_kill;
			vtable = &_vtab_impl;

			_vtab_impl.reset = [](script_thread_t *td,
								  uint32_t fake_script_hash,
								  uintptr_t *,
								  uint32_t) -> state_t {
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
						&td->script_hash_str,
						0,
						reinterpret_cast<uintptr_t>(
							&td->can_remove_blips_from_other_scripts) -
							reinterpret_cast<uintptr_t>(&td->script_hash_str) +
							8);
				}

				td->network_flag = true;
				td->can_remove_blips_from_other_scripts = false;

				td->exit_msg = "Normal exit";

				return td->context.state;
			};

			_vtab_impl.join = [](script_thread_t *td, uint32_t) -> state_t {
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
				_vtab_impl.tick = [](script_thread_t *td,
									 uint32_t ops_to_execute) -> state_t {
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
			*reinterpret_cast<uint32_t *>(&v14[v5]) =
				static_cast<uint32_t>(v13 ^ *reinterpret_cast<uint32_t *>(v5));
			v5 += 4;
			--c;
		} while (c);
		return reinterpret_cast<node_1290_t *>(result);
	}

	uint32_t length() const {
		return static_cast<uint32_t>(
			reinterpret_cast<uintptr_t>(&len1) ^ len1 ^ len2);
	}

	uint64_t hash(uint8_t ix) const {
		volatile uintptr_t n_addr =
			16 * ix + reinterpret_cast<uintptr_t>(&nxt1) + 0x54;
		volatile uint64_t c = 2;
		volatile uint64_t n_result;
		volatile auto v11 = (char *)&n_result - n_addr;
		volatile auto v10 = n_addr ^ *(uint32_t *)(n_addr + 8);
		do {
			*reinterpret_cast<uint32_t *>(&v11[n_addr]) = static_cast<uint32_t>(
				v10 ^ *reinterpret_cast<uint32_t *>(n_addr));
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
	for (auto n =
			 reinterpret_cast<T *const *>(lis)[hash % func_table_t::lists_size];
		 n;
		 n = n->next()) {
		for (uint8_t i = 0; i < n->length(); ++i) {
			if (n->hash(i) == hash) {
				return &n->funcs[i];
			}
		}
	}
	log("nob::ntv::func_table_t::find(",
		std::hex,
		hash,
		std::dec,
		"): not found!");
	return nullptr;
}

template <typename T>
size_t size(const func_table_t::list_t *lis) {
	if (!lis) {
		return 0;
	}
	size_t c = 0;
	for (size_t i = 0; i < func_table_t::lists_size; ++i) {
		for (auto n = reinterpret_cast<T *const *>(lis)[i]; n; n = n->next()) {
			for (uint8_t j = 0; j < n->length(); ++j) {
				++c;
			}
		}
	}
	return c;
}

template <typename T>
void inc_it(
	const func_table_t::list_t *lis,
	uint8_t &li_ix,
	func_table_t::list_t::node_t *&node,
	uint8_t &fn_ix) {
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

	for (auto i = static_cast<size_t>(li_ix) + 1; i < func_table_t::lists_size;
		 ++i) {
		for (n = reinterpret_cast<T *const *>(lis)[i]; n; n = n->next()) {
			for (uint8_t j = 0; j < n->length(); ++j) {
				li_ix = static_cast<uint8_t>(i);
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
void begin_it(
	const func_table_t::list_t *lis,
	uint8_t &li_ix,
	func_table_t::list_t::node_t *&node,
	uint8_t &fn_ix) {
	for (size_t i = 0; i < func_table_t::lists_size; ++i) {
		for (auto n = reinterpret_cast<T *const *>(lis)[i]; n; n = n->next()) {
			for (uint8_t j = 0; j < n->length(); ++j) {
				li_ix = static_cast<uint8_t>(i);
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

} // namespace _fn_tab

func_t *func_table_t::find(uint64_t hash) const {
	return game_build < 1290 ? _fn_tab::find<_fn_tab::node_t>(lists, hash)
							 : _fn_tab::find<_fn_tab::node_1290_t>(lists, hash);
}

size_t func_table_t::size() const {
	return game_build < 1290 ? _fn_tab::size<_fn_tab::node_t>(lists)
							 : _fn_tab::size<_fn_tab::node_1290_t>(lists);
}

std::pair<uint64_t, func_t &> func_table_t::iterator::operator*() const {
	return game_build < 1290
			   ? std::pair<uint64_t, func_t &>(
					 reinterpret_cast<_fn_tab::node_t *>(_node)->hash(_fn_ix),
					 reinterpret_cast<_fn_tab::node_t *>(_node)->funcs[_fn_ix])
			   : std::pair<uint64_t, func_t &>(
					 reinterpret_cast<_fn_tab::node_1290_t *>(_node)->hash(
						 _fn_ix),
					 reinterpret_cast<_fn_tab::node_1290_t *>(_node)
						 ->funcs[_fn_ix]);
}

func_table_t::iterator &func_table_t::iterator::operator++() {
	if (game_build < 1290) {
		_fn_tab::inc_it<_fn_tab::node_t>(_lis, _li_ix, _node, _fn_ix);
	} else {
		_fn_tab::inc_it<_fn_tab::node_1290_t>(_lis, _li_ix, _node, _fn_ix);
	}
	return *this;
}

func_table_t::iterator func_table_t::begin() const {
	iterator it(lists);
	if (game_build < 1290) {
		_fn_tab::begin_it<_fn_tab::node_t>(
			lists, it._li_ix, it._node, it._fn_ix);
	} else {
		_fn_tab::begin_it<_fn_tab::node_1290_t>(
			lists, it._li_ix, it._node, it._fn_ix);
	}
	return it;
}

global_table_t global_table;

script_list_t *script_list = nullptr;

game_state_t *game_state = nullptr;

func_t call_context_t::res_fixer = nullptr;

func_table_t *func_table = nullptr;

full_call_context_t _dft_call_ctx;

entity_obj_map_t **entity_obj_map = nullptr;

script_context_pool_t *script_context_pool = nullptr;

uint32_t *fake_script_hash_count = nullptr;

uint32_t script_thread_t::tls_off = 0;

container_t<script_thread_t *> *script_thread_t::pool = nullptr;

uint32_t *script_thread_t::id_count = nullptr;

void (*script_thread_t::init_gta_data)(script_thread_t *) = nullptr;

script_thread_t::state_t (*script_thread_t::default_tick)(
	script_thread_t *, uint32_t ops_to_execute) = nullptr;

void (*script_thread_t::default_kill)(script_thread_t *) = nullptr;

bool _pre_init_when_no_wnd = false;

void _pre_init() {
	if (!window::is_visible()) {
#ifdef NOB_FAST_LAUNCH
		auto mr = game_code.match(
			{0x70, 0x6C, 0x61, 0x74, 0x66, 0x6F, 0x72, 0x6D, 0x3A});
		if (mr.size()) {
			auto addr = mr[0].data();
			rua::mem_chmod(addr, 1);
			rua::bit_as<uint8_t>(addr) = 0xC3;
		} else {
			log("nob::ntv::_init::disable_welcome_animation: not found!");
		}
#endif
		_pre_init_when_no_wnd = true;
	}
}

bool _init() {
	auto finded = true;

	// Reference from
	// https://github.com/MockbaTheBorg/GTALuaF/blob/master/PHP/patternsGTA.txt#L10
	auto mr = game_code.match(
		{0x83, 0x3D, 1111, 1111, 1111, 1111, 1111, 0x8A, 0xD9, 0x74, 0x0A});
	if (mr.size()) {
		game_state = mr[1].derel<int32_t, 5>();
	}

	if (!game_state || _pre_init_when_no_wnd) {
		rua::masked_bytes mov_gs_6_pat({0xC7,
										0x05,
										1111,
										1111,
										1111,
										1111,
										0x06,
										0x00,
										0x00,
										0x00,
										0xEB,
										0x3F});
		auto pos_o = game_code.match_pos(mov_gs_6_pat);
		if (pos_o) {
			auto mp = pos_o.value();
			if (!game_state) {
				game_state = game_code.derel<int32_t>(mp + 2);
			}
#ifdef NOB_FAST_LAUNCH
			if (_pre_init_when_no_wnd) {
				constexpr size_t skip_sz_b = 0x1C;
				size_t skip_sz;

				auto code = game_code(mp - skip_sz_b);
				if (code.get<uint32_t>() == 0x7501F883) {
					pos_o = game_code(mp + mov_gs_6_pat.size())
								.match_pos({0xC7,
											0x05,
											1111,
											1111,
											1111,
											1111,
											0x08,
											0x00,
											0x00,
											0x00});
					if (pos_o) {
						skip_sz =
							skip_sz_b + mov_gs_6_pat.size() + pos_o.value();
						rua::mem_chmod(code.data(), skip_sz);
						memset(code.data(), 0x90, skip_sz);
					} else {
						log("nob::ntv::_init: (*game_state = 8) not found!");
					}
				} else {
					log("nob::ntv::_init: 'game_state_handler()' not found!");
				}
			}
#endif
		} else {
			log("nob::ntv::_init: (*game_state = 6) not found!");
		}
	}

	if (!game_state) {
		log("nob::ntv::game_state: not found!");
		finded = false;
	}

#ifdef NOB_FAST_LAUNCH
	if (_pre_init_when_no_wnd) {
		mr = game_code.match(
			{0x72, 0x1F, 0xE8, 1111, 1111, 1111, 1111, 0x8B, 0x0D});
		if (mr.size()) {
			auto addr = mr[0].data();
			rua::mem_chmod(addr, 2);
			rua::bit_as<uint16_t>(addr) = 0x9090;
		} else {
			log("nob::ntv::_init::disable_usage_notice_page: not found!");
			// finded = false;
		}
	}
#endif

	auto fhtt_it = fhtt_map.find(game_build);
	if (fhtt_it != fhtt_map.end()) {
		fhtt = fhtt_it->second;
	} else {
		log("nob::ntv::fhtt: not found!");
		fhtt = fhtt_map.rbegin()->second;
		finded = false;
	}

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	mr = game_code.match({0x4C,
						  0x8D,
						  0x05,
						  1111,
						  1111,
						  1111,
						  1111,
						  0x4D,
						  0x8B,
						  0x08,
						  0x4D,
						  0x85,
						  0xC9,
						  0x74,
						  0x11});
	if (mr.size()) {
		global_table._segments = mr[1].derel<int32_t>();
	} else {
		log("nob::ntv::global_table::_segments: not found!");
		finded = false;
	}

	// Reference from
	// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L104
	mr = game_code.match({0x83,
						  0x79,
						  0x18,
						  1111,
						  0x48,
						  0x8B,
						  0xD1,
						  0x74,
						  0x4A,
						  0xFF,
						  0x4A,
						  0x18});
	if (mr.size()) {
		call_context_t::res_fixer = mr[0].data();
	} else {
		log("nob::ntv::call_context_t::res_fixer: not found!");
		finded = false;
	}

	// Reference from
	// https://www.unknowncheats.me/forum/2061818-post2131.html
	if (game_build >= 1365) {
		mr = game_code.match({0x76,
							  1111,
							  1111,
							  0x8b,
							  1111,
							  1111,
							  0x48,
							  0x8d,
							  0x0d,
							  1111,
							  1111,
							  1111,
							  1111,
							  1111,
							  0x8b,
							  1111,
							  1111,
							  1111});
		if (mr.size()) {
			func_table = mr[3].derel<int32_t>();
		} else {
			log("nob::ntv::func_table: not found!");
			finded = false;
		}

	} else {
		if (game_build >= 1290) { // Reference from
			// https://www.unknowncheats.me/forum/1932632-post1648.html
			mr = game_code.match({0x40,
								  0x53,
								  0x48,
								  0x83,
								  0xEC,
								  0x20,
								  0x48,
								  0x8D,
								  0x1D,
								  1111,
								  1111,
								  1111,
								  1111,
								  0x4C,
								  0x8D,
								  0x05});
		} else {
			// Reference from
			// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L389
			mr = game_code.match({0x76,
								  0x61,
								  0x49,
								  0x8B,
								  0x7A,
								  0x40,
								  0x48,
								  0x8D,
								  0x0D,
								  1111,
								  1111,
								  1111,
								  1111});
		}
		if (mr.size()) {
			func_table = mr[1].derel<int32_t>();
		} else {
			log("nob::ntv::func_table: not found!");
			finded = false;
		}
	}

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	mr = game_code.match({0x48,
						  0x03,
						  0x15,
						  1111,
						  1111,
						  1111,
						  1111,
						  0x4C,
						  0x23,
						  0xC2,
						  0x49,
						  0x8B,
						  0x08});
	if (mr.size()) {
		script_list = mr[1].derel<int32_t>();
	} else {
		log("nob::ntv::script_list: not found!");
		finded = false;
	}

	// Reference from
	// https://github.com/JLFSL/FiveMultiplayer/blob/dev/Client/Core/MemoryAccess.h#L23
	mr = game_code.match(
		{0x4C, 0x8B, 0x05, 1111, 1111, 1111, 1111, 0x49, 0x2B, 0x00});
	if (mr.size()) {
		entity_obj_map = mr[1].derel<int32_t>();
	} else {
		log("nob::ntv::entity_obj_map: not found!");
		finded = false;
	}

	if (game_build >= 757) {
		if (game_build >= 1290) {
			mr = game_code.match({0x8B,
								  0x15,
								  1111,
								  1111,
								  1111,
								  1111,
								  0x48,
								  0x8B,
								  0x05,
								  1111,
								  1111,
								  1111,
								  1111,
								  0xFF,
								  0xC2});
		} else {
			mr = game_code.match(
				{0x89, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0x0C, 0xD8});
		}

		if (mr.size()) {
			script_thread_t::id_count = mr[1].derel<int32_t>();
		} else {
			log("nob::ntv::script_thread_t::id_count: not found!");
			// finded = false;
		}

		mr = game_code.match(
			{0xFF, 0x0D, 1111, 1111, 1111, 1111, 0x48, 0x8B, 0xF9});
		if (mr.size()) {
			fake_script_hash_count = mr[1].derel<int32_t>();
		} else {
			log("nob::ntv::fake_script_hash_count: not found!");
			// finded = false;
		}
	} else {
		// Reference from
		// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L381
		auto pos_o = game_code.match_pos(
			{0xFF, 0x40, 0x5C, 0x8B, 0x15, 1111, 1111, 1111, 1111, 0x48, 0x8B});

		if (pos_o) {
			auto game_code_slice = game_code(pos_o.value());
			script_thread_t::id_count = game_code_slice.derel<int32_t>(
				game_code_slice.match({0xFF,
									   0x40,
									   0x5C,
									   0x8B,
									   0x15,
									   1111,
									   1111,
									   1111,
									   1111,
									   0x48,
									   0x8B})[0]);
			fake_script_hash_count = game_code_slice.derel<int32_t>(-9);
		} else {
			log("nob::ntv::script_thread_t::id_count: not found!");
			log("nob::ntv::fake_script_hash_count: not found!");
			// finded = false;
		}
	}

	// Reference from
	// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L393
	mr = game_code.match({0x74,
						  0x17,
						  0x48,
						  0x8B,
						  0xC8,
						  0xE8,
						  1111,
						  1111,
						  1111,
						  1111,
						  0x48,
						  0x8D,
						  0x0D,
						  1111,
						  1111,
						  1111,
						  1111});
	if (mr.size()) {
		script_context_pool = mr[2].derel<int32_t>();
	} else {
		log("nob::ntv::script_context_pool: not found!");
		// finded = false;
	}

	// Reference from
	// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L379
	mr = game_code.match({1111, 1111, 1111, 1111, 0x48, 0x8B, 0x04,
						  0xD0, 0x4A, 0x8B, 0x14, 0x00, 0x48, 0x8B,
						  0x01, 0xF3, 0x44, 0x0F, 0x2C, 0x42, 0x20});
	if (mr.size()) {
		script_thread_t::tls_off = mr[0].get<int32_t>();
	} else {
		log("nob::ntv::script_thread_t::tls_off: not found!");
		// finded = false;
	}

	// Reference from
	// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrEngine.cpp#L357
	mr = game_code.match({0x48,
						  0x8B,
						  0xC8,
						  0xEB,
						  0x03,
						  0x48,
						  0x8B,
						  0xCB,
						  0x48,
						  0x8B,
						  0x05,
						  1111,
						  1111,
						  1111,
						  1111});
	if (mr.size()) {
		script_thread_t::pool = mr[1].derel<int32_t>();
	} else {
		log("nob::ntv::script_thread_t::pool: not found!");
		// finded = false;
	}

	// Reference from
	// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L77
	mr = game_code.match({0x83,
						  0x89,
						  0x38,
						  0x01,
						  0x00,
						  0x00,
						  0xFF,
						  0x83,
						  0xA1,
						  0x50,
						  0x01,
						  0x00,
						  0x00,
						  0xF0});

	if (mr.size()) {
		script_thread_t::init_gta_data = mr[0].data();
	} else {
		log("nob::ntv::script_thread_t::init_gta_data: not found!");
		// finded = false;
	}

	// Reference from
	// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L40
	mr = game_code.match({0x80,
						  0xB9,
						  0x46,
						  0x01,
						  0x00,
						  0x00,
						  0x00,
						  0x8B,
						  0xFA,
						  0x48,
						  0x8B,
						  0xD9,
						  0x74,
						  0x05});

	if (mr.size()) {
		script_thread_t::default_tick = mr[0].data() - 0xF;
	} else {
		log("nob::ntv::script_thread_t::default_tick: not found!");
		// finded = false;
	}

	// Reference from
	// https://github.com/GTA-Lion/citizenmp/blob/master/components/rage-scripting-five/src/scrThread.cpp#L50
	mr = game_code.match({0x48,
						  0x83,
						  0xEC,
						  0x20,
						  0x48,
						  0x83,
						  0xB9,
						  0x10,
						  0x01,
						  0x00,
						  0x00,
						  0x00,
						  0x48,
						  0x8B,
						  0xD9,
						  0x74,
						  0x14});

	if (mr.size()) {
		script_thread_t::default_kill = mr[0].data() - 6;
	} else {
		log("nob::ntv::script_thread_t::default_kill: not found!");
		// finded = false;
	}

	return finded;
}

}} // namespace nob::ntv
