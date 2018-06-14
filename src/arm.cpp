#include <nob/arm.hpp>

#include <unordered_map>

#include <cstring>

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
				{"AMMO_PETROLCAN", "WEAPON_PETROLCAN"}, {"AMMO_FIREEXTINGUISHER", "WEAPON_FIREEXTINGUISHER"},
				{"AMMO_BALL", "WEAPON_BALL"}
			};
			auto it = map.find(amm_typ);
			if (it == map.end()) {
				return nullptr;
			}
			return it->second;
		}

		static std::vector<hasher> _null_weapons;

		const std::vector<hasher> &weapons_from_group(const hasher &group) {
			static const std::unordered_map<hasher, std::vector<hasher>> map = ([]()->std::unordered_map<hasher, std::vector<hasher>> {
				std::unordered_map<hasher, std::vector<hasher>> r;
				for (auto &wpn : weapons) {
					r[weapon_group(wpn)].emplace_back(wpn);
				}
				return r;
			})();
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
				return display_info_t{hr.src_str() && strlen(hr.src_str()) ? hr.src_str() : "???", "???"};
			}
			return it->second;
		}
	}
}
