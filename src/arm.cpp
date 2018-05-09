#include <nob/arm.hpp>

#include <unordered_map>

namespace nob {
	namespace arm {
		hasher weapon_from_ammo_type(const hasher &amm_typ) {
			static const std::unordered_map<hasher, hasher> map {
				{"AMMO_PISTOL", "WEAPON_PISTOL"}, {"AMMO_STUNGUN", "WEAPON_STUNGUN"}, {"AMMO_FLAREGUN", "WEAPON_FLAREGUN"},

				{"AMMO_SMG", "WEAPON_SMG"}, {"AMMO_MG", "WEAPON_MG"},

				{"AMMO_RIFLE", "WEAPON_ASSAULTRIFLE"},

				{"AMMO_SNIPER", "WEAPON_SNIPERRIFLE"},

				{"AMMO_SHOTGUN", "WEAPON_PUMPSHOTGUN"},

				{"AMMO_RPG", "WEAPON_RPG"}, {"AMMO_HOMINGLAUNCHER", "WEAPON_HOMINGLAUNCHER"}, {"AMMO_FIREWORK", "WEAPON_FIREWORK"},
				{"AMMO_MINIGUN", "WEAPON_MINIGUN"}, {"AMMO_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER"}, {"AMMO_RAILGUN", "WEAPON_RAILGUN"},

				{"AMMO_GRENADE", "WEAPON_GRENADE"}, {"AMMO_PIPEBOMB", "WEAPON_PIPEBOMB"}, {"AMMO_STICKYBOMB", "WEAPON_STICKYBOMB"},
				{"AMMO_PROXMINE", "WEAPON_PROXMINE"}, {"AMMO_SMOKEGRENADE", "WEAPON_SMOKEGRENADE"}, {"AMMO_BZGAS", "WEAPON_BZGAS"},
				{"AMMO_MOLOTOV", "WEAPON_MOLOTOV"}, {"AMMO_FLARE", "WEAPON_FLARE"}, {"AMMO_SNOWBALL", "WEAPON_SNOWBALL"},
				{"AMMO_PETROLCAN", "WEAPON_PETROLCAN"}, {"AMMO_FIREEXTINGUISHER", "WEAPON_FIREEXTINGUISHER"}
			};
			auto it = map.find(amm_typ);
			if (it == map.end()) {
				return nullptr;
			}
			return it->second;
		}

		static std::vector<hasher> _null_weapons;

		const std::vector<hasher> &weapons_from_group(const hasher &group) {
			static const std::unordered_map<hasher, std::vector<hasher>> map {
				{"GROUP_PISTOL", {
					"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_HEAVYPISTOL",
					"WEAPON_VINTAGEPISTOL", "WEAPON_SNSPISTOL", "WEAPON_MARKSMANPISTOL", "WEAPON_MACHINEPISTOL",
					"WEAPON_REVOLVER", "WEAPON_FLAREGUN"
				}},
				{"GROUP_STUNGUN", {
					"WEAPON_STUNGUN"
				}},

				{"GROUP_SMG", {
					"WEAPON_SMG", "WEAPON_MICROSMG", "WEAPON_ASSAULTSMG", "WEAPON_MINISMG", "WEAPON_COMBATPDW"
				}},
				{"GROUP_MG", {
					"WEAPON_MG", "WEAPON_COMBATMG", "WEAPON_GUSENBERG"
				}},

				{"GROUP_RIFLE", {
					"WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_BULLPUPRIFLE",
					"WEAPON_COMPACTRIFLE", "WEAPON_SPECIALCARBINE"
				}},

				{"GROUP_SNIPER", {
					"WEAPON_SNIPERRIFLE", "WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSNIPER"
				}},

				{"GROUP_UNARMED", {
					"WEAPON_UNARMED"
				}},
				{"GROUP_MELEE", {
					"WEAPON_CROWBAR", "WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT",
					"WEAPON_GOLFCLUB", "WEAPON_DAGGER", "WEAPON_HATCHET", "WEAPON_KNUCKLE", "WEAPON_MACHETE",
					"WEAPON_SWITCHBLADE", "WEAPON_BATTLEAXE", "WEAPON_POOLCUE", "WEAPON_WRENCH", "WEAPON_FLASHLIGHT"
				}},

				{"GROUP_SHOTGUN", {
					"WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
					"WEAPON_HEAVYSHOTGUN", "WEAPON_DBSHOTGUN", "WEAPON_AUTOSHOTGUN", "WEAPON_MUSKET"
				}},

				{"GROUP_HEAVY", {
					"WEAPON_RPG", "WEAPON_HOMINGLAUNCHER", "WEAPON_FIREWORK", "WEAPON_MINIGUN",
					"WEAPON_GRENADELAUNCHER", "WEAPON_COMPACTLAUNCHER", "WEAPON_RAILGUN"
				}},

				{"GROUP_THROWN", {
					"WEAPON_GRENADE", "WEAPON_PIPEBOMB", "WEAPON_STICKYBOMB", "WEAPON_PROXMINE", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
					"WEAPON_MOLOTOV", "WEAPON_FLARE", "WEAPON_SNOWBALL"
				}},
				{"GROUP_PETROLCAN", {
					"WEAPON_PETROLCAN"
				}},
				{"GROUP_FIREEXTINGUISHER", {
					"WEAPON_FIREEXTINGUISHER"
				}}
			};
			auto it = map.find(group);
			if (it == map.end()) {
				return _null_weapons;
			}
			return it->second;
		}

		display_info_t display_info(const hasher &hr) {
			static std::unordered_map<hash_t, display_info_t> map {
				#include "arm/display_info_map.inc"
			};
			auto it = map.find(hr.hash());
			if (it == map.end()) {
				return display_info_t{hr.src_str() ? hr.src_str() : "???", "???"};
			}
			return it->second;
		}
	}
}
