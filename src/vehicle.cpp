#include <nob/entity.hpp>
#include <nob/hash.hpp>
#include <nob/script.hpp>
#include <nob/log.hpp>

#include <rua/bin.hpp>

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
		static on_load reset([]() {
			_finded_ban_vehs = false;
		});

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

		chan<bool> ch;

		std::thread([ch]() mutable {
			auto &sc_inf = *_shop_ctrllr->info;
			for (size_t i = 0; i < sc_inf.code_page_count(); ++i) {
				auto mr = rua::bin_view(
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
										_ban_vehs_g = (*(uint32_t *)sc_inf.code_addr(func_off + k + 1) & 0xFFFFFF);
										_ban_vehs_li_find_base = code_off - j;
										ch << true;
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
			ch << false;
		}).detach();

		ch >> _finded_ban_vehs;

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

	namespace {
		const char *_com_dn_flyer(hash_t iParam0, bool bParam1)
		{
			switch (iParam0)
			{
				case 0x2C634FBD:
				case 0x742E9AC0:
					return "MAIBATSU";

				case 0x9D0450CA:
				case 0x1517D4D9:
				case 0x250B0C5E:
				case 0xB79C1BF5:
					if (bParam1)
					{
						return "BUCKING";
					}
					else
					{
						return "BUCKINGHAM";
					}
					break;

				case 0xFCFCB68B:
				case 0x31F0B376:
				case 0xD9927FE3:
				case 0x39D6779E:
				case 0x81794C70:
					return "WESTERN";
					break;

				case 0x2F03547B:
				case 0x2C75F0DD:
					return "NAGASAKI";
					break;

				case 0x97E55D11:
				case 0x9C429B6A:
				case 0x403820E8:
				case 0xB39B0AE6:
					return "JOBUILT";
					break;
			}
			if (iParam0 == 0x4FF77E37)
			{
				if (bParam1)
				{
					return "BUCKING";
				}
				else
				{
					return "BUCKINGHAM";
				}
			}
			if (((((iParam0 == 0x09D80F93 || iParam0 == 0xEBC24DF2) || iParam0 == 0x4019CB4C) || iParam0 == 0xB79F589E) || iParam0 == 0x2A54C47D) || iParam0 == 0x9C5E5644)
			{
				if (bParam1)
				{
					return "BUCKING";
				}
				else
				{
					return "BUCKINGHAM";
				}
			}
			if (iParam0 == 0x6CBD1D6D)
			{
				return "WESTERN";
			}
			if (iParam0 == 0x39D6E83F || iParam0 == 0x58CDAF30)
			{
				return "MAMMOTH";
			}
			if (iParam0 == 0x920016F1 || iParam0 == 0xB2CF7250)
			{
				if (bParam1)
				{
					return "BUCKING";
				}
				else
				{
					return "BUCKINGHAM";
				}
			}
			return "";
		}

		const char *_com_dn_boat(hash_t iParam0, bool bParam1)
		{
			switch (iParam0)
			{
				case 0x17DF5EC2:
				case 0x1149422F:
					if (bParam1)
					{
						return "BUCKING";
					}
					else
					{
						return "BUCKINGHAM";
					}
					break;

				case 0x33581161:
				case 0xEF2295C9:
					return "OCELOT";
					break;

				case 0x3D961290:
					if (!bParam1)
					{
						return "OCELOT";
					}
					break;

				case 0xDB4388E4:
					if (bParam1)
					{
						return "SPEEDOPH";
					}
					else
					{
						return "SPEEDOPHILE";
					}
					break;

				case 0xED762D49:
					if (bParam1)
					{
						return "SPEEDOPH";
					}
					else
					{
						return "SPEEDOPHILE";
					}
					break;

				case 0xC2974024:
					if (bParam1)
					{
						return "SPEEDOPH";
					}
					else
					{
						return "SPEEDOPHILE";
					}
					break;

				case 0x3FD5AA2F:
					if (bParam1)
					{
						return "LAMPADA";
					}
					else
					{
						return "LAMPADATI";
					}
					break;
			}
			if (iParam0 == 0x0DC60D2B || iParam0 == 0x1A144F2A)
			{
				if (bParam1)
				{
					return "PEGASSI";
				}
				else
				{
					return "PEGASSI";
				}
			}
			return "";
		}

		const char *_com_dn(hash_t iParam0, bool bParam1)
		{
			if (ntv::VEHICLE::IS_THIS_MODEL_A_BOAT(iParam0))
			{
				return _com_dn_boat(iParam0, bParam1);
			}
			if (ntv::VEHICLE::IS_THIS_MODEL_A_PLANE(iParam0) || ntv::VEHICLE::IS_THIS_MODEL_A_HELI(iParam0))
			{
				return _com_dn_flyer(iParam0, bParam1);
			}
			switch (iParam0)
			{
				case 0x206D1B68:
					return "HIJAK";
					break;

				case 0xB9CB3B69:
					return "WEENY";
					break;

				case 0xDE3D9D22:
					return "ANNIS";
					break;

				case 0x2560B2FC:
					return "CHARIOT";
					break;

				case 0xCFCA3668:
				case 0x08852855:
				case 0x6FF0F727:
				case 0x25CBE2E2:
				case 0x1C09CF5E:
				case 0x27B4E6B0:
					if (bParam1)
					{
						return "GALLIVAN";
					}
					else
					{
						return "GALIVANTER";
					}
					break;

				case 0x29B0DA97:
				case 0xB1D80E06:
				case 0x9CF21E0F:
				case 0x432AA566:
					return "BF";
					break;

				case 0x8911B9F5:
				case 0x462FE277:
				case 0x16E478C1:
				case 0xD37B7976:
				case 0xB52B5113:
				case 0x4FB1A214:
				case 0xE882E5F6:
				case 0xA29D6D10:
					if (bParam1)
					{
						return "BENEFAC";
					}
					else
					{
						return "BENEFACTOR";
					}
					break;

				case 0x50732C82:
				case 0x3412AE2D:
				case 0xBD1B39C3:
				case 0xB8E2AE18:
				case 0x506434F6:
				case 0xE18195B2:
					if (bParam1)
					{
						return "UBERMACH";
					}
					else
					{
						return "UBERMACHT";
					}
					break;

				case 0x2D3BD401:
				case 0xB779A091:
					return "TRUFFADE";
					break;

				case 0x3EAB5555:
				case 0x8CB29A14:
				case 0x679450AF:
				case 0xFFB15B5E:
				case 0xF77ADE32:
				case 0xDA5819A3:
					if (bParam1)
					{
						return "DEWBAUCH";
					}
					else
					{
						return "DEWBAUCHEE";
					}
					break;

				case 0xC3DDFDCE:
				case 0x3D8FA25C:
				case 0xA8E38B01:
				case 0x7F5C91F1:
					return "OBEY";
					break;

				case 0x59E0FBF3:
				case 0x8F0E3594:
				case 0x71CB2FFB:
				case 0x49863E9C:
					return "CHEVAL";
					break;

				case 0x6A4BD8F6:
					if (bParam1)
					{
						return "JACKSHP";
					}
					else
					{
						return "JACKSHEEPE";
					}
					break;

				case 0x1BB290BC:
				case 0x5B42A5C4:
				case 0x690A4153:
				case 0xAFBB2CA4:
				case 0xC9E8FF76:
				case 0x8FB66F9B:
				case 0x1F3766E3:
				case 0x9B909C94:
				case 0x6210CBB0:
				case 0xCEC6B9B7:
				case 0x94204D89:
				case 0x9441D8D5:
				case 0x9628879C:
				case 0x2C33B46E:
				case 0x9BAA707C:
				case 0x72935408:
				case 0x97FA4F36:
				case 0x11AA0E14:
				case 0x72A4C31E:
					return "DECLASSE";
					break;

				case 0xD756460C:
				case 0x779F23AA:
				case 0xD0EB2BE5:
				case 0xD7278283:
				case 0x8FC3AADC:
				case 0x81634188:
				case 0xBB6B404F:
				case 0x69F06B57:
				case 0xE2504942:
					return "ALBANY";
					break;

				case 0xC1E908D2:
				case 0xFEFD644F:
				case 0xA3FC0F4D:
				case 0x03E5F6B8:
				case 0x94B395C5:
				case 0xEDD516C6:
				case 0x2BEC3CBE:
				case 0xD83C13CE:
				case 0x698521E3:
				case 0xDCE1D9F7:
				case 0x4543B74D:
				case 0x25C5AF13:
					return "BRAVADO";
					break;

				case 0x5C23AF9B:
				case 0x82E499FA:
				case 0xB1D95DA0:
				case 0x7B8AB45F:
					if (bParam1)
					{
						return "GROTTI";
					}
					else
					{
						return "Grotti_2";
					}
					break;

				case 0x067BC037:
				case 0x2EC385FE:
					if (bParam1)
					{
						return "INVERTO";
					}
					else
					{
						return "Invetero";
					}
					break;

				case 0x9D96B45B:
				case 0xDC434E51:
				case 0x04CE68AC:
				case 0xB9210FD0:
				case 0x3AF8C345:
				case 0x79FBB0C5:
				case 0x71FA16EA:
				case 0x1B38E955:
				case 0x7A61B330:
				case 0x9AE6DDA1:
				case 0xED7EADA4:
				case 0xCFB3870C:
				case 0x2B6DC64A:
				case 0x6D19CCBC:
				case 0xB12314E0:
				case 0xE5A2D6C6:
				case 0x3FC5D440:
				case 0xA7EDE74D:
				case 0x0239E390:
				case 0x2B7F9DE3:
				case 0x825A9F4C:
				case 0x14D69010:
					return "VAPID";
					break;

				case 0x02E19879:
				case 0x744CA80D:
				case 0x1ED0A534:
				case 0x34E6BF6B:
				case 0x7F2153DF:
				case 0x6FD95F68:
				case 0xB822A1AA:
				case 0x73B1C3CB:
				case 0x45D56ADA:
				case 0x6827CF72:
				case 0x898ECCEA:
				case 0xF8DE29A8:
					return "BRUTE";
					break;

				case 0xA988D3A2:
					return "BOLLOKAN";
					break;

				case 0xDAC67112:
				case 0xDCBCBE48:
					return "OCELOT";
					break;

				case 0x36848602:
				case 0x84F42E51:
				case 0xAA699BB6:
				case 0x48CECED3:
				case 0x132D5A1A:
					return "CANIS";
					break;

				case 0xB2FE5CF9:
					return "OVERFLOD";
					break;

				case 0xE62B361B:
				case 0x18F25AC7:
				case 0xF9300CC5:
				case 0xCADD5D2D:
				case 0x142E0DC3:
				case 0xCABD11E8:
				case 0x0350D1AB:
				case 0x767164D6:
					return "PEGASSI";
					break;

				case 0x831A21D5:
				case 0xF26CEFF9:
				case 0x2B26F456:
				case 0xEC8F7094:
					return "IMPONTE";
					break;

				case 0x32B29A4B:
				case 0xB802DD46:
				case 0x8612B64B:
				case 0x8E9254FB:
				case 0x34DD8AA1:
				case 0x7836CE2F:
				case 0x39DA2754:
				case 0xBC993509:
				case 0x64430650:
				case 0xAE2BFE94:
				case 0x187D938D:
				case 0xEE6024BC:
					return "KARIN";
					break;

				case 0xE9805550:
				case 0x2EF89E46:
				case 0xA960B13E:
				case 0x35ED670B:
					return "MAIBATSU";
					break;

				case 0xEB70965F:
				case 0x3DEE5EDA:
				case 0xDCBC1C3B:
				case 0x9C669788:
				case 0xB2A716A3:
				case 0xBE0E6126:
				case 0x6882FA73:
				case 0xAF599F01:
				case 0x63ABADE7:
					return "DINKA";
					break;

				case 0xBC32A33B:
					return "FATHOM";
					break;

				case 0x9F4B77BE:
				case 0xA7CE1BC5:
					return "COIL";
					break;
			}
			switch (iParam0)
			{
				case 0xE8A8BDA8:
				case 0xFAAD85EE:
				case 0x3822BDFE:
					if (bParam1)
					{
						return "LAMPADA";
					}
					else
					{
						return "LAMPADATI";
					}
					break;

				case 0xC1AE4D16:
					return "PFISTER";
					break;

				case 0x1DC0BA53:
					return "SCHYSTER";
					break;

				case 0x8B13F083:
				case 0xFF22D208:
				case 0x4BA4E8DC:
					if (bParam1)
					{
						return "DUNDREAR";
					}
					else
					{
						return "DUNDREARY";
					}
					break;

				case 0x1A7FCEFA:
				case 0x7074F39D:
				case 0xCB44B1CA:
				case 0xC3FBA120:
				case 0xD138A6BB:
				case 0x1C534995:
				case 0xCEEA3F4B:
				case 0x4008EABB:
				case 0x32B91AE8:
				case 0x58E49664:
				case 0xCD935EF9:
				case 0x5D0AAC8F:
				case 0x810369E2:
				case 0x7B7E56F0:
				case 0x9114EADA:
					return "HVY";
					break;

				case 0x21EEE87D:
				case 0x50B0215A:
				case 0xC7824E5E:
				case 0x7DE35E7D:
				case 0x73920F8E:
					return "MTL";
					break;

				case 0x61D6BA8C:
				case 0x843B73DE:
					return "STANLEY";
					break;

				case 0x5A82F9AE:
				case 0x809AA4CB:
				case 0x72435A19:
					return "JOBUILT";
					break;

				case 0xCFCFEB3B:
					return "MAMMOTH";
					break;

				case 0xF8D48E7A:
				case 0x66B4FC45:
					if (bParam1)
					{
						return "ZIRCONIU";
					}
					else
					{
						return "ZIRCONIUM";
					}
					break;

				case 0xF79A00F7:
				case 0xC9CEAF06:
					return "SHITZU";
					break;

				case 0x806B9CC3:
				case 0x77934CEE:
				case 0x2C509634:
					if (bParam1)
					{
						return "WESTERN";
					}
					else
					{
						return "WESTERNMOTORCYCLE";
					}
					break;

				case 0x8125BCF9:
				case 0x44623884:
				case 0x00ABB0C0:
				case 0xB44F0582:
				case 0xFD231729:
					return "NAGASAKI";
					break;

				case 0xDA288376:
				case 0x26321E67:
					if (bParam1)
					{
						return "PRINCIPL";
					}
					else
					{
						return "PRINCIPE";
					}
					break;

				case 0x11F76C14:
					return "LCC";
					break;

				case 0x43779C54:
				case 0x1ABA13B5:
				case 0xF4E1AA15:
					if (!bParam1)
					{
						return "Ped";
					}
					break;

				case 0x4339CD69:
				case 0xB67597EC:
				case 0xE823FB48:
					if (!bParam1)
					{
						return "TriCycles";
					}
					break;

				case 0x13B57D8A:
				case 0x42F2ED16:
				case 0x5E4327C8:
					return "ENUS";
					break;

				case 0x34B7390F:
					if (bParam1)
					{
						return "EMPEROR";
					}
					else
					{
						return "EMPORER";
					}
					break;

				case 0xB3206692:
					return "VULCAR";
					break;

				case 0x6322B39A:
					return "PROGEN";
					break;
			}
			if (iParam0 == 0xEB298297)
			{
				return "BF";
			}
			else if (iParam0 == 0x05852838)
			{
				return "CANIS";
			}
			else if (iParam0 == 0x58B3979C)
			{
				return "BRAVADO";
			}
			if (iParam0 == 0x06FF6914)
			{
				return "ALBANY";
			}
			if (iParam0 == 0xAC5DF515)
			{
				return "PEGASSI";
			}
			else if (iParam0 == 0xB2A716A3)
			{
				return "DINKA";
			}
			else if (iParam0 == 0xF77ADE32)
			{
				if (bParam1)
				{
					return "DEWBAUCH";
				}
				else
				{
					return "DEWBAUCHEE";
				}
			}
			else if (iParam0 == 0x185484E1)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			else if (iParam0 == 0x1D06D681)
			{
				return "ENUS";
			}
			else if (iParam0 == 0x2DB8D1AA)
			{
				return "ALBANY";
			}
			else if (iParam0 == 0x6D6F8F43)
			{
				return "DINKA";
			}
			else if (iParam0 == 0x2C509634)
			{
				return "DINKA";
			}
			if (iParam0 == 0x6D6F8F43)
			{
				return "DINKA";
			}
			if (iParam0 == 0xB820ED5E || iParam0 == 0xCD93A7DB)
			{
				return "VAPID";
			}
			if (iParam0 == 0x51D83328)
			{
				return "VULCAR";
			}
			if ((iParam0 == 0x047A6BC1 || iParam0 == 0xE644E480) || iParam0 == 0xB6410173)
			{
				if (bParam1)
				{
					return "BENEFAC";
				}
				else
				{
					return "BENEFACTOR";
				}
			}
			if (iParam0 == 0x322CF98F)
			{
				return "DECLASSE";
			}
			if (iParam0 == 0x404B6381)
			{
				if (bParam1)
				{
					return "LAMPADA";
				}
				else
				{
					return "LAMPADATI";
				}
			}
			if (iParam0 == 0x3C4E2113)
			{
				if (bParam1)
				{
					return "INVERTO";
				}
				else
				{
					return "Invetero";
				}
			}
			if (iParam0 == 0xF683EACA)
			{
				return "LCC";
			}
			if (iParam0 == 0x4B6C568A)
			{
				return "SHITZU";
			}
			if (iParam0 == 0xBF1691E0)
			{
				if (bParam1)
				{
					return "LAMPADA";
				}
				else
				{
					return "LAMPADATI";
				}
			}
			if (iParam0 == 0xDCE1D9F7)
			{
				return "BRAVADO";
			}
			else if (iParam0 == 0x2B7F9DE3)
			{
				return "VAPID";
			}
			else if (iParam0 == 0xBE0E6126)
			{
				return "DINKA";
			}
			else if (iParam0 == 0xDA5819A3)
			{
				if (bParam1)
				{
					return "DEWBAUCH";
				}
				else
				{
					return "DEWBAUCHEE";
				}
			}
			if (iParam0 == 0x5E4327C8)
			{
				return "ENUS";
			}
			else if (iParam0 == 0x14D69010 || iParam0 == 0xAED64A63)
			{
				return "VAPID";
			}
			else if (iParam0 == 0xAF599F01)
			{
				return "DINKA";
			}
			else if (iParam0 == 0xE2504942)
			{
				return "ALBANY";
			}
			else if (iParam0 == 0x4019CB4C || iParam0 == 0xB79F589E)
			{
				return "BUCKING";
			}
			else if (iParam0 == 0xA29D6D10)
			{
				if (bParam1)
				{
					return "BENEFAC";
				}
				else
				{
					return "BENEFACTOR";
				}
			}
			else if (iParam0 == 0x6322B39A)
			{
				return "PROGEN";
			}
			else if (iParam0 == 0x767164D6)
			{
				return "PEGASSI";
			}
			else if (iParam0 == 0x2EC385FE)
			{
				if (bParam1)
				{
					return "INVERTO";
				}
				else
				{
					return "Invetero";
				}
			}
			else if (iParam0 == 0x3FD5AA2F)
			{
				if (bParam1)
				{
					return "LAMPADA";
				}
				else
				{
					return "LAMPADATI";
				}
			}
			else if (iParam0 == 0xA7CE1BC5)
			{
				return "COIL";
			}
			if (iParam0 == 0x86618EDA || iParam0 == 0xC397F748)
			{
				return "ALBANY";
			}
			else if (iParam0 == 0x81A9CDDF || iParam0 == 0x95466BDB)
			{
				return "WILLARD";
			}
			else if ((iParam0 == 0x710A2B9B || iParam0 == 0x779B4F2D) || iParam0 == 0x1F52A43F)
			{
				return "DECLASSE";
			}
			else if (iParam0 == 0xAED64A63 || iParam0 == 0xEC8F7094)
			{
				return "VAPID";
			}
			if (iParam0 == 0x866BCE26)
			{
				return "WILLARD";
			}
			if ((iParam0 == 0x0D4EA603 || iParam0 == 0x94DA98EF) || iParam0 == 0xE2504942)
			{
				return "DECLASSE";
			}
			if (iParam0 == 0xCA62927A || iParam0 == 0x00FDFFB0)
			{
				if (bParam1)
				{
					return "DUNDREAR";
				}
				else
				{
					return "DUNDREARY";
				}
			}
			if (iParam0 == 0x42BC5E19 || iParam0 == 0xBCDE91F0)
			{
				return "VAPID";
			}
			if (iParam0 == 0x7B47A6A7 || iParam0 == 0xCE6B35A4)
			{
				return "ALBANY";
			}
			if (iParam0 == 0x9CFFFC56 || iParam0 == 0x39F9C898)
			{
				return "DECLASSE";
			}
			if (((iParam0 == 0x86FE0B60 || iParam0 == 0x360A438E) || iParam0 == 0x29FCD3E4) || iParam0 == 0xDBF2D57A)
			{
				return "ENUS";
			}
			if (iParam0 == 0x41B77FA4)
			{
				return "BRAVADO";
			}
			if (((iParam0 == 0x58CF185C || iParam0 == 0xA774B5A6) || iParam0 == 0xCB0E7CD9) || iParam0 == 0x72934BE4)
			{
				if (bParam1)
				{
					return "BENEFAC";
				}
				else
				{
					return "BENEFACTOR";
				}
			}
			if (((iParam0 == 0x6FF0F727 || iParam0 == 0x25CBE2E2) || iParam0 == 0x1C09CF5E) || iParam0 == 0x27B4E6B0)
			{
				if (bParam1)
				{
					return "GALLIVAN";
				}
				else
				{
					return "GALIVANTER";
				}
			}
			if (iParam0 == 0x8C2BD0DC)
			{
				return "IMPONTE";
			}
			if (iParam0 == 0xDC19D101)
			{
				return "ALBANY";
			}
			if (iParam0 == 0x92EF6E04)
			{
				return "PFISTER";
			}
			if (iParam0 == 0x97398A4B)
			{
				if (bParam1)
				{
					return "DEWBAUCH";
				}
				else
				{
					return "DEWBAUCHEE";
				}
			}
			if (iParam0 == 0x57F682AF)
			{
				return "BRAVADO";
			}
			if (iParam0 == 0x4BFCF28B)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			if (iParam0 == 0x7E8F677F)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			if (iParam0 == 0x47BBCF2E || iParam0 == 0xE6401328)
			{
				if (bParam1)
				{
					return "BENEFAC";
				}
				else
				{
					return "BENEFACTOR";
				}
			}
			if (iParam0 == 0x5502626C)
			{
				return "VAPID";
			}
			if (iParam0 == 0x8CF5CAE1)
			{
				return "ENUS";
			}
			if (iParam0 == 0x0DF381E5)
			{
				return "PEGASSI";
			}
			if (((iParam0 == 0x28B67ACA || iParam0 == 0x0612F4B6) || iParam0 == 0xD876DBE2) || iParam0 == 0xC96B73D9)
			{
				return "VAPID";
			}
			if (iParam0 == 0x05283265)
			{
				return "NAGASAKI";
			}
			if (iParam0 == 0x17420102 || iParam0 == 0x2C2C2324)
			{
				if (bParam1)
				{
					return "WESTERN";
				}
				else
				{
					return "WESTERNMOTORCYCLE";
				}
			}
			if (iParam0 == 0x0E2C013E || iParam0 == 0x14D22159)
			{
				return "BRAVADO";
			}
			if (iParam0 == 0xD1AD4937)
			{
				return "OBEY";
			}
			if (iParam0 == 0xB6846A55)
			{
				return "ANNIS";
			}
			if (iParam0 == 0x707E63A4)
			{
				if (bParam1)
				{
					return "LAMPADA";
				}
				else
				{
					return "LAMPADATI";
				}
			}
			if (iParam0 == 0xC0240885 || iParam0 == 0xE80F67EE)
			{
				return "DECLASSE";
			}
			if (iParam0 == 0x5C55CB39)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			if (iParam0 == 0x7B406EFB)
			{
				return "PROGEN";
			}
			if (iParam0 == 0x1CBDC10B)
			{
				return "OCELOT";
			}
			if (iParam0 == 0x30D3F6D8)
			{
				if (bParam1)
				{
					return "EMPEROR";
				}
				else
				{
					return "EMPORER";
				}
			}
			if (iParam0 == 0x829A3C44)
			{
				return "MTL";
			}
			if (iParam0 == 0xA31CB573)
			{
				return "DECLASSE";
			}
			if (iParam0 == 0x81E38F7F || iParam0 == 0x58E316C7)
			{
				return "LCC";
			}
			if ((iParam0 == 0x00675ED7 || iParam0 == 0xE7D2A16E) || iParam0 == 0xE5BA6858)
			{
				return "NAGASAKI";
			}
			if (iParam0 == 0x30FF0190 || iParam0 == 0xF0C2A91F)
			{
				return "SHITZU";
			}
			if (((((iParam0 == 0xA0438767 || iParam0 == 0xC3D7C72B) || iParam0 == 0xDE05FB87) || iParam0 == 0xAC4E93C9) || iParam0 == 0x6FACDF31) || iParam0 == 0xDB20A373)
			{
				if (bParam1)
				{
					return "WESTERN";
				}
				else
				{
					return "WESTERNMOTORCYCLE";
				}
			}
			if (iParam0 == 0x3D29CD2B)
			{
				return "BRAVADO";
			}
			if (((iParam0 == 0x794CB30C || iParam0 == 0xDBA9DBFC) || iParam0 == 0xB328B188) || iParam0 == 0x9229E4EB)
			{
				return "PEGASSI";
			}
			if (iParam0 == 0xD7C56D39)
			{
				return "BF";
			}
			if (iParam0 == 0xA5325278)
			{
				return "MAIBATSU";
			}
			if (iParam0 == 0xA1355F67)
			{
				return "NAGASAKI";
			}
			if (iParam0 == 0x877358AD)
			{
				return "PFISTER";
			}
			if (iParam0 == 0xF1B44F44 || iParam0 == 0x6ABDF65E)
			{
				if (bParam1)
				{
					return "PRINCIPL";
				}
				else
				{
					return "PRINCIPE";
				}
			}
			if ((iParam0 == 0x25676EAF || iParam0 == 0xD2D5E00E) || iParam0 == 0x1044926F)
			{
				return "PEGASSI";
			}
			if (iParam0 == 0x3DA47243 || iParam0 == 0x4131F378)
			{
				return "TRUFFADE";
			}
			if (iParam0 == 0x9734F3EA)
			{
				return "OCELOT";
			}
			if (iParam0 == 0x381E10BD)
			{
				return "IMPONTE";
			}
			if (iParam0 == 0x4662BCBB)
			{
				return "KARIN";
			}
			if (iParam0 == 0x9DAE1398)
			{
				return "JOBUILT";
			}
			if (iParam0 == 0x3AF76F4A)
			{
				return "COIL";
			}
			if (iParam0 == 0x8E08EC82)
			{
				return "MTL";
			}
			if (iParam0 == 0x85E8E76B || iParam0 == 0xE33A477B)
			{
				return "PROGEN";
			}
			if (iParam0 == 0xED62BFA9 || iParam0 == 0xCEB28249)
			{
				return "BF";
			}
			if (iParam0 == 0x0BBA2261 || iParam0 == 0xDE3D9D22)
			{
				return "ANNIS";
			}
			if (iParam0 == 0x706E2B40 || iParam0 == 0x400F5147)
			{
				if (bParam1)
				{
					return "DEWBAUCH";
				}
				else
				{
					return "DEWBAUCHEE";
				}
			}
			if (iParam0 == 0x4992196C)
			{
				return "PROGEN";
			}
			if (iParam0 == 0xAC33179C)
			{
				return "PEGASSI";
			}
			if (iParam0 == 0x2AE524A8)
			{
				return "HIJAK";
			}
			if (iParam0 == 0xC575DF11)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			if (iParam0 == 0xEC8F7094)
			{
				return "IMPONTE";
			}
			if (iParam0 == 0x097E5533 || iParam0 == 0x36B4A8A9)
			{
				return "OCELOT";
			}
			if (iParam0 == 0x0D4E5F4D)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			if ((iParam0 == 0x8D4B7A8A || iParam0 == 0x19DD9ED1) || iParam0 == 0x2189D250)
			{
				return "HVY";
			}
			if (iParam0 == 0x50D4D19F)
			{
				return "KARIN";
			}
			if (iParam0 == 0xFE141DA6)
			{
				return "BRAVADO";
			}
			if (iParam0 == 0x59A9E570 || iParam0 == 0x34B82784)
			{
				return "PEGASSI";
			}
			if (iParam0 == 0x711D4738)
			{
				return "BF";
			}
			if (iParam0 == 0xB7D9F7F1)
			{
				return "DECLASSE";
			}
			if (iParam0 == 0x7397224C || iParam0 == 0x7A2EF5E4)
			{
				if (bParam1)
				{
					return "DEWBAUCH";
				}
				else
				{
					return "DEWBAUCHEE";
				}
			}
			if (iParam0 == 0x52FF9437)
			{
				return "COIL";
			}
			if ((iParam0 == 0x6DBD6C0A || iParam0 == 0x23CA25F2) || iParam0 == 0xA4A4E453)
			{
				return "VAPID";
			}
			if (iParam0 == 0xC4810400 || iParam0 == 0xB5EF4C33)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			if (iParam0 == 0x3201DD49)
			{
				return "KARIN";
			}
			if (iParam0 == 0x81BD2ED0 || iParam0 == 0x58CDAF30)
			{
				return "MAMMOTH";
			}
			if (iParam0 == 0x586765FB)
			{
				return "IMPONTE";
			}
			if (iParam0 == 0x34DBA661 || iParam0 == 0x33B98FE2)
			{
				return "OCELOT";
			}
			if (iParam0 == 0x00E83C17)
			{
				return "ALBANY";
			}
			if ((iParam0 == 0x41D149AA || iParam0 == 0x5097F589) || iParam0 == 0xE78CC3D9)
			{
				if (bParam1)
				{
					return "UBERMACH";
				}
				else
				{
					return "UBERMACHT";
				}
			}
			if (iParam0 == 0x35DED0DD)
			{
				return "ANNIS";
			}
			if (iParam0 == 0x6F946279)
			{
				return "DECLASSE";
			}
			if (iParam0 == 0xA4D99B7D)
			{
				return "COIL";
			}
			if ((iParam0 == 0x91CA96EE || iParam0 == 0x5D1903F9) || iParam0 == 0x276D98A3)
			{
				return "PFISTER";
			}
			if (iParam0 == 0x67D2B389)
			{
				if (bParam1)
				{
					return "BENEFAC";
				}
				else
				{
					return "BENEFACTOR";
				}
			}
			if (iParam0 == 0xF8C2E0E7)
			{
				return "CANIS";
			}
			if (iParam0 == 0x8408F33A)
			{
				if (bParam1)
				{
					return "GROTTI";
				}
				else
				{
					return "Grotti_2";
				}
			}
			if (iParam0 == 0xE8A8BA94)
			{
				if (bParam1)
				{
					return "LAMPADA";
				}
				else
				{
					return "LAMPADATI";
				}
			}
			if (iParam0 == 0xF34DFB25)
			{
				return "HVY";
			}
			if ((iParam0 == 0xED552C74 || iParam0 == 0xE99011C2) || iParam0 == 0x8198AEDC)
			{
				return "OVERFLOD";
			}
			if (iParam0 == 0x378236E1)
			{
				return "WEENY";
			}
			if ((((iParam0 == 0x71CBEA98 || iParam0 == 0xB472D2B5) || iParam0 == 0xB4F32118) || iParam0 == 0x4ABEBF23) || iParam0 == 0xC52C6B93)
			{
				return "VAPID";
			}
			if (iParam0 == 0x6068AD86)
			{
				return "VULCAR";
			}
			if (iParam0 == 0x3E5BD8D9)
			{
				if (bParam1)
				{
					return "LAMPADA";
				}
				else
				{
					return "LAMPADATI";
				}
			}
			if (iParam0 == 0x42836BE5)
			{
				return "DECLASSE";
			}
			if (iParam0 == 0x3D7C6410)
			{
				return "PEGASSI";
			}
			if (iParam0 == 0xF330CB6A)
			{
				return "DINKA";
			}
			if (iParam0 == 0xBC5DC07E)
			{
				return "CHEVAL";
			}
			if (iParam0 == 0xC514AAE0)
			{
				return "RUNE";
			}
			return "";
		}
	}

	vehicle::names_t vehicle::display_names_from_model(const model &m) {
		if (!m.is_vehicle()) {
			return names_t();
		}
		std::string cdn(_com_dn(m, true));
		if (cdn.empty()) {
			cdn = "";
		}
		return names_t(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m), cdn);
	}
} /* nob */
