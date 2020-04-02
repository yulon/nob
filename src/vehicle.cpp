#include <nob/entity.hpp>
#include <nob/hash.hpp>
#include <nob/log.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>

#include <rua/bytes.hpp>
#include <rua/sync.hpp>

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

const char *_com_dn_flyer(hash_t iParam0, bool bParam1) {
	switch (iParam0) {
	case hash("FROGGER"):
	case hash("frogger2"):
		return "MAIBATSU";

	case hash("MAVERICK"):
	case hash("POLMAV"):
	case hash("LUXOR"):
	case hash("SHAMAL"):
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
		break;

	case hash("CARGOBOB"):
	case hash("annihilator"):
	case hash("CUBAN800"):
	case hash("DUSTER"):
	case hash("STUNT"):
		return "WESTERN";
		break;

	case hash("BUZZARD"):
	case hash("BUZZARD2"):
		return "NAGASAKI";
		break;

	case hash("MAMMATUS"):
	case hash("VELUM"):
	case hash("VELUM2"):
	case hash("LAZER"):
		return "JOBUILT";
		break;
	}
	if (iParam0 == hash("VESTRA")) {
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
	}
	if (((((iParam0 == hash("MILJET") || iParam0 == hash("SWIFT")) ||
		   iParam0 == hash("SWIFT2")) ||
		  iParam0 == hash("LUXOR2")) ||
		 iParam0 == hash("supervolito")) ||
		iParam0 == hash("supervolito2")) {
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
	}
	if (iParam0 == hash("BESRA")) {
		return "WESTERN";
	}
	if (iParam0 == hash("HYDRA") || iParam0 == hash("thruster")) {
		return "MAMMOTH";
	}
	if (iParam0 == hash("VOLATUS") || iParam0 == hash("NIMBUS")) {
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
	}
	return "";
}

const char *_com_dn_boat(hash_t iParam0, bool bParam1) {
	switch (iParam0) {
	case hash("SQUALO"):
	case hash("TROPIC"):
		if (bParam1) {
			return "BUCKING";
		} else {
			return "BUCKINGHAM";
		}
		break;

	case hash("JETMAX"):
	case hash("SUNTRAP"):
		return "OCELOT";
		break;

	case hash("DINGHY"):
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

	case hash("SEASHARK"):
		if (bParam1) {
			return "SPEEDOPH";
		} else {
			return "SPEEDOPHILE";
		}
		break;

	case hash("TORO"):
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
		break;
	}
	if (iParam0 == hash("SPEEDER") || iParam0 == hash("speeder2")) {
		if (bParam1) {
			return "PEGASSI";
		} else {
			return "PEGASSI";
		}
	}
	return "";
}

const char *_com_dn(hash_t iParam0, bool bParam1) {
	if (ntv::VEHICLE::IS_THIS_MODEL_A_BOAT(iParam0)) {
		return _com_dn_boat(iParam0, bParam1);
	}
	if (ntv::VEHICLE::IS_THIS_MODEL_A_PLANE(iParam0) ||
		ntv::VEHICLE::IS_THIS_MODEL_A_HELI(iParam0)) {
		return _com_dn_flyer(iParam0, bParam1);
	}
	switch (iParam0) {
	case hash("khamelion"):
		return "HIJAK";
		break;

	case hash("ISSI2"):
	case hash("issi7"):
		return "WEENY";
		break;

	case hash("ELEGY2"):
	case hash("hellion"):
		return "ANNIS";
		break;

	case hash("ROMERO"):
		return "CHARIOT";
		break;

	case hash("BALLER"):
	case hash("BALLER2"):
	case hash("BALLER3"):
	case hash("BALLER4"):
	case hash("BALLER5"):
	case hash("BALLER6"):
		if (bParam1) {
			return "GALLIVAN";
		} else {
			return "GALIVANTER";
		}
		break;

	case hash("SURFER"):
	case hash("SURFER2"):
	case hash("DUNE"):
	case hash("bfinjection"):
		return "BF";
		break;

	case hash("feltzer2"):
	case hash("DUBSTA"):
	case hash("SURANO"):
	case hash("schwarzer"):
	case hash("SCHAFTER2"):
	case hash("SERRANO"):
	case hash("dubsta2"):
	case hash("FELTZER3"):
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
		break;

	case hash("SENTINEL"):
	case hash("SENTINEL2"):
	case hash("ZION"):
	case hash("ZION2"):
	case hash("zion3"):
	case hash("ORACLE"):
	case hash("ORACLE2"):
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
		break;

	case hash("ZTYPE"):
	case hash("ADDER"):
	case hash("thrax"):
		return "TRUFFADE";
		break;

	case hash("JB700"):
	case hash("RAPIDGT"):
	case hash("rapidgt2"):
	case hash("EXEMPLAR"):
	case hash("MASSACRO"):
	case hash("MASSACRO2"):
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
		break;

	case hash("TAILGATER"):
	case hash("NINEF"):
	case hash("NINEF2"):
	case hash("ROCOTO"):
	case hash("drafter"):
		return "OBEY";
		break;

	case hash("PICADOR"):
	case hash("SURGE"):
	case hash("FUGITIVE"):
	case hash("MARSHALL"):
		return "CHEVAL";
		break;

	case hash("MOWER"):
		if (bParam1) {
			return "JACKSHP";
		} else {
			return "JACKSHEEPE";
		}
		break;

	case hash("TORNADO"):
	case hash("TORNADO2"):
	case hash("TORNADO3"):
	case hash("BURRITO"):
	case hash("burrito2"):
	case hash("PREMIER"):
	case hash("VOODOO2"):
	case hash("SABREGT"):
	case hash("rancherxl"):
	case hash("VIGERO"):
	case hash("ASEA"):
	case hash("asea2"):
	case hash("GRANGER"):
	case hash("PRANGER"):
	case hash("SHERIFF"):
	case hash("SHERIFF2"):
	case hash("GBURRITO"):
	case hash("GBURRITO2"):
	case hash("STALION"):
		return "DECLASSE";
		break;

	case hash("buccaneer"):
	case hash("cavalcade"):
	case hash("cavalcade2"):
	case hash("EMPEROR"):
	case hash("EMPEROR2"):
	case hash("MANANA"):
	case hash("PRIMO"):
	case hash("washington"):
	case hash("VIRGO"):
		return "ALBANY";
		break;

	case hash("BANSHEE"):
	case hash("BISON"):
	case hash("GRESLEY"):
	case hash("YOUGA"):
	case hash("GAUNTLET"):
	case hash("BUFFALO"):
	case hash("BUFFALO2"):
	case hash("ratloader"):
	case hash("DLOADER"):
	case hash("ratloader2"):
	case hash("RUMPO"):
	case hash("BANSHEE2"):
	case hash("gauntlet3"):
		return "BRAVADO";
		break;

	case hash("STINGER"):
	case hash("stingergt"):
	case hash("CHEETAH"):
	case hash("carbonizzare"):
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
		break;

	case hash("COQUETTE"):
	case hash("COQUETTE3"):
		if (bParam1) {
			return "INVERTO";
		} else {
			return "Invetero";
		}
		break;

	case hash("RADI"):
	case hash("SADLER"):
	case hash("dominator"):
	case hash("SANDKING"):
	case hash("sandking2"):
	case hash("POLICE"):
	case hash("police3"):
	case hash("POLICET"):
	case hash("BENSON"):
	case hash("BULLET"):
	case hash("MINIVAN"):
	case hash("SPEEDO"):
	case hash("SPEEDO2"):
	case hash("PEYOTE"):
	case hash("TOWTRUCK"):
	case hash("towtruck2"):
	case hash("BOBCATXL"):
	case hash("STANIER"):
	case hash("HOTKNIFE"):
	case hash("SLAMVAN"):
	case hash("GUARDIAN"):
	case hash("CHINO"):
	case hash("caracara2"):
		return "VAPID";
		break;

	case hash("TIPTRUCK"):
	case hash("TACO"):
	case hash("utillitruck"):
	case hash("utillitruck2"):
	case hash("utillitruck3"):
	case hash("CAMPER"):
	case hash("RIOT"):
	case hash("TOURBUS"):
	case hash("ambulance"):
	case hash("STOCKADE"):
	case hash("BOXVILLE"):
	case hash("PONY"):
		return "BRUTE";
		break;

	case hash("PRAIRIE"):
		return "BOLLOKAN";
		break;

	case hash("JACKAL"):
	case hash("F620"):
	case hash("locust"):
		return "OCELOT";
		break;

	case hash("MESA"):
	case hash("MESA3"):
	case hash("BODHI2"):
	case hash("SEMINOLE"):
	case hash("CRUSADER"):
		return "CANIS";
		break;

	case hash("ENTITYXF"):
		return "OVERFLOD";
		break;

	case hash("MONROE"):
	case hash("INFERNUS"):
	case hash("BATI"):
	case hash("BATI2"):
	case hash("VACCA"):
	case hash("RUFFIAN"):
	case hash("faggio2"):
	case hash("OSIRIS"):
	case hash("zorrusso"):
		return "PEGASSI";
		break;

	case hash("PHOENIX"):
	case hash("RUINER"):
	case hash("DUKES"):
	case hash("DUKES2"):
		return "IMPONTE";
		break;

	case hash("BJXL"):
	case hash("REBEL"):
	case hash("REBEL2"):
	case hash("asterope"):
	case hash("INTRUDER"):
	case hash("FUTO"):
	case hash("SULTAN"):
	case hash("dilettante"):
	case hash("dilettante2"):
	case hash("KURUMA"):
	case hash("KURUMA2"):
	case hash("SULTANRS"):
		return "KARIN";
		break;

	case hash("PENUMBRA"):
	case hash("SANCHEZ"):
	case hash("SANCHEZ2"):
	case hash("MULE"):
		return "MAIBATSU";
		break;

	case hash("BLISTA"):
	case hash("BLISTA2"):
	case hash("BLISTA3"):
	case hash("DOUBLE"):
	case hash("JESTER"):
	case hash("JESTER2"):
	case hash("ENDURO"):
	case hash("VINDICATOR"):
	case hash("AKUMA"):
		return "DINKA";
		break;

	case hash("FQ2"):
		return "FATHOM";
		break;

	case hash("VOLTIC"):
	case hash("BRAWLER"):
		return "COIL";
		break;
	}
	switch (iParam0) {
	case hash("FELON"):
	case hash("FELON2"):
	case hash("CASCO"):
	case hash("Novak"):
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
		break;

	case hash("COMET2"):
		return "PFISTER";
		break;

	case hash("FUSILADE"):
		return "SCHYSTER";
		break;

	case hash("STRETCH"):
	case hash("REGINA"):
	case hash("LANDSTALKER"):
		if (bParam1) {
			return "DUNDREAR";
		} else {
			return "DUNDREARY";
		}
		break;

	case hash("HANDLER"):
	case hash("bulldozer"):
	case hash("DOCKTUG"):
	case hash("CUTTER"):
	case hash("MIXER"):
	case hash("MIXER2"):
	case hash("BARRACKS"):
	case hash("BARRACKS2"):
	case hash("BIFF"):
	case hash("forklift"):
	case hash("RIPLEY"):
	case hash("AIRTUG"):
	case hash("DUMP"):
	case hash("INSURGENT2"):
	case hash("INSURGENT"):
		return "HVY";
		break;

	case hash("PACKER"):
	case hash("FLATBED"):
	case hash("TIPTRUCK2"):
	case hash("POUNDER"):
	case hash("FIRETRUK"):
		return "MTL";
		break;

	case hash("TRACTOR"):
	case hash("TRACTOR2"):
		return "STANLEY";
		break;

	case hash("HAULER"):
	case hash("PHANTOM"):
	case hash("TRASH"):
		return "JOBUILT";
		break;

	case hash("PATRIOT"):
		return "MAMMOTH";
		break;

	case hash("JOURNEY"):
	case hash("STRATUM"):
		if (bParam1) {
			return "ZIRCONIU";
		} else {
			return "ZIRCONIUM";
		}
		break;

	case hash("VADER"):
	case hash("PCJ"):
		return "SHITZU";
		break;

	case hash("BAGGER"):
	case hash("DAEMON"):
	case hash("SOVEREIGN"):
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
		break;

	case hash("BLAZER"):
	case hash("CADDY"):
	case hash("carbonrs"):
	case hash("BLAZER3"):
	case hash("BLAZER2"):
		return "NAGASAKI";
		break;

	case hash("NEMESIS"):
	case hash("LECTRO"):
		if (bParam1) {
			return "PRINCIPL";
		} else {
			return "PRINCIPE";
		}
		break;

	case hash("HEXER"):
		return "LCC";
		break;

	case hash("BMX"):
	case hash("CRUISER"):
	case hash("SCORCHER"):
		if (!bParam1) {
			return "Ped";
		}
		break;

	case hash("TRIBIKE"):
	case hash("TRIBIKE2"):
	case hash("TRIBIKE3"):
		if (!bParam1) {
			return "TriCycles";
		}
		break;

	case hash("cogcabrio"):
	case hash("SUPERD"):
	case hash("WINDSOR"):
		return "ENUS";
		break;

	case hash("HABANERO"):
		if (bParam1) {
			return "EMPEROR";
		} else {
			return "EMPORER";
		}
		break;

	case hash("INGOT"):
	case hash("nebula"):
		return "VULCAR";
		break;

	case hash("T20"):
		return "PROGEN";
		break;
	}
	if (iParam0 == hash("BIFTA")) {
		return "BF";
	} else if (iParam0 == hash("KALAHARI")) {
		return "CANIS";
	} else if (iParam0 == hash("PARADISE")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("BTYPE")) {
		return "ALBANY";
	}
	if (iParam0 == hash("ZENTORNO")) {
		return "PEGASSI";
	} else if (iParam0 == hash("JESTER")) {
		return "DINKA";
	} else if (iParam0 == hash("MASSACRO")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	} else if (iParam0 == hash("TURISMOR")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	} else if (iParam0 == hash("HUNTLEY")) {
		return "ENUS";
	} else if (iParam0 == hash("ALPHA")) {
		return "ALBANY";
	} else if (iParam0 == hash("THRUST")) {
		return "DINKA";
	} else if (iParam0 == hash("SOVEREIGN")) {
		return "DINKA";
	}
	if (iParam0 == hash("THRUST")) {
		return "DINKA";
	}
	if (iParam0 == hash("BLADE") || iParam0 == hash("MONSTER")) {
		return "VAPID";
	}
	if (iParam0 == hash("WARRENER")) {
		return "VULCAR";
	}
	if ((iParam0 == hash("GLENDALE") || iParam0 == hash("PANTO")) ||
		iParam0 == hash("DUBSTA3")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == hash("RHAPSODY")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("PIGALLE")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("COQUETTE2")) {
		if (bParam1) {
			return "INVERTO";
		} else {
			return "Invetero";
		}
	}
	if (iParam0 == hash("INNOVATION")) {
		return "LCC";
	}
	if (iParam0 == hash("HAKUCHOU")) {
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
	} else if (iParam0 == hash("SLAMVAN")) {
		return "VAPID";
	} else if (iParam0 == hash("JESTER2")) {
		return "DINKA";
	} else if (iParam0 == hash("MASSACRO2")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == hash("WINDSOR")) {
		return "ENUS";
	} else if (iParam0 == hash("CHINO") || iParam0 == hash("CHINO2")) {
		return "VAPID";
	} else if (iParam0 == hash("VINDICATOR")) {
		return "DINKA";
	} else if (iParam0 == hash("VIRGO")) {
		return "ALBANY";
	} else if (iParam0 == hash("SWIFT2") || iParam0 == hash("LUXOR2")) {
		return "BUCKING";
	} else if (iParam0 == hash("FELTZER3")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	} else if (iParam0 == hash("T20")) {
		return "PROGEN";
	} else if (iParam0 == hash("OSIRIS")) {
		return "PEGASSI";
	} else if (iParam0 == hash("COQUETTE3")) {
		if (bParam1) {
			return "INVERTO";
		} else {
			return "Invetero";
		}
	} else if (iParam0 == hash("TORO")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	} else if (iParam0 == hash("BRAWLER")) {
		return "COIL";
	}
	if (iParam0 == hash("PRIMO2") || iParam0 == hash("buccaneer2")) {
		return "ALBANY";
	} else if (iParam0 == hash("FACTION") || iParam0 == hash("FACTION2")) {
		return "WILLARD";
	} else if (
		(iParam0 == hash("MOONBEAM2") || iParam0 == hash("VOODOO")) ||
		iParam0 == hash("MOONBEAM")) {
		return "DECLASSE";
	} else if (iParam0 == hash("CHINO2") || iParam0 == hash("DUKES2")) {
		return "VAPID";
	}
	if (iParam0 == hash("FACTION3")) {
		return "WILLARD";
	}
	if ((iParam0 == hash("SABREGT2") || iParam0 == hash("TORNADO5")) ||
		iParam0 == hash("VIRGO")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("VIRGO2") || iParam0 == hash("VIRGO3")) {
		if (bParam1) {
			return "DUNDREAR";
		} else {
			return "DUNDREARY";
		}
	}
	if (iParam0 == hash("SLAMVAN3") || iParam0 == hash("MINIVAN2")) {
		return "VAPID";
	}
	if (iParam0 == hash("LURCHER") || iParam0 == hash("BTYPE2")) {
		return "ALBANY";
	}
	if (iParam0 == hash("MAMBA") || iParam0 == hash("TAMPA")) {
		return "DECLASSE";
	}
	if (((iParam0 == hash("cognoscenti") || iParam0 == hash("COG55")) ||
		 iParam0 == hash("COG552")) ||
		iParam0 == hash("cognoscenti2")) {
		return "ENUS";
	}
	if (iParam0 == hash("verlierer2")) {
		return "BRAVADO";
	}
	if (((iParam0 == hash("SCHAFTER4") || iParam0 == hash("SCHAFTER3")) ||
		 iParam0 == hash("SCHAFTER5")) ||
		iParam0 == hash("SCHAFTER6")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (((iParam0 == hash("BALLER3") || iParam0 == hash("BALLER4")) ||
		 iParam0 == hash("BALLER5")) ||
		iParam0 == hash("BALLER6")) {
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
	if (iParam0 == hash("PFISTER811")) {
		return "PFISTER";
	}
	if (iParam0 == hash("SEVEN70")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == hash("RUMPO3")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("BESTIAGTS")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("PROTOTIPO")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("XLS") || iParam0 == hash("XLS2")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == hash("FMJ")) {
		return "VAPID";
	}
	if (iParam0 == hash("WINDSOR2")) {
		return "ENUS";
	}
	if (iParam0 == hash("REAPER")) {
		return "PEGASSI";
	}
	if (((iParam0 == hash("CONTENDER") || iParam0 == hash("trophytruck")) ||
		 iParam0 == hash("trophytruck2")) ||
		iParam0 == hash("DOMINATOR2")) {
		return "VAPID";
	}
	if (iParam0 == hash("BF400")) {
		return "NAGASAKI";
	}
	if (iParam0 == hash("CLIFFHANGER") || iParam0 == hash("GARGOYLE")) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if (iParam0 == hash("BUFFALO3") || iParam0 == hash("GAUNTLET2")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("OMNIS")) {
		return "OBEY";
	}
	if (iParam0 == hash("LE7B")) {
		return "ANNIS";
	}
	if (iParam0 == hash("TROPOS")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("TAMPA2") || iParam0 == hash("STALION2")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("BRIOSO")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("TYRUS")) {
		return "PROGEN";
	}
	if (iParam0 == hash("LYNX")) {
		return "OCELOT";
	}
	if (iParam0 == hash("SHEAVA")) {
		if (bParam1) {
			return "EMPEROR";
		} else {
			return "EMPORER";
		}
	}
	if (iParam0 == hash("RALLYTRUCK")) {
		return "MTL";
	}
	if (iParam0 == hash("TORNADO6")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("AVARUS") || iParam0 == hash("SANCTUS")) {
		return "LCC";
	}
	if ((iParam0 == hash("CHIMERA") || iParam0 == hash("SHOTARO")) ||
		iParam0 == hash("BLAZER4")) {
		return "NAGASAKI";
	}
	if (iParam0 == hash("DEFILER") || iParam0 == hash("HAKUCHOU2")) {
		return "SHITZU";
	}
	if (((((iParam0 == hash("NIGHTBLADE") || iParam0 == hash("ZOMBIEA")) ||
		   iParam0 == hash("ZOMBIEB")) ||
		  iParam0 == hash("DAEMON2")) ||
		 iParam0 == hash("RATBIKE")) ||
		iParam0 == hash("WOLFSBANE")) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if (iParam0 == hash("YOUGA2")) {
		return "BRAVADO";
	}
	if (((iParam0 == hash("ESSKEY") || iParam0 == hash("VORTEX")) ||
		 iParam0 == hash("FAGGIO3")) ||
		iParam0 == hash("FAGGIO")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("RAPTOR")) {
		return "BF";
	}
	if (iParam0 == hash("MANCHEZ")) {
		return "MAIBATSU";
	}
	if (iParam0 == hash("BLAZER5")) {
		return "NAGASAKI";
	}
	if (iParam0 == hash("COMET3")) {
		return "PFISTER";
	}
	if (iParam0 == hash("DIABLOUS") || iParam0 == hash("DIABLOUS2")) {
		if (bParam1) {
			return "PRINCIPL";
		} else {
			return "PRINCIPE";
		}
	}
	if ((iParam0 == hash("FCR") || iParam0 == hash("FCR2")) ||
		iParam0 == hash("TEMPESTA")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("NERO") || iParam0 == hash("NERO2")) {
		return "TRUFFADE";
	}
	if (iParam0 == hash("penetrator")) {
		return "OCELOT";
	}
	if (iParam0 == hash("RUINER2")) {
		return "IMPONTE";
	}
	if (iParam0 == hash("TECHNICAL2")) {
		return "KARIN";
	}
	if (iParam0 == hash("PHANTOM2")) {
		return "JOBUILT";
	}
	if (iParam0 == hash("VOLTIC2")) {
		return "COIL";
	}
	if (iParam0 == hash("wastelander")) {
		return "MTL";
	}
	if (iParam0 == hash("ITALIGTB") || iParam0 == hash("ITALIGTB2")) {
		return "PROGEN";
	}
	if (iParam0 == hash("DUNE5") || iParam0 == hash("DUNE4")) {
		return "BF";
	}
	if (iParam0 == hash("ELEGY") || iParam0 == hash("ELEGY2")) {
		return "ANNIS";
	}
	if (iParam0 == hash("SPECTER") || iParam0 == hash("SPECTER2")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == hash("GP1")) {
		return "PROGEN";
	}
	if (iParam0 == hash("INFERNUS2")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("RUSTON")) {
		return "HIJAK";
	}
	if (iParam0 == hash("TURISMO2")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("DUKES2")) {
		return "IMPONTE";
	}
	if (iParam0 == hash("ARDENT") || iParam0 == hash("XA21")) {
		return "OCELOT";
	}
	if (iParam0 == hash("CHEETAH2")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if ((iParam0 == hash("INSURGENT3") || iParam0 == hash("NIGHTSHARK")) ||
		iParam0 == hash("APC")) {
		return "HVY";
	}
	if (iParam0 == hash("TECHNICAL3")) {
		return "KARIN";
	}
	if (iParam0 == hash("HALFTRACK") || iParam0 == hash("bison3")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("TORERO") || iParam0 == hash("OPPRESSOR")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("DUNE3")) {
		return "BF";
	}
	if (iParam0 == hash("TAMPA3")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("VAGNER") || iParam0 == hash("RAPIDGT3")) {
		if (bParam1) {
			return "DEWBAUCH";
		} else {
			return "DEWBAUCHEE";
		}
	}
	if (iParam0 == hash("CYCLONE")) {
		return "COIL";
	}
	if ((iParam0 == hash("RETINUE") || iParam0 == hash("hustler")) ||
		iParam0 == hash("riata")) {
		return "VAPID";
	}
	if (iParam0 == hash("VISIONE") || iParam0 == hash("VIGILANTE")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("z190")) {
		return "KARIN";
	}
	if (iParam0 == hash("avenger") || iParam0 == hash("thruster")) {
		return "MAMMOTH";
	}
	if (iParam0 == hash("deluxo")) {
		return "IMPONTE";
	}
	if (iParam0 == hash("stromberg") || iParam0 == hash("pariah")) {
		return "OCELOT";
	}
	if (iParam0 == hash("hermes")) {
		return "ALBANY";
	}
	if ((iParam0 == hash("sentinel3") || iParam0 == hash("sc1")) ||
		iParam0 == hash("revolter")) {
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
	}
	if (iParam0 == hash("savestra")) {
		return "ANNIS";
	}
	if (iParam0 == hash("yosemite")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("raiden")) {
		return "COIL";
	}
	if ((iParam0 == hash("neon") || iParam0 == hash("comet4")) ||
		iParam0 == hash("comet5")) {
		return "PFISTER";
	}
	if (iParam0 == hash("streiter")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == hash("kamacho")) {
		return "CANIS";
	}
	if (iParam0 == hash("gt500")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if (iParam0 == hash("viseris")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("barrage")) {
		return "HVY";
	}
	if ((iParam0 == hash("autarch") || iParam0 == hash("tyrant")) ||
		iParam0 == hash("entity2")) {
		return "OVERFLOD";
	}
	if (iParam0 == hash("issi3")) {
		return "WEENY";
	}
	if ((((iParam0 == hash("gb200") || iParam0 == hash("ellie")) ||
		  iParam0 == hash("flashgt")) ||
		 iParam0 == hash("caracara")) ||
		iParam0 == hash("dominator3")) {
		return "VAPID";
	}
	if (iParam0 == hash("fagaloa")) {
		return "VULCAR";
	}
	if (iParam0 == hash("michelli")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("hotring")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("tezeract")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("jester3")) {
		return "DINKA";
	}
	if (iParam0 == hash("taipan")) {
		return "CHEVAL";
	}
	if (iParam0 == hash("cheburek")) {
		return "RUNE";
	}
	if (iParam0 == hash("swinger")) {
		return "OCELOT";
	}
	if (iParam0 == hash("freecrawler")) {
		return "CANIS";
	}
	if (iParam0 == hash("mule4")) {
		return "MAIBATSU";
	}
	if (iParam0 == hash("pounder2")) {
		return "MTL";
	}
	if (iParam0 == hash("speedo4")) {
		return "VAPID";
	}
	if (iParam0 == hash("patriot2")) {
		return "MAMMOTH";
	}
	if (iParam0 == hash("oppressor2")) {
		return "PEGASSI";
	}
	if (iParam0 == hash("stafford")) {
		return "ENUS";
	}
	if (iParam0 == hash("menacer")) {
		return "HVY";
	}
	if (iParam0 == hash("scramjet")) {
		return "DECLASSE";
	}
	if ((iParam0 == hash("monster3") || iParam0 == hash("monster4")) ||
		iParam0 == hash("monster5")) {
		return "BRAVADO";
	}
	if ((iParam0 == hash("scarab") || iParam0 == hash("scarab2")) ||
		iParam0 == hash("scarab3")) {
		return "HVY";
	}
	if ((iParam0 == hash("issi4") || iParam0 == hash("issi5")) ||
		iParam0 == hash("issi6")) {
		return "WEENY";
	}
	if (iParam0 == hash("toros")) {
		return "PEGASSI";
	}
	if ((((((((((iParam0 == hash("clique") || iParam0 == hash("imperator")) ||
				iParam0 == hash("imperator2")) ||
			   iParam0 == hash("imperator3")) ||
			  iParam0 == hash("dominator4")) ||
			 iParam0 == hash("dominator5")) ||
			iParam0 == hash("dominator6")) ||
		   iParam0 == hash("slamvan4")) ||
		  iParam0 == hash("slamvan5")) ||
		 iParam0 == hash("slamvan6")) ||
		iParam0 == hash("SLAMVAN2")) {
		return "VAPID";
	}
	if (iParam0 == hash("deveste")) {
		if (bParam1) {
			return "PRINCIPL";
		} else {
			return "PRINCIPE";
		}
	}
	if ((((((((iParam0 == hash("impaler") || iParam0 == hash("impaler2")) ||
			  iParam0 == hash("impaler3")) ||
			 iParam0 == hash("impaler4")) ||
			iParam0 == hash("vamos")) ||
		   iParam0 == hash("tulip")) ||
		  iParam0 == hash("brutus")) ||
		 iParam0 == hash("brutus2")) ||
		iParam0 == hash("brutus3")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("deviant")) {
		return "SCHYSTER";
	}
	if (iParam0 == hash("schlagen")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == hash("italigto")) {
		if (bParam1) {
			return "GROTTI";
		} else {
			return "Grotti_2";
		}
	}
	if ((iParam0 == hash("cerberus") || iParam0 == hash("cerberus2")) ||
		iParam0 == hash("cerberus3")) {
		return "MTL";
	}
	if ((iParam0 == hash("deathbike") || iParam0 == hash("deathbike2")) ||
		iParam0 == hash("deathbike3")) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if ((iParam0 == hash("bruiser") || iParam0 == hash("bruiser2")) ||
		iParam0 == hash("bruiser3")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if ((iParam0 == hash("zr380") || iParam0 == hash("zr3802")) ||
		iParam0 == hash("zr3803")) {
		return "ANNIS";
	}
	if (iParam0 == hash("caracara2") || iParam0 == hash("peyote2")) {
		return "VAPID";
	}
	if (iParam0 == hash("drafter")) {
		return "OBEY";
	}
	if (iParam0 == hash("Dynasty") || iParam0 == hash("issi7")) {
		return "WEENY";
	}
	if (iParam0 == hash("gauntlet3") || iParam0 == hash("gauntlet4")) {
		return "BRAVADO";
	}
	if (iParam0 == hash("hellion") || iParam0 == hash("s80")) {
		return "ANNIS";
	}
	if (iParam0 == hash("krieger")) {
		if (bParam1) {
			return "BENEFAC";
		} else {
			return "BENEFACTOR";
		}
	}
	if (iParam0 == hash("locust") || iParam0 == hash("jugular")) {
		return "OCELOT";
	}
	if (iParam0 == hash("nebula")) {
		return "VULCAR";
	}
	if (iParam0 == hash("Novak")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("paragon") || iParam0 == hash("paragon2")) {
		return "ENUS";
	}
	if (iParam0 == hash("thrax")) {
		return "TRUFFADE";
	}
	if (iParam0 == hash("zion3")) {
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
	}
	if (iParam0 == hash("emerus")) {
		return "PROGEN";
	}
	if (iParam0 == hash("neo")) {
		return "VYSSER";
	}
	if (iParam0 == hash("rrocket")) {
		if (bParam1) {
			return "WESTERN";
		} else {
			return "WESTERNMOTORCYCLE";
		}
	}
	if (iParam0 == hash("BURRITO") || iParam0 == hash("burrito2")) {
		return "DECLASSE";
	}
	if (iParam0 == hash("formula")) {
		return "PROGEN";
	}
	if (iParam0 == hash("everon")) {
		return "KARIN";
	}
	if (iParam0 == hash("imorgon")) {
		return "OVERFLOD";
	}
	if (iParam0 == hash("kanjo")) {
		return "DINKA";
	}
	if (iParam0 == hash("komoda")) {
		if (bParam1) {
			return "LAMPADA";
		} else {
			return "LAMPADATI";
		}
	}
	if (iParam0 == hash("rebla")) {
		if (bParam1) {
			return "UBERMACH";
		} else {
			return "UBERMACHT";
		}
	}
	if (iParam0 == hash("Sugoi")) {
		return "DINKA";
	}
	if (iParam0 == hash("sultan2")) {
		return "KARIN";
	}
	if (iParam0 == hash("vstr")) {
		return "ALBANY";
	}
	if (iParam0 == hash("zhaba")) {
		return "RUNE";
	}
	if (!bParam1) {
		if (hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("GALLIVAN")) {
			return "GALIVANTER";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("BENEFAC")) {
			return "BENEFACTOR";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("UBERMACH")) {
			return "UBERMACHT";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("DEWBAUCH")) {
			return "DEWBAUCHEE";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("JACKSHP")) {
			return "JACKSHEEPE";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("GROTTI")) {
			return "Grotti_2";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("INVERTO")) {
			return "Invetero";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("LAMPADA")) {
			return "LAMPADATI";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("DUNDREAR")) {
			return "DUNDREARY";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("ZIRCONIU")) {
			return "ZIRCONIUM";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("WESTERN")) {
			return "WESTERNMOTORCYCLE";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("PRINCIPL")) {
			return "PRINCIPE";
		} else if (
			hash(ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0)) ==
			hash("EMPEROR")) {
			return "EMPORER";
		} else {
			return ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0);
		}
	} else {
		return ntv::VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(iParam0);
	}
	return "";
}

} // namespace

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

} // namespace nob
