#include <nob.hpp>
#include <nob/hack.hpp>

namespace nob {
	std::vector<std::string> model::banned_vehicles;

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	void _find_banned_vehicles(ntv::script_list_t::info_t::code_t *sc_ci, int scriptSwitchOffset) {
		int64_t curAddress = (int64_t)sc_ci->pos_addr(scriptSwitchOffset + 2);
		int startOff = scriptSwitchOffset + 2;
		int cases = *(unsigned char*)(curAddress - 1);
		for (int i = 0; i < cases;i++) {
			curAddress += 6;
			startOff += 6;
			int jumpoff = *(short*)(curAddress - 2);
			int64_t caseOff = (int64_t)sc_ci->pos_addr(startOff + jumpoff);
			unsigned char opCode = *(unsigned char*)caseOff;
			int hash;

			if (opCode == 0x28) { //push int
				hash = *(int*)(caseOff + 1);
			} else if(opCode == 0x61) { //push int 24
				hash = *(int*)(caseOff + 1) & 0xFFFFFF;
			} else {
				continue;
			}
			model::banned_vehicles.push_back(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash));
		}
	}

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	void vehicle::unlock_banned_vehicles() {
		if (!ntv::script_list || !ntv::global_table) {
			return;
		}
		auto sc_ci = ntv::script_list->find("shop_controller")->code;
		if (!sc_ci || !sc_ci->is_valid()) {
			return;
		}
		int id = call_onmt([sc_ci]()->uintptr_t {
			for (int i = 0; i < sc_ci->page_count(); i++) {
				auto addr = hack::mem_match(
					(const uint8_t *)sc_ci->page_addr(i), sc_ci->page_size(i),
					{0x28, 0x26, 0xCE, 0x6B, 0x86, 0x39, 0x03}
				);
				if (!addr) {
					continue;
				}
				int real_code_off = (int)(addr - (int64_t)sc_ci->page_addr(i) + (i << 14));
				for (int j = 0; j < 2000; j++) {
					if (*(int*)sc_ci->pos_addr(real_code_off - j) == 0x0008012D) {
						int func_off = *(int *)sc_ci->pos_addr(real_code_off - j + 6) & 0xFFFFFF;
						for (int k = 0x5; k < 0x40; k++) {
							if ((*(int*)sc_ci->pos_addr(func_off + k) & 0xFFFFFF) == 0x01002E) {
								for (k = k + 1; k < 30; k++) {
									if (*(unsigned char*)sc_ci->pos_addr(func_off + k) == 0x5F) {

										auto func_call_offset = real_code_off - j;
										for (int i = 14; i < 400; i++) {
											if (*(unsigned char*)sc_ci->pos_addr( + i) == 0x62) {
												_find_banned_vehicles(sc_ci, func_call_offset + i);
												break;
											}
										}

										return *(int*)sc_ci->pos_addr(func_off + k + 1) & 0xFFFFFF;
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
			return 0;
		});
		if (id) {
			ntv::global_table[id] = 1;
		}
	}
} /* nob */
