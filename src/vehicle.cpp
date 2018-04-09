#include <nob/entity.hpp>
#include <nob/hash.hpp>
#include <nob/script.hpp>
#include <nob/log.hpp>

#include <rua/mem.hpp>

#include <thread>
#include <queue>

namespace nob {
	const std::array<hasher, 304> base_vehicles {{
		// These data from ScriptHookV/NativeTrainer
		"NINEF", "NINEF2", "BLISTA", "ASEA", "ASEA2", "BOATTRAILER", "BUS", "ARMYTANKER", "ARMYTRAILER", "ARMYTRAILER2",
		"SUNTRAP", "COACH", "AIRBUS", "ASTEROPE", "AIRTUG", "AMBULANCE", "BARRACKS", "BARRACKS2", "BALLER", "BALLER2",
		"BJXL", "BANSHEE", "BENSON", "BFINJECTION", "BIFF", "BLAZER", "BLAZER2", "BLAZER3", "BISON", "BISON2",
		"BISON3", "BOXVILLE", "BOXVILLE2", "BOXVILLE3", "BOBCATXL", "BODHI2", "BUCCANEER", "BUFFALO", "BUFFALO2", "BULLDOZER",
		"BULLET", "BLIMP", "BURRITO", "BURRITO2", "BURRITO3", "BURRITO4", "BURRITO5", "CAVALCADE", "CAVALCADE2", "POLICET",
		"GBURRITO", "CABLECAR", "CADDY", "CADDY2", "CAMPER", "CARBONIZZARE", "CHEETAH", "COMET2", "COGCABRIO", "COQUETTE",
		"CUTTER", "GRESLEY", "DILETTANTE", "DILETTANTE2", "DUNE", "DUNE2", "HOTKNIFE", "DLOADER", "DUBSTA", "DUBSTA2",
		"DUMP", "RUBBLE", "DOCKTUG", "DOMINATOR", "EMPEROR", "EMPEROR2", "EMPEROR3", "ENTITYXF", "EXEMPLAR", "ELEGY2",
		"F620", "FBI", "FBI2", "FELON", "FELON2", "FELTZER2", "FIRETRUK", "FLATBED", "FORKLIFT", "FQ2",
		"FUSILADE", "FUGITIVE", "FUTO", "GRANGER", "GAUNTLET", "HABANERO", "HAULER", "HANDLER", "INFERNUS", "INGOT",
		"INTRUDER", "ISSI2", "JACKAL", "JOURNEY", "JB700", "KHAMELION", "LANDSTALKER", "LGUARD", "MANANA", "MESA",
		"MESA2", "MESA3", "CRUSADER", "MINIVAN", "MIXER", "MIXER2", "MONROE", "MOWER", "MULE", "MULE2",
		"ORACLE", "ORACLE2", "PACKER", "PATRIOT", "PBUS", "PENUMBRA", "PEYOTE", "PHANTOM", "PHOENIX", "PICADOR",
		"POUNDER", "POLICE", "POLICE4", "POLICE2", "POLICE3", "POLICEOLD1", "POLICEOLD2", "PONY", "PONY2", "PRAIRIE",
		"PRANGER", "PREMIER", "PRIMO", "PROPTRAILER", "RANCHERXL", "RANCHERXL2", "RAPIDGT", "RAPIDGT2", "RADI", "RATLOADER",
		"REBEL", "REGINA", "REBEL2", "RENTALBUS", "RUMPO", "RUMPO2", "RHINO", "RIOT", "RIPLEY", "ROCOTO",
		"ROMERO", "SABREGT", "SADLER", "SADLER2", "SANDKING", "SANDKING2", "SCHAFTER2", "SCHWARZER", "SCRAP", "SEMINOLE",
		"SENTINEL", "SENTINEL2", "ZION", "ZION2", "SERRANO", "SHERIFF", "SHERIFF2", "SPEEDO", "SPEEDO2", "STANIER",
		"STINGER", "STINGERGT", "STOCKADE", "STOCKADE3", "STRATUM", "SULTAN", "SUPERD", "SURANO", "SURFER", "SURFER2",
		"SURGE", "TACO", "TAILGATER", "TAXI", "TRASH", "TRACTOR", "TRACTOR2", "TRACTOR3", "GRAINTRAILER", "BALETRAILER",
		"TIPTRUCK", "TIPTRUCK2", "TORNADO", "TORNADO2", "TORNADO3", "TORNADO4", "TOURBUS", "TOWTRUCK", "TOWTRUCK2", "UTILLITRUCK",
		"UTILLITRUCK2", "UTILLITRUCK3", "WASHINGTON", "STRETCH", "YOUGA", "ZTYPE", "SANCHEZ", "SANCHEZ2", "SCORCHER", "TRIBIKE",
		"TRIBIKE2", "TRIBIKE3", "FIXTER", "CRUISER", "BMX", "POLICEB", "AKUMA", "CARBONRS", "BAGGER", "BATI",
		"BATI2", "RUFFIAN", "DAEMON", "DOUBLE", "PCJ", "VADER", "VIGERO", "FAGGIO2", "HEXER", "ANNIHILATOR",
		"BUZZARD", "BUZZARD2", "CARGOBOB2", "CARGOBOB3", "SKYLIFT", "POLMAV", "MAVERICK", "NEMESIS", "FROGGER", "FROGGER2",
		"CUBAN800", "DUSTER", "STUNT", "MAMMATUS", "JET", "SHAMAL", "LUXOR", "TITAN", "LAZER", "CARGOPLANE",
		"SQUALO", "MARQUIS", "DINGHY2", "JETMAX", "PREDATOR", "SEASHARK2", "SUBMERSIBLE", "TRAILERS", "TRAILERS2", "TRAILERS3",
		"TVTRAILER", "RAKETRAILER", "TANKER", "TRAILERLOGS", "TR2", "TR3", "TR4", "TRFLAT", "TRAILERSMALL", "VELUM",
		"ADDER", "VOLTIC", "VACCA", "FUROREGT", "BTYPE", "DOMINATOR2", "SUBMERSIBLE2", "RATLOADER2", "BUCCANEER2", "VOODOO",
		"CARGOBOB4", "COGNOSCENTI", "COGNOSCENTI2", "DINGHY4", "NIGHTSHADE", "SEASHARK3", "SPEEDER2", "SUPERVOLITO", "SUPERVOLITO2", "TORO2",
		"TROPIC2", "VALKYRIE2", "VERLIERER2", "BTYPE3"
	}};

	std::vector<hasher> _ban_vehs;

	static ntv::script_list_t::script_t *_shop_ctrllr = nullptr;

	size_t _ban_vehs_g, _ban_vehs_li_find_base;
	bool _finded_ban_vehs = false, _finding_ban_vehs = false;

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	bool _find_ban_vehs() {
		if (_finded_ban_vehs) {
			return true;
		}

		if (_finding_ban_vehs) {
			do {
				yield();
			} while (_finding_ban_vehs);
			return _finded_ban_vehs;
		}

		_finding_ban_vehs = true;

		while (!ntv::SCRIPT::HAS_SCRIPT_LOADED("shop_controller")) {
			yield();
		}

		if (!_shop_ctrllr) {
			_shop_ctrllr = ntv::script_list->find("shop_controller");
			if (!_shop_ctrllr) {
				return false;
			}
		}

		chan<size_t> ch;

		std::thread([ch]() mutable {
			auto &sc_inf = *_shop_ctrllr->info;
			for (size_t i = 0; i < sc_inf.code_page_count(); ++i) {
				auto mr = rua::mem::data(
					rua::any_ptr(sc_inf.code_pages[i]),
					sc_inf.code_page_size(i)
				).match({0x28, 0x26, 0xCE, 0x6B, 0x86, 0x39, 0x03});
				if (!mr) {
					continue;
				}
				size_t code_off = sc_inf.code_off(i, sc_inf.code_pages[i] + mr.pos);
				for (size_t j = 0; j < 2000; j++) {
					if (*(uint32_t *)sc_inf.code_addr(code_off - j) == 0x0008012D) {
						size_t func_off = *(uint32_t *)sc_inf.code_addr(code_off - j + 6) & 0xFFFFFF;
						for (size_t k = 0x5; k < 0x40; k++) {
							if ((*(uint32_t *)sc_inf.code_addr(func_off + k) & 0xFFFFFF) == 0x01002E) {
								for (k = k + 1; k < 30; k++) {
									if (*(uint8_t *)sc_inf.code_addr(func_off + k) == 0x5F) {
										ch
											<< (*(uint32_t *)sc_inf.code_addr(func_off + k + 1) & 0xFFFFFF)
											<< code_off - j
											<< true
										;
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
			ch << SIZE_MAX << SIZE_MAX << false;
		}).detach();

		ch >> _ban_vehs_g >> _ban_vehs_li_find_base >> _finded_ban_vehs;

		_finding_ban_vehs = false;

		return _finded_ban_vehs;
	}

	void unlock_banned_vehicles() {
		if (_find_ban_vehs()) {
			ntv::global_table[_ban_vehs_g] = 1;
		}
	}

	// Reference from https://github.com/zorg93/EnableMpCars-GTAV
	const std::vector<hasher> &banned_vehicles() {
		if (_ban_vehs.size() || !_find_ban_vehs()) {
			return _ban_vehs;
		}

		while (!ntv::SCRIPT::HAS_SCRIPT_LOADED("shop_controller")) {
			yield();
		}

		chan<std::vector<hasher>> vehs_ch;

		std::thread([vehs_ch]() mutable {
			auto &sc_inf = *_shop_ctrllr->info;
			std::vector<hasher> vehs;
			for (size_t i = 14; i < 400; i++) {
				if (*(uint8_t *)sc_inf.code_addr(_ban_vehs_li_find_base + i) == 0x62) {
					size_t switch_off = _ban_vehs_li_find_base + i;
					auto cur_addr = (uint64_t)sc_inf.code_addr(switch_off + 2);
					size_t start_off = switch_off + 2;
					size_t cases = *(uint8_t *)(cur_addr - 1);
					for (size_t i = 0; i < cases; i++) {
						cur_addr += 6;
						start_off += 6;
						size_t jump_off = *(uint16_t *)(cur_addr - 2);
						int64_t case_off = (int64_t)sc_inf.code_addr(start_off + jump_off);
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

	std::vector<hasher> _dlc_vehs;

	const std::vector<hasher> &dlc_vehicles() {
		if (_dlc_vehs.size()) {
			return _dlc_vehs;
		}
		for (int i = 0; i < ntv::DLC1::GET_NUM_DLC_VEHICLES(); ++i) {
			_dlc_vehs.emplace_back(ntv::DLC1::GET_DLC_VEHICLE_MODEL(i));
		}
		return _dlc_vehs;
	}
} /* nob */
