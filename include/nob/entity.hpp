#pragma once

#include "arm.hpp"
#include "gc.hpp"
#include "hash.hpp"
#include "i18n.hpp"
#include "log.hpp"
#include "model.hpp"
#include "ntv.hpp"
#include "script.hpp"
#include "vector.hpp"

#include <string>
#include <unordered_map>

namespace nob {

class entity {
public:
	entity(int native_handle = 0) : _h(native_handle) {}

	entity(model m, const vector3 &coords, bool dynamic = true) :
		entity(ntv::OBJECT::CREATE_OBJECT_NO_OFFSET(
			m.load(), coords.x, coords.y, coords.z, false, false, dynamic)) {
		if (!_h) {
			return;
		}

		auto h = _h;
		gc::delegate(*this, [h]() mutable {
			if (ntv::ENTITY::DOES_ENTITY_EXIST(h)) {
				ntv::ENTITY::DELETE_ENTITY(&h);
			}
		});
	}

	int native_handle() const {
		return _h;
	}

	operator int() const {
		return native_handle();
	}

	void del() {
		gc::undelegate(*this);

		ntv::ENTITY::DELETE_ENTITY(&_h);
	}

	void free() {
		gc::undelegate(*this);

		ntv::ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&_h);
	}

	bool is_dead() const {
		return ntv::ENTITY::IS_ENTITY_DEAD(_h);
	}

	bool is_exist() const {
		return ntv::ENTITY::DOES_ENTITY_EXIST(_h);
	}

	operator bool() const {
		return _h && is_exist();
	}

	vector3 pos() const {
		return ntv::ENTITY::GET_ENTITY_COORDS(_h, true);
	}

	vector3 pos(const vector3 &relative_pos) const {
		return ntv::ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(
			_h, relative_pos.x, relative_pos.y, relative_pos.z);
	}

	vector3 relative_pos(const vector3 &pos) const {
		return ntv::ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(
			_h, pos.x, pos.y, pos.z);
	}

	void move(const vector3 &coords, bool auto_refresh_display = true) {
		auto obj = (**nob::ntv::entity_obj_map)[_h];
		if (!obj) {
			return;
		}

		obj->move(coords);

		if (auto_refresh_display) {
			rot(rot());
		}

		nob::ntv::ROPE::ACTIVATE_PHYSICS(_h);

		// nob::ntv::ENTITY::SET_ENTITY_COORDS_NO_OFFSET(_h, coords.x, coords.y,
		// coords.z, false, false, false);
	}

	vector3 rot() const {
		return ntv::ENTITY::GET_ENTITY_ROTATION(_h, 2);
	}

	void rot(const vector3 &val) {
		ntv::ENTITY::SET_ENTITY_ROTATION(_h, val.x, val.y, val.z, 2, true);
	}

	vector4 quat() const {
		vector4 val;
		ntv::ENTITY::GET_ENTITY_QUATERNION(_h, &val.x, &val.y, &val.z, &val.w);
		return val;
	}

	void quat(const vector4 &val) {
		ntv::ENTITY::SET_ENTITY_QUATERNION(_h, val.x, val.y, val.z, val.w);
	}

	vector3 vel() const {
		return ntv::ENTITY::GET_ENTITY_VELOCITY(_h);
	}

	void vel(const vector3 &val) {
		ntv::ENTITY::SET_ENTITY_VELOCITY(_h, val.x, val.y, val.z);
	}

	struct movement_t {
		vector3 pos, rot, vel;
	};

	movement_t movement() const {
		return {pos(), rot(), vel()};
	}

	void movement(
		const movement_t &mmt,
		float speed = -1.f,
		std::function<void()> callback = nullptr) {
		if (speed <= 0.f) {
			move(mmt.pos, false);
			rot(mmt.rot);
			vel(mmt.vel);
			if (callback) {
				callback();
			}
			return;
		}
		auto &mover = _mmt_smooth_mover();
		mover.map[_h] = {mmt,
						 speed,
						 speed * (mmt.pos - pos()),
						 speed * (mmt.rot - rot()),
						 0.f,
						 std::move(callback)};
		mover.run();
	}

	bool visible() const {
		return ntv::ENTITY::IS_ENTITY_VISIBLE(_h);
	}

	void visible(bool toggle = true) {
		ntv::ENTITY::SET_ENTITY_VISIBLE(_h, toggle, false);
	}

	int alpha() const {
		return ntv::ENTITY::GET_ENTITY_ALPHA(_h);
	}

	void alpha(int alpha) {
		ntv::ENTITY::SET_ENTITY_ALPHA(_h, alpha, true);
	}

	void reset_alpha() {
		ntv::ENTITY::RESET_ENTITY_ALPHA(_h);
	}

	void collidable(bool toggle = true) {
		ntv::ENTITY::SET_ENTITY_COLLISION(_h, toggle, true);
	}

	void physics_collidable(bool toggle = true) {
		ntv::ENTITY::SET_ENTITY_COLLISION(_h, toggle, toggle);
	}

	void freeze_pos(bool toggle = true) {
		ntv::ENTITY::FREEZE_ENTITY_POSITION(_h, toggle);
	}

	void invincible(bool toggle = true) {
		ntv::ENTITY::SET_ENTITY_INVINCIBLE(_h, toggle);
	}

	model get_model() const {
		return static_cast<hash_t>(ntv::ENTITY::GET_ENTITY_MODEL(_h));
	}

	bool is_character() const {
		return ntv::ENTITY::IS_ENTITY_A_PED(_h);
	}

	bool is_vehicle() const {
		return ntv::ENTITY::IS_ENTITY_A_VEHICLE(_h);
	}

	bool is_trivial() const {
		return ntv::ENTITY::IS_ENTITY_AN_OBJECT(_h);
	}

	bool is_on_screen() const {
		return ntv::ENTITY::IS_ENTITY_ON_SCREEN(_h);
	}

	int health() {
		return ntv::ENTITY::GET_ENTITY_HEALTH(_h);
	}

	int health_max() {
		return ntv::ENTITY::GET_ENTITY_MAX_HEALTH(_h);
	}

	void health(int v) const {
		ntv::ENTITY::SET_ENTITY_HEALTH(_h, v);
	}

	bool is_touching(entity target) const {
		return ntv::ENTITY::IS_ENTITY_TOUCHING_ENTITY(_h, target);
	}

protected:
	int _h;

private:
	struct _mmt_smooth_mover_t {
		struct info_t {
			movement_t dest;
			float speed;
			vector3 speed_pos, speed_rot;
			float prgs;
			std::function<void()> callback;
		};
		std::unordered_map<int, info_t> map;
		task tsk;
		size_t last_ts = 0;

		void run() {
			if (!tsk) {
				tsk = task([this]() mutable {
					size_t ts = GetTickCount();
					if (last_ts) {
						for (auto it = map.begin(); it != map.end();) {
							entity ety(it->first);
							if (!ety) {
								it = map.erase(it);
								if (map.empty()) {
									tsk.del();
									return;
								}
								continue;
							}

							auto &dest = it->second.dest;
							auto now_pos = ety.pos();
							auto dur =
								static_cast<float>(ts - last_ts) / 1000.f;
							it->second.prgs += dur * it->second.speed;

							if (it->second.prgs >= 1.f) {
								ety.move(dest.pos, false);
								ety.rot(dest.rot);
								ety.vel(dest.vel);

								if (it->second.callback) {
									it->second.callback();
								}

								it = map.erase(it);
								if (map.empty()) {
									tsk.del();
									return;
								}
								continue;
							}

							ety.move(now_pos + dur * it->second.speed_pos);
							++it;
						}
					}
					last_ts = ts;
					// yield();
				});
			}
		}
	};

	static _mmt_smooth_mover_t &_mmt_smooth_mover() {
		static _mmt_smooth_mover_t md;
		return md;
	}

	////////////////////////////////////////////////////////////////////

public:
	class anim_dict {
	public:
		anim_dict() : _name(""), _tslc(0) {}

		anim_dict(std::nullptr_t) : anim_dict() {}

		anim_dict(const char *name) : _name(name), _tslc(0) {}

		anim_dict(std::string name) : _name(std::move(name)), _tslc(0) {}

		anim_dict(const anim_dict &src) : _name(src._name), _tslc(0) {}

		~anim_dict() {
			free();
		}

		anim_dict &operator=(const anim_dict &src) {
			free();
			_name = src._name;
			return *this;
		}

		anim_dict(anim_dict &&src) :
			_name(std::move(src._name)), _tslc(src._tslc) {
			if (src._tslc == this_script::load_count) {
				src._tslc = 0;
			}
		}

		anim_dict &operator=(anim_dict &&src) {
			free();
			_name = std::move(src._name);
			if (src._tslc == this_script::load_count) {
				_tslc = src._tslc;
				src._tslc = 0;
			}
			return *this;
		}

		const std::string &name() const {
			return _name;
		}

		using native_handle_t = const char *;

		native_handle_t native_handle() const {
			return _name.c_str();
		}

		operator bool() const {
			return _name.length();
		}

		bool is_loaded() const {
			assert(*this);

			return ntv::STREAMING::HAS_ANIM_DICT_LOADED(_name.c_str());
		}

		const anim_dict &load() {
			assert(*this);

			if (_tslc == this_script::load_count) {
				return *this;
			}

		start:

			if (gc::try_ref(*this)) {
				assert(is_loaded());

				_tslc = this_script::load_count;
				return *this;
			}

			ntv::STREAMING::REQUEST_ANIM_DICT(_name.c_str());

			auto cur_lc = this_script::load_count;

			while (!is_loaded()) {
				yield();
				if (cur_lc != this_script::load_count) {
					goto start;
				}
			}

			_tslc = cur_lc;

			auto n = _name;
			gc::delegate(*this, [n]() {
				if (ntv::STREAMING::HAS_ANIM_DICT_LOADED(n.c_str())) {
					ntv::STREAMING::REMOVE_ANIM_DICT(n.c_str());
				}
			});

			return *this;
		}

		void free() {
			if (_tslc && _tslc == this_script::load_count) {
				gc::free(*this);
				_tslc = 0;
			}
		}

	private:
		std::string _name;
		size_t _tslc;
	};
};

class vehicle;

class character : public entity {
public:
	character(int native_handle = 0) : entity(native_handle) {}

	character(model m, const vector3 &coords, bool player_body = false) :
		entity(ntv::PED::CREATE_PED(
			4, m.load(), coords.x, coords.y, coords.z, 0.0f, false, false)) {
		if (!_h) {
			return;
		}

		auto h = _h;
		gc::delegate(*this, [h]() mutable {
			if (h == ntv::PLAYER::PLAYER_PED_ID()) {
				return;
			}
			if (!ntv::ENTITY::DOES_ENTITY_EXIST(h)) {
				return;
			}
			ntv::PED::DELETE_PED(&h);
		});

		if (player_body) {
			ntv::PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(_h, true);
			ntv::PED::SET_PED_FLEE_ATTRIBUTES(_h, 0, 0);
			ntv::PED::SET_PED_COMBAT_ATTRIBUTES(_h, 292, true);
			ntv::PED::SET_PED_DIES_INSTANTLY_IN_WATER(_h, false);
			ntv::PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(
				_h, 1); // Blocks ragdolling when shot.
			ntv::WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(_h, false);
			ntv::PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(_h, false);
			ntv::AI::SET_PED_PATH_AVOID_FIRE(_h, false);
		}
		ntv::PED::SET_PED_CONFIG_FLAG(_h, 281, true); // PED_FLAG_NO_WRITHE
	}

	void del();

	void free();

	void resurrect() {
		ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(_h);
		ntv::ENTITY::SET_ENTITY_COLLISION(_h, true, true);
		if (_h == ntv::PLAYER::PLAYER_PED_ID()) {
			ntv::GAMEPLAY::_RESET_LOCALPLAYER_STATE();
		}
	}

	void set_random_outfit() {
		ntv::PED::SET_PED_RANDOM_COMPONENT_VARIATION(_h, false);
	}

	void set_default_outfit() {
		ntv::PED::SET_PED_DEFAULT_COMPONENT_VARIATION(_h);
	}

	void set_last_outfit() {
		for (int i = 0; i < 12; i++) {
			for (int d =
					 ntv::PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(_h, i) - 1;
				 d >= 0;
				 d--) {
				for (int t = ntv::PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(
								 _h, i, d) -
							 1;
					 t >= 0;
					 t--) {
					if (ntv::PED::IS_PED_COMPONENT_VARIATION_VALID(
							_h, i, d, t)) {
						ntv::PED::SET_PED_COMPONENT_VARIATION(_h, i, d, t, 0);
						break;
					}
				}
			}
		}
	}

	void still();

	void jump();

	void climb();

	void climb_ladder();

	static constexpr float speed_walk = 1.0f;
	static constexpr float speed_run = 1.2f;
	static constexpr float speed_sprint = 3.0f;

	void go_to(const vector3 &target, float speed = speed_sprint);

	void go(float speed = speed_sprint) {
		go_to(pos({0, 10, 0}), speed);
	}

	void skydive();

	void add_parachute_pack() {
		if (!has_weapon_in_pack(nob::hash("GADGET_PARACHUTE"))) {
			add_weapon(nob::hash("GADGET_PARACHUTE"));
		}
	}

	void open_parachute();

	void open_fake_parachute();

	void stop_motion_command();

	inline void get_in_vehicle(vehicle veh, int seat = -1, bool run_to = true);

	inline void into_vehicle(vehicle veh, int seat = -1);

	void leave_vehicle(bool can_jump = true) {
		auto veh = ntv::PED::GET_VEHICLE_PED_IS_IN(_h, false);
		if (veh) {
			ntv::AI::TASK_LEAVE_VEHICLE(_h, veh, can_jump ? 4160 : 0);
		}
	}

	bool is_in_vehicle(bool include_door_interactives = false) const {
		return ntv::PED::IS_PED_IN_ANY_VEHICLE(_h, include_door_interactives);
	}

	bool is_on_vehicle() const {
		return ntv::PED::IS_PED_ON_VEHICLE(_h);
	}

	inline bool is_on_vehicle(vehicle veh) const;

	inline vehicle current_vehicle() const;

	inline vehicle last_vehicle() const;

	inline vehicle trying_to_enter_vehicle() const;

	inline int trying_to_enter_vehicle_seat() const;

	inline void
	drive_to(const nob::vector3 &coords, float speed, bool along_paths = true);

	enum class motion_state_t : uint8_t {
		null = 0,
		still,
		walking,
		runing,
		sprinting,
		jumping,
		falling,
		skydiving,
		parachuting,
		climbing,
		climbing_ladder,
		covering,
		paralysing
	};

	motion_state_t motion_state() const;

	struct movement_t : public entity::movement_t {
		motion_state_t motion_state;
	};

	movement_t movement() const {
		movement_t mmt;
		static_cast<entity::movement_t &>(mmt) = entity::movement();
		mmt.motion_state = motion_state();
		return mmt;
	}

	void movement(
		const movement_t &,
		float speed = -1.f,
		bool delayed_action = true,
		const std::function<void()> &callback = nullptr);

	void add_weapon(const hasher &wpn) {
		ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, wpn.hash(), 0, false, false);
	}

	void rm_weapon(const hasher &wpn) {
		ntv::WEAPON::REMOVE_WEAPON_FROM_PED(_h, wpn.hash());
	}

	void add_all_weapons() {
		for (auto &wpn : arm::weapons) {
			if (wpn == "WEAPON_UNARMED") {
				continue;
			}

			auto wpn_grp = arm::weapon_group(wpn);

			if (wpn_grp != "GROUP_THROWN") {
				add_weapon(wpn);
			}

			if (wpn_grp == "GROUP_MELEE") {
				continue;
			}

			weapon_ammo(wpn, weapon_ammo_max(wpn));
		}
	}

	void clear_armed() {
		ntv::WEAPON::REMOVE_ALL_PED_WEAPONS(_h, true);
	}

	void switch_weapon(const hasher &wpn) {
		if (is_current_weapon(wpn)) {
			return;
		}
		if (is_in_vehicle()) {
			ntv::WEAPON::SET_CURRENT_PED_VEHICLE_WEAPON(_h, wpn.hash());
			if (!is_current_weapon(wpn) && arm::weapon_group(wpn).hash() != 0) {
				ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, wpn.hash(), 0, false, true);
			}
			return;
		}
		if (!has_weapon_in_pack(wpn)) {
			ntv::WEAPON::GIVE_WEAPON_TO_PED(_h, wpn.hash(), 0, false, true);
			return;
		}
		ntv::WEAPON::SET_CURRENT_PED_WEAPON(_h, wpn.hash(), true);
	}

	hasher current_weapon() const {
		hash_t h;
		if (is_in_vehicle()) {
			ntv::WEAPON::GET_CURRENT_PED_VEHICLE_WEAPON(_h, &h);
		} else {
			ntv::WEAPON::GET_CURRENT_PED_WEAPON(_h, &h, true);
		}
		return h;
	}

	bool is_current_weapon(const hasher &wpn) const {
		return current_weapon() == wpn;
	}

	void unarmed() {
		switch_weapon("WEAPON_UNARMED");
	}

	bool is_unarmed() const {
		return is_current_weapon("WEAPON_UNARMED");
	}

	bool has_weapon_in_pack(const hasher &wpn) const {
		return ntv::WEAPON::HAS_PED_GOT_WEAPON(_h, wpn.hash(), false);
	}

	bool has_weapon(const hasher &wpn) const {
		return is_current_weapon(wpn.hash()) ? true : has_weapon_in_pack(wpn);
	}

	int weapon_clip_ammo_max(const hasher &wpn) const {
		return ntv::WEAPON::GET_MAX_AMMO_IN_CLIP(_h, wpn.hash(), true);
	}

	void weapon_clip_ammo(const hasher &wpn, int total) {
		ntv::WEAPON::SET_AMMO_IN_CLIP(_h, wpn.hash(), total);
	}

	int weapon_clip_ammo(const hasher &wpn) const {
		int total;
		ntv::WEAPON::GET_AMMO_IN_CLIP(_h, wpn.hash(), &total);
		return total;
	}

	int weapon_ammo_max(const hasher &wpn) const {
		int total;
		ntv::WEAPON::GET_MAX_AMMO(_h, wpn.hash(), &total);
		return total;
	}

	void weapon_ammo(const hasher &wpn, int total) {
		if (!weapon_ammo(wpn)) {
			add_weapon_ammo(wpn, total);
			return;
		}
		ntv::WEAPON::SET_PED_AMMO(_h, wpn.hash(), total);
	}

	int weapon_ammo(const hasher &wpn) const {
		return ntv::WEAPON::GET_AMMO_IN_PED_WEAPON(_h, wpn.hash());
	}

	void add_weapon_ammo(const hasher &wpn, int count) {
		if (arm::weapon_group(wpn) == "GROUP_THROWN") {
			ntv::WEAPON::GIVE_WEAPON_TO_PED(
				_h, wpn.hash(), count, false, false);
		}
		ntv::WEAPON::ADD_AMMO_TO_PED(_h, wpn.hash(), count);
	}

	hasher weapon_ammo_type(const hasher &wpn) const {
		return ntv::WEAPON::GET_PED_AMMO_TYPE_FROM_WEAPON(_h, wpn.hash());
	}

	int ammo_max(const hasher &type) const {
		return weapon_ammo_max(arm::weapon_from_ammo_type(type));
	}

	void ammo(const hasher &type, int total) {
		weapon_ammo(arm::weapon_from_ammo_type(type), total);
	}

	int ammo(const hasher &type) const {
		return ntv::WEAPON::GET_PED_AMMO_BY_TYPE(_h, type.hash());
	}

	void add_ammo(const hasher &type, int count) {
		auto wpn = arm::weapon_from_ammo_type(type);
		if (arm::weapon_group(wpn) == "GROUP_THROWN") {
			ntv::WEAPON::GIVE_WEAPON_TO_PED(
				_h, wpn.hash(), count, false, false);
		}
		ntv::WEAPON::SET_PED_AMMO_BY_TYPE(_h, type.hash(), count);
	}

	void ammo_no_consumption(bool toggle = true) {
		for (auto type : arm::ammo_types) {
			ntv::WEAPON::SET_PED_INFINITE_AMMO(
				_h, toggle, arm::weapon_from_ammo_type(type));
		}
		ntv::WEAPON::SET_PED_INFINITE_AMMO_CLIP(_h, toggle);
	}

	void print_weapon_info() const {
#ifndef NDEBUG
		auto cur_wpn = current_weapon();
		if (cur_wpn == "WEAPON_UNARMED") {
			log("unarmed!");
			return;
		}

		std::stringstream ss;

		ss << "weapon ";
		for (auto &hr : arm::weapons) {
			if (hr == cur_wpn) {
				ss << hr.src_str() << " ";
				break;
			}
		}
		if (is_in_vehicle()) {
			for (auto &hr : arm::vehicle_weapons) {
				if (hr == cur_wpn) {
					ss << hr.src_str() << " ";
					break;
				}
			}
		}
		ss << std::hex << cur_wpn.hash() << std::endl;

		auto grp = arm::weapon_group(cur_wpn);
		ss << "  group: ";
		for (auto &hr : arm::weapon_groups) {
			if (hr == grp) {
				ss << hr.src_str() << " ";
				break;
			}
		}
		ss << grp.hash() << std::endl;

		auto amm_ty = weapon_ammo_type(cur_wpn);
		ss << "  ammo type: ";
		for (auto &hr : arm::ammo_types) {
			if (hr == amm_ty) {
				ss << hr.src_str() << " ";
				break;
			}
		}
		ss << amm_ty.hash();

		auto info = arm::weapon_info(cur_wpn);
		if (info.valid) {
			ss << std::endl
			   << "  damage: " << info.damage / 255.0f << std::endl
			   << "  speed: " << info.speed / 255.0f << std::endl
			   << "  capacity: " << info.capacity / 255.0f << std::endl
			   << "  accuracy: " << info.accuracy / 255.0f << std::endl
			   << "  range: " << info.range / 255.0f;
		}

		log(ss.str());
#endif
	}

	void disable_melee(bool toggle = true) {
		ntv::PED::SET_PED_CONFIG_FLAG(
			_h, 122, toggle); // PED_FLAG_NO_PLAYER_MELEE
		ntv::PED::SET_PED_CONFIG_FLAG(_h, 314, toggle); // PED_FLAG_NO_PED_MELEE
	}

	void disable_attack(bool toggle = true) {
		ntv::PED::SET_ENABLE_HANDCUFFS(_h, !toggle);
	}

	void look();

	void stop_look() {
		ntv::AI::TASK_CLEAR_LOOK_AT(_h);
	}

	void focus(const vector3 &coords);

	void aim(bool toggle = true);

	void shoot(bool toggle = true);

	void shoot_once();

	void cover();

	void paralysis();

	void cant_be_explode_head(bool toggle = true) {
		ntv::PED::SET_PED_SUFFERS_CRITICAL_HITS(_h, !toggle);
	}

	bool is_in_melee_combat() const {
		return ntv::PED::IS_PED_IN_MELEE_COMBAT(_h);
	}

	entity melee_target() const {
		return ntv::PED::GET_MELEE_TARGET_FOR_PED(_h);
	}

	void melee(entity e) {
		return ntv::AI::TASK_PUT_PED_DIRECTLY_INTO_MELEE(
			_h, e, 0.0, 0.0, 0.0, 0);
	}

	void accuracy(int val) {
		ntv::PED::SET_PED_ACCURACY(_h, val);
	}

	int accuracy() const {
		return ntv::PED::GET_PED_ACCURACY(_h);
	}

	static void commad_damage_modifier(float val) {
		ntv::PED::SET_AI_WEAPON_DAMAGE_MODIFIER(val);
		ntv::PED::SET_AI_MELEE_WEAPON_DAMAGE_MODIFIER(val);
	}

	static void reset_commad_damage_modifier() {
		ntv::PED::RESET_AI_WEAPON_DAMAGE_MODIFIER();
		ntv::PED::RESET_AI_MELEE_WEAPON_DAMAGE_MODIFIER();
	}

	enum class ntv_task_t : unsigned int {
		TASK_ACHIEVE_HEADING = 0x7276d3df,
		TASK_AIM_GUN_AT_COORD = 0x49bef36e,
		TASK_AIM_GUN_AT_ENTITY = 0x6134071b,
		TASK_AIM_GUN_SCRIPTED = 0x0c69931f,
		TASK_AIM_GUN_SCRIPTED_WITH_TARGET = 0x0c69931f,
		TASK_ARREST_PED = 0x52ff82c0,
		TASK_BOAT_MISSION = 0xb41f1a34,
		TASK_CHAT_TO_PED = 0x0fc239cd,
		TASK_CLEAR_DEFENSIVE_AREA = 0x00a101c8,
		TASK_CLIMB = 0xb802fdca,
		TASK_CLIMB_LADDER = 0x66403353,
		TASK_COMBAT_PED = 0x2e85a751,
		TASK_COMBAT_HATED_TARGETS_AROUND_PED = 0xaa05b492,
		TASK_COMBAT_HATED_TARGETS_AROUND_PED_TIMED = 0x2719c0d1,
		TASK_COMBAT_HATED_PED_IN_AREA = 0x42cc4f21,
		TASK_COMBAT_TIMED = 0xf2e41a8a,
		TASK_COWER = 0x1c43f4cf,
		TASK_DRIVE_BY = 0x7d711e7d,
		TASK_EVERYONE_LEAVE_VEHICLE = 0xa569f146,
		TASK_EXIT_COVER = 0x4e961d82,
		TASK_FOLLOW_NAV_MESH_TO_COORD = 0x2a89b8a7,
		TASK_FOLLOW_NAV_MESH_TO_COORD_ADVANCED = 0x9c4fbcac,
		TASK_FOLLOW_POINT_ROUTE = 0xb232526f,
		TASK_FOLLOW_TO_OFFSET_OF_ENTITY = 0x3ef867f4,
		TASK_FOLLOW_WAYPOINT_RECORDING = 0x9b4fc7d8,
		TASK_FORCE_MOTION_STATE = 0x9e78ac1f,
		TASK_GET_OFF_BOAT = 0x9a27a999,
		TASK_GO_STRAIGHT_TO_COORD = 0x7d8f4411,
		TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_ENTITY = 0x78ec0ff6,
		TASK_GO_TO_COORD_AND_AIM_AT_HATED_ENTITIES_NEAR_COORD = 0x290a02bc,
		TASK_GO_TO_COORD_ANY_MEANS = 0x93399e79,
		TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS = 0x45b5a146,
		TASK_GO_TO_COORD_ANY_MEANS_EXTRA_PARAMS_WITH_CRUISE_SPEED = 0x4de5c290,
		TASK_GOTO_ENTITY = 0x4924437d,
		TASK_GOTO_ENTITY_AIMING = 0x967ea21c,
		TASK_GOTO_ENTITY_OFFSET = 0x87e3e0a8,
		TASK_GOTO_ENTITY_OFFSET_XY = 0x87e3e0a8,
		TASK_GUARD_ASSIGNED_DEFENSIVE_AREA = 0xdf5f4ba7,
		TASK_GUARD_CURRENT_POS = 0x8ce49d34,
		TASK_GUARD_SPHERE_DEFENSIVE_AREA = 0x21e8d4e4,
		TASK_HANDS_UP = 0xa573b67c,
		TASK_HELI_CHASE = 0x27369192,
		TASK_HELI_MISSION = 0xb41f1a34,
		TASK_VEHICLE_HELI_PROTECT = 0xb41f1a34,
		TASK_JUMP = 0x24415046,
		TASK_LEAVE_ANY_VEHICLE = 0xce98fbb3,
		TASK_LEAVE_VEHICLE = 0x1ae73569,
		TASK_MOVE_NETWORK_ADVANCED = 0x0494661c,
		TASK_MOVE_NETWORK = 0x0494661c,
		TASK_PARACHUTE = 0x76ca4a8e,
		TASK_PARACHUTE_TO_TARGET = 0x4921b47a,
		TASK_PATROL = 0xb550726c,
		TASK_PAUSE = 0x03c990ec,
		TASK_PED_SLIDE_TO_COORD_HDG_RATE = 0x3e5094a7,
		TASK_PERFORM_SEQUENCE = 0x0e763797,
		TASK_PERFORM_SEQUENCE_FROM_PROGRESS = 0x5485fd94,
		TASK_PLANE_CHASE = 0x02dba9bf,
		TASK_PLANE_CHASE_2 = 0x043e4a56,
		TASK_PLANE_MISSION = 0xb41f1a34,
		TASK_PLANT_BOMB = 0x8127fd1a,
		TASK_PUT_PED_DIRECTLY_INTO_COVER = 0x8b2f140e,
		TASK_PUT_PED_DIRECTLY_INTO_MELEE = 0xfbbf6f4d,
		TASK_RAPPEL_FROM_HELI = 0xef8d6b40,
		TASK_REACT_AND_FLEE_PED = 0x7dedf098,
		TASK_RELOAD_WEAPON = 0xc322ed6f,
		TASK_SCRIPTED_ANIMATION = 0x87b9a382,
		TASK_SEEK_COVER_FROM_PED = 0x71e30bdc,
		TASK_SEEK_COVER_FROM_POS = 0xa77a06c5,
		TASK_SEEK_COVER_TO_COVER_COORD = 0x6c01775c,
		TASK_SEEK_COVER_TO_COVER_POINT = 0x99afa8a3,
		TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS = 0x6f9c865c,
		TASK_SET_DECISION_MAKER = 0x4e5b453c,
		TASK_SET_PED_SPHERE_DEFENSIVE_AREA = 0x00a101c8,
		TASK_SHOCKING_EVENT_REACT = 0x498babe3,
		TASK_SHOOT_GUN_AT_COORD = 0xd90ef188,
		TASK_SHOOT_AT_ENTITY = 0x0a01f8b8,
		TASK_SHUFFLE_TO_NEXT_VEHICLE_SEAT = 0x153011fc,
		TASK_SKY_DIVE = 0x4b65f15c,
		TASK_SMART_FLEE_POINT = 0xf10822aa,
		TASK_SMART_FLEE_PED = 0x6ba30179,
		TASK_STAND_GUARD = 0xd88f2cde,
		TASK_STAND_STILL = 0xc572e06a,
		TASK_START_SCENARIO_AT_POSITION = 0xbe86c566,
		TASK_START_SCENARIO_IN_PLACE = 0x3b3a458f,
		TASK_STAY_IN_COVER = 0xe1c16e99,
		TASK_STEALTH_KILL = 0x5014cc1a,
		TASK_SWAP_WEAPON = 0x2ab81462,
		TASK_GENERAL_SWEEP = 0x491a782d,
		TASK_GENERAL_SWEEP_2 = 0x491a782d,
		TASK_SYNCHRONIZED_SCENE = 0x6a67a5cc,
		TASK_THROW_PROJECTILE = 0xad37bf03,
		TASK_TOGGLE_DUCK = 0x0f3b8554,
		TASK_TURN_PED_TO_FACE_COORD = 0x574bb8f5,
		TASK_TURN_PED_TO_FACE_ENTITY = 0xcbce4595,
		TASK_USE_MOBILE_PHONE = 0x37d339a1,
		TASK_USE_MOBILE_PHONE_TIMED = 0x37d339a1,
		TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD = 0x9bd19ae7,
		TASK_USE_NEAREST_SCENARIO_CHAIN_TO_COORD_WARP = 0x9bd19ae7,
		TASK_USE_NEAREST_SCENARIO_TO_COORD = 0x623a5efe,
		TASK_USE_NEAREST_SCENARIO_TO_COORD_WARP = 0x623a5efe,
		TASK_VEHICLE_CHASE = 0x2288a57c,
		TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE = 0x21d33957,
		TASK_VEHICLE_DRIVE_TO_COORD = 0x93a5526e,
		TASK_VEHICLE_DRIVE_WANDER = 0xf09b15b3,
		TASK_VEHICLE_ESCORT = 0xb41f1a34,
		TASK_VEHICLE_FOLLOW = 0xb41f1a34,
		TASK_VEHICLE_FOLLOW_WAYPOINT_RECORDING = 0xf1f17ae7,
		TASK_VEHICLE_GOTO_NAVMESH = 0xfbb43c4a,
		TASK_VEHICLE_MISSION_PED_TARGET = 0xb41f1a34,
		TASK_VEHICLE_MISSION = 0xb41f1a34,
		TASK_VEHICLE_PARK = 0xefc8537e,
		TASK_VEHICLE_TEMP_ACTION = 0x81b4d53a,
		TASK_WANDER_IN_AREA = 0x370bcf53,
		TASK_WANDER_STANDARD = 0xbba3b7ca,
		TASK_WARP_PED_INTO_VEHICLE = 0xbc555b9d,
		TASK_WRITHE = 0x8ec23e41,
		TASK_VEHICLE_AIM_AT_COORD = 0x00c59c52,
		TASK_VEHICLE_AIM_AT_PED = 0x6f30f4c1,
		TASK_VEHICLE_SHOOT_AT_COORD = 0xaf18b824,
		TASK_VEHICLE_SHOOT_AT_PED = 0x20123810,
		_TASK_ENTER_VEHICLE = 0x950b6492,
		_TASK_PERFORM_SEQUENCE = 0xe763797
	};

	int ntv_task_state(ntv_task_t t) const {
		return nob::ntv::AI::GET_SCRIPT_TASK_STATUS(
			_h, static_cast<uint32_t>(t));
	}

	bool has_ntv_task(ntv_task_t t) const {
		return ntv_task_state(t) != 7;
	}

	void play_anim(
		const anim_dict &dict,
		const char *name,
		int duration = -1,
		int flag = 0,
		float speed = 8.0f) {
		ntv::AI::TASK_PLAY_ANIM(
			_h,
			dict.native_handle(),
			name,
			speed,
			0.0f,
			duration,
			flag,
			0.0f,
			0,
			0,
			0);
	}

	void stop_anim(const anim_dict &dict, const char *name) {
		ntv::AI::STOP_ANIM_TASK(_h, dict.native_handle(), name, 0.0f);
	}

	////////////////////////////////////////////////////////////////////

	class group {
	public:
		group(const std::string &name) : _n(name), _h(0), _tslc(0) {}

		~group() {
			del();
		}

		void del() {
			if (_tslc && _tslc == this_script::load_count) {
				gc::free(*this);
				_h = 0;
			}
		}

		using native_handle_t = hash_t;

		native_handle_t native_handle() const {
			return _h;
		}

		operator native_handle_t() const {
			return native_handle();
		}

		void add(character chr) {
			auto cur_lc = this_script::load_count;
			if (_tslc != cur_lc) {
				_tslc = cur_lc;
				ntv::PED::ADD_RELATIONSHIP_GROUP(_n.c_str(), &_h);
				auto h = _h;
				gc::delegate(
					*this, [h]() { ntv::PED::REMOVE_RELATIONSHIP_GROUP(h); });
			}
			ntv::PED::SET_PED_RELATIONSHIP_GROUP_HASH(chr, _h);
		}

		void rm(character chr) {
			ntv::PED::SET_PED_RELATIONSHIP_GROUP_HASH(
				chr, ntv::PED::GET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(chr));
		}

		void cant_be_damaged(entity e, bool toggle = true) {
			ntv::ENTITY::SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(
				e, !toggle, _h);
		}

		void like(const group &target) {
			ntv::PED::SET_RELATIONSHIP_BETWEEN_GROUPS(2, _h, target);
		}

		void hate(const group &target) {
			ntv::PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, _h, target);
		}

		void clear_relationship(const group &target) {
			ntv::PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(
				ntv::PED::GET_RELATIONSHIP_BETWEEN_GROUPS(_h, target),
				_h,
				target);
		}

	private:
		std::string _n;
		hash_t _h;
		size_t _tslc;
	};
};

class vehicle : public entity {
public:
	vehicle(int native_handle = 0) : entity(native_handle) {}

	vehicle(model m, const vector3 &coords, float heading = 0.0f) :
		entity(ntv::VEHICLE::CREATE_VEHICLE(
			m.load(), coords.x, coords.y, coords.z, heading, false, false)) {
		if (!_h) {
			return;
		}

		auto h = _h;
		gc::delegate(*this, [h]() mutable {
			if (ntv::ENTITY::DOES_ENTITY_EXIST(h)) {
				ntv::VEHICLE::DELETE_VEHICLE(&h);
			}
		});

		ntv::VEHICLE::SET_VEHICLE_MOD_KIT(_h, 0);
	}

	void del() {
		gc::undelegate(*this);

		ntv::VEHICLE::DELETE_VEHICLE(&_h);
	}

	void free() {
		gc::undelegate(*this);

		ntv::ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&_h);
	}

	void place_on_ground() {
		ntv::VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(_h);
	}

	static constexpr int mod_type_sum = 50;

	int mod_sum(int type) const {
		return ntv::VEHICLE::GET_NUM_VEHICLE_MODS(_h, type);
	}

	void mod(int type, int ix) {
		ntv::VEHICLE::SET_VEHICLE_MOD(_h, type, ix, true);
	}

	int mod(int type) {
		return ntv::VEHICLE::GET_VEHICLE_MOD(_h, type);
	}

	std::string mod_type_name(int type) {
		auto c_str = ntv::VEHICLE::GET_MOD_SLOT_NAME(_h, type);
		if (c_str) {
			std::string str(c_str);
			if (str.length()) {
				return std::move(str);
			}
		}
		return "MOD_TYPE_" + std::to_string(type);
	}

	std::string mod_name(int type, int ix) {
		auto c_str = ntv::VEHICLE::GET_MOD_TEXT_LABEL(_h, type, ix);
		if (c_str) {
			std::string str(c_str);
			if (str.length()) {
				return std::move(str);
			}
		}
		return "MOD_" + (ix < 0 ? std::string("DEFAULT") : std::to_string(ix));
	}

	void set_best_mods() {
		for (int i = 1; i < mod_type_sum; ++i) {
			if (i == 14 || i == 15 || i == 23 || i == 24 || i == 48) {
				continue;
			}

			auto n = mod_sum(i);
			if (n > 0) {
				mod(i, n - 1);
			}
		}
	}

	enum class tint_type_t : int {
		normal = 0,
		metallic,
		pearl,
		matte,
		metal,
		chrome
	};

	void tint(tint_type_t type, int ix) {
		ntv::VEHICLE::SET_VEHICLE_MOD_COLOR_1(
			_h, static_cast<int>(type), ix, 0);
	}

	void second_tint(tint_type_t type, int ix) {
		ntv::VEHICLE::SET_VEHICLE_MOD_COLOR_2(_h, static_cast<int>(type), ix);
	}

	struct tint_t {
		tint_type_t type;
		int ix;
	};

	void tint(const tint_t &t) {
		tint(t.type, t.ix);
	}

	void second_tint(const tint_t &t) {
		second_tint(t.type, t.ix);
	}

	tint_t tint() const {
		tint_t t;
		int pl;
		ntv::VEHICLE::GET_VEHICLE_MOD_COLOR_1(
			_h, reinterpret_cast<int *>(&t.type), &t.ix, &pl);
		return t;
	}

	tint_t secondary_tint() const {
		tint_t t;
		ntv::VEHICLE::GET_VEHICLE_MOD_COLOR_2(
			_h, reinterpret_cast<int *>(&t.type), &t.ix);
		return t;
	}

	std::string tint_name() const {
		return ntv::VEHICLE::GET_VEHICLE_MOD_COLOR_1_NAME(_h, false);
	}

	std::string second_tint_name() const {
		return ntv::VEHICLE::GET_VEHICLE_MOD_COLOR_2_NAME(_h);
	}

	void tints_from_ll_ix(int primary, int secondary) {
		ntv::VEHICLE::SET_VEHICLE_COLOURS(_h, primary, secondary);
	}

	void tints_ll_ix(int &primary, int &secondary) const {
		ntv::VEHICLE::GET_VEHICLE_COLOURS(_h, &primary, &secondary);
	}

	enum class lights_state_t : uint8_t { off, low_beams_on, high_beams_on };

	lights_state_t lights_state() const {
		BOOL low_beams_on, high_beams_on;
		ntv::VEHICLE::GET_VEHICLE_LIGHTS_STATE(
			_h, &low_beams_on, &high_beams_on);
		if (high_beams_on) {
			return lights_state_t::high_beams_on;
		}
		if (low_beams_on) {
			return lights_state_t::low_beams_on;
		}
		return lights_state_t::off;
	}

	void lights_state(lights_state_t ls) {
		auto cls = lights_state();
		switch (ls) {
		case lights_state_t::high_beams_on:
			if (cls == lights_state_t::high_beams_on) {
				return;
			}
			if (cls == lights_state_t::off) {
				ntv::VEHICLE::SET_VEHICLE_LIGHTS(_h, 3);
				return;
			}
			ntv::VEHICLE::SET_VEHICLE_FULLBEAM(_h, true);
			return;
		case lights_state_t::low_beams_on:
			if (cls == lights_state_t::high_beams_on) {
				ntv::VEHICLE::SET_VEHICLE_FULLBEAM(_h, false);
			}
			if (cls == lights_state_t::low_beams_on) {
				return;
			}
			ntv::VEHICLE::SET_VEHICLE_LIGHTS(_h, 3);
			return;
		case lights_state_t::off:
			if (cls == lights_state_t::off) {
				return;
			}
			if (cls == lights_state_t::high_beams_on) {
				ntv::VEHICLE::SET_VEHICLE_FULLBEAM(_h, false);
			}
			ntv::VEHICLE::SET_VEHICLE_LIGHTS(_h, 4);
		}
	}

	bool is_playing_radio() const {
		return ntv::AUDIO::_IS_VEHICLE_RADIO_LOUD(_h);
	}

	std::string radio_station() const {
		if (ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(
				ntv::PLAYER::PLAYER_PED_ID(), _h) &&
			is_playing_radio()) {
			return ntv::AUDIO::GET_PLAYER_RADIO_STATION_NAME();
		}
		return "OFF";
	}

	void radio_station(const std::string &rs) {
		if (rs.empty()) {
			ntv::AUDIO::SET_VEH_RADIO_STATION(_h, "OFF");
			return;
		}
		ntv::AUDIO::SET_VEH_RADIO_STATION(_h, rs.c_str());
	}

	void honk_horn(bool toggle = true) {
		ntv::AUDIO::SET_HORN_ENABLED(_h, toggle);
	}

	void engine_on(bool toggle = true) {
		ntv::VEHICLE::SET_VEHICLE_ENGINE_ON(_h, toggle, true, true);
	}

	static constexpr float engine_health_max = 1000.0f;
	static constexpr float engine_health_smoking = 300.0f;
	static constexpr float engine_health_fire = 0.0f;
	static constexpr float engine_health_min = -4000.0f;

	/*
		-4000: Engine is destroyed
		0 and below: Engine catches fire and health rapidly declines
		300: Engine is smoking and losing functionality
		1000: Engine is perfect
	*/

	float engine_health() const {
		return ntv::VEHICLE::GET_VEHICLE_ENGINE_HEALTH(_h);
	}

	void engine_health(float v) {
		ntv::VEHICLE::SET_VEHICLE_ENGINE_HEALTH(_h, v);
	}

	static constexpr float petrol_tank_health_max = 1000.0f;
	static constexpr float petrol_tank_health_leaking_gas = 650.0f;
	static constexpr float petrol_tank_health_min = -4000.0f;

	/*
		1000 is max health
		Begins leaking gas at around 650 health
		-999.90002441406 appears to be minimum health, although nothing special
	   occurs
	*/

	float petrol_tank_health() const {
		return ntv::VEHICLE::GET_VEHICLE_PETROL_TANK_HEALTH(_h);
	}

	void petrol_tank_health(float v) {
		ntv::VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(_h, v);
	}

	void explode(bool blast_wave = true) {
		ntv::VEHICLE::EXPLODE_VEHICLE(_h, blast_wave, false);
	}

	void explosion_proof(bool toggle = true) {
		ntv::VEHICLE::SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(
			_h, !toggle);
	}

	bool has(character chr) const {
		return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(chr, _h);
	}

	character passenger_from_seat(int ix) const {
		return ntv::VEHICLE::GET_PED_IN_VEHICLE_SEAT(_h, ix);
	}

	bool has_passenger_from_seat(int ix) const {
		return !ntv::VEHICLE::IS_VEHICLE_SEAT_FREE(_h, ix);
	}

	int passengers_max() {
		return ntv::VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(_h);
	}

	void open_door(int ix, bool instantly = false) {
		ntv::VEHICLE::SET_VEHICLE_DOOR_OPEN(_h, ix, false, instantly);
	}

	void close_all_doors(bool instantly = false) {
		ntv::VEHICLE::SET_VEHICLE_DOORS_SHUT(_h, instantly);
	}

	bool bulletproof_tires() const {
		return !ntv::VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(_h);
	}

	void bulletproof_tires(bool toggle = true) {
		ntv::VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(_h, !toggle);
	}

	void disable_crash_damage(bool toggle = true) {
		ntv::VEHICLE::SET_VEHICLE_STRONG(_h, toggle);
	}

	void action(int ac) {
		ntv::AI::TASK_VEHICLE_TEMP_ACTION(passenger_from_seat(-1), _h, ac, -1);
	}

	enum class class_t : int {
		none = -1,
		compact,
		sedan,
		suv,
		coupe,
		muscle,
		sport_classic,
		sport,
		super,
		motorcycle,
		off_road,
		industrial,
		utility,
		van,
		cycle,
		boat,
		helicopter,
		plane,
		service,
		emergency,
		military,
		commercial,
		train
	};

	static class_t get_class_from_model(const model &m) {
		if (!m.is_vehicle()) {
			return class_t::none;
		}
		return static_cast<class_t>(
			ntv::VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(m));
	}

	class_t get_class() const {
		return static_cast<class_t>(ntv::VEHICLE::GET_VEHICLE_CLASS(_h));
	}

	class names_t {
	public:
		std::string veh_name, com_name;

		names_t(const std::string &vn = "", const std::string &cn = "") :
			veh_name(vn), com_name(cn) {}

		const std::string &comb() {
			if (_combed.empty()) {
				_combed =
					com_name.empty() ? veh_name : com_name + " " + veh_name;
			}
			return _combed;
		}

		std::string comb() const {
			if (_combed.empty()) {
				return com_name.empty() ? veh_name : com_name + " " + veh_name;
			}
			return _combed;
		}

		operator const std::string &() {
			return comb();
		}

		operator std::string() const {
			return comb();
		}

		operator const char *() {
			return comb().c_str();
		}

	private:
		std::string _combed;
	};

	static names_t display_names_from_model(const model &);

	names_t display_names() const {
		return display_names_from_model(get_model());
	}

	static names_t localized_names_from_model(const model &m) {
		auto dns = display_names_from_model(m);
		dns.veh_name = i18n(dns.veh_name);
		dns.com_name = i18n(dns.com_name);
		return dns;
	}

	names_t localized_names() const {
		return localized_names_from_model(get_model());
	}

	bool is_armed() const {
		return ntv::VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(_h);
	}

	void special_ability_bar_active(bool toggle = true) {
		ntv::VEHICLE::_SET_VEHICLE_HUD_SPECIAL_ABILITY_BAR_ACTIVE(_h, toggle);
	}
};

inline bool character::is_on_vehicle(vehicle veh) const {
	return ntv::PED::IS_PED_ON_SPECIFIC_VEHICLE(_h, veh);
}

inline void character::get_in_vehicle(vehicle veh, int seat, bool run_to) {
	ntv::AI::TASK_ENTER_VEHICLE(_h, veh, -1, seat, run_to ? 2.0f : 1.0f, 1, 0);
}

inline void character::into_vehicle(vehicle veh, int seat) {
	ntv::PED::SET_PED_INTO_VEHICLE(_h, veh, seat);
}

inline vehicle character::current_vehicle() const {
	return ntv::PED::GET_VEHICLE_PED_IS_IN(_h, false);
}

inline vehicle character::last_vehicle() const {
	return ntv::PED::GET_VEHICLE_PED_IS_IN(_h, true);
}

inline vehicle character::trying_to_enter_vehicle() const {
	return ntv::PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(_h);
}

inline int character::trying_to_enter_vehicle_seat() const {
	return ntv::PED::GET_SEAT_PED_IS_TRYING_TO_ENTER(_h);
}

inline void
character::drive_to(const nob::vector3 &coords, float speed, bool along_paths) {
	auto veh = current_vehicle();
	if (!veh) {
		return;
	}
	nob::ntv::AI::TASK_VEHICLE_DRIVE_TO_COORD(
		_h,
		veh,
		coords.x,
		coords.y,
		coords.z,
		speed,
		0,
		veh.get_model(),
		along_paths ? 262144 : 16777216,
		0.f,
		0.f);
}

class plane : public vehicle {
public:
	using vehicle::vehicle;

	enum class landing_gear_state : int {
		deployed = 0,
		closing,
		opening,
		retracted
	};

	void landing_gear(landing_gear_state state) {
		ntv::VEHICLE::CONTROL_LANDING_GEAR(_h, static_cast<int>(state));
	}

	landing_gear_state landing_gear() {
		return static_cast<landing_gear_state>(
			ntv::VEHICLE::GET_LANDING_GEAR_STATE(_h));
	}

	bool has_landing_gear() {
		return ntv::VEHICLE::_VEHICLE_HAS_LANDING_GEAR(_h);
	}

	void jet_engine_on(bool toggle = true) {
		ntv::VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(_h, toggle);
	}
};

class helicopter : public plane {
public:
	using plane::plane;

	/*
		Max 1000.
		At -100 both helicopter rotors will stall.
	*/

	float heli_engine_health() const {
		return ntv::VEHICLE::_GET_HELI_ENGINE_HEALTH(_h);
	}

	/*
		Max 1000.
		At 0 the tail rotor will stall.
	*/

	float rotor_health() const {
		return ntv::VEHICLE::_GET_HELI_MAIN_ROTOR_HEALTH(_h);
	}

	float tail_rotor_health() const {
		return ntv::VEHICLE::_GET_HELI_TAIL_ROTOR_HEALTH(_h);
	}

	void searchlight(bool toggle = true) {
		ntv::VEHICLE::SET_VEHICLE_SEARCHLIGHT(_h, toggle, false);
	}

	void rotor_lift_force(float val = 1.0f) {
		ntv::VEHICLE::SET_HELI_BLADES_SPEED(_h, val);
	}
};

class cargobob : public helicopter {
public:
	using helicopter::helicopter;

	void detach(vehicle veh) {
		if (_h) {
			ntv::VEHICLE::DETACH_VEHICLE_FROM_CARGOBOB(veh, _h);
		} else {
			ntv::VEHICLE::DETACH_VEHICLE_FROM_ANY_CARGOBOB(veh);
		}
	}

	bool is_attached(vehicle veh) const {
		return ntv::VEHICLE::IS_VEHICLE_ATTACHED_TO_CARGOBOB(_h, veh);
	}

	vehicle attached() const {
		return ntv::VEHICLE::GET_VEHICLE_ATTACHED_TO_CARGOBOB(_h);
	}

	void attach(vehicle veh) {
		ntv::VEHICLE::ATTACH_VEHICLE_TO_CARGOBOB(veh, _h, 0, 0, 0, 0);
	}

	void put_down_hook() {
		ntv::VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(_h, 0);
	}

	void put_down_magnet() {
		ntv::VEHICLE::CREATE_PICK_UP_ROPE_FOR_CARGOBOB(_h, 1);
	}

	void magnet_strength(float val) {
		ntv::VEHICLE::_SET_CARGOBOB_PICKUP_MAGNET_STRENGTH(_h, val);
	}

	bool has_magnet() const {
		return ntv::VEHICLE::_DOES_CARGOBOB_HAVE_PICKUP_MAGNET(_h);
	}
};

////////////////////////////////////////////////////////////////////////////

extern const std::array<hasher, 696> characters;

extern const std::array<const char *, 696> characters_desc;

extern const std::array<hasher, 304> base_vehicles;

const std::vector<hasher> &dlc_vehicles();

void unban_vehicles();

const std::vector<hasher> &banned_vehicles();

} // namespace nob
