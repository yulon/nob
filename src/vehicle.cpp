#include <nob/object.hpp>
#include <nob/hack.hpp>
#include <nob/hash.hpp>
#include <nob/script.hpp>

#include <thread>
#include <queue>

namespace nob {
	std::vector<hasher> model::banned_vehicles;

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	void _find_banned_vehicles(ntv::script_t *shop_ctrllr, size_t func_call_off) {
		for (size_t i = 14; i < 400; i++) {
			if (*(uint8_t *)shop_ctrllr->pos_addr(func_call_off + i) == 0x62) {
				size_t switch_off = func_call_off + i;
				auto cur_addr = (uint64_t)shop_ctrllr->pos_addr(switch_off + 2);
				size_t start_off = switch_off + 2;
				size_t cases = *(uint8_t *)(cur_addr - 1);
				for (size_t i = 0; i < cases; i++) {
					cur_addr += 6;
					start_off += 6;
					size_t jump_off = *(uint16_t *)(cur_addr - 2);
					int64_t case_off = (int64_t)shop_ctrllr->pos_addr(start_off + jump_off);
					uint8_t code = *(uint8_t *)case_off;

					hash_t hash;

					if (code == 0x28) { //push int
						hash = *(uint32_t *)(case_off + 1);
					} else if(code == 0x61) { //push int 24
						hash = *(uint32_t *)(case_off + 1) & 0xFFFFFF;
					} else {
						continue;
					}

					model::banned_vehicles.emplace_back(hash);
				}
				return;
			}
		}
	}

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	void vehicle::unlock_banned_vehicles() {
		if (model::banned_vehicles.size() || !ntv::script_list || !ntv::global_table) {
			return;
		}
		auto shop_ctrllr = ntv::script_list->find("shop_controller")->script;
		if (!shop_ctrllr || !shop_ctrllr->is_valid()) {
			return;
		}

		chan<uint32_t> id_ch;

		std::thread([shop_ctrllr, id_ch]() mutable {
			for (int i = 0; i < shop_ctrllr->page_count(); i++) {
				auto addr = hack::mem_match(
					(const uint8_t *)shop_ctrllr->page_addr(i), shop_ctrllr->page_size(i),
					{0x28, 0x26, 0xCE, 0x6B, 0x86, 0x39, 0x03}
				);
				if (!addr) {
					continue;
				}
				size_t real_code_off = addr - (uint64_t)shop_ctrllr->page_addr(i) + (i << 14);
				for (size_t j = 0; j < 2000; j++) {
					if (*(uint32_t *)shop_ctrllr->pos_addr(real_code_off - j) == 0x0008012D) {
						size_t func_off = *(uint32_t *)shop_ctrllr->pos_addr(real_code_off - j + 6) & 0xFFFFFF;
						for (size_t k = 0x5; k < 0x40; k++) {
							if ((*(uint32_t *)shop_ctrllr->pos_addr(func_off + k) & 0xFFFFFF) == 0x01002E) {
								for (k = k + 1; k < 30; k++) {
									if (*(uint8_t *)shop_ctrllr->pos_addr(func_off + k) == 0x5F) {
										_find_banned_vehicles(shop_ctrllr, real_code_off - j);
										id_ch << (*(uint32_t *)shop_ctrllr->pos_addr(func_off + k + 1) & 0xFFFFFF);
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
			id_ch << 0;
		}).detach();

		uint32_t id;

		id_ch >> id;

		if (id) {
			ntv::global_table[id] = 1;
		}
	}
} /* nob */
