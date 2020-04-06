#include <nob/entity.hpp>
#include <nob/hash.hpp>
#include <nob/log.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>

#include <rua/bytes.hpp>
#include <rua/sync.hpp>

#include <cstring>
#include <vector>

namespace nob {

// These data from ScriptHookV/NativeTrainer
const std::array<hasher, 304> base_vehicles{
	{"NINEF",		 "NINEF2",		 "BLISTA",		 "ASEA",
	 "ASEA2",		 "BOATTRAILER",	 "BUS",			 "ARMYTANKER",
	 "ARMYTRAILER",	 "ARMYTRAILER2", "SUNTRAP",		 "COACH",
	 "AIRBUS",		 "ASTEROPE",	 "AIRTUG",		 "AMBULANCE",
	 "BARRACKS",	 "BARRACKS2",	 "BALLER",		 "BALLER2",
	 "BJXL",		 "BANSHEE",		 "BENSON",		 "BFINJECTION",
	 "BIFF",		 "BLAZER",		 "BLAZER2",		 "BLAZER3",
	 "BISON",		 "BISON2",		 "BISON3",		 "BOXVILLE",
	 "BOXVILLE2",	 "BOXVILLE3",	 "BOBCATXL",	 "BODHI2",
	 "BUCCANEER",	 "BUFFALO",		 "BUFFALO2",	 "BULLDOZER",
	 "BULLET",		 "BLIMP",		 "BURRITO",		 "BURRITO2",
	 "BURRITO3",	 "BURRITO4",	 "BURRITO5",	 "CAVALCADE",
	 "CAVALCADE2",	 "POLICET",		 "GBURRITO",	 "CABLECAR",
	 "CADDY",		 "CADDY2",		 "CAMPER",		 "CARBONIZZARE",
	 "CHEETAH",		 "COMET2",		 "COGCABRIO",	 "COQUETTE",
	 "CUTTER",		 "GRESLEY",		 "DILETTANTE",	 "DILETTANTE2",
	 "DUNE",		 "DUNE2",		 "HOTKNIFE",	 "DLOADER",
	 "DUBSTA",		 "DUBSTA2",		 "DUMP",		 "RUBBLE",
	 "DOCKTUG",		 "DOMINATOR",	 "EMPEROR",		 "EMPEROR2",
	 "EMPEROR3",	 "ENTITYXF",	 "EXEMPLAR",	 "ELEGY2",
	 "F620",		 "FBI",			 "FBI2",		 "FELON",
	 "FELON2",		 "FELTZER2",	 "FIRETRUK",	 "FLATBED",
	 "FORKLIFT",	 "FQ2",			 "FUSILADE",	 "FUGITIVE",
	 "FUTO",		 "GRANGER",		 "GAUNTLET",	 "HABANERO",
	 "HAULER",		 "HANDLER",		 "INFERNUS",	 "INGOT",
	 "INTRUDER",	 "ISSI2",		 "JACKAL",		 "JOURNEY",
	 "JB700",		 "KHAMELION",	 "LANDSTALKER",	 "LGUARD",
	 "MANANA",		 "MESA",		 "MESA2",		 "MESA3",
	 "CRUSADER",	 "MINIVAN",		 "MIXER",		 "MIXER2",
	 "MONROE",		 "MOWER",		 "MULE",		 "MULE2",
	 "ORACLE",		 "ORACLE2",		 "PACKER",		 "PATRIOT",
	 "PBUS",		 "PENUMBRA",	 "PEYOTE",		 "PHANTOM",
	 "PHOENIX",		 "PICADOR",		 "POUNDER",		 "POLICE",
	 "POLICE4",		 "POLICE2",		 "POLICE3",		 "POLICEOLD1",
	 "POLICEOLD2",	 "PONY",		 "PONY2",		 "PRAIRIE",
	 "PRANGER",		 "PREMIER",		 "PRIMO",		 "PROPTRAILER",
	 "RANCHERXL",	 "RANCHERXL2",	 "RAPIDGT",		 "RAPIDGT2",
	 "RADI",		 "RATLOADER",	 "REBEL",		 "REGINA",
	 "REBEL2",		 "RENTALBUS",	 "RUMPO",		 "RUMPO2",
	 "RHINO",		 "RIOT",		 "RIPLEY",		 "ROCOTO",
	 "ROMERO",		 "SABREGT",		 "SADLER",		 "SADLER2",
	 "SANDKING",	 "SANDKING2",	 "SCHAFTER2",	 "SCHWARZER",
	 "SCRAP",		 "SEMINOLE",	 "SENTINEL",	 "SENTINEL2",
	 "ZION",		 "ZION2",		 "SERRANO",		 "SHERIFF",
	 "SHERIFF2",	 "SPEEDO",		 "SPEEDO2",		 "STANIER",
	 "STINGER",		 "STINGERGT",	 "STOCKADE",	 "STOCKADE3",
	 "STRATUM",		 "SULTAN",		 "SUPERD",		 "SURANO",
	 "SURFER",		 "SURFER2",		 "SURGE",		 "TACO",
	 "TAILGATER",	 "TAXI",		 "TRASH",		 "TRACTOR",
	 "TRACTOR2",	 "TRACTOR3",	 "GRAINTRAILER", "BALETRAILER",
	 "TIPTRUCK",	 "TIPTRUCK2",	 "TORNADO",		 "TORNADO2",
	 "TORNADO3",	 "TORNADO4",	 "TOURBUS",		 "TOWTRUCK",
	 "TOWTRUCK2",	 "UTILLITRUCK",	 "UTILLITRUCK2", "UTILLITRUCK3",
	 "WASHINGTON",	 "STRETCH",		 "YOUGA",		 "ZTYPE",
	 "SANCHEZ",		 "SANCHEZ2",	 "SCORCHER",	 "TRIBIKE",
	 "TRIBIKE2",	 "TRIBIKE3",	 "FIXTER",		 "CRUISER",
	 "BMX",			 "POLICEB",		 "AKUMA",		 "CARBONRS",
	 "BAGGER",		 "BATI",		 "BATI2",		 "RUFFIAN",
	 "DAEMON",		 "DOUBLE",		 "PCJ",			 "VADER",
	 "VIGERO",		 "FAGGIO2",		 "HEXER",		 "ANNIHILATOR",
	 "BUZZARD",		 "BUZZARD2",	 "CARGOBOB2",	 "CARGOBOB3",
	 "SKYLIFT",		 "POLMAV",		 "MAVERICK",	 "NEMESIS",
	 "FROGGER",		 "FROGGER2",	 "CUBAN800",	 "DUSTER",
	 "STUNT",		 "MAMMATUS",	 "JET",			 "SHAMAL",
	 "LUXOR",		 "TITAN",		 "LAZER",		 "CARGOPLANE",
	 "SQUALO",		 "MARQUIS",		 "DINGHY2",		 "JETMAX",
	 "PREDATOR",	 "SEASHARK2",	 "SUBMERSIBLE",	 "TRAILERS",
	 "TRAILERS2",	 "TRAILERS3",	 "TVTRAILER",	 "RAKETRAILER",
	 "TANKER",		 "TRAILERLOGS",	 "TR2",			 "TR3",
	 "TR4",			 "TRFLAT",		 "TRAILERSMALL", "VELUM",
	 "ADDER",		 "VOLTIC",		 "VACCA",		 "FUROREGT",
	 "BTYPE",		 "DOMINATOR2",	 "SUBMERSIBLE2", "RATLOADER2",
	 "BUCCANEER2",	 "VOODOO",		 "CARGOBOB4",	 "COGNOSCENTI",
	 "COGNOSCENTI2", "DINGHY4",		 "NIGHTSHADE",	 "SEASHARK3",
	 "SPEEDER2",	 "SUPERVOLITO",	 "SUPERVOLITO2", "TORO2",
	 "TROPIC2",		 "VALKYRIE2",	 "VERLIERER2",	 "BTYPE3"}};

std::vector<hasher> _ban_vehs;

static ntv::script_list_t::script_t *_shop_ctl = nullptr;

size_t _ban_vehs_g, _ban_vehs_li_find_base;
bool _finded_ban_vehs = false, _finding_ban_vehs = false;

// Reference from https://github.com/zorg93/EnableMpCars-GTAV
bool _find_ban_vehs() {
	static on_load reset([]() { _finded_ban_vehs = false; });

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

	if (!_shop_ctl) {
		_shop_ctl = ntv::script_list->find("shop_controller");
		if (!_shop_ctl) {
			return false;
		}
	}

	_finded_ban_vehs = rua::wait([]() -> bool {
		rua::masked_bytes pat;
		if (game_build >= 1604) {
			pat = {0x2D, 1111, 1111, 0x00, 0x00, 0x2C, 0x01, 1111, 1111,
				   0x56, 0x04, 0x00, 0x6E, 0x2E, 1111, 0x01, 0x5F, 1111,
				   1111, 1111, 1111, 0x04, 0x00, 0x6E, 0x2E, 1111, 0x01};
		} else {
			pat = {0x2C, 0x01, 1111, 1111, 0x20, 0x56, 0x04, 0x00,
				   0x6E, 0x2E, 1111, 0x01, 0x5F, 1111, 1111, 1111,
				   1111, 0x04, 0x00, 0x6E, 0x2E, 1111, 0x01};
		}
		auto &sc_inf = *_shop_ctl->info;
		for (size_t i = 0; i < sc_inf.code_page_count(); ++i) {
			auto mr = rua::bytes_view(
						  rua::generic_ptr(sc_inf.code_pages[i]),
						  sc_inf.code_page_size(i))
						  .match(pat);
			if (mr.empty() || mr.size() < 3) {
				continue;
			}
			_ban_vehs_g = *mr[mr.size() - 2].data().as<uint32_t *>() & 0xFFFFFF;
			return true;
		}
		return false;
	});

	_finding_ban_vehs = false;
	return _finded_ban_vehs;
}

void unban_vehicles() {
	if (_find_ban_vehs()) {
		ntv::global_table[_ban_vehs_g] = 1;
	}
}

// Reference from https://github.com/zorg93/EnableMpCars-GTAV
const std::vector<hasher> &banned_vehicles() {
	return _ban_vehs;

	if (_ban_vehs.size() || !_find_ban_vehs()) {
		return _ban_vehs;
	}

	while (!ntv::SCRIPT::HAS_SCRIPT_LOADED("shop_controller")) {
		yield();
	}

	_ban_vehs = rua::wait([]() -> std::vector<hasher> {
		auto &sc_inf = *_shop_ctl->info;
		std::vector<hasher> vehs;
		for (size_t i = 14; i < 400; i++) {
			if (*(uint8_t *)sc_inf.code_addr(_ban_vehs_li_find_base + i) ==
				0x62) {
				size_t switch_off = _ban_vehs_li_find_base + i;
				auto cur_addr = (uint64_t)sc_inf.code_addr(switch_off + 2);
				size_t start_off = switch_off + 2;
				size_t cases = *(uint8_t *)(cur_addr - 1);
				for (size_t i = 0; i < cases; i++) {
					cur_addr += 6;
					start_off += 6;
					size_t jump_off = *(uint16_t *)(cur_addr - 2);
					int64_t case_off =
						(int64_t)sc_inf.code_addr(start_off + jump_off);
					uint8_t code = *(uint8_t *)case_off;
					hash_t hash;
					if (code == 0x28) { // push int
						hash = *(uint32_t *)(case_off + 1);
					} else if (code == 0x61) { // push int 24
						hash = *(uint32_t *)(case_off + 1) & 0xFFFFFF;
					} else {
						continue;
					}
					vehs.emplace_back(hash);
				}
				break;
			}
		}
		return vehs;
	});
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

const char *_mfr_dn_flyer(hash_t iParam0, bool bParam1) {
	switch (iParam0) {
	case hash("frogger"):
	case hash("frogger2"):
		return "MAIBATSU";

	case hash("maverick"):
	case hash("polmav"):
	case hash("luxor"):
	case hash("shamal"):
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
		break;

	case hash("cargobob"):
	case hash("annihilator"):
	case hash("cuban800"):
	case hash("duster"):
	case hash("stunt"):
		return "WESTERN";
		break;

	case hash("buzzard"):
	case hash("buzzard2"):
		return "NAGASAKI";
		break;

	case hash("mammatus"):
	case hash("velum"):
	case hash("velum2"):
	case hash("lazer"):
		return "JOBUILT";
		break;
	}
	if (iParam0 == hash("vestra")) {
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
	}
	if (((((iParam0 == hash("miljet") || iParam0 == hash("swift")) ||
		   iParam0 == hash("swift2")) ||
		  iParam0 == hash("luxor2")) ||
		 iParam0 == hash("supervolito")) ||
		iParam0 == hash("supervolito2")) {
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
	}
	if (iParam0 == hash("besra")) {
		return "WESTERN";
	}
	if (iParam0 == hash("hydra") || iParam0 == 1489874736) {
		return "MAMMOTH";
	}
	if (iParam0 == hash("volatus") || iParam0 == hash("nimbus")) {
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
	}
	return "";
}

const char *_mfr_dn_boat(hash_t iParam0, bool bParam1) {
	switch (iParam0) {
	case hash("squalo"):
	case hash("tropic"):
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
		break;

	case hash("jetmax"):
	case hash("suntrap"):
		return "OCELOT";
		break;

	case hash("dinghy"):
		if (!bParam1) {
			return "OCELOT";
		}
		break;

	case hash("seashark2"):
		if (bParam1) {
			return "SPEEDOPH";
		} else {
			return "SPEEDOPHILE";
		}
		break;

	case hash("seashark3"):
		if (bParam1) {
			return "SPEEDOPH";
		} else {
			return "SPEEDOPHILE";
		}
		break;

	case hash("seashark"):
		if (bParam1) {
			return "SPEEDOPH";
		} else {
			return "SPEEDOPHILE";
		}
		break;

	case hash("toro"):
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
		break;
	}
	if (iParam0 == hash("speeder") || iParam0 == hash("speeder2")) {
		if (bParam1) {
			return "PEGASSI";
		} else {
			return "PEGASSI";
		}
	}
	return "";
}

const char *_mfr_dn(hash_t iParam0, bool bParam1) {
	if (ntv::VEHICLE::IS_THIS_MODEL_A_BOAT(iParam0)) {
		return _mfr_dn_boat(iParam0, bParam1);
	}
	if (ntv::VEHICLE::IS_THIS_MODEL_A_PLANE(iParam0) ||
		ntv::VEHICLE::IS_THIS_MODEL_A_HELI(iParam0)) {
		return _mfr_dn_flyer(iParam0, bParam1);
	}
	switch (iParam0) {
	case hash("khamelion"):
		return "HIJAK";
		break;

	case hash("issi2"):
	case 1854776567:
		return "WEENY";
		break;

	case hash("elegy2"):
	case -362150785:
		return "ANNIS";
		break;

	case hash("romero"):
		return "CHARIOT";
		break;

	case hash("baller"):
	case hash("baller2"):
	case hash("baller3"):
	case hash("baller4"):
	case hash("baller5"):
	case hash("baller6"):
		if (bParam1) {
			return "GALLIVAN";
		} else {
			return "GALIVANTER";
		}
		break;

	case hash("surfer"):
	case hash("surfer2"):
	case hash("dune"):
	case hash("bfinjection"):
		return "BF";
		break;

	case hash("feltzer2"):
	case hash("dubsta"):
	case hash("surano"):
	case hash("schwarzer"):
	case hash("schafter2"):
	case hash("serrano"):
	case hash("dubsta2"):
	case hash("feltzer3"):
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
		break;

	case hash("sentinel"):
	case hash("sentinel2"):
	case hash("zion"):
	case hash("zion2"):
	case 1862507111:
	case hash("oracle"):
	case hash("oracle2"):
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
		break;

	case hash("ztype"):
	case hash("adder"):
	case 1044193113:
		return "TRUFFADE";
		break;

	case hash("jb700"):
	case hash("rapidgt"):
	case hash("rapidgt2"):
	case hash("exemplar"):
	case hash("massacro"):
	case hash("massacro2"):
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
		break;

	case hash("tailgater"):
	case hash("ninef"):
	case hash("ninef2"):
	case hash("rocoto"):
	case 686471183:
		return "OBEY";
		break;

	case hash("picador"):
	case hash("surge"):
	case hash("fugitive"):
	case hash("marshall"):
		return "CHEVAL";
		break;

	case hash("mower"):
		if (bParam1) {
			return "JACKSHP";
		} else {
			return "JACKSHEEPE";
		}
		break;

	case hash("tornado"):
	case hash("tornado2"):
	case hash("tornado3"):
	case hash("burrito"):
	case hash("burrito2"):
	case hash("premier"):
	case hash("voodoo2"):
	case hash("sabregt"):
	case hash("rancherxl"):
	case hash("vigero"):
	case hash("asea"):
	case hash("asea2"):
	case hash("granger"):
	case hash("pranger"):
	case hash("sheriff"):
	case hash("sheriff2"):
	case hash("gburrito"):
	case hash("gburrito2"):
	case hash("stalion"):
		return "DECLASSE";
		break;

	case hash("buccaneer"):
	case hash("cavalcade"):
	case hash("cavalcade2"):
	case hash("emperor"):
	case hash("emperor2"):
	case hash("manana"):
	case hash("primo"):
	case hash("washington"):
	case hash("virgo"):
		return "ALBANY";
		break;

	case hash("banshee"):
	case hash("bison"):
	case hash("gresley"):
	case hash("youga"):
	case hash("gauntlet"):
	case hash("buffalo"):
	case hash("buffalo2"):
	case hash("ratloader"):
	case hash("dloader"):
	case hash("ratloader2"):
	case hash("rumpo"):
	case hash("banshee2"):
	case 722226637:
		return "BRAVADO";
		break;

	case hash("stinger"):
	case hash("stingergt"):
	case hash("cheetah"):
	case hash("carbonizzare"):
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
		break;

	case hash("coquette"):
	case hash("coquette3"):
		if (bParam1) {
			return "INVERTO";
		} else {
			return "Invetero";
		}
		break;

	case hash("radi"):
	case hash("sadler"):
	case hash("dominator"):
	case hash("sandking"):
	case hash("sandking2"):
	case hash("police"):
	case hash("police3"):
	case hash("policet"):
	case hash("benson"):
	case hash("bullet"):
	case hash("minivan"):
	case hash("speedo"):
	case hash("speedo2"):
	case hash("peyote"):
	case hash("towtruck"):
	case hash("towtruck2"):
	case hash("bobcatxl"):
	case hash("stanier"):
	case hash("hotknife"):
	case hash("slamvan"):
	case hash("guardian"):
	case hash("chino"):
	case -1349095620:
		return "VAPID";
		break;

	case hash("tiptruck"):
	case hash("taco"):
	case hash("utillitruck"):
	case hash("utillitruck2"):
	case hash("utillitruck3"):
	case hash("camper"):
	case hash("riot"):
	case hash("tourbus"):
	case hash("ambulance"):
	case hash("stockade"):
	case hash("boxville"):
	case hash("pony"):
		return "BRUTE";
		break;

	case hash("prairie"):
		return "BOLLOKAN";
		break;

	case hash("jackal"):
	case hash("f620"):
	case -941272559:
		return "OCELOT";
		break;

	case hash("mesa"):
	case hash("mesa3"):
	case hash("bodhi2"):
	case hash("seminole"):
	case hash("crusader"):
		return "CANIS";
		break;

	case hash("entityxf"):
		return "OVERFLOD";
		break;

	case hash("monroe"):
	case hash("infernus"):
	case hash("bati"):
	case hash("bati2"):
	case hash("vacca"):
	case hash("ruffian"):
	case hash("faggio2"):
	case hash("osiris"):
	case -682108547:
		return "PEGASSI";
		break;

	case hash("phoenix"):
	case hash("ruiner"):
	case hash("dukes"):
	case hash("dukes2"):
		return "IMPONTE";
		break;

	case hash("bjxl"):
	case hash("rebel"):
	case hash("rebel2"):
	case hash("asterope"):
	case hash("intruder"):
	case hash("futo"):
	case hash("sultan"):
	case hash("dilettante"):
	case hash("dilettante2"):
	case hash("kuruma"):
	case hash("kuruma2"):
	case hash("sultanrs"):
		return "KARIN";
		break;

	case hash("penumbra"):
	case hash("sanchez"):
	case hash("sanchez2"):
	case hash("mule"):
		return "MAIBATSU";
		break;

	case hash("blista"):
	case hash("blista2"):
	case hash("blista3"):
	case hash("double"):
	case hash("jester"):
	case hash("jester2"):
	case hash("enduro"):
	case hash("vindicator"):
	case hash("akuma"):
		return "DINKA";
		break;

	case hash("fq2"):
		return "FATHOM";
		break;

	case hash("voltic"):
	case hash("brawler"):
		return "COIL";
		break;
	}
	switch (iParam0) {
	case hash("felon"):
	case hash("felon2"):
	case hash("casco"):
	case -1829436850:
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
		break;

	case hash("comet2"):
		return "PFISTER";
		break;

	case hash("fusilade"):
		return "SCHYSTER";
		break;

	case hash("stretch"):
	case hash("regina"):
	case hash("landstalker"):
		if (bParam1) {
			return "DUNDREAR";
		} else {
			return "DUNDREARY";
		}
		break;

	case hash("handler"):
	case hash("bulldozer"):
	case hash("docktug"):
	case hash("cutter"):
	case hash("mixer"):
	case hash("mixer2"):
	case hash("barracks"):
	case hash("barracks2"):
	case hash("biff"):
	case hash("forklift"):
	case hash("ripley"):
	case hash("airtug"):
	case hash("dump"):
	case hash("insurgent2"):
	case hash("insurgent"):
		return "HVY";
		break;

	case hash("packer"):
	case hash("flatbed"):
	case hash("tiptruck2"):
	case hash("pounder"):
	case 1938952078:
		return "MTL";
		break;

	case hash("tractor"):
	case hash("tractor2"):
		return "STANLEY";
		break;

	case hash("hauler"):
	case hash("phantom"):
	case hash("trash"):
		return "JOBUILT";
		break;

	case hash("patriot"):
		return "MAMMOTH";
		break;

	case hash("journey"):
	case hash("stratum"):
		if (bParam1) {
			return "ZIRCONIU";
		} else {
			return "ZIRCONIUM";
		}
		break;

	case hash("vader"):
	case hash("pcj"):
		return "SHITZU";
		break;

	case hash("bagger"):
	case hash("daemon"):
	case hash("sovereign"):
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
		break;

	case hash("blazer"):
	case hash("caddy"):
	case hash("carbonrs"):
	case hash("blazer3"):
	case hash("blazer2"):
		return "NAGASAKI";
		break;

	case hash("nemesis"):
	case hash("lectro"):
		if (bParam1) {
			return "PRINCIPL";
		} else {
			return "PRINCIPE";
		}
		break;

	case hash("hexer"):
		return "LCC";
		break;

	case hash("bmx"):
	case hash("cruiser"):
	case hash("scorcher"):
		if (!bParam1) {
			return "Ped";
		}
		break;

	case hash("tribike"):
	case hash("tribike2"):
	case hash("tribike3"):
		if (!bParam1) {
			return "TriCycles";
		}
		break;

	case hash("cogcabrio"):
	case hash("superd"):
	case hash("windsor"):
		return "ENUS";
		break;

	case hash("habanero"):
		if (bParam1) {
			return "EMPEROR";
		} else {
			return "EMPORER";
		}
		break;

	case hash("ingot"):
	case -882629065:
		return "VULCAR";
		break;

	case hash("t20"):
		return "PROGEN";
		break;
	}
	if (iParam0 == hash("bifta")) {
		return "BF";
	} else if (iParam0 == hash("kalahari")) {
		return "CANIS";
	} else if (iParam0 == hash("paradise")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("btype")) {
		return "ALBANY";
	}
	if (iParam0 == hash("zentorno")) {
		return "PEGASSI";
	} else if (iParam0 == hash("jester")) {
		return "DINKA";
	} else if (iParam0 == hash("massacro")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	} else if (iParam0 == hash("turismor")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	} else if (iParam0 == hash("huntley")) {
		return "ENUS";
	} else if (iParam0 == hash("alpha")) {
		return "ALBANY";
	} else if (iParam0 == hash("thrust")) {
		return "DINKA";
	} else if (iParam0 == hash("sovereign")) {
		return "DINKA";
	}
	if (iParam0 == hash("thrust")) {
		return "DINKA";
	}
	if (iParam0 == hash("blade") || iParam0 == hash("monster")) {
		return "VAPID";
	}
	if (iParam0 == hash("warrener")) {
		return "VULCAR";
	}
	if ((iParam0 == hash("glendale") || iParam0 == hash("panto")) ||
		iParam0 == hash("dubsta3")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == hash("rhapsody")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("pigalle")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("coquette2")) {
		if (bParam1) {
			return "INVERTO";
		} else {
			return "Invetero";
		}
	}
	if (iParam0 == hash("innovation")) {
		return "LCC";
	}
	if (iParam0 == hash("hakuchou")) {
		return "SHITZU";
	}
	if (iParam0 == hash("furoregt")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("ratloader2")) {
		return "BRAVADO";
	} else if (iParam0 == hash("slamvan")) {
		return "VAPID";
	} else if (iParam0 == hash("jester2")) {
		return "DINKA";
	} else if (iParam0 == hash("massacro2")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == hash("windsor")) {
		return "ENUS";
	} else if (iParam0 == hash("chino") || iParam0 == hash("chino2")) {
		return "VAPID";
	} else if (iParam0 == hash("vindicator")) {
		return "DINKA";
	} else if (iParam0 == hash("virgo")) {
		return "ALBANY";
	} else if (iParam0 == hash("swift2") || iParam0 == hash("luxor2")) {
		return "BUCKING";
	} else if (iParam0 == hash("feltzer3")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	} else if (iParam0 == hash("t20")) {
		return "PROGEN";
	} else if (iParam0 == hash("osiris")) {
		return "PEGASSI";
	} else if (iParam0 == hash("coquette3")) {
		if (bParam1) {
			return "INVERTO";
		} else {
			return "Invetero";
		}
	} else if (iParam0 == hash("toro")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	} else if (iParam0 == hash("brawler")) {
		return "COIL";
	}
	if (iParam0 == hash("primo2") || iParam0 == hash("buccaneer2")) {
		return "ALBANY";
	} else if (iParam0 == hash("faction") || iParam0 == hash("faction2")) {
		return "WILLARD";
	} else if (
		(iParam0 == hash("moonbeam2") || iParam0 == hash("voodoo")) ||
		iParam0 == hash("moonbeam")) {
		return "DECLASSE";
	} else if (iParam0 == hash("chino2") || iParam0 == hash("dukes2")) {
		return "VAPID";
	}
	if (iParam0 == hash("faction3")) {
		return "WILLARD";
	}
	if ((iParam0 == hash("sabregt2") || iParam0 == hash("tornado5")) ||
		iParam0 == hash("virgo")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("virgo2") || iParam0 == hash("virgo3")) {
		if (bParam1) {
			return "DUNDREAR";
		} else {
			return "DUNDREARY";
		}
	}
	if (iParam0 == hash("slamvan3") || iParam0 == hash("minivan2")) {
		return "VAPID";
	}
	if (iParam0 == hash("lurcher") || iParam0 == hash("btype2")) {
		return "ALBANY";
	}
	if (iParam0 == hash("mamba") || iParam0 == hash("tampa")) {
		return "DECLASSE";
	}
	if (((iParam0 == hash("cognoscenti") || iParam0 == hash("cog55")) ||
		 iParam0 == hash("cog552")) ||
		iParam0 == hash("cognoscenti2")) {
		return "ENUS";
	}
	if (iParam0 == hash("verlierer2")) {
		return "BRAVADO";
	}
	if (((iParam0 == hash("schafter4") || iParam0 == hash("schafter3")) ||
		 iParam0 == hash("schafter5")) ||
		iParam0 == hash("schafter6")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (((iParam0 == hash("baller3") || iParam0 == hash("baller4")) ||
		 iParam0 == hash("baller5")) ||
		iParam0 == hash("baller6")) {
		if (bParam1) {
			return "GALLIVAN";
		} else {
			return "GALIVANTER";
		}
	}
	if (iParam0 == hash("nightshade")) {
		return "IMPONTE";
	}
	if (iParam0 == hash("btype3")) {
		return "ALBANY";
	}
	if (iParam0 == hash("pfister811")) {
		return "PFISTER";
	}
	if (iParam0 == hash("seven70")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == hash("rumpo3")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("bestiagts")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("prototipo")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("xls") || iParam0 == hash("xls2")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == hash("fmj")) {
		return "VAPID";
	}
	if (iParam0 == hash("windsor2")) {
		return "ENUS";
	}
	if (iParam0 == hash("reaper")) {
		return "PEGASSI";
	}
	if (((iParam0 == hash("contender") || iParam0 == hash("trophytruck")) ||
		 iParam0 == hash("trophytruck2")) ||
		iParam0 == hash("dominator2")) {
		return "VAPID";
	}
	if (iParam0 == hash("bf400")) {
		return "NAGASAKI";
	}
	if (iParam0 == hash("cliffhanger") || iParam0 == hash("gargoyle")) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if (iParam0 == hash("buffalo3") || iParam0 == hash("gauntlet2")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("omnis")) {
		return "OBEY";
	}
	if (iParam0 == hash("le7b")) {
		return "ANNIS";
	}
	if (iParam0 == hash("tropos")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("tampa2") || iParam0 == hash("stalion2")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("brioso")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("tyrus")) {
		return "PROGEN";
	}
	if (iParam0 == hash("lynx")) {
		return "OCELOT";
	}
	if (iParam0 == hash("sheava")) {
		if (bParam1) {
			return "EMPEROR";
		} else {
			return "EMPORER";
		}
	}
	if (iParam0 == hash("rallytruck")) {
		return "MTL";
	}
	if (iParam0 == hash("tornado6")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("avarus") || iParam0 == hash("sanctus")) {
		return "LCC";
	}
	if ((iParam0 == hash("chimera") || iParam0 == hash("shotaro")) ||
		iParam0 == hash("blazer4")) {
		return "NAGASAKI";
	}
	if (iParam0 == hash("defiler") || iParam0 == hash("hakuchou2")) {
		return "SHITZU";
	}
	if (((((iParam0 == hash("nightblade") || iParam0 == hash("zombiea")) ||
		   iParam0 == hash("zombieb")) ||
		  iParam0 == hash("daemon2")) ||
		 iParam0 == hash("ratbike")) ||
		iParam0 == hash("wolfsbane")) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if (iParam0 == hash("youga2")) {
		return "BRAVADO";
	}
	if (((iParam0 == hash("esskey") || iParam0 == hash("vortex")) ||
		 iParam0 == hash("faggio3")) ||
		iParam0 == hash("faggio")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("raptor")) {
		return "BF";
	}
	if (iParam0 == hash("manchez")) {
		return "MAIBATSU";
	}
	if (iParam0 == hash("blazer5")) {
		return "NAGASAKI";
	}
	if (iParam0 == hash("comet3")) {
		return "PFISTER";
	}
	if (iParam0 == hash("diablous") || iParam0 == hash("diablous2")) {
		if (bParam1) {
			return "PRINCIPL";
		} else {
			return "PRINCIPE";
		}
	}
	if ((iParam0 == hash("fcr") || iParam0 == hash("fcr2")) ||
		iParam0 == hash("tempesta")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("nero") || iParam0 == hash("nero2")) {
		return "TRUFFADE";
	}
	if (iParam0 == hash("penetrator")) {
		return "OCELOT";
	}
	if (iParam0 == hash("ruiner2")) {
		return "IMPONTE";
	}
	if (iParam0 == hash("technical2")) {
		return "KARIN";
	}
	if (iParam0 == hash("phantom2")) {
		return "JOBUILT";
	}
	if (iParam0 == hash("voltic2")) {
		return "COIL";
	}
	if (iParam0 == hash("wastelander")) {
		return "MTL";
	}
	if (iParam0 == hash("italigtb") || iParam0 == hash("italigtb2")) {
		return "PROGEN";
	}
	if (iParam0 == hash("dune5") || iParam0 == hash("dune4")) {
		return "BF";
	}
	if (iParam0 == hash("elegy") || iParam0 == hash("elegy2")) {
		return "ANNIS";
	}
	if (iParam0 == hash("specter") || iParam0 == hash("specter2")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == 1234311532) {
		return "PROGEN";
	}
	if (iParam0 == -1405937764) {
		return "PEGASSI";
	}
	if (iParam0 == 719660200) {
		return "HIJAK";
	}
	if (iParam0 == -982130927) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("dukes2")) {
		return "IMPONTE";
	}
	if (iParam0 == 159274291 || iParam0 == 917809321) {
		return "OCELOT";
	}
	if (iParam0 == 223240013) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if ((iParam0 == -1924433270 || iParam0 == 433954513) ||
		iParam0 == 562680400) {
		return "HVY";
	}
	if (iParam0 == 1356124575) {
		return "KARIN";
	}
	if (iParam0 == -32236122 || iParam0 == hash("bison3")) {
		return "BRAVADO";
	}
	if (iParam0 == 1504306544 || iParam0 == 884483972) {
		return "PEGASSI";
	}
	if (iParam0 == 1897744184) {
		return "BF";
	}
	if (iParam0 == -1210451983) {
		return "DECLASSE";
	}
	if (iParam0 == 1939284556 || iParam0 == 2049897956) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == 1392481335) {
		return "COIL";
	}
	if ((iParam0 == 1841130506 || iParam0 == 600450546) ||
		iParam0 == -1532697517) {
		return "VAPID";
	}
	if (iParam0 == -998177792 || iParam0 == -1242608589) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == 838982985) {
		return "KARIN";
	}
	if (iParam0 == -2118308144 || iParam0 == 1489874736) {
		return "MAMMOTH";
	}
	if (iParam0 == 1483171323) {
		return "IMPONTE";
	}
	if (iParam0 == 886810209 || iParam0 == 867799010) {
		return "OCELOT";
	}
	if (iParam0 == 15219735) {
		return "ALBANY";
	}
	if ((iParam0 == 1104234922 || iParam0 == 1352136073) ||
		iParam0 == -410205223) {
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
	}
	if (iParam0 == 903794909) {
		return "ANNIS";
	}
	if (iParam0 == 1871995513) {
		return "DECLASSE";
	}
	if (iParam0 == -1529242755) {
		return "COIL";
	}
	if ((iParam0 == -1848994066 || iParam0 == 1561920505) ||
		iParam0 == 661493923) {
		return "PFISTER";
	}
	if (iParam0 == 1741861769) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == -121446169) {
		return "CANIS";
	}
	if (iParam0 == -2079788230) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == -391595372) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == -212993243) {
		return "HVY";
	}
	if ((iParam0 == -313185164 || iParam0 == -376434238) ||
		iParam0 == -2120700196) {
		return "OVERFLOD";
	}
	if (iParam0 == 931280609) {
		return "WEENY";
	}
	if ((((iParam0 == 1909189272 || iParam0 == -1267543371) ||
		  iParam0 == -1259134696) ||
		 iParam0 == 1254014755) ||
		iParam0 == -986944621) {
		return "VAPID";
	}
	if (iParam0 == 1617472902) {
		return "VULCAR";
	}
	if (iParam0 == 1046206681) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == 1115909093) {
		return "DECLASSE";
	}
	if (iParam0 == 1031562256) {
		return "PEGASSI";
	}
	if (iParam0 == -214906006) {
		return "DINKA";
	}
	if (iParam0 == -1134706562) {
		return "CHEVAL";
	}
	if (iParam0 == -988501280) {
		return "RUNE";
	}
	if (iParam0 == 500482303) {
		return "OCELOT";
	}
	if (iParam0 == -54332285) {
		return "CANIS";
	}
	if (iParam0 == 1945374990) {
		return "MAIBATSU";
	}
	if (iParam0 == 1653666139) {
		return "MTL";
	}
	if (iParam0 == 219613597) {
		return "VAPID";
	}
	if (iParam0 == -420911112) {
		return "MAMMOTH";
	}
	if (iParam0 == 2069146067) {
		return "PEGASSI";
	}
	if (iParam0 == 321186144) {
		return "ENUS";
	}
	if (iParam0 == 2044532910) {
		return "HVY";
	}
	if (iParam0 == -638562243) {
		return "DECLASSE";
	}
	if ((iParam0 == 1721676810 || iParam0 == 840387324) ||
		iParam0 == -715746948) {
		return "BRAVADO";
	}
	if ((iParam0 == -1146969353 || iParam0 == 1542143200) ||
		iParam0 == -579747861) {
		return "HVY";
	}
	if ((iParam0 == 628003514 || iParam0 == 1537277726) ||
		iParam0 == 1239571361) {
		return "WEENY";
	}
	if (iParam0 == -1168952148) {
		return "PEGASSI";
	}
	if ((((((((((iParam0 == -1566607184 || iParam0 == 444994115) ||
				iParam0 == 1637620610) ||
			   iParam0 == -755532233) ||
			  iParam0 == -688189648) ||
			 iParam0 == -1375060657) ||
			iParam0 == -1293924613) ||
		   iParam0 == -2061049099) ||
		  iParam0 == 373261600) ||
		 iParam0 == 1742022738) ||
		iParam0 == hash("slamvan2")) {
		return "VAPID";
	}
	if (iParam0 == 1591739866) {
		if (bParam1) {
			return "PRINCIPL";
		} else {
			return "PRINCIPE";
		}
	}
	if ((((((((iParam0 == -2096690334 || iParam0 == 1009171724) ||
			  iParam0 == -1924800695) ||
			 iParam0 == -1744505657) ||
			iParam0 == -49115651) ||
		   iParam0 == 1456744817) ||
		  iParam0 == 2139203625) ||
		 iParam0 == -1890996696) ||
		iParam0 == 2038858402) {
		return "DECLASSE";
	}
	if (iParam0 == 1279262537) {
		return "SCHYSTER";
	}
	if (iParam0 == -507495760) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == -331467772) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if ((iParam0 == -801550069 || iParam0 == 679453769) ||
		iParam0 == 1909700336) {
		return "MTL";
	}
	if ((iParam0 == -27326686 || iParam0 == -1812949672) ||
		iParam0 == -1374500452) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if ((iParam0 == 668439077 || iParam0 == -1694081890) ||
		iParam0 == -2042350822) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if ((iParam0 == 540101442 || iParam0 == -1106120762) ||
		iParam0 == -1478704292) {
		return "ANNIS";
	}
	if (iParam0 == -1349095620 || iParam0 == -1804415708) {
		return "VAPID";
	}
	if (iParam0 == 686471183) {
		return "OBEY";
	}
	if (iParam0 == 310284501 || iParam0 == 1854776567) {
		return "WEENY";
	}
	if (iParam0 == 722226637 || iParam0 == 1934384720) {
		return "BRAVADO";
	}
	if (iParam0 == -362150785 || iParam0 == -324618589) {
		return "ANNIS";
	}
	if (iParam0 == -664141241) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == -941272559 || iParam0 == -208911803) {
		return "OCELOT";
	}
	if (iParam0 == -882629065) {
		return "VULCAR";
	}
	if (iParam0 == -1829436850) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == -447711397 || iParam0 == 1416466158) {
		return "ENUS";
	}
	if (iParam0 == 1044193113) {
		return "TRUFFADE";
	}
	if (iParam0 == 1862507111) {
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
	}
	if (iParam0 == 1323778901) {
		return "PROGEN";
	}
	if (iParam0 == -1620126302) {
		return "VYSSER";
	}
	if (iParam0 == 916547552) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if (iParam0 == hash("burrito") || iParam0 == hash("burrito2")) {
		return "DECLASSE";
	}
	if (iParam0 == 340154634) {
		return "PROGEN";
	}
	if (iParam0 == -1756021720) {
		return "KARIN";
	}
	if (iParam0 == -1132721664) {
		return "OVERFLOD";
	}
	if (iParam0 == 409049982) {
		return "DINKA";
	}
	if (iParam0 == -834353991) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == 83136452) {
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
	}
	if (iParam0 == 987469656) {
		return "DINKA";
	}
	if (iParam0 == 872704284) {
		return "KARIN";
	}
	if (iParam0 == 1456336509) {
		return "ALBANY";
	}
	if (iParam0 == 1284356689) {
		return "RUNE";
	}
	if (!bParam1) {
		if (!strcmp(
				ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0),
				"GALLIVAN")) {
			return "GALIVANTER";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "BENEFAC")) {
			return "BENEFACTOR";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "UBERMACH")) {
			return "UBERMACHT";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "DEWBAUCH")) {
			return "DEWBAUCHEE";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "JACKSHP")) {
			return "JACKSHEEPE";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "GROTTI")) {
			return "Grotti_2";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "INVERTO")) {
			return "Invetero";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "LAMPADA")) {
			return "LAMPADATI";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "DUNDREAR")) {
			return "DUNDREARY";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "ZIRCONIU")) {
			return "ZIRCONIUM";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "WESTERN")) {
			return "WESTERNMOTORCYCLE";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "PRINCIPL")) {
			return "PRINCIPE";
		} else if (!strcmp(
					   ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
						   iParam0),
					   "EMPEROR")) {
			return "EMPORER";
		} else {
			return ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(
				iParam0);
		}
	} else {
		return ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0);
	}
	return "";
}

} // namespace

vehicle::names_t vehicle::display_names_from_model(const model &m) {
	if (!m.is_vehicle()) {
		return names_t();
	}
	if (game_build >= 1868) {
		return names_t(
			ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m),
			ntv::VEHICLE::GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(m));
	}
	std::string mn(_mfr_dn(m, true));
	if (mn.empty()) {
		return names_t(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m));
	}
	return names_t(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(m), mn);
}

} // namespace nob
