#pragma once

#include "ntv.hpp"
#include "hash.hpp"

#include <cstdint>

namespace nob {
	namespace weapon {
		_NOB_STATIC_HASH(unarmed, weapon_unarmed);
		_NOB_STATIC_HASH(knife, weapon_knife);
		_NOB_STATIC_HASH(nightstick, weapon_nightstick);
		_NOB_STATIC_HASH(hammer, weapon_hammer);
		_NOB_STATIC_HASH(bat, weapon_bat);
		_NOB_STATIC_HASH(golf_club, weapon_golfclub);
		_NOB_STATIC_HASH(crowbar, weapon_crowbar);
		_NOB_STATIC_HASH(pistol, weapon_pistol);
		_NOB_STATIC_HASH(combat_pistol, weapon_combatpistol);
		_NOB_STATIC_HASH(ap_pistol, weapon_appistol);
		_NOB_STATIC_HASH(pistol_50, weapon_pistol50);
		_NOB_STATIC_HASH(micro_smg, weapon_microsmg);
		_NOB_STATIC_HASH(smg, weapon_smg);
		_NOB_STATIC_HASH(assault_smg, weapon_assaultsmg);
		_NOB_STATIC_HASH(combat_pdw, weapon_combatpdw);
		_NOB_STATIC_HASH(assault_rifle, weapon_assaultrifle);
		_NOB_STATIC_HASH(carbine_rifle, weapon_carbinerifle);
		_NOB_STATIC_HASH(advanced_rifle, weapon_advancedrifle);
		_NOB_STATIC_HASH(mg, weapon_mg);
		_NOB_STATIC_HASH(combat_mg, weapon_combatmg);
		_NOB_STATIC_HASH(pump_shotgun, weapon_pumpshotgun);
		_NOB_STATIC_HASH(sawn_off_shotgun, weapon_sawnoffshotgun);
		_NOB_STATIC_HASH(assault_shotgun, weapon_assaultshotgun);
		_NOB_STATIC_HASH(bullpup_shotgun, weapon_bullpupshotgun);
		_NOB_STATIC_HASH(stun_gun, weapon_stungun);
		_NOB_STATIC_HASH(sniper_rifle, weapon_sniperrifle);
		_NOB_STATIC_HASH(heavy_sniper, weapon_heavysniper);
		_NOB_STATIC_HASH(grenade_launcher, weapon_grenadelauncher);
		_NOB_STATIC_HASH(grenade_launcher_smoke, weapon_grenadelaunchersmoke);
		_NOB_STATIC_HASH(rpg, weapon_rpg);
		_NOB_STATIC_HASH(minigun, weapon_minigun);
		_NOB_STATIC_HASH(grenade, weapon_grenade);
		_NOB_STATIC_HASH(sticky_bomb, weapon_stickybomb);
		_NOB_STATIC_HASH(smoke_grenade, weapon_smokegrenade);
		_NOB_STATIC_HASH(bz_gas, weapon_bzgas);
		_NOB_STATIC_HASH(molotov, weapon_molotov);
		_NOB_STATIC_HASH(fire_extinguisher, weapon_fireextinguisher);
		_NOB_STATIC_HASH(petrol_can, weapon_petrolcan);
		_NOB_STATIC_HASH(sns_pistol, weapon_snspistol);
		_NOB_STATIC_HASH(special_carbine, weapon_specialcarbine);
		_NOB_STATIC_HASH(heavy_pistol, weapon_heavypistol);
		_NOB_STATIC_HASH(bullpup_rifle, weapon_bullpuprifle);
		_NOB_STATIC_HASH(homing_launcher, weapon_hominglauncher);
		_NOB_STATIC_HASH(proximity_mine, weapon_proximitymine);
		_NOB_STATIC_HASH(snowball, weapon_snowball);
		_NOB_STATIC_HASH(vintage_pistol, weapon_vintagepistol);
		_NOB_STATIC_HASH(dagger, weapon_dagger);
		_NOB_STATIC_HASH(firework, weapon_firework);
		_NOB_STATIC_HASH(musket, weapon_musket);
		_NOB_STATIC_HASH(marksman_rifle, weapon_marksmanrifle);
		_NOB_STATIC_HASH(heavyshotgun, weapon_heavyshotgun);
		_NOB_STATIC_HASH(gusenberg, weapon_gusenberg);
		_NOB_STATIC_HASH(hatchet, weapon_hatchet);
		_NOB_STATIC_HASH(railgun, weapon_railgun);

		#pragma pack(push, 1)
		struct attr_t {
			uint8_t
				damage,
				speed,
				capacity,
				accuracy,
				range;
		};
		#pragma pack(pop)

		inline attr_t get_attr(hash_t wpn) {
			attr_t attr;
			ntv::WEAPON::GET_WEAPON_HUD_STATS(wpn, reinterpret_cast<int *>(&attr));
			return attr;
		}
	}
}
