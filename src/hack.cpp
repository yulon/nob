#include <nob.hpp>

#include <windows.h>
#include <psapi.h>

#include <vector>
#include <thread>
#include <cstring>
#include <iostream>

namespace nob {
	namespace hack {
		uintptr_t mem_match(const uint8_t *mem_addr, size_t mem_len, const std::vector<uint16_t> &ptr) {
			for (size_t i = 0; i < mem_len; i++) {
				size_t j;
				for (j = 0; i + j < mem_len && j < ptr.size(); j++) {
					if (ptr[j] < 256 && ptr[j] != mem_addr[i + j]) {
						break;
					}
				}
				if (j == ptr.size()) {
					return (uintptr_t)mem_addr + (uintptr_t)i;
				}
			}
			return 0;
		}

		inline uintptr_t mem_match(const std::vector<uint16_t> &ptr) {
			MODULEINFO mi;
			GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &mi, sizeof(MODULEINFO));
			return mem_match((const uint8_t *)mi.lpBaseOfDll, mi.SizeOfImage, ptr);
		}

		template <typename T>
		T *find_const_ptr(const std::vector<uint16_t> &logged_ptr_code) {
			auto addr = mem_match(logged_ptr_code);
			if (!addr) {
				return 0;
			}
			return reinterpret_cast<T *>(addr + *(int *)(addr + 3) + 7);
		}

		/*
		class globals_t {
			public:
				uint64_t *base_addr;

				uint64_t &get(int id) {
					return base_addr[id >> 18 & 0x3F][id & 0x3FFFF];
				}
		}

		auto globals = find_const_ptr<globals_t>({
			0x4C, 0x8D, 0x05, 1111, 1111, 1111, 1111, 0x4D, 0x8B, 0x08,
			0x4D, 0x85, 0xC9, 0x74, 0x11
		});
		*/

		struct script_infos_t {
			struct info_t {
				struct code_t {
					char padding1[16];					//0x0
					unsigned char **blocks_offset;		//0x10
					char padding2[4];					//0x18
					int length;							//0x1C
					char padding3[4];					//0x20
					int local_count;					//0x24
					char padding4[4];					//0x28
					int native_count;					//0x2C
					int64_t *local_offset;				//0x30
					char padding5[8];					//0x38
					int64_t *native_offset;				//0x40
					char padding6[16];					//0x48
					int nameHash;						//0x58
					char padding7[4];					//0x5C
					char *name;							//0x60
					char **strings_offset;				//0x68
					int string_size;					//0x70
					char padding8[12];					//0x74

					bool is_valid() const {
						return length;
					}

					int page_count() const {
						return (length + 0x3FFF) >> 14;
					}

					int page_size(int page) const {
						return (page < 0 || page >= page_count() ? 0 : (page == page_count() - 1) ? length & 0x3FFF : 0x4000);
					}

					unsigned char* page_addr(int page) const {
						return blocks_offset[page];
					}

					unsigned char* pos_addr(int pos) const {
						return pos < 0 || pos >= length ? NULL : &blocks_offset[pos >> 14][pos & 0x3FFF];
					}

					char* get_string(int str_pos) const {
						return str_pos < 0 || str_pos >= string_size ? NULL : &strings_offset[str_pos >> 14][str_pos & 0x3FFF];
					}
				};

				code_t *code;
				char padding[4];
				int hash;
			};

			info_t *infos;
			char padding[16];
			int size;

			info_t *find(const char *name) const {
				int hash = ntv::GAMEPLAY::GET_HASH_KEY(name);
				for (int i = 0; i < size; i++) {
					if (infos[i].hash == hash) {
						return &infos[i];
					}
				}
				return nullptr;
			}
		};

		auto script_infos = find_const_ptr<script_infos_t>({
			0x48, 0x03, 0x15, 1111, 1111, 1111, 1111, 0x4C, 0x23, 0xC2,
			0x49, 0x8B, 0x08
		});
	} /* hack */

	std::vector<std::string> model::banned_vehicles;

	void _find_banned_vehicles(hack::script_infos_t::info_t::code_t *sc_ci, int scriptSwitchOffset) {
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
		if (!hack::script_infos) {
			return;
		}
		auto sc_ci = hack::script_infos->find("shop_controller")->code;
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
						int func_off = *(int*)sc_ci->pos_addr(real_code_off - j + 6) & 0xFFFFFF;
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
			*shv::getGlobalPtr(id) = 1;
		}
	}

	namespace ui {
		uintptr_t _wheel_slowmo_fp = 0;
		// Reference from https://www.unknowncheats.me/forum/grand-theft-auto-v/181752-weapon-wheel-slowmotion.html
		void disable_wheel_slowmo() {
			if (!_wheel_slowmo_fp) {
				_wheel_slowmo_fp = call_onmt([]()->uintptr_t {
					return hack::mem_match({
						0x48, 0x89, 0x5C, 0x24, 0x08, 0x57, 0x48, 0x83, 0xEC, 0x20,
						0x33, 0xC0, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x83, 0xFA, 0x01,
						0x75, 1111, 0x38, 0x05, 1111, 1111, 1111, 1111, 0x0F, 0x45,
						0xF8
					});
				});
				if (_wheel_slowmo_fp) {
					memcpy((void *)_wheel_slowmo_fp, (const uint8_t[3]){
						0x31, 0xC0, //xor eax, eax
						0xC3 //ret
					}, 3);
				}
			}
		}
	} /* ui */
} /* nob */
