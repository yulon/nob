#pragma once

#include "base.hpp"
#include "consts.hpp"

namespace nob { namespace ntv {
namespace WEAPON { namespace {
lazy_func_t<void(Ped ped)> SET_PED_DROPS_WEAPON(0x6B7513D9966FBEC0);
lazy_func_t<int(Ped ped, Hash weaponHash, BOOL p2)>
	GET_MAX_AMMO_IN_CLIP(0xA38DCFFCEA8962FA);
lazy_func_t<void(Ped ped, Any ammoType, int ammo)>
	SET_PED_AMMO_BY_TYPE(0x5FD1E1F011E76D7E);
lazy_func_t<BOOL(Hash weaponHash)> HAS_WEAPON_ASSET_LOADED(0x36E353271F0E90EE);
lazy_func_t<BOOL(Ped ped)> SET_WEAPON_SMOKEGRENADE_ASSIGNED(0x4B7620C47217126C);
lazy_func_t<Hash(Hash componentHash)>
	GET_WEAPON_COMPONENT_TYPE_MODEL(0x0DB57B41EC1DB083);
lazy_func_t<void(Ped ped, Hash weaponHash, int ammo)>
	ADD_AMMO_TO_PED(0x78F0424C34306220);
lazy_func_t<void(Hash weaponHash, BOOL p1)>
	REMOVE_ALL_PROJECTILES_OF_TYPE(0xFC52E0F37E446528);
lazy_func_t<BOOL(Ped ped)> _PED_SKIP_NEXT_RELOADING(0x8C0D57EA686FAD87);
lazy_func_t<void(BOOL toggle)> ENABLE_LASER_SIGHT_RENDERING(0xC8B46D7727D864AA);
lazy_func_t<void(Ped ped, Hash weaponHash, BOOL equipNow)>
	SET_CURRENT_PED_WEAPON(0xADF692B254977C0C);
lazy_func_t<BOOL(Ped ped, Hash weaponHash, int ammo)>
	SET_AMMO_IN_CLIP(0xDCD2A934D65CB497);
lazy_func_t<int(Ped ped, Any ammoType)>
	GET_PED_AMMO_BY_TYPE(0x39D22031557946C1);
lazy_func_t<BOOL(Ped ped, Hash weaponHash, Hash componentHash)>
	IS_PED_WEAPON_COMPONENT_ACTIVE(0x0D78DE0572D3969E);
lazy_func_t<BOOL(Hash weaponHash, Any *outData)>
	GET_WEAPON_HUD_STATS(0xD92C739EE34C9EBA);
lazy_func_t<int(Hash weaponHash)> GET_WEAPON_CLIP_SIZE(0x583BE370B1EC6EB4);
lazy_func_t<void(Ped ped, Hash weaponHash, int ammo)>
	SET_PED_AMMO(0x14E56BC5B5DB6A19);
lazy_func_t<void(Ped ped, BOOL visible, BOOL deselectWeapon, BOOL p3, BOOL p4)>
	SET_PED_CURRENT_WEAPON_VISIBLE(0x0725A4CCFDED9A70);
lazy_func_t<float(Ped ped)>
	_GET_LOCKON_RANGE_OF_CURRENT_PED_WEAPON(0x840F03E9041E2C9C);
lazy_func_t<void(Any p0, Any p1)>
	REMOVE_WEAPON_COMPONENT_FROM_WEAPON_OBJECT(0xF7D82B0D66777611);
lazy_func_t<void(Object weaponObject, Ped ped)>
	GIVE_WEAPON_OBJECT_TO_PED(0xB1FA61371AF7C4B7);
lazy_func_t<int(Hash weaponHash)> GET_WEAPON_TINT_COUNT(0x5DCF6C5CAB2E9BF7);
lazy_func_t<void(Ped ped, Hash weaponHash)>
	REMOVE_WEAPON_FROM_PED(0x4899CB088EDF59B8);
lazy_func_t<void(Ped ped)> CLEAR_PED_LAST_WEAPON_DAMAGE(0x0E98F88A24C5F4B8);
lazy_func_t<void(Ped ped, Hash weaponHash, int ammoCount, BOOL equipNow)>
	GIVE_DELAYED_WEAPON_TO_PED(0xB282DC6EBD803C75);
lazy_func_t<Object(Ped ped, BOOL p1)>
	GET_WEAPON_OBJECT_FROM_PED(0xCAE1DC9A0E22A16D);
lazy_func_t<float(Any p0, Any p1)> _0x3133B907D8B32053(0x3133B907D8B32053);
lazy_func_t<Hash(Hash weaponHash)> GET_WEAPONTYPE_SLOT(0x4215460B9B8B7FA0);
lazy_func_t<BOOL(Ped ped, int p1)> IS_PED_ARMED(0x475768A975D5AD17);
lazy_func_t<BOOL(Ped ped, Hash weaponHash, int weaponType)>
	HAS_PED_BEEN_DAMAGED_BY_WEAPON(0x2D343D2219CD027A);
lazy_func_t<BOOL(Ped ped, Hash weaponHash, int *ammo)>
	GET_MAX_AMMO(0xDC16122C7A20C933);
lazy_func_t<void(Ped ped, Hash weaponHash, Hash componentHash)>
	GIVE_WEAPON_COMPONENT_TO_PED(0xD966D51AA5B28BB9);
lazy_func_t<BOOL(Ped ped)> IS_PED_CURRENT_WEAPON_SILENCED(0x65F0C5AE05943EC7);
lazy_func_t<BOOL(Ped ped, Hash *weaponHash)>
	GET_CURRENT_PED_VEHICLE_WEAPON(0x1017582BCD3832DC);
lazy_func_t<void(Ped ped, BOOL p1)> REMOVE_ALL_PED_WEAPONS(0xF25DF915FA38C5F3);
lazy_func_t<
	void(Ped ped, Hash weaponHash, int ammoCount, BOOL isHidden, BOOL equipNow)>
	GIVE_WEAPON_TO_PED(0xBF0FD6E56C964FCB);
lazy_func_t<BOOL(Entity entity, Hash weaponHash, int weaponType)>
	HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(0x131D401334815E94);
lazy_func_t<void(Hash weaponHash, int p1, int p2)>
	REQUEST_WEAPON_ASSET(0x5443438F033E29C3);
lazy_func_t<void(Hash weaponHash)> REMOVE_WEAPON_ASSET(0xAA08EF13F341C8FC);
lazy_func_t<void(Ped ped, float xBias, float yBias)>
	SET_PED_CHANCE_OF_FIRING_BLANKS(0x8378627201D5497D);
lazy_func_t<BOOL(Ped ped, Hash weaponHash)>
	SET_CURRENT_PED_VEHICLE_WEAPON(0x75C55983C2C39DAA);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_INFINITE_AMMO_CLIP(0x183DADC6AA953186);
lazy_func_t<void(Ped ped, Hash gadgetHash, BOOL p2)>
	SET_PED_GADGET(0xD0D7B1E680ED4A1A);
lazy_func_t<BOOL(Ped ped, Hash weaponHash, Hash componentHash)>
	HAS_PED_GOT_WEAPON_COMPONENT(0xC593212475FAE340);
lazy_func_t<int(Object weapon)>
	GET_WEAPON_OBJECT_TINT_INDEX(0xCD183314F7CD2E57);
lazy_func_t<void(Ped ped, BOOL toggle, Hash weaponHash)>
	SET_PED_INFINITE_AMMO(0x3EDCB0505123623B);
lazy_func_t<BOOL(Ped ped, Vector3 *coords)>
	GET_PED_LAST_WEAPON_IMPACT_COORD(0x6C4D0409BA1A2BC2);
lazy_func_t<Hash(Ped ped, Hash weaponSlot)>
	GET_PED_WEAPONTYPE_IN_SLOT(0xEFFED78E9011134D);
lazy_func_t<float(Ped ped)>
	GET_MAX_RANGE_OF_CURRENT_PED_WEAPON(0x814C9D19DFD69679);
lazy_func_t<BOOL(Object weapon, Hash addonHash)>
	HAS_WEAPON_GOT_WEAPON_COMPONENT(0x76A18844E743BF91);
lazy_func_t<BOOL(Hash weaponHash, Hash componentHash)>
	DOES_WEAPON_TAKE_WEAPON_COMPONENT(0x5CEE3DF569CECAB0);
lazy_func_t<BOOL(Hash weaponHash)>
	CAN_USE_WEAPON_ON_PARACHUTE(0xBC7BE5ABC0879F74);
lazy_func_t<Hash(Ped ped, BOOL p1)> GET_BEST_PED_WEAPON(0x8483E98E8B888AE2);
lazy_func_t<BOOL(Ped ped, Hash weaponHash, BOOL p2)>
	HAS_PED_GOT_WEAPON(0x8DECB02F88F428BC);
lazy_func_t<void(Any ammoType, int ammo)>
	SET_PED_AMMO_TO_DROP(0xA4EFEF9440A5B0EF);
lazy_func_t<void(Entity weaponObject)>
	REQUEST_WEAPON_HIGH_DETAIL_MODEL(0x48164DBB970AC3F0);
lazy_func_t<BOOL(Ped ped, Hash *weaponHash, BOOL p2)>
	GET_CURRENT_PED_WEAPON(0x3A87E44BB9A01D54);
lazy_func_t<Entity(Ped ped)>
	GET_CURRENT_PED_WEAPON_ENTITY_INDEX(0x3B390A939AF0B5FC);
lazy_func_t<BOOL(Ped driver, Vehicle vehicle, Hash weaponHash, Any p3)>
	HAS_VEHICLE_GOT_PROJECTILE_ATTACHED(0x717C8481234E3B88);
lazy_func_t<Entity(Ped ped, float p1)> _0xB4C8D77C80C0421E(0xB4C8D77C80C0421E);
lazy_func_t<int(Ped ped, Hash weaponhash)>
	GET_AMMO_IN_PED_WEAPON(0x015A522136D7F951);
lazy_func_t<void(Entity entity)>
	CLEAR_ENTITY_LAST_WEAPON_DAMAGE(0xAC678E40BE7C74D2);
lazy_func_t<Hash(Ped ped)> GET_SELECTED_PED_WEAPON(0x0A6DB4965674D243);
lazy_func_t<Object(
	Hash weaponHash,
	int ammoCount,
	float x,
	float y,
	float z,
	BOOL showWorldModel,
	float heading,
	Any p7)>
	CREATE_WEAPON_OBJECT(0x9541D3CF0D398F36);
lazy_func_t<void(Ped ped, Hash weaponHash, int tintIndex)>
	SET_PED_WEAPON_TINT_INDEX(0x50969B9B89ED5738);
lazy_func_t<void(Object weapon, int tintIndex)>
	SET_WEAPON_OBJECT_TINT_INDEX(0xF827589017D4E4A9);
lazy_func_t<BOOL(Hash componentHash, int *outData)>
	GET_WEAPON_COMPONENT_HUD_STATS(0xB3CAF387AE12E9F8);
lazy_func_t<void(Ped ped)> _0xE4DCEC7FD5B739A5(0xE4DCEC7FD5B739A5);
lazy_func_t<BOOL(Hash weaponHash)> IS_WEAPON_VALID(0x937C71165CF334B3);
lazy_func_t<void(
	Ped ped,
	Hash weaponHash,
	float xOffset,
	float yOffset,
	float zOffset,
	int ammoCount)>
	SET_PED_DROPS_INVENTORY_WEAPON(0x208A1888007FC0E6);
lazy_func_t<BOOL(Ped ped)> MAKE_PED_RELOAD(0x20AE33F3AC9C0033);
lazy_func_t<void(Object weaponObject, Hash addonHash)>
	GIVE_WEAPON_COMPONENT_TO_WEAPON_OBJECT(0x33E179436C0B31DB);
lazy_func_t<void(float p0)> _0xE620FD3512A04F18(0xE620FD3512A04F18);
lazy_func_t<Hash(Ped ped, Hash weaponHash)>
	GET_PED_AMMO_TYPE_FROM_WEAPON(0x7FEAD38B326B9F74);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_DROPS_WEAPONS_WHEN_DEAD(0x476AE72C1D19D1A8);
lazy_func_t<BOOL(Ped ped, Hash gadgetHash)>
	GET_IS_PED_GADGET_EQUIPPED(0xF731332072F5156C);
lazy_func_t<void(Ped ped, Hash weaponHash, BOOL p2)>
	EXPLODE_PROJECTILES(0xFC4BD125DE7611E4);
lazy_func_t<int(Ped ped, Hash weaponHash)>
	GET_PED_WEAPON_TINT_INDEX(0x2B9EEDC07BD06B9F);
lazy_func_t<Any(float distance)>
	SET_FLASH_LIGHT_FADE_DISTANCE(0xCEA66DAD478CD39B);
lazy_func_t<Hash(Hash weaponHash)> GET_WEAPONTYPE_MODEL(0xF46CDC33180FDA94);
lazy_func_t<void(Ped ped, BOOL toggle)>
	HIDE_PED_WEAPON_FOR_SCRIPTED_CUTSCENE(0x6F6981D2253C208F);
lazy_func_t<int(Hash weaponHash)> GET_WEAPON_DAMAGE_TYPE(0x3BE0BB12D25FB305);
lazy_func_t<BOOL(Ped ped)> IS_PED_WEAPON_READY_TO_SHOOT(0xB80CA294F2F26749);
lazy_func_t<BOOL(Ped ped, Hash weaponHash, int *ammo)>
	GET_AMMO_IN_CLIP(0x2E1202248937775C);
lazy_func_t<void(Ped ped, Hash animStyle)>
	SET_WEAPON_ANIMATION_OVERRIDE(0x1055AC3A667F09D9);
lazy_func_t<Hash(Hash weaponHash)> GET_WEAPONTYPE_GROUP(0xC3287EE3050FB74C);
lazy_func_t<void(Ped ped, Hash weaponHash, Hash componentHash)>
	REMOVE_WEAPON_COMPONENT_FROM_PED(0x1E8BE90C74FB4C09);
}} // namespace WEAPON::
namespace SOCIALCLUB { namespace {
lazy_func_t<BOOL(int *p0)> _0x225798743970412B(0x225798743970412B);
lazy_func_t<BOOL(Any p0, Any *p1)>
	SC_INBOX_MESSAGE_GET_UGCDATA(0x69D82604A1A5A254);
lazy_func_t<void(Any *p0, Any p1)> _0x44ACA259D67651DB(0x44ACA259D67651DB);
lazy_func_t<Any(Any p0)> _0x07C61676E5BB52CD(0x07C61676E5BB52CD);
lazy_func_t<Any(Any *p0)> _0x4A7D6E727F941747(0x4A7D6E727F941747);
lazy_func_t<BOOL(int p0, const char *p1, Any *p2)>
	_0x8CC469AB4D349B7C(0x8CC469AB4D349B7C);
lazy_func_t<BOOL(int p0, const char *context, int *out)>
	SC_INBOX_MESSAGE_GET_DATA_INT(0xA00EFE4082C4056E);
lazy_func_t<void(int offset, int limit)>
	_SC_INBOX_GET_EMAILS(0x040ADDCBAFA1018A);
lazy_func_t<BOOL(const char *p0)> _0x8416FE4E4629D7D7(0x8416FE4E4629D7D7);
lazy_func_t<int(Any p0)> _0x930DE22F07B1CCE3(0x930DE22F07B1CCE3);
lazy_func_t<BOOL(int p0, Any *p1)> _0x4737980E8A283806(0x4737980E8A283806);
lazy_func_t<BOOL(const char *p0, int *p1)>
	_0x92DA6E70EF249BD1(0x92DA6E70EF249BD1);
lazy_func_t<BOOL(Any *p0, Any *p1, Any *p2)>
	_0x1989C6E6F67E76A8(0x1989C6E6F67E76A8);
lazy_func_t<BOOL(int p0, const char *p1, Any *p2)>
	_0x699E4A5C8C893A18(0x699E4A5C8C893A18);
lazy_func_t<Hash(int p0)> _SC_INBOX_MESSAGE_INIT(0xBB8EA16ECBC976C4);
lazy_func_t<BOOL(int p0)> _SC_INBOX_MESSAGE_POP(0x2C015348CF19CA1D);
lazy_func_t<BOOL(Any p0, Any *p1)> _0x287F1F75D2803595(0x287F1F75D2803595);
lazy_func_t<BOOL(Any p0)> _0xF22CA0FD74B80E7A(0xF22CA0FD74B80E7A);
lazy_func_t<BOOL(Any *p0, Any *p1, Any *p2)>
	_0xD0EE05FE193646EA(0xD0EE05FE193646EA);
lazy_func_t<int()> _GET_TOTAL_SC_INBOX_IDS(0x03A93FF1A2CA0864);
lazy_func_t<BOOL(const char *playerName)>
	_0x6AFD2CD753FEEF83(0x6AFD2CD753FEEF83);
lazy_func_t<Any(Any p0, Any p1)> _0x1D4446A62D35B0D0(0x1D4446A62D35B0D0);
lazy_func_t<BOOL(Any p0, float p1)> _0x487912FD248EFDDF(0x487912FD248EFDDF);
lazy_func_t<BOOL(Any p0, Any p1)> _0xFE4C1D0D3B9CC17E(0xFE4C1D0D3B9CC17E);
lazy_func_t<BOOL(int p0)> _IS_SC_INBOX_VALID(0x93028F1DB42BFD08);
lazy_func_t<BOOL(const char *p0, int *p1)>
	_0xF6BAAAF762E1BF40(0xF6BAAAF762E1BF40);
lazy_func_t<Any(Any p0)> _0x700569DBA175A77C(0x700569DBA175A77C);
lazy_func_t<void(int *networkHandle)> _0xDA024BDBD600F44A(0xDA024BDBD600F44A);
lazy_func_t<Any()> _0x16DA8172459434AA(0x16DA8172459434AA);
lazy_func_t<Any(Any p0)> _0x9237E334F6E43156(0x9237E334F6E43156);
lazy_func_t<Any()> _0xD8122C407663B995(0xD8122C407663B995);
lazy_func_t<Entity()> _SC_GET_NICKNAME(0x198D161F458ECC7F);
lazy_func_t<BOOL(Any p0, int *p1)> _0x87E0052F08BD64E6(0x87E0052F08BD64E6);
lazy_func_t<void(const char *p0)> _0x116FB94DC4B79F17(0x116FB94DC4B79F17);
lazy_func_t<Any()> _0xDF649C4E9AFDD788(0xDF649C4E9AFDD788);
lazy_func_t<BOOL(int taskHandle)>
	_SC_HAS_CHECK_STRING_TASK_COMPLETED(0x1753344C770358AE);
lazy_func_t<Any(Any p0, Any p1)> _0x2E89990DDFF670C3(0x2E89990DDFF670C3);
lazy_func_t<const char *(int p0)>
	_SC_INBOX_MESSAGE_GET_STRING(0xF3E31D16CBDCB304);
lazy_func_t<void()> SC_EMAIL_MESSAGE_CLEAR_RECIP_LIST(0x55DF6DB45179236E);
lazy_func_t<BOOL(Any p0, Any p1)> _0x1F1E9682483697C7(0x1F1E9682483697C7);
lazy_func_t<Any(Any p0)> _0x8147FFF6A718E1AD(0x8147FFF6A718E1AD);
lazy_func_t<void()> _0x675721C9F644D161(0x675721C9F644D161);
lazy_func_t<BOOL(int p0, const char *p1)>
	_SC_INBOX_MESSAGE_GET_DATA_BOOL(0xFFE5C16F402D851D);
lazy_func_t<Any()> _0xFF8F3A92B75ED67A(0xFF8F3A92B75ED67A);
lazy_func_t<BOOL()> _0x3001BEF2FECA3680(0x3001BEF2FECA3680);
lazy_func_t<Any(Any p0)> _0xD302E99EDF0449CF(0xD302E99EDF0449CF);
lazy_func_t<BOOL(Any p0)> _0x6BFB12CE158E3DD4(0x6BFB12CE158E3DD4);
lazy_func_t<BOOL(int p0)> _SC_INBOX_MESSAGE_PUSH(0x9A2C8064B6C1E41A);
lazy_func_t<void(BOOL p0)> _0xBFA0A56A817C6C7D(0xBFA0A56A817C6C7D);
lazy_func_t<Any()> _0xBC1CC91205EC8D6E(0xBC1CC91205EC8D6E);
lazy_func_t<BOOL(const char *string, int *taskHandle)>
	_SC_START_CHECK_STRING_TASK(0x75632C5ECD7ED843);
lazy_func_t<BOOL(Any *p0, int *p1)> _0x0F73393BAC7E6730(0x0F73393BAC7E6730);
lazy_func_t<BOOL(int p0)> _0x418DC16FAE452C1C(0x418DC16FAE452C1C);
lazy_func_t<BOOL(int p0, const char *context, const char *out)>
	SC_INBOX_MESSAGE_GET_DATA_STRING(0x7572EF42FC6A9B6D);
lazy_func_t<int(int taskHandle)>
	_SC_GET_CHECK_STRING_STATUS(0x82E4A58BABC15AE7);
lazy_func_t<Any(Any p0)> _0x85535ACF97FC0969(0x85535ACF97FC0969);
lazy_func_t<Any(Any p0)> _0x5C4EBFFA98BDB41C(0x5C4EBFFA98BDB41C);
lazy_func_t<BOOL(Any p0, Any *p1)> _0x19853B5B17D77BCA(0x19853B5B17D77BCA);
lazy_func_t<void(const char *p0)> _0xA68D3D229F4F3B06(0xA68D3D229F4F3B06);
lazy_func_t<void(Player *player)>
	SC_EMAIL_MESSAGE_PUSH_GAMER_TO_RECIP_LIST(0x2330C12A7A605D16);
}} // namespace SOCIALCLUB::
namespace GAMEPLAY { namespace {
lazy_func_t<void(float p0)> _0xF751B16FB32ABC1D(0xF751B16FB32ABC1D);
lazy_func_t<Any()> _0xDC9274A7EF6B2867(0xDC9274A7EF6B2867);
lazy_func_t<BOOL()> _0xD3D15555431AB793(0xD3D15555431AB793);
lazy_func_t<void(float p0)> _0x405591EC8FD9096D(0x405591EC8FD9096D);
lazy_func_t<BOOL()> IS_PS3_VERSION(0xCCA1072C29D096C2);
lazy_func_t<void(Any p0, BOOL p1)> _0xE6869BECDD8F2403(0xE6869BECDD8F2403);
lazy_func_t<void()> RESET_DISPATCH_IDEAL_SPAWN_DISTANCE(0x77A84429DD9F0A15);
lazy_func_t<void(float speed)> SET_WIND_SPEED(0xEE09ECEDBABE47FC);
lazy_func_t<void(float p0)> _0xC54A08C85AE4D410(0xC54A08C85AE4D410);
lazy_func_t<void(int *address, int offset)> SET_BIT(0x933D6A9EEC1BACD0);
lazy_func_t<void()> _0x7EC6F9A478A6A512(0x7EC6F9A478A6A512);
lazy_func_t<Any()> _0x2B5E102E4A42F2BF(0x2B5E102E4A42F2BF);
lazy_func_t<int(int value)> ABSI(0xF0D31AD191A74F87);
lazy_func_t<void(Hash hash, BOOL p1)> _REMOVE_STEALTH_KILL(0xA6A12939F16D85BE);
lazy_func_t<void(BOOL p0)> _0x65D2EBB47E1CEC21(0x65D2EBB47E1CEC21);
lazy_func_t<BOOL()> IS_STUNT_JUMP_MESSAGE_SHOWING(0x2272B0A1343129F4);
lazy_func_t<void(Any *p0, const char *name)>
	REGISTER_BOOL_TO_SAVE(0xC8F4131414C835A1);
lazy_func_t<void(Any *p0, int p1, const char *structName)>
	_START_SAVE_STRUCT(0xBF737600CDDBEADD);
lazy_func_t<void(BOOL toggle)>
	SET_FADE_IN_AFTER_DEATH_ARREST(0xDA66D2796BA33F12);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	BOOL p6,
	BOOL p7,
	BOOL p8,
	BOOL p9,
	BOOL p10,
	Any p11,
	BOOL p12)>
	IS_AREA_OCCUPIED(0xA61B4DF533DCB56E);
lazy_func_t<void(int p0)> DELETE_STUNT_JUMP(0xDC518000E39DAE1F);
lazy_func_t<int()> _0x996DD1E1E02F1008(0x996DD1E1E02F1008);
lazy_func_t<float(
	float x1, float y1, float z1, float x2, float y2, float z2, BOOL useZ)>
	GET_DISTANCE_BETWEEN_COORDS(0xF1B760881820C952);
lazy_func_t<void(const char *weatherType)>
	SET_WEATHER_TYPE_NOW(0x29B487C359E19889);
lazy_func_t<void(const char *p0)> _0x11B56FBBF7224868(0x11B56FBBF7224868);
lazy_func_t<void()> STOP_SAVE_DATA(0x74E20C9145FB66FD);
lazy_func_t<Any()> _0xABB2FA71C83A1B72(0xABB2FA71C83A1B72);
lazy_func_t<void()> _0x23227DF0B2115469(0x23227DF0B2115469);
lazy_func_t<BOOL(Any *p1, Any *p2, Any p3, BOOL p4)>
	_0xB335F761606DB47C(0xB335F761606DB47C);
lazy_func_t<void(Hash modelHash, Vector3 *minimum, Vector3 *maximum)>
	GET_MODEL_DIMENSIONS(0x03E8D3D5F549087A);
lazy_func_t<void(int fakeWantedLevel)>
	SET_FAKE_WANTED_LEVEL(0x1454F2448DE30163);
lazy_func_t<Any()> _0x3BBBD13E5041A79E(0x3BBBD13E5041A79E);
lazy_func_t<float(float p0)> TAN(0x632106CC96E82E91);
lazy_func_t<void(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	BOOL p7,
	BOOL p8,
	BOOL p9,
	BOOL p10,
	BOOL p11)>
	CLEAR_ANGLED_AREA_OF_VEHICLES(0x11DB3500F042A8AA);
lazy_func_t<
	int(const char *str1, const char *str2, BOOL matchCase, int maxLength)>
	COMPARE_STRINGS(0x1E34710ECD4AB0EB);
lazy_func_t<
	BOOL(float p0, float p1, float p2, float p3, float p4, float p5, BOOL p6)>
	IS_BULLET_IN_BOX(0xDE0F6D7450D37351);
lazy_func_t<BOOL(const char *string, int *outInteger)>
	STRING_TO_INT(0x5A5F40FE637EB584);
lazy_func_t<void(BOOL toggle)>
	SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(0xB98236CAAECEF897);
lazy_func_t<BOOL(int incidentId)> IS_INCIDENT_VALID(0xC8BC6461E629BEAA);
lazy_func_t<Any(Player player)> SET_FIRE_AMMO_THIS_FRAME(0x11879CDD803D30F4);
lazy_func_t<float(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	BOOL p9)>
	_0x7F8F6405F4777AF6(0x7F8F6405F4777AF6);
lazy_func_t<const char *()> GET_ONSCREEN_KEYBOARD_RESULT(0x8362B09B91893647);
lazy_func_t<
	Any(float p0, float p1, float p2, float p3, float p4, float p5, float p6)>
	_0x918C7B2D2FF3928B(0x918C7B2D2FF3928B);
lazy_func_t<void(const char *weatherType)>
	SET_WEATHER_TYPE_PERSIST(0x704983DF373B198F);
lazy_func_t<void(const char *weatherType, float time)>
	_SET_WEATHER_TYPE_OVER_TIME(0xFB5045B7C42B75BF);
lazy_func_t<void()> CLEAR_OVERRIDE_WEATHER(0x338D2E3477711050);
lazy_func_t<float(float x1, float y1, float x2, float y2)>
	GET_ANGLE_BETWEEN_2D_VECTORS(0x186FC4BE848E1C92);
lazy_func_t<void(float x, float y, float z, float heading)>
	_SET_CUSTOM_RESPAWN_POSITION(0x706B5EDCAA7FA663);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)> SET_SAVE_HOUSE(0x4F548CABEAE553BC);
lazy_func_t<Any()> _0xEB2104E905C6F2E9(0xEB2104E905C6F2E9);
lazy_func_t<void(int time)> SET_RANDOM_SEED(0x444D98F98C11F3EC);
lazy_func_t<void()> _0xC7DB36C24634F52B(0xC7DB36C24634F52B);
lazy_func_t<BOOL(
	Ped ped, Hash projHash, float radius, Vector3 *projPos, BOOL ownedByPlayer)>
	_GET_PROJECTILE_NEAR_PED_COORDS(0xDFB4138EEFED7B81);
lazy_func_t<float(float p0)> ASIN(0xC843060B5765DCE7);
lazy_func_t<void(BOOL unk)> SET_SAVE_MENU_ACTIVE(0xC9BF75D28165FF77);
lazy_func_t<BOOL(
	BOOL p0,
	float p1,
	float p2,
	float p3,
	float p4,
	BOOL p5,
	float p6,
	float p7)>
	OVERRIDE_SAVE_HOUSE(0x1162EA8AE9D24EEA);
lazy_func_t<void()> END_REPLAY_STATS(0xA23E821FBDF8A5F2);
lazy_func_t<void(Any p0)>
	REMOVE_DISPATCH_SPAWN_BLOCKING_AREA(0x264AC28B01B353A5);
lazy_func_t<void(BOOL p0)> _0x6F2135B6129620C1(0x6F2135B6129620C1);
lazy_func_t<int()> GET_GAME_TIMER(0x9CD27B0045628463);
lazy_func_t<void(
	float x,
	float y,
	float z,
	float radius,
	BOOL p4,
	BOOL p5,
	BOOL p6,
	BOOL p7)>
	_CLEAR_AREA_OF_EVERYTHING(0x957838AAF91BD12D);
lazy_func_t<void(BOOL toggle)> _0xB51B9AB9EF81868C(0xB51B9AB9EF81868C);
lazy_func_t<void(BOOL toggle)> _USE_FREEMODE_MAP_BEHAVIOR(0x9BAE5AD2508DF078);
lazy_func_t<void(float p0)> _0xB3E6360DDE733E82(0xB3E6360DDE733E82);
lazy_func_t<Any(Any p0)> _0x8098C8D6597AAE18(0x8098C8D6597AAE18);
lazy_func_t<void()> CLEAR_REPLAY_STATS(0x1B1AB132A16FDA55);
lazy_func_t<int()> GET_FAKE_WANTED_LEVEL(0x4C9296CBCD1B971E);
lazy_func_t<void(int *address, int offset)> CLEAR_BIT(0xE80492A9AC099A93);
lazy_func_t<Any()> GET_SNOW_LEVEL(0xC5868A966E5BE3AE);
lazy_func_t<void(BOOL toggle)> IGNORE_NEXT_RESTART(0x21FFB63D8C615361);
lazy_func_t<Any()> _0x6E04F06094C87047(0x6E04F06094C87047);
lazy_func_t<void(Any p0, float p1)>
	SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS(0x44F7CBC1BEB3327D);
lazy_func_t<void(Any *p0)> _0x31125FD509D9043F(0x31125FD509D9043F);
lazy_func_t<void(float x, float y, float z, float radius, BOOL isNetworkGame)>
	CLEAR_AREA_OF_PROJECTILES(0x0A1CB9094635D1A6);
lazy_func_t<int(int dispatchService)>
	_GET_NUMBER_OF_DISPATCHED_UNITS_FOR_PLAYER(0xEB4A0C2D56441717);
lazy_func_t<BOOL()> _0x684A41975F077262(0x684A41975F077262);
lazy_func_t<float(float dx, float dy)>
	GET_HEADING_FROM_VECTOR_2D(0x2FFB6B224F4B2926);
lazy_func_t<Vector3()> GET_WIND_DIRECTION(0x1F400FEF721170DA);
lazy_func_t<BOOL(int address, int offset)> IS_BIT_SET(0xA921AA820C25702F);
lazy_func_t<void(int flag)> _SET_UNK_MAP_FLAG(0xC5F0A8EBD3F361CE);
lazy_func_t<void(Ped ped, BOOL toggle, BOOL p2)>
	ENABLE_TENNIS_MODE(0x28A04B411933F8A6);
lazy_func_t<void(Player player)>
	SET_EXPLOSIVE_AMMO_THIS_FRAME(0xA66C71C98D5F2CFB);
lazy_func_t<void()> _0x437138B6A830166A(0x437138B6A830166A);
lazy_func_t<void()> CLEAR_WEATHER_TYPE_PERSIST(0xCCC39339BEF76CF5);
lazy_func_t<void(int policeIndex, BOOL toggle)>
	DISABLE_POLICE_RESTART(0x23285DED6EBD7EA3);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int damage,
	BOOL p7,
	Hash weaponHash,
	Ped ownerPed,
	BOOL isAudible,
	BOOL isInvisible,
	float speed)>
	SHOOT_SINGLE_BULLET_BETWEEN_COORDS(0x867654CBC7606F2C);
lazy_func_t<BOOL(
	Ped ped,
	Hash projHash,
	float radius,
	Vector3 *projPos,
	Entity *projEnt,
	BOOL ownedByPlayer)>
	_GET_PROJECTILE_NEAR_PED(0x82FDE6A57EE4EE44);
lazy_func_t<void(BOOL p0)> _0xD79185689F8FD5DF(0xD79185689F8FD5DF);
lazy_func_t<Any()> _0x4750FC27570311EC(0x4750FC27570311EC);
lazy_func_t<BOOL()> GET_MISSION_FLAG(0xA33CDCCDA663159E);
lazy_func_t<BOOL(Any p0)> _0x17DF68D720AA77F8(0x17DF68D720AA77F8);
lazy_func_t<Any()> _0x1B2366C3F2A5C8DF(0x1B2366C3F2A5C8DF);
lazy_func_t<void()> _CREATE_LIGHTNING_THUNDER(0xF6062E089251C898);
lazy_func_t<void(
	float X,
	float Y,
	float Z,
	float radius,
	BOOL p4,
	BOOL ignoreCopCars,
	BOOL ignoreObjects,
	BOOL p7)>
	CLEAR_AREA(0xA56F01F3765B93A0);
lazy_func_t<BOOL(float p0, float p1, float p2, float p3, BOOL p4)>
	IS_BULLET_IN_AREA(0x3F2023999AD51C1F);
lazy_func_t<BOOL(const char *string)> IS_STRING_NULL(0xF22B6C47C6EAB066);
lazy_func_t<Any(float p0, float p1, float p2, float p3)>
	_0x2D4259F1FEB81DA9(0x2D4259F1FEB81DA9);
lazy_func_t<void(Player player)> SET_SUPER_JUMP_THIS_FRAME(0x57FFF03E423A4C0B);
lazy_func_t<void()> _0xE3D969D2785FFB5E(0xE3D969D2785FFB5E);
lazy_func_t<void(Any p0, Any p1)> _0xEB078CA2B5E82ADD(0xEB078CA2B5E82ADD);
lazy_func_t<BOOL()> _0xE8B9C0EC9E183F35(0xE8B9C0EC9E183F35);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0x1BB299305C3E8C13(0x1BB299305C3E8C13);
lazy_func_t<Any()> GET_RANDOM_EVENT_FLAG(0xD2D57F1D764117B1);
lazy_func_t<void(BOOL toggle)> SET_FADE_OUT_AFTER_ARREST(0x1E0B4DC0D990A4E7);
lazy_func_t<Any(float p0, float p1, float p2, float p3, Any p4)>
	ADD_POLICE_RESTART(0x452736765B31FC4B);
lazy_func_t<Vector3(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	BOOL p9)>
	_0x21C235BC64831E5A(0x21C235BC64831E5A);
lazy_func_t<BOOL()> IS_THIS_A_MINIGAME_SCRIPT(0x7B30F65D7B710098);
lazy_func_t<BOOL(
	float x, float y, float z, Hash projHash, float radius, BOOL ownedByPlayer)>
	_IS_PROJECTILE_TYPE_IN_RADIUS(0x34318593248C8FB2);
lazy_func_t<void(Any p0, Any *p1, Any *p2, float p3, float p4, BOOL p5)>
	_0xE266ED23311F24D4(0xE266ED23311F24D4);
lazy_func_t<void(Any p0, Any p1, float p2, float p3, float p4, BOOL p5)>
	_0x8FA9C42FC5D7C64B(0x8FA9C42FC5D7C64B);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	float p9,
	float p10,
	float p11,
	Any *p12)>
	_0xF56DFB7B61BE7276(0xF56DFB7B61BE7276);
lazy_func_t<Any()> _0xD642319C54AADEB6(0xD642319C54AADEB6);
lazy_func_t<int(int profileSetting)> GET_PROFILE_SETTING(0xC488FF2356EA7791);
lazy_func_t<BOOL(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	Hash projHash,
	Vector3 *projPos,
	BOOL ownedByPlayer)>
	_GET_IS_PROJECTILE_TYPE_IN_AREA(0x8D7A43EC6A5FEA45);
lazy_func_t<void(Any *p0, const char *name)>
	REGISTER_ENUM_TO_SAVE(0x10C2FA78D0E128A1);
lazy_func_t<void(int p0, BOOL p1)> _0x1EAE0A6E978894A2(0x1EAE0A6E978894A2);
lazy_func_t<void(float p0)> _0x31727907B2C43C55(0x31727907B2C43C55);
lazy_func_t<void(BOOL toggle)> SET_MINIGAME_IN_PROGRESS(0x19E00D7322C6F85B);
lazy_func_t<BOOL()> IS_FRONTEND_FADING(0x7EA2B6AF97ECA6ED);
lazy_func_t<void()> STOP_SAVE_STRUCT(0xEB1774DF12BB9F12);
lazy_func_t<void(Any p0, BOOL p1)> _0xB129E447A2EDA4BF(0xB129E447A2EDA4BF);
lazy_func_t<void()> _0x06462A961E94B67C(0x06462A961E94B67C);
lazy_func_t<float()> _GET_BENCHMARK_TIME(0xE599A503B3837E1B);
lazy_func_t<BOOL()> IS_SNIPER_INVERTED(0x61A23B7EDA9BDA24);
lazy_func_t<BOOL()> IS_DURANGO_VERSION(0x4D982ADB1978442D);
lazy_func_t<BOOL()> IS_XBOX360_VERSION(0xF6201B4DAF662A9D);
lazy_func_t<BOOL()> _0x9689123E3F213AA5(0x9689123E3F213AA5);
lazy_func_t<void(const char *p0)> _0x02DEAAC8F8EA7FE7(0x02DEAAC8F8EA7FE7);
lazy_func_t<
	BOOL(float p0, float p1, float p2, float p3, float p4, float p5, Any p6)>
	IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(0xE54E209C35FFA18D);
lazy_func_t<void()> POPULATE_NOW(0x7472BB270D7B4F3E);
lazy_func_t<void()> STOP_SAVE_ARRAY(0x04456F95153C6BE4);
lazy_func_t<void(Any p0, float p1)> _0xD261BA3E7E998072(0xD261BA3E7E998072);
lazy_func_t<BOOL(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	float distance,
	Vector3 *spawnPoint)>
	FIND_SPAWN_POINT_IN_DIRECTION(0x6874E2190B0C1972);
lazy_func_t<BOOL(Any p0)> _0x19BFED045C647C49(0x19BFED045C647C49);
lazy_func_t<void(const char *p0, const char *p1)>
	_0x4DCDF92BF64236CD(0x4DCDF92BF64236CD);
lazy_func_t<Hash(const char *string)> GET_HASH_KEY(0xD24D37CC275948CC);
lazy_func_t<void(BOOL toggle)> SET_FADE_OUT_AFTER_DEATH(0x4A18E01DF2C87B86);
lazy_func_t<void()> RESET_DISPATCH_SPAWN_BLOCKING_AREAS(0xAC7BFD5C1D83EA75);
lazy_func_t<void()> _0xB3CD58CCA6CDA852(0xB3CD58CCA6CDA852);
lazy_func_t<void(float direction)> SET_WIND_DIRECTION(0xEB0F4468467B4528);
lazy_func_t<void(float p0)> _0x7C9C0B1EEB1F9072(0x7C9C0B1EEB1F9072);
lazy_func_t<Any *()> GET_RAIN_LEVEL(0x96695E368AD855F3);
lazy_func_t<void(Any *p0, const char *name)>
	_0x6F7794F28C6B2535(0x6F7794F28C6B2535);
lazy_func_t<void(Any *p0, int p1, const char *arrayName)>
	_START_SAVE_ARRAY(0x60FE567DF1B1AF9D);
lazy_func_t<void(BOOL p0)> _0x9D8D44ADBBA61EF2(0x9D8D44ADBBA61EF2);
lazy_func_t<BOOL(const char *weatherType)>
	IS_NEXT_WEATHER_TYPE(0x2FAA3A30BEC0F25D);
lazy_func_t<void(float p0)> _0xC3C221ADDDE31A11(0xC3C221ADDDE31A11);
lazy_func_t<Any()> _0x72DE52178C291CB5(0x72DE52178C291CB5);
lazy_func_t<int()> _0x6856EC3D35C81EA4(0x6856EC3D35C81EA4);
lazy_func_t<BOOL(Hash hash)>
	_HAS_CHEAT_STRING_JUST_BEEN_ENTERED(0x557E43C447E700A8);
lazy_func_t<void(Any *p0, const char *name)>
	_0x48F069265A0E4BEC(0x48F069265A0E4BEC);
lazy_func_t<void(Any *p0, const char *name)>
	_0xFAA457EF263E8763(0xFAA457EF263E8763);
lazy_func_t<int()> UPDATE_ONSCREEN_KEYBOARD(0x0CF2B696BBF945AE);
lazy_func_t<void(float p0)> _0x9F5E6BB6B34540DA(0x9F5E6BB6B34540DA);
lazy_func_t<float(float startRange, float endRange)>
	GET_RANDOM_FLOAT_IN_RANGE(0x313CE5879CEB6FCD);
lazy_func_t<int(int startRange, int endRange)>
	GET_RANDOM_INT_IN_RANGE(0xD53343AA4FB7DD28);
lazy_func_t<void(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	Any *p9,
	Any *p10,
	Any *p11,
	Any *p12)>
	_0xF2F6A2FA49278625(0xF2F6A2FA49278625);
lazy_func_t<BOOL(float x, float y, float z, float p3, BOOL p4, BOOL p5)>
	HAS_BULLET_IMPACTED_IN_AREA(0x9870ACFB89A90995);
lazy_func_t<int()> GET_INDEX_OF_CURRENT_LEVEL(0xCBAD6729F7B1F4FC);
lazy_func_t<void(int dispatchService, BOOL toggle)>
	ENABLE_DISPATCH_SERVICE(0xDC0F817884CDD856);
lazy_func_t<void()> _0x1FF6BF9A63E5757F(0x1FF6BF9A63E5757F);
lazy_func_t<int(int threadId)> _GET_FREE_STACK_SLOTS_COUNT(0xFEAD16FC8F9DFC0F);
lazy_func_t<void()> _0x37DEB0AA183FB6D8(0x37DEB0AA183FB6D8);
lazy_func_t<const char *()> _GET_GLOBAL_CHAR_BUFFER(0x24DA7D7667FD7B09);
lazy_func_t<BOOL(const char *weatherType)>
	IS_PREV_WEATHER_TYPE(0x44F28F86433B10A9);
lazy_func_t<void(int level)> SET_GRAVITY_LEVEL(0x740E14FAD5842351);
lazy_func_t<void(Any p0)> SET_RANDOM_EVENT_FLAG(0x971927086CFD2158);
lazy_func_t<void(int p0)> ENABLE_STUNT_JUMP_SET(0xE369A5783B866016);
lazy_func_t<BOOL(
	int incidentType,
	float x,
	float y,
	float z,
	int p5,
	float radius,
	int *outIncidentID)>
	CREATE_INCIDENT(0x3F892CAF67444AE7);
lazy_func_t<void(float p0)>
	SET_DISPATCH_IDEAL_SPAWN_DISTANCE(0x6FE601A64180D423);
lazy_func_t<Any()> _0x5AA3BEFA29F03AD4(0x5AA3BEFA29F03AD4);
lazy_func_t<void(BOOL toggle)> USING_MISSION_CREATOR(0xF14878FC50BEC6EE);
lazy_func_t<int()> _0x397BAA01068BAA96(0x397BAA01068BAA96);
lazy_func_t<void(int incidentId)> DELETE_INCIDENT(0x556C1AA270D5A207);
lazy_func_t<void()> _0xC79AE21974B01FB2(0xC79AE21974B01FB2);
lazy_func_t<Hash()> GET_NEXT_WEATHER_TYPE_HASH_NAME(0x711327CD09C8F162);
lazy_func_t<Any()> _0x075F1D57402C93BA(0x075F1D57402C93BA);
lazy_func_t<void(BOOL p0)> _0xDEA36202FC3382DF(0xDEA36202FC3382DF);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	BOOL p7)>
	IS_BULLET_IN_ANGLED_AREA(0x1A8B5F3C01E2B477);
lazy_func_t<BOOL()> IS_AUSSIE_VERSION(0x9F1935CA1F724008);
lazy_func_t<void(Any p0)> _0x703CC7F60CBB2B57(0x703CC7F60CBB2B57);
lazy_func_t<void(
	int p0,
	const char *windowTitle,
	const char *p2,
	const char *defaultText,
	const char *defaultConcat1,
	const char *defaultConcat2,
	const char *defaultConcat3,
	int maxInputLength)>
	DISPLAY_ONSCREEN_KEYBOARD(0x00DC833F2568DBF6);
lazy_func_t<BOOL(Any p0, Any *p1, Any *p2)>
	_0x8EF5573A1F801A5C(0x8EF5573A1F801A5C);
lazy_func_t<float()> GET_FRAME_TIME(0x15C40837039FFAF7);
lazy_func_t<void(Hash weatherType1, Hash weatherType2, float percentWeather2)>
	_SET_WEATHER_TYPE_TRANSITION(0x578C752848ECFA0C);
lazy_func_t<BOOL()> IS_MEMORY_CARD_IN_USE(0x8A75CE2956274ADD);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0xD10F442036302D50(0xD10F442036302D50);
lazy_func_t<void(Any p0, float p1)>
	SET_DISPATCH_TIME_BETWEEN_SPAWN_ATTEMPTS_MULTIPLIER(0x48838ED9937A15D1);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0xB8721407EE9C3FF6(0xB8721407EE9C3FF6);
lazy_func_t<void(const char *p0)> _0x8D74E26F54B4E5C3(0x8D74E26F54B4E5C3);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	float range,
	BOOL p4,
	BOOL p5,
	BOOL p6,
	BOOL p7,
	BOOL p8,
	Any p9,
	BOOL p10)>
	IS_POSITION_OCCUPIED(0xADCDE75E1C60F32D);
lazy_func_t<Any()> _0x5B1F2E327B6B6FE1(0x5B1F2E327B6B6FE1);
lazy_func_t<BOOL(float x1, float y1, float z1, float x2, float y2, float z2)>
	IS_SNIPER_BULLET_IN_AREA(0xFEFCF11B01287125);
lazy_func_t<void()> _RESET_LOCALPLAYER_STATE(0xC0AA53F866B3134D);
lazy_func_t<void()> _0x92790862E36C2ADA(0x92790862E36C2ADA);
lazy_func_t<
	void(Hash *weatherType1, Hash *weatherType2, float *percentWeather2)>
	_GET_WEATHER_TYPE_TRANSITION(0xF3BBE884A14BB413);
lazy_func_t<float(float p0, float p1)> ATAN2(0x8927CBF9D22261A4);
lazy_func_t<Any()> _0x44A0BDC559B35F6E(0x44A0BDC559B35F6E);
lazy_func_t<BOOL(const char *string)>
	IS_STRING_NULL_OR_EMPTY(0xCA042B6957743895);
lazy_func_t<void(int *var, int rangeStart, int rangeEnd, int p3)>
	SET_BITS_IN_RANGE(0x8EF07E15701D61ED);
lazy_func_t<BOOL()> IS_STUNT_JUMP_IN_PROGRESS(0x7A3F19700A4D0525);
lazy_func_t<void(Any *p0, Any *p1)> _0xA735353C77334EA0(0xA735353C77334EA0);
lazy_func_t<void(Any p0)> _0x97E7E2C04245115B(0x97E7E2C04245115B);
lazy_func_t<int()> GET_ALLOCATED_STACK_SIZE(0x8B3CA62B1EF19B62);
lazy_func_t<int(int var, int rangeStart, int rangeEnd)>
	GET_BITS_IN_RANGE(0x53158863FCC0893A);
lazy_func_t<
	Any(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8)>
	_0x67F6413D3220E18D(0x67F6413D3220E18D);
lazy_func_t<Any()> _0x14832BF2ABA53FC5(0x14832BF2ABA53FC5);
lazy_func_t<BOOL()> IS_AUTO_SAVE_IN_PROGRESS(0x69240733738C19A0);
lazy_func_t<void()> _CLEAR_CLOUD_HAT(0x957E790EA1727B64);
lazy_func_t<BOOL()> IS_PC_VERSION(0x48AF36444B965238);
lazy_func_t<BOOL(Any p0)> _0xE95B0C7D5BA3B96B(0xE95B0C7D5BA3B96B);
lazy_func_t<float()> GET_WIND_SPEED(0xA8CF1CC0AFCD3F12);
lazy_func_t<void(float p0)> _0xA8434F1DFF41D6E7(0xA8434F1DFF41D6E7);
lazy_func_t<void(BOOL toggle)> SET_GAME_PAUSED(0x577D1284D6873711);
lazy_func_t<void(BOOL toggle)> _SHOW_PED_IN_PAUSE_MENU(0x4EBB7E87AA0DBED4);
lazy_func_t<void(const char *weatherType)>
	SET_OVERRIDE_WEATHER(0xA43D5C6FE51ADBEF);
lazy_func_t<void(float intensity)> _SET_RAIN_FX_INTENSITY(0x643E26EA6E024D92);
lazy_func_t<BOOL(float x, float y, float z, float *groundZ, Vector3 *offsets)>
	_GET_GROUND_Z_COORD_WITH_OFFSETS(0x8BDC7BFC57A81E76);
lazy_func_t<void(BOOL toggle)> SET_FADE_IN_AFTER_LOAD(0xF3D78F59DFE18D79);
lazy_func_t<BOOL()> _0xA049A5BE0F04F2F8(0xA049A5BE0F04F2F8);
lazy_func_t<void(BOOL toggle)> SET_MISSION_FLAG(0xC4301E5121A0ED73);
lazy_func_t<void()> _FORCE_SOCIAL_CLUB_UPDATE(0xEB6891F03362FB12);
lazy_func_t<void(BOOL p0)> _0x2587A48BC88DFADF(0x2587A48BC88DFADF);
lazy_func_t<void(float x, float y, float z, float radius, int flags)>
	CLEAR_AREA_OF_OBJECTS(0xDD9B9B385AAC7F5B);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	Any p7,
	BOOL p8)>
	IS_PROJECTILE_TYPE_IN_ANGLED_AREA(0xF0BC12401061DEA0);
lazy_func_t<void(Any *p0, const char *name)>
	REGISTER_FLOAT_TO_SAVE(0x7CAEC29ECB5DFEBB);
lazy_func_t<void(float p0)> _0xB8F87EAD7533B176(0xB8F87EAD7533B176);
lazy_func_t<void(float opacity)> _SET_CLOUD_HAT_OPACITY(0xF36199225D6D8C86);
lazy_func_t<void(BOOL toggle)> SET_CREDITS_ACTIVE(0xB938B7E6D3C0620C);
lazy_func_t<void(
	int p0,
	const char *windowTitle,
	Any *p2,
	const char *defaultText,
	const char *defaultConcat1,
	const char *defaultConcat2,
	const char *defaultConcat3,
	const char *defaultConcat4,
	const char *defaultConcat5,
	const char *defaultConcat6,
	const char *defaultConcat7,
	int maxInputLength)>
	_DISPLAY_ONSCREEN_KEYBOARD_2(0xCA78CFA0366592FE);
lazy_func_t<void(float p0)> _0xC3EAD29AB273ECE8(0xC3EAD29AB273ECE8);
lazy_func_t<int()> GET_FRAME_COUNT(0xFC8202EFC642E6F2);
lazy_func_t<void(float p0)> _0x6216B116083A7CB4(0x6216B116083A7CB4);
lazy_func_t<void(BOOL disableRespawn)>
	_DISABLE_AUTOMATIC_RESPAWN(0x2C2B3493FBF51C71);
lazy_func_t<void(Any p0)> _0x69FE6DC87BD2A5E9(0x69FE6DC87BD2A5E9);
lazy_func_t<BOOL()> IS_MINIGAME_IN_PROGRESS(0x2B4A15E44DE0F478);
lazy_func_t<BOOL(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	BOOL ownedByPlayer)>
	IS_PROJECTILE_IN_AREA(0x5270A8FBC098C3F8);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	BOOL p6,
	BOOL p7)>
	HAS_BULLET_IMPACTED_IN_BOX(0xDC8C5D7CFEAB8394);
lazy_func_t<
	int(float p0,
		float p1,
		float p2,
		float p3,
		float p4,
		float p5,
		float p6,
		float p7,
		float p8,
		float p9,
		float p10,
		float p11,
		float p12,
		float p13,
		float p14,
		Any p15,
		Any p16)>
	ADD_STUNT_JUMP(0x1A992DA297A4630C);
lazy_func_t<void()> _0x8951EB9C6906D3C8(0x8951EB9C6906D3C8);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	_0xA4A0065E39C9F25C(0xA4A0065E39C9F25C);
lazy_func_t<BOOL()> IS_ORBIS_VERSION(0xA72BC0B675B1519E);
lazy_func_t<void(int p0)> DISABLE_STUNT_JUMP_SET(0xA5272EBEDD4747F6);
lazy_func_t<BOOL(Hash hash, int amount)>
	_HAS_BUTTON_COMBINATION_JUST_BEEN_ENTERED(0x071E2A839DE82D90);
lazy_func_t<void(Any *p0, Any p1, BOOL p2)> START_SAVE_DATA(0xA9575F812C6A7997);
lazy_func_t<Hash()> GET_PREV_WEATHER_TYPE_HASH_NAME(0x564B884A05EC45A3);
lazy_func_t<void(float speed)> SET_WIND(0xAC3A74E8384A9919);
lazy_func_t<void(BOOL toggle)>
	SET_THIS_SCRIPT_CAN_BE_PAUSED(0xAA391C728106F7AF);
lazy_func_t<void(Any p0, const char *p1, float p2)>
	_0x54F157E0336A3822(0x54F157E0336A3822);
lazy_func_t<void(Any *p0)> _0xEBD3205A207939ED(0xEBD3205A207939ED);
lazy_func_t<void()> SET_RANDOM_WEATHER_TYPE(0x8B05F884CF7E8020);
lazy_func_t<
	int(float p0,
		float p1,
		float p2,
		float p3,
		float p4,
		float p5,
		float p6,
		float p7,
		float p8,
		float p9,
		float p10,
		float p11,
		float p12,
		float p13,
		float p14,
		float p15,
		float p16,
		Any p17,
		Any p18)>
	ADD_STUNT_JUMP_ANGLED(0xBBE5D803A5360CBF);
lazy_func_t<void()> _0xD9F692D349249528(0xD9F692D349249528);
lazy_func_t<void(const char *weatherType)>
	SET_WEATHER_TYPE_NOW_PERSIST(0xED712CA327900C8A);
lazy_func_t<void()> _SET_NEXT_RESPAWN_TO_CUSTOM(0xA2716D40842EAF79);
lazy_func_t<
	Any(float p0, float p1, float p2, float p3, Any *p4, Any p5, Any p6)>
	REGISTER_SAVE_HOUSE(0xC0714D0A7EEECA54);
lazy_func_t<Any()> _0x2107A3773771186D(0x2107A3773771186D);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int damage,
	BOOL p7,
	Hash weaponHash,
	Ped ownerPed,
	BOOL isAudible,
	BOOL isInvisible,
	float speed,
	Entity entity)>
	_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_PRESET_PARAMS(0xE3A7742E0B7A2F8B);
lazy_func_t<void(int p0)> _0x3ED1438C1F5C6612(0x3ED1438C1F5C6612);
lazy_func_t<void()> _0xFB00CA71DA386228(0xFB00CA71DA386228);
lazy_func_t<void(float p0)> _0xB9854DFDE0D833D6(0xB9854DFDE0D833D6);
lazy_func_t<void()>
	NETWORK_SET_SCRIPT_IS_SAFE_FOR_NETWORK_GAME(0x9243BAC96D64C050);
lazy_func_t<void()> DO_AUTO_SAVE(0x50EEAAD86232EE55);
lazy_func_t<BOOL(Any p0)> _0x1327E2FE9746BAEE(0x1327E2FE9746BAEE);
lazy_func_t<void(const char *type, float transitionTime)>
	_SET_CLOUD_HAT_TRANSITION(0xFC4842A34657BFCB);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int damage,
	BOOL p7,
	Hash weaponHash,
	Ped ownerPed,
	BOOL isAudible,
	BOOL isInvisible,
	float speed,
	Entity entity,
	BOOL p14,
	BOOL p15,
	BOOL p16,
	BOOL p17)>
	_SHOOT_SINGLE_BULLET_BETWEEN_COORDS_WITH_EXTRA_PARAMS(0xBFE5756E7407064A);
lazy_func_t<float(float value)> ABSF(0x73D57CFFDD12C355);
lazy_func_t<void(Any *p0, const char *name)>
	REGISTER_TEXT_LABEL_TO_SAVE(0xEDB1232C5BEAE62F);
lazy_func_t<
	Any(float p0,
		float p1,
		float p2,
		float p3,
		float p4,
		float p5,
		BOOL p6,
		BOOL p7)>
	_0x32C7A7E8C43A1F80(0x32C7A7E8C43A1F80);
lazy_func_t<void(Any p0)> _0xBA4B8D83BDC75551(0xBA4B8D83BDC75551);
lazy_func_t<void(float x, float y, float z, float radius, int flags)>
	CLEAR_AREA_OF_COPS(0x04F8FC8FCF58F88D);
lazy_func_t<BOOL()> _0x6FDDF453C0C756EC(0x6FDDF453C0C756EC);
lazy_func_t<void(float x, float y, float z, float radius, int flags)>
	CLEAR_AREA_OF_PEDS(0xBE31FD6CE464AC59);
lazy_func_t<BOOL(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int type,
	BOOL p7)>
	IS_PROJECTILE_TYPE_IN_AREA(0x2E0DC353342C4A6D);
lazy_func_t<void(Any *p0, const char *name)>
	REGISTER_INT_TO_SAVE(0x34C9EE5986258415);
lazy_func_t<BOOL(
	int incidentType,
	Ped ped,
	int amountOfPeople,
	float radius,
	int *outIncidentID)>
	CREATE_INCIDENT_WITH_ENTITY(0x05983472F0494E60);
lazy_func_t<void(Any p0, Any p1)> BEGIN_REPLAY_STATS(0xE0E500246FF73D66);
lazy_func_t<float()> _GET_CLOUD_HAT_OPACITY(0x20AC25E781AE4A84);
lazy_func_t<void(const char *scriptName)>
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(0x9DC711BC69C548DF);
lazy_func_t<void(int type, BOOL toggle)>
	_0x9B2BD3773123EA2F(0x9B2BD3773123EA2F);
lazy_func_t<void(Any p0, Any p1)> _0xE532EC1A63231B4F(0xE532EC1A63231B4F);
lazy_func_t<Any(Player player)>
	SET_EXPLOSIVE_MELEE_THIS_FRAME(0xFF1BED81BFDC0FE0);
lazy_func_t<void(float p0)> _0xA7A1127490312C36(0xA7A1127490312C36);
lazy_func_t<float(float p0)> ACOS(0x1D08B970013C34B6);
lazy_func_t<float(float p0)> ATAN(0xA9D1795CD5043663);
lazy_func_t<void(
	float x,
	float y,
	float z,
	float radius,
	BOOL p4,
	BOOL p5,
	BOOL p6,
	BOOL p7,
	BOOL p8)>
	CLEAR_AREA_OF_VEHICLES(0x01C7B9B38428AEB6);
lazy_func_t<int(float x, float y, float z, float p3, Any p4)>
	ADD_HOSPITAL_RESTART(0x1F464EF988465A81);
lazy_func_t<void(int hospitalIndex, BOOL toggle)>
	DISABLE_HOSPITAL_RESTART(0xC8535819C450EBA8);
lazy_func_t<BOOL(const char *string1, const char *string2)>
	ARE_STRINGS_EQUAL(0x0C515FAB3FF9EA92);
lazy_func_t<int(BOOL p0)> _0xA09F896CE912481F(0xA09F896CE912481F);
lazy_func_t<void(float time)> SET_TIME_SCALE(0x1D408577D440E81E);
lazy_func_t<void()> CANCEL_STUNT_JUMP(0xE6B7B0ACD4E4B75E);
lazy_func_t<void(Any *p0, const char *name)>
	_0x8269816F6CFD40F8(0x8269816F6CFD40F8);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0xB08B85D860E7BA3C(0xB08B85D860E7BA3C);
lazy_func_t<Any()> _0xEA2F2061875EED90(0xEA2F2061875EED90);
lazy_func_t<BOOL(float x, float y, float z, float *groundZ, BOOL unk)>
	GET_GROUND_Z_FOR_3D_COORD(0xC906A7DAB05C8D2B);
lazy_func_t<Any()> _0x2B626A0150E4D449(0x2B626A0150E4D449);
lazy_func_t<Any()> _0xD10282B6E3751BA0(0xD10282B6E3751BA0);
lazy_func_t<void(const char *p0, float p1)>
	_0xA74802FB8D0B7814(0xA74802FB8D0B7814);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0x0A60017F841A54F2(0x0A60017F841A54F2);
lazy_func_t<BOOL(Ped ped)> IS_TENNIS_MODE(0x5D5479D115290C3F);
}} // namespace GAMEPLAY::
namespace CAM { namespace {
lazy_func_t<void(Any p0, float p1)> _0xE111A7C0D200CBC5(0xE111A7C0D200CBC5);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0x0FB82563989CF4FB(0x0FB82563989CF4FB);
lazy_func_t<void()> _0xC8391C309684595A(0xC8391C309684595A);
lazy_func_t<void(float p0, float p1)> _0xCED08CBE8EBB97C7(0xCED08CBE8EBB97C7);
lazy_func_t<void(Any p0)> _0x11FA5D3479C7DD47(0x11FA5D3479C7DD47);
lazy_func_t<void(Cam cam, BOOL toggle)>
	SET_CAM_USE_SHALLOW_DOF_MODE(0x16A96863A17552BB);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0x609278246A29CA34(0x609278246A29CA34);
lazy_func_t<BOOL()> IS_GAMEPLAY_HINT_ACTIVE(0xE520FF1AD2785B40);
lazy_func_t<void(Cam cam)> STOP_CAM_POINTING(0xF33AB75780BA57DE);
lazy_func_t<void(Any p0, float p1, float p2, float p3)>
	_0x503F5920162365B2(0x503F5920162365B2);
lazy_func_t<BOOL()> IS_SCREEN_FADING_OUT(0x797AC7CB535BA28F);
lazy_func_t<BOOL()> _0x705A276EBFF3133D(0x705A276EBFF3133D);
lazy_func_t<void(int p0)> _SET_CAM_EFFECT(0x80C8B1846639BB19);
lazy_func_t<void(Cam cam, float p1)> SET_CAM_SPLINE_PHASE(0x242B5874F0A4E052);
lazy_func_t<float()> _0x80EC114669DAEFF4(0x80EC114669DAEFF4);
lazy_func_t<void(Cam p0)> _0xC8B5C4A79CC18B94(0xC8B5C4A79CC18B94);
lazy_func_t<Any(float p0)> _0x70894BD0915C5BCA(0x70894BD0915C5BCA);
lazy_func_t<float()> GET_GAMEPLAY_CAM_RELATIVE_HEADING(0x743607648ADD4587);
lazy_func_t<void(Cam cam, BOOL toggle)>
	SET_CAM_AFFECTS_AIMING(0x8C1DC7770C51DC8D);
lazy_func_t<void()> _0x59424BD75174C9B1(0x59424BD75174C9B1);
lazy_func_t<int()> GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(0xEE82280AB767B690);
lazy_func_t<void(Any p0, Any p1)> _0x2A2173E46DAECD12(0x2A2173E46DAECD12);
lazy_func_t<float(Cam cam)> GET_CAM_NEAR_CLIP(0xC520A34DAFBF24B1);
lazy_func_t<void(Cam cam, float dofStrength)>
	SET_CAM_DOF_STRENGTH(0x5EE29B4D7D5DF897);
lazy_func_t<void(Cam cam, int p1, float p2, float p3)>
	OVERRIDE_CAM_SPLINE_VELOCITY(0x40B62FA033EB0346);
lazy_func_t<Vector3()> GET_GAMEPLAY_CAM_COORD(0x14D6F5678D8F1B37);
lazy_func_t<BOOL(const char *p0, int p1)>
	SET_FOLLOW_PED_CAM_CUTSCENE_CHAT(0x44A113DD6FFC48D1);
lazy_func_t<void(BOOL p0)> SET_CINEMATIC_MODE_ACTIVE(0xDCF0754AC3D6FD4E);
lazy_func_t<Entity(
	float p0,
	int p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	int p7,
	int p8)>
	_0x89215EC747DF244A(0x89215EC747DF244A);
lazy_func_t<Any()> _0x17FCA7199A530203(0x17FCA7199A530203);
lazy_func_t<void(float yaw)> _SET_GAMEPLAY_CAM_RAW_YAW(0x103991D4A307D472);
lazy_func_t<void(int viewMode)>
	SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(0xAC253D7842768F48);
lazy_func_t<Any()> _0x8BFCEB5EA1B161B6(0x8BFCEB5EA1B161B6);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0x0A9F2A468B328E74(0x0A9F2A468B328E74);
lazy_func_t<Vector3(int rotationOrder)>
	GET_GAMEPLAY_CAM_ROT(0x837765A25378F0BB);
lazy_func_t<void(float p0)> _0x5D7B620DAE436138(0x5D7B620DAE436138);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0x7BF1A54AE67AC070(0x7BF1A54AE67AC070);
lazy_func_t<BOOL(
	Cam cam,
	const char *animName,
	const char *animDictionary,
	float x,
	float y,
	float z,
	float xRot,
	float yRot,
	float zRot,
	BOOL p9,
	int p10)>
	PLAY_CAM_ANIM(0x9A2D0FB2E7852392);
lazy_func_t<int(Any p0, Any p1)> _0x26903D9CD1175F2C(0x26903D9CD1175F2C);
lazy_func_t<void()> SET_USE_HI_DOF(0xA13B0222F3D94A94);
lazy_func_t<void(
	Cam cam, Ped ped, int boneIndex, float x, float y, float z, BOOL heading)>
	ATTACH_CAM_TO_PED_BONE(0x61A3DBA14AB7F411);
lazy_func_t<void(Cam cam, float phase)>
	SET_CAM_ANIM_CURRENT_PHASE(0x4145A4C44FF3B5A6);
lazy_func_t<float(Cam cam)> GET_CAM_ANIM_CURRENT_PHASE(0xA10B2DB49E92A6B0);
lazy_func_t<Vector3(int rotationOrder)>
	_GET_GAMEPLAY_CAM_ROT(0x5B4E4C817FCC2DFB);
lazy_func_t<void(Cam cam, float nearDOF)> SET_CAM_NEAR_DOF(0x3FA4BF0A7AB7DE2C);
lazy_func_t<BOOL()> IS_SCRIPT_GLOBAL_SHAKING(0xC912AF078AF19212);
lazy_func_t<BOOL(Cam cam, const char *animName, const char *animDictionary)>
	IS_CAM_PLAYING_ANIM(0xC90621D8A0CEECF2);
lazy_func_t<void(Entity entity)> _0x2AED6301F67007D5(0x2AED6301F67007D5);
lazy_func_t<BOOL()> IS_CINEMATIC_CAM_RENDERING(0xB15162CB5826E9E8);
lazy_func_t<void(float p0)>
	SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(0xC724C701C30B2FE7);
lazy_func_t<int()> GET_FOLLOW_PED_CAM_VIEW_MODE(0x8D4D46230B2C353A);
lazy_func_t<void(int viewMode)>
	SET_FOLLOW_PED_CAM_VIEW_MODE(0x5A4F9EDF1673F704);
lazy_func_t<void(float p0)> _0xD1F8363DFAD03848(0xD1F8363DFAD03848);
lazy_func_t<void(Cam cam, float x, float y, float z)>
	POINT_CAM_AT_COORD(0xF75497BB865F0803);
lazy_func_t<void(Any p0, BOOL p1)> _0xA2767257A320FC82(0xA2767257A320FC82);
lazy_func_t<float(Cam cam)> GET_CAM_SPLINE_NODE_PHASE(0xD9D0E694C8282C96);
lazy_func_t<void(
	float x,
	float y,
	float z,
	int duration,
	int blendOutDuration,
	int blendInDuration,
	int unk)>
	SET_GAMEPLAY_COORD_HINT(0xD51ADCD2D8BC0FB3);
lazy_func_t<void(Cam cam, BOOL active)> SET_CAM_ACTIVE(0x026FB97D0A425F84);
lazy_func_t<void(Cam cam, const char *type, float amplitude)>
	SHAKE_CAM(0x6A25241C340D3822);
lazy_func_t<void(float heading)>
	SET_GAMEPLAY_CAM_RELATIVE_HEADING(0xB4EC2312F4E5B1F1);
lazy_func_t<void(BOOL p0)> _0x247ACBC4ABBC9D1C(0x247ACBC4ABBC9D1C);
lazy_func_t<void(int zoomLevel)>
	SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(0x19464CB6E4078C8A);
lazy_func_t<float()> _GET_GAMEPLAY_CAM_FAR_CLIP(0xDFC8CBC606FDB0FC);
lazy_func_t<BOOL()> _IS_IN_VEHICLE_CAM_DISABLED(0x4F32C0D5A90A9B40);
lazy_func_t<void(Cam cam, Entity entity, float p2, float p3, float p4, BOOL p5)>
	POINT_CAM_AT_ENTITY(0x5640BFF86B16E8DC);
lazy_func_t<BOOL(Any p0)> IS_CAM_SPLINE_PAUSED(0x0290F35C0AD97864);
lazy_func_t<void()> _DISABLE_FIRST_PERSON_CAM_THIS_FRAME(0xDE2EF5DA284CC8DF);
lazy_func_t<void(Cam cam, float posX, float posY, float posZ)>
	SET_CAM_COORD(0x4D41783FB745E42E);
lazy_func_t<void(Any p0, float p1, float p2, float p3)>
	_0xC91C6C55199308CA(0xC91C6C55199308CA);
lazy_func_t<void(BOOL p0)> SET_CINEMATIC_BUTTON_ACTIVE(0x51669F7D1FB53D9F);
lazy_func_t<void(Cam camera, float p1)>
	_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(0xC3654A441402562D);
lazy_func_t<void()> _0x62ECFCFDEE7885D6(0x62ECFCFDEE7885D6);
lazy_func_t<float()> GET_GAMEPLAY_CAM_FOV(0x65019750A0324133);
lazy_func_t<void(float pitch)> _SET_GAMEPLAY_CAM_RAW_PITCH(0x759E13EBC1C15C5A);
lazy_func_t<float()> _GET_GAMEPLAY_CAM_FAR_DOF(0x9780F32BCAF72431);
lazy_func_t<void(BOOL p0)> GET_IS_MULTIPLAYER_BRIEF(0xE3433EADAAF7EE40);
lazy_func_t<void(Cam cam, float p1, float p2, float p3, float p4)>
	SET_CAM_DOF_PLANES(0x3CF48F6F96E749DC);
lazy_func_t<float(Cam cam)> GET_CAM_SPLINE_PHASE(0xB5349E36C546509A);
lazy_func_t<void(Cam cam, float fieldOfView)> SET_CAM_FOV(0xB13C14F66A00D047);
lazy_func_t<Any()> _0x19CAFA3C87F7C2FF(0x19CAFA3C87F7C2FF);
lazy_func_t<float(Any p0)> _0x5F35F6732C3FBBA0(0x5F35F6732C3FBBA0);
lazy_func_t<void(BOOL render, float p1, int p2)>
	_RENDER_FIRST_PERSON_CAM(0xC819F3CBB62BF692);
lazy_func_t<BOOL(Any p0)> IS_CINEMATIC_SHOT_ACTIVE(0xCC9F3371A7C28BC9);
lazy_func_t<void(Any p0, int p1, Any p2, Entity entity)>
	CREATE_CINEMATIC_SHOT(0x741B0129D4560F31);
lazy_func_t<BOOL(Any p0)> _0x5C48A1D6E3B33179(0x5C48A1D6E3B33179);
lazy_func_t<BOOL()> IS_FOLLOW_VEHICLE_CAM_ACTIVE(0xCBBDE6D335D6D496);
lazy_func_t<Any(Any p0)> _0xEE778F8C7E1142E2(0xEE778F8C7E1142E2);
lazy_func_t<void(Cam cam, BOOL thisScriptCheck)>
	DESTROY_CAM(0x865908C81A2C22E9);
lazy_func_t<void(
	Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation)>
	SET_CAM_ACTIVE_WITH_INTERP(0x9FBDA379383A52A4);
lazy_func_t<void(Any p0, Any p1, float p2)>
	_0xA6385DEB180F319F(0xA6385DEB180F319F);
lazy_func_t<void(const char *vehicleName)>
	_0x21E253A7F8DA5DFB(0x21E253A7F8DA5DFB);
lazy_func_t<Any()> _0xEAF0FA793D05C592(0xEAF0FA793D05C592);
lazy_func_t<Cam(const char *Gippo, BOOL p1)> CREATE_CAM(0xC3981DCE61D9E13F);
lazy_func_t<void(Any p0, BOOL p1)> _0x271017B9BA825366(0x271017B9BA825366);
lazy_func_t<
	Cam(Hash camHash,
		float posX,
		float posY,
		float posZ,
		float rotX,
		float rotY,
		float rotZ,
		float fov,
		BOOL p8,
		Any p9)>
	CREATE_CAMERA_WITH_PARAMS(0x6ABFA3E16460F22D);
lazy_func_t<float()> _GET_GAMEPLAY_CAM_ZOOM(0x7EC52CC40597D170);
lazy_func_t<Vector3()> _GET_GAMEPLAY_CAM_COORDS(0xA200EB1EE790F448);
lazy_func_t<BOOL(Cam cam)> IS_CAM_INTERPOLATING(0x036F97C908C2B52C);
lazy_func_t<Cam()> GET_RENDERING_CAM(0x5234F9F10919EABA);
lazy_func_t<BOOL(Cam cam)> DOES_CAM_EXIST(0xA7A932170592B50E);
lazy_func_t<void(BOOL p0)> STOP_SCRIPT_GLOBAL_SHAKING(0x1C9D7949FA533490);
lazy_func_t<BOOL()> IS_SCREEN_FADED_IN(0x5A859503B0C08678);
lazy_func_t<void()>
	_DISABLE_VEHICLE_FIRST_PERSON_CAM_THIS_FRAME(0xADFF1B2A555F5FBA);
lazy_func_t<void()> STOP_CUTSCENE_CAM_SHAKING(0xDB629FFD9285FA06);
lazy_func_t<
	Cam(const char *camName,
		float posX,
		float posY,
		float posZ,
		float rotX,
		float rotY,
		float rotZ,
		float fov,
		BOOL p8,
		int p9)>
	CREATE_CAM_WITH_PARAMS(0xB51194800B257161);
lazy_func_t<BOOL(Cam cam)> IS_CAM_SHAKING(0x6B24BFE83A2BE47B);
lazy_func_t<void(float distance)>
	_SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP(0x42156508606DE65E);
lazy_func_t<void(float FOV)> SET_GAMEPLAY_HINT_FOV(0x513403FB9C56211F);
lazy_func_t<void(Cam cam)> DETACH_CAM(0xA2FABBE87F4BAD82);
lazy_func_t<void(Any p0, Any p1, Any p2, float p3)>
	_0x83B8201ED82A9A2D(0x83B8201ED82A9A2D);
lazy_func_t<void(float x, float Value2)>
	SET_GAMEPLAY_CAM_RELATIVE_PITCH(0x6D0858B8EDFD2B7D);
lazy_func_t<BOOL()> IS_GAMEPLAY_CAM_LOOKING_BEHIND(0x70FDA869F3317EA9);
lazy_func_t<void(BOOL thisScriptCheck)> DESTROY_ALL_CAMS(0x8E5FB15663F79120);
lazy_func_t<void(Cam camera, float p1)>
	_SET_CAM_DOF_FNUMBER_OF_LENS(0x7DD234D6F3914C5B);
lazy_func_t<void(Cam camera, float p1)>
	_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(0x2C654B4943BDDF7C);
lazy_func_t<void(BOOL p0)> STOP_GAMEPLAY_CAM_SHAKING(0x0EF93E9F3D08C178);
lazy_func_t<void(float p0, float distance)>
	_ANIMATE_GAMEPLAY_CAM_ZOOM(0xDF2E1F7742402E81);
lazy_func_t<
	void(Cam cam, float rotX, float rotY, float rotZ, int rotationOrder)>
	SET_CAM_ROT(0x85973643155D0B07);
lazy_func_t<void()> _0xF4F2C0D4EE209E20(0xF4F2C0D4EE209E20);
lazy_func_t<void(Any p0)> _0x5C41E6BABC9E2112(0x5C41E6BABC9E2112);
lazy_func_t<Any(BOOL p0, int p1)> SET_WIDESCREEN_BORDERS(0xDCD4EA924F42D01A);
lazy_func_t<Cam(Hash camHash, BOOL p1)> CREATE_CAMERA(0x5E3CF89C6BCCA67D);
lazy_func_t<void(int cam, int timeDuration)>
	SET_CAM_SPLINE_DURATION(0x1381539FEE034CDA);
lazy_func_t<void(const char *shakeName, float intensity)>
	SHAKE_GAMEPLAY_CAM(0xFD55E49555E017CF);
lazy_func_t<Any()> _0xBF72910D0F26F025(0xBF72910D0F26F025);
lazy_func_t<Vector3(Cam cam, int rotationOrder)>
	GET_CAM_ROT(0x7D304C1C955E3E12);
lazy_func_t<void(BOOL p0, BOOL p1)> SET_TIME_IDLE_DROP(0x9DFE13ECDC1EC196);
lazy_func_t<void(float p0)> _0x0225778816FDC28C(0x0225778816FDC28C);
lazy_func_t<void()> _0xDD79DF9F4D26E1C9(0xDD79DF9F4D26E1C9);
lazy_func_t<void(float p0)> CUSTOM_MENU_COORDINATES(0x487A82C650EB7799);
lazy_func_t<void(Cam camera, float p1)>
	_SET_CAM_DOF_FOCUS_DISTANCE_BIAS(0xC669EEA5D031B7DE);
lazy_func_t<BOOL()> _0x3044240D2E0FA842(0x3044240D2E0FA842);
lazy_func_t<float(Cam cam)> GET_CAM_FAR_DOF(0x255F8DAFD540D397);
lazy_func_t<BOOL()> IS_GAMEPLAY_CAM_RENDERING(0x39B5D1B10383F0C8);
lazy_func_t<void(BOOL p0)> STOP_CINEMATIC_CAM_SHAKING(0x2238E588E588A6D7);
lazy_func_t<void()> _0xDC9DA9E8789F5246(0xDC9DA9E8789F5246);
lazy_func_t<float(Cam cam)> GET_CAM_FOV(0xC3330A45CCCDB26A);
lazy_func_t<void(
	Cam cam, const char *p1, const char *p2, const char *p3, float amplitude)>
	ANIMATED_SHAKE_CAM(0xA2746EEAE3E577CD);
lazy_func_t<Any(float minimum, float maximum)>
	_CLAMP_GAMEPLAY_CAM_YAW(0x8F993D26E0CA5E8E);
lazy_func_t<int()> GET_FOLLOW_VEHICLE_CAM_VIEW_MODE(0xA4FF579AC0E3AAAE);
lazy_func_t<void(float minAngle, float maxAngle)>
	_SET_FIRST_PERSON_CAM_PITCH_RANGE(0xBCFC632DB7673BF0);
lazy_func_t<void(Cam cam, int p1, float p2, float p3)>
	OVERRIDE_CAM_SPLINE_MOTION_BLUR(0x7DCF7C708D292D55);
lazy_func_t<void(Any p0, float p1)> _0xF55E4046F6F831DC(0xF55E4046F6F831DC);
lazy_func_t<void(Entity entity)> _0x49482F9FCD825AAA(0x49482F9FCD825AAA);
lazy_func_t<BOOL()> _0xCA9D2AA3E326D720(0xCA9D2AA3E326D720);
lazy_func_t<
	void(Any p0, float p1, float p2, float p3, BOOL p4, Any p5, Any p6, Any p7)>
	SET_GAMEPLAY_OBJECT_HINT(0x83E87508A2CA2AC6);
lazy_func_t<void(Cam cam, float amplitude)>
	SET_CAM_SHAKE_AMPLITUDE(0xD93DB43B82BC0D00);
lazy_func_t<BOOL(float x, float y, float z, float radius)>
	IS_SPHERE_VISIBLE(0xE33D59DA70B58FDF);
lazy_func_t<void(BOOL p0, BOOL p1)> _0x271401846BD26E92(0x271401846BD26E92);
lazy_func_t<void(BOOL p0)> _0x91EF6EE6419E5B97(0x91EF6EE6419E5B97);
lazy_func_t<BOOL()> IS_AIM_CAM_ACTIVE(0x68EDDA28A5976D07);
lazy_func_t<BOOL()> _0x74BD83EA840F6BC9(0x74BD83EA840F6BC9);
lazy_func_t<void(Cam cam, BOOL p1)> STOP_CAM_SHAKING(0xBDECF64367884AC3);
lazy_func_t<BOOL()> IS_FIRST_PERSON_AIM_CAM_ACTIVE(0x5E346D934122613F);
lazy_func_t<void(Any p0)> _0x8BBACBF51DA047A8(0x8BBACBF51DA047A8);
lazy_func_t<void()> _0x9E4CFFF989258472(0x9E4CFFF989258472);
lazy_func_t<
	BOOL(Any p0, Any p1, const char *animName, const char *animDictionary)>
	PLAY_SYNCHRONIZED_CAM_ANIM(0xE32EFE9AB4A9AA0C);
lazy_func_t<void(Cam cam, float range)> _SET_CAMERA_RANGE(0xF9D02130ECDD1D77);
lazy_func_t<float()> GET_GAMEPLAY_CAM_RELATIVE_PITCH(0x3A6867B4845BEDA2);
lazy_func_t<void(BOOL p0)> _0x469F2ECDEC046337(0x469F2ECDEC046337);
lazy_func_t<Any(Vehicle p0, int p1)> _0xE9EA16D6E54CDCA4(0xE9EA16D6E54CDCA4);
lazy_func_t<void(
	Cam cam,
	float posX,
	float posY,
	float posZ,
	float rotX,
	float rotY,
	float rotZ,
	float fieldOfView,
	Any p8,
	int p9,
	int p10,
	int p11)>
	SET_CAM_PARAMS(0xBFD8727AEA3CCEBA);
lazy_func_t<
	void(Any p0, float p1, float p2, float p3, BOOL p4, Any p5, Any p6, Any p7)>
	SET_GAMEPLAY_VEHICLE_HINT(0xA2297E18F3E71C2E);
lazy_func_t<void(float p0)> _0xC92717EF615B6704(0xC92717EF615B6704);
lazy_func_t<void(
	Cam cam,
	Entity entity,
	float xOffset,
	float yOffset,
	float zOffset,
	BOOL isRelative)>
	ATTACH_CAM_TO_ENTITY(0xFEDB7D269E8C60E3);
lazy_func_t<void(const char *p0, float p1)>
	_0xF4C8CF9E353AFECA(0xF4C8CF9E353AFECA);
lazy_func_t<
	void(Ped p0, float x1, float y1, float z1, BOOL p4, Any p5, Any p6, Any p7)>
	SET_GAMEPLAY_PED_HINT(0x2B486269ACD548D3);
lazy_func_t<void(Cam cam, float nearClip)>
	SET_CAM_NEAR_CLIP(0xC7848EFCCC545182);
lazy_func_t<void(Cam cam, BOOL p1)>
	SET_CAM_INHERIT_ROLL_VEHICLE(0x45F1DE9C34B93AE6);
lazy_func_t<void(BOOL p0)> _0x4008EDF7D6E48175(0x4008EDF7D6E48175);
lazy_func_t<void(const char *p0, float p1)>
	SHAKE_CINEMATIC_CAM(0xDCE214D9ED58F3CF);
lazy_func_t<
	void(Cam cam, int ped, int boneIndex, float x, float y, float z, BOOL p6)>
	POINT_CAM_AT_PED_BONE(0x68B2B5F33BA63C41);
lazy_func_t<void(Any p0, BOOL p1)> _0x661B5C8654ADD825(0x661B5C8654ADD825);
lazy_func_t<void(float distance)>
	_SET_FIRST_PERSON_CAM_NEAR_CLIP(0x0AF7B437918103B3);
lazy_func_t<void(BOOL p0)> STOP_GAMEPLAY_HINT(0xF46C581C61718916);
lazy_func_t<void(float p0)> _0xF8BDBF3D573049A1(0xF8BDBF3D573049A1);
lazy_func_t<void()> _0x5A43C76F7FC7BA5F(0x5A43C76F7FC7BA5F);
lazy_func_t<void(Cam cam, float farDOF)> SET_CAM_FAR_DOF(0xEDD91296CD01AEE0);
lazy_func_t<void(float amplitude)>
	SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(0xA87E00932DB4D85D);
lazy_func_t<float(Cam cam)> GET_CAM_FAR_CLIP(0xB60A9CFEB21CA6AA);
lazy_func_t<Any()> _0x1F2300CB7FA7B7F6(0x1F2300CB7FA7B7F6);
lazy_func_t<void(Cam camera, const char *name)>
	SET_CAM_DEBUG_NAME(0x1B93E0107865DD40);
lazy_func_t<void(
	Cam camera,
	float x,
	float y,
	float z,
	float xRot,
	float yRot,
	float zRot,
	int length,
	int p8,
	int transitionType)>
	ADD_CAM_SPLINE_NODE(0x8609C75EC438FB3B);
lazy_func_t<void(const char *p0, const char *p1, const char *p2, float p3)>
	_0xC2EAE3FB8CDBED31(0xC2EAE3FB8CDBED31);
lazy_func_t<BOOL()> IS_SCREEN_FADING_IN(0x5C544BC6C57AC575);
lazy_func_t<void(BOOL p0)> _0xDB90C6CCA48940F1(0xDB90C6CCA48940F1);
lazy_func_t<void(float p0)> _0x12DED8CA53D47EA5(0x12DED8CA53D47EA5);
lazy_func_t<BOOL(Cam cam)> IS_CAM_ACTIVE(0xDFB2B516207D3534);
lazy_func_t<Vector3(Cam cam)> GET_CAM_COORD(0xBAC038F7459AE5AE);
lazy_func_t<void(Cam cam, float farClip)> SET_CAM_FAR_CLIP(0xAE306F2A904BF86E);
lazy_func_t<Any(float minimum, float maximum)>
	_CLAMP_GAMEPLAY_CAM_PITCH(0xA516C198B7DCA1E1);
lazy_func_t<void(Cam cam, float strength)>
	SET_CAM_MOTION_BLUR_STRENGTH(0x6F0F77FBA9A8F2E6);
lazy_func_t<int(Cam cam)> GET_CAM_SPLINE_NODE_INDEX(0xB22B17DF858716A6);
lazy_func_t<void()> DISABLE_AIM_CAM_THIS_UPDATE(0x1A31FE0049E542F6);
lazy_func_t<BOOL(Cam cam)> IS_CAM_RENDERING(0x02EC0AF5C5A49B7A);
lazy_func_t<void(Any p0)> _0xFD3151CD37EA2245(0xFD3151CD37EA2245);
lazy_func_t<float()> _0x162F9D995753DC19(0x162F9D995753DC19);
lazy_func_t<void(
	Entity entity,
	float xOffset,
	float yOffset,
	float zOffset,
	BOOL p4,
	int p5,
	int p6,
	int p7,
	Any p8)>
	SET_GAMEPLAY_ENTITY_HINT(0x189E955A8313E298);
lazy_func_t<void(Any p0, Any p1)> _0xD1B0F412F109EA5D(0xD1B0F412F109EA5D);
lazy_func_t<void(int duration)> DO_SCREEN_FADE_IN(0xD4E8E24955024033);
lazy_func_t<void(int duration)> DO_SCREEN_FADE_OUT(0x891B5B39AC6302AF);
lazy_func_t<void(Any p0)> STOP_CINEMATIC_SHOT(0x7660C6E75D3A078E);
lazy_func_t<int()> GET_FOLLOW_PED_CAM_ZOOM_LEVEL(0x33E6C8EFD0CD93E9);
lazy_func_t<void(float p0, float p1)> _0x2F7F2B26DD3F18EE(0x2F7F2B26DD3F18EE);
lazy_func_t<float()> _0xD0082607100D7193(0xD0082607100D7193);
lazy_func_t<BOOL()> IS_GAMEPLAY_CAM_SHAKING(0x016C090630DF1F89);
lazy_func_t<BOOL()> IS_SCREEN_FADED_OUT(0xB16FCE9DDC7BA182);
lazy_func_t<BOOL()> IS_FOLLOW_PED_CAM_ACTIVE(0xC6D3D26810C8E0F9);
lazy_func_t<void(BOOL p0)> _0xCCD078C2665D2973(0xCCD078C2665D2973);
lazy_func_t<BOOL()> IS_CINEMATIC_CAM_SHAKING(0xBBC08F6B4CB8FF0A);
lazy_func_t<void(BOOL render, BOOL ease, int easeTime, BOOL p3, BOOL p4)>
	RENDER_SCRIPT_CAMS(0x07E5B515DB0636FC);
lazy_func_t<float()> _GET_GAMEPLAY_CAM_NEAR_DOF(0xA03502FC581F7D9B);
lazy_func_t<void(BOOL p0)> _0xA41BCD7213805AAC(0xA41BCD7213805AAC);
lazy_func_t<void()> _ENABLE_CROSSHAIR_THIS_FRAME(0xEA7F0AD7E9BA676F);
}} // namespace CAM::
namespace SYSTEM { namespace {
lazy_func_t<int(const char *scriptName, Any *args, int argCount, int stackSize)>
	START_NEW_SCRIPT_WITH_ARGS(0xB8BA7F44DF1575E1);
lazy_func_t<int()> TIMERA(0x83666F9FB8FEBD4B);
lazy_func_t<float(float value)> COS(0xD0FFB162F40A139C);
lazy_func_t<float(float x, float y, float z)> VMAG(0x652D2EEEF1D3E62C);
lazy_func_t<int(float value)> CEIL(0x11E019C8F43ACC8A);
lazy_func_t<void(int *ms)> WAIT(0x4EDE34FBADD967A6);
lazy_func_t<float(float value)> SQRT(0x71D93B57D07F9804);
lazy_func_t<float(float x, float y, float z)> VMAG2(0xA8CEACB4F35AE058);
lazy_func_t<float(float x1, float y1, float z1, float x2, float y2, float z2)>
	VDIST(0x2A488C176D52CCA5);
lazy_func_t<int(int value, int bitShift)> SHIFT_LEFT(0xEDD95A39E5544DE8);
lazy_func_t<int(float value)> FLOOR(0xF34EE736CF047844);
lazy_func_t<int(Hash scriptHash, int stackSize)>
	START_NEW_SCRIPT_WITH_NAME_HASH(0xEB1C67C3A5333A92);
lazy_func_t<int(Hash scriptHash, Any *args, int argCount, int stackSize)>
	START_NEW_SCRIPT_WITH_NAME_HASH_AND_ARGS(0xC4BB298BD441BE78);
lazy_func_t<int()> TIMERB(0xC9D9444186B5A374);
lazy_func_t<void(int value)> SETTIMERA(0xC1B1E9A034A63A62);
lazy_func_t<void(int value)> SETTIMERB(0x5AE11BC36633DE4E);
lazy_func_t<float(float base, float exponent)> POW(0xE3621CC40F31FE2E);
lazy_func_t<float(float x1, float y1, float z1, float x2, float y2, float z2)>
	VDIST2(0xB7A628320EFF8E47);
lazy_func_t<int(const char *scriptName, int stackSize)>
	START_NEW_SCRIPT(0xE81651AD79516E48);
lazy_func_t<float()> TIMESTEP(0x0000000050597EE2);
lazy_func_t<float(float value)> SIN(0x0BADBFA3B172435F);
lazy_func_t<int(int value, int bitShift)> SHIFT_RIGHT(0x97EF1E5BCE9DC075);
lazy_func_t<int(float value)> ROUND(0xF2DB717A73826179);
lazy_func_t<float(int value)> TO_FLOAT(0xBBDA792448DB5A89);
}} // namespace SYSTEM::
namespace STREAMING { namespace {
lazy_func_t<void(Hash model)> SET_MODEL_AS_NO_LONGER_NEEDED(0xE532F5D78798DAAB);
lazy_func_t<void(BOOL p0)> _0x20C6C7E4EB082A7F(0x20C6C7E4EB082A7F);
lazy_func_t<BOOL()> IS_NETWORK_LOADING_SCENE(0x41CA5A33160EA4AB);
lazy_func_t<int()> GET_PLAYER_SWITCH_TYPE(0xB3C94A90D9FC9E62);
lazy_func_t<void(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	Any p8)>
	SET_PLAYER_SWITCH_OUTRO(0xC208B673CE446B61);
lazy_func_t<Any()> DESTROY_PLAYER_IN_PAUSE_MENU(0x5B74EA8CFD5E3E7E);
lazy_func_t<Any()> _0x0C15B0E443B2349D(0x0C15B0E443B2349D);
lazy_func_t<void(const char *animDict)> REMOVE_ANIM_DICT(0xF66A602F829E2A06);
lazy_func_t<void(
	float x, float y, float z, float offsetX, float offsetY, float offsetZ)>
	_SET_FOCUS_AREA(0xBB7454BAFF08FE25);
lazy_func_t<int(float x1, float y1, float z1, float x2, float y2, float z2)>
	GET_IDEAL_PLAYER_SWITCH_TYPE(0xB5D7B26B45720E05);
lazy_func_t<Any()> _0xFB199266061F820A(0xFB199266061F820A);
lazy_func_t<void()> NETWORK_STOP_LOAD_SCENE(0x64E630FAF5F60F44);
lazy_func_t<void(BOOL toggle)>
	SET_GAME_PAUSES_FOR_STREAMING(0x717CD6E6FAEBBEDC);
lazy_func_t<void(Ped from, Ped to, int flags, int switchType)>
	START_PLAYER_SWITCH(0xFAA23F2CBA159D67);
lazy_func_t<Vector3 *()> NETWORK_UPDATE_LOAD_SCENE(0xC4582015556D1C46);
lazy_func_t<BOOL(Hash model)>
	HAS_COLLISION_FOR_MODEL_LOADED(0x22CCA434E368F03A);
lazy_func_t<BOOL()> IS_SRL_LOADED(0xD0263801A4C5B0BB);
lazy_func_t<void()> END_SRL(0x0A41540E63C9EE17);
lazy_func_t<void()> CLEAR_HD_AREA(0xCE58B1CFB9290813);
lazy_func_t<void()> CLEAR_FOCUS(0x31B73D1EA9F01DA2);
lazy_func_t<Any(float x, float y, float z, float rad, Any p4, Any p5)>
	FORMAT_FOCUS_HEADING(0x219C7B8D53E429FD);
lazy_func_t<void()> _0x03F1A106BDA7DD3E(0x03F1A106BDA7DD3E);
lazy_func_t<BOOL(Hash model)> HAS_MODEL_LOADED(0x98A4EB5D89A0C952);
lazy_func_t<void(const char *clipSet)> REMOVE_CLIP_SET(0x01F73A131C18CD94);
lazy_func_t<void(float p0)> SET_SRL_TIME(0xA74A541C6884E7B8);
lazy_func_t<BOOL(const char *animDict)>
	DOES_ANIM_DICT_EXIST(0x2DA49C3B79856961);
lazy_func_t<void()> _0x8E2A065ABDAE6994(0x8E2A065ABDAE6994);
lazy_func_t<void()> NEW_LOAD_SCENE_STOP(0xC197616D221FF4A4);
lazy_func_t<BOOL()> IS_NEW_LOAD_SCENE_LOADED(0x01B8247A7A8B9AD1);
lazy_func_t<void()> _0x43D1680C6D19A8E9(0x43D1680C6D19A8E9);
lazy_func_t<void()> BEGIN_SRL(0x9BADDC94EF83B823);
lazy_func_t<void(Hash model)> REQUEST_MENU_PED_MODEL(0xA0261AEF7ACFC51E);
lazy_func_t<void(int interiorID, const char *roomName)>
	_REQUEST_INTERIOR_ROOM_BY_NAME(0x8A7A40100EDFEC58);
lazy_func_t<
	Any(float p0, float p1, float p2, float p3, float p4, float p5, Any p6)>
	_0x0AD9710CEE2F590F(0x0AD9710CEE2F590F);
lazy_func_t<void()> _0xBD605B8E0E18B3BB(0xBD605B8E0E18B3BB);
lazy_func_t<void(const char *animDict)> REQUEST_ANIM_DICT(0xD3BD40951412FEF6);
lazy_func_t<void(const char *assetName)>
	_REMOVE_NAMED_PTFX_ASSET(0x5F61EBBE1A00F96D);
lazy_func_t<BOOL()> IS_NEW_LOAD_SCENE_ACTIVE(0xA41A05B6CB741B85);
lazy_func_t<void()> _0xD4793DFF3AF2ABCD(0xD4793DFF3AF2ABCD);
lazy_func_t<int()> SET_PLAYER_INVERTED_UP(0x08C2D6C52A3104BB);
lazy_func_t<void(Any *p0, Any *p1)> _0x95A7DABDDBB78AE7(0x95A7DABDDBB78AE7);
lazy_func_t<void(Hash model)> REQUEST_MODEL(0x963D27A58DF860AC);
lazy_func_t<BOOL(const char *animDict)>
	HAS_ANIM_DICT_LOADED(0xD031A9162D01088C);
lazy_func_t<void(const char *iplName)> REQUEST_IPL(0x41B4893843BBDB74);
lazy_func_t<void()> _0x472397322E92A856(0x472397322E92A856);
lazy_func_t<int()> GET_NUMBER_OF_STREAMING_REQUESTS(0x4060057271CEBC89);
lazy_func_t<void(int p0)> SET_VEHICLE_POPULATION_BUDGET(0xCB9E1EB3BE2AF4E9);
lazy_func_t<BOOL()> IS_PLAYER_SWITCH_IN_PROGRESS(0xD9D2CFFF49FAB35F);
lazy_func_t<Any()> _0x78C0D93253149435(0x78C0D93253149435);
lazy_func_t<void(float p0)> _0xA76359FC80B2438E(0xA76359FC80B2438E);
lazy_func_t<BOOL(Hash model)> IS_MODEL_A_VEHICLE(0x19AAC8F07BFEC53E);
lazy_func_t<void(BOOL toggle)>
	SET_REDUCE_VEHICLE_MODEL_BUDGET(0x80C527893080CCF3);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_FOCUS(0x2DDFF3FB9075D747);
lazy_func_t<Any(Any p0)> _0x7D41E9D2D17C5B2D(0x7D41E9D2D17C5B2D);
lazy_func_t<void(Any p0)> _0xD8295AF639FD9CB8(0xD8295AF639FD9CB8);
lazy_func_t<void()> _0xF4A0DADB70F57FA6(0xF4A0DADB70F57FA6);
lazy_func_t<BOOL(Hash model)> IS_MODEL_VALID(0xC0296A2EDF545E92);
lazy_func_t<void(float x, float y, float z)>
	REQUEST_ADDITIONAL_COLLISION_AT_COORD(0xC9156DC11411A9EA);
lazy_func_t<void(Entity p0)> _0x0811381EF5062FEC(0x0811381EF5062FEC);
lazy_func_t<void()> _0x63EB2B972A218CAC(0x63EB2B972A218CAC);
lazy_func_t<void(float x, float y, float z, float radius)>
	SET_HD_AREA(0xB85F26619073E775);
lazy_func_t<void()> SHUTDOWN_CREATOR_BUDGET(0xCCE26000E9A6FAD7);
lazy_func_t<void(int interiorID, BOOL toggle)>
	SET_INTERIOR_ACTIVE(0xE37B76C387BE28ED);
lazy_func_t<BOOL(const char *clipSet)> HAS_CLIP_SET_LOADED(0x318234F4F3738AF3);
lazy_func_t<Any()> _0x5B48A06DD0E792A5(0x5B48A06DD0E792A5);
lazy_func_t<void(Any *p0)> _0x0FDE9DBFC0A6BC65(0x0FDE9DBFC0A6BC65);
lazy_func_t<Any()> _0x933BBEEB8C61B5F4(0x933BBEEB8C61B5F4);
lazy_func_t<void(Hash model)> REQUEST_COLLISION_FOR_MODEL(0x923CB32A3B874FCB);
lazy_func_t<void(const char *assetName)>
	REQUEST_NAMED_PTFX_ASSET(0xB80D8756B4668AB6);
lazy_func_t<BOOL(float x, float y, float z, float radius, Any p4)>
	NEW_LOAD_SCENE_START_SPHERE(0xACCFB4ACF53551B0);
lazy_func_t<void()> _0xAD5FDF34B81BFE79(0xAD5FDF34B81BFE79);
lazy_func_t<void(const char *srl)> PREFETCH_SRL(0x3D245789CE12982C);
lazy_func_t<Any()> _0x3D3D8B3BE5A83D35(0x3D3D8B3BE5A83D35);
lazy_func_t<void(BOOL toggle)> SET_REDUCE_PED_MODEL_BUDGET(0x77B5F9A36BF96710);
lazy_func_t<Any()> REQUEST_PTFX_ASSET(0x944955FB2A3935C8);
lazy_func_t<void(Entity entity)> SET_FOCUS_ENTITY(0x198F77705FA0931D);
lazy_func_t<BOOL(Hash modelHash)> _0x0BC3144DEB678666(0x0BC3144DEB678666);
lazy_func_t<void(float x, float y, float z)> LOAD_SCENE(0x4448EB75B4904BDB);
lazy_func_t<Any(Any p0)> _0x07C313F94746702C(0x07C313F94746702C);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0xBEB2D9A1D9A8F55A(0xBEB2D9A1D9A8F55A);
lazy_func_t<BOOL(const char *animSet)> HAS_ANIM_SET_LOADED(0xC4EA073D86FB29B0);
lazy_func_t<void()> LOAD_ALL_OBJECTS_NOW(0xBD6E84632DD4CB3F);
lazy_func_t<void(BOOL toggle)> SET_STREAMING(0x6E0C692677008888);
lazy_func_t<void()> _LOAD_MISSION_CREATOR_DATA(0xB5A4DB34FE89B88A);
lazy_func_t<void(Any p0)> _0xF086AD9354FAC3A3(0xF086AD9354FAC3A3);
lazy_func_t<Any()> _0x71E7B2E657449AAD(0x71E7B2E657449AAD);
lazy_func_t<int()> GET_PLAYER_SWITCH_STATE(0x470555300D10B2A5);
lazy_func_t<void(int p0)> _0x5F2013F8BC24EE69(0x5F2013F8BC24EE69);
lazy_func_t<void(const char *p0, BOOL p1)>
	_0xAF12610C644A35C9(0xAF12610C644A35C9);
lazy_func_t<Any()> _0xBC9823AB80A3DCAC(0xBC9823AB80A3DCAC);
lazy_func_t<Any()> _0xDFA80CB25D0A19B3(0xDFA80CB25D0A19B3);
lazy_func_t<void(Any p0)> _0xF8155A7F03DDFC8E(0xF8155A7F03DDFC8E);
lazy_func_t<void(const char *iplName)> REMOVE_IPL(0xEE6C5AD3ECE0A82D);
lazy_func_t<BOOL()> HAS_PTFX_ASSET_LOADED(0xCA7D9B86ECA7481B);
lazy_func_t<void()> REMOVE_PTFX_ASSET(0x88C6814073DD4A73);
lazy_func_t<Any(float x, float y, float z)>
	REQUEST_COLLISION_AT_COORD(0x07503F7948F491A7);
lazy_func_t<void(const char *clipSet)> REQUEST_CLIP_SET(0xD2A71E1A77418A49);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	Any p7)>
	NEW_LOAD_SCENE_START(0x212A8D0D2BABFAC2);
lazy_func_t<int()> GET_PLAYER_SHORT_SWITCH_STATE(0x20F898A5D9782800);
lazy_func_t<void()> _0x74DE2E8739086740(0x74DE2E8739086740);
lazy_func_t<void(float p0, float p1, float p2, float p3)>
	_0xBED8CA5FF5E04113(0xBED8CA5FF5E04113);
lazy_func_t<void(const char *animSet)> REQUEST_ANIM_SET(0x6EA47DAE7FAD0EED);
lazy_func_t<BOOL(const char *assetName)>
	HAS_NAMED_PTFX_ASSET_LOADED(0x8702416E512EC454);
lazy_func_t<void(Any p0)> _0x4E52E752C76E7E7A(0x4E52E752C76E7E7A);
lazy_func_t<void()> _0x1E9057A74FD73E23(0x1E9057A74FD73E23);
lazy_func_t<Any()> _0x5068F488DDB54DD8(0x5068F488DDB54DD8);
lazy_func_t<BOOL(Hash model)> IS_MODEL_IN_CDIMAGE(0x35B9E0803292B641);
lazy_func_t<void(int p0)> SET_PED_POPULATION_BUDGET(0x8C95333CFC3340F3);
lazy_func_t<
	Any(float p0,
		float p1,
		float p2,
		float p3,
		float p4,
		float p5,
		float p6,
		Any p7,
		Any p8)>
	_0x1F3F018BC3AFA77C(0x1F3F018BC3AFA77C);
lazy_func_t<void(Ped ped, int flags, int unknown)>
	_SWITCH_OUT_PLAYER(0xAAB3200ED59016BC);
lazy_func_t<void(BOOL p0)> _0x40AEFD1A244741F2(0x40AEFD1A244741F2);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	_0xEF39EE20C537E98C(0xEF39EE20C537E98C);
lazy_func_t<void(const char *animSet)> REMOVE_ANIM_SET(0x16350528F93024B3);
lazy_func_t<void(BOOL toggle)> SET_DITCH_POLICE_MODELS(0x42CBE54462D92634);
lazy_func_t<void()> STOP_PLAYER_SWITCH(0x95C0A5BBDC189AA1);
lazy_func_t<BOOL(const char *iplName)> IS_IPL_ACTIVE(0x88A741E44A2B3495);
lazy_func_t<void(Any p0)> _0x1EE7D8DF4425F053(0x1EE7D8DF4425F053);
}} // namespace STREAMING::
namespace WORLDPROBE { namespace {
lazy_func_t<
	int(float x1,
		float y1,
		float z1,
		float x2,
		float y2,
		float z2,
		float radius,
		int flags,
		Entity entity,
		Any p9)>
	_START_SHAPE_TEST_CAPSULE_2(0xE6AC6C45FBE83004);
lazy_func_t<void(Hash entityHit)> _SHAPE_TEST_RESULT_ENTITY(0x2B3334BCA57CD799);
lazy_func_t<
	int(float x1,
		float y1,
		float z1,
		float x2,
		float y2,
		float z2,
		int flags,
		Entity entity,
		int p8)>
	_START_SHAPE_TEST_RAY(0x377906D8A31E5586);
lazy_func_t<int(Entity entity, int flags1, int flags2)>
	START_SHAPE_TEST_BOUNDING_BOX(0x052837721A854EC7);
lazy_func_t<
	int(float x1,
		float y1,
		float z1,
		float x2,
		float y2,
		float z2,
		float radius,
		int flags,
		Entity entity,
		int p9)>
	START_SHAPE_TEST_CAPSULE(0x28579D1B8F8AAC80);
lazy_func_t<
	int(Vector3 *pVec1, Vector3 *pVec2, int flag, Entity entity, int flag2)>
	_START_SHAPE_TEST_SURROUNDING_COORDS(0xFF6BE494C7987F34);
lazy_func_t<
	int(int rayHandle,
		BOOL *hit,
		Vector3 *endCoords,
		Vector3 *surfaceNormal,
		Entity *entityHit)>
	GET_SHAPE_TEST_RESULT(0x3D87450E15D98694);
lazy_func_t<
	int(int rayHandle,
		BOOL *hit,
		Vector3 *endCoords,
		Vector3 *surfaceNormal,
		Hash *materialHash,
		Entity *entityHit)>
	_GET_SHAPE_TEST_RESULT_EX(0x65287525D951F6BE);
lazy_func_t<
	int(float x1,
		float y1,
		float z1,
		float x2,
		float y2,
		float z2,
		int flags,
		Entity ent,
		int p8)>
	START_SHAPE_TEST_LOS_PROBE(0x7EE9F5D83DD4F90E);
lazy_func_t<
	int(float x,
		float y,
		float z,
		float x1,
		float y2,
		float z2,
		float rotX,
		float rotY,
		float rotZ,
		Any p9,
		Any p10,
		Any entity,
		Any p12)>
	START_SHAPE_TEST_BOX(0xFE466162C4401D18);
lazy_func_t<int(Entity entity, int flags1, int flags2)>
	START_SHAPE_TEST_BOUND(0x37181417CE7C8900);
}} // namespace WORLDPROBE::
namespace DATAFILE { namespace {
lazy_func_t<int(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_TYPE(0x031C55ED33227371);
lazy_func_t<int(Any *arrayData, int arrayIndex)>
	_ARRAY_VALUE_GET_TYPE(0x3A0014ADB172A3C5);
lazy_func_t<BOOL(Any p0)> _0x8F5EA1C01D65A100(0x8F5EA1C01D65A100);
lazy_func_t<BOOL(int p0, BOOL p1)> _0x9CB0BFA7A9342C3D(0x9CB0BFA7A9342C3D);
lazy_func_t<BOOL(BOOL *p0)> _0x4DFDD9EB705F8140(0x4DFDD9EB705F8140);
lazy_func_t<const char *(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_STRING(0x3D2FD9E763B24472);
lazy_func_t<void(
	Any *objectData, const char *key, float valueX, float valueY, float valueZ)>
	_OBJECT_VALUE_ADD_VECTOR3(0x4CD49B76338C7DEE);
lazy_func_t<void(Any *arrayData, int value)>
	_ARRAY_VALUE_ADD_INTEGER(0xCABDB751D86FE93B);
lazy_func_t<Vector3(Any *arrayData, int arrayIndex)>
	_ARRAY_VALUE_GET_VECTOR3(0x8D2064E5B64A628A);
lazy_func_t<void(Blip x)> _0xAD6875BBC0FC899C(0xAD6875BBC0FC899C);
lazy_func_t<BOOL(
	const char *p0, const char *p1, const char *p2, const char *p3, BOOL p4)>
	_0xA5EFC3E847D60507(0xA5EFC3E847D60507);
lazy_func_t<void()> DATAFILE_CREATE(0xD27058A1CA2B13EE);
lazy_func_t<BOOL(const char *filename)> _0x83BCCE3224735F05(0x83BCCE3224735F05);
lazy_func_t<BOOL(Any p0)> _0xFCCAE5B92A830878(0xFCCAE5B92A830878);
lazy_func_t<void()> DATAFILE_DELETE(0x9AB9C1CFC8862DFB);
lazy_func_t<void(Any *objectData, const char *key, BOOL value)>
	_OBJECT_VALUE_ADD_BOOLEAN(0x35124302A556A325);
lazy_func_t<void(Any *objectData, const char *key, float value)>
	_OBJECT_VALUE_ADD_FLOAT(0xC27E1CC2D795105E);
lazy_func_t<BOOL(const char *p0, float p1, const char *type)>
	_0x692D808C34A82143(0x692D808C34A82143);
lazy_func_t<BOOL(int p0)> _0xA69AC4ADE82B57A4(0xA69AC4ADE82B57A4);
lazy_func_t<BOOL(const char *filename)> _LOAD_UGC_FILE(0xC5238C011AF405E4);
lazy_func_t<float(Any *arrayData, int arrayIndex)>
	_ARRAY_VALUE_GET_FLOAT(0xC0C527B525D7CFB5);
lazy_func_t<const char *(Any *arrayData, int arrayIndex)>
	_ARRAY_VALUE_GET_STRING(0xD3F2FFEB8D836F52);
lazy_func_t<BOOL(Any p0)> _0xF8CC1EBE0B62E29F(0xF8CC1EBE0B62E29F);
lazy_func_t<BOOL(
	const char *p0,
	BOOL p1,
	const char *p2,
	Any *p3,
	Any *p4,
	const char *type,
	BOOL p6)>
	_0xC84527E235FCA219(0xC84527E235FCA219);
lazy_func_t<void()> _0x2ED61456317B8178(0x2ED61456317B8178);
lazy_func_t<void(Any *arrayData, float valueX, float valueY, float valueZ)>
	_ARRAY_VALUE_ADD_VECTOR3(0x407F8D034F70F0C2);
lazy_func_t<void(Any *objectData, const char *key, int value)>
	_OBJECT_VALUE_ADD_INTEGER(0xE7E035450A7948D5);
lazy_func_t<Any *(Any *objectData, const char *key)>
	_OBJECT_VALUE_ADD_OBJECT(0xA358F56F10732EE1);
lazy_func_t<Any *(Any *arrayData)> _ARRAY_VALUE_ADD_OBJECT(0x6889498B3E19C797);
lazy_func_t<Any *(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_ARRAY(0x7A983AA9DA2659ED);
lazy_func_t<void(Any *arrayData, BOOL value)>
	_ARRAY_VALUE_ADD_BOOLEAN(0xF8B0F5A43E928C76);
lazy_func_t<int(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_INTEGER(0x78F06F6B1FB5A80C);
lazy_func_t<int(Any *arrayData)> _ARRAY_VALUE_GET_SIZE(0x065DB281590CEA2D);
lazy_func_t<void()> _0x6CC86E78358D5119(0x6CC86E78358D5119);
lazy_func_t<BOOL(
	const char *p0,
	Any *p1,
	BOOL p2,
	Any *p3,
	Any *p4,
	Any *p5,
	const char *type)>
	_0x648E7A5434AF7969(0x648E7A5434AF7969);
lazy_func_t<float(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_FLOAT(0x06610343E73B9727);
lazy_func_t<Any *(Any *arrayData, int arrayIndex)>
	_ARRAY_VALUE_GET_OBJECT(0x8B5FADCC4E3A145F);
lazy_func_t<void(Any *objectData, const char *key, const char *value)>
	_OBJECT_VALUE_ADD_STRING(0x8FF3847DADD8E30C);
lazy_func_t<BOOL(int p0)> _0x52818819057F2B40(0x52818819057F2B40);
lazy_func_t<BOOL(
	const char *p0,
	const char *p1,
	const char *p2,
	const char *p3,
	const char *type)>
	_0x4645DE9980999E93(0x4645DE9980999E93);
lazy_func_t<BOOL()> DATAFILE_IS_SAVE_PENDING(0xBEDB96A7584AA8CF);
lazy_func_t<int(Any *arrayData, int arrayIndex)>
	_ARRAY_VALUE_GET_INTEGER(0x3E5AE19425CD74BE);
lazy_func_t<BOOL(Any p0)> _0x22DA66936E0FFF37(0x22DA66936E0FFF37);
lazy_func_t<BOOL(int p0)> _0x01095C95CD46B624(0x01095C95CD46B624);
lazy_func_t<void()> _0xC55854C7D7274882(0xC55854C7D7274882);
lazy_func_t<BOOL(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_BOOLEAN(0x1186940ED72FFEEC);
lazy_func_t<Any *(Any *objectData, const char *key)>
	_OBJECT_VALUE_ADD_ARRAY(0x5B11728527CA6E5F);
lazy_func_t<Any *(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_OBJECT(0xB6B9DDC412FCEEE2);
lazy_func_t<void(Any *arrayData, const char *value)>
	_ARRAY_VALUE_ADD_STRING(0x2F0661C155AEEEAA);
lazy_func_t<void(Any *arrayData, float value)>
	_ARRAY_VALUE_ADD_FLOAT(0x57A995FD75D37F56);
lazy_func_t<BOOL(Any *arrayData, int arrayIndex)>
	_ARRAY_VALUE_GET_BOOLEAN(0x50C1B2874E50C114);
lazy_func_t<BOOL(Any p0)> _0x15FF52B809DB2353(0x15FF52B809DB2353);
lazy_func_t<const char *()> DATAFILE_GET_FILE_DICT(0x906B778CA1DC72B6);
lazy_func_t<Vector3(Any *objectData, const char *key)>
	_OBJECT_VALUE_GET_VECTOR3(0x46CD3CB66E0825CC);
}} // namespace DATAFILE::
namespace ROPE { namespace {
lazy_func_t<Any(Object rope, int vertex)> UNPIN_ROPE_VERTEX(0x4B5AE2EEE4A8F180);
lazy_func_t<Any()> ROPE_LOAD_TEXTURES(0x9B9039DBF2D258C1);
lazy_func_t<void(
	Any p0,
	Any p1,
	Any p2,
	Any p3,
	Any p4,
	Any p5,
	Any p6,
	Any p7,
	Any p8,
	Any p9,
	Any p10,
	Any p11,
	Any p12,
	Any p13)>
	_0xBC0CE682D4D05650(0xBC0CE682D4D05650);
lazy_func_t<void(Object rope, float x, float y, float z)>
	SET_CGOFFSET(0xD8FA3908D7B86904);
lazy_func_t<Vector3(Object rope)> GET_CGOFFSET(0x8214A4B5A7A33612);
lazy_func_t<void(Object rope)> ROPE_CONVERT_TO_SIMPLE(0x5389D48EFA2F079A);
lazy_func_t<BOOL(Object rope)> _0x271C9D3ACA5D6409(0x271C9D3ACA5D6409);
lazy_func_t<BOOL(Object *rope)> DOES_ROPE_EXIST(0xFD5448BE3111ED96);
lazy_func_t<int(Object rope)> GET_ROPE_VERTEX_COUNT(0x3655F544CD30F0B5);
lazy_func_t<void(
	Object rope,
	Entity ent1,
	Entity ent2,
	float ent1_x,
	float ent1_y,
	float ent1_z,
	float ent2_x,
	float ent2_y,
	float ent2_z,
	float length,
	BOOL p10,
	BOOL p11,
	const char *boneName1,
	const char *boneName2)>
	ATTACH_ENTITIES_TO_ROPE(0x3D95EC8B6D940AC3);
lazy_func_t<BOOL(Any *p0)> _0x84DE3B5FB3E666F0(0x84DE3B5FB3E666F0);
lazy_func_t<Any(Object rope)> GET_ROPE_LAST_VERTEX_COORD(0x21BB0FBD3E217C2D);
lazy_func_t<void(Object object, BOOL toggle)>
	SET_DISABLE_FRAG_DAMAGE(0x01BA3AED21C16CFB);
lazy_func_t<void(Object rope, int vertex, float x, float y, float z)>
	PIN_ROPE_VERTEX(0x2B320CF14146B69A);
lazy_func_t<Any(Object rope, int vertex)>
	GET_ROPE_VERTEX_COORD(0xEA61CA8E80F09E4D);
lazy_func_t<void(Object rope)> START_ROPE_UNWINDING_FRONT(0x538D1179EC1AA9A9);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	_0xB1B6216CA2E7B55E(0xB1B6216CA2E7B55E);
lazy_func_t<void(Object rope)> SET_CG_AT_BOUNDCENTER(0xBE520D9761FF811F);
lazy_func_t<void(Any p0, BOOL p1)> _0x36CCB9BE67B970FD(0x36CCB9BE67B970FD);
lazy_func_t<void(Object rope)> START_ROPE_WINDING(0x1461C72C889E343E);
lazy_func_t<void(Any p0, Any p1)> _0xB743F735C03D7810(0xB743F735C03D7810);
lazy_func_t<Any(Object rope, BOOL enabled)>
	SET_DISABLE_BREAKING(0x5CEC1A84620E7D5B);
lazy_func_t<void(Any p0)> _0xCC6E963682533882(0xCC6E963682533882);
lazy_func_t<Object(
	float x,
	float y,
	float z,
	float rotX,
	float rotY,
	float rotZ,
	float length,
	int ropeType,
	float maxLength,
	float minLength,
	float p10,
	BOOL p11,
	BOOL p12,
	BOOL rigid,
	float p14,
	BOOL breakWhenShot,
	Any *unkPtr)>
	ADD_ROPE(0xE832D760399EB220);
lazy_func_t<Any(Object rope)> DELETE_CHILD_ROPE(0xAA5D6B1888E4DB20);
lazy_func_t<void(Object rope)> ROPE_SET_UPDATE_PINVERTS(0xC8D667EE52114ABA);
lazy_func_t<BOOL()> ROPE_ARE_TEXTURES_LOADED(0xF2D0E6A75CC05597);
lazy_func_t<void(Object rope, int vertex, float value)>
	SET_DAMPING(0xEEA3B200A6FEB65B);
lazy_func_t<Any(Object rope, const char *rope_preset)>
	LOAD_ROPE_DATA(0xCBB203C04D1ABD27);
lazy_func_t<void(Object rope, Entity entity)>
	DETACH_ROPE_FROM_ENTITY(0xBCF3026912A8647D);
lazy_func_t<void(Any p0, Any p1)> _0xDC57A637A20006ED(0xDC57A637A20006ED);
lazy_func_t<void(Object rope)> STOP_ROPE_WINDING(0xCB2D4AB84A19AA7C);
lazy_func_t<void(Object *rope, BOOL toggle)>
	ROPE_DRAW_SHADOW_ENABLED(0xF159A63806BB5BA8);
lazy_func_t<
	void(Object rope, Entity entity, float x, float y, float z, BOOL p5)>
	ATTACH_ROPE_TO_ENTITY(0x4B490A6832559A65);
lazy_func_t<void(Object rope)> STOP_ROPE_UNWINDING_FRONT(0xFFF3A50779EFBBB3);
lazy_func_t<Any(Object rope, float length)>
	ROPE_FORCE_LENGTH(0xD009F759A723DB1B);
lazy_func_t<void(
	Any p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	Any p9,
	BOOL p10)>
	BREAK_ENTITY_GLASS(0x2E648D16F6E308F3);
lazy_func_t<void(Entity entity)> ACTIVATE_PHYSICS(0x710311ADF0E20730);
lazy_func_t<void(Object *rope)> DELETE_ROPE(0x52B4829281364649);
lazy_func_t<Any()> ROPE_UNLOAD_TEXTURES(0x6CE36C35C1AC8163);
lazy_func_t<float(Object rope)> _GET_ROPE_LENGTH(0x73040398DFF9A4A6);
lazy_func_t<void(Object rope, float length)>
	ROPE_RESET_LENGTH(0xC16DE94D9BEA14A0);
lazy_func_t<void(
	float posX,
	float posY,
	float posZ,
	float vecX,
	float vecY,
	float vecZ,
	float impulse)>
	APPLY_IMPULSE_TO_CLOTH(0xE37F721824571784);
}} // namespace ROPE::
namespace WATER { namespace {
lazy_func_t<BOOL(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	Vector3 *result)>
	TEST_PROBE_AGAINST_WATER(0xFFA5D878809819DB);
lazy_func_t<BOOL(float x, float y, float z, Any p3, float *height)>
	TEST_VERTICAL_PROBE_AGAINST_ALL_WATER(0x2B3451FA1E3142E2);
lazy_func_t<void(int p0)> _REMOVE_CURRENT_RISE(0xB1252E3E59A82AAF);
lazy_func_t<void(float intensity)> _SET_CURRENT_INTENSITY(0xB96B00E976BE977F);
lazy_func_t<float()> _GET_CURRENT_INTENSITY(0x2B2A2CC86778B619);
lazy_func_t<BOOL(float x, float y, float z, float *height)>
	GET_WATER_HEIGHT(0xF6829842C06AE524);
lazy_func_t<
	BOOL(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7)>
	TEST_PROBE_AGAINST_ALL_WATER(0x8974647ED222EA5F);
lazy_func_t<void(float x, float y, float radius, float height)>
	MODIFY_WATER(0xC443FD757C3BA637);
lazy_func_t<int(float xLow, float yLow, float xHigh, float yHigh, float height)>
	_ADD_CURRENT_RISE(0xFDBF4CDBC07E1706);
lazy_func_t<void()> _RESET_CURRENT_INTENSITY(0x5E5E99285AE812DB);
lazy_func_t<BOOL(float x, float y, float z, float *height)>
	GET_WATER_HEIGHT_NO_WAVES(0x8EE6B53CE13A9794);
}} // namespace WATER::
namespace DECORATOR { namespace {
lazy_func_t<BOOL(Entity entity, const char *propertyName, int value)>
	DECOR_SET_INT(0x0CE3AA5E1CA19E10);
lazy_func_t<float(Entity entity, const char *propertyName)>
	_DECOR_GET_FLOAT(0x6524A2F114706F43);
lazy_func_t<void(const char *propertyName, int type)>
	DECOR_REGISTER(0x9FD90732F56403CE);
lazy_func_t<BOOL()> _0x241FCA5B1AA14F75(0x241FCA5B1AA14F75);
lazy_func_t<BOOL(Entity entity, const char *propertyName)>
	DECOR_EXIST_ON(0x05661B80A8C9165F);
lazy_func_t<BOOL(Entity entity, const char *propertyName)>
	DECOR_REMOVE(0x00EE9F297C738720);
lazy_func_t<BOOL(const char *propertyName, int type)>
	DECOR_IS_REGISTERED_AS_TYPE(0x4F14F9F870D6FBC8);
lazy_func_t<BOOL(Entity entity, const char *propertyName, int timestamp)>
	DECOR_SET_TIME(0x95AED7B8E39ECAA4);
lazy_func_t<BOOL(Entity entity, const char *propertyName, BOOL value)>
	DECOR_SET_BOOL(0x6B1E8E2ED1335B71);
lazy_func_t<BOOL(Entity entity, const char *propertyName, float value)>
	_DECOR_SET_FLOAT(0x211AB1DD8D0F363A);
lazy_func_t<BOOL(Entity entity, const char *propertyName)>
	DECOR_GET_BOOL(0xDACE671663F2F5DB);
lazy_func_t<int(Entity entity, const char *propertyName)>
	DECOR_GET_INT(0xA06C969B02A97298);
lazy_func_t<void()> DECOR_REGISTER_LOCK(0xA9D14EEA259F9248);
}} // namespace DECORATOR::
namespace AI { namespace {
lazy_func_t<void(Any p0)> VEHICLE_WAYPOINT_PLAYBACK_PAUSE(0x8A4E6AC373666BC5);
lazy_func_t<void()> TASK_FLUSH_ROUTE(0x841142A1376E9006);
lazy_func_t<Any(Any p0)> GET_VEHICLE_WAYPOINT_TARGET_POINT(0x416B62AC8B9E5BBD);
lazy_func_t<void(Any p0, Any p1, BOOL p2, Any p3)>
	_0xE70BA7B90F8390DC(0xE70BA7B90F8390DC);
lazy_func_t<void(Ped ped)> UNCUFF_PED(0x67406F2C8F87FC4F);
lazy_func_t<void(Ped ped, BOOL p1)> TASK_PARACHUTE(0xD2F1C53C97EE81AB);
lazy_func_t<void(
	Ped ped,
	Entity entity,
	float offsetX,
	float offsetY,
	float offsetZ,
	float movementSpeed,
	int timeout,
	float stoppingRange,
	BOOL persistFollowing)>
	TASK_FOLLOW_TO_OFFSET_OF_ENTITY(0x304AE42E357B8C7E);
lazy_func_t<void(Ped ped, int p1)> TASK_CLIMB_LADDER(0xB6C987F9285A3814);
lazy_func_t<void(
	Ped ped,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	Any p7,
	BOOL p8)>
	TASK_SEEK_COVER_TO_COORDS(0x39246A6958EF072C);
lazy_func_t<void(Ped ped, Ped target, float p2)>
	TASK_VEHICLE_SHOOT_AT_PED(0x10AB107B887214D8);
lazy_func_t<void(Any p0)>
	VEHICLE_WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(0x5CEB25A7D2848963);
lazy_func_t<BOOL(Ped ped)> IS_PED_RUNNING_ARREST_TASK(0x3DC52677769B4AE0);
lazy_func_t<void(Ped ped, BOOL avoidFire)>
	SET_PED_PATH_AVOID_FIRE(0x4455517B28441E60);
lazy_func_t<void(
	Ped ped,
	const char *animDictionary,
	const char *animationName,
	float speed,
	float speedMultiplier,
	int duration,
	int flag,
	float playbackRate,
	BOOL lockX,
	BOOL lockY,
	BOOL lockZ)>
	TASK_PLAY_ANIM(0xEA47FE3719165B94);
lazy_func_t<void(Ped ped, Ped target, int time, int p3)>
	TASK_WRITHE(0xCDDC2B77CE54AC6E);
lazy_func_t<BOOL(Any p0)> _0x30ED88D5E0C56A37(0x30ED88D5E0C56A37);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float speed,
	int timeout,
	float unkFloat,
	int unkInt,
	float unkX,
	float unkY,
	float unkZ,
	float unk_40000f)>
	TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED(0x17F58B88D085DBAC);
lazy_func_t<void(Ped ped, const char *animDict, const char *animName)>
	PLAY_ANIM_ON_RUNNING_SCENARIO(0x748040460F8DF5DC);
lazy_func_t<float(Any p0)> GET_PED_WAYPOINT_DISTANCE(0xE6A877C64CAF1BC5);
lazy_func_t<void(Ped ped, float x, float y, float z, int duration)>
	TASK_TURN_PED_TO_FACE_COORD(0x1DDA930A0AC38571);
lazy_func_t<void(Any p0, Ped ped, int p2, Any p3)>
	TASK_COMBAT_PED_TIMED(0x944F30DCB7096BDE);
lazy_func_t<BOOL(Ped ped)> IS_PED_WALKING(0xDE4C184B2B9B071A);
lazy_func_t<void(const char *name)>
	REQUEST_WAYPOINT_RECORDING(0x9EEFB62EB27B5792);
lazy_func_t<void(Any p0, float p1, BOOL p2)>
	WAYPOINT_PLAYBACK_OVERRIDE_SPEED(0x7D7D2B47FA788E85);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	Any timeout,
	BOOL p5,
	float p6,
	BOOL p7,
	BOOL p8,
	Any p9,
	BOOL p10)>
	TASK_PUT_PED_DIRECTLY_INTO_COVER(0x4172393E6BE1FECE);
lazy_func_t<int(Ped ped)> GET_PED_WAYPOINT_PROGRESS(0x2720AAA75001E094);
lazy_func_t<void(Ped driver, Vehicle vehicle, int action, int time)>
	TASK_VEHICLE_TEMP_ACTION(0xC429DCEEB339E129);
lazy_func_t<BOOL(Ped ped)>
	IS_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(0x8785E6E40C7A8818);
lazy_func_t<void(Ped ped, Vehicle boat)> _TASK_GET_OFF_BOAT(0x9C00E77AF14B2DFF);
lazy_func_t<void(Any *p0, BOOL p1, float p2, float p3)>
	USE_WAYPOINT_RECORDING_AS_ASSISTED_MOVEMENT_ROUTE(0x5A353B8E6B1095B5);
lazy_func_t<void(Any p0, float p1, Any p2, Any p3)>
	TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED(0x2BBA30B854534A0C);
lazy_func_t<void(int ped, float x, float y, float z)>
	TASK_THROW_PROJECTILE(0x7285951DBF6B5A51);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	const char *WPRecording,
	int p3,
	int p4,
	int p5,
	int p6,
	float p7,
	BOOL p8,
	float p9)>
	TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING(0x3123FAA6DB1CF7ED);
lazy_func_t<void(Ped ped, int duration)> TASK_COWER(0x3EB1FE9E8E908E15);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	Vehicle targetVehicle,
	int mode,
	float speed,
	int drivingStyle,
	float minDistance,
	int p7,
	float noRoadsDistance)>
	TASK_VEHICLE_ESCORT(0x0FA6E4B75F302400);
lazy_func_t<void(Any p0, Any p1, float p2, float p3, float p4)>
	TASK_EXIT_COVER(0x79B258E397854D29);
lazy_func_t<void(Ped ped, Ped target)> TASK_ARREST_PED(0xF3B9A78A178572B1);
lazy_func_t<
	void(Ped ped, Entity lookAt, int duration, int unknown1, int unknown2)>
	TASK_LOOK_AT_ENTITY(0x69F4BE8C8CC4796C);
lazy_func_t<ScrHandle(
	float p0, float p1, float p2, float p3, Any p4, Any p5, Any p6, BOOL p7)>
	ADD_COVER_POINT(0xD5C12A75C7B9497F);
lazy_func_t<int(Vehicle vehicle)>
	GET_VEHICLE_WAYPOINT_PROGRESS(0x9824CFF8FC66E159);
lazy_func_t<void(
	Ped ped,
	const char *p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	Any p8,
	float p9,
	BOOL p10,
	const char *animDict,
	int flags)>
	_TASK_MOVE_NETWORK_ADVANCED(0xD5B35BEA41919ACB);
lazy_func_t<void(
	Entity entity,
	Entity target,
	int duration,
	float distance,
	float speed,
	float p5,
	int p6)>
	TASK_GO_TO_ENTITY(0x6A071245EB0D1882);
lazy_func_t<void()> CREATE_PATROL_ROUTE(0xAF8A443CCC8018DC);
lazy_func_t<float(Ped ped)>
	GET_PHONE_GESTURE_ANIM_TOTAL_TIME(0x1EE0F68A7C25DEC6);
lazy_func_t<void(
	Ped pilot,
	Vehicle plane,
	float runwayStartX,
	float runwayStartY,
	float runwayStartZ,
	float runwayEndX,
	float runwayEndY,
	float runwayEndZ)>
	TASK_PLANE_LAND(0xBF19721FA34D32C0);
lazy_func_t<void(Ped ped, int eventHandle)>
	TASK_SHOCKING_EVENT_REACT(0x452419CBD838065B);
lazy_func_t<void(Ped ped, float x, float y, float z, float heading)>
	TASK_PLANT_BOMB(0x965FEC691D55E9BF);
lazy_func_t<int(Ped ped)> GET_NAVMESH_ROUTE_RESULT(0x632E831F382A0FA8);
lazy_func_t<void(Ped ped)> CLEAR_PED_TASKS(0xE1EF3C1216AFF2CD);
lazy_func_t<void(Ped ped)>
	_TASK_STOP_PHONE_GESTURE_ANIMATION(0x3FA00D4F4641BFAE);
lazy_func_t<Any(Object taskSequence)> CLOSE_SEQUENCE_TASK(0x39E72BC99E6360CB);
lazy_func_t<void(Ped ped, Vehicle vehicle)>
	TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT(0x7AA80209BDA643EB);
lazy_func_t<void(Ped ped)>
	CLEAR_DRIVEBY_TASK_UNDERNEATH_DRIVING_TASK(0xC35B5CDB2824CF69);
lazy_func_t<void(float p0)> SET_NEXT_DESIRED_MOVE_STATE(0xF1B9F16E89E2C93A);
lazy_func_t<void(Any p0, Any p1)> ADD_PATROL_ROUTE_LINK(0x23083260DEC3A551);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float speed,
	Any p5,
	BOOL p6,
	int walkingStyle,
	float p8,
	Any p9,
	Any p10,
	Any p11)>
	TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS(0x1DD45F9ECFDB1BC9);
lazy_func_t<void(Ped ped, int p1, BOOL p2)>
	STOP_ANIM_PLAYBACK(0xEE08C992D238C5D1);
lazy_func_t<void(
	Ped ped,
	Entity entityToWalkTo,
	Entity entityToAimAt,
	float speed,
	BOOL shootatEntity,
	float p5,
	float p6,
	BOOL p7,
	BOOL p8,
	Hash firingPattern)>
	TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(0x97465886D35210E9);
lazy_func_t<BOOL(const char *name, int *points)>
	WAYPOINT_RECORDING_GET_NUM_POINTS(0x5343532C01A07234);
lazy_func_t<void(Ped ped, float x, float y, float z, int duration, BOOL p5)>
	TASK_SEEK_COVER_FROM_POS(0x75AC2B60386D89F2);
lazy_func_t<void(BOOL p0, BOOL p1)> TASK_TOGGLE_DUCK(0xAC96609B9995EDF8);
lazy_func_t<void(Ped ped, BOOL p1)> TASK_SWAP_WEAPON(0xA21C51255B205245);
lazy_func_t<void(Any p0)>
	WAYPOINT_PLAYBACK_USE_DEFAULT_SPEED(0x6599D834B12D0800);
lazy_func_t<Any(Any p0, Any p1)> _0xAB13A5565480B6D9(0xAB13A5565480B6D9);
lazy_func_t<Any(Object *taskSequence)> CLEAR_SEQUENCE_TASK(0x3841422E9C488D8C);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	TASK_PERFORM_SEQUENCE_FROM_PROGRESS(0x89221B16730234F0);
lazy_func_t<void(const char *patrolRoute)>
	DELETE_PATROL_ROUTE(0x7767DD9D65E91319);
lazy_func_t<void(Ped ped, const char *p1, float p2)>
	_0xD5BB4025AE449A4E(0xD5BB4025AE449A4E);
lazy_func_t<BOOL(Ped ped)> IS_MOVE_BLEND_RATIO_SPRINTING(0x24A2AD74FA9814E2);
lazy_func_t<BOOL(Ped ped)> IS_PED_STILL(0xAC29253EEF8F0180);
lazy_func_t<void(Ped ped, Entity entity, int duration)>
	TASK_TURN_PED_TO_FACE_ENTITY(0x5AD23D40115353AC);
lazy_func_t<BOOL(Ped ped)> IS_PED_ACTIVE_IN_SCENARIO(0xAA135F9482C82CC3);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	float x,
	float y,
	float z,
	float speed,
	Any p6,
	Hash vehicleModel,
	int drivingMode,
	float stopRange,
	float p10)>
	TASK_VEHICLE_DRIVE_TO_COORD(0xE2A2AA2F659D77A7);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float speed,
	int timeout,
	float stoppingRange,
	BOOL persistFollowing,
	float unk)>
	TASK_FOLLOW_NAV_MESH_TO_COORD(0x15D3A79D4E44B913);
lazy_func_t<void(const char *scenarioType, BOOL toggle)>
	SET_SCENARIO_TYPE_ENABLED(0xEB47EC4E34FB7EE1);
lazy_func_t<void(
	Ped pedHandle,
	float goToLocationX,
	float goToLocationY,
	float goToLocationZ,
	float focusLocationX,
	float focusLocationY,
	float focusLocationZ,
	float speed,
	BOOL shootAtEnemies,
	float distanceToStopAt,
	float noRoadsDistance,
	BOOL unkTrue,
	int unkFlag,
	int aimingFlag,
	Hash firingPattern)>
	TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD(0xA55547801EB331FC);
lazy_func_t<BOOL(Ped ped)> IS_PED_SPRINTING(0x57E457CD2C0FC168);
lazy_func_t<BOOL(Ped ped)> _0x3E38E28A1D80DDF6(0x3E38E28A1D80DDF6);
lazy_func_t<void(Ped ped, Ped targetPed, int p2, int p3)>
	TASK_COMBAT_PED(0xF166E48407BAC484);
lazy_func_t<void(
	Any p0, Any p1, float p2, float p3, float p4, Any p5, BOOL p6, BOOL p7)>
	TASK_AIM_GUN_SCRIPTED_WITH_TARGET(0x8605AF0DE8B3A5AC);
lazy_func_t<void(Any p0, float p1)>
	SET_DRIVE_TASK_MAX_CRUISE_SPEED(0x404A5AA9B9F0B746);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	int timeout,
	int seat,
	float speed,
	int flag,
	Any p6)>
	TASK_ENTER_VEHICLE(0xC20E50AA46D09CA8);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	float x,
	float y,
	float z,
	float heading,
	int mode,
	float radius,
	BOOL keepEngineOn)>
	TASK_VEHICLE_PARK(0x0F3E34E968EA374E);
lazy_func_t<void(Ped ped, Any *p1, Any *p2, Any *p3, float p4, float p5)>
	TASK_SCRIPTED_ANIMATION(0x126EF75F1E17ABE5);
lazy_func_t<void(Any p0, Any p1, float p2, float p3, float p4, Any p5, BOOL p6)>
	TASK_SEEK_COVER_TO_COVER_POINT(0xD43D95C7A869447F);
lazy_func_t<void(Any p0, float p1, float p2, float p3, float p4, Any p5)>
	TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP(0x97A28E63F0BA5631);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float aimAtX,
	float aimAtY,
	float aimAtZ,
	float moveSpeed,
	BOOL p8,
	float p9,
	float p10,
	BOOL p11,
	Any flags,
	BOOL p13,
	Hash firingPattern)>
	TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(0x11315AB3385B8AC0);
lazy_func_t<BOOL(const char *name, int point, Vector3 *coord)>
	WAYPOINT_RECORDING_GET_COORD(0x2FB897405C90B361);
lazy_func_t<BOOL(int PlayerID)> _0x921CE12C489C4C41(0x921CE12C489C4C41);
lazy_func_t<void(
	Entity entity1,
	Entity entity2,
	float p2,
	float p3,
	float p4,
	float p5,
	Any p6)>
	TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY(0x61E360B7E040D12E);
lazy_func_t<Any(Ped ped, BOOL Toggle)>
	SET_PED_PATH_CAN_USE_LADDERS(0x77A5B103C87F476E);
lazy_func_t<BOOL(Ped ped)> IS_MOVE_BLEND_RATIO_RUNNING(0xD4D8636C0199A939);
lazy_func_t<void(Ped pilot, Entity entityToFollow, float x, float y, float z)>
	TASK_PLANE_CHASE(0x2D2386F273FF7A25);
lazy_func_t<void(Ped p0, Hash p1)> TASK_SET_DECISION_MAKER(0xEB8517DDA73720DA);
lazy_func_t<void(Ped ped)> TASK_SKY_DIVE(0x601736CFE536B0A0);
lazy_func_t<int(Ped targetPed, Hash taskHash)>
	GET_SCRIPT_TASK_STATUS(0x77F1BEB8863288D5);
lazy_func_t<void(
	Ped shootingPed,
	Ped targetPed,
	Vehicle targetVehicle,
	float x,
	float y,
	float z)>
	SET_MOUNTED_WEAPON_TARGET(0xCCD892192C6D2BB9);
lazy_func_t<void(Any p0)> TASK_CLEAR_DEFENSIVE_AREA(0x95A6C46A31D1917D);
lazy_func_t<Vector3(ScrHandle coverpoint)>
	GET_SCRIPTED_COVER_POINT_COORDS(0x594A1028FC2A3E85);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float speed,
	Any p5,
	BOOL p6,
	int walkingStyle,
	float p8,
	Any p9,
	Any p10,
	Any p11,
	Any p12)>
	TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED(
		0xB8ECD61F531A7B02);
lazy_func_t<int(Ped ped)> GET_SEQUENCE_PROGRESS(0x00A9010CFE1E3533);
lazy_func_t<BOOL(Ped ped)>
	IS_MOUNTED_WEAPON_TASK_UNDERNEATH_DRIVING_TASK(0xA320EF046186FA3B);
lazy_func_t<BOOL(Ped ped)> IS_PED_GETTING_UP(0x2A74E1D5F2F00EEC);
lazy_func_t<void(Ped ped, int flag, BOOL set)>
	SET_TASK_VEHICLE_CHASE_BEHAVIOR_FLAG(0xCC665AAC360D31E7);
lazy_func_t<void(
	Ped pilot,
	Vehicle aircraft,
	Vehicle targetVehicle,
	Ped targetPed,
	float destinationX,
	float destinationY,
	float destinationZ,
	int missionFlag,
	float angularDrag,
	float unk,
	float targetHeading,
	float maxZ,
	float minZ)>
	TASK_PLANE_MISSION(0x23703CD154E83B88);
lazy_func_t<BOOL(float x, float y, float z)>
	DOES_SCRIPTED_COVER_POINT_EXIST_AT_COORDS(0xA98B8E3C088E5A31);
lazy_func_t<BOOL(Ped ped, const char *p1)>
	_0xA7FFBA498E4AAF67(0xA7FFBA498E4AAF67);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float speed,
	Any p5,
	BOOL p6,
	int walkingStyle,
	float p8)>
	TASK_GO_TO_COORD_ANY_MEANS(0x5BC448CB78FA3E88);
lazy_func_t<BOOL(Ped ped, int taskNumber)>
	GET_IS_TASK_ACTIVE(0xB0760331C7AA4155);
lazy_func_t<void(Ped ped, int p1, int p2)>
	TASK_LEAVE_ANY_VEHICLE(0x504D54DF3F6F2247);
lazy_func_t<void(Ped ped, float x, float y, float z, float p4)>
	TASK_VEHICLE_SHOOT_AT_COORD(0x5190796ED39C9B6D);
lazy_func_t<void(Any p0, float p1, float p2, float p3, BOOL p4)>
	WAYPOINT_PLAYBACK_START_AIMING_AT_COORD(0x8968400D900ED8B3);
lazy_func_t<void(float x, float y, float z)>
	TASK_EXTEND_ROUTE(0x1E7889778264843A);
lazy_func_t<void(Ped ped, float p1)> _0x88E32DB8C1A4AA4B(0x88E32DB8C1A4AA4B);
lazy_func_t<void(Vehicle vehicle)>
	TASK_EVERYONE_LEAVE_VEHICLE(0x7F93691AB4B92272);
lazy_func_t<void(Ped ped, float x, float y, float z)>
	TASK_VEHICLE_AIM_AT_COORD(0x447C1E9EF844BC0F);
lazy_func_t<void(Ped ped, int duration, Ped facingPed, int p3, BOOL p4)>
	TASK_HANDS_UP(0xF2EAB31979A7F910);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float distance,
	int time,
	BOOL p6,
	BOOL p7)>
	TASK_SMART_FLEE_COORD(0x94587F17E9C365D5);
lazy_func_t<void(Ped ped, Entity entity, int duration, BOOL p3)>
	TASK_AIM_GUN_AT_ENTITY(0x9B53BB6E8943AF53);
lazy_func_t<void()> RESET_SCENARIO_GROUPS_ENABLED(0xDD902D0349AFAD3A);
lazy_func_t<float(const char *p0, int p1)>
	GET_WAYPOINT_DISTANCE_ALONG_ROUTE(0xA5B769058763E497);
lazy_func_t<const char *(Ped ped)> _0x717E4D1F2048376D(0x717E4D1F2048376D);
lazy_func_t<
	void(Ped ped, Vehicle vehicle, int timeOut, int doorIndex, float speed)>
	TASK_OPEN_VEHICLE_DOOR(0x965791A9A488A062);
lazy_func_t<void(
	Ped ped, const char *animDictionary, const char *animationName, float p3)>
	STOP_ANIM_TASK(0x97FF36A1D40EA00A);
lazy_func_t<
	void(Ped ped, float x, float y, float z, float distance, int duration)>
	TASK_USE_NEAREST_SCENARIO_TO_COORD(0x277F471BA9DB000B);
lazy_func_t<void(
	int p0,
	const char *p1,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int p8)>
	ADD_PATROL_ROUTE_NODE(0x8EDF950167586B7C);
lazy_func_t<void(Any p0, float p1, float p2, float p3, BOOL p4, Any p5)>
	WAYPOINT_PLAYBACK_START_SHOOTING_AT_COORD(0x057A25CFCC9DB671);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	float x,
	float y,
	float z,
	float speed,
	int driveMode,
	float stopRange)>
	TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(0x158BB33F920D360C);
lazy_func_t<void(
	Ped ped,
	Entity entity,
	int duration,
	float xOffset,
	float yOffset,
	float zOffset,
	float moveBlendRatio,
	BOOL useNavmesh)>
	TASK_GOTO_ENTITY_OFFSET_XY(0x338E7EF52B6095A9);
lazy_func_t<void(Ped ped, int time)> TASK_STAND_STILL(0x919BE13EED931959);
lazy_func_t<void(Ped ped, float p1, int p2)>
	TASK_WANDER_STANDARD(0xBB9CE077274F6A1B);
lazy_func_t<void(Ped ped)> CLEAR_PED_TASKS_IMMEDIATELY(0xAAA34F8A7CB32098);
lazy_func_t<void(Ped driver, float cruiseSpeed)>
	SET_DRIVE_TASK_CRUISE_SPEED(0x5C9B84BD7D31D908);
lazy_func_t<void(Ped ped, float x, float y, float z)>
	ADD_VEHICLE_SUBTASK_ATTACK_COORD(0x5CF0D8F9BBA0DD75);
lazy_func_t<void(Any p0, BOOL p1, Any p2, Any p3)>
	WAYPOINT_PLAYBACK_RESUME(0x244F70C84C547D2D);
lazy_func_t<void(Ped ped, BOOL toggle)>
	TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(0x90D2156198831D69);
lazy_func_t<void(Object taskSequence, BOOL repeat)>
	SET_SEQUENCE_TO_REPEAT(0x58C70CF3A41E4AE7);
lazy_func_t<void(
	Ped pilot,
	Vehicle aircraft,
	Vehicle targetVehicle,
	Ped targetPed,
	float destinationX,
	float destinationY,
	float destinationZ,
	int missionFlag,
	float maxSpeed,
	float landingRadius,
	float targetHeading,
	int unk1,
	int unk2,
	Hash unk3,
	int landingFlags)>
	TASK_HELI_MISSION(0xDAD029E187A2BEB4);
lazy_func_t<void(
	Ped pedDriver,
	Vehicle boat,
	Any p2,
	Any p3,
	float x,
	float y,
	float z,
	Any p7,
	float maxSpeed,
	int drivingStyle,
	float p10,
	Any p11)>
	TASK_BOAT_MISSION(0x15C86013127CE63F);
lazy_func_t<BOOL(const char *name)>
	GET_IS_WAYPOINT_RECORDING_LOADED(0xCB4E8BE8A0063C5D);
lazy_func_t<void(Ped ped, BOOL unused)> TASK_CLIMB(0x89D9FCC2435112F1);
lazy_func_t<void(const char *route)>
	ASSISTED_MOVEMENT_REMOVE_ROUTE(0x3548536485DD792B);
lazy_func_t<Any(Ped ped, BOOL Toggle)>
	SET_PED_PATH_CAN_USE_CLIMBOVERS(0x8E06A6FE76C9EFF4);
lazy_func_t<void(Ped ped, BOOL Toggle)>
	SET_PED_PATH_CAN_DROP_FROM_HEIGHT(0xE361C5C71C431A4F);
lazy_func_t<BOOL(Ped ped)> PED_HAS_USE_SCENARIO_TASK(0x295E3CCEC879CCD7);
lazy_func_t<BOOL(const char *route)>
	ASSISTED_MOVEMENT_IS_ROUTE_LOADED(0x60F9A4393A21F741);
lazy_func_t<void(Any p0, float p1, Any p2, Any p3, BOOL p4)>
	SET_ANIM_WEIGHT(0x207F1A47C0342F48);
lazy_func_t<void(Ped ped, int drivingStyle)>
	SET_DRIVE_TASK_DRIVING_STYLE(0xDACE1BE37D88AF67);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	float x,
	float y,
	float z,
	float speed,
	int behaviorFlag,
	float stoppingRange)>
	TASK_VEHICLE_GOTO_NAVMESH(0x195AEEB13CEFE2EE);
lazy_func_t<BOOL(Ped ped)> IS_PLAYING_PHONE_GESTURE_ANIM(0xB8EBB1E9D3588C10);
lazy_func_t<void(const char *scenarioGroup, BOOL p1)>
	SET_SCENARIO_GROUP_ENABLED(0x02C8E5B49848664E);
lazy_func_t<void(Any p0)> VEHICLE_WAYPOINT_PLAYBACK_RESUME(0xDC04FCAA7839D492);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float speed,
	int timeout,
	float targetHeading,
	float distanceToSlide)>
	TASK_GO_STRAIGHT_TO_COORD(0xD76B57B44F1E6F8B);
lazy_func_t<void(Ped ped, float speed, int unknown)>
	TASK_FOLLOW_POINT_ROUTE(0x595583281858626E);
lazy_func_t<BOOL(Ped ped, const char *p1)>
	_0xB4F47213DF45A64C(0xB4F47213DF45A64C);
lazy_func_t<void(Any p0, BOOL p1, Any p2, BOOL p3)>
	SET_ANIM_LOOPED(0x70033C3CC29A1FF4);
lazy_func_t<void(Ped ped, int duration)>
	TASK_USE_MOBILE_PHONE_TIMED(0x5EE02954A14C69DB);
lazy_func_t<void(const char *scenarioGroup)>
	SET_EXCLUSIVE_SCENARIO_GROUP(0x535E97E1F7FC0C6A);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	Ped pedTarget,
	int mode,
	float maxSpeed,
	int drivingStyle,
	float minDistance,
	float p7,
	BOOL p8)>
	TASK_VEHICLE_MISSION_PED_TARGET(0x9454528DF15D657A);
lazy_func_t<void(
	Ped driver,
	Vehicle vehicle,
	Entity targetEntity,
	float speed,
	int drivingStyle,
	int minDistance)>
	_TASK_VEHICLE_FOLLOW(0xFC545A9F0626E3B6);
lazy_func_t<void(Ped ped, int p1)> TASK_USE_MOBILE_PHONE(0xBD2A8EC3AF4DE7DB);
lazy_func_t<void(Ped ped, Ped target, int duration, BOOL p3)>
	TASK_SEEK_COVER_FROM_PED(0x84D32B3BEC531324);
lazy_func_t<
	void(Ped ped, Ped meleeTarget, float p2, float p3, float p4, BOOL p5)>
	TASK_PUT_PED_DIRECTLY_INTO_MELEE(0x1C6CD14A876FFE39);
lazy_func_t<void(const char *name)>
	REMOVE_WAYPOINT_RECORDING(0xFF1B8B4AA1C25DC8);
lazy_func_t<void(Ped ped, Hash state, BOOL p2)>
	TASK_FORCE_MOTION_STATE(0x4F056E1AFFEF17AB);
lazy_func_t<void(Any p0, float p1, float p2, float p3)>
	UPDATE_TASK_SWEEP_AIM_POSITION(0xBB106883F5201FC4);
lazy_func_t<void(Ped ped, float x, float y, float z)>
	SET_PARACHUTE_TASK_TARGET(0xC313379AF0FCEDA7);
lazy_func_t<void(
	Ped shootingPed,
	Ped targetPed,
	Vehicle targetVehicle,
	float x,
	float y,
	float z)>
	SET_DRIVEBY_TASK_TARGET(0xE5B302114D8162EE);
lazy_func_t<
	void(Ped ped, Any p1, Any p2, float x, float y, float z, int duration)>
	TASK_GOTO_ENTITY_OFFSET(0xE39B4FF4FDEBDE27);
lazy_func_t<void(Ped ped, float distance)>
	SET_TASK_VEHICLE_CHASE_IDEAL_PURSUIT_DISTANCE(0x639B642FACBE4EDD);
lazy_func_t<void(
	Ped ped,
	const char *scenarioName,
	float x,
	float y,
	float z,
	float heading,
	int duration,
	BOOL sittingScenario,
	BOOL teleport)>
	TASK_START_SCENARIO_AT_POSITION(0xFA4EFC79F69D4F07);
lazy_func_t<int(Vehicle veh)>
	GET_ACTIVE_VEHICLE_MISSION_TYPE(0x534AEBA6E5ED4CAB);
lazy_func_t<void(Ped ped, Hash scriptTask, BOOL p2, BOOL p3)>
	TASK_AIM_GUN_SCRIPTED(0x7A192BE16D373D00);
lazy_func_t<BOOL(Any p0)>
	IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_VEHICLE(0xF5134943EA29868C);
lazy_func_t<
	void(Ped ped, float x, float y, float z, int duration, Hash firingPattern)>
	TASK_SHOOT_AT_COORD(0x46A6CC01E0826106);
lazy_func_t<void(ScrHandle coverpoint)> REMOVE_COVER_POINT(0xAE287C923D891715);
lazy_func_t<void(
	Ped ped,
	Vehicle vehicle,
	float x,
	float y,
	float z,
	int p5,
	int p6,
	int p7,
	float p8,
	float p9,
	BOOL p10)>
	TASK_VEHICLE_MISSION_COORS_TARGET(0xF0AF20AA7731F8C3);
lazy_func_t<void(Ped ped)> TASK_STAY_IN_COVER(0xE5DA8615A6180789);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float radius,
	float minimalLength,
	float timeBetweenWalks)>
	TASK_WANDER_IN_AREA(0xE054346CA3A0F315);
lazy_func_t<void(Any p0, Any *p1, Any *p2, Any *p3, float p4, float p5)>
	PLAY_ENTITY_SCRIPTED_ANIM(0x77A1EEC547E7FCF1);
lazy_func_t<void(Ped ped, const char *p1, Any p2, BOOL p3, BOOL p4)>
	TASK_PATROL(0xBDA5DF49D080FE4E);
lazy_func_t<void(Ped ped, Ped ped2)>
	ADD_VEHICLE_SUBTASK_ATTACK_PED(0x85F462BADC7DA47F);
lazy_func_t<void(Any p0)>
	WAYPOINT_PLAYBACK_STOP_AIMING_OR_SHOOTING(0x47EFA040EBB8E2EA);
lazy_func_t<int(Ped ped, float *distRemaining, BOOL *isPathReady)>
	GET_NAVMESH_ROUTE_DISTANCE_REMAINING(0xC6F5C0BCDC74D62D);
lazy_func_t<Any(Object *taskSequence)> OPEN_SEQUENCE_TASK(0xE8854A4326B9E12B);
lazy_func_t<void(Ped pilot, Entity entityToFollow, float x, float y, float z)>
	TASK_HELI_CHASE(0xAC83B1DB38D0ADA0);
lazy_func_t<void(Ped p0, float p1, float p2, BOOL p3)>
	TASK_GUARD_CURRENT_POSITION(0x4A58A47A72E3FCB4);
lazy_func_t<void(Ped ped, Ped target)>
	TASK_VEHICLE_AIM_AT_PED(0xE41885592B08B097);
lazy_func_t<void(Ped ped, float thrust)>
	SET_PARACHUTE_TASK_THRUST(0x0729BAC1B8C64317);
lazy_func_t<void(
	Entity entity, float x, float y, float z, float duration, Any p5, Any p6)>
	TASK_LOOK_AT_COORD(0x6FA46612594F7973);
lazy_func_t<
	void(Ped ped, float x, float y, float z, float heading, float duration)>
	TASK_PED_SLIDE_TO_COORD(0xD04FE6765D990A06);
lazy_func_t<float(const char *name, int point)>
	WAYPOINT_RECORDING_GET_SPEED_AT_POINT(0x005622AEBC33ACA9);
lazy_func_t<void(Any p0, float p1, Any p2, BOOL p3)>
	SET_ANIM_RATE(0x032D49C5E359C847);
lazy_func_t<
	void(Any p0, float p1, float p2, float p3, float p4, float p5, Any p6)>
	TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(0xD2A207EEBDF9889B);
lazy_func_t<void(Ped ped, int ms)> TASK_PAUSE(0xE73A266DB0CA9042);
lazy_func_t<void(Ped ped, BOOL mayEnterWater)>
	SET_PED_PATHS_WIDTH_PLANT(0xF35425A4204367EC);
lazy_func_t<void(Ped ped, BOOL unused)> TASK_RELOAD_WEAPON(0x62D2916F56B9CD2D);
lazy_func_t<BOOL(Any p0)>
	IS_WAYPOINT_PLAYBACK_GOING_ON_FOR_PED(0xE03B3F2D3DC59B64);
lazy_func_t<void(float dist)>
	ASSISTED_MOVEMENT_OVERRIDE_LOAD_DISTANCE_THIS_FRAME(0x13945951E16EF912);
lazy_func_t<void(Ped ped, Vehicle vehicle, float speed, int drivingStyle)>
	TASK_VEHICLE_DRIVE_WANDER(0x480142959D337D00);
lazy_func_t<void(Ped p0, Ped p1, float p2, float p3, float p4, BOOL p5)>
	UPDATE_TASK_AIM_GUN_SCRIPTED_TARGET(0x9724FB59A3E72AD0);
lazy_func_t<void(Ped killer, Ped target, Hash actionType, float p3, Any p4)>
	TASK_STEALTH_KILL(0xAA5DC05579D60BD9);
lazy_func_t<void(
	Ped driverPed,
	Ped targetPed,
	Vehicle targetVehicle,
	float targetX,
	float targetY,
	float targetZ,
	float distanceToShoot,
	int pedAccuracy,
	BOOL p8,
	Hash firingPattern)>
	TASK_DRIVE_BY(0x2F8AF0E82773A171);
lazy_func_t<void(Ped ped, float radius, int p2)>
	TASK_COMBAT_HATED_TARGETS_AROUND_PED(0x7BF835BB9E2698C8);
lazy_func_t<void(Ped ped, Vehicle vehicle, int flags)>
	TASK_LEAVE_VEHICLE(0xD3DBCE61A490BE02);
lazy_func_t<void(Ped ped, float heading, int timeout)>
	TASK_ACHIEVE_HEADING(0x93B93A37987F1F3D);
lazy_func_t<void()> RESET_EXCLUSIVE_SCENARIO_GROUP(0x4202BBCB8684563D);
lazy_func_t<void(Any p0, float p1)>
	VEHICLE_WAYPOINT_PLAYBACK_OVERRIDE_SPEED(0x121F0593E0A431D7);
lazy_func_t<void(
	Ped ped,
	int scene,
	const char *animDictionary,
	const char *animationName,
	float speed,
	float speedMultiplier,
	int duration,
	int flag,
	float playbackRate,
	Any p9)>
	TASK_SYNCHRONIZED_SCENE(0xEEA929141F699854);
lazy_func_t<
	void(Entity entity, Entity target, int duration, Hash firingPattern)>
	TASK_SHOOT_AT_ENTITY(0x08DA95E8298AE772);
lazy_func_t<void(
	float playerX,
	float playerY,
	float playerZ,
	float radiusX,
	float radiusY,
	float radiusZ,
	BOOL p6,
	BOOL p7,
	BOOL p8,
	BOOL p9)>
	ADD_COVER_BLOCKING_AREA(0x45C597097DD7CB81);
lazy_func_t<void(float height)>
	SET_GLOBAL_MIN_BIRD_FLIGHT_HEIGHT(0x6C6B148586F934F7);
lazy_func_t<void(
	Ped pilot,
	Vehicle vehicle,
	Entity entityToFollow,
	float targetSpeed,
	int p4,
	float radius,
	int altitude,
	int p7)>
	TASK_VEHICLE_HELI_PROTECT(0x1E09C32048FEFD1C);
lazy_func_t<float(Ped ped)>
	GET_PED_DESIRED_MOVE_BLEND_RATIO(0x8517D4A6CA8513ED);
lazy_func_t<BOOL(float p0, float p1, float p2, float p3, BOOL p4)>
	IS_SCENARIO_OCCUPIED(0x788756D73AC2E07C);
lazy_func_t<void(Ped ped, const char *p1, BOOL p2)>
	_0xB0A6CFD2C69C1088(0xB0A6CFD2C69C1088);
lazy_func_t<void(Ped ped, BOOL unused, BOOL flag1, BOOL flag2)>
	TASK_JUMP(0x0AE4086104E067B1);
lazy_func_t<void(
	Ped ped,
	const char *animDict,
	const char *animName,
	float posX,
	float posY,
	float posZ,
	float rotX,
	float rotY,
	float rotZ,
	float speed,
	float speedMultiplier,
	int duration,
	Any flag,
	float animTime,
	Any p14,
	Any p15)>
	TASK_PLAY_ANIM_ADVANCED(0x83CDB10EA29B370B);
lazy_func_t<void(
	Ped p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	Any p6,
	float p7,
	float p8,
	float p9,
	float p10)>
	TASK_GUARD_SPHERE_DEFENSIVE_AREA(0xC946FE14BE0EB5E2);
lazy_func_t<void()> REMOVE_ALL_COVER_BLOCKING_AREAS(0xDB6708C0B46F56D8);
lazy_func_t<void(Any p0, float p1, float p2, float p3, float p4, Any p5)>
	TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD(0x9FDA1B3D7E7028B3);
lazy_func_t<void(
	Any p0,
	float p1,
	float p2,
	float p3,
	Any p4,
	float p5,
	BOOL p6,
	float p7,
	float p8,
	BOOL p9,
	Any p10,
	BOOL p11,
	Any p12,
	Any p13)>
	TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(0xB2A16444EAD9AE47);
lazy_func_t<void(Ped ped, Any p1, Any p2, Any p3)>
	SET_HIGH_FALL_TASK(0x8C825BDC7741D37C);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	TASK_FOLLOW_WAYPOINT_RECORDING(0x0759591819534F7B);
lazy_func_t<Any(Ped ped, Object taskSequence)>
	TASK_PERFORM_SEQUENCE(0x5ABA3986D90D8A3B);
lazy_func_t<void(Ped ped, float p1)>
	SET_PED_DESIRED_MOVE_BLEND_RATIO(0x1E982AC8716912C5);
lazy_func_t<BOOL(Ped ped)> IS_PED_BEING_ARRESTED(0x90A09F3A45FED688);
lazy_func_t<void(const char *route)>
	ASSISTED_MOVEMENT_REQUEST_ROUTE(0x817268968605947A);
lazy_func_t<void(
	Ped ped,
	const char *anim,
	const char *p2,
	const char *p3,
	const char *p4,
	int p5,
	Vehicle vehicle,
	float p7,
	float p8)>
	TASK_SWEEP_AIM_ENTITY(0x2047C02158D6405A);
lazy_func_t<
	void(Ped ped, Entity target, float distanceToStopAt, float StartAimingDist)>
	TASK_GOTO_ENTITY_AIMING(0xA9DA48FAB8A76C12);
lazy_func_t<void()> CLOSE_PATROL_ROUTE(0xB043ECA801B8CBC1);
lazy_func_t<BOOL(Ped ped)> IS_PED_CUFFED(0x74E559B3BC910685);
lazy_func_t<BOOL(const char *scenarioType)>
	IS_SCENARIO_TYPE_ENABLED(0x3A815DB3EA088722);
lazy_func_t<BOOL(Ped ped)> IS_PED_STRAFING(0xE45B7F222DE47E09);
lazy_func_t<void(
	Ped ped,
	const char *animDict,
	const char *animation,
	const char *boneMaskType,
	float p4,
	float p5,
	BOOL p6,
	BOOL p7)>
	TASK_PLAY_PHONE_GESTURE_ANIMATION(0x8FBB6758B3B3E9EC);
lazy_func_t<void(Ped ped)> TASK_CLEAR_LOOK_AT(0x0F804F1DB19B9689);
lazy_func_t<BOOL(const char *scenarioGroup)>
	IS_SCENARIO_GROUP_ENABLED(0x367A09DED4E05B99);
lazy_func_t<void(Ped ped, int duration)>
	UPDATE_TASK_HANDS_UP_DURATION(0xA98FCAFD7893C834);
lazy_func_t<void(Ped ped, float x, float y, float z)>
	TASK_PARACHUTE_TO_TARGET(0xB33E291AFA6BD03A);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	SET_PED_WAYPOINT_ROUTE_OFFSET(0xED98E10B0AFCE4B4);
lazy_func_t<void(const char *route, int props)>
	ASSISTED_MOVEMENT_SET_ROUTE_PROPERTIES(0xD5002D78B7162E1B);
lazy_func_t<BOOL(Ped ped)> IS_MOVE_BLEND_RATIO_STILL(0x349CE7B56DAFD95C);
lazy_func_t<
	void(Ped ped, float x, float y, float z, int time, BOOL p5, BOOL p6)>
	TASK_AIM_GUN_AT_COORD(0x6671F3EEC681BDA1);
lazy_func_t<
	void(Ped ped, const char *scenarioName, int unkDelay, BOOL playEnterAnim)>
	TASK_START_SCENARIO_IN_PLACE(0x142A02425FF02BD9);
lazy_func_t<void(Ped ped)> CLEAR_PED_SECONDARY_TASK(0x176CECF6F920D707);
lazy_func_t<BOOL(float p0, float p1, float p2, Any *p3, float p4, BOOL p5)>
	DOES_SCENARIO_OF_TYPE_EXIST_IN_AREA(0x0A9D0C2A3BBC86C1);
lazy_func_t<BOOL(Ped ped)> _0x621C6E4729388E41(0x621C6E4729388E41);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_WRITHE(0xDEB6D52126E7D640);
lazy_func_t<void(const char *patrolRoute)>
	OPEN_PATROL_ROUTE(0xA36BFB5EE89F3D82);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	WAYPOINT_PLAYBACK_PAUSE(0x0F342546AA06FED5);
lazy_func_t<float(Ped ped)>
	GET_PHONE_GESTURE_ANIM_CURRENT_TIME(0x47619ABE8B268C60);
lazy_func_t<void(
	Vehicle vehicle, const char *animation_set, const char *animation_name)>
	TASK_VEHICLE_PLAY_ANIM(0x69F5C3BD0F3EBD89);
lazy_func_t<void(Any p0, Any p1, BOOL p2)>
	WAYPOINT_PLAYBACK_START_AIMING_AT_PED(0x20E330937C399D29);
lazy_func_t<void(
	Ped ped,
	const char *task,
	float multiplier,
	BOOL p3,
	const char *animDict,
	int flags)>
	_TASK_MOVE_NETWORK(0x2D537BA194896636);
lazy_func_t<void(Ped ped, Entity entity)>
	UPDATE_TASK_SWEEP_AIM_ENTITY(0xE4973DBDBE6E44B3);
lazy_func_t<void(
	Any p0,
	Any *p1,
	Any *p2,
	Any *p3,
	Any *p4,
	Any p5,
	float p6,
	float p7,
	float p8,
	float p9,
	float p10)>
	TASK_SWEEP_AIM_POSITION(0x7AFE8FDC10BC07D2);
lazy_func_t<void(
	Ped ped,
	Ped target,
	Any p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7)>
	TASK_CHAT_TO_PED(0x8C338E0263E4FD19);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	float heading,
	const char *scenarioName)>
	TASK_STAND_GUARD(0xAE032F8BBA959E90);
lazy_func_t<void(
	Ped ped, Ped fleeTarget, float distance, Any fleeTime, BOOL p4, BOOL p5)>
	TASK_SMART_FLEE_PED(0x22B0D0E37CCB840D);
lazy_func_t<void(Ped driver, Entity targetEnt)>
	TASK_VEHICLE_CHASE(0x3C08A8E30363B353);
lazy_func_t<BOOL(Any p0)> WAYPOINT_PLAYBACK_GET_IS_PAUSED(0x701375A7D43F01CB);
lazy_func_t<BOOL(Ped ped)> IS_MOVE_BLEND_RATIO_WALKING(0xF133BBBE91E1691F);
lazy_func_t<void(Ped ped, float x, float y, float z, float radius, Any p5)>
	TASK_COMBAT_HATED_TARGETS_IN_AREA(0x4CF5F55DAC3280A0);
lazy_func_t<void(
	Any p0,
	Any p1,
	float p2,
	float p3,
	float p4,
	float p5,
	BOOL p6,
	float p7,
	float p8,
	BOOL p9,
	BOOL p10,
	Any p11)>
	TASK_GO_TO_ENTITY_WHILE_AIMING_AT_COORD(0x04701832B739DCE5);
lazy_func_t<BOOL(Ped ped)> CONTROL_MOUNTED_WEAPON(0xDCFE42068FE0135A);
lazy_func_t<void(Ped ped, Vehicle vehicle, int seat)>
	TASK_WARP_PED_INTO_VEHICLE(0x9A7D091411C5F684);
lazy_func_t<BOOL(float x, float y, float z, float radius, BOOL b)>
	DOES_SCENARIO_EXIST_IN_AREA(0x5A59271FFADD33C1);
lazy_func_t<BOOL(const char *scenarioGroup)>
	DOES_SCENARIO_GROUP_EXIST(0xF9034C136C9E00D3);
lazy_func_t<Any(Ped ped, const char *p1)>
	_0xD01015C7316AE176(0xD01015C7316AE176);
lazy_func_t<void(Ped ped, int unused)>
	TASK_RAPPEL_FROM_HELI(0x09693B0312F91649);
lazy_func_t<const char *(int p0)>
	GET_CLIP_SET_FOR_SCRIPTED_GUN_TASK(0x3A8CADC7D37AACC5);
lazy_func_t<void()> RESET_SCENARIO_TYPES_ENABLED(0x0D40EE2A7F2B2D6D);
lazy_func_t<void(Ped ped, BOOL p1, BOOL p2)>
	_0x8FD89A6240813FD0(0x8FD89A6240813FD0);
lazy_func_t<BOOL(const char *name, float x, float y, float z, int *point)>
	WAYPOINT_RECORDING_GET_CLOSEST_WAYPOINT(0xB629A298081F876F);
lazy_func_t<BOOL(Ped ped)> IS_PED_RUNNING(0xC5286FFC176F28A2);
lazy_func_t<void(Any p0, float p1, float p2, float p3, float p4)>
	TASK_SET_SPHERE_DEFENSIVE_AREA(0x933C06518B52A9A4);
lazy_func_t<void(Ped ped, float x, float y, float z, float radius, Any p5)>
	TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP(0x58E2E0F23F6B76C3);
lazy_func_t<void(
	int p0,
	int p1,
	Vehicle veh,
	Any p3,
	float p4,
	Any p5,
	float p6,
	float p7,
	BOOL p8)>
	TASK_VEHICLE_MISSION(0x659427E0EF36BCDE);
lazy_func_t<
	void(Ped ped, float x, float y, float z, float heading, float p5, float p6)>
	TASK_PED_SLIDE_TO_COORD_HDG_RATE(0x5A4A6A6D3DC64F52);
lazy_func_t<void(Ped ped, Ped fleeTarget)>
	TASK_REACT_AND_FLEE_PED(0x72C896464915D1B1);
lazy_func_t<void(Ped ped, BOOL avoidWater)>
	SET_PED_PATH_PREFER_TO_AVOID_WATER(0x38FE1EC73743793C);
}} // namespace AI::
namespace ITEMSET { namespace {
lazy_func_t<void(Any p0)> DESTROY_ITEMSET(0xDE18220B1C183EDA);
lazy_func_t<BOOL(Any p0)> IS_ITEMSET_VALID(0xB1B1EA596344DFAB);
lazy_func_t<BOOL(Any p0, Any p1)> ADD_TO_ITEMSET(0xE3945201F14637DD);
lazy_func_t<void(Any p0, Any p1)> REMOVE_FROM_ITEMSET(0x25E68244B0177686);
lazy_func_t<void(Any p0)> CLEAN_ITEMSET(0x41BC0D722FC04221);
lazy_func_t<Vehicle(Vehicle distri)> CREATE_ITEMSET(0x35AD299F50D91B24);
lazy_func_t<Any(ScrHandle x)> GET_ITEMSET_SIZE(0xD9127E83ABF7C631);
lazy_func_t<Any(Any p0, Any p1)>
	GET_INDEXED_ITEM_IN_ITEMSET(0x7A197E2521EE2BAB);
lazy_func_t<BOOL(Any p0, Any p1)> IS_IN_ITEMSET(0x2D0FC594D1E9C107);
}} // namespace ITEMSET::
namespace CONTROLS { namespace {
lazy_func_t<BOOL(int inputGroup)> _IS_INPUT_DISABLED(0xA571D46727E2B718);
lazy_func_t<void(int p0, int red, int green, int blue)>
	_0x8290252FFF36ACB5(0x8290252FFF36ACB5);
lazy_func_t<void(Any p0)> _0xCB0360EFEFB2580D(0xCB0360EFEFB2580D);
lazy_func_t<void(Any p0, Any p1)> _0xF239400E16C23E08(0xF239400E16C23E08);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_CONTROL_ENABLED(0x1CEA6BFDF248E5D9);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_DISABLED_CONTROL_JUST_PRESSED(0x91AEF906BCA88877);
lazy_func_t<float(int inputGroup, int control)>
	_0x4F8A26A890FD62FB(0x4F8A26A890FD62FB);
lazy_func_t<void(BOOL toggle)>
	SET_PLAYERPAD_SHAKES_WHEN_CONTROLLER_DISABLED(0x798FDEB5B1575088);
lazy_func_t<BOOL(const char *p0)> _0x3D42B92563939375(0x3D42B92563939375);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_CONTROL_JUST_PRESSED(0x580417101DDB492F);
lazy_func_t<BOOL(int inputGroup)> _IS_INPUT_JUST_DISABLED(0x13337B38DB572509);
lazy_func_t<const char *(int inputGroup, int control, Player p2)>
	GET_CONTROL_INSTRUCTIONAL_BUTTON(0x0499D7B09FC9B407);
lazy_func_t<void(int p0, int duration, int frequency)>
	SET_PAD_SHAKE(0x48B3886C1358D0D5);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	_0x14D29BB12D47F68C(0x14D29BB12D47F68C);
lazy_func_t<void(Any p0)> STOP_PAD_SHAKE(0x38C16A305E8CDC8D);
lazy_func_t<BOOL()> _0xE1615EC03B3BB4FD(0xE1615EC03B3BB4FD);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_CONTROL_JUST_RELEASED(0x50F940259D3841E6);
lazy_func_t<float(int inputGroup, int control)>
	_0x5B84D09CEC5209C5(0x5B84D09CEC5209C5);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_DISABLED_CONTROL_PRESSED(0xE2587F8CBBD87B1D);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_CONTROL_RELEASED(0x648EE3E7F38877DD);
lazy_func_t<BOOL(BOOL p0)> _0x23F09EADC01449D6(0x23F09EADC01449D6);
lazy_func_t<BOOL()> IS_LOOK_INVERTED(0x77B612531280010D);
lazy_func_t<int(int p0)> _0xD7D22F5592AED8BA(0xD7D22F5592AED8BA);
lazy_func_t<const char *(int inputGroup, int control, BOOL p2)>
	_0x80C2FD58D720C801(0x80C2FD58D720C801);
lazy_func_t<int()> GET_LOCAL_PLAYER_AIM_STATE(0xBB41AFBBBC0A0287);
lazy_func_t<void(int inputGroup)> _DISABLE_INPUT_GROUP(0x7F4724035FDCA1DD);
lazy_func_t<int(int inputGroup, int control)>
	GET_CONTROL_VALUE(0xD95E79E8686D2C27);
lazy_func_t<void(BOOL p0)> _0x5B73C77D9EB66E24(0x5B73C77D9EB66E24);
lazy_func_t<float(int inputGroup, int control)>
	GET_DISABLED_CONTROL_NORMAL(0x11E65974A982637C);
lazy_func_t<BOOL()> _0x0F70731BACCFBB96(0x0F70731BACCFBB96);
lazy_func_t<BOOL()> _0xFC859E2374407556(0xFC859E2374407556);
lazy_func_t<void(int inputGroup, int control, BOOL enable)>
	ENABLE_CONTROL_ACTION(0x351220255D64C155);
lazy_func_t<float(int inputGroup, int control)>
	GET_CONTROL_NORMAL(0xEC3C9B8D5327B563);
lazy_func_t<BOOL(int inputGroup, int control, float amount)>
	_SET_CONTROL_NORMAL(0xE8A25867FBA3B05E);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_DISABLED_CONTROL_JUST_RELEASED(0x305C8DCD79DA8B0F);
lazy_func_t<void(int inputGroup)>
	DISABLE_ALL_CONTROL_ACTIONS(0x5F4B6931816E599B);
lazy_func_t<void(int inputGroup)>
	ENABLE_ALL_CONTROL_ACTIONS(0xA5FFE9B05F199DE7);
lazy_func_t<BOOL(const char *p0)> _0x4683149ED1DDE7A1(0x4683149ED1DDE7A1);
lazy_func_t<void()> _0x643ED62D5EA3BEBD(0x643ED62D5EA3BEBD);
lazy_func_t<BOOL(float x, float y)> _SET_CURSOR_LOCATION(0xFC695459D4D0E219);
lazy_func_t<Any()> _0x59B9A7AF4C95133C(0x59B9A7AF4C95133C);
lazy_func_t<void(int inputGroup, int control)>
	SET_INPUT_EXCLUSIVE(0xEDE476E5EE29EDB1);
lazy_func_t<void(int inputGroup, int control, BOOL disable)>
	DISABLE_CONTROL_ACTION(0xFE99B66D079CF6BC);
lazy_func_t<BOOL(int inputGroup, int control)>
	IS_CONTROL_PRESSED(0xF3A21BCD95725A4A);
lazy_func_t<BOOL(int inputGroup)> _0x6CD79468A1E595C6(0x6CD79468A1E595C6);
lazy_func_t<void(Any p0)> _0xA0CEFCEA390AAB9B(0xA0CEFCEA390AAB9B);
}} // namespace CONTROLS::
namespace FIRE { namespace {
lazy_func_t<void(float x, float y, float z, float radius)>
	STOP_FIRE_IN_RANGE(0x056A8A219B8E829F);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)>
	_0x6070104B699B2EF4(0x6070104B699B2EF4);
lazy_func_t<Entity(
	int explosionType,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	float radius)>
	_GET_PED_INSIDE_EXPLOSION_AREA(0x14BA4BA137AF6CEC);
lazy_func_t<int(float X, float Y, float Z, int maxChildren, BOOL isGasFire)>
	START_SCRIPT_FIRE(0x6B83617E04503888);
lazy_func_t<void(Entity entity)> STOP_ENTITY_FIRE(0x7F0DD2EBBB651AFF);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_ON_FIRE(0x28D3FED7190D3A0B);
lazy_func_t<Any(Entity entity)> START_ENTITY_FIRE(0xF6A9D9708F6F23DF);
lazy_func_t<int(float x, float y, float z, float radius)>
	GET_NUMBER_OF_FIRES_IN_RANGE(0x50CAD495A460B305);
lazy_func_t<BOOL(Vector3 *outPosition, float x, float y, float z)>
	GET_CLOSEST_FIRE_POS(0x352A9F6BCF90081F);
lazy_func_t<void(
	Ped ped,
	float x,
	float y,
	float z,
	int explosionType,
	float damageScale,
	BOOL isAudible,
	BOOL isInvisible,
	float cameraShake)>
	ADD_OWNED_EXPLOSION(0x172AA1B624FA1013);
lazy_func_t<BOOL(int explosionType, float x, float y, float z, float radius)>
	IS_EXPLOSION_IN_SPHERE(0xAB0F816885B0E483);
lazy_func_t<void(int fireHandle)> REMOVE_SCRIPT_FIRE(0x7FF548385680673F);
lazy_func_t<void(
	float x,
	float y,
	float z,
	int explosionType,
	float damageScale,
	BOOL isAudible,
	BOOL isInvisible,
	float cameraShake)>
	ADD_EXPLOSION(0xE3AD2BDBAEE269AC);
lazy_func_t<void(
	float x,
	float y,
	float z,
	int explosionType,
	Hash explosionFx,
	float damageScale,
	BOOL isAudible,
	BOOL isInvisible,
	float cameraShake)>
	ADD_EXPLOSION_WITH_USER_VFX(0x36DD3FE58B5E5212);
lazy_func_t<BOOL(
	int explosionType,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2)>
	IS_EXPLOSION_IN_AREA(0x2E2EBA0EE7CED0E0);
lazy_func_t<BOOL(
	int explosionType,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	float angle)>
	IS_EXPLOSION_IN_ANGLED_AREA(0xA079A6C51525DC4B);
}} // namespace FIRE::
namespace DLC1 { namespace {
lazy_func_t<BOOL(Any *dlcData)> _IS_DLC_DATA_EMPTY(0xD4D7B033C3AA243C);
lazy_func_t<
	void(Hash componentHash, int componentId, Any *p2, Any *p3, Any *p4)>
	GET_VARIANT_COMPONENT(0x6E11F282F11863B6);
lazy_func_t<Hash(int dlcVehicleIndex)>
	GET_DLC_VEHICLE_MODEL(0xECC01B7C5763333C);
lazy_func_t<void(int componentId, int *outComponent)>
	GET_SHOP_PED_QUERY_COMPONENT(0x249E310B2D920699);
lazy_func_t<int(int character, BOOL p1)>
	_0xF3FBE2D50A6A8C28(0xF3FBE2D50A6A8C28);
lazy_func_t<int(int character)> _GET_NUM_DECORATIONS(0x278F76C3B0A8F109);
lazy_func_t<BOOL(int p0, int p1, int *outComponent)>
	_0xFF56381874F82086(0xFF56381874F82086);
lazy_func_t<Any(Any p0)> GET_SHOP_PED_OUTFIT_LOCATE(0x073CA26B079F956E);
lazy_func_t<BOOL(Any outfit, int slot, Any *item)>
	_GET_PROP_FROM_OUTFIT(0x19F2A026EDF0013F);
lazy_func_t<int()> GET_NUM_DLC_VEHICLES(0xA7A866D21CD2329B);
lazy_func_t<int(int dlcVehicleIndex)> GET_DLC_VEHICLE_FLAGS(0x5549EE11FA22FCF2);
lazy_func_t<BOOL(Any modData)> IS_DLC_VEHICLE_MOD(0x0564B9FF9631B82C);
lazy_func_t<void(Any p0, Any *p1)> GET_SHOP_PED_QUERY_PROP(0xDE44A00999B2837D);
lazy_func_t<void(Any p0, Any *p1)> GET_SHOP_PED_OUTFIT(0xB7952076E444979D);
lazy_func_t<int(Hash componentHash)> _0xC17AD0E5752BECDA(0xC17AD0E5752BECDA);
lazy_func_t<
	BOOL(int dlcWeaponIndex, int dlcWeapCompIndex, Any *ComponentDataPtr)>
	GET_DLC_WEAPON_COMPONENT_DATA(0x6CF598A2957C2BF8);
lazy_func_t<void(int *outComponent)>
	INIT_SHOP_PED_COMPONENT(0x1E8C308FD312C036);
lazy_func_t<
	int(int character, int p1, int p2, BOOL p3, int p4, int componentId)>
	_GET_NUM_PROPS_FROM_OUTFIT(0x9BDF59818B1E38C1);
lazy_func_t<BOOL(Hash componentHash, Hash drawableSlotHash, int componentId)>
	_0x341DE7ED1D2A1BFD(0x341DE7ED1D2A1BFD);
lazy_func_t<BOOL(int dlcWeaponIndex, int *outData)>
	GET_DLC_WEAPON_DATA(0x79923CD21BECE14E);
lazy_func_t<void(int *outProp)> INIT_SHOP_PED_PROP(0xEB0A2B758F7B850F);
lazy_func_t<void(Any p0, Any *p1)> _0x5D5CAFF661DDF6FC(0x5D5CAFF661DDF6FC);
lazy_func_t<void(Any p0, Any p1, Any *p2, Any *p3, Any *p4)>
	_0xE1CA84EBF72E691D(0xE1CA84EBF72E691D);
lazy_func_t<Hash(
	Entity entity, int componentId, int drawableVariant, int textureVariant)>
	GET_HASH_NAME_FOR_COMPONENT(0x0368B3A838070348);
lazy_func_t<Any(Any p0)> _0x017568A8182D98A6(0x017568A8182D98A6);
lazy_func_t<int()> GET_NUM_DLC_WEAPONS(0xEE47635F352DA367);
lazy_func_t<int(int modData)> _0xC098810437312FFF(0xC098810437312FFF);
lazy_func_t<void(Hash p0, Any *p1)> GET_SHOP_PED_COMPONENT(0x74C0E2A57EC66760);
lazy_func_t<
	void(Hash componentHash, int componentId, Any *p2, Any *p3, Any *p4)>
	GET_FORCED_COMPONENT(0x6C93ED8C2F74859B);
lazy_func_t<int(Hash componentHash)>
	_GET_NUM_FORCED_COMPONENTS(0xC6B9DB42C04DD8C3);
lazy_func_t<void(Any p0, Any *outfit)>
	GET_SHOP_PED_QUERY_OUTFIT(0x6D793F03A631FE56);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2)>
	_0xA9F9C2E0FDE11CBB(0xA9F9C2E0FDE11CBB);
lazy_func_t<BOOL(int dlcVehicleIndex, int *outData)>
	GET_DLC_VEHICLE_DATA(0x33468EDC08E371F6);
lazy_func_t<int(int dlcWeaponIndex)>
	GET_NUM_DLC_WEAPON_COMPONENTS(0x405425358A7D61FE);
lazy_func_t<int(int p0, int p1, int p2, int p3)>
	_0x50F457823CE6EB5F(0x50F457823CE6EB5F);
lazy_func_t<
	Hash(Entity entity, int componentId, int propIndex, int propTextureIndex)>
	GET_HASH_NAME_FOR_PROP(0x5D6160275CAEC8DD);
}} // namespace DLC1::
namespace TIME { namespace {
lazy_func_t<void(int hour, int minute, int second)>
	SET_CLOCK_TIME(0x47C3B5848C3E45D8);
lazy_func_t<void(BOOL toggle)> PAUSE_CLOCK(0x4055E40BD2DBEC1D);
lazy_func_t<void(int hours, int minutes, int seconds)>
	ADD_TO_CLOCK_TIME(0xD716F30D8C8980E2);
lazy_func_t<int()> GET_CLOCK_HOURS(0x25223CA6B4D20B7F);
lazy_func_t<int()> GET_CLOCK_SECONDS(0x494E97C2EF27C470);
lazy_func_t<void(int day, int month, int year)>
	SET_CLOCK_DATE(0xB096419DF0D06CE7);
lazy_func_t<int()> GET_MILLISECONDS_PER_GAME_MINUTE(0x2F8B4D1C595B11DB);
lazy_func_t<int()> GET_CLOCK_YEAR(0x961777E64BDAF717);
lazy_func_t<int()> GET_CLOCK_MINUTES(0x13D2B8ADD79640F2);
lazy_func_t<int()> GET_CLOCK_DAY_OF_MONTH(0x3D10BC92A4DB1D35);
lazy_func_t<int()> GET_CLOCK_MONTH(0xBBC72712E80257A1);
lazy_func_t<
	void(int *year, int *month, int *day, int *hour, int *minute, int *second)>
	GET_POSIX_TIME(0xDA488F299A5B164E);
lazy_func_t<
	void(int *year, int *month, int *day, int *hour, int *minute, int *second)>
	_GET_UTC_TIME(0x8117E09A19EEF4D3);
lazy_func_t<
	void(int *year, int *month, int *day, int *hour, int *minute, int *second)>
	GET_LOCAL_TIME(0x50C7A99057A69748);
lazy_func_t<void(int hour, int minute, int second)>
	ADVANCE_CLOCK_TIME_TO(0xC8CA9670B9D83B3B);
lazy_func_t<int()> GET_CLOCK_DAY_OF_WEEK(0xD972E4BD7AEB235F);
}} // namespace TIME::
namespace PATHFIND { namespace {
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	float radius,
	BOOL p4,
	BOOL p5,
	BOOL p6,
	Vector3 *outPosition,
	int *nodeId)>
	GET_RANDOM_VEHICLE_NODE(0x93E0DB8440B73A7D);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	float desiredX,
	float desiredY,
	float desiredZ,
	int nthClosest,
	Vector3 *outPosition,
	float *outHeading,
	int nodetype,
	Any p10,
	Any p11)>
	GET_NTH_CLOSEST_VEHICLE_NODE_FAVOUR_DIRECTION(0x45905BE8654AE067);
lazy_func_t<BOOL(float p0, float p1, float p2, float p3)>
	_0x07FB139B592FA687(0x07FB139B592FA687);
lazy_func_t<void(float x, float y, float radius)>
	ADD_NAVMESH_REQUIRED_REGION(0x387EAD7EE42F6685);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	BOOL unknown1,
	BOOL unknown2)>
	SET_ROADS_IN_AREA(0xBF1A602B5BA52FEE);
lazy_func_t<void(Any p0)> _0x2801D0012266DF07(0x2801D0012266DF07);
lazy_func_t<BOOL(float x1, float y1, float z1, float x2, float y2, float z2)>
	IS_NAVMESH_LOADED_IN_AREA(0xF813C7E63F9062A5);
lazy_func_t<BOOL(Any p0)>
	DOES_NAVMESH_BLOCKING_OBJECT_EXIST(0x0EAEB0DB4B132399);
lazy_func_t<float(float x1, float y1, float z1, float x2, float y2, float z2)>
	CALCULATE_TRAVEL_DISTANCE_BETWEEN_POINTS(0xADD95C7005C4A197);
lazy_func_t<
	void(float x1, float y1, float z1, float x2, float y2, float z2, float p6)>
	SET_ROADS_BACK_TO_ORIGINAL_IN_ANGLED_AREA(0x0027501B9F3B407E);
lazy_func_t<Any()> _0xBBB45C3CF5C8AA85(0xBBB45C3CF5C8AA85);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)>
	_0xD0BC1C6FB18EE154(0xD0BC1C6FB18EE154);
lazy_func_t<
	Any(float p0,
		float p1,
		float p2,
		float p3,
		float p4,
		float p5,
		float p6,
		BOOL p7,
		Any p8)>
	ADD_NAVMESH_BLOCKING_OBJECT(0xFCD5C8E06E502F5A);
lazy_func_t<BOOL(
	float x, float y, float z, BOOL onGround, Vector3 *outPosition, int flags)>
	GET_SAFE_COORD_FOR_PED(0xB61C8E878A4199CA);
lazy_func_t<void(
	Any p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	Any p8)>
	UPDATE_NAVMESH_BLOCKING_OBJECT(0x109E99373F290687);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	SET_PED_PATHS_BACK_TO_ORIGINAL(0xE04B48F2CC926253);
lazy_func_t<Any()> _0x869DAACBBE9FA006(0x869DAACBBE9FA006);
lazy_func_t<BOOL(int vehicleNodeId)>
	IS_VEHICLE_NODE_ID_VALID(0x1EAF30FCFBF5AF74);
lazy_func_t<void(float p0)> _0x0B919E1FB47CC4E0(0x0B919E1FB47CC4E0);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	float angle,
	BOOL unknown1,
	BOOL unknown2,
	BOOL unknown3)>
	SET_ROADS_IN_ANGLED_AREA(0x1A5AA1208AF5DB59);
lazy_func_t<Any(float p0, float p1, float p2, float p3, float p4, float p5)>
	_0x01708E8DD3FF8C65(0x01708E8DD3FF8C65);
lazy_func_t<
	int(float x, float y, float z, int nth, int nodetype, float p5, float p6)>
	GET_NTH_CLOSEST_VEHICLE_NODE_ID(0x22D7275A79FE8215);
lazy_func_t<void(BOOL p0)> _0x228E5C6AD4D74BFD(0x228E5C6AD4D74BFD);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)>
	_0xAA76052DDA9BFC3E(0xAA76052DDA9BFC3E);
lazy_func_t<void(BOOL ignore)> SET_IGNORE_NO_GPS_FLAG(0x72751156E7678833);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	Vector3 *outPosition,
	int nodeType,
	float p5,
	float p6)>
	GET_CLOSEST_VEHICLE_NODE(0x240A18690AE96513);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	Vector3 *outPosition,
	float *outHeading,
	int nodeType,
	float p6,
	int p7)>
	GET_CLOSEST_VEHICLE_NODE_WITH_HEADING(0xFF071FB798B803B0);
lazy_func_t<void()> REMOVE_NAVMESH_REQUIRED_REGIONS(0x916F0A3CDEC3445E);
lazy_func_t<float(float p0, float p1)> _0x29C24BFBED8AB8FB(0x29C24BFBED8AB8FB);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3, Any p4)>
	_0x16F46FB18C8009E4(0x16F46FB18C8009E4);
lazy_func_t<float(float p0, float p1, float p2, float p3)>
	_0x8ABE8608576D9CE3(0x8ABE8608576D9CE3);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	int nthClosest,
	Vector3 *outPosition,
	Any unknown1,
	Any unknown2,
	Any unknown3)>
	GET_NTH_CLOSEST_VEHICLE_NODE(0xE50E52416CCF948B);
lazy_func_t<void(float p0, float p1, float p2, float p3, float p4, float p5)>
	SET_ROADS_BACK_TO_ORIGINAL(0x1EE7063B80FFC77C);
lazy_func_t<BOOL(float x, float y, float z, int *density, int *flags)>
	GET_VEHICLE_NODE_PROPERTIES(0x0568566ACBB5DEDC);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	int nthClosest,
	Vector3 *outPosition,
	float *heading,
	Any *unknown1,
	int unknown2,
	float unknown3,
	float unknown4)>
	GET_NTH_CLOSEST_VEHICLE_NODE_WITH_HEADING(0x80CA6A8B6C094CC4);
lazy_func_t<
	Any(float x,
		float y,
		float z,
		int nthClosest,
		Vector3 *outPosition,
		float outHeading,
		Any p6,
		float p7,
		float p8)>
	GET_NTH_CLOSEST_VEHICLE_NODE_ID_WITH_HEADING(0x6448050E9C2A7207);
lazy_func_t<BOOL(int nodeID)> _GET_IS_SLOW_ROAD_FLAG(0x4F5070AA58F69279);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)>
	DISABLE_NAVMESH_IN_AREA(0x4C8872D8CDBE1B8B);
lazy_func_t<void(
	float x1, float y1, float z1, float x2, float y2, float z2, BOOL unknown)>
	SET_PED_PATHS_IN_AREA(0x34F060F4BF92E018);
lazy_func_t<BOOL(float x, float y, float z, Vehicle vehicle)>
	IS_POINT_ON_ROAD(0x125BF4ABFC536B09);
lazy_func_t<Any()> _0xD3A6A0EF48823A8C(0xD3A6A0EF48823A8C);
lazy_func_t<void(Any p0)> REMOVE_NAVMESH_BLOCKING_OBJECT(0x46399A7895957C0E);
lazy_func_t<float(float left, float right)>
	_0x336511A34F2E5185(0x336511A34F2E5185);
lazy_func_t<float(float p0, float p1, float p2, float p3)>
	_0x3599D741C9AC6310(0x3599D741C9AC6310);
lazy_func_t<void(int nodeId, Vector3 *outPosition)>
	GET_VEHICLE_NODE_POSITION(0x703123E5E7D429C2);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	SET_GPS_DISABLED_ZONE(0xDC20483CD3DD5201);
lazy_func_t<BOOL(BOOL keepInMemory)> LOAD_ALL_PATH_NODES(0x80E4A6EDDB0BE8D9);
lazy_func_t<BOOL(float p0, float p1, float p2, float p3)>
	_0xF7B79A50B905A30D(0xF7B79A50B905A30D);
lazy_func_t<
	void(float x, float y, float z, Hash *streetName, Hash *crossingRoad)>
	GET_STREET_NAME_AT_COORD(0x2EB41072B4C1E4C0);
lazy_func_t<Any(BOOL p0)> _0x1FC289A0C3FF470F(0x1FC289A0C3FF470F);
lazy_func_t<BOOL()> ARE_ALL_NAVMESH_REGIONS_LOADED(0x8415D95B194A3AEA);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	Vector3 *outPosition,
	float unknown1,
	int unknown2)>
	GET_CLOSEST_MAJOR_VEHICLE_NODE(0x2EABE3B06F58C1BE);
lazy_func_t<
	Any(float x,
		float y,
		float z,
		float p3,
		int p4,
		Vector3 *p5,
		Vector3 *p6,
		Any *p7,
		Any *p8,
		float *p9,
		BOOL p10)>
	GET_CLOSEST_ROAD(0x132F52BBA570FE92);
lazy_func_t<BOOL(int nodeID)> _GET_SUPPORTS_GPS_ROUTE_FLAG(0xA2AE5C478B96E3B6);
lazy_func_t<
	int(float x,
		float y,
		float z,
		BOOL p3,
		float *direction,
		float *vehicle,
		float *distToNxJunction)>
	GENERATE_DIRECTIONS_TO_COORD(0xF90125F1F79ECDF8);
}} // namespace PATHFIND::
namespace INTERIOR { namespace {
lazy_func_t<Vector3(int interiorID, float x, float y, float z)>
	GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(0x9E3B3E6D66F6E22F);
lazy_func_t<Hash(Entity entity)> GET_KEY_FOR_ENTITY_IN_ROOM(0x399685DB942336BC);
lazy_func_t<int(float x, float y, float z)>
	GET_INTERIOR_AT_COORDS(0xB0F7F8663821D9C3);
lazy_func_t<BOOL(int interiorID)> IS_INTERIOR_READY(0x6726BDCCC1932F0E);
lazy_func_t<int(float x, float y, float z)>
	GET_INTERIOR_FROM_COLLISION(0xEC4CF9FCB29A4424);
lazy_func_t<void(int interiorID, BOOL toggle)>
	DISABLE_INTERIOR(0x6170941419D7D8EC);
lazy_func_t<Hash(Entity entity)> GET_ROOM_KEY_FROM_ENTITY(0x47C2A06D4F5F424B);
lazy_func_t<void(Hash roomHashKey)> _0x405DC2AEF6AF95B9(0x405DC2AEF6AF95B9);
lazy_func_t<Hash()> _GET_ROOM_KEY_FROM_GAMEPLAY_CAM(0xA6575914D2A0B450);
lazy_func_t<void(int interiorID)> REFRESH_INTERIOR(0x41F37C3427C75AE0);
lazy_func_t<void(Hash mapObjectHash)>
	_HIDE_MAP_OBJECT_THIS_FRAME(0xA97F257D0151A6AB);
lazy_func_t<BOOL()> IS_INTERIOR_SCENE(0xBC72B5D7A1CBD54D);
lazy_func_t<void(Entity entity, int interiorID)>
	_0x82EBB79E258FA2B7(0x82EBB79E258FA2B7);
lazy_func_t<void(int interiorID)> _LOAD_INTERIOR(0x2CA429C029CCF247);
lazy_func_t<void(BOOL toggle)> _0x9E6542F0CE8E70A3(0x9E6542F0CE8E70A3);
lazy_func_t<int(int interiorID)> GET_INTERIOR_GROUP_ID(0xE4A84ABF135EF91A);
lazy_func_t<int(Entity entity)> GET_INTERIOR_FROM_ENTITY(0x2107BA504071A6BB);
lazy_func_t<void(int interiorID)> UNPIN_INTERIOR(0x261CCE7EED010641);
lazy_func_t<int(float x, float y, float z, const char *interiorType)>
	GET_INTERIOR_AT_COORDS_WITH_TYPE(0x05B7A89BD78797FC);
lazy_func_t<int(float x, float y, float z, int unk)>
	_UNK_GET_INTERIOR_AT_COORDS(0xF0F77ADB9F67E79D);
lazy_func_t<void()> _0x23B59D8912F94246(0x23B59D8912F94246);
lazy_func_t<void(Pickup pickup, const char *roomName)>
	ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(0x3F6167F351168730);
lazy_func_t<void(int interiorID, const char *propName)>
	_DISABLE_INTERIOR_PROP(0x420BD37289EEE162);
lazy_func_t<BOOL(int interiorID, const char *propName)>
	_IS_INTERIOR_PROP_ENABLED(0x35F7DD45E8C0A16D);
lazy_func_t<BOOL(int interiorID)> IS_INTERIOR_CAPPED(0x92BAC8ACF88CEC26);
lazy_func_t<void(Entity entity)> CLEAR_ROOM_FOR_ENTITY(0xB365FC0C4E27FFA7);
lazy_func_t<void(Entity entity, int interiorID, Hash roomHashKey)>
	FORCE_ROOM_FOR_ENTITY(0x52923C4710DD9907);
lazy_func_t<void(int interiorID, const char *propName)>
	_ENABLE_INTERIOR_PROP(0x55E86AF2712B36A1);
lazy_func_t<BOOL(int interiorID)> IS_INTERIOR_DISABLED(0xBC5115A5A939DD15);
lazy_func_t<BOOL(int interiorID)> IS_VALID_INTERIOR(0x26B0E73D7EAAF4D3);
lazy_func_t<void(int interiorID, Hash roomHashKey)>
	_0x920D853F3E17F1DA(0x920D853F3E17F1DA);
lazy_func_t<void(const char *roomName)> _0xAF348AFCB575A441(0xAF348AFCB575A441);
lazy_func_t<Any(int interiorID)> _0x4C2330E61D3DEB56(0x4C2330E61D3DEB56);
lazy_func_t<BOOL(float x, float y, float z)>
	_ARE_COORDS_COLLIDING_WITH_EXTERIOR(0xEEA5AC2EDA7C33E8);
lazy_func_t<void(int interiorID, BOOL toggle)> CAP_INTERIOR(0xD9175F941610DB54);
}} // namespace INTERIOR::
namespace SCRIPT { namespace {
lazy_func_t<const char *()> GET_THIS_SCRIPT_NAME(0x442E0A7EDE4A738A);
lazy_func_t<void()> SHUTDOWN_LOADING_SCREEN(0x078EBE9809CCD637);
lazy_func_t<const char *(int threadId)> _GET_NAME_OF_THREAD(0x05A42BA9FC8DA96B);
lazy_func_t<void()> _BEGIN_ENUMERATING_THREADS(0xDADFADA5A20143A8);
lazy_func_t<BOOL(int eventGroup, int eventIndex)>
	GET_EVENT_EXISTS(0x936E6168A9BCEDB5);
lazy_func_t<void(int threadId)> TERMINATE_THREAD(0xC8B189ED9138BCD4);
lazy_func_t<void(Hash scriptHash)>
	SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(0xC5BC038960E9DB27);
lazy_func_t<int()> _GET_ID_OF_NEXT_THREAD_IN_ENUMERATION(0x30B4FA1C82DD4B9F);
lazy_func_t<void(int eventGroup, int *args, int argCount, int bit)>
	TRIGGER_SCRIPT_EVENT(0x5AE99C571D5BBE5D);
lazy_func_t<BOOL(const char *scriptName)> HAS_SCRIPT_LOADED(0xE6CC9F3BA0FB9EF1);
lazy_func_t<BOOL(Hash scriptHash)>
	HAS_SCRIPT_WITH_NAME_HASH_LOADED(0x5F0F0C783EB16C04);
lazy_func_t<BOOL(Hash scriptHash)>
	_DOES_SCRIPT_WITH_NAME_HASH_EXIST(0xF86AA3C56BA31381);
lazy_func_t<Hash()> GET_HASH_OF_THIS_SCRIPT_NAME(0x8A1C8B1738FFE87E);
lazy_func_t<int(int eventGroup, int eventIndex)>
	GET_EVENT_AT_INDEX(0xD8F66A3A60C62153);
lazy_func_t<void()> _0xB1577667C3708F9B(0xB1577667C3708F9B);
lazy_func_t<void(const char *scriptName)>
	SET_SCRIPT_AS_NO_LONGER_NEEDED(0xC90D2DCACD56184C);
lazy_func_t<int(Hash scriptHash)>
	_GET_NUMBER_OF_INSTANCES_OF_SCRIPT_WITH_NAME_HASH(0x2C83A9DA6BFFC4F9);
lazy_func_t<int(int eventGroup)> GET_NUMBER_OF_EVENTS(0x5F92A689A06620AA);
lazy_func_t<void(const char *scriptName)> REQUEST_SCRIPT(0x6EB5F71AA68F2E8E);
lazy_func_t<BOOL(int threadId)> IS_THREAD_ACTIVE(0x46E9AE36D8FA6417);
lazy_func_t<int()> GET_ID_OF_THIS_THREAD(0xC30338E8088E2E21);
lazy_func_t<void()> TERMINATE_THIS_THREAD(0x1090044AD1DA76FA);
lazy_func_t<
	BOOL(int eventGroup, int eventIndex, int *argStruct, int argStructSize)>
	GET_EVENT_DATA(0x2902843FCD2B2D79);
lazy_func_t<void(Hash scriptHash)>
	REQUEST_SCRIPT_WITH_NAME_HASH(0xD62A67D26D9653E6);
lazy_func_t<BOOL(const char *scriptName)> DOES_SCRIPT_EXIST(0xFC04745FBE67C19A);
lazy_func_t<void(BOOL toggle)> SET_NO_LOADING_SCREEN(0x5262CC1995D07E09);
lazy_func_t<BOOL()> _GET_NO_LOADING_SCREEN(0x18C1270EA7F199BC);
}} // namespace SCRIPT::
namespace BRAIN { namespace {
lazy_func_t<void(const char *action)> _0x6E91B04E08773030(0x6E91B04E08773030);
lazy_func_t<void(const char *name, Hash model, float p2, float p3)>
	ADD_SCRIPT_TO_RANDOM_PED(0x4EE5367468A65CCC);
lazy_func_t<void(
	const char *scriptName, Hash objectName, int p2, float p3, int p4, int p5)>
	REGISTER_OBJECT_SCRIPT_BRAIN(0x0BE84C318BA6EC22);
lazy_func_t<void(Any *p0, float p1, Any p2)>
	REGISTER_WORLD_POINT_SCRIPT_BRAIN(0x3CDC7136613284BD);
lazy_func_t<void(int brainSet)> DISABLE_SCRIPT_BRAIN_SET(0x14D8518E9760F08F);
lazy_func_t<void()> _0x0B40ED49D7D6FF84(0x0B40ED49D7D6FF84);
lazy_func_t<void()> _0x4D953DF78EBF8158(0x4D953DF78EBF8158);
lazy_func_t<void(const char *action)> _0x6D6840CEE8845831(0x6D6840CEE8845831);
lazy_func_t<BOOL(Object object)>
	IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(0xCCBA154209823057);
lazy_func_t<BOOL()>
	IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE(0xC5042CC6F5E3D450);
lazy_func_t<void(int brainSet)> ENABLE_SCRIPT_BRAIN_SET(0x67AA4D73F0CFA86B);
}} // namespace BRAIN::
namespace NETWORK { namespace {
lazy_func_t<void()> NETWORK_GET_PRIMARY_CLAN_DATA_CANCEL(0x042E4B70B93E6054);
lazy_func_t<BOOL(Any p0)> _0x631DC5DFF4B110E3(0x631DC5DFF4B110E3);
lazy_func_t<void(BOOL p0)> _0x39917E1B4CB0F911(0x39917E1B4CB0F911);
lazy_func_t<BOOL(int *networkHandle, Any *p1, Any p2, Any p3)>
	_NETWORK_SEND_PRESENCE_INVITE(0xC3C7A6AFDB244624);
lazy_func_t<BOOL(Any p0, Any *p1)>
	NETWORK_GET_PRESENCE_INVITE_HANDLE(0x38D5B0FEBB086F75);
lazy_func_t<void(BOOL p0)> _0x1B857666604B1A74(0x1B857666604B1A74);
lazy_func_t<void(BOOL p0)> _0x0FF2862B61A58AF9(0x0FF2862B61A58AF9);
lazy_func_t<void()> _DOWNLOAD_CHECK(0x4F18196C8D38768D);
lazy_func_t<BOOL()> _0x422D396F80A96547(0x422D396F80A96547);
lazy_func_t<
	void(float x, float y, float z, float heading, BOOL unk, BOOL changetime)>
	NETWORK_RESURRECT_LOCAL_PLAYER(0xEA23C49EAA83ACFB);
lazy_func_t<void(Entity entity)> _0x715135F4B82AC90D(0x715135F4B82AC90D);
lazy_func_t<void(Entity entity, BOOL normal, BOOL slow)>
	NETWORK_FADE_OUT_ENTITY(0xDE564951F95E09ED);
lazy_func_t<Any(Vehicle vehicle, BOOL isAudible, BOOL isInvisible, BOOL p3)>
	NETWORK_EXPLODE_VEHICLE(0x301A42153C9AD707);
lazy_func_t<Any(Any p0, Any p1)> _0x6F44CBF56D79FAC0(0x6F44CBF56D79FAC0);
lazy_func_t<void(BOOL p0)> _NETWORK_SESSION_HOSTED(0xC19F6C8E7865A6FF);
lazy_func_t<BOOL()> NETWORK_CAN_BAIL(0x580CE4438479CC61);
lazy_func_t<int(BOOL p0)> NETWORK_GET_ACTIVITY_PLAYER_NUM(0x73E2B500410DA5A2);
lazy_func_t<int(BOOL p0)> GET_NUM_RESERVED_MISSION_PEDS(0x1F13D5AE5CB17E17);
lazy_func_t<Any()> _0x9FEDF86898F100E9(0x9FEDF86898F100E9);
lazy_func_t<void()> NETWORK_CLEAR_FOLLOWERS(0x058F43EC59A8631A);
lazy_func_t<void()> _0xEBF8284D8CADEB53(0xEBF8284D8CADEB53);
lazy_func_t<void(Any p0)> _0xF1B84178F8674195(0xF1B84178F8674195);
lazy_func_t<int()> NETWORK_GET_NUM_PARTICIPANTS(0x18D0456E86604654);
lazy_func_t<Entity(int netHandle)> NET_TO_ENT(0xBFFEAB45A9A9094A);
lazy_func_t<void(Any p0)> _0xCAE55F48D3D7875C(0xCAE55F48D3D7875C);
lazy_func_t<BOOL()> NETWORK_IS_ACTIVITY_SESSION(0x05095437424397FA);
lazy_func_t<void(const char *memberId, int *networkHandle, int bufferSize)>
	NETWORK_HANDLE_FROM_MEMBER_ID(0xA0FD21BED61E5C4C);
lazy_func_t<void()> NETWORK_CLEAR_CLOCK_TIME_OVERRIDE(0xD972DF67326F966E);
lazy_func_t<BOOL()> _IS_SOCIALCLUB_BANNED(0xA0AD7E2AF5349F61);
lazy_func_t<int(const char *scriptName, int p1, int p2)>
	NETWORK_GET_HOST_OF_SCRIPT(0x1D6A14F1F9A736FC);
lazy_func_t<void(BOOL p0)> _0x77758139EC9B66C7(0x77758139EC9B66C7);
lazy_func_t<void(BOOL toggle)> SET_STORE_ENABLED(0x9641A9FF718E9C5E);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any *p3, Any p4, BOOL p5)>
	_0x692D58DF40657E8C(0x692D58DF40657E8C);
lazy_func_t<Any()> _0x59328EB08C5CEB2B(0x59328EB08C5CEB2B);
lazy_func_t<Any(Any p0, Any p1)> _0x171DF6A0C07FB3DC(0x171DF6A0C07FB3DC);
lazy_func_t<BOOL()> NETWORK_HAVE_ONLINE_PRIVILEGES(0x25CB5A9F37BFD063);
lazy_func_t<Any(Any p0)> _0x742B58F723233ED9(0x742B58F723233ED9);
lazy_func_t<void(int netID, BOOL toggle)>
	_NETWORK_SET_NETWORK_ID_DYNAMIC(0x2B1813ABA29016C5);
lazy_func_t<BOOL(const char *tunableContext, const char *tunableName)>
	NETWORK_ACCESS_TUNABLE_BOOL(0xAA6A47A573ABB75A);
lazy_func_t<BOOL(Hash tunableContext, Hash tunableName, int *value)>
	_NETWORK_ACCESS_TUNABLE_INT_HASH(0x40FCE03E50E8DBE8);
lazy_func_t<void(int randomInt, Vector3 *coordinates, float *heading)>
	NETWORK_GET_RESPAWN_RESULT(0x371EA43692861CF1);
lazy_func_t<
	BOOL(const char *tunableContext, const char *tunableName, int *value)>
	NETWORK_ACCESS_TUNABLE_INT(0x8BE1146DFD5D4468);
lazy_func_t<void()> _0x17440AA15D1D3739(0x17440AA15D1D3739);
lazy_func_t<Any()> _0xA306F470D1660581(0xA306F470D1660581);
lazy_func_t<BOOL(Any p0)> _0x72D918C99BCACC54(0x72D918C99BCACC54);
lazy_func_t<void(BOOL p0)>
	NETWORK_SESSION_BLOCK_JOIN_REQUESTS(0xA73667484D7037C3);
lazy_func_t<void()> NETWORK_REMOVE_ALL_TRANSITION_INVITE(0x726E0375C7A26368);
lazy_func_t<Player(int *networkHandle)>
	NETWORK_GET_PLAYER_FROM_GAMER_HANDLE(0xCE5F689CF5A0A49D);
lazy_func_t<BOOL(Any p0)> _0xAEAB987727C5A8A4(0xAEAB987727C5A8A4);
lazy_func_t<void()> _0xB7C7F6AD6424304B(0xB7C7F6AD6424304B);
lazy_func_t<BOOL(Player player)>
	NETWORK_IS_PLAYER_IN_MP_CUTSCENE(0x63F9EE203C3619F2);
lazy_func_t<BOOL()> _HAS_BG_SCRIPT_BEEN_DOWNLOADED(0x8132C0EB8B2B3293);
lazy_func_t<BOOL(Hash tunableContext, Hash tunableName, float *value)>
	_NETWORK_ACCESS_TUNABLE_FLOAT_HASH(0x972BC203BBC4C4D5);
lazy_func_t<BOOL()> _0xEF0912DDF7C4CB4B(0xEF0912DDF7C4CB4B);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any p3)>
	NETWORK_DO_TRANSITION_QUICKMATCH_ASYNC(0xA091A5E44F0072E5);
lazy_func_t<Any()> _0x14922ED3E38761F0(0x14922ED3E38761F0);
lazy_func_t<BOOL(int *clanDesc, int bufferSize)>
	_0x7543BB439F63792B(0x7543BB439F63792B);
lazy_func_t<Any()> _0xC7BE335216B5EC7C(0xC7BE335216B5EC7C);
lazy_func_t<BOOL(Any p0)> _0x8C8D2739BA44AF0F(0x8C8D2739BA44AF0F);
lazy_func_t<BOOL()> _FACEBOOK_SET_CREATE_CHARACTER_COMPLETE(0xDC48473142545431);
lazy_func_t<void()> _0x83FE8D7229593017(0x83FE8D7229593017);
lazy_func_t<void()> NETWORK_SESSION_VOICE_HOST(0x9C1556705F864230);
lazy_func_t<BOOL(int friendIndex)>
	NETWORK_IS_FRIEND_INDEX_ONLINE(0xBAD8F2A42B844821);
lazy_func_t<Any(Any p0)> _0x662635855957C411(0x662635855957C411);
lazy_func_t<void()> _0x2302C0264EA58D31(0x2302C0264EA58D31);
lazy_func_t<BOOL(int *clanDesc, int bufferSize, int *networkHandle)>
	NETWORK_CLAN_PLAYER_GET_DESC(0xEEE6EACBE8874FBA);
lazy_func_t<BOOL(Any *p0, Any p1, BOOL p2, Any *p3)>
	_0xC7397A83F7A2A462(0xC7397A83F7A2A462);
lazy_func_t<Any(Any p0, Any p1)> _GET_CONTENT_FILE_VERSION(0x37025B27D9B658B1);
lazy_func_t<BOOL(int milestoneId)>
	_FACEBOOK_SET_MILESTONE_COMPLETE(0x0AE1F1653B554AB9);
lazy_func_t<BOOL(
	Player player,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	int flags)>
	_0x5A6FFA2433E2F14C(0x5A6FFA2433E2F14C);
lazy_func_t<void()> NETWORK_END_TUTORIAL_SESSION(0xD0AFAFF5A51D72F7);
lazy_func_t<Any()> _0xD38C4A6D047C019D(0xD38C4A6D047C019D);
lazy_func_t<Any()> _0xA8ACB6459542A8C8(0xA8ACB6459542A8C8);
lazy_func_t<void()> NETWORK_SESSION_CANCEL_INVITE(0x2FBF47B1B36D36F9);
lazy_func_t<BOOL(Player player)> NETWORK_JOIN_TRANSITION(0x9D060B08CD63321A);
lazy_func_t<BOOL(Player player)>
	NETWORK_IS_PLAYER_CONNECTED(0x93DC1BE4E1ABE9D1);
lazy_func_t<const char *(Player player)>
	NETWORK_PLAYER_GET_NAME(0x7718D2E2060837D2);
lazy_func_t<BOOL(Any p0)> _0x3054F114121C21EA(0x3054F114121C21EA);
lazy_func_t<BOOL(Any *p0)> NETWORK_IS_GAMER_BLOCKED_BY_ME(0xE944C4F5AF1B5883);
lazy_func_t<void(Any p0, Any *p1)> _0xCFD115B373C0DF63(0xCFD115B373C0DF63);
lazy_func_t<Any()> _0x66B59CFFD78467AF(0x66B59CFFD78467AF);
lazy_func_t<BOOL(float p0, float p1, float p2, float p3)>
	IS_SPHERE_VISIBLE_TO_ANOTHER_MACHINE(0xD82CF8E64C8729D8);
lazy_func_t<Any()> _0xEDF7F927136C224B(0xEDF7F927136C224B);
lazy_func_t<BOOL(Any p0)> _0x993CBE59D350D225(0x993CBE59D350D225);
lazy_func_t<void()> _0x283B6062A2C01E9B(0x283B6062A2C01E9B);
lazy_func_t<Any()> _0x01ABCE5E7CBDA196(0x01ABCE5E7CBDA196);
lazy_func_t<int()> NETWORK_GET_RANDOM_INT(0x599E4FA1F87EB5FF);
lazy_func_t<BOOL(const char *name)>
	NETWORK_IS_FRIEND_ONLINE(0x425A44533437B64D);
lazy_func_t<void(BOOL toggle)> NETWORK_SET_TEAM_ONLY_CHAT(0xD5B4883AC32F24C3);
lazy_func_t<void(Any p0)> _0x5B8ED3DB018927B1(0x5B8ED3DB018927B1);
lazy_func_t<BOOL(Player player)> NETWORK_IS_PLAYER_ACTIVE(0xB8DFD30D6973E135);
lazy_func_t<
	int(float x,
		float y,
		float z,
		float xRot,
		float yRot,
		float zRot,
		int p6,
		int p7,
		int p8,
		float p9)>
	NETWORK_CREATE_SYNCHRONISED_SCENE(0x7CD6BC4C2BBDD526);
lazy_func_t<Any(Any p0)> _0xCA94551B50B4932C(0xCA94551B50B4932C);
lazy_func_t<BOOL(Player player, int index)>
	_NETWORK_IS_PLAYER_EQUAL_TO_INDEX(0x9DE986FC9A87C474);
lazy_func_t<void()> _0x265635150FB0D82E(0x265635150FB0D82E);
lazy_func_t<Any()> _0xC87E740D9F3872CC(0xC87E740D9F3872CC);
lazy_func_t<BOOL()> _FACEBOOK_DO_UNK_CHECK(0xA75E2B6733DA5142);
lazy_func_t<BOOL()> NETWORK_IS_CABLE_CONNECTED(0xEFFB25453D8600F9);
lazy_func_t<void(BOOL p0)> _NETWORK_BLOCK_KICKED_PLAYERS(0x6B07B9CE4D390375);
lazy_func_t<BOOL(Any p0)>
	NETWORK_ARE_TRANSITION_DETAILS_VALID(0x2615AA2A695930C1);
lazy_func_t<BOOL(Any *p0)> _0x3F9990BF5F22759C(0x3F9990BF5F22759C);
lazy_func_t<BOOL(Any p0)> _0xE64A3CA08DFA37A9(0xE64A3CA08DFA37A9);
lazy_func_t<BOOL(Any p0)> _0x162C23CA83ED0A62(0x162C23CA83ED0A62);
lazy_func_t<BOOL(Player p0, Any *p1, Any p2)>
	_0x1AD5B71586B94820(0x1AD5B71586B94820);
lazy_func_t<BOOL(const char *friendName)>
	NETWORK_IS_FRIEND_IN_MULTIPLAYER(0x57005C18827F3A28);
lazy_func_t<BOOL(Any p0)> _0x4A2D4E8BF4265B0F(0x4A2D4E8BF4265B0F);
lazy_func_t<Any()> _0x7DB53B37A2F211A0(0x7DB53B37A2F211A0);
lazy_func_t<Any()> _0xFFE1E5B792D92B34(0xFFE1E5B792D92B34);
lazy_func_t<Any()> _0x2CC848A861D01493(0x2CC848A861D01493);
lazy_func_t<Any()> _0x94A8394D150B013A(0x94A8394D150B013A);
lazy_func_t<BOOL(BOOL p0, int maxPlayers, BOOL p2)>
	NETWORK_DO_TRANSITION_TO_NEW_GAME(0x4665F51EFED00034);
lazy_func_t<BOOL(Any *p0, Any *p1)> _0xB746D20B17F2A229(0xB746D20B17F2A229);
lazy_func_t<void(Any p0)> NETWORK_SET_PROPERTY_ID(0x1775961C2FBBCB5C);
lazy_func_t<Any()> _0x24E4E51FC16305F9(0x24E4E51FC16305F9);
lazy_func_t<Any()> _0x5AE17C6B0134B7F1(0x5AE17C6B0134B7F1);
lazy_func_t<BOOL(int *networkHandle, const char *p1, int p2, int p3, BOOL p4)>
	NETWORK_SEND_TRANSITION_GAMER_INSTRUCTION(0x31D1D2B858D25E6B);
lazy_func_t<void(BOOL p0)> _NETWORK_BLOCK_INVITES_2(0x4A9FDE3A5A6D0437);
lazy_func_t<void(Any *p0, Any *p1)> _0x0D77A82DC2D0DA59(0x0D77A82DC2D0DA59);
lazy_func_t<void(Player friendIndex, int *networkHandle, int bufferSize)>
	NETWORK_HANDLE_FROM_FRIEND(0xD45CB817D7E177D2);
lazy_func_t<BOOL(int timeA, int timeB)> IS_TIME_LESS_THAN(0xCB2CF5148012C8D0);
lazy_func_t<BOOL(Hash tunableContext, Hash tunableName, BOOL defaultValue)>
	_NETWORK_ACCESS_TUNABLE_BOOL_HASH_FAIL_VAL(0xC7420099936CE286);
lazy_func_t<Any(Any *p0, Any *p1, Any p2, Any p3, Any p4)>
	_0x7FD2990AF016795E(0x7FD2990AF016795E);
lazy_func_t<Any()> _0x9614B71F8ADB982B(0x9614B71F8ADB982B);
lazy_func_t<BOOL()> NETWORK_PLAYER_IS_CHEATER(0x655B91F1495A9090);
lazy_func_t<int(int index)> NETWORK_GET_PARTICIPANT_INDEX(0x1B84DF6AF2A46938);
lazy_func_t<BOOL(Entity entity)>
	NETWORK_REQUEST_CONTROL_OF_ENTITY(0xB69317BF5E782347);
lazy_func_t<void(BOOL toggle)>
	NETWORK_SET_OVERRIDE_SPECTATOR_MODE(0x70DA3BF8DACD3210);
lazy_func_t<Any()> _0x45E816772E93A9DB(0x45E816772E93A9DB);
lazy_func_t<BOOL()> NETWORK_IS_SESSION_BUSY(0xF4435D66A8E2905E);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any p3, Any *p4, Any p5)>
	NETWORK_DO_TRANSITION_QUICKMATCH_WITH_GROUP(0x9C4AB58491FDC98A);
lazy_func_t<BOOL(Any *p0)>
	NETWORK_MARK_TRANSITION_GAMER_AS_FULLY_JOINED(0x5728BB6D63E3FF1D);
lazy_func_t<void(BOOL p0)> _0x3C5C1E2C2FF814B1(0x3C5C1E2C2FF814B1);
lazy_func_t<BOOL(Any p0)> _0x70EA8DA57840F9BE(0x70EA8DA57840F9BE);
lazy_func_t<BOOL()> NETWORK_SESSION_IS_CLOSED_FRIENDS(0xFBCFA2EA2E206890);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_IS_ACTIVITY_SPECTATOR_FROM_HANDLE(0x2763BBAA72A7BCB9);
lazy_func_t<BOOL(const char *animDict, const char *animName)>
	_NETWORK_CLAN_ANIMATION(0x729E3401F0430686);
lazy_func_t<Any()> _0x91B87C55093DE351(0x91B87C55093DE351);
lazy_func_t<void(BOOL p0)>
	SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(0xE5F773C1A1D9D168);
lazy_func_t<void(int netScene)>
	NETWORK_STOP_SYNCHRONISED_SCENE(0xC254481A4574CB2F);
lazy_func_t<void()> _0xBA96394A0EECFA65(0xBA96394A0EECFA65);
lazy_func_t<void(int p0)> _NETWORK_SCTV_SLOTS(0x49EC8030F5015F8B);
lazy_func_t<Any()> _0xC42DD763159F3461(0xC42DD763159F3461);
lazy_func_t<void()> NETWORK_OPEN_TRANSITION_MATCHMAKING(0x2B3A8F7CA3A38FDE);
lazy_func_t<Entity(Player player, Hash *weaponHash)>
	NETWORK_GET_ENTITY_KILLER_OF_PLAYER(0x42B2DAA6B596F5F8);
lazy_func_t<BOOL(int *netHandle1, int *netHandle2)>
	NETWORK_ARE_HANDLES_THE_SAME(0x57DBA049E110F217);
lazy_func_t<BOOL(Any p0)> _0xA9240A96C74CCA13(0xA9240A96C74CCA13);
lazy_func_t<BOOL(int p0)> TEXTURE_DOWNLOAD_HAS_FAILED(0x5776ED562C134687);
lazy_func_t<Any(Any p0, Any p1, Any p2, int maxPlayers, Any p4, Any p5)>
	NETWORK_SESSION_ENTER(0x330ED4D05491934F);
lazy_func_t<BOOL(Any *p0, Any *p1, int players, BOOL p3, BOOL p4, BOOL p5)>
	NETWORK_DO_TRANSITION_TO_NEW_FREEMODE(0x9E80A5BA8109F974);
lazy_func_t<void(Any p0)> _0x4811BBAC21C5FCD5(0x4811BBAC21C5FCD5);
lazy_func_t<BOOL(Any p0)> _0x8806CEBFABD3CE05(0x8806CEBFABD3CE05);
lazy_func_t<void(int amount)> RESERVE_NETWORK_MISSION_PEDS(0xB60FEBA45333D36F);
lazy_func_t<Any(Any *p0)> _0x3C891A251567DFCE(0x3C891A251567DFCE);
lazy_func_t<Any(float p0, float p1, float p2, float p3, float p4, float p5)>
	NETWORK_ADD_ENTITY_AREA(0x494C8FB299290269);
lazy_func_t<Any()> _0x0AFCE529F69B21FF(0x0AFCE529F69B21FF);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any *p3)>
	_0xD5A4B59980401588(0xD5A4B59980401588);
lazy_func_t<BOOL()> NETWORK_IS_FINDING_GAMERS(0xDDDF64C91BFCF0AA);
lazy_func_t<BOOL()> NETWORK_SESSION_WAS_INVITED(0x23DFB504655D0CE4);
lazy_func_t<BOOL(Any p0)> NETWORK_ACCEPT_PRESENCE_INVITE(0xFA91550DF9318B22);
lazy_func_t<void(int netId, BOOL toggle)>
	SET_NETWORK_ID_CAN_MIGRATE(0x299EEB23175895FC);
lazy_func_t<void(Entity entity, BOOL toggle)>
	_NETWORK_SET_ENTITY_INVISIBLE_TO_NETWORK(0xF1CA12B18AEF5298);
lazy_func_t<Any(Any p0)> _0x24409FC4C55CB22D(0x24409FC4C55CB22D);
lazy_func_t<BOOL(const char *scriptName, Player player, BOOL p2, Any p3)>
	NETWORK_IS_SCRIPT_ACTIVE(0x9D40DF90FAD26098);
lazy_func_t<BOOL(Entity entity)>
	NETWORK_GET_ENTITY_IS_NETWORKED(0xC7827959479DCC78);
lazy_func_t<Any(Any p0, Any p1)> _0x87E5C46C187FE0AE(0x87E5C46C187FE0AE);
lazy_func_t<Any(Any p0, Any p1)> _0x4E548C0D7AE39FF9(0x4E548C0D7AE39FF9);
lazy_func_t<Any()> _0x597F8DBA9B206FC7(0x597F8DBA9B206FC7);
lazy_func_t<Any()> NETWORK_LEAVE_TRANSITION(0xD23A1A815D21DB19);
lazy_func_t<Any(Any p0)>
	NETWORK_GET_PRESENCE_INVITE_INVITER(0x4962CC4AA2F345B7);
lazy_func_t<BOOL()> NETWORK_IS_LOCAL_PLAYER_INVINCIBLE(0x8A8694B48715B000);
lazy_func_t<void(Entity entity, BOOL state)>
	NETWORK_FADE_IN_ENTITY(0x1F4ED342ACEFE62D);
lazy_func_t<Any(Any p0)> _0x3B39236746714134(0x3B39236746714134);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any *p3)>
	_0x3195F8DD0D531052(0x3195F8DD0D531052);
lazy_func_t<BOOL(Any p0)> _0x5CAE833B0EE0C500(0x5CAE833B0EE0C500);
lazy_func_t<void()> _0x1153FA02A659051C(0x1153FA02A659051C);
lazy_func_t<BOOL(int *p0, Any p1)>
	NETWORK_CLAN_GET_MEMBERSHIP_VALID(0x48A59CF88D43DF0E);
lazy_func_t<int(BOOL p0)> GET_NUM_RESERVED_MISSION_VEHICLES(0xCF3A965906452031);
lazy_func_t<void()> NETWORK_RESET_BODY_TRACKER(0x72433699B4E6DD64);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0xFAE628F1E9ADB239(0xFAE628F1E9ADB239);
lazy_func_t<Any()> NETWORK_GET_HOST_OF_THIS_SCRIPT(0xC7B4D79B01FA7A5C);
lazy_func_t<void(Entity entity)>
	NETWORK_UNREGISTER_NETWORKED_ENTITY(0x7368E683BB9038D6);
lazy_func_t<BOOL(Player *player, Any *p1)>
	_NETWORK_GET_PLAYER_CREW_EMBLEM_TXD_NAME(0x5835D9CD92E83184);
lazy_func_t<Any()> NETWORK_GET_PRIMARY_CLAN_DATA_CLEAR(0x9AA46BADAD0E27ED);
lazy_func_t<BOOL(Any p0, Any *p1)> _0x584770794D758C18(0x584770794D758C18);
lazy_func_t<void(Any *p0)> _0x66F010A4B031A331(0x66F010A4B031A331);
lazy_func_t<Player(Ped ped)>
	NETWORK_GET_PLAYER_INDEX_FROM_PED(0x6C0E2E0125610278);
lazy_func_t<void()> NETWORK_SET_MISSION_FINISHED(0x3B3D11CD9FFCDFC9);
lazy_func_t<void(Any p0)> _0xC9B43A33D09CADA7(0xC9B43A33D09CADA7);
lazy_func_t<Any()> _0x2EAC52B4019E2782(0x2EAC52B4019E2782);
lazy_func_t<Any()> _0xBA9775570DB788CF(0xBA9775570DB788CF);
lazy_func_t<void()> NETWORK_SESSION_LEAVE_SINGLE_PLAYER(0x3442775428FD2DAA);
lazy_func_t<void(int p0, const char *gxtLabel)>
	_NETWORK_SET_RICH_PRESENCE_2(0x3E200C2BCF4164EB);
lazy_func_t<BOOL(Any *p0)>
	NETWORK_CLAN_DOWNLOAD_MEMBERSHIP_PENDING(0x5B9E023DC6EBEDC0);
lazy_func_t<void()> _0xBD0BE0BFC927EAC1(0xBD0BE0BFC927EAC1);
lazy_func_t<Any()> _0x941E5306BCD7C2C7(0x941E5306BCD7C2C7);
lazy_func_t<Any()> _0xA0FA4EC6A05DA44E(0xA0FA4EC6A05DA44E);
lazy_func_t<BOOL()> NETWORK_IS_TRANSITION_STARTED(0x53FA83401D9C07FE);
lazy_func_t<BOOL(Any *p0)>
	NETWORK_GET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(
		0x74881E6BCAE2327C);
lazy_func_t<void(Any p0)> _0x77FADDCBE3499DF7(0x77FADDCBE3499DF7);
lazy_func_t<BOOL(Entity entity)>
	NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(0x18A47D074708FD68);
lazy_func_t<Any(Any p0)> _0xB4271092CA7EDF48(0xB4271092CA7EDF48);
lazy_func_t<Any(Any p0)> _0xDEB2B99A1AF1A2A6(0xDEB2B99A1AF1A2A6);
lazy_func_t<BOOL()> _NETWORK_IS_TEXT_CHAT_ACTIVE(0x5FCF4D7069B09026);
lazy_func_t<void(BOOL p0)> FADE_OUT_LOCAL_PLAYER(0x416DBD4CD6ED8DD2);
lazy_func_t<void()> _0x5C497525F803486B(0x5C497525F803486B);
lazy_func_t<BOOL()> NETWORK_IS_CLOUD_AVAILABLE(0x9A4CF4F48AD77302);
lazy_func_t<BOOL(Any p0, Any p1, BOOL p2)>
	_0x83F28CE49FBBFFBA(0x83F28CE49FBBFFBA);
lazy_func_t<void(BOOL p0)> _0x3F52E880AAF6C8CA(0x3F52E880AAF6C8CA);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any p3)>
	NETWORK_DO_TRANSITION_QUICKMATCH(0x71FB0EBCD4915D56);
lazy_func_t<void(Player p0, float *p1, float *p2)>
	_0xADB57E5B663CCA8B(0xADB57E5B663CCA8B);
lazy_func_t<void(Any p0)> _0x5E3AA4CA2B6FB0EE(0x5E3AA4CA2B6FB0EE);
lazy_func_t<BOOL(int netId)>
	_NETWORK_CAN_NETWORK_ID_BE_SEEN(0xA1607996431332DF);
lazy_func_t<int(int timeA, int timeB)> GET_TIME_DIFFERENCE(0xA2C6FC031D46FFF0);
lazy_func_t<BOOL(int p0, int maxPlayers)>
	NETWORK_SESSION_HOST_CLOSED(0xED34C0C02C098BB7);
lazy_func_t<BOOL()> NETWORK_SESSION_IS_SOLO(0xF3929C2379B60CCE);
lazy_func_t<void()> _0xF814FEC6A19FD6E0(0xF814FEC6A19FD6E0);
lazy_func_t<BOOL(Any *p0, Any *p1, Any p2, Any p3)>
	_0x1171A97A3D3981B6(0x1171A97A3D3981B6);
lazy_func_t<Any()> _0xC0D2AF00BCC234CA(0xC0D2AF00BCC234CA);
lazy_func_t<Any(Any p0)> _0x703F12425ECA8BF5(0x703F12425ECA8BF5);
lazy_func_t<Any()> _0xC7ABAC5DE675EE3B(0xC7ABAC5DE675EE3B);
lazy_func_t<Any()> _0xE0A6138401BCB837(0xE0A6138401BCB837);
lazy_func_t<BOOL(Player player)>
	_NETWORK_SESSION_IS_PLAYER_VOTED_TO_KICK(0xD6D09A6F32F49EF1);
lazy_func_t<Any()> _0x59DF79317F85A7E0(0x59DF79317F85A7E0);
lazy_func_t<Any()> NETWORK_LAUNCH_TRANSITION(0x2DCF46CB1A4F0884);
lazy_func_t<int(int netScene)>
	_NETWORK_CONVERT_SYNCHRONISED_SCENE_TO_SYNCHRONIZED_SCENE(
		0x02C40BF885C567B6);
lazy_func_t<void()> _0x444C4525ECE0A4B9(0x444C4525ECE0A4B9);
lazy_func_t<BOOL(int *p0, int *clanMembership, int p2)>
	NETWORK_CLAN_GET_MEMBERSHIP(0xC8BC2011F67B3411);
lazy_func_t<int()> GET_NETWORK_TIME(0x7A5487FE9FAA6B48);
lazy_func_t<BOOL(Any p0)> _0x4C61B39930D045DA(0x4C61B39930D045DA);
lazy_func_t<void(BOOL toggle)>
	NETWORK_SET_ACTIVITY_SPECTATOR(0x75138790B4359A74);
lazy_func_t<void(Any p0)> _0x524FF0AEFF9C3973(0x524FF0AEFF9C3973);
lazy_func_t<Object(int netHandle)> NET_TO_OBJ(0xD8515F5FEA14CB3F);
lazy_func_t<BOOL(int *networkHandle)> NETWORK_IS_FRIEND(0x1A24A179F9B31654);
lazy_func_t<BOOL(Any p0)> _0x82377B65E943F72D(0x82377B65E943F72D);
lazy_func_t<Any()> _0xC55A0B40FFB1ED23(0xC55A0B40FFB1ED23);
lazy_func_t<BOOL(Any p0)> _0x422F32CC7E56ABAD(0x422F32CC7E56ABAD);
lazy_func_t<void(BOOL toggle)>
	USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(0x5FFE9B4144F9712F);
lazy_func_t<Any(Any p0)> _0x722F5D28B61C5EA8(0x722F5D28B61C5EA8);
lazy_func_t<void()> NETWORK_SESSION_FORCE_CANCEL_INVITE(0xA29177F7703B5644);
lazy_func_t<BOOL()> NETWORK_HAS_FOLLOW_INVITE(0x76D9B976C4C09FDE);
lazy_func_t<void(int time)>
	NETWORK_SET_LOCAL_PLAYER_INVINCIBLE_TIME(0x2D95C7E2D7E07307);
lazy_func_t<BOOL(float x, float y, float z)>
	IS_NETWORK_VEHICLE_BEEN_DAMAGED_BY_ANY_OBJECT(0xDBD2056652689917);
lazy_func_t<BOOL()>
	_NETWORK_IS_CLAN_MEMBERSHIP_FINISHED_DOWNLOADING(0xB3F64A6A91432477);
lazy_func_t<void()> _0x68103E2247887242(0x68103E2247887242);
lazy_func_t<void(BOOL toggle)> NETWORK_SET_VOICE_ACTIVE(0xBABEC9E69A91C57B);
lazy_func_t<void(BOOL p0, BOOL p1)>
	SET_LOCAL_PLAYER_VISIBLE_IN_CUTSCENE(0xD1065D68947E7B6E);
lazy_func_t<BOOL(int netID)>
	IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(0x6E192E33AD436366);
lazy_func_t<BOOL(Any p0, Any p1)> _0xAEEF48CDF5B6CE7C(0xAEEF48CDF5B6CE7C);
lazy_func_t<BOOL(Any *p0, Any p1)> _0x02A8BEC6FD9AF660(0x02A8BEC6FD9AF660);
lazy_func_t<BOOL()> NETWORK_IS_IN_SESSION(0xCA97246103B63917);
lazy_func_t<void()> _0x25D990F8E0E3F13C(0x25D990F8E0E3F13C);
lazy_func_t<int()> NETWORK_GET_NUM_CONNECTED_PLAYERS(0xA4A79DD2D9600654);
lazy_func_t<BOOL(Any *p0, Any p1, Any *p2, Any *p3)>
	NETWORK_INVITE_GAMERS(0x9D80CD1D0E6327DE);
lazy_func_t<BOOL(Any *p0)>
	NETWORK_SET_CURRENTLY_SELECTED_GAMER_HANDLE_FROM_INVITE_MENU(
		0x7206F674F2A3B1BB);
lazy_func_t<BOOL(int netId)>
	NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(0xA670B3662FAFFBD0);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	SET_ENTITY_VISIBLE_IN_CUTSCENE(0xE0031D3C8F36AB82);
lazy_func_t<BOOL(Any p0)> _0x2E0BF682CC778D49(0x2E0BF682CC778D49);
lazy_func_t<void(int amount)>
	RESERVE_NETWORK_MISSION_VEHICLES(0x76B02E21ED27A469);
lazy_func_t<int(int p0)> _GET_CONTENT_CATEGORY(0xA7BAB11E7C9C6C5A);
lazy_func_t<const char *(Any p0)> _GET_CONTENT_ID(0x55AA95F481D694D2);
lazy_func_t<void(BOOL p0)> _0xCFEB8AF24FC1D0BB(0xCFEB8AF24FC1D0BB);
lazy_func_t<Any()> NETWORK_IS_TRANSITION_HOST(0x0B824797C9BF2159);
lazy_func_t<BOOL()> NETWORK_HAS_HEADSET(0xE870F9F1F7B4F1FA);
lazy_func_t<int(int *p0)> NETWORK_CLAN_GET_MEMBERSHIP_COUNT(0xAAB11F6C4ADBC2C1);
lazy_func_t<void(int amount)>
	RESERVE_NETWORK_MISSION_OBJECTS(0x4E5C93BD0C32FBF8);
lazy_func_t<BOOL()> NETWORK_IS_GAME_IN_PROGRESS(0x10FAB35428CCC9D7);
lazy_func_t<void(BOOL p0, Any p1)>
	NETWORK_SET_KEEP_FOCUSPOINT(0x7F8413B7FC2AA6B9);
lazy_func_t<Any()> _0x6512765E3BE78C50(0x6512765E3BE78C50);
lazy_func_t<BOOL()> _NETWORK_IS_PSN_AVAILABLE(0x8D11E61A4ABF49CC);
lazy_func_t<BOOL(Player player)> _NETWORK_PLAYER_SOMETHING(0x565E430DB3B05BEC);
lazy_func_t<void(BOOL p0)> _0x9D7AFCBF21C51712(0x9D7AFCBF21C51712);
lazy_func_t<void(BOOL p0)> _0xAAA553E7DD28A457(0xAAA553E7DD28A457);
lazy_func_t<void(Any p0, Any p1)> _0xFB680D403909DC70(0xFB680D403909DC70);
lazy_func_t<int(Ped ped)> PED_TO_NET(0x0EDEC3C276198689);
lazy_func_t<BOOL()> NETWORK_IS_ADDING_FRIEND(0x6EA101606F6E4D81);
lazy_func_t<void(Any p0)> _0x113E6E3E50E286B0(0x113E6E3E50E286B0);
lazy_func_t<Any(float p0, float p1, float p2, float p3, float p4, float p5)>
	_0x25B99872D588A101(0x25B99872D588A101);
lazy_func_t<BOOL(Hash tunableContext, Hash tunableName)>
	_NETWORK_DOES_TUNABLE_EXIST_HASH(0xE4E53E1419D81127);
lazy_func_t<void(int p0, BOOL p1)>
	NETWORK_SESSION_CHANGE_SLOTS(0xB4AB419E0D86ACAE);
lazy_func_t<BOOL(Any p0, BOOL p1, Any p2)>
	_NETWORK_IS_THIS_SCRIPT_MARKED(0xD1110739EEADB592);
lazy_func_t<void()> _0x741A3D8380319A81(0x741A3D8380319A81);
lazy_func_t<Any(Any p0)> _0x2A7776C709904AB0(0x2A7776C709904AB0);
lazy_func_t<Any(Any p0, Any p1)> _0x759299C5BB31D2A9(0x759299C5BB31D2A9);
lazy_func_t<void()> _0xFA2888E3833C8E96(0xFA2888E3833C8E96);
lazy_func_t<void(BOOL p0)> _NETWORK_CHAT_MUTE(0x57B192B4D4AD23D5);
lazy_func_t<int()> _GET_NUM_MEMBERSHIP_DESC(0x1F471B79ACC90BEF);
lazy_func_t<void(int netId, BOOL state)>
	_0x3FA36981311FA4FF(0x3FA36981311FA4FF);
lazy_func_t<void(BOOL p0, BOOL p1)>
	NETWORK_SET_IN_MP_CUTSCENE(0x9CA5DE655269FEC4);
lazy_func_t<Any()> _0x35F0B98A8387274D(0x35F0B98A8387274D);
lazy_func_t<BOOL(const char *message, int *networkHandle)>
	NETWORK_SEND_TEXT_MESSAGE(0x3A214F2EC889B100);
lazy_func_t<void()> NETWORK_BAIL_TRANSITION(0xEAA572036990CD1B);
lazy_func_t<void()> SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME(0x593850C16A36B692);
lazy_func_t<int(int timeA, int timeB)> GET_TIME_OFFSET(0x017008CCDAD48503);
lazy_func_t<void(int netScene, const char *animDict, const char *animName)>
	_NETWORK_FORCE_LOCAL_USE_OF_SYNCED_SCENE_CAMERA(0xCF8BD3B0BD6D42D7);
lazy_func_t<void(Player player, BOOL toggle)>
	_NETWORK_OVERRIDE_SEND_RESTRICTIONS(0x97DD4C5944CC2E6A);
lazy_func_t<
	BOOL(const char *tunableContext, const char *tunableName, float *value)>
	NETWORK_ACCESS_TUNABLE_FLOAT(0xE5608CA7BC163A5F);
lazy_func_t<void(Player player)>
	NETWORK_SESSION_KICK_PLAYER(0xFA8904DC5F304220);
lazy_func_t<BOOL(Hash tunableContext, Hash tunableName)>
	_NETWORK_ACCESS_TUNABLE_BOOL_HASH(0xEA16B69D93D71A45);
lazy_func_t<BOOL(Any p0)> _0x237D5336A9A54108(0x237D5336A9A54108);
lazy_func_t<Any()> _0x1D4DC17C38FEAFF0(0x1D4DC17C38FEAFF0);
lazy_func_t<Any()> _0x883D79C4071E18B3(0x883D79C4071E18B3);
lazy_func_t<void(BOOL p0)> _0xFD75DABC0957BF33(0xFD75DABC0957BF33);
lazy_func_t<Any(Any p0)> _0x36391F397731595D(0x36391F397731595D);
lazy_func_t<void(int netId, BOOL toggle)>
	SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(0xE05E81A888FA63C8);
lazy_func_t<void(Entity entity)> _0xCD71A4ECAB22709E(0xCD71A4ECAB22709E);
lazy_func_t<BOOL(Any *p0, Any *p1)> _0x152D90E4C1B4738A(0x152D90E4C1B4738A);
lazy_func_t<Any(Any p0)> _0xBF09786A7FCAB582(0xBF09786A7FCAB582);
lazy_func_t<Any()> _0x793FF272D5B365F4(0x793FF272D5B365F4);
lazy_func_t<BOOL(Player player)>
	NETWORK_AM_I_MUTED_BY_PLAYER(0x9D6981DFC91A8604);
lazy_func_t<void(int p0, Any p1, Any p2, Any p3)>
	NETWORK_SET_RICH_PRESENCE(0x1DCCACDCFC569362);
lazy_func_t<BOOL(Any p0)> _0x3A3D5568AF297CD5(0x3A3D5568AF297CD5);
lazy_func_t<Any()> NETWORK_JOIN_GROUP_ACTIVITY(0xA06509A691D12BE4);
lazy_func_t<void(BOOL p0, BOOL p1)> _0x0C978FDA19692C2C(0x0C978FDA19692C2C);
lazy_func_t<BOOL(Any p0)> NETWORK_REMOVE_PRESENCE_INVITE(0xF0210268DB0974B1);
lazy_func_t<BOOL()> NETWORK_GAMERTAG_FROM_HANDLE_SUCCEEDED(0xFD00798DBA7523DD);
lazy_func_t<BOOL()> NETWORK_CAN_SET_WAYPOINT(0xC927EC229934AF60);
lazy_func_t<void(BOOL p0)> _0xC505036A35AFD01B(0xC505036A35AFD01B);
lazy_func_t<BOOL(int *player)>
	NETWORK_CAN_COMMUNICATE_WITH_GAMER(0xA150A4F065806B1F);
lazy_func_t<BOOL(Player player)> NETWORK_PLAYER_HAS_HEADSET(0x3FB99A8B08D18FD6);
lazy_func_t<void(int p0)>
	NETWORK_SESSION_HOST_SINGLE_PLAYER(0xC74C33FCA52856D5);
lazy_func_t<void(Any p0, Any p1)>
	NETWORK_APPLY_TRANSITION_PARAMETER(0x521638ADA1BA0D18);
lazy_func_t<void(Any p0)>
	NETWORK_SET_TRANSITION_ACTIVITY_ID(0x30DE938B516F0AD2);
lazy_func_t<int(Player player)> NETWORK_GET_PLAYER_INDEX(0x24FB80D107371267);
lazy_func_t<const char *(int friendIndex)>
	_NETWORK_GET_FRIEND_NAME_FROM_INDEX(0x4164F227D052E293);
lazy_func_t<BOOL(Any *p0)>
	_NETWORK_CHECK_DATA_MANAGER_FOR_HANDLE(0x796A87B3B68D1F3D);
lazy_func_t<void(Player player, BOOL toggle)>
	NETWORK_OVERRIDE_CHAT_RESTRICTIONS(0x3039AE5AD2C9C0C4);
lazy_func_t<void(BOOL p0)> _0xF98DDE0A8ED09323(0xF98DDE0A8ED09323);
lazy_func_t<Any()> _0x8B0C2964BA471961(0x8B0C2964BA471961);
lazy_func_t<BOOL()> NETWORK_SESSION_IS_VISIBLE(0xBA416D68C631496A);
lazy_func_t<Any()> NETWORK_IS_ACTIVITY_SPECTATOR(0x12103B9E0C9F92FB);
lazy_func_t<void(int *vars, int numVars)>
	NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES(0x3364AA97340CA215);
lazy_func_t<BOOL(Any *p0, Any *p1)>
	NETWORK_GET_PRIMARY_CLAN_DATA_NEW(0xC080FF658B2E41DA);
lazy_func_t<void(BOOL p0)> _0xFC18DB55AE19E046(0xFC18DB55AE19E046);
lazy_func_t<void()> NETWORK_CLEAR_VOICE_CHANNEL(0xE036A705F989E049);
lazy_func_t<void(int unixEpoch, Any *timeStructure)>
	_GET_DATE_AND_TIME_FROM_UNIX_EPOCH(0xAC97AF97FA68E5D5);
lazy_func_t<void(int *networkHandle, int bufferSize)>
	NETWORK_GET_LOCAL_HANDLE(0xE86051786B66CD8E);
lazy_func_t<BOOL(Any *p0)> NETWORK_GAMER_HAS_HEADSET(0xF2FD55CB574BCC55);
lazy_func_t<BOOL(int *p0)> NETWORK_IS_GAMER_TALKING(0x71C33B22606CD88A);
lazy_func_t<BOOL(Any *p0)> NETWORK_AM_I_MUTED_BY_GAMER(0xDF02A2C93F1F26DA);
lazy_func_t<void(BOOL p0)> NETWORK_OVERRIDE_TRANSITION_CHAT(0xAF66059A131AA269);
lazy_func_t<void(Entity entity)>
	SET_ENTITY_LOCALLY_INVISIBLE(0xE135A9FF3F5D05D8);
lazy_func_t<Any(Any p0)> _0x32DD916F3F7C9672(0x32DD916F3F7C9672);
lazy_func_t<BOOL()> _FACEBOOK_IS_AVAILABLE(0x43865688AE10F0D7);
lazy_func_t<Any()> _0x593570C289A77688(0x593570C289A77688);
lazy_func_t<void(BOOL toggle)>
	NETWORK_SET_FRIENDLY_FIRE_OPTION(0xF808475FA571D823);
lazy_func_t<BOOL(int amount)> CAN_REGISTER_MISSION_PEDS(0xBCBF4FEF9FA5D781);
lazy_func_t<BOOL(Ped ped, Player player)>
	_NETWORK_COPY_PED_BLEND_DATA(0x99B72C7ABDE5C910);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_GET_TRANSITION_HOST(0x65042B9774C4435E);
lazy_func_t<float(Any p0)> NETWORK_GET_PLAYER_LOUDNESS(0x21A1684A25C2867F);
lazy_func_t<Any()> _0x67FC09BC554A75E5(0x67FC09BC554A75E5);
lazy_func_t<BOOL()> _FACEBOOK_IS_SENDING_DATA(0x62B9FEC9A11F10EF);
lazy_func_t<void(Any p0, const char *p1, BOOL p2)>
	_0xEBEFC2E77084F599(0xEBEFC2E77084F599);
lazy_func_t<void(Entity entity)> SET_ENTITY_LOCALLY_VISIBLE(0x241E289B5C059EDC);
lazy_func_t<BOOL()> _IS_ROCKSTAR_BANNED(0x8020A73847E0CA7D);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_IS_TRANSITION_HOST_FROM_HANDLE(0x6B5C83BA3EFE6A10);
lazy_func_t<void(BOOL p0)> _0x6A5D89D7769A40D8(0x6A5D89D7769A40D8);
lazy_func_t<BOOL(
	Player player,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	float p9,
	float p10,
	int flags)>
	_0x4BA92A18502BCA61(0x4BA92A18502BCA61);
lazy_func_t<BOOL(Any p0)> _0x1D610EB0FEA716D9(0x1D610EB0FEA716D9);
lazy_func_t<Any(Any p0)> _0x5E0165278F6339EE(0x5E0165278F6339EE);
lazy_func_t<void(Any p0, BOOL p1)> _0xBBDF066252829606(0xBBDF066252829606);
lazy_func_t<void(int Hours, int Minutes, int Seconds)>
	NETWORK_OVERRIDE_CLOCK_TIME(0xE679E3E06E363892);
lazy_func_t<BOOL(Any *p0, Any *p1, Any *p2)>
	_0x1DE0F5F50D723CAA(0x1DE0F5F50D723CAA);
lazy_func_t<void(int *p0, int p1)> NETWORK_ADD_FOLLOWERS(0x236406F60CF216D6);
lazy_func_t<void(int *networkHandle)>
	NETWORK_SESSION_GET_INVITER(0xE57397B4A3429DD0);
lazy_func_t<BOOL()> NETWORK_IS_IN_TRANSITION(0x68049AEFF83D8F0A);
lazy_func_t<void(Any *p0)> NETWORK_REMOVE_TRANSITION_INVITE(0x7524B431B2E6F7EE);
lazy_func_t<void(int netId, BOOL p1, BOOL p2)>
	SET_NETWORK_ID_VISIBLE_IN_CUTSCENE(0xA6928482543022B4);
lazy_func_t<BOOL(Any p0)> _0xA699957E60D80214(0xA699957E60D80214);
lazy_func_t<Any()> NETWORK_IS_IN_TUTORIAL_SESSION(0xADA24309FE08DACF);
lazy_func_t<BOOL(Any p0)> _0xA2F952104FC6DD4B(0xA2F952104FC6DD4B);
lazy_func_t<void(Any p0, BOOL p1)> _0x267C78C60E806B9A(0x267C78C60E806B9A);
lazy_func_t<Any()> _0x74698374C45701D2(0x74698374C45701D2);
lazy_func_t<BOOL()> _0x855BC38818F6F684(0x855BC38818F6F684);
lazy_func_t<void()> NETWORK_CLEAR_TRANSITION_CREATOR_HANDLE(0xFB3272229A82C759);
lazy_func_t<Any(Any p0)> _0xD39B3FFF8FFDD5BF(0xD39B3FFF8FFDD5BF);
lazy_func_t<BOOL(Player player)>
	NETWORK_IS_PLAYER_MUTED_BY_ME(0x8C71288AE68EDE39);
lazy_func_t<BOOL(Any *p0, Any p1)>
	NETWORK_GET_PRIMARY_CLAN_DATA_START(0xCE86D8191B762107);
lazy_func_t<int()> _0x89023FBBF9200E9F(0x89023FBBF9200E9F);
lazy_func_t<const char *(Any p0)> _GET_ROOT_CONTENT_ID(0xC0173D6BFF4E0348);
lazy_func_t<ScrHandle()> NETWORK_IS_MULTIPLAYER_DISABLED(0x9747292807126EDA);
lazy_func_t<BOOL(BOOL p0, BOOL p1)> NETWORK_SESSION_END(0xA02E59562D711006);
lazy_func_t<void(Any p0)> _0x702BC4D605522539(0x702BC4D605522539);
lazy_func_t<void(Any *globalPtr)>
	_NETWORK_VOICE_CONNECT_TO_PLAYER(0xABD5E88B8A2D3DB2);
lazy_func_t<BOOL(Any *p0, Any *p1, Any p2, Any p3)>
	FILLOUT_PM_PLAYER_LIST_WITH_NAMES(0x716B6DB9D1886106);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any *p3)>
	_0xA7862BC5ED1DFD7E(0xA7862BC5ED1DFD7E);
lazy_func_t<BOOL()> _0x67A5589628E0CFF6(0x67A5589628E0CFF6);
lazy_func_t<int()> NETWORK_GET_MAX_FRIENDS(0xAFEBB0D5D8F687D2);
lazy_func_t<int(BOOL p0)> _0x0CD9AB83489430EA(0x0CD9AB83489430EA);
lazy_func_t<Any()> _0x0C1F7D49C39D2289(0x0C1F7D49C39D2289);
lazy_func_t<Any()> _0xEA14EEF5B7CD2C30(0xEA14EEF5B7CD2C30);
lazy_func_t<BOOL()> _0x5A6AA44FF8E931E6(0x5A6AA44FF8E931E6);
lazy_func_t<int(int rangeStart, int rangeEnd)>
	_NETWORK_GET_RANDOM_INT_IN_RANGE(0xE30CF56F1EFA5F43);
lazy_func_t<Any()> _0xC32EA7A2F6CA7557(0xC32EA7A2F6CA7557);
lazy_func_t<Any(Any p0, Any p1)> _0x40F7E66472DF3E5C(0x40F7E66472DF3E5C);
lazy_func_t<BOOL(int p0, int maxPlayers, BOOL p2)>
	NETWORK_SESSION_HOST(0x6F3D4ED9BEE4E61D);
lazy_func_t<Any(Any p0)> _0x728C4CC7920CD102(0x728C4CC7920CD102);
lazy_func_t<BOOL(Hash doorHash)>
	_NETWORK_HAS_CONTROL_OF_PAVEMENT_STATS(0xC01E93FAC20C3346);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any *p3)>
	_0x5324A0E3E4CE3570(0x5324A0E3E4CE3570);
lazy_func_t<Any(int p0, Any *p1)> _0xBAF6BABF9E7CCC13(0xBAF6BABF9E7CCC13);
lazy_func_t<Any()> _0x2FC5650B0271CB57(0x2FC5650B0271CB57);
lazy_func_t<BOOL()> NETWORK_IS_HOST_OF_THIS_SCRIPT(0x83CD99A1E6061AB5);
lazy_func_t<BOOL(Entity p0)> _0xB07D3185E11657A5(0xB07D3185E11657A5);
lazy_func_t<Any()> NETWORK_GET_TALKER_PROXIMITY(0x84F0F13120B4E098);
lazy_func_t<BOOL(Any p0, Any *p1)> _0xA134777FF7F33331(0xA134777FF7F33331);
lazy_func_t<BOOL()> _0x1353F87E89946207(0x1353F87E89946207);
lazy_func_t<int()> NETWORK_GET_NUM_FOUND_GAMERS(0xA1B043EE79A916FB);
lazy_func_t<void(int *networkHandle)>
	NETWORK_SHOW_PROFILE_UI(0x859ED1CEA343FCA8);
lazy_func_t<int(BOOL p0)> _0xCB215C4B56A7FAE7(0xCB215C4B56A7FAE7);
lazy_func_t<BOOL()> NETWORK_CAN_SESSION_END(0x4EEBC3694E49C572);
lazy_func_t<BOOL()>
	NETWORK_GET_THIS_SCRIPT_IS_NETWORK_SCRIPT(0x2910669969E9535E);
lazy_func_t<void(int netScene)>
	NETWORK_START_SYNCHRONISED_SCENE(0x9A1B3FCDB36C8697);
lazy_func_t<int(BOOL p0)> GET_NUM_RESERVED_MISSION_OBJECTS(0xAA81B5F10BC43AC2);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any p3)>
	_0x6D4CB481FAC835E8(0x6D4CB481FAC835E8);
lazy_func_t<Any()> _0x606E4D3E3CCCF3EB(0x606E4D3E3CCCF3EB);
lazy_func_t<BOOL()> _0xBD545D44CCE70597(0xBD545D44CCE70597);
lazy_func_t<int(int p0)> _NETWORK_SESSION_GET_UNK(0x56CE820830EF040B);
lazy_func_t<Any()> NETWORK_IS_TRANSITION_TO_GAME(0x9D7696D8F4FA6CB7);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_CLAN_PLAYER_IS_ACTIVE(0xB124B57F571D8F18);
lazy_func_t<BOOL(int amount)> CAN_REGISTER_MISSION_VEHICLES(0x7277F1F2E085EE74);
lazy_func_t<BOOL(int *networkHandle)>
	_NETWORK_IS_FRIEND_ONLINE_2(0x87EB7A3FFCB314DB);
lazy_func_t<BOOL(Any p0)> _0x4DF7CFFF471A7FB1(0x4DF7CFFF471A7FB1);
lazy_func_t<void()> NETWORK_REQUEST_CLOUD_TUNABLES(0x42FB3B532D526E6C);
lazy_func_t<void(BOOL p0)> _0x5539C3EBF104A53A(0x5539C3EBF104A53A);
lazy_func_t<void(int *hours, int *minutes, int *seconds)>
	_NETWORK_GET_SERVER_TIME(0x6D03BFBD643B2A02);
lazy_func_t<void()> NETWORK_CLEAR_FOUND_GAMERS(0x6D14CCEE1B40381A);
lazy_func_t<Any()> _0x37A4494483B9F5C9(0x37A4494483B9F5C9);
lazy_func_t<int()> NETWORK_GET_NUM_PRESENCE_INVITES(0xCEFA968912D0F78D);
lazy_func_t<void(int p0)> TEXTURE_DOWNLOAD_RELEASE(0x487EB90B98E9FB19);
lazy_func_t<void()> _0x45A83257ED02D9BC(0x45A83257ED02D9BC);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any p3, Any p4, Any p5)>
	_0x9BF438815F5D96EA(0x9BF438815F5D96EA);
lazy_func_t<BOOL(Any p0)> _0x2D5DC831176D0114(0x2D5DC831176D0114);
lazy_func_t<BOOL(Any *p0)> NETWORK_HAS_INVITED_GAMER(0x4D86CD31E8976ECE);
lazy_func_t<BOOL(Pickup pickup)>
	NETWORK_HAS_CONTROL_OF_PICKUP(0x5BC9495F0B3B6FA6);
lazy_func_t<int(Vehicle vehicle)> VEH_TO_NET(0xB4C94523F023419C);
lazy_func_t<BOOL(int *p0)> NETWORK_IS_GAMER_MUTED_BY_ME(0xCE60DE011B6C7978);
lazy_func_t<void()> _0x966DD84FB6A46017(0x966DD84FB6A46017);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_INVISIBLE_LOCALLY(0x12B37D54667DB0B8);
lazy_func_t<Any()> _0x88B588B41FF7868E(0x88B588B41FF7868E);
lazy_func_t<BOOL(const char *p0, BOOL p1, const char *contentType)>
	_0x158EC424F35EC469(0x158EC424F35EC469);
lazy_func_t<BOOL()> NETWORK_IS_SESSION_STARTED(0x9DE624D2FC4B603F);
lazy_func_t<void()> _0xF083835B70BA9BFE(0xF083835B70BA9BFE);
lazy_func_t<Any()> _0x2BF66D2E7414F686(0x2BF66D2E7414F686);
lazy_func_t<BOOL()> NETWORK_PLAYER_IS_BADSPORT(0x19D8DA0E5A68045A);
lazy_func_t<Entity(int netId)>
	NETWORK_GET_ENTITY_FROM_NETWORK_ID(0xCE4E5D9B0A4FF560);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_IS_CHATTING_IN_PLATFORM_PARTY(0x8DE9945BCC9AEC52);
lazy_func_t<Player()> PARTICIPANT_ID(0x90986E8876CE0A83);
lazy_func_t<void(int netID, BOOL p1)>
	ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(0xD45B1FFCCD52FF19);
lazy_func_t<void()> _0x17E0198B3882C2CB(0x17E0198B3882C2CB);
lazy_func_t<BOOL()> _0x5DC577201723960A(0x5DC577201723960A);
lazy_func_t<BOOL(Player player)>
	NETWORK_HAS_PLAYER_STARTED_TRANSITION(0x9AC9CCBFA8C29795);
lazy_func_t<BOOL(Hash doorHash)>
	NETWORK_HAS_CONTROL_OF_DOOR(0xCB3C68ADB06195DF);
lazy_func_t<void(BOOL p0)> _0xF46A1E03E8755980(0xF46A1E03E8755980);
lazy_func_t<Any(Any p0)> _0x8BD6C6DEA20E82C6(0x8BD6C6DEA20E82C6);
lazy_func_t<Any()> _0x74FB3E29E6D10FA9(0x74FB3E29E6D10FA9);
lazy_func_t<BOOL()> NETWORK_SESSION_IS_CLOSED_CREW(0x74732C6CA90DA2B4);
lazy_func_t<BOOL(int p0)> NETWORK_IS_PARTICIPANT_ACTIVE(0x6FF8FF40B6357D45);
lazy_func_t<void(int netScene, Entity entity, int bone)>
	NETWORK_ATTACH_SYNCHRONISED_SCENE_TO_ENTITY(0x478DCBD2A98B705A);
lazy_func_t<
	Any(float p0, float p1, float p2, float p3, float p4, float p5, float p6)>
	_NETWORK_ADD_ENTITY_ANGLED_AREA(0x376C6375BA60293A);
lazy_func_t<BOOL(int p0, int maxPlayers)>
	NETWORK_SESSION_HOST_FRIENDS_ONLY(0xB9CFD27A5D578D83);
lazy_func_t<void()> _0xB13E88E655E5A3BC(0xB13E88E655E5A3BC);
lazy_func_t<Any()> NETWORK_IS_TRANSITION_BUSY(0x520F3282A53D26B7);
lazy_func_t<BOOL(Any *p0)> _0x07DD29D5E22763F1(0x07DD29D5E22763F1);
lazy_func_t<BOOL(Any p0, float p1, float p2, float p3, float p4)>
	IS_SPHERE_VISIBLE_TO_PLAYER(0xDC3A310219E5DA62);
lazy_func_t<BOOL(int *memberDesc, int p1)>
	NETWORK_CLAN_GET_MEMBERSHIP_DESC(0x48DE78AF2C8885B8);
lazy_func_t<BOOL(const char *heistName, int cashEarned, int xpEarned)>
	_FACEBOOK_SET_HEIST_COMPLETE(0x098AB65B9ED9A9EC);
lazy_func_t<BOOL(int *loadingState)>
	NETWORK_CAN_ACCESS_MULTIPLAYER(0xAF50DA1A3F8B1BA4);
lazy_func_t<void(BOOL p0)> _0x7AC752103856FB20(0x7AC752103856FB20);
lazy_func_t<void()> NETWORK_SESSION_VOICE_LEAVE(0x6793E42BE02B575D);
lazy_func_t<Any()> _0xB5D3453C98456528(0xB5D3453C98456528);
lazy_func_t<Any()> _0x0DBD5D7E3C5BEC3B(0x0DBD5D7E3C5BEC3B);
lazy_func_t<BOOL(int p0, int *p1, Vector3 *p2)>
	_0xC22912B1D85F26B1(0xC22912B1D85F26B1);
lazy_func_t<BOOL(int p0, int p1, int maxPlayers, BOOL p3)>
	NETWORK_SESSION_FRIEND_MATCHMAKING(0x2CFC76E0D087C994);
lazy_func_t<Hash(int *networkHandle)>
	_NETWORK_HASH_FROM_GAMER_HANDLE(0x58575AC3CF2CA8EC);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_GAMERTAG_FROM_HANDLE_START(0x9F0C0A981D73FA56);
lazy_func_t<BOOL(const char *friendName)>
	NETWORK_IS_FRIEND_IN_SAME_TITLE(0x2EA9A3BEDF3F17B8);
lazy_func_t<void(Object object, BOOL toggle)>
	_SET_NETWORK_OBJECT_NON_CONTACT(0x6274C4712850841E);
lazy_func_t<void(Player player, float x, float y, float z, BOOL p4, BOOL p5)>
	_NETWORK_RESPAWN_COORDS(0x9769F811D1785B03);
lazy_func_t<void(int *clanDesc, int bufferSize, int *networkHandle)>
	_0xF45352426FF3A4F0(0xF45352426FF3A4F0);
lazy_func_t<Any()> _0x02ADA21EA2F6918F(0x02ADA21EA2F6918F);
lazy_func_t<Any()> _0x299EF3C576773506(0x299EF3C576773506);
lazy_func_t<Any(Any p0)> _0x6C34F1208B8923FD(0x6C34F1208B8923FD);
lazy_func_t<BOOL(Any p0)> NETWORK_REMOVE_ENTITY_AREA(0x93CF869BAA0C4874);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any *p3)>
	_0xF9E1CCAE8BA4C281(0xF9E1CCAE8BA4C281);
lazy_func_t<BOOL(Any p0)> _0x7FCC39C46C3C03BD(0x7FCC39C46C3C03BD);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any p3)>
	NETWORK_SESSION_ACTIVITY_QUICKMATCH(0xBE3E347A87ACEB82);
lazy_func_t<BOOL(Any *p0)> _0x85A0EF54A500882C(0x85A0EF54A500882C);
lazy_func_t<BOOL(Any p0)> NETWORK_IS_PENDING_FRIEND(0x0BE73DA6984A6E33);
lazy_func_t<Any()> _0xB37E4E6A2388CA7B(0xB37E4E6A2388CA7B);
lazy_func_t<Any()> _0x5E24341A7F92A74B(0x5E24341A7F92A74B);
lazy_func_t<void(
	Ped ped,
	int netScene,
	const char *animDict,
	const char *animnName,
	float speed,
	float speedMultiplier,
	int duration,
	int flag,
	float playbackRate,
	Any p9)>
	NETWORK_ADD_PED_TO_SYNCHRONISED_SCENE(0x742A637471BCECD9);
lazy_func_t<BOOL(const char *tunableContext, const char *tunableName)>
	NETWORK_DOES_TUNABLE_EXIST(0x85E5F8B9B898B20A);
lazy_func_t<BOOL(int p0, int p1, int p2, int maxPlayers, BOOL p4)>
	NETWORK_SESSION_CREW_MATCHMAKING(0x94BC51E9449D917F);
lazy_func_t<void(Any p0)> _0x600F8CB31C7AAB6E(0x600F8CB31C7AAB6E);
lazy_func_t<void(const char *userId, int *networkHandle, int bufferSize)>
	NETWORK_HANDLE_FROM_USER_ID(0xDCD51DD8F87AEC5C);
lazy_func_t<BOOL(Player player)> NETWORK_IS_PLAYER_TALKING(0x031E11F3D447647E);
lazy_func_t<void()> _0xF03755696450470C(0xF03755696450470C);
lazy_func_t<BOOL(Player player)>
	NETWORK_AM_I_BLOCKED_BY_PLAYER(0x87F395D957D4353D);
lazy_func_t<int()> _GET_POSIX_TIME(0x9A73240B49945C76);
lazy_func_t<BOOL()> _HAS_TUNABLES_BEEN_DOWNLOADED(0x0467C11ED88B7D28);
lazy_func_t<Any *()> _0x76BF03FADBF154F5(0x76BF03FADBF154F5);
lazy_func_t<Any(Any *p0, Any p1)>
	NETWORK_GET_TRANSITION_MEMBERS(0x73B000F7FBC55829);
lazy_func_t<Any()> _0xD0A484CB2F829FBE(0xD0A484CB2F829FBE);
lazy_func_t<Any(Any p0, Any p1, Any p2)>
	_0x58CC181719256197(0x58CC181719256197);
lazy_func_t<const char *(int friendIndex)>
	NETWORK_GET_FRIEND_NAME(0xE11EBBB2A783FE8B);
lazy_func_t<Any(Any *p0)> _0xC64DED7EF0D2FE37(0xC64DED7EF0D2FE37);
lazy_func_t<BOOL()> _0x4237E822315D8BA9(0x4237E822315D8BA9);
lazy_func_t<BOOL(Any p0, BOOL p1)> _0x78321BEA235FD8CD(0x78321BEA235FD8CD);
lazy_func_t<BOOL(int timeA, int timeB)> IS_TIME_MORE_THAN(0xDE350F8651E4346C);
lazy_func_t<Any()> _0x6FB7BB3607D27FA2(0x6FB7BB3607D27FA2);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any *p3, Any *p4)>
	_0x9F6E2821885CAEE2(0x9F6E2821885CAEE2);
lazy_func_t<Any()> _0x5EA784D197556507(0x5EA784D197556507);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	NETWORK_HOST_TRANSITION(0xA60BB5CE242BB254);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_IS_GAMER_IN_MY_SESSION(0x0F10B05DDF8D16E9);
lazy_func_t<void(BOOL p0)> _0xCFEB46DCD7D8D5EB(0xCFEB46DCD7D8D5EB);
lazy_func_t<void(Player player, BOOL p1)>
	_0xBF22E0F32968E967(0xBF22E0F32968E967);
lazy_func_t<BOOL(Any p0)> USING_NETWORK_WEAPONTYPE(0xE26CCFF8094D8C74);
lazy_func_t<BOOL(Any *p0)> _0xB57A49545BA53CE7(0xB57A49545BA53CE7);
lazy_func_t<Any()> _0x10BD227A753B0D84(0x10BD227A753B0D84);
lazy_func_t<Any()> _0xF2EAC213D5EA0623(0xF2EAC213D5EA0623);
lazy_func_t<void(Entity p0, Any p1)> _0xE66C690248F11150(0xE66C690248F11150);
lazy_func_t<void(Player player, BOOL toggle)>
	NETWORK_OVERRIDE_RECEIVE_RESTRICTIONS(0xDDF73E2B1FEC5AB4);
lazy_func_t<BOOL(Any *p0, BOOL p1, Any *p2)>
	_0x274A1519DFC1094F(0x274A1519DFC1094F);
lazy_func_t<void(Any p0)> _0xB606E6CC59664972(0xB606E6CC59664972);
lazy_func_t<
	int(int *PlayerHandle, const char *FilePath, const char *Name, BOOL p3)>
	TEXTURE_DOWNLOAD_REQUEST(0x16160DA74A8E74A2);
lazy_func_t<Any()> _0x7808619F31FF22DB(0x7808619F31FF22DB);
lazy_func_t<Any()> _0x53AFD64C6758F2F9(0x53AFD64C6758F2F9);
lazy_func_t<Any(Any p0)>
	NETWORK_GET_PRESENCE_INVITE_SESSION_ID(0x26E1CD96B0903D60);
lazy_func_t<void(Any p0)> _0xCA575C391FEA25CC(0xCA575C391FEA25CC);
lazy_func_t<void()> _0xFB8F2A6F3DF08CBE(0xFB8F2A6F3DF08CBE);
lazy_func_t<BOOL(Any *p0, Any p1)>
	NETWORK_INVITE_GAMERS_TO_TRANSITION(0x4A595C32F77DFF76);
lazy_func_t<BOOL(Any *p0, BOOL p1, Any *p2)>
	_0xD05D1A6C74DA3498(0xD05D1A6C74DA3498);
lazy_func_t<Any()> _0x60EDD13EB3AC1FF3(0x60EDD13EB3AC1FF3);
lazy_func_t<Any(Any p0)> NETWORK_GET_PRESENCE_INVITE_ID(0xDFF09646E12EC386);
lazy_func_t<Any()> _0xFD8B834A8BA05048(0xFD8B834A8BA05048);
lazy_func_t<const char *(int *networkHandle)>
	NETWORK_MEMBER_ID_FROM_GAMER_HANDLE(0xC82630132081BB6F);
lazy_func_t<Any(Any p0)> _0xB309EBEA797E001F(0xB309EBEA797E001F);
lazy_func_t<BOOL(Ped ped, Player player)>
	_0x0EDE326D47CD0F3E(0x0EDE326D47CD0F3E);
lazy_func_t<BOOL()> NETWORK_CAN_ENTER_MULTIPLAYER(0x7E782A910C362C25);
lazy_func_t<BOOL()> _NETWORK_PLAYER_IS_UNK(0x172F75B6EE2233BA);
lazy_func_t<BOOL(int netID)> NETWORK_DOES_NETWORK_ID_EXIST(0x38CE16C96BD11344);
lazy_func_t<const char *(Player player, const char *userID)>
	NETWORK_PLAYER_GET_USERID(0x4927FC39CD0869A0);
lazy_func_t<BOOL(int amount)> CAN_REGISTER_MISSION_OBJECTS(0x800DD4721A8B008B);
lazy_func_t<void(int *networkHandle)>
	NETWORK_SET_GAMER_INVITED_TO_TRANSITION(0xCA2C8073411ECDB6);
lazy_func_t<void(int lobbySize, BOOL p1, int playerId)>
	NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(0x1CA59E306ECB80A5);
lazy_func_t<Any()> _0x3A17A27D75C74887(0x3A17A27D75C74887);
lazy_func_t<Any()> _0x4D02279C83BE69FE(0x4D02279C83BE69FE);
lazy_func_t<BOOL(Any p0)> _0xF53E48461B71EECB(0xF53E48461B71EECB);
lazy_func_t<Any()> _0x5A0A3D1A186A5508(0x5A0A3D1A186A5508);
lazy_func_t<void(BOOL toggle)> NETWORK_BLOCK_INVITES(0x34F9E9049454A7A0);
lazy_func_t<void(Player player, int *networkHandle, int bufferSize)>
	NETWORK_HANDLE_FROM_PLAYER(0x388EB2B86C73B6B3);
lazy_func_t<void(BOOL p0)> SET_LOCAL_PLAYER_VISIBLE_LOCALLY(0x7619364C82D3BF14);
lazy_func_t<void(BOOL p0)> _0x94538037EE44F5CF(0x94538037EE44F5CF);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2, Any *p3)>
	NETWORK_GET_BACKGROUND_LOADING_RECIPIENTS(0x97A770BEEF227E2B);
lazy_func_t<BOOL()> _NETWORK_ARE_ROS_AVAILABLE(0x85443FF4C328F53B);
lazy_func_t<Any(int p0, Any *p1)> _0xFB1F9381E80FA13F(0xFB1F9381E80FA13F);
lazy_func_t<BOOL(Any p0)> _0x919B3C98ED8292F9(0x919B3C98ED8292F9);
lazy_func_t<BOOL(Any p0, Any p1, Hash *weaponHash)>
	_NETWORK_GET_DESROYER_OF_ENTITY(0x4CACA84440FA26F6);
lazy_func_t<void(BOOL p0)> _0x7D395EA61622E116(0x7D395EA61622E116);
lazy_func_t<void(BOOL p0)> NETWORK_SESSION_MARK_VISIBLE(0x271CC6AB59EBF9A5);
lazy_func_t<BOOL(Any *p0)> NETWORK_IS_INACTIVE_PROFILE(0x7E58745504313A2E);
lazy_func_t<BOOL(int ped_amt, int vehicle_amt, int object_amt, int pickup_amt)>
	CAN_REGISTER_MISSION_ENTITIES(0x69778E7564BADE6D);
lazy_func_t<void(int playerType, int playerCount)>
	_NETWORK_SESSION_SET_MAX_PLAYERS(0x8B6A4DD0AF9CE215);
lazy_func_t<BOOL()> NETWORK_GAMERTAG_FROM_HANDLE_PENDING(0xB071E27958EF4CF0);
lazy_func_t<void(BOOL p0, Any p1)> _0x5C707A667DF8B9FA(0x5C707A667DF8B9FA);
lazy_func_t<BOOL()>
	_NETWORK_REQUEST_CLOUD_BACKGROUND_SCRIPTS(0x924426BFFD82E915);
lazy_func_t<BOOL(Any p0)> _0x5A34CD9C3C5BEC44(0x5A34CD9C3C5BEC44);
lazy_func_t<BOOL(int *networkHandle, int bufferSize)>
	NETWORK_IS_HANDLE_VALID(0x6F79B93B0A8E4133);
lazy_func_t<Any(Any p0, Any p1)> _0x1ACCFBA3D8DAB2EE(0x1ACCFBA3D8DAB2EE);
lazy_func_t<BOOL(Any p0, Any p1, BOOL p2)>
	_0x595F028698072DD9(0x595F028698072DD9);
lazy_func_t<int(Entity entity)>
	NETWORK_GET_NETWORK_ID_FROM_ENTITY(0xA11700682F3AD45C);
lazy_func_t<BOOL(Player player)>
	NETWORK_PLAYER_IS_ROCKSTAR_DEV(0x544ABDDA3B409B6D);
lazy_func_t<BOOL()> NETWORK_IS_CLOCK_TIME_OVERRIDDEN(0xD7C95D322FF57522);
lazy_func_t<BOOL(Any *p0, Any *p1)> SET_BALANCE_ADD_MACHINE(0x815E5E3073DA1D67);
lazy_func_t<BOOL(int *networkHandle, int event, int amountReceived)>
	BAD_SPORT_PLAYER_LEFT_DETECTED(0xEC5E3AF5289DCA81);
lazy_func_t<void(Entity entity)>
	NETWORK_REGISTER_ENTITY_AS_NETWORKED(0x06FAACD625D80CAA);
lazy_func_t<Any()> _0xFBC5E768C7A77A6A(0xFBC5E768C7A77A6A);
lazy_func_t<Any()> _0xD53ACDBEF24A46E8(0xD53ACDBEF24A46E8);
lazy_func_t<Any()> NETWORK_IS_TRANSITION_MATCHMAKING(0x292564C735375EDF);
lazy_func_t<int(int netId, Hash *weaponHash)>
	NETWORK_GET_DESTROYER_OF_NETWORK_ID(0x7A1ADEEF01740A24);
lazy_func_t<Hash(Player player)>
	_NETWORK_HASH_FROM_PLAYER_HANDLE(0xBC1D768F2F5D6C05);
lazy_func_t<BOOL(Any *p0)> _0x135F9B7B7ADD2185(0x135F9B7B7ADD2185);
lazy_func_t<void(float p0)> NETWORK_SET_TALKER_PROXIMITY(0xCBF12D65F95AD686);
lazy_func_t<BOOL()> NETWORK_HAS_PENDING_INVITE(0xAC8C7B9B88C4A668);
lazy_func_t<void()> _0x64F62AFB081E260D(0x64F62AFB081E260D);
lazy_func_t<BOOL()> _0x5D10B3795F3FC886(0x5D10B3795F3FC886);
lazy_func_t<int()> NETWORK_GET_TIMEOUT_TIME(0x5ED0356A0CE3A34F);
lazy_func_t<const char *(int p0)> TEXTURE_DOWNLOAD_GET_NAME(0x3448505B6E35262D);
lazy_func_t<void()> _0x9465E683B12D3F6B(0x9465E683B12D3F6B);
lazy_func_t<Any()> _0xBDB6F89C729CF388(0xBDB6F89C729CF388);
lazy_func_t<void(BOOL p0)> _0x973D76AA760A6CB6(0x973D76AA760A6CB6);
lazy_func_t<BOOL(Any p0)> _0x3DBF2DF0AEB7D289(0x3DBF2DF0AEB7D289);
lazy_func_t<BOOL(Any *p0)> NETWORK_AM_I_BLOCKED_BY_GAMER(0x15337C7C268A27B2);
lazy_func_t<void(Ped ped, float x, float y, float z, float p4)>
	_0xA7E30DE9272B6D49(0xA7E30DE9272B6D49);
lazy_func_t<BOOL(BOOL p0, int maxPlayers)>
	NETWORK_DO_TRANSITION_TO_GAME(0x3E9BB38102A589B0);
lazy_func_t<int()> _0xCF61D4B4702EE9EB(0xCF61D4B4702EE9EB);
lazy_func_t<int()> _0x638A3A81733086DB(0x638A3A81733086DB);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any *p3, Any *p4)>
	_0x678BB03C1A3BD51E(0x678BB03C1A3BD51E);
lazy_func_t<BOOL(Player player)>
	NETWORK_IS_PLAYER_BLOCKED_BY_ME(0x57AF1F8E27483721);
lazy_func_t<BOOL(int p0, const char *p1)>
	_0x2B51EDBEFC301339(0x2B51EDBEFC301339);
lazy_func_t<Any()> NETWORK_GET_PRIMARY_CLAN_DATA_SUCCESS(0x5B4F04F19376A0BA);
lazy_func_t<BOOL(Any p0, float p1, float p2, float p3)>
	NETWORK_FIND_MATCHED_GAMERS(0xF7B2CFDE5C9F700D);
lazy_func_t<Any()> _0xF9B83B77929D8863(0xF9B83B77929D8863);
lazy_func_t<void()> _0x86E0660E4F5C956D(0x86E0660E4F5C956D);
lazy_func_t<int()> NETWORK_GET_SCRIPT_STATUS(0x57D158647A6BFABF);
lazy_func_t<void(int player, BOOL p1)>
	NETWORK_DISABLE_INVINCIBLE_FLASHING(0x9DD368BF06983221);
lazy_func_t<void(BOOL p0, Any p1, BOOL p2)>
	_0x419594E137637120(0x419594E137637120);
lazy_func_t<void(int netId, int time)>
	SET_NETWORK_VEHICLE_RESPOT_TIMER(0xEC51713AB6EC36E8);
lazy_func_t<void()> _0x72D0706CD6CCDB58(0x72D0706CD6CCDB58);
lazy_func_t<void()> _0xA1E5E0204A6FCC70(0xA1E5E0204A6FCC70);
lazy_func_t<void(BOOL toggle)> NETWORK_SUPPRESS_INVITE(0xA0682D67EF1FBA3D);
lazy_func_t<BOOL()> NETWORK_IS_IN_SPECTATOR_MODE(0x048746E388762E11);
lazy_func_t<void(int netID)> _0x407091CF6037118E(0x407091CF6037118E);
lazy_func_t<BOOL()> NETWORK_IS_SIGNED_ONLINE(0x1077788E268557C2);
lazy_func_t<BOOL(Any p0)> NETWORK_X_AFFECTS_GAMERS(0xE532D6811B3A4D2A);
lazy_func_t<void()>
	NETWORK_IS_PLAYER_ANIMATION_DRAWING_SYNCHRONIZED(0xC6F8AB8A4189CF3A);
lazy_func_t<Any()> _0x62A0296C1BB1CEB3(0x62A0296C1BB1CEB3);
lazy_func_t<Any()> _0xD313DE83394AF134(0xD313DE83394AF134);
lazy_func_t<void(int p0)> _0x367EF5E2F439B4C6(0x367EF5E2F439B4C6);
lazy_func_t<Any()> NETWORK_ENABLE_MOTION_DRUGGED(0x0B0CC10720653F3B);
lazy_func_t<Any()> _0x769951E2455E2EB5(0x769951E2455E2EB5);
lazy_func_t<Any(Any *p0, Any p1)> _0x120364DE2845DAF8(0x120364DE2845DAF8);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_IS_PARTY_MEMBER(0x676ED266AADD31E0);
lazy_func_t<BOOL(int netId)>
	NETWORK_HAS_CONTROL_OF_NETWORK_ID(0x4D36070FE0215186);
lazy_func_t<void(Any p0)> NETWORK_SET_VOICE_CHANNEL(0xEF6212C2EFEF1A23);
lazy_func_t<void(BOOL toggle, Ped playerPed)>
	NETWORK_SET_IN_SPECTATOR_MODE(0x423DE3854BB50894);
lazy_func_t<Any()> _0x26F07DD83A5F7F98(0x26F07DD83A5F7F98);
lazy_func_t<BOOL(Any p0)> _0xEBFA8D50ADDC54C4(0xEBFA8D50ADDC54C4);
lazy_func_t<BOOL()> _CAN_PLAY_ONLINE(0x5F91D5D0B36AA310);
lazy_func_t<void(BOOL p0)> _0x261E97AD7BCF3D40(0x261E97AD7BCF3D40);
lazy_func_t<BOOL(Any *p0)>
	NETWORK_HAS_INVITED_GAMER_TO_TRANSITION(0x7284A47B3540E6CF);
lazy_func_t<Any()> NETWORK_ACTION_FOLLOW_INVITE(0xC88156EBB786F8D5);
lazy_func_t<BOOL(Player player, int p1, Hash scriptHash)>
	_NETWORK_IS_PLAYER_IN_SCRIPT(0x46FB3ED415C7641C);
lazy_func_t<int()> NETWORK_GET_FRIEND_COUNT(0x203F1CFD823B27A4);
lazy_func_t<BOOL(Any *p0, Any p1, Any *p2)>
	SET_BALANCE_ADD_MACHINES(0xB8322EEB38BE7C26);
lazy_func_t<const char *(int p0)>
	GET_PLAYER_ADVANCED_MODIFIER_PRIVILEGES(0xCD67AD041A394C9C);
lazy_func_t<BOOL()> NETWORK_IS_HOST(0x8DB296B814EDDA07);
lazy_func_t<Vehicle(int netHandle)> NET_TO_VEH(0x367B936610BA360C);
lazy_func_t<BOOL()> HAS_NETWORK_TIME_STARTED(0x46718ACEEDEAFC84);
lazy_func_t<const char *(int time)> GET_TIME_AS_STRING(0x9E23B1777A927DAD);
lazy_func_t<int(Hash contentHash)>
	_GET_TUNABLES_CONTENT_MODIFIER_ID(0x187382F8A3E0A6C3);
lazy_func_t<void(Any *p0)>
	NETWORK_SET_TRANSITION_CREATOR_HANDLE(0xEF26739BCD9907D5);
lazy_func_t<BOOL(Any p0, Any *p1)> _0x44B37CDCAE765AAE(0x44B37CDCAE765AAE);
lazy_func_t<BOOL(int doorID)>
	NETWORK_REQUEST_CONTROL_OF_DOOR(0x870DDFD5A4A796E4);
lazy_func_t<void(int team, BOOL toggle)>
	_0x6F697A66CE78674E(0x6F697A66CE78674E);
lazy_func_t<BOOL()> NETWORK_IS_IN_MP_CUTSCENE(0x6CC27C9FA2040220);
lazy_func_t<BOOL(Any *p0, Any p1, BOOL p2, int players, BOOL p4)>
	NETWORK_DO_TRANSITION_TO_FREEMODE(0x3AAD8B2FCA1E289F);
lazy_func_t<void()> NETWORK_CLOSE_TRANSITION_MATCHMAKING(0x43F4DBA69710E01E);
lazy_func_t<BOOL(Any *p0, Any *p1, Any p2, Any p3)>
	_NETWORK_SEND_PRESENCE_TRANSITION_INVITE(0xC116FF9B4D488291);
lazy_func_t<int(Object object)> OBJ_TO_NET(0x99BFDC94A603E541);
lazy_func_t<BOOL(int timeA, int timeB)> IS_TIME_EQUAL_TO(0xF5BC95857BD6D512);
lazy_func_t<int()> _NETWORK_GET_NUM_PARTICIPANTS_HOST(0xA6C90FBC38E395EE);
lazy_func_t<BOOL(int *networkHandle, const char *message)>
	NETWORK_ADD_FRIEND(0x8E02D73914064223);
lazy_func_t<BOOL(Any p0)> _0x13518FF1C6B28938(0x13518FF1C6B28938);
lazy_func_t<BOOL()> NETWORK_IS_SESSION_ACTIVE(0xD83C2B94E7508980);
lazy_func_t<int(Any *p0, Any p1, Any p2)>
	NETWORK_GET_NUM_SCRIPT_PARTICIPANTS(0x3658E8CD94FC121A);
lazy_func_t<BOOL(Entity entity)>
	NETWORK_HAS_CONTROL_OF_ENTITY(0x01BF60A500E28887);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_VISIBLE_LOCALLY(0xFAA10F1FAFB11AF2);
lazy_func_t<void(
	Entity entity,
	int netScene,
	const char *animDict,
	const char *animName,
	float speed,
	float speedMulitiplier,
	int flag)>
	NETWORK_ADD_ENTITY_TO_SYNCHRONISED_SCENE(0xF2404D68CBC855FA);
lazy_func_t<BOOL()> _NETWORK_PLAYER_IS_IN_CLAN(0x579CCED0265D4896);
lazy_func_t<BOOL(Player player)> IS_PLAYER_IN_CUTSCENE(0xE73092F4157CD126);
lazy_func_t<int(Any p0)> _GET_CONTENT_DESCRIPTION_HASH(0x7CF0448787B23758);
lazy_func_t<Any(Any *p0, Any p1, Any p2, Any p3, Any *p4, BOOL p5)>
	_0x308F96458B7087CC(0x308F96458B7087CC);
lazy_func_t<BOOL()> NETWORK_IS_SIGNED_IN(0x054354A99211EB96);
lazy_func_t<void(int maxSpectators)>
	NETWORK_SET_ACTIVITY_SPECTATOR_MAX(0x9D277B76D1D12222);
lazy_func_t<BOOL(int clanDesc)> NETWORK_CLAN_JOIN(0x9FAAA4F4FC71F87F);
lazy_func_t<Any()> NETWORK_GET_PRIMARY_CLAN_DATA_PENDING(0xB5074DB804E28CE7);
lazy_func_t<void(Any p0)> _0x6BFF5F84102DF80A(0x6BFF5F84102DF80A);
lazy_func_t<BOOL()> NETWORK_SESSION_IS_PRIVATE(0xCEF70AA5B3F89BA1);
lazy_func_t<void(Any p0, Any p1)>
	NETWORK_CHANGE_TRANSITION_SLOTS(0xEEEDA5E6D7080987);
lazy_func_t<Ped(int netHandle)> NET_TO_PED(0xBDCD95FC216A8B3E);
lazy_func_t<BOOL(Any *p0)> _0xCCA4318E1AB03F1F(0xCCA4318E1AB03F1F);
lazy_func_t<int(BOOL p0)> _0x12B6281B6C6706C0(0x12B6281B6C6706C0);
lazy_func_t<void()> _0x61A885D3F7CFEE9A(0x61A885D3F7CFEE9A);
lazy_func_t<void()> _0x140E6A44870A11CE(0x140E6A44870A11CE);
lazy_func_t<BOOL(Entity entity)>
	NETWORK_GET_ENTITY_IS_LOCAL(0x0991549DE4D64762);
lazy_func_t<BOOL(int *p0)>
	NETWORK_CLAN_REMOTE_MEMBERSHIPS_ARE_IN_CACHE(0xBB6E6FEE99D866B2);
lazy_func_t<void()> _0xE9B99B6853181409(0xE9B99B6853181409);
lazy_func_t<Any()> _0x63B406D7884BFA95(0x63B406D7884BFA95);
lazy_func_t<void()> NETWORK_BAIL(0x95914459A87EBA28);
lazy_func_t<BOOL(int *networkHandle, Any p1, Any p2)>
	FILLOUT_PM_PLAYER_LIST(0xCBBD7C4991B64809);
lazy_func_t<const char *(int *networkHandle)>
	NETWORK_GET_GAMERTAG_FROM_HANDLE(0x426141162EBE5CDB);
lazy_func_t<BOOL(int *networkHandle)>
	NETWORK_CLAN_DOWNLOAD_MEMBERSHIP(0xA989044E70010ABE);
lazy_func_t<Any(Any *p0, Any *p1, BOOL p2)>
	_0x0B203B4AFDE53A4F(0x0B203B4AFDE53A4F);
lazy_func_t<void(BOOL p0)> _0xA2E9C1AB8A92E8CD(0xA2E9C1AB8A92E8CD);
lazy_func_t<BOOL()> NETWORK_IS_IN_PARTY(0x966C2BC2A7FE3F30);
lazy_func_t<void(int *vars, int sizeofVars)>
	NETWORK_REGISTER_HOST_BROADCAST_VARIABLES(0x3E9B2F01C50DF595);
lazy_func_t<Any()> _0xA72835064DD63E4C(0xA72835064DD63E4C);
lazy_func_t<void(Any p0)> _0xF49ABC20D8552257(0xF49ABC20D8552257);
lazy_func_t<Any()> _0xC571D0E77D8BBC29(0xC571D0E77D8BBC29);
lazy_func_t<BOOL(Any p0)> NETWORK_IS_PLAYER_A_PARTICIPANT(0x3CA58F6CB7CBD784);
lazy_func_t<void(int netId, Player player, BOOL toggle)>
	_SET_NETWORK_ID_SYNC_TO_PLAYER(0xA8A024587329F36A);
lazy_func_t<void()> NETWORK_CLEAR_PROPERTY_ID(0xC2B82527CA77053E);
lazy_func_t<int(Any *p0, Any p1)> _0xD66C9E72B3CC4982(0xD66C9E72B3CC4982);
lazy_func_t<void(Entity entity, BOOL toggle)>
	NETWORK_SET_ENTITY_CAN_BLEND(0xD830567D88A1E873);
lazy_func_t<BOOL(Any p0)> _0x21D04D7BC538C146(0x21D04D7BC538C146);
lazy_func_t<Any()> _0xEBCAB9E5048434F4(0xEBCAB9E5048434F4);
lazy_func_t<void(Any p0)> _0xF1EEA2DDA9FFA69D(0xF1EEA2DDA9FFA69D);
lazy_func_t<BOOL(Any *p0, Any p1)> NETWORK_GET_FOUND_GAMER(0x9DCFF2AFB68B3476);
lazy_func_t<Any()> NETWORK_CLEAR_FOLLOW_INVITE(0x439BFDE3CD0610F6);
lazy_func_t<int()> PARTICIPANT_ID_TO_INT(0x57A3BDDAD8E5AA0A);
lazy_func_t<void(const char *p0, const char *p1)>
	_0x58C21165F6545892(0x58C21165F6545892);
}} // namespace NETWORK::
namespace UNK2 { namespace {
lazy_func_t<BOOL()> _IS_INTERIOR_RENDERING_DISABLED(0x95AB8B5C992C7B58);
lazy_func_t<void()> _0x5AD3932DAEB1E5D3(0x5AD3932DAEB1E5D3);
lazy_func_t<void(BOOL p0)> _0xE058175F8EAFE79A(0xE058175F8EAFE79A);
lazy_func_t<void()> _RESET_EDITOR_VALUES(0x3353D13F09307691);
lazy_func_t<void()> _ACTIVATE_ROCKSTAR_EDITOR(0x49DA8145672B2725);
lazy_func_t<void(const char *p0, BOOL p1)>
	_0x7E2BD3EF6C205F09(0x7E2BD3EF6C205F09);
}} // namespace UNK2::
namespace PED { namespace {
lazy_func_t<Ped(Ped ped, float heading, BOOL isNetwork, BOOL thisScriptCheck)>
	CLONE_PED(0xEF29A16337FACADB);
lazy_func_t<void(Ped ped, int amount)> SET_PED_MONEY(0xA9C8960E8684C1B5);
lazy_func_t<Any(Ped ped, Any p1)> _0x36B77BB84687C318(0x36B77BB84687C318);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_MAX_TIME_UNDERWATER(0x6BA428C528D9E522);
lazy_func_t<BOOL(Ped ped)> IS_CONVERSATION_PED_DEAD(0xE0A0AEC214B1FABA);
lazy_func_t<BOOL(Ped ped)> IS_PED_SHOOTING(0x34616828CD07F1A1);
lazy_func_t<void(Ped ped, BOOL toggle)> _0xAFC976FD0580C7B3(0xAFC976FD0580C7B3);
lazy_func_t<Vector3(Ped ped, BOOL p1)>
	GET_PED_DEFENSIVE_AREA_POSITION(0x3C06B8786DD94CD1);
lazy_func_t<void(Ped ped)> GIVE_PED_NM_MESSAGE(0xB158DFCCC56E5C5B);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_PLAY_GESTURE_ANIMS(0xBAF20C5432058024);
lazy_func_t<void(Any p0, BOOL p1)> _0xA660FAF550EB37E5(0xA660FAF550EB37E5);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_STEERS_AROUND_PEDS(0x46F2193B3AD1D891);
lazy_func_t<void(Ped ped, int amount)> ADD_ARMOUR_TO_PED(0x5BA652A0CD14DF2F);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_USE_AUTO_CONVERSATION_LOOKAT(0xEC4686EC06434678);
lazy_func_t<const char *(int handle)>
	GET_PEDHEADSHOT_TXD_STRING(0xDB4EACD4AD0A5D6B);
lazy_func_t<void(Ped ped)>
	CLEAR_PED_DRIVE_BY_CLIPSET_OVERRIDE(0x4AFE3690D7E0B5AC);
lazy_func_t<void(Ped ped)> SET_PED_RANDOM_PROPS(0xC44AA05345C992C6);
lazy_func_t<BOOL(
	float x,
	float y,
	float z,
	float radius,
	BOOL p4,
	BOOL p5,
	Ped *outPed,
	BOOL p7,
	BOOL p8,
	int pedType)>
	GET_CLOSEST_PED(0xC33AB876A77F8164);
lazy_func_t<int(Ped ped, int *sizeAndPeds, int ignore)>
	GET_PED_NEARBY_PEDS(0x23F8F5FC7E8C4A6B);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_ANY_SUB(0xFBFC01CCFB35D99E);
lazy_func_t<void(float value)>
	SET_AI_WEAPON_DAMAGE_MODIFIER(0x1B1E2A40A65B8521);
lazy_func_t<BOOL(Ped ped)> IS_PED_DIVING(0x5527B8246FEF9B11);
lazy_func_t<void(Ped ped, Hash hash)>
	SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(0xADB3F206518799E8);
lazy_func_t<void(int groupId, float p1, float p2, float p3)>
	SET_GROUP_FORMATION_SPACING(0x1D9D45004C28C916);
lazy_func_t<Vehicle(Ped ped)>
	SET_EXCLUSIVE_PHONE_RELATIONSHIPS(0xF92691AED837A5FC);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	_0xEEED8FAFEC331A70(0xEEED8FAFEC331A70);
lazy_func_t<BOOL(Ped ped, int flagId)> GET_PED_RESET_FLAG(0xAF9E59B1B1FBF2A0);
lazy_func_t<void(Ped ped)> _FREEZE_PED_CAMERA_ROTATION(0xFF287323B0E2C69A);
lazy_func_t<void(Ped ped, BOOL p1)>
	SET_PED_RANDOM_COMPONENT_VARIATION(0xC8A9481A01E63C28);
lazy_func_t<BOOL(int colorID)> _IS_PED_HAIR_COLOR_VALID(0xE0D36E5D9E99CC21);
lazy_func_t<BOOL(
	Ped ped,
	int time,
	int p2,
	int ragdollType,
	float x,
	float y,
	float z,
	float p7,
	float p8,
	float p9,
	float p10,
	float p11,
	float p12,
	float p13)>
	SET_PED_TO_RAGDOLL_WITH_FALL(0xD76632D99E4966C8);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_COWER_IN_COVER(0xCB7553CDCEF4A735);
lazy_func_t<Any(Any p0)> _0x511F1A683387C7E2(0x511F1A683387C7E2);
lazy_func_t<void(Ped ped, int p1, int p2, int p3)>
	_0xD69411AA0CEBF9E9(0xD69411AA0CEBF9E9);
lazy_func_t<void(int relationship, Hash group1, Hash group2)>
	CLEAR_RELATIONSHIP_BETWEEN_GROUPS(0x5E29243FB56FC6D4);
lazy_func_t<void(Ped driver, float ability)>
	SET_DRIVER_ABILITY(0xB195FFA8042FC5C3);
lazy_func_t<void(Ped ped, BOOL p1)> _0x2B694AFCF64E6994(0x2B694AFCF64E6994);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_BE_TARGETTED(0x63F58F7C80513AAD);
lazy_func_t<void(Ped ped, BOOL p1, BOOL p2)>
	_0x2208438012482A1A(0x2208438012482A1A);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_ENVEFF_SCALE(0xBF29516833893561);
lazy_func_t<void(int sceneID, BOOL toggle)>
	SET_SYNCHRONIZED_SCENE_LOOPED(0xD9A897A4C6C2974F);
lazy_func_t<BOOL(Any p0, Any p1, float p2, float p3, float p4, float p5)>
	_0x06087579E7AA85A9(0x06087579E7AA85A9);
lazy_func_t<BOOL(Ped ped, BOOL p1)> IS_PED_DEAD_OR_DYING(0x3317DEDB88C95038);
lazy_func_t<BOOL(Ped ped, Vehicle vehicle)>
	IS_PED_SITTING_IN_VEHICLE(0xA808AA1D79230FC2);
lazy_func_t<Ped(int groupID, int memberNumber)>
	GET_PED_AS_GROUP_MEMBER(0x51455483CF23ED97);
lazy_func_t<Any(Any p0)> _0xAAA6A3698A69E048(0xAAA6A3698A69E048);
lazy_func_t<BOOL(Ped ped)> IS_PED_JUMPING(0xCEDABC5900A0BF97);
lazy_func_t<int(int type)>
	_GET_FIRST_PARENT_ID_FOR_PED_TYPE(0x68D353AB88B97E0C);
lazy_func_t<void(Ped ped, Any p1, float p2, float p3, Any p4)>
	APPLY_PED_BLOOD_DAMAGE_BY_ZONE(0x816F6981C60BF53B);
lazy_func_t<void(Any p0, BOOL p1)> _0x9A77DFD295E29B09(0x9A77DFD295E29B09);
lazy_func_t<void(Any p0, BOOL p1)> _0xCEDA60A74219D064(0xCEDA60A74219D064);
lazy_func_t<void(Any p0, BOOL p1)> _0x2016C603D6B8987C(0x2016C603D6B8987C);
lazy_func_t<BOOL(Ped ped, Any p1)> HAS_PED_RECEIVED_EVENT(0x8507BCB710FA6DC0);
lazy_func_t<
	Ped(int pedType,
		Hash modelHash,
		float x,
		float y,
		float z,
		float heading,
		BOOL isNetwork,
		BOOL thisScriptCheck)>
	CREATE_PED(0xD49F9B0955C367DE);
lazy_func_t<BOOL(Ped ped)> IS_PED_SITTING_IN_ANY_VEHICLE(0x826AA586EDB9FEF8);
lazy_func_t<void(Ped ped, int groupId)>
	SET_PED_AS_GROUP_MEMBER(0x9F3480FE65DB31B5);
lazy_func_t<void(Ped ped, Hash context)>
	SET_PED_IN_VEHICLE_CONTEXT(0x530071295899A8C6);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	_0xEC6935EBE0847B90(0xEC6935EBE0847B90);
lazy_func_t<BOOL(Ped ped)> IS_PED_STOPPED(0x530944F6F4B8A214);
lazy_func_t<BOOL(
	Ped ped,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	BOOL p7,
	BOOL p8)>
	IS_PED_SHOOTING_IN_AREA(0x7E9DFE24AC1E58EF);
lazy_func_t<Any(Ped ped)> RESET_PED_VISIBLE_DAMAGE(0x3AC1F7B898F30C05);
lazy_func_t<BOOL(Ped ped)> _0xDCCA191DF9980FD7(0xDCCA191DF9980FD7);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_AS_COP(0xBB03C38DD3FB7FFD);
lazy_func_t<void(Ped ped, Any p1, float p2, float p3, Any *p4)>
	APPLY_PED_BLOOD_BY_ZONE(0x3311E47B91EDCBBC);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	_0x25361A96E0F7E419(0x25361A96E0F7E419);
lazy_func_t<BOOL(Any p0, float p1, float p2, float p3, float p4)>
	_0xFCF37A457CB96DC0(0xFCF37A457CB96DC0);
lazy_func_t<void(Any sceneID, BOOL p1)>
	_SET_SYNCHRONIZED_SCENE_OCCLUSION_PORTAL(0x394B9CD12435C981);
lazy_func_t<void(
	Ped ped,
	int stance,
	const char *animDictionary,
	const char *animationName,
	float p4,
	BOOL p5)>
	SET_PED_ALTERNATE_MOVEMENT_ANIM(0x90A43CC281FFAB46);
lazy_func_t<BOOL(Ped ped)> CAN_PED_RAGDOLL(0x128F79EDCECE4FD5);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_RAGDOLL_ON_COLLISION(0xF0A4F1BBF4FA7497);
lazy_func_t<BOOL(Ped ped, int *outBone)>
	GET_PED_LAST_DAMAGE_BONE(0xD75960F6BD9EA49C);
lazy_func_t<int(Ped ped)> GET_SEAT_PED_IS_TRYING_TO_ENTER(0x6F4C85ACD641BCD2);
lazy_func_t<BOOL(Ped ped, Any event)>
	IS_PED_RESPONDING_TO_EVENT(0x625B774D75C87068);
lazy_func_t<
	void(Ped ped, Ped father, Ped mother, float fathersSide, float mothersSide)>
	SET_PED_BLEND_FROM_PARENTS(0x137BBD05230DB22D);
lazy_func_t<void()> STOP_ANY_PED_MODEL_BEING_SUPPRESSED(0xB47BD05FA66B40CF);
lazy_func_t<BOOL(Ped ped, Any *p1, Any *p2)>
	_0xF60165E1D2C5370B(0xF60165E1D2C5370B);
lazy_func_t<
	Ped(Vehicle vehicle,
		int pedType,
		Hash modelHash,
		int seat,
		BOOL isNetwork,
		BOOL thisScriptCheck)>
	CREATE_PED_INSIDE_VEHICLE(0x7DD959874C1FD534);
lazy_func_t<int(Ped ped)> GET_PED_ARMOUR(0x9483AF821605B1D8);
lazy_func_t<int(Ped ped, int propId)>
	GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(0x5FAF9754E789FB47);
lazy_func_t<BOOL(
	Ped ped, int time1, int time2, int ragdollType, BOOL p4, BOOL p5, BOOL p6)>
	SET_PED_TO_RAGDOLL(0xAE99FB955581844A);
lazy_func_t<BOOL(Ped ped, Entity entity)>
	IS_PED_HEADTRACKING_ENTITY(0x813A0A7C9D2E831F);
lazy_func_t<void(int groupHandle, float separationRange)>
	SET_GROUP_SEPARATION_RANGE(0x4102C7858CFEE4E4);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_ENABLE_SCUBA(0xF99F62004024D506);
lazy_func_t<BOOL(Any p0)> _0xED6D8E27A43B8CDE(0xED6D8E27A43B8CDE);
lazy_func_t<BOOL(Any p0)> _0xF41B5D290C99A3D6(0xF41B5D290C99A3D6);
lazy_func_t<void(Ped ped, float p1, float p2, float p3, float p4, float p5)>
	SET_PED_BOUNDS_ORIENTATION(0x4F5F651ACCC9C4CF);
lazy_func_t<BOOL(Ped ped, BOOL p1)> _0xBA63D9FE45412247(0xBA63D9FE45412247);
lazy_func_t<Any(Any p0)> _0x9D728C1E12BF5518(0x9D728C1E12BF5518);
lazy_func_t<
	int(float x, float y, float z, float roll, float pitch, float yaw, int p6)>
	CREATE_SYNCHRONIZED_SCENE(0x8C18E0F9080ADD73);
lazy_func_t<BOOL(Ped ped)> IS_PED_HANGING_ON_TO_VEHICLE(0x1C86D8AEF8254B78);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_ANY_TRAIN(0x6F972C1AB75A1ED0);
lazy_func_t<BOOL(Ped ped)> IS_PED_RUNNING_MOBILE_PHONE_TASK(0x2AFE52F782F25775);
lazy_func_t<void(Any p0, Any p1)> _0x78C4E9961DB3EB5B(0x78C4E9961DB3EB5B);
lazy_func_t<BOOL(Ped ped1, Ped ped2)> _CAN_PED_SEE_PED(0x6CD5A433374D4CFB);
lazy_func_t<int(Ped ped, int boneId)> GET_PED_BONE_INDEX(0x3F428D08BE5AAE31);
lazy_func_t<int(Ped ped)> GET_PED_PARACHUTE_LANDING_TYPE(0x8B9F1FC6AE8166C0);
lazy_func_t<BOOL(Ped ped, Any *headBlendData)>
	_GET_PED_HEAD_BLEND_DATA(0x2746BD9D88C5C5D0);
lazy_func_t<
	void(Ped ped, int componentId, int drawableId, int TextureId, BOOL attach)>
	SET_PED_PROP_INDEX(0x93376B65A266EB5F);
lazy_func_t<void(Ped ped, BOOL p1)> _0x6647C5F6F5792496(0x6647C5F6F5792496);
lazy_func_t<BOOL(Ped ped)> IS_PED_BEING_STEALTH_KILLED(0x863B23EFDE9C5DF2);
lazy_func_t<BOOL(float x1, float y1, float z1, float x2, float y2, float z2)>
	IS_COP_PED_IN_AREA_3D(0x16EC4839969F9F5E);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_DIES_IN_SINKING_VEHICLE(0xD718A22995E2B4BC);
lazy_func_t<void(Ped ped, Any p1)>
	SET_PED_RESERVE_PARACHUTE_TINT_INDEX(0xE88DA0751C22A2AD);
lazy_func_t<void(Ped ped)>
	RESET_PED_WEAPON_MOVEMENT_CLIPSET(0x97B0DB5B4AA74E77);
lazy_func_t<int(Ped ped, int componentId)>
	GET_PED_PROP_INDEX(0x898CC20EA75BACD8);
lazy_func_t<BOOL(Ped ped)> IS_PED_DUCKING(0xD125AE748725C6BC);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_VISUAL_FIELD_MAX_ANGLE(0x70793BDCA1E854D4);
lazy_func_t<int(Hash group1, Hash group2)>
	GET_RELATIONSHIP_BETWEEN_GROUPS(0x9E6B70061662AE5C);
lazy_func_t<void(int groupID, Any *unknown, int *sizeInMembers)>
	GET_GROUP_SIZE(0x8DE69FE35CA09A45);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_GRAVITY(0x9FF447B6B6AD960A);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_ENABLE_HANDCUFFS(0xDF1AF8B5D56542FA);
lazy_func_t<void(Any p0, BOOL p1)> _0x576594E8D64375E2(0x576594E8D64375E2);
lazy_func_t<BOOL(Ped ped)> _0xB8B52E498014F5B0(0xB8B52E498014F5B0);
lazy_func_t<void(Any p0)> _0xE6CA85E7259CE16B(0xE6CA85E7259CE16B);
lazy_func_t<void(Ped ped, BOOL p1)> _0xF9ACF4A08098EA25(0xF9ACF4A08098EA25);
lazy_func_t<void(Ped ped, float value)> SET_PED_CAPSULE(0x364DF566EC833DE2);
lazy_func_t<Any()> _0xA586FBEB32A53DBB(0xA586FBEB32A53DBB);
lazy_func_t<void(Ped ped, Vehicle vehicle, int seatIndex)>
	SET_PED_INTO_VEHICLE(0xF75B0D629E1C063D);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_ANY_BOAT(0x2E0E1C2B4F6CB339);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_VISUAL_FIELD_MIN_ANGLE(0x2DB492222FB21E26);
lazy_func_t<int(Ped ped, int componentId, int drawableId)>
	GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(0x8F7156A3142A6BAD);
lazy_func_t<BOOL(Ped ped, int componentId, int drawableId, int textureId)>
	IS_PED_COMPONENT_VARIATION_VALID(0xE825F6B6CEA7671D);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_TORSO_IK(0xF2B7106D37947CE0);
lazy_func_t<BOOL(Any p0)> _0xF0DAEF2F545BEE25(0xF0DAEF2F545BEE25);
lazy_func_t<void(Ped ped)> _0xD33DAA36272177C4(0xD33DAA36272177C4);
lazy_func_t<Ped(float posX, float posY, float posZ)>
	CREATE_RANDOM_PED(0xB4AC7D0CF06BFE8F);
lazy_func_t<int(Ped ped, int componentId)>
	GET_PED_PALETTE_VARIATION(0xE3DD5F2A84B42281);
lazy_func_t<void(Ped ped, BOOL p1)>
	_SET_PED_CAN_PLAY_INJURED_ANIMS(0x33A60D8BDD6E508C);
lazy_func_t<void(int sceneID, float phase)>
	SET_SYNCHRONIZED_SCENE_PHASE(0x734292F4F0ABF6D0);
lazy_func_t<void(Ped ped, BOOL p1)> _0x52D59AB61DDC05DD(0x52D59AB61DDC05DD);
lazy_func_t<void(Ped ped)> REMOVE_PED_FROM_GROUP(0xED74007FFB146BC2);
lazy_func_t<int(Ped ped)> GET_PED_ALERTNESS(0xF6AA118530443FD2);
lazy_func_t<void(Any p0)> _0x5AAB586FFEC0FD96(0x5AAB586FFEC0FD96);
lazy_func_t<void(Ped ped, int flags)>
	_SET_PED_RAGDOLL_BLOCKING_FLAGS(0x26695EC767728D84);
lazy_func_t<void(Ped ped, int flags)>
	_RESET_PED_RAGDOLL_BLOCKING_FLAGS(0xD86D101FCFD00A4B);
lazy_func_t<void(Ped ped)> CLEAR_PED_WETNESS(0x9C720776DAA43E7E);
lazy_func_t<void(Ped ped, const char *p1)>
	SET_PED_COWER_HASH(0xA549131166868ED3);
lazy_func_t<BOOL(int colorID)> _IS_PED_BLUSH_COLOR_VALID(0x604E810189EE3A59);
lazy_func_t<void(Ped ped, int propIndex)>
	SET_PED_HELMET_PROP_INDEX(0x26D83693ED99291C);
lazy_func_t<void(Ped ped, int attributeIndex, BOOL enabled)>
	SET_PED_COMBAT_ATTRIBUTES(0x9F7794730795E019);
lazy_func_t<BOOL(Ped ped)> IS_PED_USING_ACTION_MODE(0x00E73468D085F745);
lazy_func_t<void(Any p0)> _0x1280804F7CFD2D6C(0x1280804F7CFD2D6C);
lazy_func_t<BOOL(Ped ped, int flag)> _0x46B05BCAE43856B0(0x46B05BCAE43856B0);
lazy_func_t<BOOL(Ped ped)> IS_PED_ON_MOUNT(0x460BC76A0E10655E);
lazy_func_t<Any(Ped ped, BOOL toggle)>
	SET_PED_ENABLE_WEAPON_BLOCKING(0x97A790315D3831FD);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_STEERS_AROUND_VEHICLES(0xEB6FB9D48DDE23EC);
lazy_func_t<BOOL(Ped ped, float x, float y, float z, float range)>
	_0x68772DB2B2526F9F(0x68772DB2B2526F9F);
lazy_func_t<void(float x, float y, float z)>
	SET_SCRIPTED_CONVERSION_COORD_THIS_FRAME(0x5086C7843552CF85);
lazy_func_t<void(Ped ped, float range)>
	SET_PED_VISUAL_FIELD_PERIPHERAL_RANGE(0x9C74B0BC831B753A);
lazy_func_t<void(Ped ped, int p1)> _0x1A330D297AAC6BC1(0x1A330D297AAC6BC1);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_STEERS_AROUND_OBJECTS(0x1509C089ADC208BF);
lazy_func_t<void(Any p0, const char *p1)>
	_0x9DBA107B4937F809(0x9DBA107B4937F809);
lazy_func_t<void(Ped ped, const char *animGroupGesture)>
	SET_PED_GESTURE_GROUP(0xDDF803377F94AAA8);
lazy_func_t<BOOL(int colorID)> _IS_PED_LIPSTICK_COLOR_VALID(0x0525A2C2562F3CD4);
lazy_func_t<int(int type)> _GET_NUM_PARENT_PEDS_OF_TYPE(0x5EF37013A6539C9D);
lazy_func_t<int(float x, float y, float z, float radius, Hash object)>
	_CREATE_SYNCHRONIZED_SCENE_2(0x62EC273D00187DCA);
lazy_func_t<BOOL(int sceneID)> IS_SYNCHRONIZED_SCENE_LOOPED(0x62522002E0C391BA);
lazy_func_t<void()> _0x5A7F62FDA59759BD(0x5A7F62FDA59759BD);
lazy_func_t<void(BOOL p0)> _0x9911F4A24485F653(0x9911F4A24485F653);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_DUCKING(0x030983CA930B692D);
lazy_func_t<int(Ped ped, int propId, int drawableId)>
	GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(0xA6E7F1CEB523E171);
lazy_func_t<BOOL(Any p0)> _0xFEC9A3B1820F3331(0xFEC9A3B1820F3331);
lazy_func_t<void(Ped ped, int team, BOOL toggle)>
	SET_PED_CAN_BE_TARGETTED_BY_TEAM(0xBF1CA77833E58F2C);
lazy_func_t<void(Ped ped, float angle)>
	SET_PED_VISUAL_FIELD_CENTER_ANGLE(0x3B6405E8AB34A907);
lazy_func_t<void(Ped ped, float posX, float posY, float posZ)>
	SET_PED_COORDS_KEEP_VEHICLE(0x9AFEFF481A85AB2E);
lazy_func_t<Vector3(
	const char *animDict,
	const char *animName,
	float x,
	float y,
	float z,
	float xRot,
	float yRot,
	float zRot,
	float p8,
	int p9)>
	GET_ANIM_INITIAL_OFFSET_POSITION(0xBE22B26DD764C040);
lazy_func_t<void(Any p0)> _0x36C6984C3ED0C911(0x36C6984C3ED0C911);
lazy_func_t<void(int groupId, int formationType)>
	SET_GROUP_FORMATION(0xCE2F5FC3AF7E8C1E);
lazy_func_t<void(Ped ped, float sweat)> SET_PED_SWEAT(0x27B0405F59637D1F);
lazy_func_t<void(Ped pedHandle, int groupHandle, BOOL toggle)>
	SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(0x2E2F4240B3F24647);
lazy_func_t<void(Ped driver, float p1)> _0xDED5AF5A0EA4B297(0xDED5AF5A0EA4B297);
lazy_func_t<void(Ped ped, float angle)>
	SET_PED_VISUAL_FIELD_MAX_ELEVATION_ANGLE(0x78D0B67629D75856);
lazy_func_t<void(Ped ped, int combatType, float p2)>
	SET_COMBAT_FLOAT(0xFF41B4B141ED981C);
lazy_func_t<void(Ped ped, float p1)>
	RESET_PED_MOVEMENT_CLIPSET(0xAA74EC0CB0AAEA2C);
lazy_func_t<
	void(Ped ped, int overlayID, int colorType, int colorID, int secondColorID)>
	_SET_PED_HEAD_OVERLAY_COLOR(0x497BF74A7B9CB952);
lazy_func_t<void(Ped ped)> RESET_PED_RAGDOLL_TIMER(0x9FA4664CF62E47E8);
lazy_func_t<void(Ped ped, Any p1, BOOL p2)>
	HIDE_PED_BLOOD_DAMAGE_BY_ZONE(0x62AB793144DE75DC);
lazy_func_t<BOOL(Ped ped, int flagId, BOOL p2)>
	GET_PED_CONFIG_FLAG(0x7EE53118C892B513);
lazy_func_t<float(int sceneID)> GET_SYNCHRONIZED_SCENE_RATE(0xD80932D577274D40);
lazy_func_t<void(Any p0)> _0x5D517B27CF6ECD04(0x5D517B27CF6ECD04);
lazy_func_t<int(Ped ped)> GET_PED_ACCURACY(0x37F4AD56ECBC0CD6);
lazy_func_t<void(Ped ped)> CLEAR_PED_BLOOD_DAMAGE(0x8FE22675A5A45817);
lazy_func_t<void(Ped ped, BOOL p1)> _0x425AECF167663F48(0x425AECF167663F48);
lazy_func_t<BOOL(Ped ped)> IS_PED_WEARING_HELMET(0xF33BDFE19B309B19);
lazy_func_t<int(Ped ped1, Ped ped2)>
	GET_RELATIONSHIP_BETWEEN_PEDS(0xEBA5AD3A0EAF7121);
lazy_func_t<Hash(Ped ped)>
	GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(0x42FDD0F017B1E38E);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_EVASIVE_DIVE(0x6B7A646C242A7059);
lazy_func_t<BOOL(Ped ped, BOOL exceptUseWeapon)>
	IS_PED_IN_COVER(0x60DFD0691A170B88);
lazy_func_t<void(BOOL toggle)>
	SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(0x8A4986851C4EF6E7);
lazy_func_t<void(Ped ped)> _0xA21C118553BBDF02(0xA21C118553BBDF02);
lazy_func_t<BOOL(Ped p0)> _0x66680A92700F43DF(0x66680A92700F43DF);
lazy_func_t<void(Ped ped)> REMOVE_PED_PREFERRED_COVER_SET(0xFDDB234CF74073D9);
lazy_func_t<void(Ped ped, int textureIndex)>
	SET_PED_HELMET_TEXTURE_INDEX(0xF1550C4BD22582E2);
lazy_func_t<BOOL(BOOL unk)> CAN_CREATE_RANDOM_PED(0x3E8349C08E4B82E4);
lazy_func_t<void(float x1, float y1, float z1, float x2, float y2, float z2)>
	SET_PED_NON_CREATION_AREA(0xEE01041D559983EA);
lazy_func_t<void(Ped ped, int index)> _SET_PED_EYE_COLOR(0x50B56988B170AFDF);
lazy_func_t<void(Ped ped, int r, int g, int b, int p4)>
	_0xCC9682B8951C5229(0xCC9682B8951C5229);
lazy_func_t<BOOL(Ped ped, const char *scenario)>
	IS_PED_USING_SCENARIO(0x1BF094736DD62C2E);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_SUFFERS_CRITICAL_HITS(0xEBD76F2359F190AC);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_MAX_TIME_IN_WATER(0x43C851690662113D);
lazy_func_t<void(Ped ped, const char *clipSet)>
	SET_PED_STRAFE_CLIPSET(0x29A28F3F8CF6D854);
lazy_func_t<void(Ped ped, BOOL p1)> _0xE43A13C9E4CCCBCF(0xE43A13C9E4CCCBCF);
lazy_func_t<BOOL(Any p0)> _0xF2385935BFFD4D92(0xF2385935BFFD4D92);
lazy_func_t<Any(Any p0)> _0x953563CE563143AF(0x953563CE563143AF);
lazy_func_t<void(Any p0, float p1)> _0x288DF530C92DAD6F(0x288DF530C92DAD6F);
lazy_func_t<BOOL(Ped ped, Ped target)>
	CAN_PED_IN_COMBAT_SEE_TARGET(0xEAD42DE3610D0721);
lazy_func_t<void(Ped ped, float radius, int maxFriends)>
	SET_PED_TO_INFORM_RESPECTED_FRIENDS(0x112942C6E708F70B);
lazy_func_t<BOOL(Ped ped)> IS_PED_USING_ANY_SCENARIO(0x57AB4A3080F85143);
lazy_func_t<void(Any p0)> _0xF1C03A5352243A30(0xF1C03A5352243A30);
lazy_func_t<void(Ped ped, int index)>
	SET_PED_GROUP_MEMBER_PASSENGER_INDEX(0x0BDDB8D9EC6BCF3C);
lazy_func_t<void(Any p0, Any p1)> _0xC1F6EBF9A3D55538(0xC1F6EBF9A3D55538);
lazy_func_t<BOOL(const char *asset)>
	HAS_ACTION_MODE_ASSET_LOADED(0xE4B5F4BF2CB24E65);
lazy_func_t<BOOL(Ped ped)> IS_PED_A_PLAYER(0x12534C348C6CB68B);
lazy_func_t<void(Ped ped, Ped lookAt)>
	SET_PED_PRIMARY_LOOKAT(0xCD17B554996A8D9E);
lazy_func_t<void(
	int sceneID,
	float x,
	float y,
	float z,
	float roll,
	float pitch,
	float yaw,
	BOOL p7)>
	SET_SYNCHRONIZED_SCENE_ORIGIN(0x6ACF6B7225801CD7);
lazy_func_t<void(Ped ped)> _0xED3C76ADFA6D07C4(0xED3C76ADFA6D07C4);
lazy_func_t<void(Ped ped, Ped targetPed)>
	CLONE_PED_TO_TARGET(0xE952D6431689AD9A);
lazy_func_t<void(float p0, Any p1)> _0xFF4803BC019852D9(0xFF4803BC019852D9);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_STAY_IN_VEHICLE_WHEN_JACKED(0xEDF4079F9D54C9A1);
lazy_func_t<Hash(Ped ped)> GET_PED_CAUSE_OF_DEATH(0x16FFE42AB2D2DC59);
lazy_func_t<int()> _GET_NUM_HAIR_COLORS(0xE5C0CF872C2AD150);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_MODEL_IS_SUPPRESSED(0xE163A4BCE4DE6F11);
lazy_func_t<Any()> _0xF445DE8DA80A1792(0xF445DE8DA80A1792);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_BE_DRAGGED_OUT(0xC1670E958EEE24E5);
lazy_func_t<void(Ped ped)> FORCE_PED_TO_OPEN_PARACHUTE(0x16E42E800B472221);
lazy_func_t<Entity(Ped ped, BOOL p1, BOOL p2)>
	_0x8C4F3BF23B6237DB(0x8C4F3BF23B6237DB);
lazy_func_t<Vehicle(Ped ped)> GET_VEHICLE_PED_IS_USING(0x6094AD011A2EA87D);
lazy_func_t<int(Ped ped, int componentId)>
	GET_PED_PROP_TEXTURE_INDEX(0xE131A28626F81AB2);
lazy_func_t<void(Ped ped, BOOL toggle, BOOL p2)>
	SET_PED_CAN_PLAY_VISEME_ANIMS(0xF833DDBA3B104D43);
lazy_func_t<void()> _0xFEE4A5459472A9F8(0xFEE4A5459472A9F8);
lazy_func_t<void(Any p0, BOOL p1)> _0x2F3C3D9F50681DE4(0x2F3C3D9F50681DE4);
lazy_func_t<void(Ped ped)>
	SET_PED_WETNESS_ENABLED_THIS_FRAME(0xB5485E4907B53019);
lazy_func_t<void(Ped ped, BOOL p1)>
	GET_PED_FLOOD_INVINCIBILITY(0x2BC338A7B21F4608);
lazy_func_t<BOOL(int handle)> IS_PEDHEADSHOT_VALID(0xA0A9668F158129A2);
lazy_func_t<int(Ped ped)> GET_PED_PARACHUTE_STATE(0x79CFD9827CC979B6);
lazy_func_t<void(Any p0)> _0x733C87D4CE22BEA2(0x733C87D4CE22BEA2);
lazy_func_t<Vector3(
	const char *animDict,
	const char *animName,
	float x,
	float y,
	float z,
	float xRot,
	float yRot,
	float zRot,
	float p8,
	int p9)>
	GET_ANIM_INITIAL_OFFSET_ROTATION(0x4B805E6046EE9E47);
lazy_func_t<void(Ped ped, int index, float scale)>
	_SET_PED_FACE_FEATURE(0x71A5C1DBA060049E);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_MELEE_COMBAT(0x4E209B2C1EAD5159);
lazy_func_t<BOOL(Ped ped)> IS_PED_GETTING_INTO_A_VEHICLE(0xBB062B2B5722478E);
lazy_func_t<void(Ped driver, float aggressiveness)>
	SET_DRIVER_AGGRESSIVENESS(0xA731F608CA104E3C);
lazy_func_t<BOOL(Ped ped, Hash motionStateHash, BOOL p2, BOOL p3, BOOL p4)>
	FORCE_PED_MOTION_STATE(0xF28965D04F570DCA);
lazy_func_t<int(int unused)> CREATE_GROUP(0x90370EBE0FEE1A3D);
lazy_func_t<void(Ped ped, int propId)> CLEAR_PED_PROP(0x0943E5B8E078E76E);
lazy_func_t<void(Any p0)> _0xA52D5247A4227E14(0xA52D5247A4227E14);
lazy_func_t<Any()> _0xA635C11B8C44AFC2(0xA635C11B8C44AFC2);
lazy_func_t<void(Pickup p0, Any p1, Blip *p2)>
	_0xE861D0B05C7662B8(0xE861D0B05C7662B8);
lazy_func_t<void(Ped ped)> CLEAR_ALL_PED_PROPS(0xCD8A7537A9B52F06);
lazy_func_t<
	Vector3(Ped ped, int boneId, float offsetX, float offsetY, float offsetZ)>
	GET_PED_BONE_COORDS(0x17C07FC640E86B4E);
lazy_func_t<void(Ped ped, BOOL instantly)>
	REMOVE_PED_HELMET(0xA7B2458D0AD6DED8);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_SWITCH_WEAPON(0xED7F7EFE9FABF340);
lazy_func_t<void(Any p0)> _0x600048C60D5C2C51(0x600048C60D5C2C51);
lazy_func_t<void(Any p0, Any *p1)> _0xB782F8238512BAD5(0xB782F8238512BAD5);
lazy_func_t<void(const char *asset)>
	REMOVE_ACTION_MODE_ASSET(0x13E940F88470FA51);
lazy_func_t<void(float p0, float p1)>
	SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0x7A556143A1C03898);
lazy_func_t<void(Ped ped, int tintIndex)>
	SET_PED_PARACHUTE_TINT_INDEX(0x333FC8DB079B7186);
lazy_func_t<void(Hash groupHash)> REMOVE_RELATIONSHIP_GROUP(0xB6BA2444AB393DA2);
lazy_func_t<BOOL(float x, float y, float z, float radius)>
	IS_ANY_PED_NEAR_POINT(0x083961498679DC9F);
lazy_func_t<void()> RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(0x46E56A7CD1D63C3F);
lazy_func_t<int(Any p0)> _0x5407B7288D0478B7(0x5407B7288D0478B7);
lazy_func_t<Any(const char *name, Hash *groupHash)>
	ADD_RELATIONSHIP_GROUP(0xF372BC22FCB88606);
lazy_func_t<BOOL(Ped ped1, Ped ped2)>
	IS_PED_HEADTRACKING_PED(0x5CD3CB88A7F8850D);
lazy_func_t<int()> _GET_NUM_MAKEUP_COLORS(0xD1F7CA1535D22818);
lazy_func_t<void(
	Ped ped,
	Ped target,
	float xOffset,
	float yOffset,
	float zOffset,
	float radius,
	BOOL p6)>
	SET_PED_DEFENSIVE_SPHERE_ATTACHED_TO_PED(0xF9B8F91AAD3B953E);
lazy_func_t<BOOL(Ped ped)> WAS_PED_SKELETON_UPDATED(0x11B499C1E0FF8559);
lazy_func_t<BOOL(Ped ped)> IS_PED_TRACKED(0x4C5E1F087CD10BB7);
lazy_func_t<void(Ped ped)> RESET_PED_IN_VEHICLE_CONTEXT(0x22EF8FF8778030EB);
lazy_func_t<BOOL(Ped ped)> IS_TRACKED_PED_VISIBLE(0x91C8E617F64188AC);
lazy_func_t<void(
	float x,
	float y,
	float z,
	float p3,
	float p4,
	float p5,
	float p6,
	int interiorFlags,
	float scale,
	int duration)>
	_0xB2AFF10216DEFA2F(0xB2AFF10216DEFA2F);
lazy_func_t<void(Ped ped, float multiplier)>
	SET_PED_LOD_MULTIPLIER(0xDC2C5C242AAC342B);
lazy_func_t<Vehicle(Ped ped, BOOL lastVehicle)>
	GET_VEHICLE_PED_IS_IN(0x9A9112A0FE9A4713);
lazy_func_t<BOOL(Ped ped)> IS_PED_PRONE(0xD6A86331A537A7B9);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_GET_OUT_UPSIDE_DOWN_VEHICLE(0xBC0ED94165A48BC2);
lazy_func_t<Any(Any p0)> _0x1E77FA7A62EE6C4C(0x1E77FA7A62EE6C4C);
lazy_func_t<void(
	Ped ped,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	BOOL p8,
	BOOL p9)>
	SET_PED_ANGLED_DEFENSIVE_AREA(0xC7F76DF27A5045A1);
lazy_func_t<void(Ped ped)> _CLEAR_PED_FACIAL_DECORATIONS(0xE3B27E70CEAB9F0C);
lazy_func_t<void(Ped ped, BOOL cannotRemove, int helmetFlag, int textureIndex)>
	GIVE_PED_HELMET(0x54C7C4A94367717E);
lazy_func_t<void()> _0x4759CC730F947C81(0x4759CC730F947C81);
lazy_func_t<BOOL(Ped ped)> _0x14590DDBEDB1EC85(0x14590DDBEDB1EC85);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_ANY_HELI(0x298B91AE825E5705);
lazy_func_t<BOOL(int groupId)> DOES_GROUP_EXIST(0x7C6B0C22F9F40BBE);
lazy_func_t<void(Ped ped, const char *clipset)>
	SET_PED_DRIVE_BY_CLIPSET_OVERRIDE(0xED34AB6C5CB36520);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(0x9F8AA94D6D97DBF4);
lazy_func_t<
	void(Ped ped, Any p1, float p2, float p3, float p4, float p5, BOOL p6)>
	_0xE4723DB6E736CCFF(0xE4723DB6E736CCFF);
lazy_func_t<void(Ped ped, int combatMovement)>
	SET_PED_COMBAT_MOVEMENT(0x4D9CA1009AFBD057);
lazy_func_t<BOOL(const char *asset)>
	HAS_STEALTH_MODE_ASSET_LOADED(0xE977FC5B08AF3441);
lazy_func_t<void(Ped ped)> CLEAR_PED_DECORATIONS(0x0E5173C163976E38);
lazy_func_t<void(Ped ped, const char *animName, const char *animDict)>
	SET_FACIAL_IDLE_ANIM_OVERRIDE(0xFFC24B988B938B38);
lazy_func_t<void(Ped ped, BOOL p1)> _0xF5846EDB26A98A24(0xF5846EDB26A98A24);
lazy_func_t<BOOL(Any p0)> _0x7F2F4F13AC5257EF(0x7F2F4F13AC5257EF);
lazy_func_t<int(Ped ped)> GET_PED_MONEY(0x3F69145BBA87BAE7);
lazy_func_t<void(Any p0, Any p1)> SET_PED_CLOTH_PRONE(0x82A3D6D9CC2CB8E3);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_PLAYS_HEAD_ON_HORN_ANIM_WHEN_DIES_IN_VEHICLE(0x94D94BF1A75AED3D);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_ENABLE_PED_ENVEFF_SCALE(0xD2C5AA0C0E8D0F1E);
lazy_func_t<void(Ped ped)> SET_PED_MOVE_ANIMS_BLEND_OUT(0x9E8C908F41584ECD);
lazy_func_t<BOOL(Ped ped)> IS_PED_CLIMBING(0x53E8CB4F48BFE623);
lazy_func_t<void(Ped ped, float angle)>
	SET_PED_VISUAL_FIELD_MIN_ELEVATION_ANGLE(0x7A276EB2C224D70F);
lazy_func_t<BOOL(Ped ped)> IS_PED_FLEEING(0xBBCCE00B381F8482);
lazy_func_t<void(Ped ped, int state)>
	SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(0x7A6535691B477C48);
lazy_func_t<BOOL(
	Ped ped,
	BOOL p1,
	BOOL p2,
	BOOL p3,
	BOOL p4,
	BOOL p5,
	BOOL p6,
	BOOL p7,
	Any p8)>
	_0x03EA03AF85A85CB7(0x03EA03AF85A85CB7);
lazy_func_t<Player(Ped ped)> GET_PLAYER_PED_IS_FOLLOWING(0x6A3975DEA89F9A17);
lazy_func_t<BOOL(Ped ped, const char *animDict, const char *anim)>
	IS_SCRIPTED_SCENARIO_PED_USING_CONDITIONAL_ANIM(0x6EC47A344923E1ED);
lazy_func_t<void(Ped ped, int stance, float p2)>
	CLEAR_PED_ALTERNATE_MOVEMENT_ANIM(0xD8D19675ED5FBDCE);
lazy_func_t<Any(Ped ped)> SET_PED_RAGDOLL_FORCE_FALL(0x01F6594B923B9251);
lazy_func_t<BOOL(Ped ped)> IS_PED_BEING_JACKED(0x9A497FE2DF198913);
lazy_func_t<int(Ped ped)> GET_PED_MAX_HEALTH(0x4700A416E8324EF3);
lazy_func_t<int(Ped ped)> GET_PED_COMBAT_MOVEMENT(0xDEA92412FCAEB3F5);
lazy_func_t<void(int scene)> _DISPOSE_SYNCHRONIZED_SCENE(0xCD9CC7E200A52A6F);
lazy_func_t<BOOL(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	BOOL p6,
	BOOL p7)>
	IS_ANY_PED_SHOOTING_IN_AREA(0xA0D3D71EA1086C55);
lazy_func_t<BOOL(Ped ped)> IS_PED_FALLING(0xFB92A102F1C4DFA3);
lazy_func_t<BOOL(Ped ped, Ped target)> IS_PED_IN_COMBAT(0x4859F1FC66A6278E);
lazy_func_t<BOOL(Ped ped)> _IS_PED_STANDING_IN_COVER(0x6A03BF943D767C93);
lazy_func_t<void(Ped ped)> _0xF79F9DEF0AADE61A(0xF79F9DEF0AADE61A);
lazy_func_t<
	int(float x1,
		float y1,
		float z1,
		float x2,
		float y2,
		float z2,
		BOOL p6,
		BOOL p7,
		BOOL p8,
		BOOL p9)>
	ADD_SCENARIO_BLOCKING_AREA(0x1B5C85C612E5256E);
lazy_func_t<BOOL()> CAN_CREATE_RANDOM_DRIVER(0xB8EB95E5B4E56978);
lazy_func_t<void(Ped ped, int damageAmount, BOOL armorFirst)>
	APPLY_DAMAGE_TO_PED(0x697157CED63F18D4);
lazy_func_t<void(Ped ped, const char *clipSet, float p2)>
	SET_PED_MOVEMENT_CLIPSET(0xAF8A94EDE7712BEF);
lazy_func_t<void(Ped ped, int p1, const char *p2)>
	CLEAR_PED_DAMAGE_DECAL_BY_ZONE(0x523C79AEEFCC4A2A);
lazy_func_t<void(Ped *ped)> DELETE_PED(0x9614299DCB53E54B);
lazy_func_t<void(Any p0)> _0xC79196DCB36F6121(0xC79196DCB36F6121);
lazy_func_t<float(Ped ped)> GET_PED_ENVEFF_SCALE(0x9C14D30395A51A3C);
lazy_func_t<BOOL(Ped ped)> IS_PED_INJURED(0x84A2DD9AC37C35C1);
lazy_func_t<void(float modifier)>
	SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(0x66460DEDDD417254);
lazy_func_t<void(Any p0, BOOL p1)>
	SET_TIME_EXCLUSIVE_DISPLAY_TEXTURE(0xFD325494792302D7);
lazy_func_t<void(Ped ped, BOOL p1, const char *action)>
	SET_PED_STEALTH_MOVEMENT(0x88CBB5CEB96B7BD2);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_NEVER_LEAVES_GROUP(0x3DBFC55D5C9BB447);
lazy_func_t<BOOL(Ped ped)>
	IS_PED_TRYING_TO_ENTER_A_LOCKED_VEHICLE(0x44D28D5DDFE5F68C);
lazy_func_t<void(Ped ped, float shapeMix, float skinMix, float thirdMix)>
	UPDATE_PED_HEAD_BLEND_DATA(0x723538F61C647C5A);
lazy_func_t<BOOL(Ped ped)> GET_PED_STEALTH_MOVEMENT(0x7C2AC9CA66575FBF);
lazy_func_t<Vehicle(Ped ped)>
	GET_VEHICLE_PED_IS_TRYING_TO_ENTER(0x814FA8BE5449445D);
lazy_func_t<float(Ped ped, int p1)> GET_COMBAT_FLOAT(0x52DFF8A10508090A);
lazy_func_t<int(Ped ped)> GET_PED_TYPE(0xFF059E1E4C01E63C);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_ANY_TAXI(0x6E575D6A898AB852);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	_0xFE07FF6495D52E2A(0xFE07FF6495D52E2A);
lazy_func_t<void(Any p0, BOOL p1)> _0xA9B61A329BFDCBEA(0xA9B61A329BFDCBEA);
lazy_func_t<int(int overlayID)>
	_GET_NUM_HEAD_OVERLAY_VALUES(0xCF1CE768BB43480E);
lazy_func_t<
	Ped(float x,
		float y,
		float z,
		float xRadius,
		float yRadius,
		float zRadius,
		int pedType)>
	GET_RANDOM_PED_AT_COORD(0x876046A8E3A4B71C);
lazy_func_t<void(Ped ped, int colorID, int highlightColorID)>
	_SET_PED_HAIR_COLOR(0x4CFFC65454C93A49);
lazy_func_t<Any(Ped ped, int slot, int drawableId, int textureId)>
	_0x39D55A620FCB6A3A(0x39D55A620FCB6A3A);
lazy_func_t<void(Ped ped, float x, float y, float z, BOOL toggle)>
	SET_PED_SHOOTS_AT_COORD(0x96A05E4FB321B1BA);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_MOTION_BLUR(0x0A986918B102B448);
lazy_func_t<void(Ped ped, int overlayID, int index, float opacity)>
	SET_PED_HEAD_OVERLAY(0x48F44967FA05CC1E);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0x952F06BEECD775CC(0x952F06BEECD775CC);
lazy_func_t<void(Ped ped, const char *damagePack, float damage, float mult)>
	APPLY_PED_DAMAGE_PACK(0x46DF918788CB093F);
lazy_func_t<void(Any p0)> _0x7D7A2E43E74E2EB8(0x7D7A2E43E74E2EB8);
lazy_func_t<void(Any p0)> _0xB50EB4CCB29704AC(0xB50EB4CCB29704AC);
lazy_func_t<void(Ped ped, Any itemSet)>
	SET_PED_PREFERRED_COVER_SET(0x8421EB4DA7E391B9);
lazy_func_t<void(Ped ped)> RESURRECT_PED(0x71BC8E838B9C6035);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_CAN_LEG_IK(0x73518ECE2485412B);
lazy_func_t<void(Ped ped, int flagId, BOOL doReset)>
	SET_PED_RESET_FLAG(0xC1E8A365BF3B29F2);
lazy_func_t<BOOL(Ped p0, Any *p1)> _0x9C6A6C19B6C0C496(0x9C6A6C19B6C0C496);
lazy_func_t<void(Ped ped, const char *p1)>
	_0x781DE8FA214E87D2(0x781DE8FA214E87D2);
lazy_func_t<Any()> _0xE8A169E666CBC541(0xE8A169E666CBC541);
lazy_func_t<void(Ped ped, BOOL toggle)> _0x129466ED55140F8D(0x129466ED55140F8D);
lazy_func_t<void(
	Ped ped,
	int p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	int p7,
	BOOL p8,
	const char *p9)>
	APPLY_PED_DAMAGE_DECAL(0x397C38AA7B4A5F83);
lazy_func_t<Any(Ped ped)> GET_PED_DECORATIONS_STATE(0x71EAB450D86954A1);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_BE_SHOT_IN_VEHICLE(0xC7EF1BA83230BA07);
lazy_func_t<void(Ped ped, float posX, float posY, float posZ)>
	SET_PED_COORDS_NO_GANG(0x87052FE446E07247);
lazy_func_t<void(
	Ped ped, const char *animDict, const char *animName, float p3, BOOL p4)>
	SET_PED_ALTERNATE_WALK_ANIM(0x6C60394CB4F75E9A);
lazy_func_t<int(Ped ped, int componentId)>
	GET_PED_DRAWABLE_VARIATION(0x67F3780DD425D4FC);
lazy_func_t<void(Ped ped, float p1, float p2, float p3, BOOL p4)>
	SET_PED_DEFENSIVE_AREA_DIRECTION(0x413C6C763A4AFFAD);
lazy_func_t<void(Ped ped, int helmetFlag)>
	SET_PED_HELMET_FLAG(0xC0E78D5C2CE3EB25);
lazy_func_t<void(BOOL value)>
	SET_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(0x14F19A8782C8071E);
lazy_func_t<void(Ped ped)> REVIVE_INJURED_PED(0x8D8ACD8388CD99CE);
lazy_func_t<void(Any p0, BOOL p1)> _0xCD018C591F94CB43(0xCD018C591F94CB43);
lazy_func_t<void(Any p0, BOOL p1)> _0x5B6010B3CBC29095(0x5B6010B3CBC29095);
lazy_func_t<void(Ped ped, int flagId, BOOL value)>
	SET_PED_CONFIG_FLAG(0x1913FE4CBF41C463);
lazy_func_t<BOOL(Ped ped, int componentId, int drawableId, int TextureId)>
	_IS_PED_PROP_VALID(0x2B16A3BFF1FBCE49);
lazy_func_t<void(float x, float y, float z, float range, int p4)>
	SET_SCENARIO_PEDS_SPAWN_IN_SPHERE_AREA(0x28157D43CF600981);
lazy_func_t<void()> RESET_AI_WEAPON_DAMAGE_MODIFIER(0xEA16670E7BA4743C);
lazy_func_t<BOOL(Ped ped)> _0x26AF0E8E30BD2A2C(0x26AF0E8E30BD2A2C);
lazy_func_t<BOOL(Any p0)> _0x3E802F11FBE27674(0x3E802F11FBE27674);
lazy_func_t<BOOL(Ped ped)> _0xA3F3564A5B3646C0(0xA3F3564A5B3646C0);
lazy_func_t<BOOL(int sceneId)>
	IS_SYNCHRONIZED_SCENE_RUNNING(0x25D39B935A038A26);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_FLYING_VEHICLE(0x9134873537FA419C);
lazy_func_t<void(Ped ped, Hash collection, Hash overlay)>
	_SET_PED_FACIAL_DECORATION(0x5619BFA07CFD7833);
lazy_func_t<BOOL(Ped ped)> IS_PED_MALE(0x6D9F5FAA7488BA46);
lazy_func_t<BOOL(Ped ped)> IS_PED_GOING_INTO_COVER(0x9F65DBC537E59AD5);
lazy_func_t<Any(Ped ped)> _0x6585D955A68452A5(0x6585D955A68452A5);
lazy_func_t<Any(Hash modelHash, Any p1, Any p2)>
	_0xC56FBF2F228E1DAC(0xC56FBF2F228E1DAC);
lazy_func_t<void(
	Ped ped,
	Ped attachPed,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	BOOL p9,
	BOOL p10)>
	SET_PED_DEFENSIVE_AREA_ATTACHED_TO_PED(0x4EF47FE21698A8B6);
lazy_func_t<void(const char *asset)>
	REMOVE_STEALTH_MODE_ASSET(0x9219857D21F0E842);
lazy_func_t<void(Ped ped, Hash collection, Hash overlay)>
	_SET_PED_DECORATION(0x5F5D1665E352A839);
lazy_func_t<void(int sceneID, float rate)>
	SET_SYNCHRONIZED_SCENE_RATE(0xB6C49F8A5E295A5D);
lazy_func_t<void(
	Ped ped,
	int ikIndex,
	Entity entityLookAt,
	int boneLookAt,
	float offsetX,
	float offsetY,
	float offsetZ,
	Any p7,
	int blendInDuration,
	int blendOutDuration)>
	SET_IK_TARGET(0xC32779C16FCEECD9);
lazy_func_t<void(const char *asset)>
	REQUEST_ACTION_MODE_ASSET(0x290E2780BB7AA598);
lazy_func_t<void(Ped ped, int amount)> SET_PED_ARMOUR(0xCEA04D83135264CC);
lazy_func_t<void(BOOL toggle)> _0xF2BEBCDFAFDAA19E(0xF2BEBCDFAFDAA19E);
lazy_func_t<void(int sceneID)> DETACH_SYNCHRONIZED_SCENE(0x6D38F1F04CBB37EA);
lazy_func_t<Any()> _0x3C67506996001F5E(0x3C67506996001F5E);
lazy_func_t<void(Ped ped, Hash weaponHash)>
	EXPLODE_PED_HEAD(0x2D05CED3A38D0F3A);
lazy_func_t<void(BOOL p0)> _0x6B0E6172C9A4D902(0x6B0E6172C9A4D902);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_SEEING_RANGE(0xF29CF591C4BF6CEE);
lazy_func_t<void(Ped ped, Hash hash)>
	SET_PED_RELATIONSHIP_GROUP_HASH(0xC80A74AC829DDD92);
lazy_func_t<void(int groupHandle)>
	RESET_GROUP_FORMATION_DEFAULT_SPACING(0x63DAB4CCB3273205);
lazy_func_t<void(Any p0, Any *p1, Any *p2, Any *p3)>
	_0x013E5CFC38CD5387(0x013E5CFC38CD5387);
lazy_func_t<BOOL(Ped ped)> _0x784002A632822099(0x784002A632822099);
lazy_func_t<int(Hash collection, Hash overlay)>
	_GET_TATTOO_ZONE(0x9FD452BFBE7A7A8B);
lazy_func_t<void(Ped ped, float heading)>
	SET_PED_DESIRED_HEADING(0xAA5A7ECE2AA8FE70);
lazy_func_t<Any(Any p0, float p1, float p2, float p3, float p4)>
	_0x336B3D200AB007CB(0x336B3D200AB007CB);
lazy_func_t<int(Ped ped, int componentId)>
	GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(0x27561561732A7842);
lazy_func_t<BOOL(Any *p0, Any *p1)> _0x9E30E91FB03A2CAF(0x9E30E91FB03A2CAF);
lazy_func_t<BOOL(Ped ped)> _0x61767F73EACEED21(0x61767F73EACEED21);
lazy_func_t<BOOL(Ped ped, Vehicle vehicle)>
	IS_PED_ON_SPECIFIC_VEHICLE(0xEC5F66E459AF3BB2);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_HEARING_RANGE(0x33A8F7F7D5F7F33C);
lazy_func_t<void(Ped ped, const char *clipSet)>
	SET_PED_WEAPON_MOVEMENT_CLIPSET(0x2622E35B77D3ACA2);
lazy_func_t<void(Ped ped, int p1)>
	CLEAR_PED_BLOOD_DAMAGE_BY_ZONE(0x56E3B78C5408D9F4);
lazy_func_t<void(Any p0, BOOL p1)>
	REMOVE_SCENARIO_BLOCKING_AREA(0x31D16B74C6E29D66);
lazy_func_t<void(Ped ped, BOOL canWearHelmet)>
	SET_PED_HELMET(0x560A43136EB58105);
lazy_func_t<void(Ped ped, int p1)> SET_PED_COMBAT_RANGE(0x3C606747B23E497B);
lazy_func_t<void(Ped ped, int responseType)>
	SET_PED_TARGET_LOSS_RESPONSE(0x0703B9079823DA4A);
lazy_func_t<void(Ped ped, BOOL p1, Any p2, const char *action)>
	SET_PED_USING_ACTION_MODE(0xD75ACCF5E0FB5367);
lazy_func_t<void(int handle)> UNREGISTER_PEDHEADSHOT(0x96B1361D9B24C2FF);
lazy_func_t<Any()> _0xEBB376779A760AA8(0xEBB376779A760AA8);
lazy_func_t<BOOL(Ped ped)> IS_PED_ON_FOOT(0x01FEE67DB37F59B2);
lazy_func_t<BOOL(Ped ped)> IS_PED_DOING_DRIVEBY(0xB2C086CC1BF8F2BF);
lazy_func_t<BOOL(Ped ped, int p1)> IS_PED_BEING_STUNNED(0x4FBACCE3B4138EE8);
lazy_func_t<BOOL(Ped ped)> CAN_KNOCK_PED_OFF_VEHICLE(0x51AC07A44D4F5B8A);
lazy_func_t<void(BOOL toggle)> SET_CREATE_RANDOM_COPS(0x102E68B2024D536D);
lazy_func_t<BOOL(Ped ped)> WAS_PED_KILLED_BY_TAKEDOWN(0x7F08E26039C7347C);
lazy_func_t<float(int sceneID)>
	GET_SYNCHRONIZED_SCENE_PHASE(0xE4A310B1D7FA73CC);
lazy_func_t<void(Ped ped, Hash patternHash)>
	SET_PED_FIRING_PATTERN(0x9AC577F5A12AD8A9);
lazy_func_t<void(Any p0, Any *p1, Any *p2, Any *p3)>
	_0x4852FC386E2E1BB5(0x4852FC386E2E1BB5);
lazy_func_t<BOOL(Ped ped)> IS_PED_RUNNING_RAGDOLL_TASK(0xE3B6097CC25AA69E);
lazy_func_t<void(Ped ped)> KNOCK_PED_OFF_VEHICLE(0x45BBCBA77C29A841);
lazy_func_t<void(
	Ped ped,
	int boneIndex,
	float xRot,
	float yRot,
	float zRot,
	const char *woundType)>
	APPLY_PED_BLOOD(0x83F7E01C7B769A26);
lazy_func_t<BOOL(Ped ped)> WAS_PED_KILLED_BY_STEALTH(0xF9800AA1A771B000);
lazy_func_t<BOOL(Ped ped)> IS_PED_FATALLY_INJURED(0xD839450756ED5A80);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_PARACHUTE_FREE_FALL(0x7DCE8BDA0F1C1200);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_PEEK_IN_COVER(0xC514825C507E3736);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_ALLOW_VEHICLES_OVERRIDE(0x3C028C636A414ED9);
lazy_func_t<BOOL(Ped ped)> IS_PED_ON_VEHICLE(0x67722AEB798E5FAB);
lazy_func_t<BOOL(Ped ped)> IS_PED_PLANTING_BOMB(0xC70B5FAE151982D8);
lazy_func_t<void(Ped ped, BOOL p1)> _0x49E50BDB8BA4DAB2(0x49E50BDB8BA4DAB2);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_PLAY_AMBIENT_BASE_ANIMS(0x0EB0585D15254740);
lazy_func_t<BOOL(Ped ped)> IS_PED_HUMAN(0xB980061DA992779D);
lazy_func_t<Ped(int groupID)> _GET_PED_AS_GROUP_LEADER(0x5CCE68DBD5FE93EC);
lazy_func_t<void(Ped ped, float p1)> _0x110F526AB784111F(0x110F526AB784111F);
lazy_func_t<Any()> _0x876928DDDFCCC9CD(0x876928DDDFCCC9CD);
lazy_func_t<Vector3(Ped ped, float p1, float p2)>
	GET_DEAD_PED_PICKUP_COORDS(0xCD5003B097200F36);
lazy_func_t<void(Ped ped, int value)> SET_PED_MAX_HEALTH(0xF5F6378C4F3419D3);
lazy_func_t<Any(Ped ped, BOOL toggle)>
	SET_PED_DIES_WHEN_INJURED(0x5BA7919BED300023);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(0xDF993EE5E90ABA25);
lazy_func_t<void(Ped ped, float p1)>
	SET_SCRIPTED_ANIM_SEAT_OFFSET(0x5917BBA32D06C230);
lazy_func_t<void(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	int interiorFlags,
	float scale,
	int duration)>
	_0x2DF9038C90AD5264(0x2DF9038C90AD5264);
lazy_func_t<BOOL()> CAN_CREATE_RANDOM_COPS(0x5EE2CAFF7F17770D);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_TO_LOAD_COVER(0x332B562EEDA62399);
lazy_func_t<void(Ped ped, Ped target)> REGISTER_TARGET(0x2F25D9AEFA34FBA2);
lazy_func_t<BOOL(Ped ped, Vehicle vehicle, BOOL atGetIn)>
	IS_PED_IN_VEHICLE(0xA3EE4A07279BB9DB);
lazy_func_t<BOOL(Ped ped, Hash modelHash)> IS_PED_MODEL(0xC9D55B1A358A5BF7);
lazy_func_t<void(Ped ped, Player player, BOOL toggle)>
	SET_PED_CAN_BE_TARGETTED_BY_PLAYER(0x66B57B72E0836A76);
lazy_func_t<int(Ped ped, int overlayID)>
	_GET_PED_HEAD_OVERLAY_VALUE(0xA60EF3B6461A4D43);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_GENERATES_DEAD_BODY_EVENTS(0x7FB17BA2E7DECA5B);
lazy_func_t<BOOL(int handle)> IS_PEDHEADSHOT_READY(0x7085228842B13A67);
lazy_func_t<BOOL(Ped ped)> IS_PED_ON_ANY_BIKE(0x94495889E22C6479);
lazy_func_t<BOOL(Ped ped)> IS_PED_PERFORMING_STEALTH_KILL(0xFD4CCDBCC59941B7);
lazy_func_t<int(Ped ped)> REGISTER_PEDHEADSHOT(0x4462658788425076);
lazy_func_t<BOOL(Ped ped)> IS_PED_AIMING_FROM_COVER(0x3998B1276A3300E5);
lazy_func_t<void(Ped ped, float value)> SET_PED_ID_RANGE(0xF107E836A70DCE05);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_AS_ENEMY(0x02A0C9720B854BFA);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_PLAY_AMBIENT_ANIMS(0x6373D1349925A70E);
lazy_func_t<BOOL(Ped ped, Hash modelHash)> IS_PED_IN_MODEL(0x796D90EFB19AA332);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_GROUP(0x5891CAC5D4ACFF74);
lazy_func_t<void(Ped ped)>
	SET_PED_DEFAULT_COMPONENT_VARIATION(0x45EEE61580806D63);
lazy_func_t<void(Ped ped)> CLEAR_FACIAL_IDLE_ANIM_OVERRIDE(0x726256CC1EEB182F);
lazy_func_t<void(Ped ped)>
	STOP_PED_WEAPON_FIRING_WHEN_DROPPED(0xC158D28142A34608);
lazy_func_t<void(Ped ped, int p1)> SET_PED_COMBAT_ABILITY(0xC7622C0D36B2FDA8);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_DIES_INSTANTLY_IN_WATER(0xEEB64139BA29A7CF);
lazy_func_t<BOOL(Ped ped)> _0x7350823473013C02(0x7350823473013C02);
lazy_func_t<void(Ped *ped)> REMOVE_PED_ELEGANTLY(0xAC6D445B994DF95E);
lazy_func_t<int(Ped ped)> _0x1E98817B311AE98A(0x1E98817B311AE98A);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_DIES_IN_VEHICLE(0x2A30922C90C9B42C);
lazy_func_t<void(BOOL startImmediately, int messageId)>
	CREATE_NM_MESSAGE(0x418EF2A1BCE56685);
lazy_func_t<void(float multiplier)>
	SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0x95E3D6257B166CF2);
lazy_func_t<void(Ped ped, BOOL p1, BOOL p2)>
	SET_PED_CAN_SMASH_GLASS(0x1CCE141467FF42A2);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_BE_TARGETED_WHEN_INJURED(0x638C03B0F9878F57);
lazy_func_t<int(Ped ped, int bone)>
	GET_PED_RAGDOLL_BONE_INDEX(0x2057EF813397A772);
lazy_func_t<BOOL(Ped ped)> IS_PED_HURT(0x5983BB449D7FDB12);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_ANY_PLANE(0x5FFF4CFC74D8FB80);
lazy_func_t<void(Ped ped, int attributes, BOOL p2)>
	SET_PED_FLEE_ATTRIBUTES(0x70A2D1137C8ED7C9);
lazy_func_t<void(Ped ped, BOOL p1)> _0x75BA1CB3B7D40CAF(0x75BA1CB3B7D40CAF);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_MAX_MOVE_BLEND_RATIO(0x433083750C5E064A);
lazy_func_t<void(Ped ped, int ms)>
	SET_PED_MIN_GROUND_TIME_FOR_STUNGUN(0xFA0675AB151073FA);
lazy_func_t<void(Ped ped, int value)> SET_PED_ALERTNESS(0xDBA71115ED9941A6);
lazy_func_t<void(Ped ped, float p1)>
	CLEAR_PED_ALTERNATE_WALK_ANIM(0x8844BBFCE30AA9E9);
lazy_func_t<Ped(Ped ped)> GET_MELEE_TARGET_FOR_PED(0x18A3E9EE1297FD39);
lazy_func_t<BOOL(Ped ped)> IS_PED_JACKING(0x4AE4FF911DFB61DA);
lazy_func_t<void(Ped ped, float height)>
	SET_PED_WETNESS_HEIGHT(0x44CB6447D2571AA0);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_MOVE_RATE_OVERRIDE(0x085BF80FA50A39D1);
lazy_func_t<int(Ped ped, int *sizeAndVehs)>
	GET_PED_NEARBY_VEHICLES(0xCFF869CBFA210D82);
lazy_func_t<void(Any p0, Any p1)> _0x83A169EABCDB10A2(0x83A169EABCDB10A2);
lazy_func_t<void(Ped ped, int groupId)>
	SET_PED_AS_GROUP_LEADER(0x2A7819605465FBCE);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_ALLOWED_TO_DUCK(0xDA1F1B7BE1A8766F);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_ENABLE_BOUND_ANKLES(0xC52E0F855C58FC2E);
lazy_func_t<void(Any p0, BOOL p1, Any p2, Any p3)>
	_0xCB968B53FC7F916D(0xCB968B53FC7F916D);
lazy_func_t<Any(Any p0)> _0xF033419D1B81FAE8(0xF033419D1B81FAE8);
lazy_func_t<void(
	Ped ped, int componentId, int drawableId, int textureId, int paletteId)>
	SET_PED_COMPONENT_VARIATION(0x262B14F48D29DE80);
lazy_func_t<void(Ped ped, const char *animName, const char *animDict)>
	PLAY_FACIAL_ANIM(0xE1E65CA8AC9C00ED);
lazy_func_t<Any(Ped ped)> GET_PED_COMBAT_RANGE(0xF9D9F7F2DB8E2FA0);
lazy_func_t<void(Any p0, Any *p1, Any *p2, Any *p3)>
	_0x280C7E3AC7F56E90(0x280C7E3AC7F56E90);
lazy_func_t<Ped(Vehicle vehicle, BOOL returnHandle)>
	CREATE_RANDOM_PED_AS_DRIVER(0x9B62392B474F44A0);
lazy_func_t<void(int groupId)> REMOVE_GROUP(0x8EB2F69076AF7053);
lazy_func_t<int(Ped ped, int componentId)>
	GET_PED_TEXTURE_VARIATION(0x04A355E041E004E6);
lazy_func_t<void(Any p0)> _0x570389D1C3DE3C6B(0x570389D1C3DE3C6B);
lazy_func_t<BOOL(Ped ped, BOOL atGetIn)>
	IS_PED_IN_ANY_VEHICLE(0x997ABD671D25CA0B);
lazy_func_t<BOOL(Ped ped, int groupId)> IS_PED_GROUP_MEMBER(0x9BB01E3834671191);
lazy_func_t<BOOL(Ped ped, Ped otherPed, float angle)>
	IS_PED_FACING_PED(0xD71649DB0A545AA3);
lazy_func_t<void(Ped ped, int shootRate)>
	SET_PED_SHOOT_RATE(0x614DA022990752DC);
lazy_func_t<Vector3(Ped ped, BOOL worldSpace)>
	GET_PED_EXTRACTED_DISPLACEMENT(0xE0AF41401ADF87E3);
lazy_func_t<BOOL(Ped ped, Entity *evadingEntity)>
	IS_PED_EVASIVE_DIVING(0x414641C26E105898);
lazy_func_t<void(Any p0, Any p1)> _0x1216E0BFA72CC703(0x1216E0BFA72CC703);
lazy_func_t<void()> CLEAR_PED_NON_CREATION_AREA(0x2E05208086BA0651);
lazy_func_t<void(Ped ped, float p1)> _0x2735233A786B1BEF(0x2735233A786B1BEF);
lazy_func_t<BOOL(Ped ped)> IS_PED_RAGDOLL(0x47E4E977581C5B55);
lazy_func_t<BOOL(Ped ped)> _0xD1871251F3B5ACD7(0xD1871251F3B5ACD7);
lazy_func_t<void(Ped ped)> _0xC2EE020F5FB4DB53(0xC2EE020F5FB4DB53);
lazy_func_t<BOOL(Ped ped)> IS_PED_SWIMMING_UNDER_WATER(0xC024869A53992F34);
lazy_func_t<void(Any p0)> _0xA3A9299C4F2ADB98(0xA3A9299C4F2ADB98);
lazy_func_t<void(Ped ped, float value)>
	SET_PED_MIN_MOVE_BLEND_RATIO(0x01A898D26E2333DD);
lazy_func_t<BOOL(Ped ped)> IS_PED_VAULTING(0x117C70D1F5730B5E);
lazy_func_t<Ped(Ped ped)> GET_PEDS_JACKER(0x9B128DC36C1E04CF);
lazy_func_t<void(Ped ped)> RESET_PED_STRAFE_CLIPSET(0x20510814175EA477);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_ANY_POLICE_VEHICLE(0x0BD04E29640C9C12);
lazy_func_t<void(int sceneID, Entity entity, int boneIndex)>
	ATTACH_SYNCHRONIZED_SCENE_TO_ENTITY(0x272E4723B56A3B96);
lazy_func_t<void(Ped ped)> RESET_PED_LAST_VEHICLE(0xBB8DE8CF6A8DD8BB);
lazy_func_t<void(Any p0, BOOL p1)> _0x061CB768363D6424(0x061CB768363D6424);
lazy_func_t<BOOL(Ped ped)> HAS_PED_HEAD_BLEND_FINISHED(0x654CD0A825161131);
lazy_func_t<void(Ped ped)> _0x4668D80430D6C299(0x4668D80430D6C299);
lazy_func_t<
	void(Ped ped, float x, float y, float z, float radius, BOOL p5, BOOL p6)>
	SET_PED_SPHERE_DEFENSIVE_AREA(0x9D3151A373974804);
lazy_func_t<void(Ped ped, const char *name)>
	SET_PED_NAME_DEBUG(0x98EFA132A4117BE1);
lazy_func_t<void(
	Ped ped,
	Any p1,
	float p2,
	float p3,
	float p4,
	float p5,
	Any p6,
	float p7,
	Any *p8)>
	APPLY_PED_BLOOD_SPECIFIC(0xEF0D582CBF2D9B0F);
lazy_func_t<Ped(Ped ped)> GET_MOUNT(0xE7E11B8DCBED1058);
lazy_func_t<Hash(Ped ped)> GET_PED_RELATIONSHIP_GROUP_HASH(0x7DBDD04862D95F04);
lazy_func_t<void(Ped ped, float radius)>
	REGISTER_HATED_TARGETS_AROUND_PED(0x9222F300BF8354FE);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_CAN_HEAD_IK(0xC11C18092C5530DC);
lazy_func_t<void(Ped ped, BOOL toggle, BOOL p2)>
	SET_CAN_ATTACK_FRIENDLY(0xB3B1CB349FF9C75D);
lazy_func_t<void(Any p0, BOOL p1)> _0x2B5AA717A181FB4C(0x2B5AA717A181FB4C);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_DIES_IN_WATER(0x56CEF0AC79073BDE);
lazy_func_t<Ped(Ped ped)> GET_JACK_TARGET(0x5486A79D9FBD342D);
lazy_func_t<void(Ped ped, BOOL toggle)>
	SET_PED_CAN_BE_TARGETED_WITHOUT_LOS(0x4328652AE5769C71);
lazy_func_t<void(Any p0)> _0x80054D7FCC70EEC6(0x80054D7FCC70EEC6);
lazy_func_t<void(Ped ped, int mode)> SET_PED_LEG_IK_MODE(0xC396F5B86FF9FEBD);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	_0xD8C3BE3EE94CAF2D(0xD8C3BE3EE94CAF2D);
lazy_func_t<BOOL(Ped ped)> IS_PED_RELOADING(0x24B100C68C645951);
lazy_func_t<BOOL()> CAN_CREATE_RANDOM_BIKE_RIDER(0xEACEEDA81751915C);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_COVER_FACING_LEFT(0x845333B3150583AB);
lazy_func_t<Entity(Ped ped)> GET_PED_SOURCE_OF_DEATH(0x93C8B64DEB84728C);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_KEEP_TASK(0x971D38760FBC02EF);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_CAN_RAGDOLL(0xB128377056A54E2A);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_CAN_ARM_IK(0x6C3B4D6D13B4C841);
lazy_func_t<Any(Ped ped, int accuracy)> SET_PED_ACCURACY(0x7AEFB85C1D49DEB6);
lazy_func_t<BOOL(Ped ped)> IS_PED_JUMPING_OUT_OF_VEHICLE(0x433DDFFE2044B636);
lazy_func_t<BOOL(int p0)> _0x451294E859ECC018(0x451294E859ECC018);
lazy_func_t<void(Ped ped, int *outTintIndex)>
	GET_PED_PARACHUTE_TINT_INDEX(0xEAF5F7E5AE7C6C9D);
lazy_func_t<void(Ped ped, float unk)> _0xEC4B4B3B9908052A(0xEC4B4B3B9908052A);
lazy_func_t<BOOL(Ped ped)> IS_PED_SWIMMING(0x9DE327631295B4C2);
lazy_func_t<void(
	Ped ped,
	int shapeFirstID,
	int shapeSecondID,
	int shapeThirdID,
	int skinFirstID,
	int skinSecondID,
	int skinThirdID,
	float shapeMix,
	float skinMix,
	float thirdMix,
	BOOL isParent)>
	SET_PED_HEAD_BLEND_DATA(0x9414E18B9434C2FE);
lazy_func_t<void(Ped ped, BOOL p1, BOOL p2, BOOL p3, BOOL p4)>
	KNOCK_OFF_PED_PROP(0x6FD7816A36615F48);
lazy_func_t<void(Ped ped)> _0xAFF4710E2A0A6C12(0xAFF4710E2A0A6C12);
lazy_func_t<void(Ped ped)> CLEAR_PED_LAST_DAMAGE_BONE(0x8EF6B7AC68E2F01B);
lazy_func_t<Any(Ped ped, BOOL pinned, int p2)>
	SET_PED_PINNED_DOWN(0xAAD6D1ACF08F4612);
lazy_func_t<void(int relationship, Hash group1, Hash group2)>
	SET_RELATIONSHIP_BETWEEN_GROUPS(0xBF25EB89375A37AD);
lazy_func_t<int(Ped ped)> GET_PED_GROUP_INDEX(0xF162E133B4E7A675);
lazy_func_t<void(BOOL toggle)>
	SET_CREATE_RANDOM_COPS_ON_SCENARIOS(0x444CB7D7DBE6973D);
lazy_func_t<int(Any p0)> _0xEA9960D07DADCF10(0xEA9960D07DADCF10);
lazy_func_t<void(Ped ped, BOOL toggle)>
	REMOVE_PED_DEFENSIVE_AREA(0x74D4E028107450A9);
lazy_func_t<void()> REMOVE_SCENARIO_BLOCKING_AREAS(0xD37401D78A929A49);
lazy_func_t<void(Ped ped)> _0x687C0B594907D2E8(0x687C0B594907D2E8);
lazy_func_t<BOOL(Ped ped)> _0xEBD0EDBA5BE957CF(0xEBD0EDBA5BE957CF);
lazy_func_t<void(const char *asset)>
	REQUEST_STEALTH_MODE_ASSET(0x2A0A62FCDEE16D4F);
}} // namespace PED::
namespace OBJECT { namespace {
lazy_func_t<void()> _0x66A49D021870FE88(0x66A49D021870FE88);
lazy_func_t<BOOL(Any p0, BOOL p1, BOOL p2, BOOL p3, Any p4)>
	_0x85B6C850546FDDE2(0x85B6C850546FDDE2);
lazy_func_t<Vector3(Pickup pickup)> GET_PICKUP_COORDS(0x225B8B35C88029B3);
lazy_func_t<void(Object *object)> DELETE_OBJECT(0x539E0AE3E6634B9F);
lazy_func_t<void(Hash doorHash, BOOL p1)>
	_0xD9B71952F78A2640(0xD9B71952F78A2640);
lazy_func_t<Pickup(
	Hash pickupHash,
	float x,
	float y,
	float z,
	BOOL placeOnGround,
	Hash modelHash)>
	CREATE_PORTABLE_PICKUP(0x2EAF1FDB2FB55698);
lazy_func_t<Object(Pickup pickup)> GET_PICKUP_OBJECT(0x5099BC55630B25AE);
lazy_func_t<BOOL(Object object)> _0x11D1E53A726891FE(0x11D1E53A726891FE);
lazy_func_t<void(Hash doorHash, BOOL p1, BOOL p2, BOOL p3)>
	_0xC485E07E4F0B7958(0xC485E07E4F0B7958);
lazy_func_t<Object(
	Hash modelHash,
	float x,
	float y,
	float z,
	BOOL isNetwork,
	BOOL thisScriptCheck,
	BOOL dynamic)>
	CREATE_OBJECT_NO_OFFSET(0x9A294B2138ABB884);
lazy_func_t<void(Any p0)> _0x762DB2D380B48D04(0x762DB2D380B48D04);
lazy_func_t<void(
	Object object,
	float weight,
	float p2,
	float p3,
	float p4,
	float p5,
	float gravity,
	float p7,
	float p8,
	float p9,
	float p10,
	float buoyancy)>
	SET_OBJECT_PHYSICS_PARAMS(0xF6DF6E90DE7DF90F);
lazy_func_t<BOOL(Pickup pickup)> DOES_PICKUP_EXIST(0xAFC1CA75AD4074D1);
lazy_func_t<void(Object object, Any p1, BOOL p2)>
	SET_TEAM_PICKUP_OBJECT(0x53E0DF1A2A3CF0CA);
lazy_func_t<void(Pickup pickup)> REMOVE_PICKUP(0x3288D8ACAECD2AB2);
lazy_func_t<void(Object p0, Any p1, BOOL p2)>
	_0xE7E4C198B0185900(0xE7E4C198B0185900);
lazy_func_t<int(float x, float y, float z, float rotation, const char *name)>
	_GET_DES_OBJECT(0xB48FCED898292E52);
lazy_func_t<void(Hash hash, BOOL toggle)>
	_0xF2E1A7133DD356A6(0xF2E1A7133DD356A6);
lazy_func_t<Pickup(
	Hash pickupHash,
	float posX,
	float posY,
	float posZ,
	float rotX,
	float rotY,
	float rotZ,
	int flag,
	int amount,
	Any p9,
	BOOL p10,
	Hash modelHash)>
	CREATE_PICKUP_ROTATE(0x891804727E0A98B7);
lazy_func_t<void(Hash doorHash, float p1, BOOL p2, BOOL p3)>
	_0x03C27E13B42A0E82(0x03C27E13B42A0E82);
lazy_func_t<BOOL(Hash doorHash)> _DOES_DOOR_EXIST(0xC153C43EA202C8C1);
lazy_func_t<void(BOOL p0)> _0xC7F29CA00F46350E(0xC7F29CA00F46350E);
lazy_func_t<Pickup(
	Hash pickupHash,
	float posX,
	float posY,
	float posZ,
	int p4,
	int value,
	Hash modelHash,
	BOOL returnHandle,
	BOOL p8)>
	CREATE_AMBIENT_PICKUP(0x673966A0C0FD7171);
lazy_func_t<BOOL(Pickup pickup)> HAS_PICKUP_BEEN_COLLECTED(0x80EC48E6679313F9);
lazy_func_t<
	BOOL(float p0, float p1, float p2, float p3, Hash modelHash, Any p5)>
	HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_BROKEN(0x761B0E69AC4D007E);
lazy_func_t<BOOL(float p0, float p1, float p2, Any p3, Any *p4)>
	_0x589F80B325CC82C5(0x589F80B325CC82C5);
lazy_func_t<BOOL(Any p0, Player player, float p2, int p3)>
	_0x024A60DEB0EA69F0(0x024A60DEB0EA69F0);
lazy_func_t<void()> _0xA2C1F5E92AFE49ED(0xA2C1F5E92AFE49ED);
lazy_func_t<BOOL(
	Object object,
	float toX,
	float toY,
	float toZ,
	float speedX,
	float speedY,
	float speedZ,
	BOOL collision)>
	SLIDE_OBJECT(0x2FDFF4107B8C1147);
lazy_func_t<Pickup(
	Hash pickupHash,
	float x,
	float y,
	float z,
	BOOL placeOnGround,
	Hash modelHash)>
	_CREATE_PORTABLE_PICKUP_2(0x125494B98A21AAF7);
lazy_func_t<Pickup(
	Hash pickupHash,
	float posX,
	float posY,
	float posZ,
	int p4,
	int value,
	BOOL p6,
	Hash modelHash)>
	CREATE_PICKUP(0xFBA08C503DD5FA58);
lazy_func_t<void(Pickup pickup, int duration)>
	SET_PICKUP_REGENERATION_TIME(0x78015C9B4B3ECC9D);
lazy_func_t<void(Any p0, BOOL p1)> _0xC6033D32241F6FB5(0xC6033D32241F6FB5);
lazy_func_t<void(BOOL p0)> _0x78857FC65CADB909(0x78857FC65CADB909);
lazy_func_t<Object(
	Object modelHash,
	float x,
	float y,
	float z,
	BOOL isNetwork,
	BOOL thisScriptCheck,
	BOOL dynamic)>
	CREATE_OBJECT(0x509D5878EB39E842);
lazy_func_t<void()> _0x701FDA1E82076BA4(0x701FDA1E82076BA4);
lazy_func_t<BOOL(Any p0, Player player, int p2)>
	_0x1761DC5D8471CBAA(0x1761DC5D8471CBAA);
lazy_func_t<BOOL(Any p0)> _0xDF97CDD4FC08FD34(0xDF97CDD4FC08FD34);
lazy_func_t<void(Any p0, BOOL p1)> _0xEB6F1A9B5510A5D2(0xEB6F1A9B5510A5D2);
lazy_func_t<
	BOOL(float p0, float p1, float p2, float p3, Hash modelHash, BOOL p5)>
	_0x46494A2475701343(0x46494A2475701343);
lazy_func_t<float(Any p0)> _0x260EE4FDBDF4DB01(0x260EE4FDBDF4DB01);
lazy_func_t<BOOL(int handle)> _DOES_DES_OBJECT_EXIST(0x52AF537A0C5B8AAD);
lazy_func_t<void(float x, float y, float z, int colorIndex)>
	_HIGHLIGHT_PLACEMENT_COORDS(0x3430676B11CDF21D);
lazy_func_t<Hash(Pickup pickupHash)> _GET_PICKUP_HASH(0x5EAAD83F8CFB4575);
lazy_func_t<void(
	Hash type, float x, float y, float z, BOOL locked, float heading, BOOL p6)>
	SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(0xF82D8F1926A02C3D);
lazy_func_t<void(Hash doorHash, BOOL p1)>
	_0xA85A21582451E951(0xA85A21582451E951);
lazy_func_t<BOOL(Hash objectHash, float x, float y, float z, float range)>
	IS_OBJECT_NEAR_POINT(0x8C90FE4B381BA60A);
lazy_func_t<void(Hash doorHash, float heading, BOOL p2, BOOL p3)>
	_0x9BA001CB45CBF627(0x9BA001CB45CBF627);
lazy_func_t<BOOL(Hash door)> IS_DOOR_CLOSED(0xC531EE8A1145A149);
lazy_func_t<BOOL(Object object)> IS_OBJECT_VISIBLE(0x8B32ACE6326A7546);
lazy_func_t<void(Object object)> _MARK_OBJECT_FOR_DELETION(0xADBE4809F19F927A);
lazy_func_t<void(Object object, BOOL p1, BOOL p2)>
	_0x92AEFB5F6E294023(0x92AEFB5F6E294023);
lazy_func_t<BOOL(float x, float y, float z, float range, BOOL p4)>
	IS_ANY_OBJECT_NEAR_POINT(0x397DC58FF00298D1);
lazy_func_t<Vector3(
	float xPos,
	float yPos,
	float zPos,
	float heading,
	float xOffset,
	float yOffset,
	float zOffset)>
	_GET_OBJECT_OFFSET_FROM_COORDS(0x163E252DE035A133);
lazy_func_t<float(Hash doorHash)> _0x65499865FCA6E5EC(0x65499865FCA6E5EC);
lazy_func_t<void(Any p0)> TRACK_OBJECT_VISIBILITY(0xB252BC036B525623);
lazy_func_t<void(Hash hash, int p1)> _0x0BF3B3BD47D79C08(0x0BF3B3BD47D79C08);
lazy_func_t<void(float x, float y, float z, int value, int amount, Hash model)>
	CREATE_MONEY_PICKUPS(0x0589B5E791CE9B2B);
lazy_func_t<void(Object object, BOOL p1)>
	_SET_OBJECT_SOMETHING(0x77F33F2CCF64B3AA);
lazy_func_t<void(Hash doorHash, int limit, BOOL p2, BOOL p3)>
	_SET_DOOR_ACCELERATION_LIMIT(0x6BAB9442830C7F53);
lazy_func_t<int(Hash doorHash)> _0x4BC2854478F3A749(0x4BC2854478F3A749);
lazy_func_t<void(Any p0)> _0x4A39DB43E47CF3AA(0x4A39DB43E47CF3AA);
lazy_func_t<void(Object object)> _0xF9C1681347C8BD15(0xF9C1681347C8BD15);
lazy_func_t<BOOL(Any garage, BOOL p1, int p2)>
	IS_GARAGE_EMPTY(0x90E47239EA1980B8);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2, BOOL p3, BOOL p4)>
	_0x190428512B240692(0x190428512B240692);
lazy_func_t<Vector3(float x, float y, float z, Any p3, Any p4)>
	GET_SAFE_PICKUP_COORDS(0x6E16BC2503FF1FF0);
lazy_func_t<Object(
	float x,
	float y,
	float z,
	float radius,
	Hash modelHash,
	BOOL isMission,
	BOOL p6,
	BOOL p7)>
	GET_CLOSEST_OBJECT_OF_TYPE(0xE143FA2249364369);
lazy_func_t<void(
	Hash doorHash,
	Hash modelHash,
	float x,
	float y,
	float z,
	BOOL p5,
	BOOL p6,
	BOOL p7)>
	ADD_DOOR_TO_SYSTEM(0x6F8838D03D1DC226);
lazy_func_t<int(Hash doorHash)> _0x160AA1B32F6139B8(0x160AA1B32F6139B8);
lazy_func_t<void(Object object, BOOL toggle)>
	_0xB2D0BDE54F0E8E5A(0xB2D0BDE54F0E8E5A);
lazy_func_t<BOOL(Object object)>
	PLACE_OBJECT_ON_GROUND_PROPERLY(0x58A850EAEE20FAA3);
lazy_func_t<void(Ped ped, Any p1)>
	ATTACH_PORTABLE_PICKUP_TO_PED(0x8DC39368BDD57755);
lazy_func_t<
	Any(Any coords,
		float radius,
		Hash modelHash,
		float x,
		float y,
		float z,
		Vector3 *p6,
		int p7)>
	_0x163F8B586BC95F2A(0x163F8B586BC95F2A);
lazy_func_t<BOOL(Any p0, Entity entity, int p2)>
	_0xF0EED5A6BC7B237A(0xF0EED5A6BC7B237A);
lazy_func_t<void(Any p0, BOOL p1)> _0xBCE595371A5FBAAF(0xBCE595371A5FBAAF);
lazy_func_t<void(Player player, Hash pickupHash, BOOL p2)>
	_0x616093EC6B139DD9(0x616093EC6B139DD9);
lazy_func_t<
	void(Hash type, float x, float y, float z, BOOL *locked, float *heading)>
	GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(0xEDC1A5B84AEF33FF);
lazy_func_t<void(BOOL p0)> _0x31F924B53EADDF65(0x31F924B53EADDF65);
lazy_func_t<void(Object object, int paintIndex)>
	_SET_OBJECT_TEXTURE_VARIANT(0x971DA0055324D033);
lazy_func_t<float(Any p0, BOOL p1)>
	GET_OBJECT_FRAGMENT_DAMAGE_HEALTH(0xB6FBFD079B8D0596);
lazy_func_t<void(Any p0, Any p1)> _0xF92099527DB8E2A7(0xF92099527DB8E2A7);
lazy_func_t<BOOL(Any p0, BOOL p1, BOOL p2, BOOL p3, Any p4)>
	_0x673ED815D6E323B7(0x673ED815D6E323B7);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	SET_FORCE_OBJECT_THIS_FRAME(0xF538081986E49E9D);
lazy_func_t<void(Any p0, float p1, BOOL p2)>
	_0xA08FE5E49BDC39DD(0xA08FE5E49BDC39DD);
lazy_func_t<Hash(Pickup pickupHash)>
	_GET_WEAPON_HASH_FROM_PICKUP(0x08F96CA6C551AD51);
lazy_func_t<void(Hash doorHash)> REMOVE_DOOR_FROM_SYSTEM(0x464D8E1427156FE4);
lazy_func_t<void(Hash p0, BOOL p1)> _0x88EAEC617CD26926(0x88EAEC617CD26926);
lazy_func_t<void(float p0)> _0x318516E02DE3ECE2(0x318516E02DE3ECE2);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	float p9,
	BOOL p10,
	BOOL p11)>
	IS_POINT_IN_ANGLED_AREA(0x2A70BAE8883E4C81);
lazy_func_t<void(int handle, int state)>
	_SET_DES_OBJECT_STATE(0x5C29F698D404C5E1);
lazy_func_t<void(Hash pickupHash)>
	REMOVE_ALL_PICKUPS_OF_TYPE(0x27F9D613092159CF);
lazy_func_t<void(Object object, BOOL toggle)>
	SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(0x406137F8EF90EAF5);
lazy_func_t<void(Hash doorHash, float ajar, BOOL p2, BOOL p3)>
	_SET_DOOR_AJAR_ANGLE(0xB6E6FBA95C7324AC);
lazy_func_t<Any(int handle)> _GET_DES_OBJECT_STATE(0x899BA936634A322E);
lazy_func_t<BOOL(Object pickupObject)>
	DOES_PICKUP_OBJECT_EXIST(0xD9EFB6DBF7DAAEA3);
lazy_func_t<BOOL(Any p0)> _0x0378C08504160D0D(0x0378C08504160D0D);
lazy_func_t<BOOL(float x, float y, float z, float radius, Hash hash, BOOL p5)>
	DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(0xBFA48E2FF417213F);
lazy_func_t<Any(Any p0)> _0xDB41D07A45A6D4B7(0xDB41D07A45A6D4B7);
lazy_func_t<Any(Object object, BOOL targettable)>
	SET_OBJECT_TARGETTABLE(0x8A7391690F5AFD81);
lazy_func_t<void(
	Hash doorHash,
	float x,
	float y,
	float z,
	BOOL locked,
	float xRotMult,
	float yRotMult,
	float zRotMult)>
	_DOOR_CONTROL(0x9B12F9A24FABEDB0);
lazy_func_t<BOOL(Any p0, Entity entity, float p2, int p3)>
	_0x372EF6699146A1E4(0x372EF6699146A1E4);
lazy_func_t<void(Ped ped)> DETACH_PORTABLE_PICKUP_FROM_PED(0xCF463D1E9A0AECB1);
lazy_func_t<BOOL(Object object)> HAS_OBJECT_BEEN_BROKEN(0x8ABFB70C49CC43E2);
lazy_func_t<void(Object object, BOOL toggle)>
	_0x4D89D607CB3DD1D2(0x4D89D607CB3DD1D2);
lazy_func_t<BOOL(Hash pickupHash, float x, float y, float z, float radius)>
	_IS_PICKUP_WITHIN_RADIUS(0xF9C36251F6E48E33);
}} // namespace OBJECT::
namespace DECISIONEVENT { namespace {
lazy_func_t<void(BOOL p0)> REMOVE_ALL_SHOCKING_EVENTS(0xEAABE8FDFA21274C);
lazy_func_t<void(int type)>
	SUPPRESS_SHOCKING_EVENT_TYPE_NEXT_FRAME(0x3FD2EC8BF1F1CF30);
lazy_func_t<void(Hash name, int type)>
	CLEAR_DECISION_MAKER_EVENT_RESPONSE(0x4FC9381A7AEE8968);
lazy_func_t<BOOL(ScrHandle event)> REMOVE_SHOCKING_EVENT(0x2CDA538C44C6CCE5);
lazy_func_t<void(Hash name, int type)>
	UNBLOCK_DECISION_MAKER_EVENT(0xD7CD9CF34F2C99E8);
lazy_func_t<ScrHandle(int type, float x, float y, float z, float duration)>
	ADD_SHOCKING_EVENT_AT_POSITION(0xD9F8455409B525E9);
lazy_func_t<ScrHandle(int type, Entity entity, float duration)>
	ADD_SHOCKING_EVENT_FOR_ENTITY(0x7FD8F3BE76F89422);
lazy_func_t<BOOL(int type, float x, float y, float z, float radius)>
	IS_SHOCKING_EVENT_IN_SPHERE(0x1374ABB7C15BAB92);
lazy_func_t<void()>
	REMOVE_SHOCKING_EVENT_SPAWN_BLOCKING_AREAS(0x340F1415B68AEADE);
lazy_func_t<void()> SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME(0x2F9A292AD0A3BD89);
lazy_func_t<void(Ped ped, Hash name)> SET_DECISION_MAKER(0xB604A2942ADED0EE);
lazy_func_t<void(Hash name, int type)>
	BLOCK_DECISION_MAKER_EVENT(0xE42FCDFD0E4196F7);
lazy_func_t<void()> SUPPRESS_AGITATION_EVENTS_NEXT_FRAME(0x5F3B7749C112D552);
}} // namespace DECISIONEVENT::
namespace NETWORKCASH { namespace {
lazy_func_t<void(int amount)>
	_NETWORK_EARN_FROM_GANG_PICKUP(0xA03D4ACE0A3284CE);
lazy_func_t<void(int amount, BOOL p1, BOOL p2)>
	NETWORK_SPENT_TAXI(0x17C3A7D31EAE39F9);
lazy_func_t<void(int value, int *p1, BOOL p2, BOOL p3)>
	NETWORK_PAY_MATCH_ENTRY_FEE(0x9346E14F2AF74D46);
lazy_func_t<void(int cost, BOOL p1, BOOL p2)>
	NETWORK_BUY_HELI_STRIKE(0x81AA4610E3FD3A69);
lazy_func_t<int()> NETWORK_GET_VC_BANK_BALANCE(0x76EF28DA05EA395A);
lazy_func_t<void(int amount, const char *p1)>
	NETWORK_EARN_FROM_JOB(0xB2CC4836834E8A98);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_TELESCOPE(0x7FE61782AD94CC09);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_BUY_PASSIVE_MODE(0x6D3A430D1A809179);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_NO_COPS(0xD5BB406F4E04019F);
lazy_func_t<void(Any p0, Any *p1, Any *p2)>
	_NETWORK_EARN_FROM_JOB_BONUS(0x6816FB4416760775);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_PROSTITUTES(0xB21B89501CFAC79E);
lazy_func_t<int(int character)>
	NETWORK_GET_VC_WALLET_BALANCE(0xA40F9C2623F6A8B5);
lazy_func_t<void(int characterIndex, BOOL p1, BOOL p2)>
	NETWORK_DELETE_CHARACTER(0x05A50AF38947EB8D);
lazy_func_t<Any()> _0x1C2473301B1C66BA(0x1C2473301B1C66BA);
lazy_func_t<void(int amount, const char *heistHash)>
	NETWORK_EARN_FROM_MISSION_H(0x61326EE6DF15B0CA);
lazy_func_t<void(Any p0, Any p1)>
	NETWORK_EARN_FROM_IMPORT_EXPORT(0xF92A014A634442D6);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_HIRE_MERCENARY(0xE7B80E2BF9D80BD6);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_BOUNTY(0x29B260B84947DFCC);
lazy_func_t<BOOL(Any p0, Any p1)> _0xDC18531D7019A535(0xDC18531D7019A535);
lazy_func_t<void(int amount, int *networkHandle)>
	NETWORK_GIVE_PLAYER_JOBSHARE_CASH(0xFB18DF9CB95E0105);
lazy_func_t<BOOL(Any p0, BOOL p1, BOOL p2)>
	NETWORK_MONEY_CAN_BET(0x81404F3DC124FE5B);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_BULL_SHARK(0xA6DD8458CE24012C);
lazy_func_t<void(int amount, BOOL p1, BOOL p2)>
	NETWORK_SPENT_ROBBED_BY_MUGGER(0x995A65F15F581359);
lazy_func_t<void(Any p0, Any p1, BOOL p2, BOOL p3)>
	NETWORK_SPENT_CINEMA(0x6B38ECB05A63A685);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_REQUEST_JOB(0x8204DA7934DF3155);
lazy_func_t<void(float propertyCost, Hash propertyName, BOOL p2, BOOL p3)>
	NETWORK_BUY_PROPERTY(0x650A08A280870AF6);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_BOAT_PICKUP(0x524EE43A37232C00);
lazy_func_t<BOOL(Any p0)> _0xE154B48B68EF72BC(0xE154B48B68EF72BC);
lazy_func_t<float *(Any p0)> _0x6FCF8DDEA146C45B(0x6FCF8DDEA146C45B);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_HELI_PICKUP(0x7BF1D73DB2ECA492);
lazy_func_t<void(Any p0, Any *p1, BOOL p2, BOOL p3)>
	NETWORK_SPENT_BUY_WANTEDLEVEL(0xE1B13771A843C4F6);
lazy_func_t<void(int value, int *networkHandle)>
	NETWORK_RECEIVE_PLAYER_JOBSHARE_CASH(0x56A3B51944C50598);
lazy_func_t<void(int amount)> NETWORK_EARN_FROM_HOLDUPS(0x45B8154E077D9E4D);
lazy_func_t<void(Any p0, Any p1)>
	NETWORK_EARN_FROM_AI_TARGET_KILL(0x515B4A22E4D3C6D7);
lazy_func_t<
	void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7)>
	NETWORK_EARN_FROM_VEHICLE(0xB539BD8A4C1EECF8);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_PAY_UTILITY_BILL(0xAFE08B35EC0C9EAE);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_AMMO_DROP(0xB162DC95C0A3317B);
lazy_func_t<Any(Any p0)> _0xF70EFA14FE091429(0xF70EFA14FE091429);
lazy_func_t<void(int amount)> NETWORK_EARN_FROM_ROCKSTAR(0x02CE1D6AC0FC73EA);
lazy_func_t<void(int cost, BOOL p1, BOOL p2)>
	NETWORK_BUY_AIRSTRIKE(0x763B4BD305338F19);
lazy_func_t<void(
	int amount,
	Hash vehicleModel,
	int *networkHandle,
	BOOL notBankrupt,
	BOOL hasTheMoney)>
	NETWORK_SPENT_PAY_VEHICLE_INSURANCE_PREMIUM(0x9FF28D88C766E3E8);
lazy_func_t<void(Any p0, Any p1, BOOL p2, BOOL p3)>
	NETWORK_SPENT_PLAYER_HEALTHCARE(0x7C99101F7FCE2EE5);
lazy_func_t<void(
	Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6, Any p7, Any p8)>
	NETWORK_EARN_FROM_PERSONAL_VEHICLE(0x3F4D00167E41E0AD);
lazy_func_t<void(Any p0, BOOL p1, Any p2, BOOL p3)>
	NETWORK_SPENT_IN_STRIPCLUB(0xEE99784E4467689C);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_HOLDUPS(0xD9B86B9872039763);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	_NETWORK_SPENT_REQUEST_HEIST(0x9D26502BB97BFE62);
lazy_func_t<BOOL(Any p0)> NETWORK_CAN_BET(0x3A54E33660DED67F);
lazy_func_t<void(int amount, int *networkHandle, Any *p2, Any p3)>
	NETWORK_EARN_FROM_BOUNTY(0x131BB5DA15453ACF);
lazy_func_t<void(int amount, Hash propertyName)>
	NETWORK_EARN_FROM_PROPERTY(0x849648349D77F5C5);
lazy_func_t<void(int p0, const char *p1, int p2)>
	_NETWORK_EARN_FROM_DAILY_OBJECTIVE(0x6EA318C91C1A8786);
lazy_func_t<void(Any p0, Any p1, Any *p2, BOOL p3, BOOL p4)>
	NETWORK_SPENT_BETTING(0x1C436FD11FFA692F);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_BUY_REVEAL_PLAYERS(0x6E176F1B18BC0637);
lazy_func_t<const char *()>
	_NETWORK_GET_BANK_BALANCE_STRING(0xA6FA3979BED01B81);
lazy_func_t<void(Any p0)> NETWORK_CLEAR_CHARACTER_WALLET(0xA921DED15FDF28F5);
lazy_func_t<Any(int amount)> NETWORK_EARN_FROM_PICKUP(0xED1517D3AF17C698);
lazy_func_t<void(int amount)>
	_NETWORK_EARN_FROM_ARMOUR_TRUCK(0xF514621E8EA463D0);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_ARREST_BAIL(0x812F5488B1B2A299);
lazy_func_t<const char *(int *p0, int *p1, const char *p2)>
	PROCESS_CASH_GIFT(0x20194D48EAEC9A41);
lazy_func_t<void(int amountSpent, Any p1, BOOL p2, BOOL p3)>
	NETWORK_BUY_FAIRGROUND_RIDE(0x8A7B3952DD64D2B5);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_PAY_EMPLOYEE_WAGE(0x5FD5ED82CBBE9989);
lazy_func_t<void(int amount, BOOL p1, BOOL p2)>
	NETWORK_SPENT_CASH_DROP(0x289016EC778D60E0);
lazy_func_t<void(int bank, BOOL p1, BOOL p2)>
	NETWORK_SPENT_FROM_ROCKSTAR(0x6A445B64ED7ABEB5);
lazy_func_t<BOOL()> _0x7C4FCCD2E4DEB394(0x7C4FCCD2E4DEB394);
lazy_func_t<BOOL(Any p0, Any p1, Any p2, Any p3)>
	NETWORK_CAN_RECEIVE_PLAYER_CASH(0x5D17BE59D2123284);
lazy_func_t<void(int amount, const char *p1)>
	NETWORK_EARN_FROM_BETTING(0x827A5BA1A44ACA6D);
lazy_func_t<void(Any p0, Any *p1, BOOL p2)>
	NETWORK_EARN_FROM_CHALLENGE_WIN(0x2B171E6B2F64D8DF);
lazy_func_t<void(
	Ped player,
	Hash item,
	Any p2,
	Any p3,
	BOOL p4,
	const char *item_name,
	Any p6,
	Any p7,
	Any p8,
	BOOL p9)>
	NETWORK_BUY_ITEM(0xF0077C797F66A355);
lazy_func_t<void(int cost, BOOL p1, BOOL p2)>
	NETWORK_BUY_HEALTHCARE(0xD9B067E55253E3DD);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_HIRE_MUGGER(0xE404BFB981665BF0);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	NETWORK_SPENT_BUY_OFFTHERADAR(0xA628A745E2275C5D);
lazy_func_t<void(int amount)> NETWORK_EARN_FROM_CRATE_DROP(0xB1CC1B9EC3007A2A);
lazy_func_t<void(int amount)>
	NETWORK_EARN_FROM_NOT_BADSPORT(0x4337511FA8221D36);
lazy_func_t<void(Any p0, Any p1, Any p2, BOOL p3, BOOL p4)>
	NETWORK_SPENT_CARWASH(0xEC03C719DB2F4306);
lazy_func_t<void(Any p0, Any *p1, BOOL p2, BOOL p3)>
	NETWORK_SPENT_CALL_PLAYER(0xACDE7185B374177C);
lazy_func_t<int()> NETWORK_GET_VC_BALANCE(0x5CBAD97E059E1B94);
lazy_func_t<void(int p0, int p1)> NETWORK_INITIALIZE_CASH(0x3DA5ECD1A56CBA6D);
lazy_func_t<void(int amount, Player victim, BOOL p2, BOOL p3)>
	NETWORK_BUY_BOUNTY(0x7B718E197453F2D9);
lazy_func_t<BOOL(Any p0)> _0xE260E0BB9CD995AC(0xE260E0BB9CD995AC);
lazy_func_t<void(int index, const char *context, const char *reason, BOOL unk)>
	NETWORK_REFUND_CASH(0xF9C812CD7C46E817);
lazy_func_t<void(int p0, const char *p1, Any *p2)>
	_NETWORK_EARN_FROM_AMBIENT_JOB(0xFB6DB092FBAE29E6);
lazy_func_t<BOOL(Any p0, BOOL p1, BOOL p2, BOOL p3, Any p4)>
	NETWORK_CAN_SPEND_MONEY(0xAB3CAA6B422164DA);
lazy_func_t<BOOL(Any p0, BOOL p1, BOOL p2, BOOL p3, Any *p4, Any p5)>
	_0x7303E27CC6532080(0x7303E27CC6532080);
}} // namespace NETWORKCASH::
namespace UNK { namespace {
lazy_func_t<void(BOOL p0)> _0xFA1E0E893D915215(0xFA1E0E893D915215);
lazy_func_t<int()> _0xF2CA003F167E21D2(0xF2CA003F167E21D2);
lazy_func_t<void(BOOL p0)> _0xB0C56BD3D808D863(0xB0C56BD3D808D863);
lazy_func_t<void(BOOL p0)> _IS_IN_LOADING_SCREEN(0xFC309E94546FCDB5);
lazy_func_t<BOOL()> _IS_UI_LOADING_MULTIPLAYER(0xC6DC823253FBB366);
lazy_func_t<void(BOOL p0)> _0xC7E7181C09F33B69(0xC7E7181C09F33B69);
lazy_func_t<BOOL()> _0xEF7D17BC6C85264C(0xEF7D17BC6C85264C);
lazy_func_t<Any()> _0x8AA464D4E0F6ACCD(0x8AA464D4E0F6ACCD);
lazy_func_t<int()> _GET_CURRENT_LANGUAGE_ID(0x2BDD44CC428A7EAE);
lazy_func_t<int()> _GET_USER_LANGUAGE_ID(0xA8AE43AEC1A61314);
}} // namespace UNK::
namespace UNK1 { namespace {
lazy_func_t<void(BOOL p0)> _0x48621C9FCA3EBD28(0x48621C9FCA3EBD28);
lazy_func_t<void()> _0xF854439EFBB3B583(0xF854439EFBB3B583);
lazy_func_t<void()> _0xAF66DCEE6609B148(0xAF66DCEE6609B148);
lazy_func_t<Any()> _0xDF4B952F7D381B95(0xDF4B952F7D381B95);
lazy_func_t<void(const char *missionNameLabel, Any p1)>
	_0x208784099002BC30(0x208784099002BC30);
lazy_func_t<void()> _STOP_RECORDING_AND_DISCARD_CLIP(0x88BB3507ED41A240);
lazy_func_t<void(float p0, float p1, BOOL p2)>
	_0x293220DA1B46CEBC(0x293220DA1B46CEBC);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0x66972397E0757E7A(0x66972397E0757E7A);
lazy_func_t<void(int mode)> _START_RECORDING(0xC3AC2FFF9612AC81);
lazy_func_t<BOOL()> _IS_RECORDING(0x1897CA71995A90B4);
lazy_func_t<BOOL(BOOL *p0)> _0x33D47E85B476ABCD(0x33D47E85B476ABCD);
lazy_func_t<Any()> _0x4282E08174868BE3(0x4282E08174868BE3);
lazy_func_t<void()> _0x81CBAE94390F9F89(0x81CBAE94390F9F89);
lazy_func_t<void()> _0x13B350B8AD0EEE10(0x13B350B8AD0EEE10);
lazy_func_t<void()> _0xEB2D525B57F42B40(0xEB2D525B57F42B40);
lazy_func_t<void()> _STOP_RECORDING_AND_SAVE_CLIP(0x071A5197D6AFC8B3);
lazy_func_t<BOOL()> _0x644546EC5287471B(0x644546EC5287471B);
}} // namespace UNK1::
namespace UNK3 { namespace {
lazy_func_t<Any()> _0x3C4487461E9B0DCB(0x3C4487461E9B0DCB);
lazy_func_t<BOOL(Any p0)> _NETWORK_SHOP_START_SESSION(0xA135AC892A58FC07);
lazy_func_t<BOOL(BOOL p0, BOOL p1)> _0x35A1B3E1D1315CFA(0x35A1B3E1D1315CFA);
lazy_func_t<BOOL(Any *p0, Any p1)>
	_NETWORK_SHOP_BASKET_ADD_ITEM(0xF30980718C8ED876);
lazy_func_t<BOOL(int charStatInt, int amount)>
	_NETWORK_TRANSFER_BANK_TO_WALLET(0xD47A2C1BA117471D);
lazy_func_t<BOOL(Any p0)>
	_NETWORK_SHOP_SET_TELEMETRY_NONCE_SEED(0x9507D4271988E1AE);
lazy_func_t<Any()> _0x357B152EF96C30B6(0x357B152EF96C30B6);
lazy_func_t<BOOL(Any *p0)> _0x0395CB47B022E62C(0x0395CB47B022E62C);
lazy_func_t<BOOL(Any *p0)> _0xC13C38E47EA5DF31(0xC13C38E47EA5DF31);
lazy_func_t<Any()> _0x350AA5EBC03D3BD2(0x350AA5EBC03D3BD2);
lazy_func_t<BOOL()> _NETWORK_SHOP_GET_TRANSACTIONS_DISABLED(0x810E8431C0614BF9);
lazy_func_t<Any()> _NETWORK_SHOP_BASKET_IS_FULL(0x27F76CC6C55AD30E);
lazy_func_t<BOOL(
	int *transactionID,
	Hash p1,
	Hash transactionHash,
	int amount,
	Hash p4,
	int mode)>
	_NETWORK_SHOP_BEGIN_SERVICE(0x3C5FD37B5499582E);
lazy_func_t<Any()>
	_NETWORK_SHOP_DELETE_SET_TELEMETRY_NONCE_SEED(0x112CEF1615A1139F);
lazy_func_t<Any()> _0xE3E5A7C64CA2C6ED(0xE3E5A7C64CA2C6ED);
lazy_func_t<BOOL(Any p0)>
	_NETWORK_SHOP_SESSION_APPLY_RECEIVED_DATA(0x2F41D51BA3BCD1F1);
lazy_func_t<BOOL(Any *p0, int p1, int p2, int p3)>
	_NETWORK_SHOP_BASKET_START(0x279F08B1A4B29B7E);
lazy_func_t<BOOL(int transactionID)>
	_NETWORK_SHOP_TERMINATE_SERVICE(0xE2A99A9B524BEFFF);
lazy_func_t<Any()> _0x0A6D923DFFC9BD89(0x0A6D923DFFC9BD89);
lazy_func_t<BOOL(int charStatInt, int amount)>
	_NETWORK_TRANSFER_WALLET_TO_BANK(0xC2F7FE5309181C7D);
lazy_func_t<Any()> _0x23789E777D14CE44(0x23789E777D14CE44);
lazy_func_t<Any()> _0x85F6C9ABA1DE2BCF(0x85F6C9ABA1DE2BCF);
lazy_func_t<BOOL()> _0x72EB7BA9B69BF6AB(0x72EB7BA9B69BF6AB);
lazy_func_t<int(Hash itemHash, Hash hash2, BOOL p2)>
	_NETWORK_SHOP_GET_PRICE(0xC27009422FCCA88D);
lazy_func_t<BOOL(Any *p0)> _0x170910093218C8B9(0x170910093218C8B9);
lazy_func_t<BOOL(int mpChar)>
	_NETWORK_SHOP_GET_TRANSACTIONS_ENABLED_FOR_CHARACTER(0xB24F0944DA203D9E);
lazy_func_t<BOOL()> _NETWORK_SHOP_BASKET_END(0xA65568121DF2EA26);
lazy_func_t<int(int p0)> _0x74A0FD0688F1EE45(0x74A0FD0688F1EE45);
lazy_func_t<BOOL(Any *p0, Any *p1)> _0x897433D292B44130(0x897433D292B44130);
lazy_func_t<BOOL(int transactionID)>
	_NETWORK_SHOP_CHECKOUT_START(0x39BE7CEA8D9CC8E6);
lazy_func_t<BOOL()>
	_NETWORK_SHOP_CASH_TRANSFER_SET_TELEMETRY_NONCE_SEED(0x498C1E05CE5F7877);
lazy_func_t<const char *()> _GET_ONLINE_VERSION(0xFCA9373EF340AC0A);
lazy_func_t<Any()> _0x2B949A1E6AEC8F6A(0x2B949A1E6AEC8F6A);
lazy_func_t<BOOL(Any *p0)> _0xCF38DAFBB49EDE5E(0xCF38DAFBB49EDE5E);
lazy_func_t<BOOL(Any p0, Any *p1)>
	_NETWORK_SHOP_BASKET_APPLY_SERVER_DATA(0xE1A0450ED46A7812);
lazy_func_t<BOOL(Any p0, BOOL p1, Any p2)>
	_0x51F1A8E48C3D2F6D(0x51F1A8E48C3D2F6D);
}} // namespace UNK3::
namespace ENTITY { namespace {
lazy_func_t<float(Entity entity)> GET_ENTITY_ROLL(0x831E0242595560DF);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_STATIC(0x1218E6886D3D8327);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_UPSIDEDOWN(0x1DBD58820FA61D71);
lazy_func_t<float(Entity entity)>
	GET_ENTITY_HEIGHT_ABOVE_GROUND(0x1DD55701034110E5);
lazy_func_t<void(Entity entity, BOOL bCanBeDamaged, int relGroup)>
	SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(0xE22D8FDE858B8119);
lazy_func_t<int(Entity entity)> GET_ENTITY_ALPHA(0x5A47B3B5E63E94C6);
lazy_func_t<BOOL(
	Entity entity,
	float xPos,
	float yPos,
	float zPos,
	float xSize,
	float ySize,
	float zSize,
	BOOL p7,
	BOOL p8,
	int p9)>
	IS_ENTITY_AT_COORD(0x20B60995556D004F);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_INVINCIBLE(0x3882114BDE571AD4);
lazy_func_t<void(Entity entity, BOOL toggle, BOOL unk)>
	SET_ENTITY_VISIBLE(0xEA1C610A04DB6BBB);
lazy_func_t<BOOL(Entity entity)>
	HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(0x605F5A140F202491);
lazy_func_t<float(Entity entity, const char *animDict, const char *animName)>
	GET_ENTITY_ANIM_CURRENT_TIME(0x346D81500D088F42);
lazy_func_t<Vector3(Entity entity, int rotationOrder)>
	GET_ENTITY_ROTATION(0xAFBD61CC738D9EB9);
lazy_func_t<void(Entity entity, int value)>
	SET_ENTITY_LOD_DIST(0x5927F96A78577363);
lazy_func_t<void(Entity entity, int value)>
	SET_ENTITY_MAX_HEALTH(0x166E7CF68597D8B5);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_ON_SCREEN(0xE659E47AF827484B);
lazy_func_t<BOOL(
	Entity entity,
	const char *animName,
	const char *animDict,
	float p3,
	BOOL loop,
	BOOL stayInAnim,
	BOOL p6,
	float delta,
	Any bitset)>
	PLAY_ENTITY_ANIM(0x7FB218262B810701);
lazy_func_t<void(Entity entity, float speed)>
	SET_ENTITY_MAX_SPEED(0x0E46A3FCBDE2A1B1);
lazy_func_t<Ped(Entity entity)>
	GET_PED_INDEX_FROM_ENTITY_INDEX(0x04A2A40C73395041);
lazy_func_t<void(Entity entity, BOOL p1)>
	_0x694E00132F2823ED(0x694E00132F2823ED);
lazy_func_t<void(Entity entity, BOOL p1)>
	_0xDC6F8601FAF2E893(0xDC6F8601FAF2E893);
lazy_func_t<void(
	Entity entity,
	int forceFlags,
	float x,
	float y,
	float z,
	float offX,
	float offY,
	float offZ,
	int boneIndex,
	BOOL isDirectionRel,
	BOOL ignoreUpVec,
	BOOL isForceRel,
	BOOL p12,
	BOOL p13)>
	APPLY_FORCE_TO_ENTITY(0xC5F68BE9613E2D18);
lazy_func_t<float(Entity entity)> GET_ENTITY_FORWARD_X(0x8BB4EF4214E0E6D5);
lazy_func_t<float(Entity entity)> GET_ENTITY_SPEED(0xD5037BA82E12416F);
lazy_func_t<Object(Entity entity)>
	GET_OBJECT_INDEX_FROM_ENTITY_INDEX(0xD7E3B9735C0F89D6);
lazy_func_t<Player(Entity entity, int team)>
	GET_NEAREST_PLAYER_TO_ENTITY_ON_TEAM(0x4DC9A62F844D9337);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_RECORDS_COLLISIONS(0x0A50A1EEDAD01E65);
lazy_func_t<BOOL(Hash entityModelHash, float x, float y, float z, BOOL p4)>
	WOULD_ENTITY_BE_OCCLUDED(0xEE5D2A122E09EC42);
lazy_func_t<BOOL(Entity entity)>
	IS_ENTITY_WAITING_FOR_WORLD_COLLISION(0xD05BFF0C0A12C68F);
lazy_func_t<void(Ped *ped)> SET_PED_AS_NO_LONGER_NEEDED(0x2595DD4236549CE3);
lazy_func_t<void(Vehicle *vehicle)>
	SET_VEHICLE_AS_NO_LONGER_NEEDED(0x629BFA74418D6239);
lazy_func_t<void(float x, float y, float z, float radius, Hash model, BOOL p5)>
	CREATE_MODEL_HIDE(0x8A97BCA30A0CE478);
lazy_func_t<Hash(Entity entity)>
	GET_LAST_MATERIAL_HIT_BY_ENTITY(0x5C3D0A935F535C4C);
lazy_func_t<float(const char *animDict, const char *animName)>
	_GET_ANIM_DURATION(0xFEDDF04D62B8D790);
lazy_func_t<float(Entity entity)>
	_GET_ENTITY_PHYSICS_HEADING(0x846BF6291198A71E);
lazy_func_t<int(Entity entity)> GET_ENTITY_HEALTH(0xEEF059FAD016D209);
lazy_func_t<Vector3(Entity entity, int boneIndex)>
	GET_WORLD_POSITION_OF_ENTITY_BONE(0x44A8FCB8ED227738);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_DEAD(0x5F9532F3B5CC2551);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_HAS_GRAVITY(0x4A4722448F18EEF5);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_A_MISSION_ENTITY(0x0A7B270912999B3C);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_CAN_BE_DAMAGED(0x1760FFA8AB074D66);
lazy_func_t<void(Entity entity, float heading)>
	SET_ENTITY_HEADING(0x8E2530AA8ADA980E);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_ALWAYS_PRERENDER(0xACAD101E1FB66689);
lazy_func_t<BOOL(Entity entity)>
	HAS_ENTITY_BEEN_DAMAGED_BY_ANY_OBJECT(0x95EB9964FF5C5C65);
lazy_func_t<Entity(Entity entity)> GET_ENTITY_ATTACHED_TO(0x48C2BED9180FE123);
lazy_func_t<float(Entity entity)> GET_ENTITY_FORWARD_Y(0x866A4A5FAE349510);
lazy_func_t<Vehicle(Entity entity)>
	GET_VEHICLE_INDEX_FROM_ENTITY_INDEX(0x4B53F92932ADFAC0);
lazy_func_t<void(Entity entity, int alphaLevel, int skin)>
	SET_ENTITY_ALPHA(0x44A0870B7E92D7C0);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_MOTION_BLUR(0x295D82A8559F9150);
lazy_func_t<void(
	Entity entity,
	Vector3 *rightVector,
	Vector3 *forwardVector,
	Vector3 *upVector,
	Vector3 *position)>
	GET_ENTITY_MATRIX(0xECB2FC7235A7D137);
lazy_func_t<Any(Entity entity)>
	CLEAR_ENTITY_LAST_DAMAGE_ENTITY(0xA72CD9CA74A5ECBA);
lazy_func_t<void(Entity entity, BOOL p1, BOOL collision)>
	DETACH_ENTITY(0x961AC54BF0613F5D);
lazy_func_t<void(
	Entity entity,
	float xPos,
	float yPos,
	float zPos,
	BOOL xAxis,
	BOOL yAxis,
	BOOL zAxis)>
	SET_ENTITY_COORDS_NO_OFFSET(0x239A3351AC1DA385);
lazy_func_t<void(Entity entity)> _0x78E8E3A640178255(0x78E8E3A640178255);
lazy_func_t<BOOL(Entity entity)>
	HAS_ENTITY_COLLIDED_WITH_ANYTHING(0x8BAD02F0368D9E14);
lazy_func_t<Vector3(Entity entity)>
	GET_ENTITY_FORWARD_VECTOR(0x0A794A5A57F8DF91);
lazy_func_t<void(
	Entity entity,
	float xPos,
	float yPos,
	float zPos,
	BOOL xAxis,
	BOOL yAxis,
	BOOL zAxis,
	BOOL clearArea)>
	SET_ENTITY_COORDS(0x06843DA7060A026B);
lazy_func_t<void(Entity entity, float x, float y, float z, float w)>
	SET_ENTITY_QUATERNION(0x77B21BE7AC540F07);
lazy_func_t<BOOL(Entity entity1, Entity entity2)>
	HAS_ENTITY_CLEAR_LOS_TO_ENTITY_IN_FRONT(0x0267D00AF114F17A);
lazy_func_t<int(Entity entity)> GET_ENTITY_LOD_DIST(0x4159C2762B5791D6);
lazy_func_t<void(Entity entity, float p1)>
	_0x5C3B791D580E0BC2(0x5C3B791D580E0BC2);
lazy_func_t<void(
	Entity entity1,
	Entity entity2,
	int boneIndex,
	float xPos,
	float yPos,
	float zPos,
	float xRot,
	float yRot,
	float zRot,
	BOOL p9,
	BOOL useSoftPinning,
	BOOL collision,
	BOOL isPed,
	int vertexIndex,
	BOOL fixedRot)>
	ATTACH_ENTITY_TO_ENTITY(0x6B9BBD38AB0796DF);
lazy_func_t<BOOL(Entity entity, float p1, BOOL p2)>
	STOP_SYNCHRONIZED_ENTITY_ANIM(0x43D3807C077261E3);
lazy_func_t<void(
	Entity entity,
	BOOL bulletProof,
	BOOL fireProof,
	BOOL explosionProof,
	BOOL collisionProof,
	BOOL meleeProof,
	BOOL p6,
	BOOL p7,
	BOOL p8)>
	SET_ENTITY_PROOFS(0xFAEE099C6F890BB8);
lazy_func_t<void(
	float x,
	float y,
	float z,
	float radius,
	Hash originalModel,
	Hash newModel,
	BOOL p6)>
	REMOVE_MODEL_SWAP(0x033C0F9A64E229AE);
lazy_func_t<BOOL(Object entity)> DOES_ENTITY_EXIST(0x7239B21A38F536BA);
lazy_func_t<float(Entity entity)> GET_ENTITY_PITCH(0xD45DC2893621E1FE);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_A_VEHICLE(0x6AC7003FA6E5575E);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_IN_AIR(0x886E37EC497200B6);
lazy_func_t<BOOL(
	const char *animDictionary,
	const char *animName,
	const char *p2,
	Any *p3,
	Any *p4)>
	FIND_ANIM_EVENT_PHASE(0x07F1BE2BCCAA27A7);
lazy_func_t<Hash(Entity entity)> GET_ENTITY_MODEL(0x9F47B058362C84B5);
lazy_func_t<BOOL(
	Entity entity,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	BOOL p7,
	BOOL p8,
	Any p9)>
	IS_ENTITY_IN_AREA(0x54736AA40E271165);
lazy_func_t<float(Entity entity)>
	GET_ENTITY_SUBMERGED_LEVEL(0xE81AFC1BC4CC41CE);
lazy_func_t<BOOL(Entity entity, Hash actionHash)>
	HAS_ANIM_EVENT_FIRED(0xEAF4CD9EA3E7E922);
lazy_func_t<const char *(Entity entity, ScrHandle *script)>
	GET_ENTITY_SCRIPT(0xA6E9C38DB51D7748);
lazy_func_t<void(
	Entity entity,
	float pitch,
	float roll,
	float yaw,
	int rotationOrder,
	BOOL p5)>
	SET_ENTITY_ROTATION(0x8524A8B0171D5E07);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	REMOVE_FORCED_OBJECT(0x61B6775E83C0DB6F);
lazy_func_t<void(Entity entity, BOOL p1)>
	_0x2C2E3DC128F44309(0x2C2E3DC128F44309);
lazy_func_t<float(Entity entity)> GET_ENTITY_HEADING(0xE83D4F9BA2A38914);
lazy_func_t<void(
	Entity entity,
	const char *animDictionary,
	const char *animName,
	float time)>
	SET_ENTITY_ANIM_CURRENT_TIME(0x4487C259F0F70977);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_RENDER_SCORCHED(0x730F5F8D3F0F2050);
lazy_func_t<void(float x, float y, float z, float radius, Hash model, BOOL p5)>
	CREATE_MODEL_HIDE_EXCLUDING_SCRIPT_OBJECTS(0x3A52AE588830BF7F);
lazy_func_t<Vector3(Entity entity, BOOL relative)>
	GET_ENTITY_SPEED_VECTOR(0x9A8D700A51CB7B0D);
lazy_func_t<void(Entity *entity)> DELETE_ENTITY(0xAE3CBE5BF394C9C9);
lazy_func_t<void(Entity entity, int state)>
	SET_ENTITY_TRAFFICLIGHT_OVERRIDE(0x57C5DB656185EAC4);
lazy_func_t<
	BOOL(Entity entity, const char *animDict, const char *animName, int p3)>
	HAS_ENTITY_ANIM_FINISHED(0x20B711662962B472);
lazy_func_t<void(Entity entity, BOOL toggle, BOOL keepPhysics)>
	SET_ENTITY_COLLISION(0x1A9205C1B9EE827F);
lazy_func_t<BOOL(Entity entity)>
	_GET_ENTITY_COLLISON_DISABLED(0xCCF1E97BEFDAE480);
lazy_func_t<void(
	Entity entity,
	float xPos,
	float yPos,
	float zPos,
	BOOL xAxis,
	BOOL yAxis,
	BOOL zAxis,
	BOOL clearArea)>
	_SET_ENTITY_COORDS_2(0x621873ECE1178967);
lazy_func_t<void(float x, float y, float z, Any p3, Hash modelHash, BOOL p5)>
	CREATE_FORCED_OBJECT(0x150E808B375A385A);
lazy_func_t<void(Entity entity, BOOL p1)>
	_0xE12ABE5E3A389A6C(0xE12ABE5E3A389A6C);
lazy_func_t<BOOL(Entity entity)> DOES_ENTITY_HAVE_PHYSICS(0xDA95EA3317CC5064);
lazy_func_t<Vector3(Entity entity, float posX, float posY, float posZ)>
	GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(0x2274BC1C4885E333);
lazy_func_t<BOOL(
	Entity entity1,
	Entity entity2,
	float xSize,
	float ySize,
	float zSize,
	BOOL p5,
	BOOL p6,
	int p7)>
	IS_ENTITY_AT_ENTITY(0x751B70C3D034E187);
lazy_func_t<BOOL(Entity entity, Hash modelHash)>
	IS_ENTITY_TOUCHING_MODEL(0x0F42323798A58C8C);
lazy_func_t<float(Entity entity, const char *animDict, const char *animName)>
	GET_ENTITY_ANIM_TOTAL_TIME(0x50BD2730B191E360);
lazy_func_t<void(
	float x,
	float y,
	float z,
	float radius,
	Hash originalModel,
	Hash newModel,
	BOOL p6)>
	CREATE_MODEL_SWAP(0x92C47782FDA8B2A3);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_LIGHTS(0x7CFBA6A80BDF3874);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_LOAD_COLLISION_FLAG(0x0DC7CABAB1E9B67E);
lazy_func_t<void(Entity entity, BOOL p1)>
	_0xA80AE305E0A3044F(0xA80AE305E0A3044F);
lazy_func_t<BOOL(
	Entity entity,
	float originX,
	float originY,
	float originZ,
	float edgeX,
	float edgeY,
	float edgeZ,
	float angle,
	BOOL p8,
	BOOL p9,
	Any p10)>
	IS_ENTITY_IN_ANGLED_AREA(0x51210CED3DA1C78A);
lazy_func_t<void(Entity entity, BOOL toggle)>
	_SET_ENTITY_SOMETHING(0x3910051CCECDB00C);
lazy_func_t<BOOL(
	Entity entity,
	int syncedScene,
	const char *animation,
	const char *propName,
	float p4,
	float p5,
	Any p6,
	float p7)>
	PLAY_SYNCHRONIZED_ENTITY_ANIM(0xC77720A12FE14A86);
lazy_func_t<void(Entity entity, BOOL p1, float p2)>
	SET_ENTITY_IS_TARGET_PRIORITY(0xEA02E132F5C68722);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_ONLY_DAMAGED_BY_PLAYER(0x79F020FF9EDC0748);
lazy_func_t<BOOL(Entity entity1, Entity entity2, BOOL p2)>
	HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(0xC86D67D52A707CF8);
lazy_func_t<Vector3(Entity entity, float offsetX, float offsetY, float offsetZ)>
	GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(0x1899F328B0E12848);
lazy_func_t<
	Any(Entity entity, const char *animation, const char *animGroup, float p3)>
	STOP_ENTITY_ANIM(0x28004F88151E03E0);
lazy_func_t<void(
	Entity entity,
	const char *animDictionary,
	const char *animName,
	float speedMultiplier)>
	SET_ENTITY_ANIM_SPEED(0x28D1A16553C51776);
lazy_func_t<void(Entity entity)>
	FORCE_ENTITY_AI_AND_ANIMATION_UPDATE(0x40FDEDB72F8293B2);
lazy_func_t<Any(Entity entity)> RESET_ENTITY_ALPHA(0x9B1E824FFBB7027A);
lazy_func_t<void(Entity entity, BOOL p1)>
	_0x1A092BB0C3808B96(0x1A092BB0C3808B96);
lazy_func_t<void(Entity entity, int health)>
	SET_ENTITY_HEALTH(0x6B76DC1F3AE6E6A3);
lazy_func_t<BOOL(Entity entity)>
	HAS_COLLISION_LOADED_AROUND_ENTITY(0xE9676F61BC0B3321);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	REMOVE_MODEL_HIDE(0xD9E3006FB3CBD765);
lazy_func_t<Vector3(Entity entity)> GET_ENTITY_VELOCITY(0x4805D2B1D8CF94A9);
lazy_func_t<BOOL(Entity entity)>
	IS_ENTITY_VISIBLE_TO_SCRIPT(0xD796CB5BA8F20E32);
lazy_func_t<void(Entity entity)> PROCESS_ENTITY_ATTACHMENTS(0xF4080490ADC51C6F);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_DYNAMIC(0x1718DE8E3F2823CA);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_VISIBLE(0x47D6F43D77935C75);
lazy_func_t<void(Entity entity, BOOL p1, Hash relationshipHash)>
	SET_ENTITY_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(0x7022BD828FA0B082);
lazy_func_t<BOOL(Entity entity1, Entity entity2, int traceType)>
	HAS_ENTITY_CLEAR_LOS_TO_ENTITY(0xFCDFF7B72D23A1AC);
lazy_func_t<int(Entity entity)> GET_ENTITY_MAX_HEALTH(0x15D757606D170C3C);
lazy_func_t<int(Entity entity)> GET_ENTITY_TYPE(0x8ACD366038D14505);
lazy_func_t<BOOL(
	Entity entity, const char *animDict, const char *animName, int taskFlag)>
	IS_ENTITY_PLAYING_ANIM(0x1F0B79228E461EC9);
lazy_func_t<void(Entity entity, float x, float y, float z)>
	SET_ENTITY_VELOCITY(0x1C99BB7B6E96D16F);
lazy_func_t<void(Entity entity, float *x, float *y, float *z, float *w)>
	GET_ENTITY_QUATERNION(0x7B3703D2D32DFA18);
lazy_func_t<int(Entity entity)> _GET_ENTITY_POPULATION_TYPE(0xF6F5161F4534EDFF);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_A_PED(0x524AC5ECEA15343E);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_CAN_BE_TARGETED_WITHOUT_LOS(0xD3997889736FD899);
lazy_func_t<BOOL(Entity entity)>
	IS_ENTITY_ATTACHED_TO_ANY_OBJECT(0xCF511840CEEDE0CC);
lazy_func_t<BOOL(Entity entity)>
	IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(0x26AA915AD89BFB4B);
lazy_func_t<BOOL(Entity entity, Entity targetEntity)>
	IS_ENTITY_TOUCHING_ENTITY(0x17FFC1B2BA35A494);
lazy_func_t<void(
	Entity entity,
	int forceType,
	float x,
	float y,
	float z,
	BOOL p5,
	BOOL isDirectionRel,
	BOOL isForceRel,
	BOOL p8)>
	APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(0x18FF00FC7EFF559E);
lazy_func_t<BOOL(Entity entity)> DOES_ENTITY_HAVE_DRAWABLE(0x060D6E96F8B8E48D);
lazy_func_t<BOOL(Entity entity)>
	HAS_ENTITY_BEEN_DAMAGED_BY_ANY_VEHICLE(0xDFD5033FDBA0A9C8);
lazy_func_t<Player(Entity entity)>
	GET_NEAREST_PLAYER_TO_ENTITY(0x7196842CB375CDB3);
lazy_func_t<BOOL(int handle)> IS_AN_ENTITY(0x731EC8A916BD11A1);
lazy_func_t<void(Entity entity, BOOL toggle)>
	FREEZE_ENTITY_POSITION(0x428CA6DBD1094446);
lazy_func_t<BOOL(float p0, float p1, float p2, float p3, Any p4, float p5)>
	STOP_SYNCHRONIZED_MAP_ENTITY_ANIM(0x11E79CAB7183B6F5);
lazy_func_t<void(Entity entity, BOOL p1, BOOL p2)>
	SET_ENTITY_AS_MISSION_ENTITY(0xAD738C3085FE7E11);
lazy_func_t<int(Entity entity, const char *boneName)>
	GET_ENTITY_BONE_INDEX_BY_NAME(0xFB71170B7E76ACBA);
lazy_func_t<void(Object *object)>
	SET_OBJECT_AS_NO_LONGER_NEEDED(0x3AE22DEB5BA5A3E6);
lazy_func_t<float(
	Entity entity, float X, float Y, float Z, BOOL atTop, BOOL inWorldCoords)>
	GET_ENTITY_HEIGHT(0x5A504562485944DD);
lazy_func_t<BOOL(Entity entity, const char *zone)>
	IS_ENTITY_IN_ZONE(0xB6463CF6AF527071);
lazy_func_t<BOOL(Entity entity, float angle)>
	IS_ENTITY_UPRIGHT(0x5333F526F6AB19AA);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_OCCLUDED(0xE31C2C72B8692B64);
lazy_func_t<void(Entity entity, BOOL p1, BOOL p2)>
	_SET_ENTITY_COLLISION_2(0x9EBC85ED0FFFE51C);
lazy_func_t<void(Entity entity1, Entity entity2, BOOL unknown)>
	SET_ENTITY_NO_COLLISION_ENTITY(0xA53ED5520C07654A);
lazy_func_t<Vector3(Entity entity)>
	GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(0xE465D4AB7CA6AE72);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_AN_OBJECT(0x8D68C8FD0FACA94E);
lazy_func_t<BOOL(Entity entity)>
	IS_ENTITY_ATTACHED_TO_ANY_PED(0xB1632E9A5F988D11);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_IN_WATER(0xCFB0A0D8EDD145A3);
lazy_func_t<BOOL(Entity entity)> IS_ENTITY_ATTACHED(0xB346476EF1A64897);
lazy_func_t<BOOL(Entity from, Entity to)>
	IS_ENTITY_ATTACHED_TO_ENTITY(0xEFBE71898A993728);
lazy_func_t<void(
	Entity entity1,
	Entity entity2,
	int boneIndex1,
	int boneIndex2,
	float xPos1,
	float yPos1,
	float zPos1,
	float xPos2,
	float yPos2,
	float zPos2,
	float xRot,
	float yRot,
	float zRot,
	float breakForce,
	BOOL fixedRot,
	BOOL p15,
	BOOL collision,
	BOOL teleport,
	int p18)>
	ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(0xC3675780C92F90F9);
lazy_func_t<BOOL(
	float p0,
	float p1,
	float p2,
	float p3,
	Any p4,
	Any p5,
	Any *p6,
	Any *p7,
	float p8,
	float p9,
	Any p10,
	float p11)>
	PLAY_SYNCHRONIZED_MAP_ENTITY_ANIM(0xB9C54555ED30FBC4);
lazy_func_t<BOOL(Entity entity, BOOL p2)>
	DOES_ENTITY_BELONG_TO_THIS_SCRIPT(0xDDE6DF5AE89981D2);
lazy_func_t<Vector3(Entity entity, BOOL alive)>
	GET_ENTITY_COORDS(0x3FEF770D40960D5A);
lazy_func_t<Vector3(Entity entity)>
	GET_ENTITY_ROTATION_VELOCITY(0x213B91045D09B983);
lazy_func_t<float(Entity entity)> GET_ENTITY_UPRIGHT_VALUE(0x95EED5A694951F9F);
lazy_func_t<void(Entity *entity)>
	SET_ENTITY_AS_NO_LONGER_NEEDED(0xB736A491E64A32CF);
}} // namespace ENTITY::
namespace AUDIO { namespace {
lazy_func_t<void(BOOL play)> PLAY_END_CREDITS_MUSIC(0xCD536C4D33DCC900);
lazy_func_t<void(Vehicle vehicle, BOOL Toggle)>
	SET_VEHICLE_BOOST_ACTIVE(0x4A04DE7CAB2739A1);
lazy_func_t<Any()> _0x544810ED9DB6BBE6(0x544810ED9DB6BBE6);
lazy_func_t<Any()> _0xC8B1B2425604CDD0(0xC8B1B2425604CDD0);
lazy_func_t<void(Ped ped)> RESET_PED_AUDIO_FLAGS(0xF54BB7B61036F335);
lazy_func_t<BOOL(int soundId)> HAS_SOUND_FINISHED(0xFCBDCE714A7C88E5);
lazy_func_t<void(float p0)> _0x2C96CDB04FCA358E(0x2C96CDB04FCA358E);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_0xC15907D667F7CFB2(0xC15907D667F7CFB2);
lazy_func_t<void()> _0xE4E6DD5566D28C82(0xE4E6DD5566D28C82);
lazy_func_t<Any()> GET_MUSIC_PLAYTIME(0xE7A0D23DC414507B);
lazy_func_t<void(Any *p0, float p1, float p2, float p3)>
	_0xC8EDE9BDBCCBA6D4(0xC8EDE9BDBCCBA6D4);
lazy_func_t<void(const char *p0)> _0xB4BBFD9CD8B3922B(0xB4BBFD9CD8B3922B);
lazy_func_t<void(int p0)> REGISTER_SCRIPT_WITH_AUDIO(0xC6ED9D5092438D91);
lazy_func_t<BOOL(const char *p0, BOOL p1)>
	REQUEST_SCRIPT_AUDIO_BANK(0x2F844A8B08D76685);
lazy_func_t<BOOL()> _0x109697E2FFBAC8A1(0x109697E2FFBAC8A1);
lazy_func_t<void(BOOL p0, BOOL p1)> _0x58BB377BEC7CD5F4(0x58BB377BEC7CD5F4);
lazy_func_t<void(Ped p0, const char *p1, const char *p2)>
	_0x8A694D7A68F8DC38(0x8A694D7A68F8DC38);
lazy_func_t<void(Any p0, BOOL p1)> _0x75773E11BA459E90(0x75773E11BA459E90);
lazy_func_t<void(
	Ped p0,
	const char *speechName,
	const char *voiceName,
	const char *speechParam,
	BOOL p4)>
	_PLAY_AMBIENT_SPEECH_WITH_VOICE(0x3523634255FC3318);
lazy_func_t<void(Any p0, const char *p1, const char *p2)>
	_0xF1F8157B8C3F171C(0xF1F8157B8C3F171C);
lazy_func_t<BOOL(const char *eventName)> CANCEL_MUSIC_EVENT(0x5B17A90291133DA5);
lazy_func_t<void(Vehicle vehicle)> PLAY_STREAM_FROM_VEHICLE(0xB70374A758007DFA);
lazy_func_t<void(BOOL active)> SET_GPS_ACTIVE(0x3BD3F52BA9B1E4E8);
lazy_func_t<void()> CLEAR_ALL_BROKEN_GLASS(0xB32209EFFDC04913);
lazy_func_t<void(const char *audioBank)>
	RELEASE_NAMED_SCRIPT_AUDIO_BANK(0x77ED170667F50170);
lazy_func_t<void(int radioStation)>
	SET_RADIO_TO_STATION_INDEX(0xA619B168B8A8570F);
lazy_func_t<void(const char *p0, float p1)>
	GET_PLAYER_HEADSET_SOUND_ALTERNATE(0xBCC29F935ED07688);
lazy_func_t<void(BOOL p0)> _0x02E93C796ABD3A97(0x02E93C796ABD3A97);
lazy_func_t<void(const char *p0, Entity p1)>
	_SET_SYNCHRONIZED_AUDIO_EVENT_POSITION_THIS_FRAME(0x950A154B8DAB6185);
lazy_func_t<void(int p0)> _0x12561FCBB62D5B9C(0x12561FCBB62D5B9C);
lazy_func_t<void(Ped ped)> _SET_PED_SCREAM(0x40CF0D12D142A9E8);
lazy_func_t<BOOL()> IS_MISSION_COMPLETE_PLAYING(0x19A30C23F5827F8A);
lazy_func_t<void(float p0, float p1)> _0x8BF907833BE275DE(0x8BF907833BE275DE);
lazy_func_t<int()> GET_PLAYER_RADIO_STATION_INDEX(0xE8AF77C4C06ADC93);
lazy_func_t<void(const char *emitterName, BOOL toggle)>
	SET_STATIC_EMITTER_ENABLED(0x399D2D3B33F1B8EB);
lazy_func_t<void(Ped ped, const char *speechName, const char *speechParam)>
	_PLAY_AMBIENT_SPEECH2(0xC6941B4A3A8FBBB9);
lazy_func_t<void(Object object)> PLAY_STREAM_FROM_OBJECT(0xEBAA9B64D76356FD);
lazy_func_t<int()> GET_AUDIBLE_MUSIC_TRACK_TEXT_ID(0x50B196FC9ED6545B);
lazy_func_t<void()> _0x0150B6FF25A9E2E5(0x0150B6FF25A9E2E5);
lazy_func_t<BOOL(Any p0, Any *p1)>
	PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(0x029FE7CD1B7E2E75);
lazy_func_t<void(Ped ped)> STOP_PED_RINGTONE(0x6C5AE23EFA885092);
lazy_func_t<void(const char *p0)> _0xD01005D2BA2EB778(0xD01005D2BA2EB778);
lazy_func_t<void(const char *stationName)>
	SET_RADIO_TO_STATION_NAME(0xC69EDA28699D5107);
lazy_func_t<void(Vehicle vehicle, Any p1)>
	SET_AUDIO_VEHICLE_PRIORITY(0xE5564483E407F914);
lazy_func_t<void(BOOL Toggle)>
	SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(0x1098355A16064BB3);
lazy_func_t<BOOL(const char *streamName, const char *soundSet)>
	LOAD_STREAM(0x1F1F957154EC51DF);
lazy_func_t<BOOL(const char *alarmName)> PREPARE_ALARM(0x9D74AE343DB65533);
lazy_func_t<BOOL(Any p0)> STOP_SYNCHRONIZED_AUDIO_EVENT(0x92D6A88E64A94430);
lazy_func_t<void(Any p0, BOOL p1, Any p2)>
	_0xBF4DC1784BE94DFA(0xBF4DC1784BE94DFA);
lazy_func_t<void(int soundId)> RELEASE_SOUND_ID(0x353FC880830B88FA);
lazy_func_t<void(Ped playerPed, Hash p1)>
	_0x7CDC8C3B89F661B3(0x7CDC8C3B89F661B3);
lazy_func_t<BOOL()> _IS_PLAYER_VEHICLE_RADIO_ENABLED(0x5F43D83FD6738741);
lazy_func_t<void(Any p0, float p1)> _0x9D3AF56E94C9AE98(0x9D3AF56E94C9AE98);
lazy_func_t<Hash(Vehicle vehicle)> GET_VEHICLE_DEFAULT_HORN(0x02165D55000219AC);
lazy_func_t<void(
	const char *p0,
	const char *p1,
	float p2,
	float p3,
	float p4,
	const char *p5)>
	_PLAY_AMBIENT_SPEECH_AT_COORDS(0xED640017ED337E45);
lazy_func_t<void(BOOL toggle)> SET_RADIO_AUTO_UNFREEZE(0xC1AA9F53CE982990);
lazy_func_t<void(const char *radioStation)>
	_0x1654F24A88A8E3FE(0x1654F24A88A8E3FE);
lazy_func_t<BOOL(Vehicle vehicle)> _0x5DB8010EE71FDEF2(0x5DB8010EE71FDEF2);
lazy_func_t<void(const char *radioStation)>
	UNFREEZE_RADIO_STATION(0xFC00454CF60B91DD);
lazy_func_t<void(BOOL toggle)> SET_AGGRESSIVE_HORNS(0x395BF71085D1B1D9);
lazy_func_t<BOOL(const char *eventName)>
	PREPARE_MUSIC_EVENT(0x1E5185B72EF5158A);
lazy_func_t<void(BOOL p0, Any p1)> _0x70B8EC8FC108A634(0x70B8EC8FC108A634);
lazy_func_t<BOOL()> IS_GAME_IN_CONTROL_OF_MUSIC(0x6D28DC1671E334FD);
lazy_func_t<void(Ped playerPed, BOOL disabled)>
	SET_PLAYER_ANGRY(0xEA241BB04110F091);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_RADIO_ENABLED(0x3B988190C0AA6C0B);
lazy_func_t<void()> PLAY_STREAM_FRONTEND(0x58FCE43488F9F5F4);
lazy_func_t<void(int soundId)> STOP_SOUND(0xA3B0C41BA5CC0BB5);
lazy_func_t<BOOL()> IS_RADIO_RETUNING(0xA151A7394A214E65);
lazy_func_t<void(BOOL p0)> _0x0B568201DD99F0EB(0x0B568201DD99F0EB);
lazy_func_t<void(BOOL p0, BOOL p1)>
	START_SCRIPT_PHONE_CONVERSATION(0x252E5F915EABB675);
lazy_func_t<Any(Any p0, Any p1)> HINT_AMBIENT_AUDIO_BANK(0x8F8C0E370AE62F5C);
lazy_func_t<int()> GET_SOUND_ID(0x430386FE9BF80B45);
lazy_func_t<void(const char *ambientZone, BOOL p1, BOOL p2)>
	SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(0xF3638DAE8C4045E1);
lazy_func_t<void()> _0x806058BBDC136E06(0x806058BBDC136E06);
lazy_func_t<void(int pedIndex, Ped ped, const char *name)>
	ADD_PED_TO_CONVERSATION(0x95D9F4BC443956E7);
lazy_func_t<void(const char *name, float p1)>
	_0x733ADF241531E5C2(0x733ADF241531E5C2);
lazy_func_t<void(Ped ped)> _SET_PED_MUTE(0x7A73D05A607734C7);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_RADIO_LOUD(0xBB6F1CAEC68B0BCE);
lazy_func_t<void(Ped ped, BOOL toggle)>
	DISABLE_PED_PAIN_AUDIO(0xA9A41C1E940FB0E8);
lazy_func_t<void(Any p0)> _0xD2DCCD8E16E20997(0xD2DCCD8E16E20997);
lazy_func_t<void(Any p0, float p1, float p2, float p3)>
	_0x33E3C6C6F2F0B506(0x33E3C6C6F2F0B506);
lazy_func_t<void()> SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE(0x9663FE6B7A61EB00);
lazy_func_t<void(const char *p0, const char *soundset)>
	_0xCADA5A0D0702381E(0xCADA5A0D0702381E);
lazy_func_t<BOOL()> IS_MOBILE_PHONE_RADIO_ACTIVE(0xB35CE999E8EF317E);
lazy_func_t<Any()> _0x3A48AB4445D499BE(0x3A48AB4445D499BE);
lazy_func_t<void()> RESTART_SCRIPTED_CONVERSATION(0x9AEB285D1818C9AC);
lazy_func_t<void()> SKIP_RADIO_FORWARD(0x6DDBBDD98E2E9C25);
lazy_func_t<void(Vehicle vehicle, BOOL mute, int p2)>
	OVERRIDE_VEH_HORN(0x3CDC1E622CCE0356);
lazy_func_t<void(float x, float y, float z)>
	SPECIAL_FRONTEND_EQUAL(0x21442F412E8DE56B);
lazy_func_t<void(Object *vehicle, ScrHandle *toggle)>
	SET_SIREN_WITH_NO_DRIVER(0x1FEF0683B96EBCF2);
lazy_func_t<Any()> AUDIO_IS_SCRIPTED_MUSIC_PLAYING(0x845FFC3A4FEEFA3E);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0xFBE20329593DEC9D(0xFBE20329593DEC9D);
lazy_func_t<void(const char *radioStation, BOOL p1)>
	_0x774BD811F656A122(0x774BD811F656A122);
lazy_func_t<void()> STOP_AUDIO_SCENES(0xBAC7FC81A75EC1A1);
lazy_func_t<int(Any p0)>
	GET_NUMBER_OF_PASSENGER_VOICE_VARIATIONS(0x66E49BF55B4B1874);
lazy_func_t<void(const char *zoneName, BOOL p1)>
	CLEAR_AMBIENT_ZONE_STATE(0x218DD44AAAC964FF);
lazy_func_t<BOOL(Vehicle vehicle)> IS_HORN_ACTIVE(0x9D6BFC12B05C6121);
lazy_func_t<void(Vehicle vehicle, const char *audioName)>
	_FORCE_VEHICLE_ENGINE_AUDIO(0x4F0C413926060B38);
lazy_func_t<Any()> _0xE73364DB90778FFA(0xE73364DB90778FFA);
lazy_func_t<void(const char *emitterName, const char *radioStation)>
	SET_EMITTER_RADIO_STATION(0xACF57305B12AF907);
lazy_func_t<BOOL()> IS_STREAM_PLAYING(0xD11FA52EB849D978);
lazy_func_t<Any()> _0xA097AB275061FB21(0xA097AB275061FB21);
lazy_func_t<void(const char *p0, float p1)>
	SET_VARIABLE_ON_STREAM(0x2F9D3834AEB9EF79);
lazy_func_t<void(const char *ambientZone, BOOL p1, BOOL p2)>
	SET_AMBIENT_ZONE_STATE_PERSISTENT(0x1D6650420CEC9D3B);
lazy_func_t<void(Ped ped, BOOL shaking)> STOP_PED_SPEAKING(0x9D64D7405520E3D3);
lazy_func_t<void()> CREATE_NEW_SCRIPTED_CONVERSATION(0xD2C91A0B572AAE56);
lazy_func_t<void(
	Player soundId,
	const char *audioName,
	const char *audioRef,
	BOOL p3,
	Any p4,
	BOOL p5)>
	PLAY_SOUND(0x7FF4944CC209192D);
lazy_func_t<void(const char *radioStation, const char *radioTrack)>
	SET_RADIO_TRACK(0xB39786F201FEE30B);
lazy_func_t<void(const char *alarmName, BOOL toggle)>
	STOP_ALARM(0xA1CADDCD98415A41);
lazy_func_t<void(const char *p0, const char *p1)>
	_0x044DBAD7A7FA2BE5(0x044DBAD7A7FA2BE5);
lazy_func_t<void(BOOL p0, BOOL p1, BOOL p2, BOOL p3)>
	PRELOAD_SCRIPT_CONVERSATION(0x3B3CAD6166916D87);
lazy_func_t<void(Ped ped, int painID, int p1)> PLAY_PAIN(0xBC9AE166038A5CEC);
lazy_func_t<BOOL(Ped ped, const char *speechName, BOOL unk)>
	_CAN_PED_SPEAK(0x49B99BF3FDA89A7A);
lazy_func_t<BOOL(Ped ped)> IS_PED_IN_CURRENT_CONVERSATION(0x049E937F18F4020C);
lazy_func_t<int()> _MAX_RADIO_STATION_INDEX(0xF1620ECB50E01DE7);
lazy_func_t<void(const char *radioStation, const char *p1)>
	_0x031ACB6ABA18C729(0x031ACB6ABA18C729);
lazy_func_t<Any()> _0x6F259F82D873B8B8(0x6F259F82D873B8B8);
lazy_func_t<void(Entity p0, const char *p1, float p2)>
	_DYNAMIC_MIXER_RELATED_FN(0x153973AB99FE8980);
lazy_func_t<BOOL(const char *scene)> IS_AUDIO_SCENE_ACTIVE(0xB65B60556E2A9225);
lazy_func_t<Any(const char *name, float p1)>
	PLAY_POLICE_REPORT(0xDFEBD56D9BD1EB16);
lazy_func_t<void(Any p0, BOOL p1)> _0x2BE4BC731D039D5A(0x2BE4BC731D039D5A);
lazy_func_t<void(const char *alarmName, BOOL p2)>
	START_ALARM(0x0355EF116C4C97B2);
lazy_func_t<BOOL(Ped ped)> IS_PED_RINGTONE_PLAYING(0x1E8E5E20937E3137);
lazy_func_t<void()> _0xFF266D1D0EB1195D(0xFF266D1D0EB1195D);
lazy_func_t<void(const char *radioStation)>
	FREEZE_RADIO_STATION(0x344F393B027E38C3);
lazy_func_t<void(Ped ped)> _SET_PED_TALK(0x4ADA3F19BE4A6047);
lazy_func_t<void(Any p0, BOOL p1)> _0x6FDDAD856E36988A(0x6FDDAD856E36988A);
lazy_func_t<void(BOOL p0)> _0xF154B8D1775B2DEC(0xF154B8D1775B2DEC);
lazy_func_t<void(Any p0, Any *p1, Any *p2)>
	INTERRUPT_CONVERSATION(0xA018A12E5C5C2FA6);
lazy_func_t<void(int newsStory)> UNLOCK_MISSION_NEWS_STORY(0xB165AB7C248B2DC1);
lazy_func_t<void(Any *p0, BOOL p1)>
	CLEAR_AMBIENT_ZONE_LIST_STATE(0x120C48C614909FA4);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	USE_SIREN_AS_HORN(0xFA932DE350266EF8);
lazy_func_t<void(float p0, float p1)> _0x149AEE66F0CB3A99(0x149AEE66F0CB3A99);
lazy_func_t<BOOL(const char *alarmName)> IS_ALARM_PLAYING(0x226435CB96CCFC8C);
lazy_func_t<void(Any p0, BOOL p1)> _0xD2CC78CD3D0B50F9(0xD2CC78CD3D0B50F9);
lazy_func_t<void()> START_PRELOADED_CONVERSATION(0x23641AFE870AF385);
lazy_func_t<void(Any *p0, BOOL p1)>
	OVERRIDE_UNDERWATER_STREAM(0xF2A9CDABCEA04BD6);
lazy_func_t<void(Vehicle vehicle, const char *radioStation)>
	SET_VEH_RADIO_STATION(0x1B9C0099CB942AC6);
lazy_func_t<void(BOOL active)> SET_FRONTEND_RADIO_ACTIVE(0xF7F26C6E9CC9EBB8);
lazy_func_t<BOOL(Any p0)> _0xC265DF9FB44A9FBD(0xC265DF9FB44A9FBD);
lazy_func_t<int()> GET_STREAM_PLAY_TIME(0x4E72BBDBCA58A3DB);
lazy_func_t<void(BOOL p0)> _0x61631F5DF50D1C34(0x61631F5DF50D1C34);
lazy_func_t<void()> UNREGISTER_SCRIPT_WITH_AUDIO(0xA8638BE228D4751A);
lazy_func_t<int(int soundId)> GET_NETWORK_ID_FROM_SOUND_ID(0x2DE3F0A134FFBC0D);
lazy_func_t<void(int soundId, const char *variableName, float value)>
	SET_VARIABLE_ON_SOUND(0xAD6B3148A78AE9B6);
lazy_func_t<BOOL(const char *p0, BOOL p1)>
	REQUEST_AMBIENT_AUDIO_BANK(0xFE02FFBED8CA9D99);
lazy_func_t<Any()> GET_PLAYER_RADIO_STATION_GENRE(0xA571991A7FE6CCEB);
lazy_func_t<BOOL(const char *ambientZone)>
	IS_AMBIENT_ZONE_ENABLED(0x01E2817A479A7F9B);
lazy_func_t<Any()> _0x5B50ABB1FE3746F4(0x5B50ABB1FE3746F4);
lazy_func_t<void()> RELEASE_AMBIENT_AUDIO_BANK(0x65475A218FFAA93D);
lazy_func_t<void(BOOL state)> SET_MOBILE_PHONE_RADIO_STATE(0xBF286C554784F3DF);
lazy_func_t<BOOL(Vehicle vehicle)> _IS_VEHICLE_RADIO_LOUD(0x032A116663A4D5AC);
lazy_func_t<void(const char *p0, BOOL p1, BOOL p2)>
	SET_AMBIENT_ZONE_LIST_STATE(0x9748FA4DE50CCE3E);
lazy_func_t<BOOL()> IS_SCRIPTED_CONVERSATION_ONGOING(0x16754C556D2EDE3D);
lazy_func_t<Any(BOOL p0)> STOP_SCRIPTED_CONVERSATION(0xD79DEEFB53455EBA);
lazy_func_t<Any(Any *p0)> _0xAA19F5572C38B564(0xAA19F5572C38B564);
lazy_func_t<void(BOOL p0)> _0xB542DE8C3D1CB210(0xB542DE8C3D1CB210);
lazy_func_t<void()> _0xD57AAAE0E2214D11(0xD57AAAE0E2214D11);
lazy_func_t<void(Ped ped)>
	STOP_CURRENT_PLAYING_AMBIENT_SPEECH(0xB8BEC0CA6F0EDB0F);
lazy_func_t<void(Any p0, float p1)> _0x01BB4D577D38BD9E(0x01BB4D577D38BD9E);
lazy_func_t<void(BOOL p0, BOOL p1, BOOL p2, BOOL p3)>
	START_SCRIPT_CONVERSATION(0x6B17C62C9635D2DC);
lazy_func_t<void(Vehicle vehicle)>
	_SOUND_VEHICLE_HORN_THIS_FRAME(0x9C11908013EA4715);
lazy_func_t<void(BOOL value)> _FORCE_AMBIENT_SIREN(0x552369F549563AD5);
lazy_func_t<BOOL(Ped ped)> IS_ANY_SPEECH_PLAYING(0x729072355FA39EC9);
lazy_func_t<const char *(int radioStation)>
	GET_RADIO_STATION_NAME(0xB28ECA15046CA8B9);
lazy_func_t<void(const char *radioStation, const char *p1, BOOL p2)>
	_0x4E404A9361F75BB2(0x4E404A9361F75BB2);
lazy_func_t<void(
	int soundId,
	const char *audioName,
	float x,
	float y,
	float z,
	const char *audioRef,
	BOOL p6,
	int range,
	BOOL p8)>
	PLAY_SOUND_FROM_COORD(0x8D8686B622B88120);
lazy_func_t<int(int netId)> GET_SOUND_ID_FROM_NETWORK_ID(0x75262FD12D0A1C84);
lazy_func_t<BOOL(Ped p0)> IS_AMBIENT_SPEECH_PLAYING(0x9072C8B49907BFAD);
lazy_func_t<BOOL(Any p0)> IS_SCRIPTED_SPEECH_PLAYING(0xCC9AA18DCC7084F4);
lazy_func_t<void(Any p0)> _0xA5F377B175A699C5(0xA5F377B175A699C5);
lazy_func_t<void()> _0x062D5EAD4DA2FA6A(0x062D5EAD4DA2FA6A);
lazy_func_t<void(BOOL p0)> _0xBEF34B1D9624D5DD(0xBEF34B1D9624D5DD);
lazy_func_t<void(Any p0, float p1)> _0x18EB48CFC41F2EA0(0x18EB48CFC41F2EA0);
lazy_func_t<void(Any p0, Any p1)> _0x892B6AB8F33606F5(0x892B6AB8F33606F5);
lazy_func_t<void(Any p0, Any p1, Any *p2)>
	_0xEE066C7006C49C0A(0xEE066C7006C49C0A);
lazy_func_t<void(Vehicle vehicle, int p1)>
	PLAY_VEHICLE_DOOR_OPEN_SOUND(0x3A539D52857EA82D);
lazy_func_t<void(const char *scene, const char *variable, float value)>
	SET_AUDIO_SCENE_VARIABLE(0xEF21A9EF089A2668);
lazy_func_t<BOOL(const char *p0, BOOL p1)>
	REQUEST_MISSION_AUDIO_BANK(0x7345BDD95E62E0F2);
lazy_func_t<void()> STOP_STREAM(0xA4718A1419D18151);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x43FA0DFC5DF87815(0x43FA0DFC5DF87815);
lazy_func_t<void(Ped ped, BOOL toggle)> SET_PED_IS_DRUNK(0x95D2D383D5396B8A);
lazy_func_t<void(BOOL toggle)>
	SET_USER_RADIO_CONTROL_ENABLED(0x19F21E63AE6EAE4E);
lazy_func_t<void(const char *p0)>
	SET_CUTSCENE_AUDIO_OVERRIDE(0x3B4BF5F0859204D9);
lazy_func_t<void()> _DISABLE_POLICE_REPORTS(0xB4F90FAF7670B16F);
lazy_func_t<Any(Any p0, Any p1)> HINT_SCRIPT_AUDIO_BANK(0xFB380A29641EC31A);
lazy_func_t<void(const char *p0)> _0xDDC635D5B3262C56(0xDDC635D5B3262C56);
lazy_func_t<void(Any p0, BOOL p1)> _0xF3365489E0DD50F9(0xF3365489E0DD50F9);
lazy_func_t<void()> _0x19AF7ED9B9D23058(0x19AF7ED9B9D23058);
lazy_func_t<int(int station)> FIND_RADIO_STATION_INDEX(0x8D67489793FF428B);
lazy_func_t<BOOL(const char *streamName, int startOffset, const char *soundSet)>
	LOAD_STREAM_WITH_START_OFFSET(0x59C16B79F53B3712);
lazy_func_t<BOOL(Any p0)> PLAY_SYNCHRONIZED_AUDIO_EVENT(0x8B2FD4560E55DD2D);
lazy_func_t<void(
	BOOL p0,
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	float x3,
	float y3,
	float z3)>
	SET_MICROPHONE_POSITION(0xB6AE90EDDE95C762);
lazy_func_t<void(Any *p0)> OVERRIDE_TREVOR_RAGE(0x13AD665062541A7E);
lazy_func_t<void(Ped ped, const char *name)>
	SET_AMBIENT_VOICE_NAME(0x6C8065A3B780185B);
lazy_func_t<void(const char *audioName)>
	PLAY_MISSION_COMPLETE_AUDIO(0xB138AAB8A70D3C69);
lazy_func_t<void(BOOL p0, BOOL p1)>
	PRELOAD_SCRIPT_PHONE_CONVERSATION(0x6004BCB0E226AAEA);
lazy_func_t<void()> RELEASE_MISSION_AUDIO_BANK(0x0EC92A1BF0857187);
lazy_func_t<void()> RESET_TREVOR_RAGE(0xE78503B10C4314E0);
lazy_func_t<void(Any p0, BOOL p1)> _0x1C073274E065C6D2(0x1C073274E065C6D2);
lazy_func_t<Any()> GET_CURRENT_SCRIPTED_CONVERSATION_LINE(0x480357EE890C295A);
lazy_func_t<Any()> _0x0626A247D2405330(0x0626A247D2405330);
lazy_func_t<const char *()> GET_PLAYER_RADIO_STATION_NAME(0xF6D733C32076AD03);
lazy_func_t<void(Any p0, float p1)> _0x59E7B488451F4D3A(0x59E7B488451F4D3A);
lazy_func_t<void(const char *scene)> STOP_AUDIO_SCENE(0xDFE8422B3B94E688);
lazy_func_t<void(const char *ringtoneName, Ped ped, BOOL p2)>
	PLAY_PED_RINGTONE(0xF9E56683CA8E11A5);
lazy_func_t<void(Ped ped, const char *speechName, const char *speechParam)>
	_PLAY_AMBIENT_SPEECH1(0x8E04FEDD28D42462);
lazy_func_t<void()> _0xDD6BCF9E94425DF9(0xDD6BCF9E94425DF9);
lazy_func_t<void(const char *flagName, BOOL toggle)>
	SET_AUDIO_FLAG(0xB9EFD5C25018725A);
lazy_func_t<void()> _0x9AC92EED5E4793AB(0x9AC92EED5E4793AB);
lazy_func_t<void(Any p0, BOOL p1)> _0x06C0023BED16DD6B(0x06C0023BED16DD6B);
lazy_func_t<Any(const char *p0, Any p1)>
	PREPARE_SYNCHRONIZED_AUDIO_EVENT(0xC7ABCACA4985A766);
lazy_func_t<BOOL(Ped ped)> IS_AMBIENT_SPEECH_DISABLED(0x932C2D096A2C3FFF);
lazy_func_t<BOOL()> IS_MOBILE_PHONE_CALL_ONGOING(0x7497D2CE2C30D24C);
lazy_func_t<void(BOOL p0)> PAUSE_SCRIPTED_CONVERSATION(0x8530AD776CD72B12);
lazy_func_t<void(Vehicle vehicle)> _0xC1805D05E6D4FE10(0xC1805D05E6D4FE10);
lazy_func_t<void(Vehicle vehicle)> BLIP_SIREN(0x1B9025BDA76822B6);
lazy_func_t<
	void(int soundId, const char *audioName, const char *audioRef, BOOL p3)>
	PLAY_SOUND_FRONTEND(0x67C540AA08E4A6F5);
lazy_func_t<void(Any p0, BOOL p1)> _0xA5342D390CDA41D6(0xA5342D390CDA41D6);
lazy_func_t<void(Ped ped)> PLAY_STREAM_FROM_PED(0x89049DD63C08B5D1);
lazy_func_t<Hash(Vehicle vehicle)> _GET_VEHICLE_HORN_HASH(0xACB5DCCA1EC76840);
lazy_func_t<BOOL()> IS_SCRIPTED_CONVERSATION_LOADED(0xDF0D54BE7A776737);
lazy_func_t<BOOL(const char *scene)> START_AUDIO_SCENE(0x013A80FC08F6E4F2);
lazy_func_t<void(
	int p0,
	const char *p1,
	const char *p2,
	int p3,
	int p4,
	BOOL p5,
	BOOL p6,
	BOOL p7,
	BOOL p8,
	int p9,
	BOOL p10,
	BOOL p11,
	BOOL p12)>
	ADD_LINE_TO_CONVERSATION(0xC5EF963405593646);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_HORN_ENABLED(0x76D683C108594D0E);
lazy_func_t<void()> RELEASE_SCRIPT_AUDIO_BANK(0x7A2D8AD0A9EB9C3F);
lazy_func_t<void(
	int soundId,
	const char *audioName,
	Entity entity,
	const char *audioRef,
	BOOL p4,
	Any p5)>
	PLAY_SOUND_FROM_ENTITY(0xE65F427EB70AB1ED);
lazy_func_t<void(Vehicle vehicle, int p1)>
	PLAY_VEHICLE_DOOR_CLOSE_SOUND(0x62A456AA4769EF34);
lazy_func_t<void(BOOL stop)> STOP_ALL_ALARMS(0x2F794A877ADD4C92);
lazy_func_t<void(Ped animal, int mood)> SET_ANIMAL_MOOD(0xCC97B29285B1DC3B);
lazy_func_t<void(const char *radioStation)>
	SET_INITIAL_PLAYER_STATION(0x88795F13FACDA88D);
lazy_func_t<void(Any *p0, BOOL p1, BOOL p2)>
	SET_AMBIENT_ZONE_STATE(0xBDA07E5950085E46);
lazy_func_t<BOOL(const char *eventName)>
	TRIGGER_MUSIC_EVENT(0x706D57B0F50DA710);
}} // namespace AUDIO::
namespace ZONE { namespace {
lazy_func_t<void(int scheduleId)>
	CLEAR_POPSCHEDULE_OVERRIDE_VEHICLE_MODEL(0x5C0DE367AA0D911C);
lazy_func_t<Hash(float x, float y, float z)>
	GET_HASH_OF_MAP_AREA_AT_COORDS(0x7EE64D51E8498728);
lazy_func_t<int(float x, float y, float z)>
	GET_ZONE_AT_COORDS(0x27040C25DE6CB2F4);
lazy_func_t<int(int zoneId)> GET_ZONE_POPSCHEDULE(0x4334BC40AA0CB4BB);
lazy_func_t<void(int zoneId, BOOL toggle)> SET_ZONE_ENABLED(0xBA5ECEEA120E5611);
lazy_func_t<void(int scheduleId, Hash vehicleHash)>
	OVERRIDE_POPSCHEDULE_VEHICLE_MODEL(0x5F7D596BAC2E7777);
lazy_func_t<int(const char *zoneName)>
	GET_ZONE_FROM_NAME_ID(0x98CD1D2934B76CC1);
lazy_func_t<const char *(float x, float y, float z)>
	GET_NAME_OF_ZONE(0xCD90657D4C30E1CA);
lazy_func_t<int(int zoneId)> GET_ZONE_SCUMMINESS(0x5F7B268D15BA0739);
}} // namespace ZONE::
namespace DLC2 { namespace {
lazy_func_t<BOOL()> _0xF2E07819EF1A5289(0xF2E07819EF1A5289);
lazy_func_t<Any()> _0x9489659372A81585(0x9489659372A81585);
lazy_func_t<Any()> _0xA213B11DFF526300(0xA213B11DFF526300);
lazy_func_t<BOOL()> _0x8D30F648014A92B5(0x8D30F648014A92B5);
lazy_func_t<BOOL()> GET_IS_LOADING_SCREEN_ACTIVE(0x10D0A8F259E93EC9);
lazy_func_t<void()> _LOAD_MP_DLC_MAPS(0x0888C3502DBBEEF5);
lazy_func_t<BOOL(Hash dlcHash)> IS_DLC_PRESENT(0x812595A0644CE1DE);
lazy_func_t<BOOL(Any *variable, Any unused)> _NULLIFY(0x46E2B844905BC5F0);
lazy_func_t<void()> _0xD7C10C4A637992C9(0xD7C10C4A637992C9);
}} // namespace DLC2::
namespace PLAYER { namespace {
lazy_func_t<BOOL(Hash playerModel)>
	IS_SPECIAL_ABILITY_UNLOCKED(0xC6017F6A6CDFA694);
lazy_func_t<void(Player player, float damageAmount)>
	SET_PLAYER_VEHICLE_DAMAGE_MODIFIER(0xA50E117CDDF82F0C);
lazy_func_t<void(Player player)> _0xBC9490CA15AEA8FB(0xBC9490CA15AEA8FB);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_SIMULATE_AIMING(0xC54C95DA968EC5B5);
lazy_func_t<BOOL(Player player)> IS_PLAYER_RIDING_TRAIN(0x4EC12697209F2196);
lazy_func_t<void(int p0)> _0x5702B917B99DB1CD(0x5702B917B99DB1CD);
lazy_func_t<void(Player player, int flags)>
	SET_PLAYER_RESET_FLAG_PREFER_REAR_SEATS(0x11D5F725F0E780E0);
lazy_func_t<Any(int achId)> GIVE_ACHIEVEMENT_TO_PLAYER(0xBEC7076D64130195);
lazy_func_t<void(Player player, float damageAmount)>
	SET_PLAYER_WEAPON_DAMAGE_MODIFIER(0xCE07B9F7817AADA3);
lazy_func_t<BOOL(Player player)> HAS_PLAYER_LEFT_THE_WORLD(0xD55DDFB47991A294);
lazy_func_t<BOOL(Player player)> IS_PLAYER_PRESSING_HORN(0xFA1E2BF8B10598F9);
lazy_func_t<void(float multiplier)>
	SET_WANTED_LEVEL_MULTIPLIER(0x020E5F00CDA207BA);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(0xD5E460AD7020A246);
lazy_func_t<void(float p0)> _0xB45EFF719D8427A6(0xB45EFF719D8427A6);
lazy_func_t<void(Player player, BOOL toggle)>
	GIVE_PLAYER_RAGDOLL_CONTROL(0x3C49C870E66F0A28);
lazy_func_t<BOOL(Player player)> IS_PLAYER_DEAD(0x424D4687FA1E5652);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_ALL_RANDOM_PEDS_FLEE(0x056E0FE8534C2949);
lazy_func_t<void(int cleanupFlags)> FORCE_CLEANUP(0xBC8983F38F78ED51);
lazy_func_t<BOOL(Player player)> IS_PLAYER_FREE_AIMING(0x2E397FD2ECD37C87);
lazy_func_t<Player(int *p0)> _0x56105E599CAB0EFA(0x56105E599CAB0EFA);
lazy_func_t<void(Player player)> _0xFFEE8FA29AB9A18E(0xFFEE8FA29AB9A18E);
lazy_func_t<void(Player player)> _0x36F1B38855F2A8DF(0x36F1B38855F2A8DF);
lazy_func_t<void(BOOL unk)> DISPLAY_SYSTEM_SIGNIN_UI(0x94DD7888C10A979E);
lazy_func_t<void(Hash playerModel)> SPECIAL_ABILITY_UNLOCK(0xF145F3BE2EFA9A3B);
lazy_func_t<void(Player player)>
	CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(0x4AACB96203D11A31);
lazy_func_t<void(Player player, BOOL p1)>
	SPECIAL_ABILITY_FILL_METER(0x3DACA8DDC6FD4980);
lazy_func_t<Ped(Player Player)> GET_PLAYER_PED_SCRIPT_INDEX(0x50FAC3A3E030A6E1);
lazy_func_t<void(Player player, int wantedLevel, BOOL disableNoMission)>
	SET_PLAYER_WANTED_LEVEL(0x39FF19C64EF7DA5B);
lazy_func_t<void(Player player, int r, int g, int b)>
	SET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(0x8217FD371A4625CF);
lazy_func_t<BOOL(Ped p0)> _0x690A61A6D13583F6(0x690A61A6D13583F6);
lazy_func_t<void(Player player)>
	DISABLE_PLAYER_VEHICLE_REWARDS(0xC142BE3BB9CE125F);
lazy_func_t<void(int duration)> START_FIRING_AMNESTY(0xBF9BD71691857E48);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_FORCED_ZOOM(0x75E7D505F2B15902);
lazy_func_t<void(Player player, BOOL p1, BOOL p2)>
	SPECIAL_ABILITY_CHARGE_LARGE(0xF733F45FA4497D93);
lazy_func_t<void(Player *player)>
	SET_PLAYER_MAY_NOT_ENTER_ANY_VEHICLE(0x1DE37BBF9E9CC14A);
lazy_func_t<BOOL()> IS_SYSTEM_UI_BEING_DISPLAYED(0x5D511E3867C87139);
lazy_func_t<void(Player Player, Ped ped, BOOL b2, BOOL b3)>
	CHANGE_PLAYER_PED(0x048189FAC643DEEE);
lazy_func_t<BOOL(Player player)> IS_PLAYER_PLAYING(0x5E9564D8246B909A);
lazy_func_t<Any(Player player)> _0xAD73CE5A09E42D12(0xAD73CE5A09E42D12);
lazy_func_t<void(Player player)> RESET_PLAYER_INPUT_GAIT(0x19531C47A2ABD691);
lazy_func_t<void(BOOL p0)> _0x2F7CEB6520288061(0x2F7CEB6520288061);
lazy_func_t<void(Player player)> SPECIAL_ABILITY_DEACTIVATE(0xD6A953C6D1492057);
lazy_func_t<void(Player player, float modifier)>
	SET_PLAYER_MELEE_WEAPON_DEFENSE_MODIFIER(0xAE540335B4ABC4E2);
lazy_func_t<void(Player player, float modifier)>
	SET_PLAYER_VEHICLE_DEFENSE_MODIFIER(0x4C60E6EFDAFF2462);
lazy_func_t<void(Player player)> _0xC3376F42B1FACCC6(0xC3376F42B1FACCC6);
lazy_func_t<void(Player player, float x, float y, float z)>
	SET_PLAYER_WANTED_CENTRE_POSITION(0x520E541A97A13354);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_EVERYONE_IGNORE_PLAYER(0x8EEDA153AD141BA4);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_SPRINT(0xA01B8075D8B92DF4);
lazy_func_t<BOOL(Player player, Ped ped)>
	CAN_PED_HEAR_PLAYER(0xF297383AA91DCA29);
lazy_func_t<void(Player player, int *tintIndex)>
	GET_PLAYER_PARACHUTE_PACK_TINT_INDEX(0x6E9C742F340CE5A2);
lazy_func_t<BOOL(Player p0)> _0x65FAEE425DE637B0(0x65FAEE425DE637B0);
lazy_func_t<void(float multiplier)>
	SET_SPECIAL_ABILITY_MULTIPLIER(0xA49C426ED0CA4AB7);
lazy_func_t<void(Player player, float modifier)>
	SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(0x4A3DC7ECCC321032);
lazy_func_t<BOOL()> _0xB9CF1F793A9F1BF1(0xB9CF1F793A9F1BF1);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_CAN_DO_DRIVE_BY(0x6E8834B52EC20C77);
lazy_func_t<float(Player player)>
	GET_PLAYER_SPRINT_STAMINA_REMAINING(0x3F9F16F8E65A7ED7);
lazy_func_t<BOOL(Player player)>
	IS_PLAYER_SCRIPT_CONTROL_ON(0x8A876A65283DD7D7);
lazy_func_t<BOOL(Player player)> IS_SPECIAL_ABILITY_ENABLED(0xB1D200FE26AEF3CB);
lazy_func_t<void(Player player)> _0x9EDD76E87D5D51BA(0x9EDD76E87D5D51BA);
lazy_func_t<void(Any toggle)> SET_POLICE_RADAR_BLIPS(0x43286D561B72B8BF);
lazy_func_t<BOOL(Player player, Entity entity)>
	IS_PLAYER_TARGETTING_ENTITY(0x7912F7FC4F6264B6);
lazy_func_t<Ped()> PLAYER_PED_ID(0xD80958FC74E988A6);
lazy_func_t<void(const char *name, int cleanupFlags)>
	FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(0x4C68DDDDF0097317);
lazy_func_t<void(Player player)> _0xC9A763D8FE87436A(0xC9A763D8FE87436A);
lazy_func_t<void(Player player)> RESET_PLAYER_STAMINA(0xA6F312FCCE9C1DFE);
lazy_func_t<void(Player player)>
	CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(0xF0B67A4DE6AB5F98);
lazy_func_t<void(Player player)>
	CLEAR_PLAYER_PARACHUTE_VARIATION_OVERRIDE(0x0F4CC924CF8C7B21);
lazy_func_t<void(Player player, int index)>
	SET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(0xAF04C87F5DC1DF38);
lazy_func_t<Vehicle()> GET_PLAYERS_LAST_VEHICLE(0xB6997A7EB3F5C8C0);
lazy_func_t<void(Player player, float multiplier)>
	SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(0x6DB47AA77FD94E09);
lazy_func_t<void(Player player, BOOL toggle)>
	_0xDE45D1A1EF45EE61(0xDE45D1A1EF45EE61);
lazy_func_t<void(Player player, float multiplier)>
	SET_AIR_DRAG_MULTIPLIER_FOR_PLAYERS_VEHICLE(0xCA7DC8329F0A1E9E);
lazy_func_t<void(Player player, float multiplier)>
	SET_PLAYER_SNEAKING_NOISE_MULTIPLIER(0xB2C1A29588A9F47C);
lazy_func_t<const char *(Player player)> GET_PLAYER_NAME(0x6D0DE6A7B5DA71F8);
lazy_func_t<int()> NETWORK_PLAYER_ID_TO_INT(0xEE68096F9F37341E);
lazy_func_t<void(Player Player, int *r, int *g, int *b)>
	GET_PLAYER_RGB_COLOUR(0xE902EF951DCE178F);
lazy_func_t<void()> PLAYER_DETACH_VIRTUAL_BOUND(0x1DD5897E2FA6E7C9);
lazy_func_t<float(Player player)>
	GET_PLAYER_UNDERWATER_TIME_REMAINING(0xA1FCF8E6AF40B731);
lazy_func_t<Player(Vehicle player)>
	IS_PLAYER_FREE_FOR_AMBIENT_TASK(0xDCCFD3F106C36AB4);
lazy_func_t<void()> ASSISTED_MOVEMENT_FLUSH_ROUTE(0x8621390F0CDCFE1F);
lazy_func_t<void(Player player, int *index)>
	GET_PLAYER_RESERVE_PARACHUTE_TINT_INDEX(0xD5A016BC3C09CF40);
lazy_func_t<void(Player player, float value)>
	SET_PLAYER_STEALTH_PERCEPTION_MODIFIER(0x4E9021C1FCDD507A);
lazy_func_t<Player()> PLAYER_ID(0x4F8644AF03D0E0D6);
lazy_func_t<void(Player player, Ped p2)>
	SPECIAL_ABILITY_CHARGE_CONTINUOUS(0xED481732DFF7E997);
lazy_func_t<BOOL(Player player, float p1)>
	_0xDD2620B7B9D16FF1(0xDD2620B7B9D16FF1);
lazy_func_t<Vector3(Player player)>
	GET_PLAYER_WANTED_CENTRE_POSITION(0x0C92BA89F1AF26F8);
lazy_func_t<void(Player player)>
	RESET_WANTED_LEVEL_DIFFICULTY(0xB9D0DD990DC141DD);
lazy_func_t<void(Player player, float p1)>
	RESTORE_PLAYER_STAMINA(0xA352C1B864CAFD33);
lazy_func_t<void(Player player, float multiplier)>
	SET_PLAYER_NOISE_MULTIPLIER(0xDB89EF50FF25FCE9);
lazy_func_t<void(Player player)>
	SET_ALL_RANDOM_PEDS_FLEE_THIS_FRAME(0x471D2FF42A94B4F2);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_INVINCIBLE(0x239528EACDC3E7DE);
lazy_func_t<BOOL(Player player, int p1, BOOL p2)>
	_0xBC0753C9CA14B506(0xBC0753C9CA14B506);
lazy_func_t<BOOL(Player player)> _0x5FC472C501CCADB3(0x5FC472C501CCADB3);
lazy_func_t<float(Player player)>
	GET_PLAYER_CURRENT_STEALTH_NOISE(0x2F395D61F3A1F877);
lazy_func_t<int(int value)> INT_TO_PARTICIPANTINDEX(0x9EC6603812C24710);
lazy_func_t<int(Player player)>
	GET_TIME_SINCE_PLAYER_DROVE_ON_PAVEMENT(0xD559D2BE9E37853B);
lazy_func_t<void(Player player, BOOL p1)>
	_0xCAC57395B151135F(0xCAC57395B151135F);
lazy_func_t<BOOL(Player player)>
	HAS_PLAYER_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(0xE4B90F367BD81752);
lazy_func_t<void(Player player, int value)>
	SET_PLAYER_MAX_ARMOUR(0x77DFCCF5948B8C71);
lazy_func_t<void(Hash playerModel)> SPECIAL_ABILITY_LOCK(0x6A09D0D590A47D13);
lazy_func_t<BOOL()> IS_PLAYER_TELEPORT_ACTIVE(0x02B15662D7F8886F);
lazy_func_t<BOOL(Player player)>
	IS_PLAYER_READY_FOR_CUTSCENE(0x908CBECC2CAA3690);
lazy_func_t<int()> GET_CAUSE_OF_MOST_RECENT_FORCE_CLEANUP(0x9A41CF4674A12272);
lazy_func_t<BOOL(Player player)> GET_PLAYER_INVINCIBLE(0xB721981B2B939E07);
lazy_func_t<void(Player player, BOOL p1)>
	_0xD2B315B6689D537D(0xD2B315B6689D537D);
lazy_func_t<void(Player player, BOOL p1)>
	SET_PLAYER_WANTED_LEVEL_NOW(0xE0A7D1E497FFCD6F);
lazy_func_t<int(Player player)>
	GET_TIME_SINCE_PLAYER_HIT_VEHICLE(0x5D35ECF3A81A0EE0);
lazy_func_t<BOOL(int achId, int progression)>
	_SET_ACHIEVEMENT_PROGRESSION(0xC2AFFFDABBDC2C5C);
lazy_func_t<void(Player player)> SPECIAL_ABILITY_RESET(0x375F0E738F861A94);
lazy_func_t<void(Player player, float multiplier)>
	SET_SWIM_MULTIPLIER_FOR_PLAYER(0xA91C6F0FF7D16A13);
lazy_func_t<Ped(Player playerID)> GET_PLAYER_PED(0x43A66C31C68491C0);
lazy_func_t<BOOL(Player player)>
	ARE_PLAYER_FLASHING_STARS_ABOUT_TO_DROP(0xAFAF86043E5874E9);
lazy_func_t<int(Player player)>
	GET_TIME_SINCE_PLAYER_HIT_PED(0xE36A25322DC35F42);
lazy_func_t<BOOL()> IS_PLAYER_ONLINE(0xF25D331DC2627BBC);
lazy_func_t<BOOL(Player player)>
	HAS_PLAYER_BEEN_SPOTTED_IN_STOLEN_VEHICLE(0xD705740BB0A1CF4C);
lazy_func_t<void(Player player, float range)>
	SET_PLAYER_LOCKON_RANGE_OVERRIDE(0x29961D490E5814FD);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_FORCED_AIM(0x0FEE4F80AC44A726);
lazy_func_t<BOOL(Player player)>
	_HAS_PLAYER_TELEPORT_FINISHED(0xE23D5873C2394C61);
lazy_func_t<void(Player player, int tintIndex)>
	SET_PLAYER_PARACHUTE_TINT_INDEX(0xA3D0E54541D9A5E5);
lazy_func_t<BOOL(Player player, Entity *entity)>
	GET_PLAYER_TARGET_ENTITY(0x13EDE1A5DBF797C9);
lazy_func_t<void(Player player, BOOL enabled)>
	SET_PLAYER_CAN_LEAVE_PARACHUTE_SMOKE_TRAIL(0xF401B182DBA8AF53);
lazy_func_t<void(Player player, Hash model)>
	SET_PLAYER_PARACHUTE_MODEL_OVERRIDE(0x977DB4641F6FC3DB);
lazy_func_t<void(Player p0)> _0x5501B7A5CDB79D37(0x5501B7A5CDB79D37);
lazy_func_t<void(Player player, int crimeType, int wantedLvlThresh)>
	REPORT_CRIME(0xE9B09589827545E7);
lazy_func_t<void()> ASSISTED_MOVEMENT_CLOSE_ROUTE(0xAEBF081FFC0A0E5E);
lazy_func_t<void(Player player, int *r, int *g, int *b)>
	GET_PLAYER_PARACHUTE_SMOKE_TRAIL_COLOR(0xEF56DBABD3CD4887);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_CLOTH_PIN_FRAMES(0x749FADDF97DFE930);
lazy_func_t<void(Player player)> RESET_PLAYER_ARREST_STATE(0x2D03E13C460760D6);
lazy_func_t<Player()> GET_PLAYER_INDEX(0xA5EDC40EF369B48D);
lazy_func_t<void(Player player, float regenRate)>
	SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(0x5DB660B38DD98A31);
lazy_func_t<int()> GET_TIME_SINCE_LAST_ARREST(0x5063F92F07C2A316);
lazy_func_t<Any(Player player)> _0x4669B3ED80F24B4E(0x4669B3ED80F24B4E);
lazy_func_t<void(Player player)>
	SET_PLAYER_HAS_RESERVE_PARACHUTE(0x7DDAB28D31FAC363);
lazy_func_t<int(Player player)> GET_PLAYER_TEAM(0x37039302F4E0A008);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(0x596976B02B6B5700);
lazy_func_t<BOOL(Player player)> _0x38D28DA81E4E9BF9(0x38D28DA81E4E9BF9);
lazy_func_t<void(float x, float y, float z)>
	_EXPAND_WORLD_LIMITS(0x5006D96C995A5827);
lazy_func_t<BOOL(Player player, BOOL atArresting)>
	IS_PLAYER_BEING_ARRESTED(0x388A47C51ABDAC8E);
lazy_func_t<void(Player player, int wantedLevel, BOOL p2)>
	SET_PLAYER_WANTED_LEVEL_NO_DROP(0x340E61DE7F471565);
lazy_func_t<void(Player player)> CLEAR_PLAYER_WANTED_LEVEL(0xB302540597885499);
lazy_func_t<BOOL(Player player)> IS_PLAYER_CONTROL_ON(0x49C32D60007AFA47);
lazy_func_t<void(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7)>
	PLAYER_ATTACH_VIRTUAL_BOUND(0xED51733DC73AED51);
lazy_func_t<int(Player player)> GET_PLAYER_WANTED_LEVEL(0xE28E54788CE8F12D);
lazy_func_t<int(Player player)>
	GET_TIME_SINCE_PLAYER_DROVE_AGAINST_TRAFFIC(0xDB89591E290D9182);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_LOCKON(0x5C8B2F450EE4328E);
lazy_func_t<void(Player player)> _0xDC64D2C53493ED12(0xDC64D2C53493ED12);
lazy_func_t<int(Player player)> GET_PLAYER_MAX_ARMOUR(0x92659B4CE1863CB3);
lazy_func_t<void(Player player, Vehicle vehicle)>
	SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(0x8026FF78F208978A);
lazy_func_t<void(Player player, Hash model)>
	SET_PLAYER_MODEL(0x00A1CADD00108836);
lazy_func_t<void(Player player, BOOL p1, BOOL p2)>
	SPECIAL_ABILITY_CHARGE_MEDIUM(0xF113E3AA9BC54613);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_POLICE_IGNORE_PLAYER(0x32C62AA929C2DA6A);
lazy_func_t<float(Player player)>
	GET_PLAYER_SPRINT_TIME_REMAINING(0x1885BC9B108B4C99);
lazy_func_t<void(int targetMode)> SET_PLAYER_TARGETING_MODE(0xB1906895227793F3);
lazy_func_t<BOOL(int cleanupFlags)>
	HAS_FORCE_CLEANUP_OCCURRED(0xC968670BFACE42D9);
lazy_func_t<void(int id, int cleanupFlags)>
	FORCE_CLEANUP_FOR_THREAD_WITH_THIS_ID(0xF745B37630DF176B);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_PLAYER_FORCE_SKIP_AIM_INTRO(0x7651BC64AE59E128);
lazy_func_t<void(Player player, BOOL toggle)>
	ENABLE_SPECIAL_ABILITY(0x181EC197DAEFE121);
lazy_func_t<Any(Player player)> GET_WANTED_LEVEL_RADIUS(0x085DEB493BE80812);
lazy_func_t<void(Player player, int *tintIndex)>
	GET_PLAYER_PARACHUTE_TINT_INDEX(0x75D3F7A1B0D9B145);
lazy_func_t<void(int index)> SET_PLAYER_CLOTH_PACKAGE_INDEX(0x9F7BBA2EA6372500);
lazy_func_t<BOOL(Player player, Entity *entity)>
	GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(0x2975C866E6713290);
lazy_func_t<void(Player player, ScrHandle modifier)>
	SET_PLAYER_WEAPON_DEFENSE_MODIFIER(0x2D83BC011CA14A3C);
lazy_func_t<BOOL(Player player)>
	GET_PLAYER_HAS_RESERVE_PARACHUTE(0x5DDFE2FF727F3CA3);
lazy_func_t<int(int wantedLevel)>
	GET_WANTED_LEVEL_THRESHOLD(0xFDD179EAF45B556C);
lazy_func_t<void(Player player, float difficulty)>
	SET_WANTED_LEVEL_DIFFICULTY(0x9B0BB33B04405E7A);
lazy_func_t<void(Player player, int p1, Any p2, Any p3, BOOL p4)>
	SET_PLAYER_PARACHUTE_VARIATION_OVERRIDE(0xD9284A8C0D48352C);
lazy_func_t<int()> GET_MAX_WANTED_LEVEL(0x462E0DB9B137DC5F);
lazy_func_t<BOOL(Player player)>
	HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(0x20CE80B0C2BF4ACC);
lazy_func_t<int()> GET_TIME_SINCE_LAST_DEATH(0xC7034807558DDFCA);
lazy_func_t<BOOL(Player player)>
	IS_PLAYER_TARGETTING_ANYTHING(0x78CFE51896B6B8A4);
lazy_func_t<void(
	Player control, float amount, int gaitType, float speed, BOOL p4, BOOL p5)>
	SIMULATE_PLAYER_INPUT_GAIT(0x477D5D63E63ECA5D);
lazy_func_t<void(int value)> SET_PLAYER_CLOTH_LOCK_COUNTER(0x14D913B777DFF5DA);
lazy_func_t<void()> _0xB885852C39CC265D(0xB885852C39CC265D);
lazy_func_t<void()> STOP_PLAYER_TELEPORT(0xC449EDED9D73009C);
lazy_func_t<void(Player player, float normalizedValue, BOOL p2)>
	SPECIAL_ABILITY_CHARGE_NORMALIZED(0xA0696A65F009EE18);
lazy_func_t<BOOL(Player player, int p1)>
	_0xF10B44FD479D69F3(0xF10B44FD479D69F3);
lazy_func_t<void(Player player, int tintIndex)>
	SET_PLAYER_PARACHUTE_PACK_TINT_INDEX(0x93B0FB27C9A04060);
lazy_func_t<void(Player player, BOOL p1)>
	_0xFF300C7649724A0B(0xFF300C7649724A0B);
lazy_func_t<void(Player player, int team)> SET_PLAYER_TEAM(0x0299FA38396A4940);
lazy_func_t<Any(Player player, BOOL toggle)>
	SET_PLAYER_CAN_USE_COVER(0xD465A8599DFF6814);
lazy_func_t<BOOL()> _IS_PLAYER_CAM_CONTROL_DISABLED(0x7C814D2FB49F40C0);
lazy_func_t<void(Player player)>
	CLEAR_PLAYER_PARACHUTE_MODEL_OVERRIDE(0x8753997EB5F6EE3F);
lazy_func_t<void(Player player, BOOL toggle)>
	DISABLE_PLAYER_FIRING(0x5E6CC07646BBEAB8);
lazy_func_t<void(Player player, BOOL p1, BOOL p2)>
	SPECIAL_ABILITY_CHARGE_SMALL(0x2E7B9B683481687D);
lazy_func_t<void(Player player, int p1, BOOL p2)>
	SPECIAL_ABILITY_CHARGE_ABSOLUTE(0xB7B0870EB531D08D);
lazy_func_t<void(Player player, int p1)> _SWITCH_CRIME_TYPE(0x9A987297ED8BD838);
lazy_func_t<BOOL(Player player)> IS_PLAYER_CLIMBING(0x95E8F73DC65EFB9C);
lazy_func_t<int(int achId)> _GET_ACHIEVEMENT_PROGRESSION(0x1C186837D0619335);
lazy_func_t<Any(Player player, BOOL p2)>
	REMOVE_PLAYER_HELMET(0xF3AC26D3CC576528);
lazy_func_t<void(
	Player player,
	float x,
	float y,
	float z,
	float heading,
	BOOL p5,
	BOOL p6,
	BOOL p7)>
	START_PLAYER_TELEPORT(0xAD15F075A4DA0FDE);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_DISABLE_AMBIENT_MELEE_MOVE(0x2E8AABFA40A84F8C);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_AUTO_GIVE_PARACHUTE_WHEN_ENTER_PLANE(0x9F343285A00B4BB6);
lazy_func_t<BOOL(Player player)>
	ARE_PLAYER_STARS_GREYED_OUT(0x0A6EB355EE14A2DB);
lazy_func_t<BOOL(Player player, Entity entity)>
	IS_PLAYER_FREE_AIMING_AT_ENTITY(0x3C06B5C839B38F7B);
lazy_func_t<void()> _0x0032A6DBA562C518(0x0032A6DBA562C518);
lazy_func_t<int(Player player)> GET_PLAYER_GROUP(0x0D127585F77030AF);
lazy_func_t<BOOL(Player player)>
	IS_SPECIAL_ABILITY_METER_FULL(0x05A1FE504B7F2587);
lazy_func_t<void(Player player, BOOL toggle)>
	SET_DISPATCH_COPS_FOR_PLAYER(0xDB172424876553F4);
lazy_func_t<void(Player player, BOOL toggle, int flags)>
	SET_PLAYER_CONTROL(0x8D32347D6D4C40A2);
lazy_func_t<void(Player player)>
	CLEAR_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(0x10C54E4389C12B42);
lazy_func_t<void(BOOL p0, ScrHandle p1)>
	_0x5DC40A8869C22141(0x5DC40A8869C22141);
lazy_func_t<BOOL()> IS_PLAYER_LOGGING_IN_NP(0x74556E1420867ECA);
lazy_func_t<void(Player player)>
	SPECIAL_ABILITY_DEACTIVATE_FAST(0x9CB5CE07A3968D5A);
lazy_func_t<BOOL(Player player)> IS_SPECIAL_ABILITY_ACTIVE(0x3E5F7FC85D854E15);
lazy_func_t<BOOL(Player player, int wantedLevel)>
	IS_PLAYER_WANTED_LEVEL_GREATER(0x238DB2A2C23EE9EF);
lazy_func_t<void(Player player, Hash model)>
	SET_PLAYER_PARACHUTE_PACK_MODEL_OVERRIDE(0xDC80A4C2F18A2B64);
lazy_func_t<int()> GET_NUMBER_OF_PLAYERS(0x407C7F91DDB46C16);
lazy_func_t<BOOL(Player player)> CAN_PLAYER_START_MISSION(0xDE7465A27D403C06);
lazy_func_t<void(int maxWantedLevel)> SET_MAX_WANTED_LEVEL(0xAA5F02DB48D704B9);
lazy_func_t<Player(int value)> INT_TO_PLAYERINDEX(0x41BD2A6B006AF756);
lazy_func_t<BOOL(int achievement)>
	HAS_ACHIEVEMENT_BEEN_PASSED(0x867365E111A3B6EB);
lazy_func_t<void(Player player, BOOL p1)>
	SPECIAL_ABILITY_DEPLETE_METER(0x1D506DBBBC51E64B);
}} // namespace PLAYER::
namespace CUTSCENE { namespace {
lazy_func_t<void(BOOL p0)> STOP_CUTSCENE(0xC7272775B4DC786E);
lazy_func_t<void(float p0, float p1, float p2, float p3, float p4, float p5)>
	SET_CUTSCENE_TRIGGER_AREA(0x9896CE4721BE84BA);
lazy_func_t<void(BOOL p0)> _0x2F137B508DE238F2(0x2F137B508DE238F2);
lazy_func_t<void(const char *cutsceneEntName, Ped ped, Hash modelHash)>
	_0x2A56C06EBEF2B0D9(0x2A56C06EBEF2B0D9);
lazy_func_t<BOOL(int p0)> _0x71B74D2AE19338D0(0x71B74D2AE19338D0);
lazy_func_t<void(const char *p0, Any p1, Any p2)>
	_0x4C61C75BEE8184C2(0x4C61C75BEE8184C2);
lazy_func_t<BOOL(const char *cutsceneName)>
	_0x4CEBC1ED31E8925E(0x4CEBC1ED31E8925E);
lazy_func_t<void(BOOL p0)> _0x06EE9048FD080382(0x06EE9048FD080382);
lazy_func_t<void(float x, float y, float z, int p3)>
	START_CUTSCENE_AT_COORDS(0x1C9ADDA3244A1FBF);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)>
	_0x011883F41211432A(0x011883F41211432A);
lazy_func_t<BOOL(Any *p0)> _0xA1C996C2A744262E(0xA1C996C2A744262E);
lazy_func_t<int()> GET_CUTSCENE_TIME(0xE625BEABBAFFDAB9);
lazy_func_t<BOOL()> HAS_CUTSCENE_FINISHED(0x7C0A893088881D57);
lazy_func_t<BOOL(const char *cutsceneEntName, Hash modelHash)>
	CAN_SET_EXIT_STATE_FOR_REGISTERED_ENTITY(0x4C6A6451C79E4662);
lazy_func_t<BOOL(BOOL p0)> CAN_SET_EXIT_STATE_FOR_CAMERA(0xB2CBCD0930DFB420);
lazy_func_t<void(BOOL p0)> _0xE36A98D8AB3D3C66(0xE36A98D8AB3D3C66);
lazy_func_t<BOOL(const char *cutsceneName)>
	HAS_THIS_CUTSCENE_LOADED(0x228D3D94F8A11C3C);
lazy_func_t<void(int p0)> _0x8D9DF6ECA8768583(0x8D9DF6ECA8768583);
lazy_func_t<void(BOOL p0, BOOL p1, BOOL p2, BOOL p3)>
	SET_CUTSCENE_FADE_VALUES(0x8093F23ABACCC7D4);
lazy_func_t<
	void(const char *cutsceneEntName, int p1, int p2, int p3, Hash modelHash)>
	SET_CUTSCENE_PED_COMPONENT_VARIATION(0xBA01E7B6DEEFBBC9);
lazy_func_t<BOOL()> _0xB56BBBCC2955D9CB(0xB56BBBCC2955D9CB);
lazy_func_t<void()> STOP_CUTSCENE_IMMEDIATELY(0xD220BDD222AC4A1E);
lazy_func_t<Entity(const char *cutsceneEntName, Hash modelHash)>
	GET_ENTITY_INDEX_OF_CUTSCENE_ENTITY(0x0A2E9FDB9A8C62F6);
lazy_func_t<BOOL(const char *cutsceneEntName, Hash modelHash)>
	DOES_CUTSCENE_ENTITY_EXIST(0x499EF20C5DB25C59);
lazy_func_t<void()> REMOVE_CUTSCENE(0x440AF51A3462B86F);
lazy_func_t<void(Any *p0)> _0xD00D76A7DFC9D852(0xD00D76A7DFC9D852);
lazy_func_t<Any(Any *p0)> _0x0ABC54DE641DC0FC(0x0ABC54DE641DC0FC);
lazy_func_t<void(int p0)> START_CUTSCENE(0x186D5CB5E7B0FF7B);
lazy_func_t<void(float x, float y, float z, float p3, int p4)>
	SET_CUTSCENE_ORIGIN(0xB812B3FD1C01CF27);
lazy_func_t<BOOL()> IS_CUTSCENE_ACTIVE(0x991251AFC3981F84);
lazy_func_t<void(const char *cutsceneName, int p1)>
	REQUEST_CUTSCENE(0x7A86743F475D9E09);
lazy_func_t<void(const char *cutsceneName, int p1, int p2)>
	_REQUEST_CUTSCENE_EX(0xC23DE0E91C30B58C);
lazy_func_t<void(
	Ped cutscenePed,
	const char *cutsceneEntName,
	int p2,
	Hash modelHash,
	int p4)>
	REGISTER_ENTITY_FOR_CUTSCENE(0xE40C1C56DF95C2E8);
lazy_func_t<Entity(const char *cutsceneEntName, Hash modelHash)>
	GET_ENTITY_INDEX_OF_REGISTERED_ENTITY(0xC0741A26499654CD);
lazy_func_t<BOOL(const char *cutsceneEntName, Hash modelHash)>
	CAN_SET_ENTER_STATE_FOR_REGISTERED_ENTITY(0x645D0B458D8E17B5);
lazy_func_t<void(BOOL toggle)> _0xC61B86C9F61EB404(0xC61B86C9F61EB404);
lazy_func_t<int()> _0xA0FE76168A189DDB(0xA0FE76168A189DDB);
lazy_func_t<
	void(const char *cutsceneEntName, int p1, int p2, int p3, Hash modelHash)>
	SET_CUTSCENE_PED_PROP_VARIATION(0x0546524ADE2E9723);
lazy_func_t<int()> GET_CUTSCENE_SECTION_PLAYING(0x49010A6A396553D8);
lazy_func_t<int()> _0x583DF8E3D4AFBD98(0x583DF8E3D4AFBD98);
lazy_func_t<Hash *()> _0x708BDD8CD795B043(0x708BDD8CD795B043);
lazy_func_t<BOOL()> IS_CUTSCENE_PLAYING(0xD3C2E180A40F031E);
lazy_func_t<void(BOOL p0, BOOL p1, BOOL p2, BOOL p3)>
	_0x20746F7B1032A3C7(0x20746F7B1032A3C7);
lazy_func_t<void(Any *p0)> _0x06A3524161C502BA(0x06A3524161C502BA);
lazy_func_t<BOOL()> WAS_CUTSCENE_SKIPPED(0x40C8656EDAEDD569);
lazy_func_t<void(Hash modelHash)> _0x7F96F23FA9B73327(0x7F96F23FA9B73327);
lazy_func_t<BOOL()> _0x5EDEF0CF8C1DAB3C(0x5EDEF0CF8C1DAB3C);
lazy_func_t<void(BOOL p0)> _0x41FAA8FB2ECE8720(0x41FAA8FB2ECE8720);
lazy_func_t<void()> REGISTER_SYNCHRONISED_SCRIPT_SPEECH(0x2131046957F31B04);
lazy_func_t<BOOL()> HAS_CUTSCENE_LOADED(0xC59F528E9AB9F339);
lazy_func_t<int()> GET_CUTSCENE_TOTAL_DURATION(0xEE53B14A19E480D4);
}} // namespace CUTSCENE::
namespace GRAPHICS { namespace {
lazy_func_t<BOOL()> _0xA67C35C56EB1BD9D(0xA67C35C56EB1BD9D);
lazy_func_t<void(BOOL p0)>
	SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(0xEEC4047028426510);
lazy_func_t<BOOL(
	Vehicle vehicle,
	Ped ped,
	int boneIndex,
	float x1,
	float x2,
	float x3,
	float y1,
	float y2,
	float y3,
	float z1,
	float z2,
	float z3,
	float scale,
	Any p13,
	int alpha)>
	_ADD_CLAN_DECAL_TO_VEHICLE(0x428BDCB9DA58DA53);
lazy_func_t<void(float alpha)>
	SET_PARTICLE_FX_NON_LOOPED_ALPHA(0x77168D722C58B2FC);
lazy_func_t<void(Object obj, float x, float y, float z)>
	REMOVE_DECALS_FROM_OBJECT_FACING(0xA6F6F70FDC6D144C);
lazy_func_t<void(float p0)> _0xBDEB86F4D5809204(0xBDEB86F4D5809204);
lazy_func_t<void(
	int scaleformHandle,
	float x,
	float y,
	float width,
	float height,
	int red,
	int green,
	int blue,
	int alpha,
	int unk)>
	DRAW_SCALEFORM_MOVIE(0x54972ADAF0294A93);
lazy_func_t<void()> _0x6A12D88881435DCA(0x6A12D88881435DCA);
lazy_func_t<void(float x, float y, float p2, float p3)>
	_SCREEN_DRAW_POSITION_RATIO(0xF5A2C681787E579D);
lazy_func_t<float(BOOL b)> _GET_ASPECT_RATIO(0xF1307EF624A80D87);
lazy_func_t<BOOL()> GET_IS_HIDEF(0x84ED31191CC5D2C9);
lazy_func_t<float()> GET_TV_VOLUME(0x2170813D3DD8661B);
lazy_func_t<void(BOOL p0)> _0x6DDBF9DFFC4AC080(0x6DDBF9DFFC4AC080);
lazy_func_t<void()> _0xE1C8709406F2C41C(0xE1C8709406F2C41C);
lazy_func_t<void(Entity entity)>
	REMOVE_PARTICLE_FX_FROM_ENTITY(0xB8FEAEEBCC127425);
lazy_func_t<BOOL(const char *scaleformName)>
	_HAS_NAMED_SCALEFORM_MOVIE_LOADED(0x0C1C5D756FB5F337);
lazy_func_t<BOOL(int hudComponent, const char *functionName)>
	_BEGIN_SCALEFORM_MOVIE_METHOD_HUD_COMPONENT(0x98C494FD5BDFBFD5);
lazy_func_t<BOOL(int scaleform, const char *functionName)>
	BEGIN_SCALEFORM_MOVIE_METHOD(0xF6E48914C7A8694E);
lazy_func_t<BOOL(const char *functionName)>
	_BEGIN_SCALEFORM_MOVIE_METHOD_N(0xAB58C27C2E6123C6);
lazy_func_t<void(Any p0, const char *p1, Any p2)>
	_0x2201C576FACAEBE8(0x2201C576FACAEBE8);
lazy_func_t<void(BOOL p0)> _0xDC459CFA0CCE245B(0xDC459CFA0CCE245B);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)>
	_0x6D955F6A9E0295B1(0x6D955F6A9E0295B1);
lazy_func_t<void(BOOL p0)> _0xE63D7C6EECECB66B(0xE63D7C6EECECB66B);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	WASH_DECALS_IN_RANGE(0x9C30613D50A6ADEF);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	_0xBE197EAA669238F4(0xBE197EAA669238F4);
lazy_func_t<BOOL(float transitionTime)>
	_TRANSITION_FROM_BLURRED(0xEFACC8AEF94430D5);
lazy_func_t<Object(
	int decalType,
	float posX,
	float posY,
	float posZ,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	float p9,
	float width,
	float height,
	float rCoef,
	float gCoef,
	float bCoef,
	float opacity,
	float timeout,
	BOOL p17,
	BOOL p18,
	BOOL p19)>
	ADD_DECAL(0xB302244A1839BDAD);
lazy_func_t<void(const char *p0)> _0xD7021272EB0A451E(0xD7021272EB0A451E);
lazy_func_t<BOOL(const char *p0, Any *p1, Any *p2, BOOL p3)>
	_0x4862437A486F91B0(0x4862437A486F91B0);
lazy_func_t<void(
	float posX,
	float posY,
	float posZ,
	float dirX,
	float dirY,
	float dirZ,
	int colorR,
	int colorG,
	int colorB,
	float distance,
	float brightness,
	float hardness,
	float radius,
	float falloff)>
	DRAW_SPOT_LIGHT(0xD0F64B265C8C8B33);
lazy_func_t<void(BOOL p0)> _0xEF398BEEE4EF45F9(0xEF398BEEE4EF45F9);
lazy_func_t<
	void(float p0, float p1, float fadeIn, float duration, float fadeOut)>
	SET_FLASH(0x0AB84296FED9CFC6);
lazy_func_t<void()> _0x92CCC17A7A2285DA(0x92CCC17A7A2285DA);
lazy_func_t<void(Any p0, float p1)> _0xD7D0B00177485411(0xD7D0B00177485411);
lazy_func_t<void()> _0xD9454B5752C857DC(0xD9454B5752C857DC);
lazy_func_t<BOOL(Hash tvChannel)> _LOAD_TV_CHANNEL(0x0AD973CA1E077B60);
lazy_func_t<void(const char *p0)> _0xBF59707B3E5ED531(0xBF59707B3E5ED531);
lazy_func_t<void(
	const char *text,
	float x,
	float y,
	float z,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_DEBUG_TEXT(0x3903E216620488E8);
lazy_func_t<void(float p0)> _0x5F0F3F56635809EF(0x5F0F3F56635809EF);
lazy_func_t<void()> _0xDE81239437E8C5A8(0xDE81239437E8C5A8);
lazy_func_t<BOOL(Object decal)> IS_DECAL_ALIVE(0xC694D74949CAFD0C);
lazy_func_t<void(Any p0)> _0xD1C55B110E4DF534(0xD1C55B110E4DF534);
lazy_func_t<Any()> _0xA4819F5E23E2FFAD(0xA4819F5E23E2FFAD);
lazy_func_t<
	int(const char *effectName,
		float xPos,
		float yPos,
		float zPos,
		float xRot,
		float yRot,
		float zRot,
		float scale,
		BOOL xAxis,
		BOOL yAxis,
		BOOL zAxis)>
	START_PARTICLE_FX_NON_LOOPED_AT_COORD(0x25129531F77B9ED3);
lazy_func_t<void(float x, float y, float z, float range)>
	REMOVE_DECALS_IN_RANGE(0x5D6B2D4830A67C62);
lazy_func_t<void()> CLEAR_TIMECYCLE_MODIFIER(0x0F07E7745A236711);
lazy_func_t<int(const char *scaleformName)>
	_REQUEST_SCALEFORM_MOVIE_INTERACTIVE(0xBD06C611BB9048C2);
lazy_func_t<void(float p0, float p1, float *p2, float *p3)>
	_0x6DD8F5AA635EB4B2(0x6DD8F5AA635EB4B2);
lazy_func_t<void(float p0)> _0xF78B803082D4386F(0xF78B803082D4386F);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	FADE_DECALS_IN_RANGE(0xD77EDADB0420E6E0);
lazy_func_t<void()> _0x98EDF76A7271E4F2(0x98EDF76A7271E4F2);
lazy_func_t<void(int *x, int *y)>
	_GET_ACTIVE_SCREEN_RESOLUTION(0x873C9F3104101DD3);
lazy_func_t<int()> CREATE_TRACKED_POINT(0xE2C9439ED45DEA60);
lazy_func_t<void()> PUSH_TIMECYCLE_MODIFIER(0x58F735290861E6B4);
lazy_func_t<void(BOOL p0)> _0xA356990E161C9E65(0xA356990E161C9E65);
lazy_func_t<void(Entity entity, int red, int green, int blue, int alpha)>
	SET_ENTITY_ICON_COLOR(0x1D5F595CCAE2E238);
lazy_func_t<void(Entity entity)> ATTACH_TV_AUDIO_TO_ENTITY(0x845BAD77CC770633);
lazy_func_t<void(BOOL p0)> SET_PARTICLE_FX_BLOOD_SCALE(0x5F6DF3D92271E8A1);
lazy_func_t<void(BOOL p0)> _0x1BBC135A4D25EDDE(0x1BBC135A4D25EDDE);
lazy_func_t<int()> _GET_MAXIMUM_NUMBER_OF_PHOTOS_2(0xDC54A7AF8B3A14EF);
lazy_func_t<void(float p0)> _0xC9B18B4619F48F7B(0xC9B18B4619F48F7B);
lazy_func_t<void(BOOL p0)> _0x02369D5C8A51FDCF(0x02369D5C8A51FDCF);
lazy_func_t<void()> _0x346EF3ECAAAB149E(0x346EF3ECAAAB149E);
lazy_func_t<void(int checkpoint, float p0)>
	_SET_CHECKPOINT_SCALE(0x4B5B4DA5D79F1943);
lazy_func_t<void(float p0)> _0xBB90E12CAC1DAB25(0xBB90E12CAC1DAB25);
lazy_func_t<void()> _0x7A42B2E236E71415(0x7A42B2E236E71415);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_DEBUG_BOX(0x083A2CA4F2E573BD);
lazy_func_t<BOOL(
	const char *effectName,
	float xPos,
	float yPos,
	float zPos,
	float xRot,
	float yRot,
	float zRot,
	float scale,
	BOOL xAxis,
	BOOL yAxis,
	BOOL zAxis)>
	_START_PARTICLE_FX_NON_LOOPED_AT_COORD_2(0xF56B8137DF10135D);
lazy_func_t<void(
	int scaleform,
	const char *functionName,
	float floatParam1,
	float floatParam2,
	float floatParam3,
	float floatParam4,
	float floatParam5,
	const char *stringParam1,
	const char *stringParam2,
	const char *stringParam3,
	const char *stringParam4,
	const char *stringParam5)>
	_CALL_SCALEFORM_MOVIE_FUNCTION_MIXED_PARAMS(0xEF662D8D57E290B1);
lazy_func_t<void(BOOL value)>
	_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_BOOL(0xC58424BA936EB458);
lazy_func_t<void(BOOL toggle)> SET_SEETHROUGH(0x7E08924259E08CE0);
lazy_func_t<
	BOOL(const char *p0, Ped ped, int p2, float posX, float posY, float posZ)>
	_DRAW_SHOWROOM(0x98C4FE6EC34154CA);
lazy_func_t<BOOL()> _0x1DD2139A9A20DCE8(0x1DD2139A9A20DCE8);
lazy_func_t<
	int(const char *effectName,
		float x,
		float y,
		float z,
		float xRot,
		float yRot,
		float zRot,
		float scale,
		BOOL xAxis,
		BOOL yAxis,
		BOOL zAxis,
		BOOL p11)>
	START_PARTICLE_FX_LOOPED_AT_COORD(0xE184F4F0DC5910E7);
lazy_func_t<void(BOOL p0)> _0x0E4299C549F0D1F1(0x0E4299C549F0D1F1);
lazy_func_t<BOOL(int scaleformHandle)>
	HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(0x8217150E1217EBFD);
lazy_func_t<void(const char *effectName)>
	_STOP_SCREEN_EFFECT(0x068E835A1D0DC0E3);
lazy_func_t<void(Any p0, Any p1)> _0xDBAA5EC848BA2D46(0xDBAA5EC848BA2D46);
lazy_func_t<void(BOOL p0)> _0x9B079E5221D984D3(0x9B079E5221D984D3);
lazy_func_t<void()> _0xA44FF770DFBC5DAE(0xA44FF770DFBC5DAE);
lazy_func_t<void(
	int scaleform,
	const char *functionName,
	float param1,
	float param2,
	float param3,
	float param4,
	float param5)>
	_CALL_SCALEFORM_MOVIE_FUNCTION_FLOAT_PARAMS(0xD0837058AE2E4BEE);
lazy_func_t<void()> END_SCALEFORM_MOVIE_METHOD(0xC6796A8FFA375E53);
lazy_func_t<void(float value)>
	_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_FLOAT(0xD69736AAE04DB51A);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_LINE(0x6B7256074AE34680);
lazy_func_t<void(Any p0, float p1, float p2, float p3, float p4)>
	_0xAE51BC858F32BA66(0xAE51BC858F32BA66);
lazy_func_t<void(float p0)> _0x54E22EA2C1956A8D(0x54E22EA2C1956A8D);
lazy_func_t<void(const char *p0)> _0xBBF327DED94E4DEB(0xBBF327DED94E4DEB);
lazy_func_t<void(float p0)> _0x949F397A288B28B3(0x949F397A288B28B3);
lazy_func_t<void(Object obj)> REMOVE_DECALS_FROM_OBJECT(0xCCF71CBDDF5B6CB9);
lazy_func_t<void(Entity entity)> _ENTITY_DESCRIPTION_TEXT(0xDEADC0DEDEADC0DE);
lazy_func_t<
	void(int checkpoint, float nearHeight, float farHeight, float radius)>
	SET_CHECKPOINT_CYLINDER_HEIGHT(0x2707AAE9D9297D89);
lazy_func_t<void(int layer)> _SET_UI_LAYER(0x61BB1D9B3A95D802);
lazy_func_t<void(BOOL p0)> _0x8CDE909A0370BB3A(0x8CDE909A0370BB3A);
lazy_func_t<void(Any p0)> SET_PARTICLE_FX_SHOOTOUT_BOAT(0x96EF97DAEB89BEF5);
lazy_func_t<void(Any *p0, Any *p1)> _0x1A8E2C8B9CF4549C(0x1A8E2C8B9CF4549C);
lazy_func_t<void(
	int scaleform,
	float posX,
	float posY,
	float posZ,
	float rotX,
	float rotY,
	float rotZ,
	float p7,
	float p8,
	float p9,
	float scaleX,
	float scaleY,
	float scaleZ,
	Any p13)>
	_DRAW_SCALEFORM_MOVIE_3D_NON_ADDITIVE(0x1CE592FDC749D6F5);
lazy_func_t<int()> GET_TV_CHANNEL(0xFC1E275A90D39995);
lazy_func_t<BOOL(const char *textureDict)>
	HAS_STREAMED_TEXTURE_DICT_LOADED(0x0145F696AAAAD2E4);
lazy_func_t<void()> _0x3669F1B198DCAA4F(0x3669F1B198DCAA4F);
lazy_func_t<void(
	Any p0, BOOL p1, float p2, float p3, float p4, float p5, BOOL p6, float p7)>
	_0xD2936CAB8B58FCBD(0xD2936CAB8B58FCBD);
lazy_func_t<void(BOOL p0)> _0xA51C4B86B71652AE(0xA51C4B86B71652AE);
lazy_func_t<void(int p0)> _0xEC52C631A1831C03(0xEC52C631A1831C03);
lazy_func_t<void(
	float xPos,
	float yPos,
	float xScale,
	float yScale,
	float rotation,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_TV_CHANNEL(0xFDDC2B4ED3C69DF0);
lazy_func_t<void(BOOL toggle)> SET_TV_AUDIO_FRONTEND(0x113D2C5DC57E1774);
lazy_func_t<BOOL(float transitionTime)>
	_TRANSITION_TO_BLURRED(0xA328A24AAA6B7FDC);
lazy_func_t<BOOL(
	const char *effectName,
	Entity entity,
	float offsetX,
	float offsetY,
	float offsetZ,
	float rotX,
	float rotY,
	float rotZ,
	float scale,
	BOOL axisX,
	BOOL axisY,
	BOOL axisZ)>
	_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_2(0xC95EB1DB6E92113D);
lazy_func_t<BOOL(const char *functionName)>
	_BEGIN_SCALEFORM_MOVIE_METHOD_V(0xB9449845F73F5E9C);
lazy_func_t<int(BOOL p0)> _0xF5BED327CEA362B1(0xF5BED327CEA362B1);
lazy_func_t<
	Any(float x,
		float y,
		float z,
		float groundLvl,
		float width,
		float transparency)>
	ADD_PETROL_DECAL(0x4F5212C7AD880DF8);
lazy_func_t<Any()> _0x459FD2C8D0AB78BC(0x459FD2C8D0AB78BC);
lazy_func_t<void(
	int scaleform,
	const char *functionName,
	const char *param1,
	const char *param2,
	const char *param3,
	const char *param4,
	const char *param5)>
	_CALL_SCALEFORM_MOVIE_FUNCTION_STRING_PARAMS(0x51BC1ED3CC44E8F7);
lazy_func_t<void(float p0, float p1, float p2)>
	_0x2485D34E50A22E84(0x2485D34E50A22E84);
lazy_func_t<
	void(int ptfxHandle, const char *propertyName, float amount, BOOL Id)>
	SET_PARTICLE_FX_LOOPED_EVOLUTION(0x5F0C4B5B1C393BE2);
lazy_func_t<void(float p0)> _0x27E32866E9A5C416(0x27E32866E9A5C416);
lazy_func_t<void(const char *name)>
	_RESET_PARTICLE_FX_ASSET_OLD_TO_NEW(0x89C8553DD3274AAE);
lazy_func_t<void(
	int scaleform1, int scaleform2, int red, int green, int blue, int alpha)>
	DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(0xCF537FDE4FBD4CE5);
lazy_func_t<void(int scaleform, const char *method)>
	CALL_SCALEFORM_MOVIE_METHOD(0xFBD96D87AC96D533);
lazy_func_t<BOOL(int p0)> _0x5E657EF1099EDD65(0x5E657EF1099EDD65);
lazy_func_t<BOOL(int p0)> _0x759650634F07B6B4(0x759650634F07B6B4);
lazy_func_t<BOOL(
	const char *effectName,
	Ped ped,
	float offsetX,
	float offsetY,
	float offsetZ,
	float rotX,
	float rotY,
	float rotZ,
	int boneIndex,
	float scale,
	BOOL axisX,
	BOOL axisY,
	BOOL axisZ)>
	_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE_2(0xA41B6A43642AC2CF);
lazy_func_t<
	int(const char *effectName,
		Ped ped,
		float xOffset,
		float yOffset,
		float zOffset,
		float xRot,
		float yRot,
		float zRot,
		int boneIndex,
		float scale,
		BOOL xAxis,
		BOOL yAxis,
		BOOL zAxis)>
	START_PARTICLE_FX_LOOPED_ON_PED_BONE(0xF28DA9F38CD1787C);
lazy_func_t<Any()> _0xBB0527EC6341496D(0xBB0527EC6341496D);
lazy_func_t<void(int decalType)> _0xB7ED70C49521A61D(0xB7ED70C49521A61D);
lazy_func_t<void(BOOL toggle)>
	DISABLE_VEHICLE_DISTANTLIGHTS(0xC9F98AC1884E73A2);
lazy_func_t<void(float strength)>
	SET_TIMECYCLE_MODIFIER_STRENGTH(0x82E7FFCD5B2326B3);
lazy_func_t<void(
	int scaleform,
	float posX,
	float posY,
	float posZ,
	float rotX,
	float rotY,
	float rotZ,
	float p7,
	float sharpness,
	float p9,
	float scaleX,
	float scaleY,
	float scaleZ,
	Any p13)>
	DRAW_SCALEFORM_MOVIE_3D(0x87D51D72255D4E78);
lazy_func_t<void()> _0x4AF92ACD3141D96C(0x4AF92ACD3141D96C);
lazy_func_t<void()> _0xEFABC7722293DA7C(0xEFABC7722293DA7C);
lazy_func_t<void()> _0x03FC694AE06C5A20(0x03FC694AE06C5A20);
lazy_func_t<void(float p0)> _0xB3C641F3630BF6DA(0xB3C641F3630BF6DA);
lazy_func_t<BOOL(BOOL p0)> _0x7AC24EAB6D74118D(0x7AC24EAB6D74118D);
lazy_func_t<void(BOOL Toggle)> ENABLE_ALIEN_BLOOD_VFX(0x9DCE1F0F78260875);
lazy_func_t<void()> _0x2BF72AD5B41AA739(0x2BF72AD5B41AA739);
lazy_func_t<void(const char *effectName, int duration, BOOL looped)>
	_START_SCREEN_EFFECT(0x2206BF9A37B7F724);
lazy_func_t<BOOL()> _0x7FA5D82B8F58EC06(0x7FA5D82B8F58EC06);
lazy_func_t<int()> GET_MAXIMUM_NUMBER_OF_PHOTOS(0x34D23450F028B0BF);
lazy_func_t<void(BOOL p0)> _0xC6372ECD45D73BCD(0xC6372ECD45D73BCD);
lazy_func_t<float()> GET_SAFE_ZONE_SIZE(0xBAF107B6BB2C97F0);
lazy_func_t<void()> _STOP_ALL_SCREEN_EFFECTS(0xB4EDDC19532BFB85);
lazy_func_t<void()> CLEAR_DRAW_ORIGIN(0xFF0B610F6BE0D7AF);
lazy_func_t<void(int point, float x, float y, float z, float radius)>
	SET_TRACKED_POINT_INFO(0x164ECBB3CF750CB0);
lazy_func_t<BOOL(
	const char *effectName,
	Entity entity,
	float offsetX,
	float offsetY,
	float offsetZ,
	float rotX,
	float rotY,
	float rotZ,
	float scale,
	BOOL axisX,
	BOOL axisY,
	BOOL axisZ)>
	START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(0x0D53A3B8DA0809D2);
lazy_func_t<void()> _0x0A123435A26C36CD(0x0A123435A26C36CD);
lazy_func_t<void(float p0)> _0x36F6626459D91457(0x36F6626459D91457);
lazy_func_t<void(BOOL p0)> _0x25FC3E33A31AD0C9(0x25FC3E33A31AD0C9);
lazy_func_t<void(int ptfxHandle, BOOL p1)>
	STOP_PARTICLE_FX_LOOPED(0x8F75998877616996);
lazy_func_t<void()> _0xD801CC02177FA3F1(0xD801CC02177FA3F1);
lazy_func_t<int()> _0x0C0C4E81E1AC60A0(0x0C0C4E81E1AC60A0);
lazy_func_t<int()> _GET_NUMBER_OF_PHOTOS(0x473151EBC762C6DA);
lazy_func_t<Any(Any p0)> _0xEC72C258667BE5EA(0xEC72C258667BE5EA);
lazy_func_t<void(
	float x,
	float y,
	float z,
	float size,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_DEBUG_CROSS(0x73B1189623049839);
lazy_func_t<void(int checkpoint)> DELETE_CHECKPOINT(0xF5ED37F54CD4D52E);
lazy_func_t<Any()> _0x35FB78DC42B7BD21(0x35FB78DC42B7BD21);
lazy_func_t<void()> _0x4B5CFC83122DF602(0x4B5CFC83122DF602);
lazy_func_t<void()> END_TEXT_COMMAND_SCALEFORM_STRING(0x362E2D3FE93A9959);
lazy_func_t<void(
	float posX,
	float posY,
	float posZ,
	float dirX,
	float dirY,
	float dirZ,
	int colorR,
	int colorG,
	int colorB,
	float distance,
	float brightness,
	float roundness,
	float radius,
	float falloff,
	int shadowId)>
	_DRAW_SPOT_LIGHT_WITH_SHADOW(0x5BCA583A583194DB);
lazy_func_t<Any(Any p0)> _0x9B6E70C5CEEF4EEB(0x9B6E70C5CEEF4EEB);
lazy_func_t<void(float X, float Y, float Z, float radius)>
	REMOVE_PARTICLE_FX_IN_RANGE(0xDD19FA1C6D657305);
lazy_func_t<BOOL(int scaleformHandle)>
	HAS_SCALEFORM_MOVIE_LOADED(0x85F01B8D5B90570E);
lazy_func_t<void(float value)> SET_NOISINESSOVERIDE(0xCB6A7C3BB17A0C67);
lazy_func_t<Any()> _0xE59343E9E96529E7(0xE59343E9E96529E7);
lazy_func_t<float()> IS_PARTICLE_FX_DELAYED_BLINK(0x5CCABFFCA31DDE33);
lazy_func_t<BOOL()> _0xEB3DAC2C86001E5E(0xEB3DAC2C86001E5E);
lazy_func_t<
	void(int decalType, const char *textureDict, const char *textureName)>
	_ADD_DECAL_TO_MARKER(0x8A35C742130C6080);
lazy_func_t<void(BOOL toggle)> _0x23BA6B0C2AD7B0D3(0x23BA6B0C2AD7B0D3);
lazy_func_t<void(BOOL p0, BOOL p1)> _0x1072F115DAB0717E(0x1072F115DAB0717E);
lazy_func_t<
	int(int type,
		float posX1,
		float posY1,
		float posZ1,
		float posX2,
		float posY2,
		float posZ2,
		float radius,
		int red,
		int green,
		int blue,
		int alpha,
		int reserved)>
	CREATE_CHECKPOINT(0x0134F0835AB6BFCB);
lazy_func_t<Any()> _0xB2EBE8CBC58B90E9(0xB2EBE8CBC58B90E9);
lazy_func_t<Vector3(const char *textureDict, const char *textureName)>
	GET_TEXTURE_RESOLUTION(0x35736EE65BD00C11);
lazy_func_t<void(const char *p0)> _0xB11D94BC55F41932(0xB11D94BC55F41932);
lazy_func_t<int()> GET_TIMECYCLE_MODIFIER_INDEX(0xFDF3D97C674AFB66);
lazy_func_t<void(float p0)> _0x46D1A61A21F566FC(0x46D1A61A21F566FC);
lazy_func_t<BOOL(int scaleformHandle)> _0xD1C7CB175E012964(0xD1C7CB175E012964);
lazy_func_t<void(int checkpoint, int red, int green, int blue, int alpha)>
	_SET_CHECKPOINT_ICON_RGBA(0xB9EA40907C680580);
lazy_func_t<void(Any p0)> _0x61F95E5BB3E0A8C6(0x61F95E5BB3E0A8C6);
lazy_func_t<void()> _0x302C91AB2D477F7E(0x302C91AB2D477F7E);
lazy_func_t<int(Any p0)> _0xA4664972A9B8F8BA(0xA4664972A9B8F8BA);
lazy_func_t<void(float p0)> _0x5E9DAF5A20F15908(0x5E9DAF5A20F15908);
lazy_func_t<void(
	int ptfxHandle,
	float x,
	float y,
	float z,
	float rotX,
	float rotY,
	float rotZ)>
	SET_PARTICLE_FX_LOOPED_OFFSETS(0xF7DDEBEC43483C43);
lazy_func_t<void(Vehicle vehicle, Any p1)>
	_0xD2300034310557E4(0xD2300034310557E4);
lazy_func_t<void(BOOL p0)> _0xC0416B061F2B7E5E(0xC0416B061F2B7E5E);
lazy_func_t<void(BOOL enabled)>
	SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(0x175B6BFC15CDD0C5);
lazy_func_t<void(
	float x,
	float y,
	float z,
	float radius,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_DEBUG_SPHERE(0xAAD68E1AB39DA632);
lazy_func_t<void(int *x, int *y)> GET_SCREEN_RESOLUTION(0x888D57E407E63624);
lazy_func_t<Any(Any p0)> _0x2C42340F916C5930(0x2C42340F916C5930);
lazy_func_t<int(const char *scaleformName)>
	REQUEST_SCALEFORM_MOVIE(0x11FE353CF9733E6F);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_DEBUG_LINE(0x7FDFADE676AA3CB0);
lazy_func_t<void(const char *oldAsset, const char *newAsset)>
	_SET_PARTICLE_FX_ASSET_OLD_TO_NEW(0xEA1E2D93F6F75ED9);
lazy_func_t<void()> _0x27CFB1B1E078CB2D(0x27CFB1B1E078CB2D);
lazy_func_t<BOOL(Vehicle vehicle, Any p1)>
	_DOES_VEHICLE_HAVE_DECAL(0x060D935D3981A275);
lazy_func_t<void(const char *button)>
	_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_BUTTON_NAME(0xE83A3E3557A56640);
lazy_func_t<void(Any p0)> _0x649C97D52332341A(0x649C97D52332341A);
lazy_func_t<void(int unk)> _0xE3E2C1B4C59DBC77(0xE3E2C1B4C59DBC77);
lazy_func_t<
	int(const char *effectName,
		Entity entity,
		float xOffset,
		float yOffset,
		float zOffset,
		float xRot,
		float yRot,
		float zRot,
		float scale,
		BOOL xAxis,
		BOOL yAxis,
		BOOL zAxis)>
	START_PARTICLE_FX_LOOPED_ON_ENTITY(0x1AE42C1660FD6517);
lazy_func_t<BOOL(int ptfxHandle)>
	DOES_PARTICLE_FX_LOOPED_EXIST(0x74AFEF0D2E1E409B);
lazy_func_t<void(BOOL p0)> _0x74C180030FDE4B69(0x74C180030FDE4B69);
lazy_func_t<void(const char *graphicsName)>
	_0xD2209BE128B5418C(0xD2209BE128B5418C);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int r1,
	int g1,
	int b1,
	int r2,
	int g2,
	int b2,
	int alpha1,
	int alpha2)>
	DRAW_DEBUG_LINE_WITH_TWO_COLOURS(0xD8B9A8AC5608FF94);
lazy_func_t<void()> _0x0218BA067D249DEA(0x0218BA067D249DEA);
lazy_func_t<void(BOOL p0)> _0x06F761EA47C1D3ED(0x06F761EA47C1D3ED);
lazy_func_t<void(BOOL enabled)>
	_SET_FROZEN_RENDERING_DISABLED(0xDFC252D8A3E15AB7);
lazy_func_t<BOOL(int method_return)>
	_GET_SCALEFORM_MOVIE_FUNCTION_RETURN_BOOL(0x768FF8961BA904D6);
lazy_func_t<void(BOOL toggle)> ENABLE_MOVIE_SUBTITLES(0x873FA65C778AD970);
lazy_func_t<int()> _0x90A78ECAA4E78453(0x90A78ECAA4E78453);
lazy_func_t<void(BOOL p0)> _0x0AE73D8DF3A762B2(0x0AE73D8DF3A762B2);
lazy_func_t<BOOL(const char *textureDict, BOOL p1)>
	_0x27FEB5254759CDE3(0x27FEB5254759CDE3);
lazy_func_t<void(BOOL toggle)> _SET_FORCE_VEHICLE_TRAILS(0x4CC7F0FEA5283FE0);
lazy_func_t<Any(Any p0)> _0xE791DF1F73ED2C8B(0xE791DF1F73ED2C8B);
lazy_func_t<void(BOOL toggle)> SET_NIGHTVISION(0x18F621F7A5B1F85D);
lazy_func_t<
	void(int scaleform, int red, int green, int blue, int alpha, int unk)>
	DRAW_SCALEFORM_MOVIE_FULLSCREEN(0x0DF606929C105BE1);
lazy_func_t<void(Object decal)> REMOVE_DECAL(0xED3F346429CCD659);
lazy_func_t<void(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	float p9,
	float p10,
	float p11,
	float p12)>
	_0x1C4FC5752BCD8E48(0x1C4FC5752BCD8E48);
lazy_func_t<int(Any p0)> _0x1670F8D05056F257(0x1670F8D05056F257);
lazy_func_t<void(
	int checkpoint,
	float posX,
	float posY,
	float posZ,
	float unkX,
	float unkY,
	float unkZ)>
	_0xF51D36185993515D(0xF51D36185993515D);
lazy_func_t<void(float x, float y, float z, Any p3)>
	SET_DRAW_ORIGIN(0xAA0008F3BBB8F416);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0x967278682CB6967A(0x967278682CB6967A);
lazy_func_t<void(BOOL p0)> _0x108BE26959A9D9BB(0x108BE26959A9D9BB);
lazy_func_t<void(BOOL p0, BOOL p1, float p2, float p3, float p4, float p5)>
	_0xBA3D65906822BED5(0xBA3D65906822BED5);
lazy_func_t<void(float r, float g, float b)>
	SET_PARTICLE_FX_NON_LOOPED_COLOUR(0x26143A59EF48B262);
lazy_func_t<void(float p0)> _0x1600FD8CF72EBC12(0x1600FD8CF72EBC12);
lazy_func_t<void()> _END_TEXT_COMMAND_SCALEFORM_STRING_2(0xAE4E8157D9ECF087);
lazy_func_t<int(Vehicle vehicle, Any p1)>
	_0xFE26117A5841B2FF(0xFE26117A5841B2FF);
lazy_func_t<void()> POP_TIMECYCLE_MODIFIER(0x3C8938D7D872211E);
lazy_func_t<void(const char *textureDict)>
	SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(0xBE2CACCF5A8AA805);
lazy_func_t<void(BOOL toggle)> SET_NOISEOVERIDE(0xE787BF1C5CF823C9);
lazy_func_t<void(int point)> DESTROY_TRACKED_POINT(0xB25DC90BAD56CA42);
lazy_func_t<Any(float p0)> _0x02AC28F3A01FA04A(0x02AC28F3A01FA04A);
lazy_func_t<void(const char *componentType)>
	BEGIN_TEXT_COMMAND_SCALEFORM_STRING(0x80338406F3475E55);
lazy_func_t<void(
	float p0,
	float p1,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	BOOL p8)>
	_0x312342E1A4874F3F(0x312342E1A4874F3F);
lazy_func_t<BOOL()> _IS_SEETHROUGH_ACTIVE(0x44B80ABAB9D80BD3);
lazy_func_t<void(Any p0, BOOL p1)>
	SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(0xACEE6F360FC1F6B6);
lazy_func_t<void(int *scaleformHandle)>
	SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(0x1D132D614DD86811);
lazy_func_t<void(
	float x,
	float y,
	float z,
	int r,
	int g,
	int b,
	float range,
	float intensity,
	float shadow)>
	_DRAW_LIGHT_WITH_RANGE_AND_SHADOW(0xF49E9A9716A04595);
lazy_func_t<void(const char *name)>
	_USE_PARTICLE_FX_ASSET_NEXT_CALL(0x6C38AF3693A69A91);
lazy_func_t<void(float p0)> _0x99AC7F0D8B9C893D(0x99AC7F0D8B9C893D);
lazy_func_t<void(int value)>
	_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_INT(0xC3D0841A0CC546A6);
lazy_func_t<void(int hudComponent)> _REQUEST_HUD_SCALEFORM(0x9304881D6F6537EA);
lazy_func_t<BOOL(int hudComponent)>
	_HAS_HUD_SCALEFORM_LOADED(0xDF6E5987D2B4D140);
lazy_func_t<void(
	int p0,
	int p1,
	int p2,
	int p3,
	int p4,
	int p5,
	int p6,
	int p7,
	int p8,
	int p9,
	int p10,
	int p11)>
	_0x5CE62918F8D703C7(0x5CE62918F8D703C7);
lazy_func_t<void(
	int type,
	float xPos,
	float yPos,
	float zPos,
	float p4,
	int red,
	int green,
	int blue,
	int alpha)>
	_0xB1BB03742917A5D6(0xB1BB03742917A5D6);
lazy_func_t<void()> _0x851CD923176EBA7C(0x851CD923176EBA7C);
lazy_func_t<
	int(const char *effectName,
		Entity entity,
		float xOffset,
		float yOffset,
		float zOffset,
		float xRot,
		float yRot,
		float zRot,
		float scale,
		BOOL xAxis,
		BOOL yAxis,
		BOOL zAxis)>
	_START_PARTICLE_FX_LOOPED_ON_ENTITY_2(0x6F60E89A7B64EE1D);
lazy_func_t<void()> _0xEFB55E7C25D3B3BE(0xEFB55E7C25D3B3BE);
lazy_func_t<void(
	const char *text,
	float x,
	float y,
	float z,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_DEBUG_TEXT_2D(0xA3BB2E9555C05A8F);
lazy_func_t<void(const char *modifierName)>
	SET_TIMECYCLE_MODIFIER(0x2C933ABF17A1DF41);
lazy_func_t<void(float p0)> _0x1CBA05AE7BD7EE05(0x1CBA05AE7BD7EE05);
lazy_func_t<BOOL(const char *p0)> _0xF1CEA8A4198D8E9A(0xF1CEA8A4198D8E9A);
lazy_func_t<int(Any p0)> _RETURN_TWO(0x40AFB081F8ADD4EE);
lazy_func_t<Any(Entity entity, const char *icon)>
	ADD_ENTITY_ICON(0x9CD43EEE12BF4DD0);
lazy_func_t<BOOL(
	float worldX, float worldY, float worldZ, float *screenX, float *screenY)>
	GET_SCREEN_COORD_FROM_WORLD_COORD(0x34E82F05DF2974F5);
lazy_func_t<Any()> _0x7B226C785A52A0A9(0x7B226C785A52A0A9);
lazy_func_t<void(float p0)> _0x2C328AF17210F009(0x2C328AF17210F009);
lazy_func_t<const char *(int method_return)> SITTING_TV(0xE1E258829A885245);
lazy_func_t<int(int p0)> _0xCB82A0BF0E3E3265(0xCB82A0BF0E3E3265);
lazy_func_t<void(int checkpoint)> _0x615D3925E87A3B26(0x615D3925E87A3B26);
lazy_func_t<void(int x, int y)> _SCREEN_DRAW_POSITION_BEGIN(0xB8A850F20A067EB6);
lazy_func_t<void(Vehicle vehicle)>
	REMOVE_DECALS_FROM_VEHICLE(0xE91F1B65F2B48D57);
lazy_func_t<int()> _0x0D6CA79EEEBD8CA3(0x0D6CA79EEEBD8CA3);
lazy_func_t<void(Entity entity, BOOL toggle)>
	SET_ENTITY_ICON_VISIBILITY(0xE0E8BEECCA96BA31);
lazy_func_t<BOOL(int point)> IS_TRACKED_POINT_VISIBLE(0xC45CCDAAC9221CA8);
lazy_func_t<int(const char *scaleformName)>
	REQUEST_SCALEFORM_MOVIE_INSTANCE(0xC514489CFB8AF806);
lazy_func_t<void(BOOL enable)> _SET_BLACKOUT(0x1268615ACE24D504);
lazy_func_t<void(Any *p0)> _0x5096FD9CCB49056D(0x5096FD9CCB49056D);
lazy_func_t<void(
	int p0,
	int p1,
	int p2,
	int p3,
	int p4,
	int p5,
	int p6,
	int p7,
	int p8,
	int p9,
	int p10,
	int p11)>
	_0x12995F2E53FFA601(0x12995F2E53FFA601);
lazy_func_t<void(BOOL toggle)> ENABLE_CLOWN_BLOOD_VFX(0xD821490579791273);
lazy_func_t<void(BOOL p0)> _0xA46B73FAA3460AE1(0xA46B73FAA3460AE1);
lazy_func_t<float(int decal)> GET_DECAL_WASH_LEVEL(0x323F647679A09103);
lazy_func_t<void(
	float x, float y, float width, float height, int r, int g, int b, int a)>
	DRAW_RECT(0x3A618A217E5154F0);
lazy_func_t<int(const char *movieMeshSetName)>
	LOAD_MOVIE_MESH_SET(0xB66064452270E8F1);
lazy_func_t<void(float p0)> _0xE2892E7E55D7073A(0xE2892E7E55D7073A);
lazy_func_t<void()> _0x14FC5833464340A8(0x14FC5833464340A8);
lazy_func_t<BOOL()> _0xD3A10FC7FD8D98CD(0xD3A10FC7FD8D98CD);
lazy_func_t<BOOL(const char *effectName)>
	_GET_SCREEN_EFFECT_IS_ACTIVE(0x36AD3E690DA5ACEB);
lazy_func_t<void()> _0x1612C45F9E3E0D44(0x1612C45F9E3E0D44);
lazy_func_t<void(int ptfxHandle, float scale)>
	SET_PARTICLE_FX_LOOPED_SCALE(0xB44250AAA456492D);
lazy_func_t<void(Any *p0)> _0x2A2A52824DB96700(0x2A2A52824DB96700);
lazy_func_t<void(float volume)> SET_TV_VOLUME(0x2982BF73F66E9DDC);
lazy_func_t<void(BOOL p0)> _0xCA4AE345A153D573(0xCA4AE345A153D573);
lazy_func_t<void(Any p0)> _0xBEB3D46BB7F043C0(0xBEB3D46BB7F043C0);
lazy_func_t<void()> _0x0A46AF8A78DC5E0A(0x0A46AF8A78DC5E0A);
lazy_func_t<void(
	float posX,
	float posY,
	float posZ,
	int colorR,
	int colorG,
	int colorB,
	float range,
	float intensity)>
	DRAW_LIGHT_WITH_RANGE(0xF2A1B2771A01DBD4);
lazy_func_t<void(
	int type,
	float posX,
	float posY,
	float posZ,
	float dirX,
	float dirY,
	float dirZ,
	float rotX,
	float rotY,
	float rotZ,
	float scaleX,
	float scaleY,
	float scaleZ,
	int red,
	int green,
	int blue,
	int alpha,
	BOOL bobUpAndDown,
	BOOL faceCamera,
	int p19,
	BOOL rotate,
	const char *textureDict,
	const char *textureName,
	BOOL drawOnEnts)>
	DRAW_MARKER(0x28477EC23D892089);
lazy_func_t<void(int movieMeshSet)> RELEASE_MOVIE_MESH_SET(0xEB119AA014E89183);
lazy_func_t<void(int ptfxHandle, float r, float g, float b, BOOL p4)>
	SET_PARTICLE_FX_LOOPED_COLOUR(0x7F8F65877F88783B);
lazy_func_t<void(BOOL toggle)>
	_SET_FORCE_PED_FOOTSTEPS_TRACKS(0xAEEDAD1420C65CC0);
lazy_func_t<void(Any p0)> _0x15E33297C3E8DC60(0x15E33297C3E8DC60);
lazy_func_t<void(const char *value)>
	_PUSH_SCALEFORM_MOVIE_METHOD_PARAMETER_STRING(0xBA7148484BD90365);
lazy_func_t<void()> _0xC35A6D07C93802B2(0xC35A6D07C93802B2);
lazy_func_t<void()> _0x27CB772218215325(0x27CB772218215325);
lazy_func_t<void(float p0, float p1, float p2, float p3, float p4)>
	_0x9CFDD90B2B844BF7(0x9CFDD90B2B844BF7);
lazy_func_t<
	int(const char *effectName,
		Entity entity,
		float xOffset,
		float yOffset,
		float zOffset,
		float xRot,
		float yRot,
		float zRot,
		int boneIndex,
		float scale,
		BOOL xAxis,
		BOOL yAxis,
		BOOL zAxis)>
	_START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(0xC6EB449E33977F0B);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	float x3,
	float y3,
	float z3,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_POLY(0xAC26716048436851);
lazy_func_t<void(Any p0, Any p1)> MOVE_VEHICLE_DECALS(0x84C8D7C2D30D3280);
lazy_func_t<void(int TV_Channel, const char *VideoSequence, BOOL Restart)>
	_LOAD_TV_CHANNEL_SEQUENCE(0xF7B38B8305F1FE8B);
lazy_func_t<void(
	const char *textureDict,
	const char *textureName,
	float screenX,
	float screenY,
	float width,
	float height,
	float heading,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_SPRITE(0xE7FFAE5EBF23D890);
lazy_func_t<void(int ptfxHandle, float range)>
	_SET_PARTICLE_FX_LOOPED_RANGE(0xDCB194B85EF7B541);
lazy_func_t<void(int scaleform, BOOL toggle)>
	SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(0x6D8EB211944DCE08);
lazy_func_t<void(int channel)> SET_TV_CHANNEL(0xBAABBB23EB6E484E);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	int red,
	int green,
	int blue,
	int alpha)>
	DRAW_BOX(0xD3A9971CADAC7252);
lazy_func_t<BOOL(BOOL p0)> _0x2A893980E96B659A(0x2A893980E96B659A);
lazy_func_t<void()> _0x5DEBD9C4DC995692(0x5DEBD9C4DC995692);
lazy_func_t<Any()> _0xBCEDB009461DA156(0xBCEDB009461DA156);
lazy_func_t<BOOL(
	const char *effectName,
	Ped ped,
	float offsetX,
	float offsetY,
	float offsetZ,
	float rotX,
	float rotY,
	float rotZ,
	int boneIndex,
	float scale,
	BOOL axisX,
	BOOL axisY,
	BOOL axisZ)>
	START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(0x0E7E72961BA18619);
lazy_func_t<
	int(const char *effectName,
		Entity entity,
		float xOffset,
		float yOffset,
		float zOffset,
		float xRot,
		float yRot,
		float zRot,
		int boneIndex,
		float scale,
		BOOL xAxis,
		BOOL yAxis,
		BOOL zAxis)>
	_START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE_2(0xDDE23F30CC5A0F03);
lazy_func_t<int()> _END_SCALEFORM_MOVIE_METHOD_RETURN(0xC50AA39A577AF886);
lazy_func_t<BOOL(int p0)> _0x3DEC726C25A11BAC(0x3DEC726C25A11BAC);
lazy_func_t<void(BOOL p0)> _0x22A249A53034450A(0x22A249A53034450A);
lazy_func_t<BOOL()> GET_IS_WIDESCREEN(0x30CF4BDA4FCB1905);
lazy_func_t<void(BOOL p0)> _0xD39D13C9FEBF0511(0xD39D13C9FEBF0511);
lazy_func_t<int(int method_return)>
	_GET_SCALEFORM_MOVIE_FUNCTION_RETURN_INT(0x2DE7EFA66B906036);
lazy_func_t<void(int ptfxHandle, BOOL p1)>
	REMOVE_PARTICLE_FX(0xC401503DFE8D53CF);
lazy_func_t<void(int ptfxHandle, float alpha)>
	SET_PARTICLE_FX_LOOPED_ALPHA(0x726845132380142E);
lazy_func_t<void(Vehicle vehicle, float p1)>
	WASH_DECALS_FROM_VEHICLE(0x5B712761429DBC14);
lazy_func_t<void(const char *modifierName, float transition)>
	SET_TRANSITION_TIMECYCLE_MODIFIER(0x3BCF567485E1971C);
lazy_func_t<void(int checkpoint, int red, int green, int blue, int alpha)>
	SET_CHECKPOINT_RGBA(0x7167371E8AD747F7);
lazy_func_t<void(const char *textureDict, BOOL p1)>
	REQUEST_STREAMED_TEXTURE_DICT(0xDFA2EF8E04127DD5);
lazy_func_t<void()> _SCREEN_DRAW_POSITION_END(0xE3A3DB414A373DAB);
lazy_func_t<void(BOOL toggle)> _SET_FAR_SHADOWS_SUPPRESSED(0x80ECBC0C856D3B0B);
lazy_func_t<void(Any p0)> _0xF44A5456AC3F4F97(0xF44A5456AC3F4F97);
lazy_func_t<int()> _0x5B0316762AFD4A64(0x5B0316762AFD4A64);
lazy_func_t<BOOL()> _IS_NIGHTVISION_ACTIVE(0x2202A3F42C8E5F79);
lazy_func_t<BOOL(float xCoord, float yCoord, float zCoord, float p3)>
	_0x2F09F7976C512404(0x2F09F7976C512404);
lazy_func_t<void(BOOL p0)> _0x03300B57FCAC6DDB(0x03300B57FCAC6DDB);
}} // namespace GRAPHICS::
namespace STATS { namespace {
lazy_func_t<Any(int statSlot)> STAT_CLEAR_SLOT_FOR_RELOAD(0xEB0A72181D4AA4AD);
lazy_func_t<BOOL(Hash statName, const char *value, BOOL save)>
	STAT_SET_STRING(0xA87B2335D12531D7);
lazy_func_t<BOOL(Hash statName, Any p1, Any p2, int p3, BOOL save)>
	STAT_SET_MASKED_INT(0x7BBB1B54583ED410);
lazy_func_t<void(float p0, float p1, float p2)>
	_PLAYSTATS_AMBIENT_MISSION_CRATE_CREATED(0xAFC7E5E075A96F46);
lazy_func_t<Any()> _0xA31FD15197B192BD(0xA31FD15197B192BD);
lazy_func_t<BOOL(Hash statName, BOOL value, BOOL save)>
	STAT_SET_BOOL(0x4B33C4243DE0C432);
lazy_func_t<Hash(int index, BOOL spStat, BOOL charStat, int character)>
	_GET_PSTAT_BOOL_HASH(0x80C75307B1C42837);
lazy_func_t<BOOL(Any *p0, Any *p1)> _0x6DEE77AFF8C21BD1(0x6DEE77AFF8C21BD1);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	PLAYSTATS_ODDJOB_DONE(0x69DEA3E9DB727B4C);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	PLAYSTATS_CLOTH_CHANGE(0x34B973047A2268B9);
lazy_func_t<BOOL(Hash statName, float value, BOOL save)>
	STAT_SET_FLOAT(0x4851997F37FE9B3C);
lazy_func_t<BOOL(Hash statHash, Any *p1, Any p2, Any p3)>
	STAT_GET_DATE(0x8B0FACEFC36C824B);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0x7EEC2A316C250073(0x7EEC2A316C250073);
lazy_func_t<void(BOOL p0)> _0xD1032E482629049E(0xD1032E482629049E);
lazy_func_t<void(Any *p0, Any *p1, Any *p2, Any *p3)>
	_0xF8C54A461C3E11DC(0xF8C54A461C3E11DC);
lazy_func_t<BOOL(Any *p0, Any *p1, Any *p2)>
	_0xF1AE5DCDBFCA2721(0xF1AE5DCDBFCA2721);
lazy_func_t<void()> _0x9B4BD21D69B1E609(0x9B4BD21D69B1E609);
lazy_func_t<BOOL(Hash statName, BOOL p1)>
	STAT_SET_CURRENT_POSIX_TIME(0xC2F84B7F9C4D0C61);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	PLAYSTATS_AWARD_XP(0x46F917F6B4128FE4);
lazy_func_t<void(Any p0)> PLAYSTATS_RANK_UP(0xC7F2DE41D102BFB4);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5, Any p6)>
	PLAYSTATS_MATCH_STARTED(0xBC80E22DED931E3D);
lazy_func_t<BOOL(Any *p0, Any p1, Any *p2)>
	LEADERBOARDS2_READ_BY_RADIUS(0x5CE587FB5A42C8C4);
lazy_func_t<BOOL(Any *p0)> LEADERBOARDS2_WRITE_DATA(0xAE2206545888AE49);
lazy_func_t<void(Any p0, Any p1)> _0x0D01D20616FC73FB(0x0D01D20616FC73FB);
lazy_func_t<BOOL(Any p0)> _0x7E6946F68A38B74F(0x7E6946F68A38B74F);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0xE95C8A1875A02CA4(0xE95C8A1875A02CA4);
lazy_func_t<void(const char *cheat)>
	PLAYSTATS_CHEAT_APPLIED(0x6058665D72302D3F);
lazy_func_t<void(Any *p0, Any *p1, Any *p2, Any *p3)>
	_0x14E0B2D1AD1044E0(0x14E0B2D1AD1044E0);
lazy_func_t<BOOL(Any *p0, Any *p1)>
	LEADERBOARDS2_READ_BY_HANDLE(0xC30713A383BFBF0E);
lazy_func_t<void(Any p0)> _0xF6792800AC95350D(0xF6792800AC95350D);
lazy_func_t<BOOL(int p0, BOOL p1, int p2)> STAT_SAVE(0xE07BCA305B82D2FD);
lazy_func_t<void(Any p0)> _0x79AB33F0FBFAC40C(0x79AB33F0FBFAC40C);
lazy_func_t<BOOL(Any p0)> LEADERBOARDS_GET_CACHE_EXISTS(0x9C51349BE6CDFE2C);
lazy_func_t<Any(Any *p0)> _0x886913BBEACA68C1(0x886913BBEACA68C1);
lazy_func_t<void(Any *p0)> _0x46326E13DA4E0546(0x46326E13DA4E0546);
lazy_func_t<BOOL(Any *p0, Any *p1, Any *p2)>
	_0xC38DC1E90D22547C(0xC38DC1E90D22547C);
lazy_func_t<Any()> _0xC6E0E2616A7576BB(0xC6E0E2616A7576BB);
lazy_func_t<void(Any p0)> _0xDAC073C7901F9E15(0xDAC073C7901F9E15);
lazy_func_t<Any(Any p0)> STAT_DELETE_SLOT(0x49A49BED12794D70);
lazy_func_t<void(BOOL p0)> _0xF434A10BA01C37D0(0xF434A10BA01C37D0);
lazy_func_t<int(int p0)> _0x94F12ABF9C79E339(0x94F12ABF9C79E339);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	_0xC5BE134EC7BA96A0(0xC5BE134EC7BA96A0);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	PLAYSTATS_PROP_CHANGE(0xBA739D6D5A05D6E7);
lazy_func_t<BOOL(Hash statName, float x, float y, float z, BOOL save)>
	STAT_SET_POS(0xDB283FDE680FE72E);
lazy_func_t<BOOL(Hash statName, const char *value, BOOL save)>
	STAT_SET_USER_ID(0x8CDDF1E452BABE11);
lazy_func_t<BOOL()> _0xB1D2BB1E1631F5B1(0xB1D2BB1E1631F5B1);
lazy_func_t<void(int value)> _0x38BAAA5DD4C9D19F(0x38BAAA5DD4C9D19F);
lazy_func_t<Any()> _0xC70DDCE56D0D3A99(0xC70DDCE56D0D3A99);
lazy_func_t<int(Hash statName)> STAT_GET_NUMBER_OF_DAYS(0xE0E854F5280FB769);
lazy_func_t<int(Hash statName)> STAT_GET_NUMBER_OF_HOURS(0xF2D4B2FE415AAFC3);
lazy_func_t<void(Any *p0, Any *p1, Any *p2, Any *p3)>
	_0xF5BB8DAC426A52C0(0xF5BB8DAC426A52C0);
lazy_func_t<void(Any *p0, Any *p1, Any *p2, Any *p3)>
	_0xA736CF7FB7C5BFF4(0xA736CF7FB7C5BFF4);
lazy_func_t<BOOL(Hash statName, Any *value, int numFields, BOOL save)>
	STAT_SET_DATE(0x2C29BFB64F4FCBE4);
lazy_func_t<BOOL(Hash statHash, int *outValue, int p2)>
	STAT_GET_INT(0x767FBC2AC802EF3D);
lazy_func_t<void(Any p0, Any p1, float p2)>
	_0x0BCA1D2C47B0D269(0x0BCA1D2C47B0D269);
lazy_func_t<void(Any p0, Any p1, Any p2, Any *p3)>
	_0x6483C25849031C4F(0x6483C25849031C4F);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0xCB00196B31C39EB1(0xCB00196B31C39EB1);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3)>
	_0x2B69F5074C894811(0x2B69F5074C894811);
lazy_func_t<Any(Any p0, Any p1, Any p2)>
	LEADERBOARDS_READ_CLEAR(0x7CCE5C737A665701);
lazy_func_t<BOOL(Any *p0, Any p1, Any p2)>
	LEADERBOARDS2_READ_BY_RANK(0xBA2C7DB0C129449A);
lazy_func_t<Any(Any p0)> _0x58A651CD201D89AD(0x58A651CD201D89AD);
lazy_func_t<void(Hash statName, float value)>
	_LEADERBOARDS_DEATHS(0x428EAF89E24F6C36);
lazy_func_t<BOOL(Any p0, Any *p1, Any *p2)>
	_0x3270F67EED31FBC1(0x3270F67EED31FBC1);
lazy_func_t<BOOL(Hash statHash, BOOL *outValue, Any p2)>
	STAT_GET_BOOL(0x11B5E6D2AE73F48E);
lazy_func_t<Hash(int index, BOOL spStat, BOOL charStat, int character)>
	_GET_TUPSTAT_INT_HASH(0xD16C2AD6B8E32854);
lazy_func_t<Any(Any p0, Any p1, Any p2)>
	LEADERBOARDS_GET_COLUMN_TYPE(0xBF4FEF46DB7894D3);
lazy_func_t<BOOL(Any *p0, Any *p1, Any p2, Any *p3, Any p4, Any *p5, Any p6)>
	LEADERBOARDS2_READ_BY_ROW(0xA9CDB1E3F0A49883);
lazy_func_t<void(const char *p0, Any p1, Any p2)>
	_0x11FF1C80276097ED(0x11FF1C80276097ED);
lazy_func_t<void()> _0x047CBED6F6F8B63C(0x047CBED6F6F8B63C);
lazy_func_t<BOOL(Any p0)> _0x7F2C4CDF2E82DF4C(0x7F2C4CDF2E82DF4C);
lazy_func_t<void(int p0)> _0xA78B8FA58200DA56(0xA78B8FA58200DA56);
lazy_func_t<BOOL(Any p0, Any p1, Any p2)>
	LEADERBOARDS_READ_PENDING(0xAC392C8483342AC2);
lazy_func_t<BOOL()> _0x5EAD2BF6484852E4(0x5EAD2BF6484852E4);
lazy_func_t<void(int value)> _0xF1A1803D3476F215(0xF1A1803D3476F215);
lazy_func_t<Any()> _0xC0E0D686DDFC6EAE(0xC0E0D686DDFC6EAE);
lazy_func_t<BOOL(Any p0, Any *p1, Any p2, Any p3, Any p4)>
	STAT_GET_MASKED_INT(0x655185A06D9EEAAB);
lazy_func_t<Any()> _0xB3DA2606774A8E2D(0xB3DA2606774A8E2D);
lazy_func_t<void(Any p0, Any p1)> PLAYSTATS_FRIEND_ACTIVITY(0x0F71DE29AB2258F1);
lazy_func_t<BOOL(Any *p0, Any *p1, Any p2, BOOL p3, Any p4, Any p5)>
	LEADERBOARDS2_READ_FRIENDS_BY_ROW(0x918B101666F9CB83);
lazy_func_t<void()> _0x71B008056E5692D6(0x71B008056E5692D6);
lazy_func_t<void(Any p0, float p1, Any p2)>
	_0x30A6614C1F7799B8(0x30A6614C1F7799B8);
lazy_func_t<Any(Any p0, Any *p1)> _0xDEAAF77EB3687E97(0xDEAAF77EB3687E97);
lazy_func_t<void(int p0)> _0x26D7399B9587FE89(0x26D7399B9587FE89);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	PLAYSTATS_SHOP_ITEM(0x176852ACAAC173D1);
lazy_func_t<void()> _0x6F361B8889A792A3(0x6F361B8889A792A3);
lazy_func_t<BOOL(Any *p0, Any p1, Any p2)>
	LEADERBOARDS2_READ_BY_SCORE_INT(0x7EEC7E4F6984A16A);
lazy_func_t<BOOL(Any *p0, Any *p1)> _0xC980E62E33DF1D5C(0xC980E62E33DF1D5C);
lazy_func_t<void(Hash statName, float value)>
	STAT_INCREMENT(0x9B5A68C6489E9909);
lazy_func_t<void(const char *p0, Any p1)>
	_0x5009DFD741329729(0x5009DFD741329729);
lazy_func_t<void(Any *p0)> PLAYSTATS_NPC_INVITE(0x93054C88E6AA7C44);
lazy_func_t<void(Any p0, Any p1, Any p2, float p3)>
	_0x121FB4DDDC2D5291(0x121FB4DDDC2D5291);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4)>
	PLAYSTATS_RACE_CHECKPOINT(0x9C375C315099DDE4);
lazy_func_t<void(Any p0)> _0x5688585E6D563CD8(0x5688585E6D563CD8);
lazy_func_t<BOOL(Hash statName, int value, BOOL save)>
	STAT_SET_INT(0xB3271D7AB655B441);
lazy_func_t<Hash(int index, BOOL spStat, BOOL charStat, int character)>
	_GET_PSTAT_INT_HASH(0x61E111E323419E07);
lazy_func_t<Any(Any p0, Any p1, Any p2)>
	LEADERBOARDS_GET_COLUMN_ID(0xC4B5467A1886EA7E);
lazy_func_t<void()> LEADERBOARDS_CLEAR_CACHE_DATA(0xD4B02A6B476E1FDC);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0x2E65248609523599(0x2E65248609523599);
lazy_func_t<Any(Any p0)> _0x5BD5F255321C4AAF(0x5BD5F255321C4AAF);
lazy_func_t<Any(Any *p0)> _0xCE5AA445ABA8DEE0(0xCE5AA445ABA8DEE0);
lazy_func_t<BOOL(Any p0)> STAT_SLOT_IS_LOADED(0x0D0A9F0E7BD91E3C);
lazy_func_t<BOOL()> _0xECB41AC6AB754401(0xECB41AC6AB754401);
lazy_func_t<BOOL()> _0x5A556B229A169402(0x5A556B229A169402);
lazy_func_t<BOOL(Hash statName, BOOL value, int mask, BOOL save)>
	STAT_SET_BOOL_MASKED(0x5BC62EC1937B9E5B);
lazy_func_t<void(Any *p0, Any p1, Any p2, Any p3)>
	PLAYSTATS_MISSION_CHECKPOINT(0xC900596A63978C1D);
lazy_func_t<BOOL(Any *p0)> _0xA0F93D5465B3094D(0xA0F93D5465B3094D);
lazy_func_t<BOOL(Any p0, Any *p1)> _0x34770B9CE0E03B91(0x34770B9CE0E03B91);
lazy_func_t<Any(Any p0)> LEADERBOARDS_GET_CACHE_TIME(0xF04C1C27DA35F6C8);
lazy_func_t<BOOL(Any p0)> STAT_LOAD_PENDING(0xA1750FFAFA181661);
lazy_func_t<void(Any p0)> _0xA8733668D1047B51(0xA8733668D1047B51);
lazy_func_t<BOOL(Hash statHash, float *outValue, Any p2)>
	STAT_GET_FLOAT(0xD7AE6C9C9C6AC54C);
lazy_func_t<BOOL(Hash statName, const char *str)>
	STAT_SET_LICENSE_PLATE(0x69FF13266D7296DA);
lazy_func_t<void()> _0x098760C7461724CD(0x098760C7461724CD);
lazy_func_t<Any()> _0x4C89FE2BDEB3F169(0x4C89FE2BDEB3F169);
lazy_func_t<BOOL(Any p0, Any *p1, Any *p2, Any *p3, Any p4)>
	STAT_GET_POS(0x350F82CCB186AA1B);
lazy_func_t<BOOL(Any *p0)> LEADERBOARDS_CACHE_DATA_ROW(0xB9BB18E2C40142ED);
lazy_func_t<void()> _0x629526ABA383BCAA(0x629526ABA383BCAA);
lazy_func_t<Any(Any p0)> _0xE496A53BA5F50A56(0xE496A53BA5F50A56);
lazy_func_t<BOOL(Hash statName, const char *value, BOOL save)>
	STAT_SET_GXT_LABEL(0x17695002FD8B2AE0);
lazy_func_t<void(Hash scaleformHash, int p1)>
	PLAYSTATS_WEBSITE_VISITED(0xDDF24D535060F811);
lazy_func_t<float(Any p0, Any p1)> _0x38491439B6BA7F7D(0x38491439B6BA7F7D);
lazy_func_t<BOOL(int p0)> STAT_LOAD(0xA651443F437B1CE6);
lazy_func_t<const char *(Hash statName)>
	STAT_GET_LICENSE_PLATE(0x5473D4195058B2E4);
lazy_func_t<Hash(
	int index, BOOL spStat, BOOL charStat, int character, const char *section)>
	_GET_NGSTAT_INT_HASH(0x2B4CDCA6F07FF3DA);
lazy_func_t<BOOL(Hash statName, int mask, int p2)>
	STAT_GET_BOOL_MASKED(0x10FE3F1B79F9B071);
lazy_func_t<void(Any *p0, Any p1, Any p2, BOOL p3)>
	PLAYSTATS_MISSION_STARTED(0xC19A2925C34D2231);
lazy_func_t<void(
	Any p0,
	Any p1,
	Any p2,
	Any p3,
	Any p4,
	Any p5,
	Any p6,
	Any p7,
	Any p8,
	Any p9)>
	_0xADDD1C754E2E2914(0xADDD1C754E2E2914);
lazy_func_t<void()> _0xC847B43F369AC0B5(0xC847B43F369AC0B5);
lazy_func_t<void()> _0x98E2BC1CA26287C3(0x98E2BC1CA26287C3);
lazy_func_t<BOOL(Hash statName, int p1, float *outValue)>
	_0xBED9F5693F34ED17(0xBED9F5693F34ED17);
lazy_func_t<int(Hash statName)> STAT_GET_NUMBER_OF_MINUTES(0x7583B4BE4C5A41B5);
lazy_func_t<int(Hash statName)> STAT_GET_NUMBER_OF_SECONDS(0x2CE056FF3723F00B);
lazy_func_t<void(int profileSetting, int value)>
	_STAT_SET_PROFILE_SETTING(0x68F01422BE1D838F);
lazy_func_t<void(Any p0, Any p1)> _0xA071E0ED98F91286(0xA071E0ED98F91286);
lazy_func_t<Hash(int index, BOOL spStat, BOOL charStat, int character)>
	_GET_TUPSTAT_BOOL_HASH(0xC4BB08EE7907471E);
lazy_func_t<void(Any p0, Any p1)> _0xF4FF020A08BC8863(0xF4FF020A08BC8863);
lazy_func_t<Any(Any p0, Any p1)> _0x88578F6EC36B4A3A(0x88578F6EC36B4A3A);
lazy_func_t<void()> _0xB475F27C6A994D65(0xB475F27C6A994D65);
lazy_func_t<Any()> _0x567384DFA67029E6(0x567384DFA67029E6);
lazy_func_t<BOOL(Any *p0)> _0xA5C80D8E768A9E66(0xA5C80D8E768A9E66);
lazy_func_t<Any()> STAT_SAVE_PENDING(0x7D3A583856F2C5AC);
lazy_func_t<const char *(Any p0)> STAT_GET_USER_ID(0x2365C388E393BBE2);
lazy_func_t<void(int time)> _0x5DA3A8DE8CB6226F(0x5DA3A8DE8CB6226F);
lazy_func_t<Any(Any p0, Any p1)>
	LEADERBOARDS_GET_NUMBER_OF_COLUMNS(0x117B45156D7EFF2E);
lazy_func_t<void(int value)> _0x55384438FC55AD8E(0x55384438FC55AD8E);
lazy_func_t<int(int p0)> _0xF4D8E7AC2A27758C(0xF4D8E7AC2A27758C);
lazy_func_t<Any()> _0x4FEF53183C3C6414(0x4FEF53183C3C6414);
lazy_func_t<BOOL(Any *p0, float p1, Any p2)>
	LEADERBOARDS2_READ_BY_SCORE_FLOAT(0xE662C8B759D08F3C);
lazy_func_t<void()> _0xC141B8917E0017EC(0xC141B8917E0017EC);
lazy_func_t<Any()> _0x9A62EC95AE10E011(0x9A62EC95AE10E011);
lazy_func_t<void(Any p0, Any p1)> _0x723C1CE13FBFDB67(0x723C1CE13FBFDB67);
lazy_func_t<void(Any *p0, Any p1, Any p2, BOOL p3, BOOL p4, BOOL p5)>
	PLAYSTATS_MISSION_OVER(0x7C4BB33A8CED7324);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	_0x1CAE5D2E3F9A07F0(0x1CAE5D2E3F9A07F0);
lazy_func_t<void(int p0, const char *p1)>
	_0x90D0622866E80445(0x90D0622866E80445);
lazy_func_t<Any()> LEADERBOARDS_READ_CLEAR_ALL(0xA34CB6E6F0DF4A0B);
lazy_func_t<BOOL(Any p0, Any p1, Any p2)>
	LEADERBOARDS_READ_SUCCESSFUL(0x2FB19228983E832C);
lazy_func_t<Any()> STAT_SAVE_PENDING_OR_REQUESTED(0xBBB6AD006F1BBEA3);
lazy_func_t<void(Any *p0, Any p1, Any p2, Any p3)>
	_0x71862B1D855F32E1(0x71862B1D855F32E1);
lazy_func_t<BOOL(Any p0, Any p1, Any *p2)>
	LEADERBOARDS_GET_CACHE_DATA_ROW(0x9120E8DBA3D69273);
lazy_func_t<const char *(Hash statHash, int p1)>
	STAT_GET_STRING(0xE50384ACC2C3DB74);
lazy_func_t<Hash(
	int index, BOOL spStat, BOOL charStat, int character, const char *section)>
	_GET_NGSTAT_BOOL_HASH(0xBA52FF538ED2BC71);
lazy_func_t<void(Any p0)> _0x8EC74CEB042E7CFF(0x8EC74CEB042E7CFF);
}} // namespace STATS::
namespace MOBILE { namespace {
lazy_func_t<void(int direction)> _MOVE_FINGER(0x95C9E72F3D7DEC9B);
lazy_func_t<BOOL(Entity entity)>
	CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(0x439E9BC95B7E7FBE);
lazy_func_t<BOOL(const char *name)>
	_NETWORK_SHOP_DOES_ITEM_EXIST(0xBD4D7EAF8A30F637);
lazy_func_t<void(Vector3 *rotation, Vehicle p1)>
	GET_MOBILE_PHONE_ROTATION(0x1CEFB61F193070AE);
lazy_func_t<void(BOOL toggle)>
	SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(0xF511F759238A5122);
lazy_func_t<void(BOOL Toggle)> _SET_PHONE_LEAN(0x44E44169EF70138E);
lazy_func_t<void(float p0)> _0x53F4892D18EC90A4(0x53F4892D18EC90A4);
lazy_func_t<void(float p0)> _0x15E69E2802C24B8D(0x15E69E2802C24B8D);
lazy_func_t<void(float p0)> _0xAC2890471901861C(0xAC2890471901861C);
lazy_func_t<void(float p0)> _0xD6ADE981781FCA09(0xD6ADE981781FCA09);
lazy_func_t<void()> DESTROY_MOBILE_PHONE(0x3BC861DF703E5097);
lazy_func_t<BOOL(Hash hash)>
	_NETWORK_SHOP_DOES_ITEM_EXIST_HASH(0x247F0F73A182EA0B);
lazy_func_t<void(float p0)> _0xF1E22DC13F5EEBAD(0xF1E22DC13F5EEBAD);
lazy_func_t<void(float scale)> SET_MOBILE_PHONE_SCALE(0xCBDD322A73D6D932);
lazy_func_t<void(float rotX, float rotY, float rotZ, Any p3)>
	SET_MOBILE_PHONE_ROTATION(0xBB779C0CA917E865);
lazy_func_t<void(float posX, float posY, float posZ)>
	SET_MOBILE_PHONE_POSITION(0x693A5C6D6734085B);
lazy_func_t<void(Vector3 *position)>
	GET_MOBILE_PHONE_POSITION(0x584FDFDA48805B86);
lazy_func_t<BOOL()> CAN_PHONE_BE_SEEN_ON_SCREEN(0xC4E2813898C97A4B);
lazy_func_t<void(BOOL p0, BOOL p1)> CELL_CAM_ACTIVATE(0xFDE8F069C542D126);
lazy_func_t<void(BOOL toggle)> _DISABLE_PHONE_THIS_FRAME(0x015C49A93E3E086E);
lazy_func_t<void(int p3)> CREATE_MOBILE_PHONE(0xA4E8E696C532FBC7);
lazy_func_t<void(float p0)> _0x1B0B4AEED5B9B41C(0x1B0B4AEED5B9B41C);
lazy_func_t<void(float p0)> _0x3117D84EFA60F77B(0x3117D84EFA60F77B);
lazy_func_t<void(float p0)> _0x466DA42C89865553(0x466DA42C89865553);
lazy_func_t<void(int *renderId)> GET_MOBILE_PHONE_RENDER_ID(0xB4A53E05F68B6FA1);
lazy_func_t<void(int *toggle)> _0xA2CCBE62CD4C91A4(0xA2CCBE62CD4C91A4);
}} // namespace MOBILE::
namespace APP { namespace {
lazy_func_t<const char *(const char *property)>
	APP_GET_STRING(0x749B023950D2311C);
lazy_func_t<void(const char *property, const char *value)>
	APP_SET_STRING(0x3FF2FCEC4B7721B4);
lazy_func_t<BOOL()> APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT(0x71EEE69745088DA0);
lazy_func_t<void(const char *blockName)> APP_SET_BLOCK(0x262AB456A3D21F93);
lazy_func_t<void()> APP_CLOSE_APP(0xE41C65E07A5F05FC);
lazy_func_t<Any()> APP_GET_DELETED_FILE_STATUS(0xC9853A2BE3DED1A6);
lazy_func_t<float(const char *property)> APP_GET_FLOAT(0x1514FB24C02C2322);
lazy_func_t<void(const char *property, int value)>
	APP_SET_INT(0x607E8E3D3E4F9611);
lazy_func_t<void(const char *appName)> APP_SET_APP(0xCFD0406ADAF90D2B);
lazy_func_t<void()> APP_SAVE_DATA(0x95C5D356CDA6E85F);
lazy_func_t<int()> APP_DATA_VALID(0x846AA8E7D55EE5B6);
lazy_func_t<void(const char *property, float value)>
	APP_SET_FLOAT(0x25D7687C68E0DAA4);
lazy_func_t<BOOL(const char *appName)> APP_HAS_SYNCED_DATA(0xCA52279A7271517F);
lazy_func_t<BOOL(const char *appName)> APP_DELETE_APP_DATA(0x44151AEA95C8A003);
lazy_func_t<int *(ScrHandle property)> APP_GET_INT(0xD3A58A12C77D9D4B);
lazy_func_t<void()> APP_CLEAR_BLOCK(0x5FE1DF3342DB7DBA);
lazy_func_t<void()> APP_CLOSE_BLOCK(0xE8E3FCF72EAC0EF8);
}} // namespace APP::
namespace VEHICLE { namespace {
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_QUADBIKE(0x39DAC362EE65FA28);
lazy_func_t<BOOL(Vehicle vehicle)> _IS_VEHICLE_DAMAGED(0xBCDC5017D3CE1E9E);
lazy_func_t<BOOL(Vehicle vehicle, int modType)>
	IS_TOGGLE_MOD_ON(0x84B233A8C8FC8AE7);
lazy_func_t<BOOL(Vehicle vehicle)>
	GET_IS_VEHICLE_ENGINE_RUNNING(0xAE31E7DF9B5B132E);
lazy_func_t<void(Vehicle vehicle, float p1)>
	_0xE842A9398079BD82(0xE842A9398079BD82);
lazy_func_t<int(int p0, const char *p1)>
	GET_VEHICLE_RECORDING_ID(0x21543C612379DB3C);
lazy_func_t<const char *(Vehicle vehicle)>
	GET_VEHICLE_MOD_COLOR_2_NAME(0x4967A516ED23A5A1);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xB055A34527CB8FD7(0xB055A34527CB8FD7);
lazy_func_t<void(Vehicle vehicle, Vehicle trailer, float radius)>
	ATTACH_VEHICLE_TO_TRAILER(0x3C7D42D58F770B54);
lazy_func_t<void(Hash vehicleHash, int vehicleAsset)>
	REQUEST_VEHICLE_ASSET(0x81A15811460FAB3A);
lazy_func_t<void(BOOL p0)> _0x35E0654F4BAD7971(0x35E0654F4BAD7971);
lazy_func_t<void(Vehicle vehicle, int r, int g, int b)>
	SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(0x7141766F91D15BEA);
lazy_func_t<void(Vehicle vehicle, Vehicle vehicle2)>
	_0xE44A982368A4AF23(0xE44A982368A4AF23);
lazy_func_t<BOOL(Vehicle vehicle)>
	SET_VEHICLE_ON_GROUND_PROPERLY(0x49733E92263139D1);
lazy_func_t<void(Vehicle vehicle)>
	SET_VEHICLE_DEFORMATION_FIXED(0x953DA1E1B12C0491);
lazy_func_t<void(Vehicle vehicle)> _0x6D6AF961B72728AE(0x6D6AF961B72728AE);
lazy_func_t<void(Vehicle vehicle, Ped ped, int p2)>
	_SET_VEHICLE_EXCLUSIVE_DRIVER_2(0xB5C51B5502E85E83);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xA7DCDF4DED40A8F4(0xA7DCDF4DED40A8F4);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x51BB2D88D31A914B(0x51BB2D88D31A914B);
lazy_func_t<void(Vehicle vehicle, int turnSignal, BOOL toggle)>
	SET_VEHICLE_INDICATOR_LIGHTS(0xB5D45264751B7DF0);
lazy_func_t<void(Vehicle vehicle)> _0x95CF53B3D687F9FA(0x95CF53B3D687F9FA);
lazy_func_t<void(Vehicle train, BOOL toggle)>
	SET_RENDER_TRAIN_AS_DERAILED(0x317B11A312DF5534);
lazy_func_t<void(Any p0)> PAUSE_PLAYBACK_RECORDED_VEHICLE(0x632A689BF42301B1);
lazy_func_t<void()> _0x48ADC8A773564670(0x48ADC8A773564670);
lazy_func_t<void(Any p0, Player p1)> _0xCF1182F682F65307(0xCF1182F682F65307);
lazy_func_t<void(Vehicle vehicle, float value)>
	SET_VEHICLE_BODY_HEALTH(0xB77D05AC8C78AADB);
lazy_func_t<void(float multiplier)>
	SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0xB3B3359379FE77D3);
lazy_func_t<void(Vehicle vehicle, BOOL killDriver, BOOL explodeOnImpact)>
	SET_VEHICLE_OUT_OF_CONTROL(0xF19D095E42D430CC);
lazy_func_t<void(Vehicle vehicle, float friction)>
	SET_VEHICLE_FRICTION_OVERRIDE(0x1837AF7C627009BA);
lazy_func_t<void(Vehicle vehicle, int *pearlescentColor, int *wheelColor)>
	GET_VEHICLE_EXTRA_COLOURS(0x3BC4245933A166F7);
lazy_func_t<BOOL(Ped ped, Vehicle vehicle, BOOL p2, BOOL p3, BOOL p4)>
	_0x639431E895B9AA57(0x639431E895B9AA57);
lazy_func_t<void(Vehicle vehicle, int tint)>
	SET_VEHICLE_WINDOW_TINT(0x57C51E6BAD752696);
lazy_func_t<BOOL(Vehicle vehicle)>
	DOES_VEHICLE_HAVE_STUCK_VEHICLE_CHECK(0x57E4C39DE5EE8470);
lazy_func_t<float(int recordingID)>
	GET_TOTAL_DURATION_OF_VEHICLE_RECORDING_ID(0x102D125411A7B6E6);
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_PLANE(0xA0948AB42D7BA0DE);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xDBC631F109350B8C(0xDBC631F109350B8C);
lazy_func_t<BOOL(Vehicle towTruck, Vehicle vehicle)>
	IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(0x146DF9EC4C4B9FD4);
lazy_func_t<float(Vehicle vehicle)>
	GET_VEHICLE_ACCELERATION(0x5DD35C8D074E57AE);
lazy_func_t<void(Vehicle *vehicle)> DELETE_VEHICLE(0xEA386986E786A54F);
lazy_func_t<const char *(Vehicle vehicle)>
	GET_VEHICLE_NUMBER_PLATE_TEXT(0x7CE1CCB9B293020E);
lazy_func_t<void(BOOL p0)> _0xE6C0C80B8C867537(0xE6C0C80B8C867537);
lazy_func_t<void(Vehicle vehicle, int extraId, BOOL disable)>
	SET_VEHICLE_EXTRA(0x7EE3A3C5E4A40CC9);
lazy_func_t<void(Vehicle vehicle, int WheelType)>
	SET_VEHICLE_WHEEL_TYPE(0x487EB21CC7295BA1);
lazy_func_t<void(Any p0, BOOL p1)> _0xDFFCEF48E511DB48(0xDFFCEF48E511DB48);
lazy_func_t<void(Vehicle vehicle, Any p1)>
	_0x500873A45724C863(0x500873A45724C863);
lazy_func_t<Vehicle(Vehicle vehicle, Vehicle wheel_rf, BOOL completely)>
	IS_VEHICLE_TYRE_BURST(0xBA291848A0815CA9);
lazy_func_t<void(Any p0, BOOL p1)> _0x0AD9E8F87FF7C16F(0x0AD9E8F87FF7C16F);
lazy_func_t<void(Vehicle cargobob, BOOL isActive)>
	_SET_CARGOBOB_PICKUP_MAGNET_ACTIVE(0x9A665550F8DA349B);
lazy_func_t<Vehicle(
	Hash modelHash,
	float x,
	float y,
	float z,
	float heading,
	BOOL isNetwork,
	BOOL thisScriptCheck)>
	CREATE_VEHICLE(0xAF35D0D2583051B0);
lazy_func_t<BOOL(Vehicle vehicle)>
	GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(0xF095C0405307B21B);
lazy_func_t<void(Any p0, float p1, BOOL p2)>
	_0xF8EBCCC96ADB9FB7(0xF8EBCCC96ADB9FB7);
lazy_func_t<float(Vehicle vehicle)> _GET_VEHICLE_MAX_SPEED(0x53AF99BAA671CA47);
lazy_func_t<BOOL(Vehicle vehicle, Entity entity)>
	_0x89D630CF5EA96D23(0x89D630CF5EA96D23);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x3441CAD2F2231923(0x3441CAD2F2231923);
lazy_func_t<void(Vehicle vehicle, int doorIndex, BOOL isBreakable)>
	_SET_VEHICLE_DOOR_CAN_BREAK(0x2FA133A4A9D37ED8);
lazy_func_t<float(Vehicle vehicle)>
	_GET_HELI_MAIN_ROTOR_HEALTH(0xE4CB7541F413D2C5);
lazy_func_t<float(Hash modelHash)>
	_GET_VEHICLE_MODEL_DOWN_FORCE(0x53409B5163D5B846);
lazy_func_t<Any(BOOL toggle)> SET_RANDOM_BOATS(0x84436EC293B1415F);
lazy_func_t<int(Any p0, float p1, Any *p2)>
	GET_ROTATION_OF_VEHICLE_RECORDING_AT_TIME(0x2058206FBE79A8AD);
lazy_func_t<void(Vehicle vehicle, int *paintType, int *color)>
	GET_VEHICLE_MOD_COLOR_2(0x81592BE4E3878728);
lazy_func_t<BOOL(Any p0)> HAS_PRELOAD_MODS_FINISHED(0x06F43E5175EB6D96);
lazy_func_t<void(
	Ped driver, Entity entity, float xTarget, float yTarget, float zTarget)>
	SET_VEHICLE_SHOOT_AT_TARGET(0x74CD9A9327A282EA);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_SIREN(0xF4924635A19EB37D);
lazy_func_t<void(Vehicle vehicle, BOOL value, BOOL instantly, BOOL otherwise)>
	SET_VEHICLE_ENGINE_ON(0x2497C4717C8B881E);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	RESET_VEHICLE_WHEELS(0x21D2E5662C1F6FED);
lazy_func_t<void(Vehicle vehicle)> RELEASE_PRELOAD_MODS(0x445D79F995508307);
lazy_func_t<BOOL(Vehicle vehicle, int seatIndex)>
	IS_VEHICLE_SEAT_FREE(0x22AC59A870E6A669);
lazy_func_t<void(Vehicle vehicle, int doorIndex, BOOL deleteDoor)>
	SET_VEHICLE_DOOR_BROKEN(0xD4D4F6A4AB575A33);
lazy_func_t<Hash(Vehicle vehicle)>
	GET_VEHICLE_CAUSE_OF_DESTRUCTION(0xE495D1EF4C91FD20);
lazy_func_t<void(Vehicle x)> _0x7C0043FDFF6436BC(0x7C0043FDFF6436BC);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x91A0BD635321F145(0x91A0BD635321F145);
lazy_func_t<Any(Vehicle vehicle)> SET_PLAYERS_LAST_VEHICLE(0xBCDF8BAF56C87B6A);
lazy_func_t<void(Vehicle vehicle, int modType)>
	REMOVE_VEHICLE_MOD(0x92D619E420858204);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_STOLEN(0x4AF9BD80EEBEB453);
lazy_func_t<Any(Vehicle vehicle)>
	CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(0x5FFBDEEC3E8E2009);
lazy_func_t<BOOL(Vehicle vehicle, BOOL p1, BOOL p2, BOOL p3)>
	IS_HELI_PART_BROKEN(0xBC74B4BE25EB6C8A);
lazy_func_t<void(Vehicle vehicle, const char *name)>
	SET_VEHICLE_NAME_DEBUG(0xBFDF984E2C22B94F);
lazy_func_t<void(Vehicle vehicle, float value)>
	_SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(0xB59E4BD37AE292DB);
lazy_func_t<Any(Vehicle vehicle)>
	CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(0x55E1D2758F34E437);
lazy_func_t<void(Vehicle vehicle, int r, int g, int b)>
	SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(0x36CED73BFED89754);
lazy_func_t<void(Any p0, Any p1, Any p2, BOOL p3)>
	SET_PLAYBACK_TO_USE_AI_TRY_TO_REVERT_BACK_LATER(0x6E63860BBB190730);
lazy_func_t<int(Vehicle vehicle)> GET_VEHICLE_MOD_KIT(0x6325D1A044AE510D);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x1F9FB66F3A3842D2(0x1F9FB66F3A3842D2);
lazy_func_t<Vehicle(Vehicle cargobob)>
	GET_VEHICLE_ATTACHED_TO_CARGOBOB(0x873B82D42AC2B9E5);
lazy_func_t<void(BOOL toggle)>
	_SET_SOMETHING_MULTIPLIER_THIS_FRAME(0xD4B8E3D1917BC86B);
lazy_func_t<Any(Vehicle train, float speed)>
	SET_TRAIN_CRUISE_SPEED(0x16469284DB8C62B5);
lazy_func_t<void(Vehicle vehicle, BOOL instantlyRaise)>
	RAISE_CONVERTIBLE_ROOF(0x8F5FB35D7E88FC70);
lazy_func_t<void(Vehicle vehicle, float p1)>
	_0x685D5561680D088B(0x685D5561680D088B);
lazy_func_t<void(Vehicle vehicle, int colorPrimary, int colorSecondary)>
	SET_VEHICLE_COLOURS(0x4F1D4BE3A7F24601);
lazy_func_t<Any(Any p0)> _0x42A4BEB35D372407(0x42A4BEB35D372407);
lazy_func_t<void(Vehicle train, float x, float y, float z)>
	SET_MISSION_TRAIN_COORDS(0x591CA673AA6AB736);
lazy_func_t<void(Vehicle vehicle, float value)>
	_0xAD2D28A1AFDFF131(0xAD2D28A1AFDFF131);
lazy_func_t<BOOL(Vehicle vehicle)>
	GET_VEHICLE_TYRES_CAN_BURST(0x678B9BB8C3F58FEB);
lazy_func_t<void(Any p0, Any p1)> _0x21973BBF8D17EDFA(0x21973BBF8D17EDFA);
lazy_func_t<void(Any p0, float p1)>
	SKIP_TIME_IN_PLAYBACK_RECORDED_VEHICLE(0x9438F7AD68771A20);
lazy_func_t<BOOL(Vehicle vehicle)> IS_BIG_VEHICLE(0x9F243D3919F442FE);
lazy_func_t<void(Vehicle vehicle)>
	REQUEST_VEHICLE_HIGH_DETAIL_MODEL(0xA6E9FDCB2C76785E);
lazy_func_t<Any(Vehicle vehicle, BOOL isStolen)>
	SET_VEHICLE_IS_STOLEN(0x67B2C79AA7FF5738);
lazy_func_t<void(Vehicle vehicle, const char *plateText)>
	SET_VEHICLE_NUMBER_PLATE_TEXT(0x95A88F0B409CDA47);
lazy_func_t<void(Vehicle vehicle, float speed)>
	SET_PLAYBACK_SPEED(0x6683AB880E427778);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_VISIBLE(0xAA0A52D24FB98293);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_SET_VEHICLE_JET_ENGINE_ON(0xB8FBC8B1330CA9B4);
lazy_func_t<int(Vehicle vehicle)> GET_VEHICLE_CLASS(0x29439776AAA00A62);
lazy_func_t<float(Vehicle vehicle)>
	_GET_VEHICLE_BODY_HEALTH_2(0xB8EF61207C2393A9);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x9F3F689B814F2599(0x9F3F689B814F2599);
lazy_func_t<void(Vehicle vehicle, float angle)>
	_SET_VERTICAL_FLIGHT_PHASE(0x9AA47FFF660CB932);
lazy_func_t<void(Vehicle vehicle, Vector3 *out1, Vector3 *out2)>
	_0xDF7E3EEB29642C38(0xDF7E3EEB29642C38);
lazy_func_t<void(Any p0)>
	SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_VEHICLE(0xAB8E2EDA0C0A5883);
lazy_func_t<void(Any p0)> _0xE30524E1871F481D(0xE30524E1871F481D);
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_BIKE(0xB50C0B0CEDC6CE84);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_BOAT_ANCHOR(0x75DBEC174AEEAD10);
lazy_func_t<Ped(Vehicle vehicle, int index)>
	GET_PED_IN_VEHICLE_SEAT(0xBB40DD2270B65366);
lazy_func_t<void(Vehicle vehicle)> SET_VEHICLE_FIXED(0x115722B1B9C14C1C);
lazy_func_t<void()> _0xE01903C47C7AC89E(0xE01903C47C7AC89E);
lazy_func_t<void()> _0x0A436B8643716D14(0x0A436B8643716D14);
lazy_func_t<void(Vehicle vehicle, BOOL state)>
	SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(0x4C7028F78FFD3681);
lazy_func_t<Any(Any p0)> _0x2C8CBFE1EA5FC631(0x2C8CBFE1EA5FC631);
lazy_func_t<Any()> _0x6ADAABD3068C5235(0x6ADAABD3068C5235);
lazy_func_t<
	Vehicle(float x, float y, float z, float radius, Hash modelHash, int flags)>
	GET_CLOSEST_VEHICLE(0xF73EB622C4F1689B);
lazy_func_t<void(int vehicleGenerator)>
	DELETE_SCRIPT_VEHICLE_GENERATOR(0x22102C9ABFCF125D);
lazy_func_t<void(Vehicle vehicle, BOOL p1, BOOL p2)>
	DISABLE_PLANE_AILERON(0x23428FC53C60919C);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_STOPPED(0x5721B434AD84D57A);
lazy_func_t<void(Vehicle vehicle, float speed)>
	SET_VEHICLE_FORWARD_SPEED(0xAB54A438726D25D5);
lazy_func_t<BOOL(Vehicle vehicle)>
	_VEHICLE_HAS_LANDING_GEAR(0x4198AB0022B15F87);
lazy_func_t<void(Vehicle vehicle, BOOL active)>
	_SET_VEHICLE_PARACHUTE_ACTIVE(0x0BFFB028B3DD0A97);
lazy_func_t<Any(Vehicle vehicle, int index)>
	FIX_VEHICLE_WINDOW(0x772282EBEB95E682);
lazy_func_t<BOOL(Vehicle vehicle)>
	IS_VEHICLE_ATTACHED_TO_TRAILER(0xE7CF3C4F9F489F0C);
lazy_func_t<float(Hash modelHash)>
	_GET_VEHICLE_MODEL_MAX_KNOTS(0xC6AD107DDC9054CC);
lazy_func_t<BOOL(Any p0, BOOL p1)> _0xF78F94D60248C737(0xF78F94D60248C737);
lazy_func_t<void(Vehicle vehicle)>
	DETACH_VEHICLE_FROM_TRAILER(0x90532EDF0D2BDD86);
lazy_func_t<void(Vehicle vehicle, int doorIndex, int speed, float angle)>
	SET_VEHICLE_DOOR_CONTROL(0xF2BFA0430F0A0FCB);
lazy_func_t<void(Vehicle vehicle, int state)>
	SET_VEHICLE_LIGHTS(0x34E710FF01247C5A);
lazy_func_t<
	Any(float p0, float p1, float p2, float p3, float p4, float p5, float p6)>
	_0x54B0F614960F4A5F(0x54B0F614960F4A5F);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	DISABLE_VEHICLE_IMPACT_EXPLOSION_ACTIVATION(0xD8050E0EB60CF274);
lazy_func_t<void(Vehicle vehicle)> _0x99AD4CCCB128CBC9(0x99AD4CCCB128CBC9);
lazy_func_t<Vector3(Vehicle cargobob)>
	_GET_CARGOBOB_HOOK_POSITION(0xCBDB9B923CACC92D);
lazy_func_t<BOOL(Vehicle vehicle)>
	IS_VEHICLE_ALARM_ACTIVATED(0x4319E335B71FFF34);
lazy_func_t<void(Vehicle vehicle, float value)>
	_SET_VEHICLE_ENGINE_POWER_MULTIPLIER(0x93A3996368C94158);
lazy_func_t<void(Vehicle vehicle, int nullAttributes)>
	RESET_VEHICLE_STUCK_TIMER(0xD7591B0065AFAA7A);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_IN_BURNOUT(0x1297A88E081430EB);
lazy_func_t<void(Vehicle vehicle)> _0xCFD778E7904C255E(0xCFD778E7904C255E);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_GRAVITY(0x89F149B6131E57DA);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xE16142B94664DEFD(0xE16142B94664DEFD);
lazy_func_t<
	void(Vehicle vehicle, int doorIndex, BOOL loose, BOOL openInstantly)>
	SET_VEHICLE_DOOR_OPEN(0x7C65DAC73C35C862);
lazy_func_t<
	Vehicle(float p0, float p1, float p2, float p3, int p4, int p5, int p6)>
	GET_RANDOM_VEHICLE_FRONT_BUMPER_IN_SPHERE(0xC5574E0AEB86BA68);
lazy_func_t<void(Vehicle vehicle, int paintType, int color, int p3)>
	SET_VEHICLE_MOD_COLOR_1(0x43FEB945EE7F85B8);
lazy_func_t<Vehicle()> GET_LAST_DRIVEN_VEHICLE(0xB2D06FAEDE65B577);
lazy_func_t<void(Vehicle vehicle, float seconds)>
	_SET_VEHICLE_ROCKET_BOOST_REFILL_TIME(0xE00F2AB100B76E89);
lazy_func_t<void(Vehicle vehicle, BOOL p1, float yaw, float pitch, float roll)>
	_JITTER_VEHICLE(0xC59872A5134879C7);
lazy_func_t<const char *(Hash modelHash)>
	GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(0xB215AAC32D25D019);
lazy_func_t<const char *(Hash modelHash)>
	GET_MFR_DISPLAY_NAME_FROM_VEHICLE_MODEL(0xF7AF4F159FF99F97);
lazy_func_t<void(Vehicle cargobob, int state)>
	CREATE_PICK_UP_ROPE_FOR_CARGOBOB(0x7BEB0C7A235F6F3B);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_CAN_BREAK(0x59BF8C3D52C92F66);
lazy_func_t<void(Vehicle vehicle)> OPEN_BOMB_BAY_DOORS(0x87E7F24270732CB1);
lazy_func_t<void(Vehicle vehicle, int plateIndex)>
	SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(0x9088EB5A43FFB0A1);
lazy_func_t<void(Any p0, float p1)> _0x1093408B4B9D1146(0x1093408B4B9D1146);
lazy_func_t<void(Vehicle heli, BOOL toggle, BOOL canBeUsedByAI)>
	SET_VEHICLE_SEARCHLIGHT(0x14E85C5EE7A4D542);
lazy_func_t<int(Vehicle vehicle)> GET_VEHICLE_WHEEL_TYPE(0xB3ED1BFB4BE636DC);
lazy_func_t<void(Vehicle veh, BOOL toggle)>
	SET_VEHICLE_ALLOW_NO_PASSENGERS_LOCKON(0x5D14D4154BFE7B2C);
lazy_func_t<int()> GET_NUMBER_OF_VEHICLE_NUMBER_PLATES(0x4C4D6B2644F458CB);
lazy_func_t<
	void(float x1, float y1, float z1, float x2, float y2, float z2, Any unk)>
	REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(0x46A1E1A299EC4BBA);
lazy_func_t<void(
	Vehicle towTruck,
	Vehicle vehicle,
	BOOL rear,
	float hookOffsetX,
	float hookOffsetY,
	float hookOffsetZ)>
	ATTACH_VEHICLE_TO_TOW_TRUCK(0x29A16F8D621C4508);
lazy_func_t<const char *(Vehicle vehicle, BOOL p1)>
	GET_VEHICLE_MOD_COLOR_1_NAME(0xB45085B721EFD38C);
lazy_func_t<void(Vehicle vehicle, int *r, int *g, int *b)>
	GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(0xB64CF2CCA9D95F52);
lazy_func_t<BOOL(Vehicle vehicle, BOOL frontBumper)>
	_0x27B926779DEB502D(0x27B926779DEB502D);
lazy_func_t<float(Any p0)> GET_TIME_POSITION_IN_RECORDING(0x5746F3A7AB7FE544);
lazy_func_t<void(Vehicle vehicle, float x, float y, float z, Any p4)>
	_0x5845066D8A1EA7F7(0x5845066D8A1EA7F7);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x88BC673CA9E0AE99(0x88BC673CA9E0AE99);
lazy_func_t<float(int vehicleClass)>
	GET_VEHICLE_CLASS_MAX_TRACTION(0xDBC86D85C5059461);
lazy_func_t<void(Vehicle vehicle)> CLOSE_BOMB_BAY_DOORS(0x3556041742A0DC74);
lazy_func_t<BOOL(Vehicle vehicle)>
	DOES_VEHICLE_HAVE_WEAPONS(0x25ECB9F8017D98E0);
lazy_func_t<BOOL(Vehicle vehicle, BOOL flag)>
	_0xF7F203E31F96F6A1(0xF7F203E31F96F6A1);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xC45C27EF50F36ADC(0xC45C27EF50F36ADC);
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_BOAT(0x45A9187928F4B9E3);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_ENGINE_CAN_DEGRADE(0x983765856F2564F9);
lazy_func_t<BOOL(Vehicle vehicle, Entity entity)>
	SET_PED_ENABLED_BIKE_RINGTONE(0x57715966069157AD);
lazy_func_t<void(Vehicle vehicle, BOOL state)>
	SET_VEHICLE_ALARM(0xCDE5E70C1DDB954C);
lazy_func_t<float(Vehicle vehicle, int modType, int modIndex)>
	GET_VEHICLE_MOD_MODIFIER_VALUE(0x90A38E9838E0A8C1);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(0xA2F80B8D040727CC);
lazy_func_t<
	Vehicle(float p0, float p1, float p2, float p3, int p4, int p5, int p6)>
	GET_RANDOM_VEHICLE_BACK_BUMPER_IN_SPHERE(0xB50807EABE20A8DC);
lazy_func_t<int(Vehicle vehicle)>
	GET_CONVERTIBLE_ROOF_STATE(0xF8C397922FC03F41);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	SET_VEHICLE_RUDDER_BROKEN(0x09606148B6C71DEF);
lazy_func_t<void(Vehicle cargobob, float p1)>
	_0xA17BAD153B51547E(0xA17BAD153B51547E);
lazy_func_t<void(int vehicleGenerator, BOOL enabled)>
	SET_SCRIPT_VEHICLE_GENERATOR(0xD9D620E0AC6DC4B0);
lazy_func_t<void(Vehicle vehicle, float speed)>
	SET_HELI_BLADES_SPEED(0xFD280B4D7F3ABC4D);
lazy_func_t<BOOL(float x, float y, float z, float radius)>
	IS_ANY_VEHICLE_NEAR_POINT(0x61E1DD6125A3EEE6);
lazy_func_t<void(Any p0, float p1, BOOL p2)>
	_0x56B94C6D7127DFBA(0x56B94C6D7127DFBA);
lazy_func_t<const char *(Vehicle vehicle, int modType, int modValue)>
	GET_MOD_TEXT_LABEL(0x8935624F8C5592CC);
lazy_func_t<void(Vehicle *train)> DELETE_MISSION_TRAIN(0x5B76B14AE875C795);
lazy_func_t<void(BOOL p0, Hash *modelHash, int *p2)>
	GET_RANDOM_VEHICLE_MODEL_IN_MEMORY(0x055BF0AC0C34F4FD);
lazy_func_t<float(Vehicle vehicle)>
	GET_VEHICLE_ENGINE_HEALTH(0xC45D23BAF168AAB8);
lazy_func_t<BOOL(Vehicle vehicle, Any p1)> CAN_SHUFFLE_SEAT(0x30785D90C956BF35);
lazy_func_t<BOOL(Vehicle vehicle, int modType)>
	GET_VEHICLE_MOD_VARIATION(0xB3924ECD70E095DC);
lazy_func_t<void(BOOL active)>
	SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(0x608207E7A8FB787C);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(0x31B927BBC44156CD);
lazy_func_t<void(Vehicle vehicle, float health)>
	SET_VEHICLE_PETROL_TANK_HEALTH(0x70DB57649FA8D0D8);
lazy_func_t<int(Vehicle vehicle, int modType)>
	GET_VEHICLE_MOD(0x772960298DA26FDB);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xB088E9A47AE6EDD5(0xB088E9A47AE6EDD5);
lazy_func_t<void(float multiplier)>
	SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0x245A6883D966D537);
lazy_func_t<BOOL(Vehicle vehicle, int extraId)>
	IS_VEHICLE_EXTRA_TURNED_ON(0xD2E6822DBFD6C8BD);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(0x465BF26AB9684352);
lazy_func_t<int(Vehicle vehicle)> GET_VEHICLE_MOD_KIT_TYPE(0xFC058F5121E54C32);
lazy_func_t<void(Vehicle vehicle, BOOL p1, BOOL p2)>
	_0x7D6F9A3EF26136A0(0x7D6F9A3EF26136A0);
lazy_func_t<float(Vehicle vehicle)> GET_VEHICLE_DIRT_LEVEL(0x8F17BC8BA08DA62B);
lazy_func_t<Any(Vehicle p0, BOOL p1, BOOL p2, BOOL p3)>
	SET_ALL_VEHICLES_SPAWN(0xE023E8AC4EF7C117);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x428BACCDF5E26EAD(0x428BACCDF5E26EAD);
lazy_func_t<void(Vehicle cargobob, float p1)>
	_0xED8286F71A819BAA(0xED8286F71A819BAA);
lazy_func_t<BOOL(Vehicle vehicle)>
	_IS_VEHICLE_ROCKET_BOOST_ACTIVE(0x3D34E80EED4AE3BE);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xC50CE861B55EAB8B(0xC50CE861B55EAB8B);
lazy_func_t<void(int vehicleAsset)> REMOVE_VEHICLE_ASSET(0xACE699C71AB9DEB5);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_FORCE_HD_VEHICLE(0x97CE68CB032583F0);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x25367DE49D64CF16(0x25367DE49D64CF16);
lazy_func_t<void(Vehicle vehicle, float angleRatio)>
	_SET_DESIRED_VERTICAL_FLIGHT_PHASE(0x30D779DE7C4F6DD3);
lazy_func_t<int(Hash modelHash)>
	GET_VEHICLE_CLASS_FROM_NAME(0xDEDF1C8BD47C2200);
lazy_func_t<Any(Vehicle vehicle, BOOL enabled)>
	SET_VEHICLE_WHEELS_CAN_BREAK(0x29B18B4FD460CA8F);
lazy_func_t<void(Vehicle vehicle, int r, int g, int b)>
	SET_VEHICLE_TYRE_SMOKE_COLOR(0xB5BA80F839791C0F);
lazy_func_t<BOOL(Vehicle veh, int doorID)>
	IS_VEHICLE_DOOR_DAMAGED(0xB8E181E559464527);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_ON_ALL_WHEELS(0xB104CD1BABF302E2);
lazy_func_t<void(Vehicle vehicle)>
	REMOVE_VEHICLE_HIGH_DETAIL_MODEL(0x00689CDE5F7C6787);
lazy_func_t<BOOL(Vehicle cargobob)>
	_DOES_CARGOBOB_HAVE_PICKUP_MAGNET(0x6E08BF5B3722BAC9);
lazy_func_t<Any(BOOL toggle)> SET_GARBAGE_TRUCKS(0x2AFD795EEAC8D30D);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_STUCK_ON_ROOF(0xB497F06B288DCFDF);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_BRAKE_LIGHTS(0x92B35082E0B42F66);
lazy_func_t<void(Any p0, Any p1)> _0x10655FAB9915623D(0x10655FAB9915623D);
lazy_func_t<void(Vehicle vehicle, BOOL active)>
	_SET_VEHICLE_HUD_SPECIAL_ABILITY_BAR_ACTIVE(0x99C82F8A139F3E4E);
lazy_func_t<BOOL(Vehicle vehicle)>
	_IS_VEHICLE_SHOP_RESPRAY_ALLOWED(0x8D474C8FAEFF6CDE);
lazy_func_t<void(Any p0, BOOL p1)> _0xE05DD0E9707003A3(0xE05DD0E9707003A3);
lazy_func_t<BOOL(Vehicle vehicle, Any p1)>
	WAS_COUNTER_ACTIVATED(0x3EC8BF18AA453FE9);
lazy_func_t<const char *(Vehicle vehicle, int modType)>
	GET_MOD_SLOT_NAME(0x51F0FEB9F6AE98C0);
lazy_func_t<BOOL(Vehicle vehicle)>
	_ANY_PASSENGERS_RAPPELING(0x291E373D483E7EE7);
lazy_func_t<void(Vehicle helicopter, float multiplier)>
	_SET_HELICOPTER_ROLL_PITCH_YAW_MULT(0x6E0859B530A365CC);
lazy_func_t<void(Vehicle vehicle, Player player, BOOL toggle)>
	SET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(0x517AAF684BB50CD1);
lazy_func_t<int(Vehicle trailers2)> GET_VEHICLE_LIVERY(0x2BB9230590DA5E8A);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x1AA8A837D2169D94(0x1AA8A837D2169D94);
lazy_func_t<BOOL(Vehicle vehicle)>
	_HAS_VEHICLE_JUMPING_ABILITY(0x9078C0C5EF8C19E9);
lazy_func_t<void(Vehicle vehicle, float fade)>
	SET_VEHICLE_ENVEFF_SCALE(0x3AFDC536C3D01674);
lazy_func_t<void(Vehicle vehicle, Entity entity)>
	_0x6A98C2ECF57FA5D4(0x6A98C2ECF57FA5D4);
lazy_func_t<void(Vehicle vehicle, float p1)>
	_0xE5810AC70602F2F5(0xE5810AC70602F2F5);
lazy_func_t<Any(Vehicle vehicle, int windowIndex)>
	ROLL_UP_WINDOW(0x602E548F46E24D59);
lazy_func_t<void(Vehicle vehicle, float value)>
	SET_VEHICLE_STEER_BIAS(0x42A8EC77D5150CBE);
lazy_func_t<void(Vehicle vehicle, Vehicle cargobob)>
	_0xE301BD63E9E13CF0(0xE301BD63E9E13CF0);
lazy_func_t<void(Vehicle vehicle)>
	ADD_VEHICLE_UPSIDEDOWN_CHECK(0xB72E26D81006005B);
lazy_func_t<float(Hash modelHash)>
	GET_VEHICLE_MODEL_MAX_TRACTION(0x539DE94D44FDFD0D);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x9BECD4B9FEF3F8A6(0x9BECD4B9FEF3F8A6);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x4E74E62E0A97E901(0x4E74E62E0A97E901);
lazy_func_t<BOOL(int vehicleAsset)>
	HAS_VEHICLE_ASSET_LOADED(0x1BBE0523B8DB9A21);
lazy_func_t<void(Vehicle cargobob, float p1)>
	_0x66979ACF5102FD2F(0x66979ACF5102FD2F);
lazy_func_t<void(Vehicle vehicle, int tyreIndex)>
	SET_VEHICLE_TYRE_FIXED(0x6E13FC662B882D1D);
lazy_func_t<int(Vehicle vehicle)>
	GET_NUMBER_OF_VEHICLE_COLOURS(0x3B963160CD65D41E);
lazy_func_t<void(Vehicle vehicle, int pearlescentColor, int wheelColor)>
	SET_VEHICLE_EXTRA_COLOURS(0x2036F561ADD12E33);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_SET_VEHICLE_SILENT(0x9D44FCCE98450843);
lazy_func_t<const char *(Vehicle vehicle, int liveryIndex)>
	GET_LIVERY_NAME(0xB4C7A93837C91A1F);
lazy_func_t<void(Vehicle vehicle, BOOL state)>
	SET_VEHICLE_IS_WANTED(0xF7EC25A3EBEEC726);
lazy_func_t<void(Vehicle cargobob, BOOL p1)>
	_0x571FEB383F629926(0x571FEB383F629926);
lazy_func_t<int(Vehicle vehicle)>
	GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(0xA7C4F2C6E744A550);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xE851E480B814D4BA(0xE851E480B814D4BA);
lazy_func_t<Ped(Vehicle vehicle, int seatIndex)>
	GET_LAST_PED_IN_VEHICLE_SEAT(0x83F969AA1EE2A664);
lazy_func_t<BOOL(Vehicle vehicle)> _0x634148744F385576(0x634148744F385576);
lazy_func_t<Any(Vehicle vehicle, BOOL p1)>
	_0x2B6747FAA9DB9D6B(0x2B6747FAA9DB9D6B);
lazy_func_t<float(Hash modelHash)>
	GET_VEHICLE_MODEL_MAX_BRAKING(0xDC53FD41B4ED944C);
lazy_func_t<float(int vehicleClass)>
	GET_VEHICLE_CLASS_MAX_AGILITY(0x4F930AD022D6DE3B);
lazy_func_t<void(Vehicle vehicle, int modType, BOOL toggle)>
	TOGGLE_VEHICLE_MOD(0x2A1F4F37F95BAD08);
lazy_func_t<void(Vehicle vehicle, int team, BOOL toggle)>
	SET_VEHICLE_DOORS_LOCKED_FOR_TEAM(0xB81F6D4A8F5EEBA8);
lazy_func_t<void(Vehicle vehicle, BOOL state)>
	SET_CAN_RESPRAY_VEHICLE(0x52BBA29D5EC69356);
lazy_func_t<Any(Vehicle vehicle, BOOL p1, Any p2)>
	SET_VEHICLE_AUTOMATICALLY_ATTACHES(0x8BA6F76BC53A1493);
lazy_func_t<BOOL(Vehicle vehicle)> _HAS_VEHICLE_PARACHUTE(0xBC9CFF381338CB4F);
lazy_func_t<BOOL(Vehicle vehicle)> _0xAE3FEE8709B39DCB(0xAE3FEE8709B39DCB);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_DISABLE_VEHICLE_PETROL_TANK_DAMAGE(0x37C8252A7C92D017);
lazy_func_t<void(Any p0, Any p1, Any *p2, float p3, Any p4)>
	START_PLAYBACK_RECORDED_VEHICLE_USING_AI(0x29DE5FA52D00428C);
lazy_func_t<void(const char *vehicle, BOOL p1)>
	_0xCAC66558B944DA67(0xCAC66558B944DA67);
lazy_func_t<void(Vehicle vehicle, int doorIndex, int destroyType)>
	SET_PED_TARGETTABLE_VEHICLE_DESTROY(0xBE70724027F85BCD);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(0xFBA550EA44404EE6);
lazy_func_t<void(
	Vehicle vehicle,
	float xOffset,
	float yOffset,
	float zOffset,
	float damage,
	float radius,
	BOOL p6)>
	SET_VEHICLE_DAMAGE(0xA1DD317EA8FD4F29);
lazy_func_t<float(Vehicle vehicle)> GET_VEHICLE_MAX_BRAKING(0xAD7E85FC227197C4);
lazy_func_t<float(Vehicle vehicle)>
	GET_VEHICLE_MAX_TRACTION(0xA132FB5370554DB0);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_SIREN_ON(0x4C9BF537BE2634B2);
lazy_func_t<int(Vehicle vehicle)>
	GET_VEHICLE_COLOUR_COMBINATION(0x6A842D197F845D56);
lazy_func_t<void(Vehicle vehicle, float p1)>
	_0xE6F13851780394DA(0xE6F13851780394DA);
lazy_func_t<void(Vehicle vehicle, float p1, float p2)>
	_0x99CAD8E7AFDB60FA(0x99CAD8E7AFDB60FA);
lazy_func_t<BOOL(Vehicle vehicle)>
	ARE_ALL_VEHICLE_WINDOWS_INTACT(0x11D862A3E977A9EF);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x1A78AD3D8240536F(0x1A78AD3D8240536F);
lazy_func_t<void(Vehicle vehicle, BOOL isAudible, BOOL isInvisible)>
	EXPLODE_VEHICLE(0xBA71116ADF5B514C);
lazy_func_t<void(Vehicle vehicle, int *r, int *g, int *b)>
	GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(0x8389CD56CA8072DC);
lazy_func_t<Vector3(int p0, float p1, const char *p2)>
	GET_POSITION_OF_VEHICLE_RECORDING_AT_TIME(0xD242728AA6F0FBA2);
lazy_func_t<void(Vehicle vehicle)> _0xB264C4D2F2B0A78B(0xB264C4D2F2B0A78B);
lazy_func_t<void(Vehicle cargobob, float p1)>
	_0x6D8EAC07506291FB(0x6D8EAC07506291FB);
lazy_func_t<void(float p0, float p1, float p2, float p3)>
	_0x9A75585FB2E54FAD(0x9A75585FB2E54FAD);
lazy_func_t<Vehicle(int variation, float x, float y, float z, BOOL direction)>
	CREATE_MISSION_TRAIN(0x63C6CCA8E68AE8C8);
lazy_func_t<void(Any p0, Any *p1)> REMOVE_VEHICLE_RECORDING(0xF1160ACCF98A3FC8);
lazy_func_t<void(float p0)> _0xBC3CCA5844452B06(0xBC3CCA5844452B06);
lazy_func_t<void(Vehicle cargobob, float strength)>
	_SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(0xBCBFCD9D1DAC19E2);
lazy_func_t<BOOL(Vehicle vehicle, BOOL *lightsOn, BOOL *highbeamsOn)>
	GET_VEHICLE_LIGHTS_STATE(0xB91B4C20085BD12F);
lazy_func_t<void(int i, const char *name)>
	REQUEST_VEHICLE_RECORDING(0xAF514CABE74CBF15);
lazy_func_t<float(Hash modelHash)>
	_GET_VEHICLE_MODEL_MOVE_RESISTANCE(0x5AA3F878A178C4FC);
lazy_func_t<int(int p0, BOOL p1)> GET_NUM_MOD_COLORS(0xA551BE18C11A476D);
lazy_func_t<int(Vehicle vehicle)> GET_VEHICLE_PLATE_TYPE(0x9CCC9525BF2408E0);
lazy_func_t<BOOL(Vehicle vehicle)>
	_ARE_VEHICLE_WINGS_INTACT(0x5991A01434CE9677);
lazy_func_t<void(Vehicle vehicle, float height)>
	_0x37EBBF3117BD6A25(0x37EBBF3117BD6A25);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x2311DD7159F00582(0x2311DD7159F00582);
lazy_func_t<Any(Vehicle vehicle, int index)>
	SMASH_VEHICLE_WINDOW(0x9E5B5E4D2CCD2259);
lazy_func_t<void(Vehicle vehicle, BOOL closeInstantly)>
	SET_VEHICLE_DOORS_SHUT(0x781B3D62BB013EF5);
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_HELI(0xDCE4334788AF94EA);
lazy_func_t<void(Any p0, BOOL p1)> _0xC1F981A6F74F0C23(0xC1F981A6F74F0C23);
lazy_func_t<BOOL(Vehicle cargobob)>
	DOES_CARGOBOB_HAVE_PICK_UP_ROPE(0x1821D91AD4B56108);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_CAN_BE_USED_BY_FLEEING_PEDS(0x300504B23BD3B711);
lazy_func_t<float(Vehicle vehicle)>
	_GET_VEHICLE_SUSPENSION_HEIGHT(0x53952FD2BAA19F17);
lazy_func_t<void(float value)>
	_SET_SOME_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0x90B6DA738A9A25DA);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xE3EBAAE484798530(0xE3EBAAE484798530);
lazy_func_t<void(Any p0, float p1)> _0xF488C566413B4232(0xF488C566413B4232);
lazy_func_t<
	void(Vehicle vehicle, int doorIndex, BOOL forceClose, BOOL lock, BOOL p4)>
	SET_VEHICLE_DOOR_LATCHED(0xA5A9653A8D2CAF48);
lazy_func_t<Any(Vehicle vehicle, int modType, int modIndex)>
	_GET_VEHICLE_MOD_DATA(0x4593CF82AA179706);
lazy_func_t<float(Hash modelHash)>
	_GET_VEHICLE_MODEL_MAX_SPEED(0xF417C2502FFFED43);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_HAS_STRONG_AXLES(0x92F0CF722BC4202F);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_HANDBRAKE(0x684785568EF26A22);
lazy_func_t<BOOL(Any p0, Any *p1)>
	HAS_VEHICLE_RECORDING_BEEN_LOADED(0x300D614A4C785FC4);
lazy_func_t<BOOL(Vehicle vehicle, BOOL isOnFireCheck)>
	IS_VEHICLE_DRIVEABLE(0x4C241E39B23DF959);
lazy_func_t<void(BOOL p0)> _0x51DB102F4A3BA5E0(0x51DB102F4A3BA5E0);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x0CDDA42F9E360CA6(0x0CDDA42F9E360CA6);
lazy_func_t<void(Vehicle vehicle, int index, BOOL onRim, float p3)>
	SET_VEHICLE_TYRE_BURST(0xEC6A202EE4960385);
lazy_func_t<void(Vehicle vehicle, Entity p1, float p2)>
	_0x374706271354CB18(0x374706271354CB18);
lazy_func_t<BOOL(Vehicle vehicle)>
	DETACH_VEHICLE_FROM_ANY_CARGOBOB(0xADF7BE450512C12F);
lazy_func_t<int(Any p0, float p1)> _0x92523B76657A517D(0x92523B76657A517D);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x206BC5DC9D1AC70A(0x206BC5DC9D1AC70A);
lazy_func_t<void(Any p0, int modType, Any p2)>
	PRELOAD_VEHICLE_MOD(0x758F49C24925568A);
lazy_func_t<void(Vehicle vehicle, int *r, int *g, int *b)>
	GET_VEHICLE_COLOR(0xF3CC740D36221548);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x1D97D1E3A70A649F(0x1D97D1E3A70A649F);
lazy_func_t<void(Vehicle vehicle, Vehicle cargobob)>
	DETACH_VEHICLE_FROM_CARGOBOB(0x0E21D3DF1051399D);
lazy_func_t<BOOL(Vehicle vehicle)> IS_TAXI_LIGHT_ON(0x7504C0F113AB50FC);
lazy_func_t<Hash(Vehicle vehicle)> GET_VEHICLE_LAYOUT_HASH(0x28D37D4F71AC5C58);
lazy_func_t<BOOL(Vehicle vehicle)>
	IS_VEHICLE_STOPPED_AT_TRAFFIC_LIGHTS(0x2959F696AE390A99);
lazy_func_t<
	void(Vehicle vehicle, int *paintType, int *color, int *pearlescentColor)>
	GET_VEHICLE_MOD_COLOR_1(0xE8D65CA700C9A693);
lazy_func_t<
	void(Vehicle vehicle, Vehicle cargobob, int p2, float x, float y, float z)>
	ATTACH_VEHICLE_TO_CARGOBOB(0x4127F1D84E347769);
lazy_func_t<BOOL(Vehicle vehicle)> _GET_BOAT_ANCHOR(0x26C10ECBDA5D043B);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_0xBE5C1255A1830FF5(0xBE5C1255A1830FF5);
lazy_func_t<int()> GET_NUM_VEHICLE_WINDOW_TINTS(0x9D1224004B3A6707);
lazy_func_t<void(Vehicle vehicle, int p1, int p2)>
	_0xF0E4BA16D1DB546C(0xF0E4BA16D1DB546C);
lazy_func_t<void()> STOP_ALL_GARAGE_ACTIVITY(0x0F87E938BDF29D66);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_REDUCE_GRIP(0x222FF6A823D122E2);
lazy_func_t<void(Vehicle vehicle, float x, float y, float z)>
	_EJECT_JB700_ROOF(0xE38CB9D7D39FDBCC);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x2C4A1590ABF43E8B(0x2C4A1590ABF43E8B);
lazy_func_t<float(int vehicleClass)>
	GET_VEHICLE_CLASS_MAX_ACCELERATION(0x2F83E7E45D9EA7AE);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xAB04325045427AAE(0xAB04325045427AAE);
lazy_func_t<void(BOOL disabled, Hash weaponHash, Vehicle vehicle, Ped owner)>
	DISABLE_VEHICLE_WEAPON(0xF4FC6A6F67D8D856);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_STRONG(0x3E8C8727991A8A0B);
lazy_func_t<Vehicle(Vehicle v, int rwing)>
	IS_VEHICLE_DOOR_FULLY_OPEN(0x3E933CFF7B111C22);
lazy_func_t<void(Vehicle vehicle, int modType, int modIndex, BOOL customTires)>
	SET_VEHICLE_MOD(0x6AF0636DDEDCB6DD);
lazy_func_t<void(Vehicle vehicle, BOOL active)>
	_SET_VEHICLE_ROCKET_BOOST_ACTIVE(0x81E1552E35DC3839);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xB28B1FE5BFADD7F5(0xB28B1FE5BFADD7F5);
lazy_func_t<void(Vehicle *train, BOOL p1)>
	SET_MISSION_TRAIN_AS_NO_LONGER_NEEDED(0xBBE7648349B49BE8);
lazy_func_t<void(Vehicle vehicle, float dirtLevel)>
	SET_VEHICLE_DIRT_LEVEL(0x79D3B596FE44EE8B);
lazy_func_t<Ped(Vehicle vehicle, int doorIndex)>
	_GET_PED_USING_VEHICLE_DOOR(0x218297BF0CFD853B);
lazy_func_t<
	Vector3(Vehicle vehicle, float offsetX, float offsetY, float offsetZ)>
	GET_VEHICLE_DEFORMATION_AT_POS(0x4EC6CFBC7B2E9536);
lazy_func_t<BOOL(Vehicle vehicle)>
	ARE_ANY_VEHICLE_SEATS_FREE(0x2D34FC3BC4ADB780);
lazy_func_t<BOOL(Vehicle vehicle)>
	GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(0x910A32E7AAD2656C);
lazy_func_t<float(Vehicle vehicle)>
	GET_VEHICLE_ENVEFF_SCALE(0xA82819CAC9C4C403);
lazy_func_t<void(Any p0, BOOL p1)> _0x21115BCD6E44656A(0x21115BCD6E44656A);
lazy_func_t<BOOL()> _0x91D6DD290888CBAB(0x91D6DD290888CBAB);
lazy_func_t<BOOL(Vehicle vehicle)>
	_HAS_VEHICLE_ROCKET_BOOST(0x36D782F68B309BDA);
lazy_func_t<float(Any p0)> GET_POSITION_IN_RECORDING(0x2DACD605FC681475);
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_CAR(0x7F6DB52EEFC96DF8);
lazy_func_t<void(Any p0, BOOL p1)> _0x279D50DE5652D935(0x279D50DE5652D935);
lazy_func_t<BOOL(Vehicle vehicle)>
	_CAN_VEHICLE_PARACHUTE_BE_ACTIVATED(0xA916396DF4154EE3);
lazy_func_t<void()> _REQUEST_VEHICLE_PHONE_EXPLOSION(0xEF49CF0270307CBE);
lazy_func_t<void(Vehicle vehicle, float p1)>
	_0x2A8F319B392E7B3F(0x2A8F319B392E7B3F);
lazy_func_t<void(Any p0, BOOL p1)> _0x0F3B4D4E43177236(0x0F3B4D4E43177236);
lazy_func_t<void(Vehicle vehicle, int windowIndex)>
	REMOVE_VEHICLE_WINDOW(0xA711568EEDB43069);
lazy_func_t<void(Vehicle vehicle)>
	SET_HELI_BLADES_FULL_SPEED(0xA178472EBB8AE60D);
lazy_func_t<BOOL(Vehicle vehicle)> IS_VEHICLE_HIGH_DETAIL(0x1F25887F3C104278);
lazy_func_t<void(Vehicle vehicle)> _0xDBA3C090E3D74690(0xDBA3C090E3D74690);
lazy_func_t<void(Vehicle vehicle, int flag)>
	SET_PLAYBACK_TO_USE_AI(0xA549C3B37EA28131);
lazy_func_t<void(Any p0, float p1, float p2, float p3)>
	_0xFAF2A78061FD9EF4(0xFAF2A78061FD9EF4);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x6EBFB22D646FFC18(0x6EBFB22D646FFC18);
lazy_func_t<float(Hash modelHash)>
	_GET_VEHICLE_MODEL_HAND_BRAKE(0xBFBA3BA79CFF7EBF);
lazy_func_t<BOOL(const char *garageName, Vehicle vehicle)>
	IS_VEHICLE_IN_GARAGE_AREA(0xCEE4490CD57BB3C2);
lazy_func_t<void(BOOL toggle)> SET_RANDOM_TRAINS(0x80D9F74197EA47D9);
lazy_func_t<void(Vehicle vehicle)> SET_LAST_DRIVEN_VEHICLE(0xACFB2463CC22BED2);
lazy_func_t<void(Vehicle cargobob, float xOffset, float yOffset, int state)>
	_SET_CARGOBOB_HOOK_POSITION(0x877C1EAEAC531023);
lazy_func_t<void(Vehicle vehicle)>
	REMOVE_VEHICLE_UPSIDEDOWN_CHECK(0xC53EB42A499A7E90);
lazy_func_t<Vehicle(Vehicle object)>
	_GET_VEHICLE_ATTACHED_TO_ENTITY(0x375E7FC44F21C8AB);
lazy_func_t<Entity(Vehicle train, int trailerNumber)>
	GET_TRAIN_CARRIAGE(0x08AAFD0814722BC3);
lazy_func_t<void(Vehicle vehicle, int paintType, int color)>
	SET_VEHICLE_MOD_COLOR_2(0x816562BADFDEC83E);
lazy_func_t<int(Vehicle vehicle)> GET_VEHICLE_WINDOW_TINT(0x0EE21293DAD47C95);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_WHEELS_CAN_BREAK_OFF_WHEN_BLOW_UP(0xA37B9A517B133349);
lazy_func_t<void(Vehicle vehicle, int r, int g, int b)>
	_SET_VEHICLE_NEON_LIGHTS_COLOUR(0x8E0A582209A62695);
lazy_func_t<BOOL(Hash model)>
	_IS_THIS_MODEL_AN_AMPHIBIOUS_CAR(0x633F6F44A537EBB6);
lazy_func_t<void(
	float x1,
	float y1,
	float z1,
	float x2,
	float y2,
	float z2,
	BOOL p6,
	BOOL p7)>
	SET_ALL_VEHICLE_GENERATORS_ACTIVE_IN_AREA(0xC12321827687FE4D);
lazy_func_t<Any(Vehicle train, float speed)>
	SET_TRAIN_SPEED(0xAA0BC91BE0B796E3);
lazy_func_t<BOOL(Vehicle cargobob, Vehicle vehicleAttached)>
	IS_VEHICLE_ATTACHED_TO_CARGOBOB(0xD40148F22E81A1D9);
lazy_func_t<void(Any p0, float p1)> _0x9007A2F21DC108D4(0x9007A2F21DC108D4);
lazy_func_t<void(Vehicle vehicle, int *r, int *g, int *b)>
	_GET_VEHICLE_NEON_LIGHTS_COLOUR(0x7619EEE8C886757F);
lazy_func_t<float(Vehicle vehicle)>
	_GET_HELI_TAIL_ROTOR_HEALTH(0xAE8CE82A4219AC8C);
lazy_func_t<BOOL(int speedzone)> _REMOVE_SPEED_ZONE(0x1033371FC8E842A7);
lazy_func_t<void(Vehicle vehicle, BOOL owned)>
	SET_VEHICLE_HAS_BEEN_OWNED_BY_PLAYER(0x2B5F9D2AF1F1722D);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_SET_VEHICLE_ST(0x1CF38D529D7441D9);
lazy_func_t<void(Vehicle vehicle, Ped ped, BOOL toggle)>
	SET_VEHICLE_TIMED_EXPLOSION(0x2E0A74E1002380B1);
lazy_func_t<Vector3(Any p0, float p1)> _0xF0F2103EFAF8CBA7(0xF0F2103EFAF8CBA7);
lazy_func_t<void(Any p0, float p1, Any p2, BOOL p3, BOOL p4, BOOL p5, Any p6)>
	ADD_VEHICLE_STUCK_CHECK_WITH_WARP(0x2FA9923062DD396C);
lazy_func_t<Entity(Vehicle towTruck)>
	GET_ENTITY_ATTACHED_TO_TOW_TRUCK(0xEFEA18DCF10F8F75);
lazy_func_t<BOOL(Vehicle vehicle, Vehicle *trailer)>
	GET_VEHICLE_TRAILER_VEHICLE(0x1CDD6BADC297830D);
lazy_func_t<void(Vehicle p0, BOOL p1)> _0x02398B627547189C(0x02398B627547189C);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_TYRES_CAN_BURST(0xEB9DC3C7D8596C46);
lazy_func_t<void(Vehicle vehicle)> ROLL_DOWN_WINDOWS(0x85796B0549DDE156);
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_TRAIN(0xAB935175B22E822B);
lazy_func_t<BOOL(Vehicle vehicle)> DOES_VEHICLE_HAVE_ROOF(0x8AC862B0B32C5B80);
lazy_func_t<BOOL(Vehicle vehicle, int p1, int p2)>
	IS_VEHICLE_STUCK_TIMER_UP(0x679BE1DAF71DA874);
lazy_func_t<int(Vehicle vehicle)> GET_LANDING_GEAR_STATE(0x9B0F3DCA3DB0F4CD);
lazy_func_t<void(Vehicle vehicle, int doorLockStatus)>
	SET_VEHICLE_DOORS_LOCKED(0xB664292EAECF7FA6);
lazy_func_t<void(Vehicle vehicle, BOOL state)>
	SET_TAXI_LIGHTS(0x598803E85E8448D9);
lazy_func_t<BOOL(Vehicle vehicle, int windowIndex)>
	IS_VEHICLE_WINDOW_INTACT(0x46E571A0E20D01F1);
lazy_func_t<void(Vehicle vehicle, int *colorPrimary, int *colorSecondary)>
	GET_VEHICLE_COLOURS(0xA19435F193E081AC);
lazy_func_t<BOOL(Vehicle vehicle)>
	IS_PLAYBACK_GOING_ON_FOR_VEHICLE(0x1C8A4C2C19E68EEC);
lazy_func_t<float(int vehicleClass)>
	_GET_VEHICLE_CLASS_MAX_SPEED(0x00C09F246ABEDD82);
lazy_func_t<void(Any p0)> _0xF87D9F2301F7D206(0xF87D9F2301F7D206);
lazy_func_t<void(Vehicle cargobob)>
	REMOVE_PICK_UP_ROPE_FOR_CARGOBOB(0x9768CF648F54C804);
lazy_func_t<void(Vehicle vehicle, BOOL p1, BOOL p2)>
	_0x9BDDC73CC6A115D4(0x9BDDC73CC6A115D4);
lazy_func_t<void(Vehicle vehicle, Ped ped)>
	SET_VEHICLE_EXCLUSIVE_DRIVER(0x41062318F23ED854);
lazy_func_t<int(Hash modelHash)>
	GET_VEHICLE_MODEL_NUMBER_OF_SEATS(0x2AD93716F184EDA4);
lazy_func_t<Any(int intersectionId, BOOL state)>
	SWITCH_TRAIN_TRACK(0xFD813BB7DB977F20);
lazy_func_t<void(Vehicle vehicle, float multiplier)>
	SET_VEHICLE_LIGHT_MULTIPLIER(0xB385454F8791F57C);
lazy_func_t<Any(Vehicle vehicle, int p1)>
	_0xA01BC64DD4BFBBAC(0xA01BC64DD4BFBBAC);
lazy_func_t<BOOL(Vehicle vehicle, BOOL p1)>
	IS_VEHICLE_A_CONVERTIBLE(0x52F357A30698BCCE);
lazy_func_t<BOOL(Vehicle vehicle)>
	IS_VEHICLE_SEARCHLIGHT_ON(0xC0F97FCE55094987);
lazy_func_t<void(Vehicle vehicle, int modKit)>
	SET_VEHICLE_MOD_KIT(0x1F2AA07F00B3217A);
lazy_func_t<BOOL(int v)>
	DOES_SCRIPT_VEHICLE_GENERATOR_EXIST(0xF6086BC836400876);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_0x9737A37136F07E75(0x9737A37136F07E75);
lazy_func_t<void(float multiplier)>
	_SET_CAR_HIGH_SPEED_BUMP_SEVERITY_MULTIPLIER(0x84FD40F56075E816);
lazy_func_t<
	int(float x,
		float y,
		float z,
		float heading,
		float p4,
		float p5,
		Hash modelHash,
		int p7,
		int p8,
		int p9,
		int p10,
		BOOL p11,
		BOOL p12,
		BOOL p13,
		BOOL p14,
		BOOL p15,
		int p16)>
	CREATE_SCRIPT_VEHICLE_GENERATOR(0x9DEF883114668116);
lazy_func_t<BOOL(
	Vector3 *outVec,
	Any p1,
	Vector3 *outVec1,
	Any p3,
	Any p4,
	Any p5,
	Any p6,
	Any p7,
	Any p8)>
	_0xA4822F1CF23F4810(0xA4822F1CF23F4810);
lazy_func_t<Any(Vehicle vehicle)> START_VEHICLE_ALARM(0xB8FF7AB45305C345);
lazy_func_t<
	void(Vehicle vehicle, Any p1, const char *playback, Any p3, Any p4, Any p5)>
	START_PLAYBACK_RECORDED_VEHICLE_WITH_FLAGS(0x7D80FD645D4DA346);
lazy_func_t<void(Hash model, BOOL suppressed)>
	SET_VEHICLE_MODEL_IS_SUPPRESSED(0x0FC2D89AC25A5814);
lazy_func_t<int(Vehicle vehicle)>
	GET_VEHICLE_DOOR_LOCK_STATUS(0x25BC98A59C2EA962);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_FULLBEAM(0x8B7FD87F0DDB421E);
lazy_func_t<void(Vehicle vehicle)>
	_DETACH_VEHICLE_WINDSCREEN(0x6D645D59FB5F5AD3);
lazy_func_t<float(Vehicle vehicle, int door)>
	GET_VEHICLE_DOOR_ANGLE_RATIO(0xFE3F9C29F7B32BD5);
lazy_func_t<void(Vehicle plane, int height)>
	_SET_PLANE_MIN_HEIGHT_ABOVE_TERRAIN(0xB893215D8D4C015B);
lazy_func_t<Any(Vehicle vehicle, int windowIndex)>
	ROLL_DOWN_WINDOW(0x7AD9E6CE657D69E3);
lazy_func_t<void(Any p0, BOOL p1)> _0x063AE2B2CC273588(0x063AE2B2CC273588);
lazy_func_t<void(Vehicle vehicle)> TRACK_VEHICLE_VISIBILITY(0x64473AEFDCF47DCA);
lazy_func_t<void(Any p0, Any p1)> _0x79DF7E806202CE01(0x79DF7E806202CE01);
lazy_func_t<void(Any p0, BOOL p1)> _0x1F2E4E06DEA8992B(0x1F2E4E06DEA8992B);
lazy_func_t<void(Vehicle vehicle, int duration, Hash mode, BOOL forever)>
	START_VEHICLE_HORN(0x9C8C6504B5B63D2C);
lazy_func_t<BOOL(Vehicle vehicle, Entity *entity)>
	_GET_VEHICLE_OWNER(0x8F5EBAB1F260CFCE);
lazy_func_t<BOOL(const char *decorator)>
	DOES_VEHICLE_EXIST_WITH_DECORATOR(0x956B409B984D9BF7);
lazy_func_t<void(Vehicle vehicle, float distance, int killEngine, BOOL unknown)>
	_SET_VEHICLE_HALT(0x260BE8F09E326A20);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x0A6A279F3AA4FD70(0x0A6A279F3AA4FD70);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x06582AFF74894C75(0x06582AFF74894C75);
lazy_func_t<void(Vehicle vehicle, int state)>
	CONTROL_LANDING_GEAR(0xCFC8BE9A5E1FE575);
lazy_func_t<BOOL(Vehicle vehicle)>
	GET_IS_RIGHT_VEHICLE_HEADLIGHT_DAMAGED(0xA7ECB73355EB2F20);
lazy_func_t<void()> DELETE_ALL_TRAINS(0x736A718577F39C7D);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	SET_CONVERTIBLE_ROOF(0xF39C4F538B5124C2);
lazy_func_t<int(Vehicle vehicle)> _0xEEBFC7A7EFDC35B4(0xEEBFC7A7EFDC35B4);
lazy_func_t<float(Vehicle vehicle)> _0x6636C535F6CC2725(0x6636C535F6CC2725);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_SET_VEHICLE_CREATES_MONEY_PICKUPS_WHEN_EXPLODED(0x068F64F2470F9656);
lazy_func_t<void(float multiplier)>
	SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0xEAE6DCC7EEE3DB1D);
lazy_func_t<BOOL(Vehicle vehicle)>
	_IS_VEHICLE_SIREN_SOUND_ON(0xB5CC40FBCB586380);
lazy_func_t<BOOL(Hash model)> _IS_THIS_MODEL_A_JETSKI(0x9537097412CF75FE);
lazy_func_t<void(Vehicle vehicle, float p1)>
	SET_VEHICLE_CEILING_HEIGHT(0xA46413066687A328);
lazy_func_t<void(Vehicle vehicle, int p1)>
	_SET_VEHICLE_LIGHTS_MODE(0x1FD09E7390A74D54);
lazy_func_t<Any(Any p0, Any p1)>
	GET_TOTAL_DURATION_OF_VEHICLE_RECORDING(0x0E48D1C262390950);
lazy_func_t<void(Vehicle vehicle, int doorIndex, BOOL closeInstantly)>
	SET_VEHICLE_DOOR_SHUT(0x93D9BD300D7789E5);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(0x71B0892EC081D60A);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_BURNOUT(0xFB8794444A7D60FB);
lazy_func_t<void()> SET_ALL_VEHICLE_GENERATORS_ACTIVE(0x34AD89078831A4BC);
lazy_func_t<BOOL(Vehicle vehicle, Any p1)>
	_0xE33FFA906CE74880(0xE33FFA906CE74880);
lazy_func_t<float(Hash modelHash)>
	GET_VEHICLE_MODEL_ACCELERATION(0x8C044C5C84505B6A);
lazy_func_t<void(Vehicle vehicle, int *r, int *g, int *b)>
	GET_VEHICLE_TYRE_SMOKE_COLOR(0xB635392A4938B3C3);
lazy_func_t<void(Vehicle vehicle, float p1)>
	_0x182F266C2D9E2BEB(0x182F266C2D9E2BEB);
lazy_func_t<float(Vehicle vehicle)> GET_VEHICLE_BODY_HEALTH(0xF271147EB7B40F12);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	STEER_UNLOCK_BIAS(0x07116E24E9D1929D);
lazy_func_t<int(Vehicle vehicle)> GET_NUM_MOD_KITS(0x33F2E3FE70EAAE1D);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	_0x5E569EC46EC21CAE(0x5E569EC46EC21CAE);
lazy_func_t<BOOL(Vehicle vehicle)> _0xD4C4642CB7F50B5D(0xD4C4642CB7F50B5D);
lazy_func_t<void()> _0xF25E02CB9C5818F8(0xF25E02CB9C5818F8);
lazy_func_t<BOOL(Vehicle vehicle)>
	_ARE_PROPELLERS_UNDAMAGED(0x755D6D5267CBBD7E);
lazy_func_t<BOOL(Vehicle vehicle)>
	_IS_VEHICLE_MOD_LOAD_DONE(0x9A83F5F9963775EF);
lazy_func_t<BOOL(Vehicle vehicle, int index)>
	_IS_VEHICLE_NEON_LIGHT_ENABLED(0x8C4B92553E4766A5);
lazy_func_t<int(Vehicle vehicle)> _0xE6B0E8CFC3633BF0(0xE6B0E8CFC3633BF0);
lazy_func_t<int(Vehicle elegy)>
	GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(0xF11BC2DD9A3E7195);
lazy_func_t<BOOL(Vehicle vehicle, Player player)>
	GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(0xF6AF6CB341349015);
lazy_func_t<int(Vehicle vehicle)> GET_VEHICLE_LIVERY_COUNT(0x87B63E25A529D526);
lazy_func_t<float(int vehicleClass)>
	GET_VEHICLE_CLASS_MAX_BRAKING(0x4BF54C16EC8FEC03);
lazy_func_t<void(Vehicle vehicle, float x, float y)>
	_SET_BIKE_LEAN_ANGLE(0x9CFA4896C3A53CBB);
lazy_func_t<void(BOOL toggle)> _DISPLAY_DISTANT_VEHICLES(0xF796359A959DF65D);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	EXPLODE_VEHICLE_IN_CUTSCENE(0x786A4EB67B01BF0B);
lazy_func_t<void(Vehicle vehicle, BOOL state)>
	SET_VEHICLE_CAN_BE_TARGETTED(0x3750146A28097A82);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x56EB5E94318D3FB6(0x56EB5E94318D3FB6);
lazy_func_t<BOOL(Any p0)>
	IS_PLAYBACK_USING_AI_GOING_ON_FOR_VEHICLE(0xAEA8FD591FAD4106);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_PROVIDES_COVER(0x5AFEEDD9BB2899D7);
lazy_func_t<void(Vehicle vehicle, int p1, const char *playback, BOOL p3)>
	START_PLAYBACK_RECORDED_VEHICLE(0x3F878F92B3A7A071);
lazy_func_t<void(Any p0)> UNPAUSE_PLAYBACK_RECORDED_VEHICLE(0x8879EE09268305D5);
lazy_func_t<void(Vehicle towTruck, Vehicle vehicle)>
	DETACH_VEHICLE_FROM_TOW_TRUCK(0xC2DB6B6708350ED8);
lazy_func_t<BOOL(Vehicle vehicle)>
	GET_IS_LEFT_VEHICLE_HEADLIGHT_DAMAGED(0x5EF77C9ADD3B11A3);
lazy_func_t<void(Vehicle vehicle, int index, BOOL toggle)>
	_SET_VEHICLE_NEON_LIGHT_ENABLED(0x2AA720E4287BF269);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x33506883545AC0DF(0x33506883545AC0DF);
lazy_func_t<void(Vehicle vehicle, Vehicle p1)>
	_0x8F719973E1445BA2(0x8F719973E1445BA2);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x192547247864DFDD(0x192547247864DFDD);
lazy_func_t<BOOL(Vehicle vehicle, int extraId)>
	DOES_EXTRA_EXIST(0x1262D55792428154);
lazy_func_t<int(Vehicle vehicle, int modType)>
	GET_NUM_VEHICLE_MODS(0xE38E9162A2500646);
lazy_func_t<Any(int value)> SET_NUMBER_OF_PARKED_VEHICLES(0xCAA15F13EBD417FF);
lazy_func_t<int(Vehicle vehicle)>
	GET_CURRENT_PLAYBACK_FOR_VEHICLE(0x42BC05C27A946054);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_INTERIORLIGHT(0xBC2042F090AF6AD3);
lazy_func_t<void(Vehicle vehicle)>
	STOP_PLAYBACK_RECORDED_VEHICLE(0x54833611C17ABDEA);
lazy_func_t<void(Vehicle vehicle, BOOL toggle)>
	SET_VEHICLE_UNDRIVEABLE(0x8ABA6AF54B942B95);
lazy_func_t<BOOL(Vehicle vehicle, BOOL front)>
	IS_VEHICLE_BUMPER_BROKEN_OFF(0x468056A6BB6F3846);
lazy_func_t<void(Vehicle vehicle, float health)>
	SET_VEHICLE_ENGINE_HEALTH(0x45F6D8EEF34ABEF1);
lazy_func_t<BOOL(Vehicle vehicle)>
	DETACH_VEHICLE_FROM_ANY_TOW_TRUCK(0xD0E9CE05A1E68CD8);
lazy_func_t<int(Vehicle vehicle)>
	GET_VEHICLE_NUMBER_OF_PASSENGERS(0x24CB2137731FFE89);
lazy_func_t<BOOL(Vehicle vehicle)> _0x62CA17B74C435651(0x62CA17B74C435651);
lazy_func_t<void(Vehicle vehicle, BOOL instantlyLower)>
	LOWER_CONVERTIBLE_ROOF(0xDED51F703D0FA83D);
lazy_func_t<float(Vehicle vehicle)>
	GET_VEHICLE_PETROL_TANK_HEALTH(0x7D5DABE888D2D074);
lazy_func_t<void(Vehicle vehicle, float multiplier)>
	SET_VEHICLE_LOD_MULTIPLIER(0x93AE6A61BE015BF1);
lazy_func_t<void(Any p0, float p1, float p2, float p3)>
	_0x796A877E459B99EA(0x796A877E459B99EA);
lazy_func_t<
	Vehicle(float x, float y, float z, float radius, Hash modelHash, int flags)>
	GET_RANDOM_VEHICLE_IN_SPHERE(0x386F6CE5BAF6091C);
lazy_func_t<BOOL(Hash model)> IS_THIS_MODEL_A_BICYCLE(0xBF94DD42F63BDED2);
lazy_func_t<BOOL(float x1, float x2, float y1, float y2, float z1, float z2)>
	IS_COP_VEHICLE_IN_AREA_3D(0x7EEF65D5F153E26A);
lazy_func_t<void(BOOL toggle)> SET_FAR_DRAW_VEHICLES(0x26324F33423F3CC3);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0x8AA9180DE2FEDD45(0x8AA9180DE2FEDD45);
lazy_func_t<int(float x, float y, float z, float radius, float speed, BOOL p5)>
	_ADD_SPEED_ZONE_FOR_COORD(0x2CE544C68FB812A0);
lazy_func_t<Any(Any p0)> _0x36492C2F0D134C56(0x36492C2F0D134C56);
lazy_func_t<void(
	Vehicle vehicle,
	Vehicle trailer,
	float p2,
	float p3,
	float p4,
	float p5,
	float p6,
	float p7,
	float p8,
	float p9,
	float p10,
	float p11)>
	_0x16B5E274BDE402F8(0x16B5E274BDE402F8);
lazy_func_t<void(Vehicle towTruck, float height)>
	_SET_TOW_TRUCK_CRANE_HEIGHT(0xFE54B92A344583CA);
lazy_func_t<void(Vehicle vehicle, int colorCombination)>
	SET_VEHICLE_COLOUR_COMBINATION(0x33E8CD3322E2FE31);
lazy_func_t<void(Vehicle vehicle, int liveryIndex)>
	SET_VEHICLE_LIVERY(0x60BF608F1B8CD1B6);
lazy_func_t<float(Vehicle vehicle)> _GET_HELI_ENGINE_HEALTH(0xAC51915D27E4A5F7);
lazy_func_t<void(Any p0, BOOL p1)> _0x4D9D109F63FEE1D4(0x4D9D109F63FEE1D4);
lazy_func_t<void(Vehicle vehicle, BOOL p1)>
	_0xC361AA040D6637A8(0xC361AA040D6637A8);
lazy_func_t<BOOL(Vehicle vehicle, Hash model)>
	IS_VEHICLE_MODEL(0x423E8DE37D934D89);
lazy_func_t<void(Vehicle vehicle)>
	REMOVE_VEHICLE_STUCK_CHECK(0x8386BFB614D06749);
}} // namespace VEHICLE::
namespace UI { namespace {
lazy_func_t<Any(int p0, BOOL p1, int p2)>
	SET_MINIMAP_COMPONENT(0x75A9A10948D1DEA6);
lazy_func_t<void(
	const char *entryHeader,
	const char *entryLine1,
	Any instructionalKey,
	const char *entryLine2,
	BOOL p4,
	Any p5,
	Any p6,
	Any *p7,
	Any *p8,
	BOOL p9)>
	_SET_WARNING_MESSAGE_3(0x701919482C74B5AB);
lazy_func_t<void(BOOL p0)> _0xECF128344E9FF9F1(0xECF128344E9FF9F1);
lazy_func_t<void(BOOL p0)> _0xBA8D65C1C65702E5(0xBA8D65C1C65702E5);
lazy_func_t<void(int p0, int p1)> SET_MULTIPLAYER_HUD_CASH(0xFD1D220394BCB824);
lazy_func_t<void(float x, float y, float z)>
	_0x0923DBF87DFF735E(0x0923DBF87DFF735E);
lazy_func_t<void(Blip blip, BOOL p1)> _0x75A16C3DA34F1245(0x75A16C3DA34F1245);
lazy_func_t<void()> _0xA4DEDE28B1814289(0xA4DEDE28B1814289);
lazy_func_t<int()> _GET_ACTIVE_WEBSITE_ID(0x01A358D9128B7A86);
lazy_func_t<void(BOOL p0, const char *name)>
	SET_MISSION_NAME(0x5F28ECF5FC84772F);
lazy_func_t<void(float x, float y)> LOCK_MINIMAP_POSITION(0x1279E861A329E73F);
lazy_func_t<Blip(Entity entity)> GET_BLIP_FROM_ENTITY(0xBC8DBDCA2436F7E8);
lazy_func_t<Any()> _0x2A25ADC48F87841F(0x2A25ADC48F87841F);
lazy_func_t<Any()> _0x593FEAE1F73392D4(0x593FEAE1F73392D4);
lazy_func_t<void()> _0xC65AB383CD91DF98(0xC65AB383CD91DF98);
lazy_func_t<void(float value, float maxValue)>
	SET_ABILITY_BAR_VALUE(0x9969599CCFF5D85E);
lazy_func_t<void(Blip *blip)> REMOVE_BLIP(0x86A652570E5F25DD);
lazy_func_t<void(float x, float y, float z)>
	_0xA905192A6781C41B(0xA905192A6781C41B);
lazy_func_t<void(int pedHandle, BOOL showViewCones)>
	_SET_PED_AI_BLIP(0xD30C50DF888D58B5);
lazy_func_t<const char *(const char *text, int position, int length)>
	_GET_TEXT_SUBSTRING(0x169BD9382084C8C0);
lazy_func_t<void(Blip blip, BOOL toggle)>
	SET_BLIP_HIGH_DETAIL(0xE2590BC29220CEBB);
lazy_func_t<void(Blip blip, BOOL toggle)> _SET_BLIP_SHRINK(0x2B6D467DAB714E8D);
lazy_func_t<void(Any p0, BOOL p1)> _0x25615540D894B814(0x25615540D894B814);
lazy_func_t<void(BOOL toggle)> TOGGLE_STEALTH_RADAR(0x6AFDFB93754950C7);
lazy_func_t<void(Blip blip, int duration)>
	SET_BLIP_FLASH_TIMER(0xD3CD6FD297AE87CC);
lazy_func_t<void(BOOL forcedShow)> _SHOW_WEAPON_WHEEL(0xEB354E5376BC81A7);
lazy_func_t<int(Blip blip)> GET_BLIP_HUD_COLOUR(0x729B5F1EFBC0AAEE);
lazy_func_t<BOOL(int slot)> HAS_ADDITIONAL_TEXT_LOADED(0x02245FE4BED318B8);
lazy_func_t<void()> CLEAR_PRINTS(0xCC33FA791322B9D9);
lazy_func_t<void(int hudIndex)>
	_SET_NOTIFICATION_COLOR_NEXT(0x39BBF623FC803EAC);
lazy_func_t<void(Any p0, BOOL p1)> _0xDCFB5D4DB8BF367E(0xDCFB5D4DB8BF367E);
lazy_func_t<void(Any p0, BOOL p1)> _0xC4278F70131BAA6D(0xC4278F70131BAA6D);
lazy_func_t<void(Any p0, Any p1, BOOL p2)>
	_0x3F5CC444DCAAA8F2(0x3F5CC444DCAAA8F2);
lazy_func_t<
	int(const char *picName1,
		const char *picName2,
		BOOL flash,
		int iconType,
		const char *sender,
		const char *subject)>
	_SET_NOTIFICATION_MESSAGE_2(0x1CCD9A37359072CF);
lazy_func_t<void(int hudIndex)>
	_SET_NOTIFICATION_BACKGROUND_COLOR(0x92F0DA1E27DB96DC);
lazy_func_t<void(Blip blip, float r, float g, float b)>
	SET_BLIP_SECONDARY_COLOUR(0x14892474891E09EB);
lazy_func_t<void(BOOL p0)> _0xE67C6DFD386EA5E7(0xE67C6DFD386EA5E7);
lazy_func_t<void(BOOL p0)> _0x82CEDC33687E1F50(0x82CEDC33687E1F50);
lazy_func_t<void()> _0xE1CD1E48E025E661(0xE1CD1E48E025E661);
lazy_func_t<const char *(const char *text, int startPosition, int endPosition)>
	_GET_TEXT_SUBSTRING_SLICE(0xCE94AEBA5D82908A);
lazy_func_t<BOOL(const char *gxt)> DOES_TEXT_LABEL_EXIST(0xAC09CA973C564252);
lazy_func_t<void(int p0, float p1)> SET_GPS_FLAGS(0x5B440763A4C8D15B);
lazy_func_t<void(BOOL p0)> _0xF06EBB91A81E09E3(0xF06EBB91A81E09E3);
lazy_func_t<void()> _0x56C8B608CFD49854(0x56C8B608CFD49854);
lazy_func_t<void(float x, float y)>
	_SET_PLAYER_BLIP_POSITION_THIS_FRAME(0x77E2DD177910E1CF);
lazy_func_t<void(Any p0)> _0x71BDB63DBAF8DA59(0x71BDB63DBAF8DA59);
lazy_func_t<BOOL(Any p0)> _0xDAF87174BE7454FF(0xDAF87174BE7454FF);
lazy_func_t<void()> DISABLE_FRONTEND_THIS_FRAME(0x6D3465A73092F0E6);
lazy_func_t<void(const char *text)>
	_BEGIN_TEXT_COMMAND_WIDTH(0x54CE8AC98E120CAB);
lazy_func_t<void(Any *p0, Any *p1)> _0x36C1451A88A09630(0x36C1451A88A09630);
lazy_func_t<void(int id)> HIDE_HUD_COMPONENT_THIS_FRAME(0x6806C51AD12B83B8);
lazy_func_t<void()> UNLOCK_MINIMAP_ANGLE(0x8183455E16C42E3A);
lazy_func_t<void()> CLEAR_BRIEF(0x9D292F73ADBD9313);
lazy_func_t<void(BOOL p0)> _SET_TEXT_CHAT_UNK(0x1DB21A44B09E8BA3);
lazy_func_t<
	int(BOOL p0,
		BOOL p1,
		int *p2,
		int p3,
		BOOL isLeader,
		BOOL unk0,
		int clanDesc,
		const char *playerName,
		int R,
		int G,
		int B)>
	_DRAW_NOTIFICATION_CLAN_INVITE(0x137BC35589E34E1E);
lazy_func_t<int(const char *STRING)> _GET_LENGTH_OF_STRING(0x43E4111189E54F0E);
lazy_func_t<void(int renderId)> SET_TEXT_RENDER_ID(0x5F15302936E07111);
lazy_func_t<void(BOOL p0)> _0xCEF214315D276FD1(0xCEF214315D276FD1);
lazy_func_t<int(int type, const char *button, const char *text)>
	_DRAW_NOTIFICATION_WITH_BUTTON(0xDD6CB2CCE7C2735C);
lazy_func_t<void(BOOL p0)> _0x14C9FDCC41F81F63(0x14C9FDCC41F81F63);
lazy_func_t<Any()> _0xF13FE2A80C05C561(0xF13FE2A80C05C561);
lazy_func_t<void()> CLEAR_SMALL_PRINTS(0x2CEA2839313C09AC);
lazy_func_t<void(BOOL p0)> _0x41350B4FC28E3941(0x41350B4FC28E3941);
lazy_func_t<void(Hash interior, float x, float y, int heading, int zoom)>
	SET_RADAR_AS_INTERIOR_THIS_FRAME(0x59E727A1C9D3E31A);
lazy_func_t<BOOL(Any p0)> _0x09C0403ED9A751C2(0x09C0403ED9A751C2);
lazy_func_t<void()> _0xFDEC055AB549E328(0xFDEC055AB549E328);
lazy_func_t<void(const char *gxtentry)>
	BEGIN_TEXT_COMMAND_SET_BLIP_NAME(0xF9113A30DE5C6670);
lazy_func_t<void()> REMOVE_MULTIPLAYER_HUD_CASH(0x968F270E39141ECA);
lazy_func_t<void(Hash weaponHash)> _0x72C1056D678BB7D8(0x72C1056D678BB7D8);
lazy_func_t<void()> _0x35EDD5B2E3FF01C0(0x35EDD5B2E3FF01C0);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3)>
	_0xC8F3AAF93D0600BF(0xC8F3AAF93D0600BF);
lazy_func_t<Vector3(Blip blip)> GET_BLIP_INFO_ID_COORD(0xFA7C7F0AADF25D09);
lazy_func_t<
	int(const char *picName1,
		const char *picName2,
		BOOL flash,
		int iconType1,
		const char *sender,
		const char *subject,
		float duration,
		const char *clanTag,
		int iconType2,
		int p9)>
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2(0x531B84E7DA981FB6);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	_0xDB34E8D56FC13B08(0xDB34E8D56FC13B08);
lazy_func_t<void()> _SHOW_CURSOR_THIS_FRAME(0xAAE7CE1D63167423);
lazy_func_t<
	int(BOOL p0,
		BOOL p1,
		int *p2,
		int p3,
		BOOL isLeader,
		BOOL unk0,
		int clanDesc,
		int R,
		int G,
		int B)>
	_DRAW_NOTIFICATION_APARTMENT_INVITE(0x97C9E4E7024A8F2C);
lazy_func_t<void()> SET_MULTIPLAYER_BANK_CASH(0xDD21B55DF695CD0A);
lazy_func_t<
	int(const char *picName1,
		const char *picName2,
		BOOL p2,
		Any p3,
		const char *p4,
		const char *p5)>
	_SET_NOTIFICATION_MESSAGE_3(0xC6F580E4C94926AC);
lazy_func_t<BOOL()> IS_HELP_MESSAGE_FADING_OUT(0x327EDEEEAC55C369);
lazy_func_t<void(int *p0, int *p1, int *p2)>
	_0x7E17BE53E1AAABAF(0x7E17BE53E1AAABAF);
lazy_func_t<void(float zoomLevel)>
	_SET_RADAR_ZOOM_LEVEL_THIS_FRAME(0xCB7CC0D58405AD41);
lazy_func_t<void()> END_TEXT_COMMAND_CLEAR_PRINT(0xFCC75460ABA29378);
lazy_func_t<void(Blip blip)> PULSE_BLIP(0x742D6FD43115AF73);
lazy_func_t<void(Blip blip, BOOL toggle)> SET_BLIP_BRIGHT(0xB203913733F27884);
lazy_func_t<void(float altitude, BOOL p1)>
	_SET_MINIMAP_ATTITUDE_INDICATOR_LEVEL(0xD201F3FF917A506D);
lazy_func_t<int(BOOL blink, BOOL p1)> _DRAW_NOTIFICATION_2(0x44FA03975424A0EE);
lazy_func_t<Any()> _0x2F057596F2BD0061(0x2F057596F2BD0061);
lazy_func_t<BOOL(Any p0, Any *p1, Any p2, Any p3, Any p4)>
	_0x24A49BEAF468DC90(0x24A49BEAF468DC90);
lazy_func_t<void(int gamerTagId, int component, int alpha)>
	SET_MP_GAMER_TAG_ALPHA(0xD48FE545CD46F857);
lazy_func_t<Any(Any *p0, Any *p1, Any *p2, BOOL p3, BOOL p4)>
	_0x8EFCCF6EC66D85E4(0x8EFCCF6EC66D85E4);
lazy_func_t<void(int distance, int r, int g, int b, int a)>
	SET_TEXT_DROPSHADOW(0x465C84BC39F1C351);
lazy_func_t<void(int p0, int r, int g, int b, int a)>
	SET_TEXT_EDGE(0x441603240D202FA6);
lazy_func_t<void(BOOL p0)> _0x98215325A695E78A(0x98215325A695E78A);
lazy_func_t<BOOL(Blip blip)> IS_BLIP_SHORT_RANGE(0xDA5F8727EB75B926);
lazy_func_t<void(float x, float y)> SET_NEW_WAYPOINT(0xFE43368D2AA4F2FC);
lazy_func_t<void(
	BOOL p0,
	Any *p1,
	Any *p2,
	Any *p3,
	Any *p4,
	Any *p5,
	Any *p6,
	Any *p7,
	Any *p8)>
	_0x817B86108EB94E51(0x817B86108EB94E51);
lazy_func_t<void(Any p0, Any p1, float p2, float p3)>
	_0xB094BC1DB4018240(0xB094BC1DB4018240);
lazy_func_t<Any(float p0, float p1, float p2)>
	_0x551DF99658DB6EE8(0x551DF99658DB6EE8);
lazy_func_t<Pickup(Blip blip)>
	GET_BLIP_INFO_ID_PICKUP_INDEX(0x9B6786E4C03DD382);
lazy_func_t<void(int headDisplayId, int color)>
	SET_MP_GAMER_TAG_HEALTH_BAR_COLOUR(0x3158C77A7E888AB4);
lazy_func_t<void(Any p0)> _0x0CF54F20DE43879C(0x0CF54F20DE43879C);
lazy_func_t<void(int duration, BOOL drawImmediately)>
	END_TEXT_COMMAND_PRINT(0x9D77056A530643F6);
lazy_func_t<Any(BOOL p0)> FLASH_WANTED_DISPLAY(0xA18AFB39081B6A1F);
lazy_func_t<BOOL(Any *p0)> RELEASE_NAMED_RENDERTARGET(0xE9F6FFE837354DD4);
lazy_func_t<void(Any p0, BOOL p1)> _0x54318C915D27E4CE(0x54318C915D27E4CE);
lazy_func_t<void(int spriteId)> _SET_CURSOR_SPRITE(0x8DB8CFFD58B62552);
lazy_func_t<void(Blip blip, float posX, float posY, float posZ)>
	SET_BLIP_COORDS(0xAE2AF67E9D9AF65D);
lazy_func_t<void(Blip blip, int color)> SET_BLIP_COLOUR(0x03D7FB09E75D6B7E);
lazy_func_t<void(Any p0)> _0x77F16B447824DA6C(0x77F16B447824DA6C);
lazy_func_t<BOOL(Ped ped)> DOES_PED_HAVE_AI_BLIP(0x15B8ECF844EE67ED);
lazy_func_t<void(Hash hash)> LINK_NAMED_RENDERTARGET(0xF6C09E276AEB3F2D);
lazy_func_t<void(Blip blip, int colour)>
	SET_BLIP_ROUTE_COLOUR(0x837155CD2F63DA09);
lazy_func_t<void(Any p0, float p1)> _0xF98E4B3E56AFC7B1(0xF98E4B3E56AFC7B1);
lazy_func_t<void(Blip blip, float scale)> SET_BLIP_SCALE(0xD38744167B2FA257);
lazy_func_t<void(Any p0, BOOL p1)>
	HIDE_SPECIAL_ABILITY_LOCKON_OPERATION(0x3EED80DFF7325CAA);
lazy_func_t<Blip *(Ped ped)> _0x7CD934010E115C2C(0x7CD934010E115C2C);
lazy_func_t<void(Blip blip)> END_TEXT_COMMAND_SET_BLIP_NAME(0xBC38B49BCB83BC9B);
lazy_func_t<void(Ped ped)> _0xC594B315EDF2D4AF(0xC594B315EDF2D4AF);
lazy_func_t<BOOL()> IS_WARNING_MESSAGE_ACTIVE(0xE18B138FABC53103);
lazy_func_t<void(BOOL p0)> _0x6F1554B0CC2089FA(0x6F1554B0CC2089FA);
lazy_func_t<void(Any p0)> _0x17AD8C9706BDD88A(0x17AD8C9706BDD88A);
lazy_func_t<int(BOOL blink, BOOL p1)> _DRAW_NOTIFICATION_3(0x378E809BF61EC840);
lazy_func_t<void()> CLEAR_PED_IN_PAUSE_MENU(0x5E62BE5DC58E9E06);
lazy_func_t<void()> _ABORT_TEXT_CHAT(0x1AC8F4AD40E22127);
lazy_func_t<void()> _0xD4438C0564490E63(0xD4438C0564490E63);
lazy_func_t<void(float scale, float size)> SET_TEXT_SCALE(0x07C837F9A01C34C9);
lazy_func_t<void(Blip blip, BOOL toggle)>
	_SET_BLIP_FRIENDLY(0xB81656BC81FE24D1);
lazy_func_t<void()> _0xCC3FDDED67BCFC63(0xCC3FDDED67BCFC63);
lazy_func_t<Any()> _0xF284AC67940C6812(0xF284AC67940C6812);
lazy_func_t<void()> CLEAR_ALL_HELP_MESSAGES(0x6178F68A87A4D3A0);
lazy_func_t<void(Blip blip, BOOL toggle)>
	SET_BLIP_AS_SHORT_RANGE(0xBE8BE4FE60E27B72);
lazy_func_t<void(BOOL toggle)> DISPLAY_CASH(0x96DEC8D5430208B7);
lazy_func_t<void(BOOL p0)> _0x1EAC5F91BCBC5073(0x1EAC5F91BCBC5073);
lazy_func_t<Vector3(int id)> GET_HUD_COMPONENT_POSITION(0x223CA69A8C4417FD);
lazy_func_t<void()> _0x583049884A2EEE3C(0x583049884A2EEE3C);
lazy_func_t<BOOL()> IS_HELP_MESSAGE_BEING_DISPLAYED(0x4D79439A6B55AC67);
lazy_func_t<void(Blip blip, int number)>
	SHOW_NUMBER_ON_BLIP(0xA3C0B359DCB848B6);
lazy_func_t<BOOL(int gamerTagId)> _HAS_MP_GAMER_TAG_2(0xEB709A36958ABE0D);
lazy_func_t<
	int(const char *picName1,
		int picName2,
		BOOL flash,
		int iconType,
		BOOL p4,
		const char *sender,
		const char *subject)>
	_SET_NOTIFICATION_MESSAGE(0x2B7E9A4EAAA93C89);
lazy_func_t<Any()> _0x4E3CD0EF8A489541(0x4E3CD0EF8A489541);
lazy_func_t<BOOL(Any p0, Any *p1)> SET_USERIDS_UIHIDDEN(0xEF4CED81CEBEDC6D);
lazy_func_t<BOOL(Hash p0, Any *p1)> _0x052991E59076E4E4(0x052991E59076E4E4);
lazy_func_t<Entity(Blip blip)>
	GET_BLIP_INFO_ID_ENTITY_INDEX(0x4BA4E2553AFEDC2C);
lazy_func_t<void(BOOL p0)> SET_TEXT_PROPORTIONAL(0x038C1F517D7FDCF8);
lazy_func_t<void()> CLEAR_GPS_PLAYER_WAYPOINT(0xFF4FB7C8CDFA3DA7);
lazy_func_t<void(const char *text)>
	ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(0x6C188BE134E074AA);
lazy_func_t<BOOL(int gamerTagId)>
	ADD_TREVOR_RANDOM_MODIFIER(0x595B5178E412E199);
lazy_func_t<Any(BOOL Toggle)> DISPLAY_RADAR(0xA0EBB943C300E693);
lazy_func_t<Any()> _0x359AF31A4B52F5ED(0x359AF31A4B52F5ED);
lazy_func_t<void(int justifyType)> SET_TEXT_JUSTIFICATION(0x4E096588B13FFECA);
lazy_func_t<BOOL()> IS_WAYPOINT_ACTIVE(0x1DD1F58F493F1DA5);
lazy_func_t<void(const char *message, BOOL p1)>
	DISPLAY_HELP_TEXT_THIS_FRAME(0x960C9FF8F616E41C);
lazy_func_t<Any()> _0xDE03620F8703A9DF(0xDE03620F8703A9DF);
lazy_func_t<void(const char *p0)> _0x9E778248D6685FE0(0x9E778248D6685FE0);
lazy_func_t<void(const char *text)>
	BEGIN_TEXT_COMMAND_CLEAR_PRINT(0xE124FA80A759019C);
lazy_func_t<void(BOOL p0)> _0x60734CC207C9833C(0x60734CC207C9833C);
lazy_func_t<void(Blip blip, BOOL toggle)>
	SET_BLIP_FLASHES_ALTERNATE(0x2E8D9498C56DD0D1);
lazy_func_t<void(BOOL active)> SET_FRONTEND_ACTIVE(0x745711A75AB09277);
lazy_func_t<void(int r, int g, int b, int a)>
	_0xD68A5FF8A3A89874(0xD68A5FF8A3A89874);
lazy_func_t<int(const char *gxt)>
	GET_LENGTH_OF_STRING_WITH_THIS_TEXT_LABEL(0x801BD273D3A23F74);
lazy_func_t<Blip(Entity entity)> ADD_BLIP_FOR_ENTITY(0x5CDE92C702A8FCE7);
lazy_func_t<void(Any p0, float x, float y, float z)>
	_0x784BA7E0ECEB4178(0x784BA7E0ECEB4178);
lazy_func_t<void()> _0xD2B32BE3FC1626C6(0xD2B32BE3FC1626C6);
lazy_func_t<void()> _0xFDD85225B2DEA55E(0xFDD85225B2DEA55E);
lazy_func_t<BOOL()> IS_RADAR_PREFERENCE_SWITCHED_ON(0x9EB6522EA68F22FE);
lazy_func_t<void()> _0x402F9ED62087E898(0x402F9ED62087E898);
lazy_func_t<BOOL()> IS_HELP_MESSAGE_ON_SCREEN(0xDAD37F45428801AE);
lazy_func_t<void()> _DISPLAY_JOB_REPORT(0x523A590C1A3CC0D3);
lazy_func_t<void()> _0x80FE4F3AB4E1B62A(0x80FE4F3AB4E1B62A);
lazy_func_t<BOOL(const char *p0)>
	IS_NAMED_RENDERTARGET_REGISTERED(0x78DCDC15C9F116B4);
lazy_func_t<void(BOOL toggle)> SET_TEXT_RIGHT_JUSTIFY(0x6B3C4650BC8BEE47);
lazy_func_t<void()> HIDE_LOADING_ON_FADE_THIS_FRAME(0x4B0311D3CDC4648F);
lazy_func_t<void(BOOL p0, Any p1, Any p2)>
	_0x900086F371220B6F(0x900086F371220B6F);
lazy_func_t<void(const char *labelName)>
	BEGIN_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(0x0A24DA3A41B718F5);
lazy_func_t<void(Blip blip)>
	ADD_TEXT_COMPONENT_SUBSTRING_BLIP_NAME(0x80EAD8E2E1D5D52E);
lazy_func_t<void(float posX, float posY, float posZ, float radius, int p4)>
	_0x72DD432F3CDFC0EE(0x72DD432F3CDFC0EE);
lazy_func_t<void(Hash gxtEntryHash)>
	ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL_HASH_KEY(0x17299B63C7683A2B);
lazy_func_t<void(const char *text)>
	BEGIN_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(0x853648FD1063A213);
lazy_func_t<void()> HIDE_HELP_TEXT_THIS_FRAME(0xD46923FC481CA285);
lazy_func_t<Hash()> _GET_CURRENT_FRONTEND_MENU(0x2309595AD6145265);
lazy_func_t<void(Hash hash)> OBJECT_DECAL_TOGGLE(0x444D8CF241EC25C5);
lazy_func_t<Any(Any *p0, Any *p1, Any p2, Any *p3, Any *p4, Any p5)>
	_0xB6871B0555B02996(0xB6871B0555B02996);
lazy_func_t<void(int r, int g, int b, int a)>
	_0x16A304E6CB2BFAB9(0x16A304E6CB2BFAB9);
lazy_func_t<BOOL(
	float worldX, float worldY, float worldZ, float *screenX, float *screenY)>
	_GET_SCREEN_COORD_FROM_WORLD_COORD(0xF9904D11F1ACBEC3);
lazy_func_t<void(int headDisplayId, BOOL p1)>
	_SET_MP_GAMER_TAG_(0xEE76FF7E6A0166B0);
lazy_func_t<void(int gamerTagId, int flag, int color)>
	SET_MP_GAMER_TAG_COLOUR(0x613ED644950626AE);
lazy_func_t<void(const char *p0)> _LOG_DEBUG_INFO(0x2162C446DFDF38FD);
lazy_func_t<void()> _0xADED7F5748ACAFE6(0xADED7F5748ACAFE6);
lazy_func_t<void(BOOL p0)> _END_TEXT_COMMAND_OBJECTIVE(0xCFDBDF5AE59BA0F4);
lazy_func_t<void(Blip blip)> HIDE_NUMBER_ON_BLIP(0x532CFF637EF80148);
lazy_func_t<BOOL(Hash hash)> _0x84698AB38D0C6636(0x84698AB38D0C6636);
lazy_func_t<void()> _0x25F87B30C382FCA7(0x25F87B30C382FCA7);
lazy_func_t<
	int(Ped ped,
		const char *username,
		BOOL pointedClanTag,
		BOOL isRockstarClan,
		const char *clanTag,
		Any p5)>
	_CREATE_MP_GAMER_TAG(0xBFEFE3321A3F5015);
lazy_func_t<BOOL()> IS_SOCIAL_CLUB_ACTIVE(0xC406BE343FC4B9AF);
lazy_func_t<BOOL(int scaleformHandle, Any *p1, Any *p2, Any *p3)>
	_0x632B2940C67F4EA9(0x632B2940C67F4EA9);
lazy_func_t<BOOL()> END_TEXT_COMMAND_IS_MESSAGE_DISPLAYED(0x8A9BA1AB3E237613);
lazy_func_t<BOOL(Any p0, Any *p1, Any p2)>
	_0x8F08017F9D7C47BD(0x8F08017F9D7C47BD);
lazy_func_t<void(BOOL toggle)> SET_MINIMAP_BLOCK_WAYPOINT(0x58FADDED207897DC);
lazy_func_t<void(Any p0, float p1, float p2)>
	_0x7679CC1BCEBE3D4C(0x7679CC1BCEBE3D4C);
lazy_func_t<Blip(int blipSprite)> GET_FIRST_BLIP_INFO_ID(0x1BEDE233E6CD2A1F);
lazy_func_t<
	int(const char *picName1,
		const char *picName2,
		BOOL flash,
		int iconType,
		const char *sender,
		const char *subject,
		float duration)>
	_SET_NOTIFICATION_MESSAGE_4(0x1E6611149DB3DB6B);
lazy_func_t<void(BOOL p0)> _0x57D760D55F54E071(0x57D760D55F54E071);
lazy_func_t<int()> _GET_BLIP_INFO_ID_ITERATOR(0x186E5D252FA50E7D);
lazy_func_t<void()> _BLOCK_WEAPON_WHEEL_THIS_FRAME(0x0AFC4AF510774B47);
lazy_func_t<BOOL(float x, float y, float radius)>
	_IS_MINIMAP_AREA_REVEALED(0x6E31B91145873922);
lazy_func_t<BOOL(Any *p0, Any *p1, Any *p2)>
	_0xC8E1071177A23BE5(0xC8E1071177A23BE5);
lazy_func_t<int()> _GET_CURRENT_NOTIFICATION(0x82352748437638CA);
lazy_func_t<void(BOOL p0)> _0xBAE4F9B97CD43B30(0xBAE4F9B97CD43B30);
lazy_func_t<void(const char *text)>
	_SET_NOTIFICATION_TEXT_ENTRY(0x202709F4C58A0424);
lazy_func_t<BOOL()> IS_RADAR_HIDDEN(0x157F93B036700462);
lazy_func_t<void(Any p0)> _0x7B21E0BB01E8224A(0x7B21E0BB01E8224A);
lazy_func_t<void()> _0x8817605C2BA76200(0x8817605C2BA76200);
lazy_func_t<Any()> _0x3D9ACB1EB139E702(0x3D9ACB1EB139E702);
lazy_func_t<int(Blip blip)> GET_BLIP_COLOUR(0xDF729E8D20CF7327);
lazy_func_t<void(BOOL toggle)> _SET_NORTH_YANKTON_MAP(0x9133955F1A2DA957);
lazy_func_t<void(
	int headDisplayId,
	const char *username,
	BOOL pointedClanTag,
	BOOL isRockstarClan,
	const char *clanTag,
	Any p5,
	int r,
	int g,
	int b)>
	_SET_MP_GAMER_TAG_COLOR(0x6DD05E9D83EFA4C9);
lazy_func_t<void(BOOL p0)> ENABLE_DEATHBLOOD_SEETHROUGH(0x4895BDEA16E7C080);
lazy_func_t<void()> _0x2632482FD6B9AB87(0x2632482FD6B9AB87);
lazy_func_t<BOOL(int p0)>
	END_TEXT_COMMAND_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(0x10BDDBFC529428DD);
lazy_func_t<const char *()>
	_IS_LOADING_PROMPT_BEING_DISPLAYED(0xD422FCC5F239A915);
lazy_func_t<void(Blip blip, int spriteId)> SET_BLIP_SPRITE(0xDF735600A4696DAF);
lazy_func_t<void()> FLASH_MINIMAP_DISPLAY(0xF2DD778C22B15BDA);
lazy_func_t<void(int gamerTagId, const char *string)>
	_SET_MP_GAMER_TAG_CHATTING(0x7B7723747CCB55B6);
lazy_func_t<Any(const char *p0)>
	GET_NAMED_RENDERTARGET_RENDER_ID(0x1A6478B61C6BDC3B);
lazy_func_t<
	int(const char *picName1,
		const char *picName2,
		BOOL flash,
		int iconType,
		const char *sender,
		const char *subject,
		float duration,
		const char *clanTag)>
	_SET_NOTIFICATION_MESSAGE_CLAN_TAG(0x5CBF7BADE20DB93E);
lazy_func_t<int(BOOL blink, BOOL p1)> _DRAW_NOTIFICATION_4(0xF020C96915705B3A);
lazy_func_t<void(BOOL toggle)> CLEAR_HELP(0x8DFCED7A656F8802);
lazy_func_t<void(Hash hash)> _ADD_FRONTEND_MENU_CONTEXT(0xDD564BDD0472C936);
lazy_func_t<void(int red, int green, int blue, int alpha)>
	_SET_NOTIFICATION_FLASH_COLOR(0x17430B918701C342);
lazy_func_t<void(Blip blip, Any p1)>
	SET_BLIP_FLASH_INTERVAL(0xAA51DB313C010A7E);
lazy_func_t<void(int id)> SHOW_HUD_COMPONENT_THIS_FRAME(0x0B4DF1FA60C0E664);
lazy_func_t<void()> _0x6EF54AB721DC6242(0x6EF54AB721DC6242);
lazy_func_t<Any(Any p0, Any p1, Any p2)>
	_0x33EE12743CCD6343(0x33EE12743CCD6343);
lazy_func_t<int(Blip blip)> GET_BLIP_INFO_ID_DISPLAY(0x1E314167F701DC3B);
lazy_func_t<BOOL()> _0x4167EFE0527D706E(0x4167EFE0527D706E);
lazy_func_t<void()> RESET_RETICULE_VALUES(0x12782CE0A636E9F0);
lazy_func_t<BOOL(Any p0)> _0x2432784ACA090DA4(0x2432784ACA090DA4);
lazy_func_t<Any()> _0x66E7CB63C97B7D20(0x66E7CB63C97B7D20);
lazy_func_t<void(Any p0, BOOL loop, BOOL beep, int duration)>
	END_TEXT_COMMAND_DISPLAY_HELP(0x238FFE5C7B0498A6);
lazy_func_t<void(int id)> RESET_HUD_COMPONENT_VALUES(0x450930E616475D0D);
lazy_func_t<BOOL()> IS_HUD_PREFERENCE_SWITCHED_ON(0x1930DFA731813EC4);
lazy_func_t<int(Blip blip)> GET_BLIP_ALPHA(0x970F608F0EE6C885);
lazy_func_t<void(Any p0)> SET_WIDESCREEN_FORMAT(0xC3B07BA00A83B0F1);
lazy_func_t<BOOL(int id)> IS_HUD_COMPONENT_ACTIVE(0xBC4C9EA5391ECC0D);
lazy_func_t<void(int gamerTagId)> REMOVE_MP_GAMER_TAG(0x31698AA80E0223F8);
lazy_func_t<void()> _0xFDB423997FA30340(0xFDB423997FA30340);
lazy_func_t<BOOL(const char *gxt, int slot)>
	HAS_THIS_ADDITIONAL_TEXT_LOADED(0xADBF060E2B30C5BC);
lazy_func_t<BOOL()> _IS_RADAR_ENABLED(0xAF754F20EB5CD51A);
lazy_func_t<void(BOOL toggle)> FLASH_ABILITY_BAR(0x02CFBA0C9E9275CE);
lazy_func_t<void(Blip blip, int index)> SET_BLIP_CATEGORY(0x234CDD44D996FD9A);
lazy_func_t<void(Any p0)> _0x6B1DE27EE78E6A19(0x6B1DE27EE78E6A19);
lazy_func_t<void(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	_0x788E7FD431BD67F1(0x788E7FD431BD67F1);
lazy_func_t<BOOL(Any p0, Any *p1, Any p2, Any p3)>
	_0x90A6526CF0381030(0x90A6526CF0381030);
lazy_func_t<void(const char *p0)> CLEAR_THIS_PRINT(0xCF708001E1E536DD);
lazy_func_t<void(Any p0, BOOL p1, BOOL p2)>
	_0x3D3D15AF7BCAAF83(0x3D3D15AF7BCAAF83);
lazy_func_t<Any()> _0x13C4B962653A5280(0x13C4B962653A5280);
lazy_func_t<void(int p0, BOOL p1)> CLEAR_ADDITIONAL_TEXT(0x2A179DF17CCF04CD);
lazy_func_t<void(int gamerTagId, int component, BOOL toggle)>
	SET_MP_GAMER_TAG_VISIBILITY(0x63BB75ABEDC1F6A0);
lazy_func_t<void()> _SHOW_SOCIAL_CLUB_LEGAL_SCREEN(0x805D7CBB36FD6C4C);
lazy_func_t<BOOL(int id)> IS_SCRIPTED_HUD_COMPONENT_ACTIVE(0xDD100EB17A94FF65);
lazy_func_t<void(const char *gxt, int slot)>
	_REQUEST_ADDITIONAL_TEXT_2(0x6009F9F1AE90D8A6);
lazy_func_t<void(Blip blip, BOOL toggle)> SET_BLIP_FLASHES(0xB14552383D39CE3E);
lazy_func_t<void()> _DISABLE_RADAR_THIS_FRAME(0x5FBAE526203990C9);
lazy_func_t<void(Any p0)> _0x975D66A0BC17064C(0x975D66A0BC17064C);
lazy_func_t<Any()> _0xA9CBFD40B3FA3010(0xA9CBFD40B3FA3010);
lazy_func_t<void(int id)>
	HIDE_SCRIPTED_HUD_COMPONENT_THIS_FRAME(0xE374C498D8BADC14);
lazy_func_t<void(BOOL toggle)> _SET_MAP_FULL_SCREEN(0x5354C5BA2EA868A4);
lazy_func_t<int()> _0x6F72CD94F7B5B68C(0x6F72CD94F7B5B68C);
lazy_func_t<Blip()> DISABLE_BLIP_NAME_FOR_VAR(0x5C90988E7C8E1AF4);
lazy_func_t<void(Any p0)> _0x06A320535F5F0248(0x06A320535F5F0248);
lazy_func_t<void(BOOL p0, Any p1, Any p2)>
	_0xC78E239AC5B2DDB9(0xC78E239AC5B2DDB9);
lazy_func_t<void(Blip blip, int alpha)> SET_BLIP_ALPHA(0x45FF974EEE1C8734);
lazy_func_t<float()> _0xE0130B41D3CF4574(0xE0130B41D3CF4574);
lazy_func_t<int()> GET_CURRENT_WEBSITE_ID(0x97D47996FC48CBAD);
lazy_func_t<void()> _0x7792424AA0EAC32E(0x7792424AA0EAC32E);
lazy_func_t<void(const char *p0)> _BEGIN_TEXT_COMMAND_TIMER(0x8F9EE5687F8EECCD);
lazy_func_t<void()> _0xD8E694757BCEA8E9(0xD8E694757BCEA8E9);
lazy_func_t<void(BOOL p0)> _END_TEXT_COMMAND_TIMER(0xA86911979638106F);
lazy_func_t<int()> GET_NUMBER_OF_ACTIVE_BLIPS(0x9A3FF3DE163034E8);
lazy_func_t<void(BOOL display)> DISPLAY_AMMO_THIS_FRAME(0xA5E78BA2B1331C55);
lazy_func_t<void(float x, float y)>
	END_TEXT_COMMAND_DISPLAY_TEXT(0xCD015E5BB0D96A57);
lazy_func_t<void(Blip blip, Player player)>
	SET_BLIP_NAME_TO_PLAYER_NAME(0x127DE7B20C60A6A3);
lazy_func_t<void()> _0x95CF81BD06EE1887(0x95CF81BD06EE1887);
lazy_func_t<void()> CLEAR_GPS_RACE_TRACK(0x7AA5B4CE533C858B);
lazy_func_t<int()> GET_PAUSE_MENU_STATE(0x272ACD84970869C5);
lazy_func_t<BOOL(const char *gxt)> DOES_TEXT_BLOCK_EXIST(0x1C7302E725259789);
lazy_func_t<Any()> _0x9049FE339D5F6F6F(0x9049FE339D5F6F6F);
lazy_func_t<void()> DISPLAY_SNIPER_SCOPE_THIS_FRAME(0x73115226F4814E62);
lazy_func_t<void(int angle)> LOCK_MINIMAP_ANGLE(0x299FAEBB108AE05B);
lazy_func_t<void()> SET_TEXT_DROP_SHADOW(0x1CA3E9EAC9D93E5E);
lazy_func_t<int()>
	GET_DEFAULT_SCRIPT_RENDERTARGET_RENDER_ID(0x52F0982D7FD156B6);
lazy_func_t<void(BOOL p0)> _0x170F541E1CADD1DE(0x170F541E1CADD1DE);
lazy_func_t<void(BOOL toggleBigMap, BOOL showFullMap)>
	_SET_RADAR_BIGMAP_ENABLED(0x231C8F89D0539D8F);
lazy_func_t<void()> _0xA8FDB297A8D25FBA(0xA8FDB297A8D25FBA);
lazy_func_t<void(const char *inputType)>
	BEGIN_TEXT_COMMAND_DISPLAY_HELP(0x8509B634FBE7DA11);
lazy_func_t<void()> SET_TEXT_OUTLINE(0x2513DFB0FB8400FE);
lazy_func_t<Any(Any p0, Any p1, Any p2, Any p3, Any p4, Any p5)>
	_0x7AE0589093A2E088(0x7AE0589093A2E088);
lazy_func_t<void(int value)> ADD_TEXT_COMPONENT_INTEGER(0x03B504CF259931BC);
lazy_func_t<Blip(int blipSprite)> GET_NEXT_BLIP_INFO_ID(0x14F96AA50D6FBEA7);
lazy_func_t<Any()> _0xAF42195A42C63BBA(0xAF42195A42C63BBA);
lazy_func_t<void(Blip blip, BOOL toggle)> SHOW_TICK_ON_BLIP(0x74513EA3E505181E);
lazy_func_t<BOOL()> IS_PAUSE_MENU_RESTARTING(0x1C491717107431C7);
lazy_func_t<Blip(Ped ped)> _GET_AI_BLIP(0x56176892826A4FE8);
lazy_func_t<void(BOOL toggle)> DISPLAY_HUD(0xA6294919E56FF02A);
lazy_func_t<
	const char *(const char *text, int position, int length, int maxLength)>
	_GET_TEXT_SUBSTRING_SAFE(0xB2798643312205C5);
lazy_func_t<int(const char *string)>
	GET_LENGTH_OF_LITERAL_STRING(0xF030907CCBB8A9FD);
lazy_func_t<void(BOOL p0)> _0xF1A6C18B35BCADE6(0xF1A6C18B35BCADE6);
lazy_func_t<void()> _0x67EEDEA1B9BAFD94(0x67EEDEA1B9BAFD94);
lazy_func_t<void(
	const char *entryHeader,
	const char *entryLine1,
	int instructionalKey,
	const char *entryLine2,
	BOOL p4,
	Any p5,
	Any *p6,
	Any *p7,
	BOOL background)>
	SET_WARNING_MESSAGE_WITH_HEADER(0xDC38CC1E35B6A5D7);
lazy_func_t<void(Ped ped, BOOL flag)>
	_IS_AI_BLIP_ALWAYS_SHOWN(0x0C4BBF625CA98C4E);
lazy_func_t<void(const char *p0)>
	_ADD_TEXT_COMPONENT_SCALEFORM(0x5F68520888E69014);
lazy_func_t<void()> _0x60E892BA4F5BDCA4(0x60E892BA4F5BDCA4);
lazy_func_t<void(Hash menuhash, BOOL Toggle_Pause, int component)>
	ACTIVATE_FRONTEND_MENU(0xEF01D36B9C9D0C7B);
lazy_func_t<void()> CLEAR_GPS_FLAGS(0x21986729D6A3A830);
lazy_func_t<void(int gamerTagId, int wantedlvl)>
	SET_MP_GAMER_TAG_WANTED_LEVEL(0xCF228E2AA03099C3);
lazy_func_t<void(Any p0)> _0x1EAE6DD17B7A5EFA(0x1EAE6DD17B7A5EFA);
lazy_func_t<Vector3()> _0x5BFF36D6ED83E0AE(0x5BFF36D6ED83E0AE);
lazy_func_t<void(const char *p0)>
	_BEGIN_TEXT_COMMAND_OBJECTIVE(0x23D69E0465570028);
lazy_func_t<BOOL()> _0x214CD562A939246A(0x214CD562A939246A);
lazy_func_t<void(
	const char *entryLine1,
	int instructionalKey,
	const char *entryLine2,
	BOOL p3,
	Any p4,
	Any *p5,
	Any *p6,
	BOOL background)>
	SET_WARNING_MESSAGE(0x7B1776B3B53F8D74);
lazy_func_t<BOOL(Any p0, Any *p1, Any p2, Any p3, Any p4, Any p5)>
	_0x0C5A80A9E096D529(0x0C5A80A9E096D529);
lazy_func_t<void()> _0x211C4EF450086857(0x211C4EF450086857);
lazy_func_t<void(Ped ped, float distance)>
	_SET_AI_BLIP_MAX_DISTANCE(0x97C65887D4B37FA9);
lazy_func_t<int(const char *p0, const char *p1, int p2, int p3, const char *p4)>
	_DRAW_NOTIFICATION_AWARD(0xAA295B6F28BD587D);
lazy_func_t<void(Blip blip, BOOL toggle)>
	SET_BLIP_AS_FRIENDLY(0x6F6F290102C02AB4);
lazy_func_t<void(Any p0, Any p1, Any p2)>
	_0x311438A071DD9B1A(0x311438A071DD9B1A);
lazy_func_t<BOOL()> _HAS_MP_GAMER_TAG(0x6E0EB3EB47C8D7AA);
lazy_func_t<void(BOOL p0)> _0x3CA6050692BC61B0(0x3CA6050692BC61B0);
lazy_func_t<void(Blip blip, int opacity, int duration)>
	SET_BLIP_FADE(0x2AEE8F8390D2298C);
lazy_func_t<BOOL()> IS_SUBTITLE_PREFERENCE_SWITCHED_ON(0xAD6DACA4BA53E0A4);
lazy_func_t<void(Blip blip, BOOL enabled)> SET_BLIP_ROUTE(0x4F7D8A9BFB0B43E9);
lazy_func_t<void(int hudColorIndex, int r, int g, int b, int a)>
	_SET_HUD_COLOUR(0xF314CF4F0211894E);
lazy_func_t<BOOL(Any p0)> _0xDD2238F57B977751(0xDD2238F57B977751);
lazy_func_t<void()> _0x75D3691713C3B05A(0x75D3691713C3B05A);
lazy_func_t<float(BOOL p0)> _END_TEXT_COMMAND_GET_WIDTH(0x85F061DA64ED2F67);
lazy_func_t<void(int red, int green, int blue, int alpha)>
	SET_TEXT_COLOUR(0xBE6B23FFA53FB442);
lazy_func_t<Blip(Pickup pickup)> ADD_BLIP_FOR_PICKUP(0xBE339365C863BD36);
lazy_func_t<BOOL(Blip blip)> IS_BLIP_ON_MINIMAP(0xE41CA53051197A27);
lazy_func_t<BOOL(Blip blip)> IS_MISSION_CREATOR_BLIP(0x26F49BF3381D933D);
lazy_func_t<BOOL()> IS_HUD_HIDDEN(0xA86478C6958735C5);
lazy_func_t<void(float p0)> RESPONDING_AS_TEMP(0xBD12C5EEE184C337);
lazy_func_t<void(BOOL toggle)> SET_GPS_FLASHES(0x320D0E0D936A0E9B);
lazy_func_t<Pickup()> _0xB2A592B04648A9CB(0xB2A592B04648A9CB);
lazy_func_t<Blip(float x, float y, float z)>
	ADD_BLIP_FOR_COORD(0x5A039BB0BCA604B6);
lazy_func_t<Any(Any p0)> _0xA13E93403F26C812(0xA13E93403F26C812);
lazy_func_t<void(BOOL p0)> _0x1185A8087587322C(0x1185A8087587322C);
lazy_func_t<void(int hudColorIndex, int *r, int *g, int *b, int *a)>
	GET_HUD_COLOUR(0x7C9C91AB74A0360F);
lazy_func_t<void()> SET_WAYPOINT_OFF(0xA7E4E2D361C2627F);
lazy_func_t<void(BOOL p0)> _0x62E849B7EB28E770(0x62E849B7EB28E770);
lazy_func_t<void()> CLEAR_REMINDER_MESSAGE(0xB57D8DD645CFA2CF);
lazy_func_t<void()> _0xCDCA26E80FAECB8F(0xCDCA26E80FAECB8F);
lazy_func_t<BOOL(int p0)> IS_STREAMING_ADDITIONAL_TEXT(0x8B6817B71B85EBF0);
lazy_func_t<void(BOOL p0, const char *name)>
	_SET_MISSION_NAME_2(0xE45087D85F468BC2);
lazy_func_t<void(Ped ped, int type)> _SET_AI_BLIP_TYPE(0xE52B8E7F85D39A08);
lazy_func_t<void(BOOL toggle)> _SET_DIRECTOR_MODE(0x808519373FD336A3);
lazy_func_t<void()> _0xA13C11E1B5C06BFC(0xA13C11E1B5C06BFC);
lazy_func_t<int(int type, int image, const char *text)>
	_DRAW_NOTIFICATION_WITH_ICON(0xD202B92CBF1D816F);
lazy_func_t<void(int zoomLevel)> SET_RADAR_ZOOM(0x096EF57A0C999BBA);
lazy_func_t<void(BOOL p0)> SET_TEXT_LEADING(0xA50ABC31E3CDFAFF);
lazy_func_t<Blip(float posX, float posY, float posZ, float radius)>
	ADD_BLIP_FOR_RADIUS(0x46818D79B1F7499A);
lazy_func_t<void(BOOL p0)> _0x3DDA37128DD1ACA8(0x3DDA37128DD1ACA8);
lazy_func_t<BOOL(int *p0, int *p1, int *p2)>
	_0xA238192F33110615(0xA238192F33110615);
lazy_func_t<void(Any *p0, Any *p1, Any *p2, Any *p3)>
	_0x317EBA71D7543F52(0x317EBA71D7543F52);
lazy_func_t<void(const char *text)>
	BEGIN_TEXT_COMMAND_DISPLAY_TEXT(0x25FBB336DF1804CB);
lazy_func_t<void(BOOL align)> SET_TEXT_CENTRE(0xC02F4DBFB51D988B);
lazy_func_t<void(Blip blip, BOOL toggle)> _SET_BLIP_FRIEND(0x23C3EB807312F01A);
lazy_func_t<void()> UNLOCK_MINIMAP_POSITION(0x3E93E06DB8EF1F30);
lazy_func_t<void(int headDisplayId, BOOL p1)>
	_SET_MP_GAMER_TAG_ICONS(0xA67F9C46D612B6F1);
lazy_func_t<BOOL(Any p0, float *p1)> _0x5FBD7095FE7AE57F(0x5FBD7095FE7AE57F);
lazy_func_t<void(const char *string)>
	_BEGIN_TEXT_COMMAND_BUSY_STRING(0xABA17D7CE615ADBF);
lazy_func_t<void(Blip blip, BOOL toggle)>
	SET_BLIP_SHOW_CONE(0x13127EC3665E8EE1);
lazy_func_t<Any()> _0x9135584D09A3437E(0x9135584D09A3437E);
lazy_func_t<BOOL()> IS_MESSAGE_BEING_DISPLAYED(0x7984C03AA5CC2F41);
lazy_func_t<void(int hudColorIndex, int hudColorIndex2)>
	_SET_HUD_COLOURS_SWITCH(0x1CCC708F0F850613);
lazy_func_t<BOOL(int gamerTagId)> IS_MP_GAMER_TAG_ACTIVE(0x4E929E7A5796FD26);
lazy_func_t<Any()> _0x1121BFA1A1A522A8(0x1121BFA1A1A522A8);
lazy_func_t<void()> _0xBA751764F0821256(0xBA751764F0821256);
lazy_func_t<void(const char *website)>
	ADD_TEXT_COMPONENT_SUBSTRING_WEBSITE(0x94CF4AC034C9C986);
lazy_func_t<void(BOOL toggle)> _SET_MINIMAP_REVEALED(0xF8DEE0A5600CBB93);
lazy_func_t<void(BOOL p0)> _0x04655F9D075D0AE5(0x04655F9D075D0AE5);
lazy_func_t<void(Blip blip, int displayId)>
	SET_BLIP_DISPLAY(0x9029B2F3DA924928);
lazy_func_t<BOOL(Hash hash)> IS_NAMED_RENDERTARGET_LINKED(0x113750538FA31298);
lazy_func_t<void()> _0x2708FC083123F9FF(0x2708FC083123F9FF);
lazy_func_t<BOOL()> _IS_TEXT_CHAT_ACTIVE(0xB118AF58B5F332A1);
lazy_func_t<int(BOOL blink, BOOL showInBrief)>
	_DRAW_NOTIFICATION(0x2ED7843F8F801023);
lazy_func_t<void(BOOL p0)> _0xB99C4E4D9499DF29(0xB99C4E4D9499DF29);
lazy_func_t<void()> _CENTER_PLAYER_ON_RADAR_THIS_FRAME(0x6D14BFDC33B34F55);
lazy_func_t<void(const char *GxtEntry)>
	BEGIN_TEXT_COMMAND_PRINT(0xB87A37EEB7FAA67D);
lazy_func_t<void(int value, BOOL commaSeparated)>
	ADD_TEXT_COMPONENT_FORMATTED_INTEGER(0x0E4C749FF9DE9CC4);
lazy_func_t<int(Blip blip)> GET_BLIP_INFO_ID_TYPE(0xBE9B0959FFD0779B);
lazy_func_t<void(int busySpinnerType)>
	_END_TEXT_COMMAND_BUSY_STRING(0xBD12F8228410D9B4);
lazy_func_t<BOOL(const char *p0, BOOL p1)>
	REGISTER_NAMED_RENDERTARGET(0x57D9C12635E25CE3);
lazy_func_t<void()> SET_RADAR_AS_EXTERIOR_THIS_FRAME(0xE81B7D2A3DAB2D81);
lazy_func_t<void(BOOL toggle)> DISPLAY_AREA_NAME(0x276B6CE369C33678);
lazy_func_t<void()> _0x14621BB1DF14E2B2(0x14621BB1DF14E2B2);
lazy_func_t<void()> _REMOVE_LOADING_PROMPT(0x10D373323E5B9C0D);
lazy_func_t<void()> _0xC2D15BEF167E27BC(0xC2D15BEF167E27BC);
lazy_func_t<void(Ped ped, int p1)> GIVE_PED_TO_PAUSE_MENU(0xAC0BFBDC3BE00E14);
lazy_func_t<void(int fontType)> SET_TEXT_FONT(0x66E0276CC5F6B9DA);
lazy_func_t<void(BOOL toggle)> SET_PAUSE_MENU_ACTIVE(0xDF47FC56C71569CF);
lazy_func_t<Hash()> _0xA48931185F0536FE(0xA48931185F0536FE);
lazy_func_t<void(int notificationId)> _REMOVE_NOTIFICATION(0xBE4390CB40B3E627);
lazy_func_t<BOOL()> _0x4A9923385BDB9DAD(0x4A9923385BDB9DAD);
lazy_func_t<void()> _0xEE4C0E6DBC6F2C6F(0xEE4C0E6DBC6F2C6F);
lazy_func_t<void(Hash menuHash, int p1)>
	RESTART_FRONTEND_MENU(0x10706DC6AD2D49C0);
lazy_func_t<void(int timestamp, int flags)>
	ADD_TEXT_COMPONENT_SUBSTRING_TIME(0x1115F16B8AB9E8BF);
lazy_func_t<void(int cash, int bank)>
	_SET_PLAYER_CASH_CHANGE(0x0772DF77852C2E30);
lazy_func_t<BOOL(Any p0, Any *p1, Any p2)>
	_0xCA6B2F7CE32AB653(0xCA6B2F7CE32AB653);
lazy_func_t<void(const char *p0, int p1)>
	_ADD_TEXT_COMPONENT_APP_TITLE(0x761B77454205A61D);
lazy_func_t<void(BOOL p0, Any p1)> KEY_HUD_COLOUR(0x1A5CD7752DD28CD3);
lazy_func_t<void()> REMOVE_MULTIPLAYER_BANK_CASH(0xC7C6789AA1CFEDD0);
lazy_func_t<Vector3(Blip blip)> GET_BLIP_COORDS(0x586AFE3FF72D996E);
lazy_func_t<void(Any p0, BOOL p1)> CLEAR_FLOATING_HELP(0x50085246ABD3FEFA);
lazy_func_t<void()> _0xBF4F34A85CA2970C(0xBF4F34A85CA2970C);
lazy_func_t<Any()> _0x3BAB9A4E4F2FF5C7(0x3BAB9A4E4F2FF5C7);
lazy_func_t<void()> _0xD2049635DEB9C375(0xD2049635DEB9C375);
lazy_func_t<void(int id, float x, float y)>
	SET_HUD_COMPONENT_POSITION(0xAABB1F56E2A17CED);
lazy_func_t<BOOL()> IS_PAUSE_MENU_ACTIVE(0xB0034A223497FFCB);
lazy_func_t<void()> HIDE_HUD_AND_RADAR_THIS_FRAME(0x719FF505F097FD20);
lazy_func_t<void(const char *entry)>
	_BEGIN_TEXT_COMMAND_LINE_COUNT(0x521FB041D93DD0E4);
lazy_func_t<const char *(const char *labelName)>
	_GET_LABEL_TEXT(0x7B5280EBA9840C72);
lazy_func_t<float(float size, int font)>
	_GET_TEXT_SCALE_HEIGHT(0xDB88A37483346780);
lazy_func_t<void(Blip blip, BOOL toggle)>
	SHOW_HEADING_INDICATOR_ON_BLIP(0x5FBCA48327B914DF);
lazy_func_t<void()> REFRESH_WAYPOINT(0x81FA173F170560D1);
lazy_func_t<Any()> _0x2E22FEFA0100275E(0x2E22FEFA0100275E);
lazy_func_t<void(BOOL p0)> _0x9245E81072704B8A(0x9245E81072704B8A);
lazy_func_t<void(int gamerTagId, const char *string)>
	SET_MP_GAMER_TAG_NAME(0xDEA2B8283BAA3944);
lazy_func_t<void(BOOL p0)> _0x4A0C7C9BB10ABB36(0x4A0C7C9BB10ABB36);
lazy_func_t<void(Blip blip, BOOL toggle)>
	SET_BLIP_AS_MISSION_CREATOR_BLIP(0x24AC0137444F9FD5);
lazy_func_t<BOOL(Blip blip)> DOES_BLIP_EXIST(0xA6DB27D19ECBB7DA);
lazy_func_t<void()> _0xB695E2CD0A2DA9EE(0xB695E2CD0A2DA9EE);
lazy_func_t<Any()> _0xA277800A9EAE340E(0xA277800A9EAE340E);
lazy_func_t<void(Blip blip, int rotation)>
	SET_BLIP_ROTATION(0xF87683CDF73C3F6E);
lazy_func_t<int(Blip blip)> GET_BLIP_SPRITE(0x1FC877464A04FC4F);
lazy_func_t<Blip()> GET_MAIN_PLAYER_BLIP_ID(0xDCD4EC3F419D02FA);
lazy_func_t<int(float x, float y)>
	_GET_TEXT_SCREEN_LINE_COUNT(0x9040DFB09BE75706);
lazy_func_t<void(float start, float end)> SET_TEXT_WRAP(0x63145D9C883A1A70);
lazy_func_t<void()> _0x20FE7FDFEEAD38C0(0x20FE7FDFEEAD38C0);
lazy_func_t<void()> _0x7669F9E39DC17063(0x7669F9E39DC17063);
lazy_func_t<Any(Any p0)> _0xE3B05614DCE1D014(0xE3B05614DCE1D014);
lazy_func_t<void(float value, int decimalPlaces)>
	ADD_TEXT_COMPONENT_FLOAT(0xE7DCB5B874BCD96E);
lazy_func_t<void(const char *labelName)>
	ADD_TEXT_COMPONENT_SUBSTRING_TEXT_LABEL(0xC63CD5D2920ACBE7);
lazy_func_t<const char *(Hash hash)>
	GET_STREET_NAME_FROM_HASH_KEY(0xD0EF8A959B8A4CB9);
lazy_func_t<void(BOOL p0)>
	ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(0x60296AF4BA14ABC5);
lazy_func_t<void(Blip blip, const char *gxtEntry)>
	SET_BLIP_NAME_FROM_TEXT_FILE(0xEAA0FFE120D92784);
lazy_func_t<void(Blip blip, int priority)>
	SET_BLIP_PRIORITY(0xAE9FC9EF6A9FAC79);
lazy_func_t<void(float pos)> _CLEAR_NOTIFICATIONS_POS(0x55598D21339CB998);
lazy_func_t<BOOL(Blip blip)> IS_BLIP_FLASHING(0xA5E41FD83AD6CEF0);
lazy_func_t<void()> _0xE6DE0561D9232A64(0xE6DE0561D9232A64);
lazy_func_t<void()> _0xEC9264727EEC0F28(0xEC9264727EEC0F28);
lazy_func_t<void(const char *gxt, int slot)>
	REQUEST_ADDITIONAL_TEXT(0x71A78003C8E71424);
}} // namespace UI::
}} // namespace nob::ntv
