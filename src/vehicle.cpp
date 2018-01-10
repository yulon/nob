#include <nob/object.hpp>
#include <nob/hash.hpp>
#include <nob/script.hpp>
#include <nob/log.hpp>

#include <rua/bin.hpp>
#include <rua/unsafe_ptr.hpp>

#include <thread>
#include <queue>

namespace nob {
	std::vector<model> _ban_vehs;

	static ntv::script_list_t::node_t *_shop_ctrllr_n = nullptr;

	size_t _ban_vehs_g, _ban_vehs_li_find_base;
	bool _finded_ban_vehs = false, _finding_ban_vehs = false;

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	bool _find_ban_vehs() {
		if (_finded_ban_vehs) {
			return true;
		}

		if (_finding_ban_vehs) {
			wait([]()->bool {
				return !_finding_ban_vehs;
			});
			return _finded_ban_vehs;
		}

		_finding_ban_vehs = true;

		if (!ntv::SCRIPT::HAS_SCRIPT_LOADED("shop_controller")) {
			wait([]()->bool {
				return ntv::SCRIPT::HAS_SCRIPT_LOADED("shop_controller");
			});
		}

		if (!_shop_ctrllr_n) {
			_shop_ctrllr_n = ntv::script_list->find("shop_controller");
			if (!_shop_ctrllr_n) {
				return false;
			}
		}

		//ntv::wait_for_valid(_shop_ctrllr_n->script);
		//ntv::wait_for_valid(*_shop_ctrllr_n->script);

		chan<bool> f_ch;
		chan<size_t> g_ch;

		std::thread([f_ch, g_ch]() mutable {
			auto &_shop_ctrllr = *_shop_ctrllr_n->script;
			for (size_t i = 0; i < _shop_ctrllr.code_pages_count(); ++i) {
				auto addr = rua::bin_ref(
					_shop_ctrllr.code_pages[i],
					_shop_ctrllr.code_page_length(i)
				).match({0x28, 0x26, 0xCE, 0x6B, 0x86, 0x39, 0x03}).data();
				if (!addr) {
					continue;
				}
				size_t code_off = _shop_ctrllr.code_off(i, addr);
				for (size_t j = 0; j < 2000; j++) {
					if (*(uint32_t *)_shop_ctrllr.code_addr(code_off - j) == 0x0008012D) {
						size_t func_off = *(uint32_t *)_shop_ctrllr.code_addr(code_off - j + 6) & 0xFFFFFF;
						for (size_t k = 0x5; k < 0x40; k++) {
							if ((*(uint32_t *)_shop_ctrllr.code_addr(func_off + k) & 0xFFFFFF) == 0x01002E) {
								for (k = k + 1; k < 30; k++) {
									if (*(uint8_t *)_shop_ctrllr.code_addr(func_off + k) == 0x5F) {
										g_ch
											<< (*(uint32_t *)_shop_ctrllr.code_addr(func_off + k + 1) & 0xFFFFFF)
											<< code_off - j
										;
										f_ch << true;
										return;
									}
								}
								break;
							}
						}
						break;
					}
				}
				break;
			}
			g_ch << SIZE_MAX << SIZE_MAX;
			f_ch << false;
		}).detach();

		g_ch >> _ban_vehs_g >> _ban_vehs_li_find_base;

		f_ch >> _finded_ban_vehs;

		_finding_ban_vehs = false;

		return _finded_ban_vehs;
	}

	void unlock_banned_vehicles() {
		if (_find_ban_vehs()) {
			ntv::global_table[_ban_vehs_g] = 1;
		}
	}

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	const std::vector<model> &banned_vehicles() {
		if (_ban_vehs.size() || !_find_ban_vehs()) {
			return _ban_vehs;
		}

		if (!ntv::SCRIPT::HAS_SCRIPT_LOADED("shop_controller")) {
			wait([]()->bool {
				return ntv::SCRIPT::HAS_SCRIPT_LOADED("shop_controller");
			});
		}

		//ntv::wait_for_valid(_shop_ctrllr_n->script);
		//ntv::wait_for_valid(*_shop_ctrllr_n->script);

		chan<std::vector<model>> vehs_ch;

		std::thread([vehs_ch]() mutable {
			auto &_shop_ctrllr = *_shop_ctrllr_n->script;
			std::vector<model> vehs;
			for (size_t i = 14; i < 400; i++) {
				if (*(uint8_t *)_shop_ctrllr.code_addr(_ban_vehs_li_find_base + i) == 0x62) {
					size_t switch_off = _ban_vehs_li_find_base + i;
					auto cur_addr = (uint64_t)_shop_ctrllr.code_addr(switch_off + 2);
					size_t start_off = switch_off + 2;
					size_t cases = *(uint8_t *)(cur_addr - 1);
					for (size_t i = 0; i < cases; i++) {
						cur_addr += 6;
						start_off += 6;
						size_t jump_off = *(uint16_t *)(cur_addr - 2);
						int64_t case_off = (int64_t)_shop_ctrllr.code_addr(start_off + jump_off);
						uint8_t code = *(uint8_t *)case_off;
						hash_t hash;
						if (code == 0x28) { //push int
							hash = *(uint32_t *)(case_off + 1);
						} else if(code == 0x61) { //push int 24
							hash = *(uint32_t *)(case_off + 1) & 0xFFFFFF;
						} else {
							continue;
						}
						vehs.emplace_back(hash);
					}
					break;
				}
			}
			vehs_ch << std::move(vehs);
		}).detach();

		vehs_ch >> _ban_vehs;

		return _ban_vehs;
	}

	std::vector<model> _dlc_vehs;

	const std::vector<model> &dlc_vehicles() {
		if (_dlc_vehs.size()) {
			return _dlc_vehs;
		}
		for (int i = 0; i < ntv::DLC1::GET_NUM_DLC_VEHICLES(); ++i) {
			_dlc_vehs.emplace_back(ntv::DLC1::GET_DLC_VEHICLE_MODEL(i));
		}
		return _dlc_vehs;
	}
} /* nob */
