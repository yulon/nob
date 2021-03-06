#include <nob/log.hpp>
#include <nob/ntv.hpp>
#include <nob/program.hpp>
#include <nob/script.hpp>
#include <nob/shv.hpp>

#include "disable_ws2.hpp"

#include <minhook.hpp>

#include <windows.h>

#include <cassert>
#include <cstring>
#include <queue>
#include <vector>

namespace nob {

extern std::queue<std::function<void()>> _inputs;

static inline void _clear_inputs() {
	while (_inputs.size()) {
		_inputs.pop();
	}
}

static inline void _flush_inputs() {
	while (_inputs.size()) {
		go(_inputs.front());
		_inputs.pop();
	}
}

namespace _hkl {
void recv();
void prevent_defaults();
} // namespace _hkl

namespace this_script {

mode_t mode = mode_t::not_loaded;

size_t load_count = 0;
std::atomic<size_t> load_count_s(0);

std::atomic<std::thread::id> thread_id;

std::atomic<bool> is_exiting(false);
std::atomic<bool> _is_exited(false);

static int _last_fc = -1;

static inline void _init() {
	_disable_ws2();

	thread_id = std::this_thread::get_id();
	load_count = ++load_count_s;

	on_load::handle();
	_clear_inputs();
}

static inline void _exit() {
	if (_is_exited) {
		return;
	}
	on_unload::handle();
	_is_exited = true;
}

static inline bool _run(bool auto_init = true, bool need_init = false) {
	_hkl::recv();

	if (auto_init) {
		auto cur_fc = ntv::GAMEPLAY::GET_FRAME_COUNT();
		if (cur_fc - _last_fc > 1) {
			need_init = true;
		}
		_last_fc = cur_fc;
	}

	if (need_init) {
		_init();
	} else {
		_flush_inputs();
	}

	if (is_exiting) {
		_exit();
		return false;
	}

	task::executor().step();

	_hkl::prevent_defaults();
	return true;
}

void WINAPI _shv_main() {
	while (_run()) {
		shv::WAIT(0);
	}
}

void _ysc_main() {
	while (_run()) {
		ntv::SYSTEM::WAIT(0);
	}
	ntv::SCRIPT::TERMINATE_THIS_THREAD();
}

bool _create_from_main_td() {
	if (!ntv::func_table) {
		return false;
	}

	static minhook<ntv::func_t> wait_hkd;

	ntv::func_t wait_fp;

	for (wait_fp = ntv::SYSTEM::WAIT.target(); !wait_fp;
		 wait_fp = ntv::SYSTEM::WAIT.target()) {
		Sleep(500);
		if (*ntv::game_state == ntv::game_state_t::playing) {
			wait_fp = ntv::SYSTEM::WAIT.target();
			if (wait_fp) {
				break;
			}
			log("nob::this_script::_create_from_main_td: "
				"nob::ntv::SYSTEM::WAIT not found!");
			return false;
		}
	}

	if (*reinterpret_cast<uint8_t *>(wait_fp) != 0x8B) {
		log("nob::this_script::_create_from_main_td: hooked by other mod!");
		return false;
	}

	if (!wait_hkd.install(wait_fp, [](ntv::call_context_t &cc) {
			if (strcmp(
					ntv::SCRIPT::GET_THIS_SCRIPT_NAME(), "main_persistent") ==
				0) {
				if (!_run()) {
					wait_hkd.original(cc);
					wait_hkd.uninstall();
					return;
				}
			}
			wait_hkd.original(cc);
		})) {
		log("nob::this_script::_create_from_main_td: hook failed!");
		return false;
	}

	return true;
}

bool _create_from_new_td() {
	static std::unique_ptr<ntv::script_thread_t> td;
	static bool need_init = true;

	td.reset(new ntv::script_thread_t(
		[]() {
			auto life = _run(false, need_init);
			if (need_init) {
				need_init = false;
			}
			if (!life) {
				td.reset();
			}
		},
		[]() { need_init = true; }));
	if (!*td) {
		td.reset();
	}
	return td.get();
}

bool _create_from_td() {
	if (_create_from_new_td()) {
		mode = mode_t::unique_thread;
		return true;
	}
	mode = mode_t::main_thread;
	return _create_from_main_td();
}

} // namespace this_script

struct _script_info {
	const char *name;
	bool essential;
};

std::vector<_script_info> _script_infos = {
	{"abigail1", false},
	{"abigail2", false},
	{"achievement_controller", false},
	{"act_cinema", false},
	{"af_intro_t_sandy", false},
	{"agency_heist1", false},
	{"agency_heist2", false},
	{"agency_heist3a", false},
	{"agency_heist3b", false},
	{"agency_prep1", false},
	{"agency_prep2amb", false},
	{"aicover_test", false},
	{"ainewengland_test", false},
	{"altruist_cult", false},
	{"ambientblimp", false},
	{"ambient_diving", false},
	{"ambient_mrsphilips", false},
	{"ambient_solomon", false},
	{"ambient_sonar", false},
	{"ambient_tonya", false},
	{"ambient_tonyacall", false},
	{"ambient_tonyacall2", false},
	{"ambient_tonyacall5", false},
	{"ambient_ufos", false},
	{"am_airstrike", false},
	{"am_ammo_drop", false},
	{"am_armwrestling", false},
	{"am_armybase", false},
	{"am_backup_heli", false},
	{"am_boat_taxi", false},
	{"am_bru_box", false},
	{"am_car_mod_tut", false},
	{"am_challenges", false},
	{"am_contact_requests", false},
	{"am_cp_collection", false},
	{"am_crate_drop", false},
	{"am_criminal_damage", false},
	{"am_cr_securityvan", false},
	{"am_darts", false},
	{"am_dead_drop", false},
	{"am_destroy_veh", false},
	{"am_distract_cops", false},
	{"am_doors", false},
	{"am_ferriswheel", false},
	{"am_gang_call", false},
	{"am_ga_pickups", false},
	{"am_heist_int", false},
	{"am_heli_taxi", false},
	{"am_hold_up", false},
	{"am_hot_property", false},
	{"am_hot_target", false},
	{"am_hunt_the_beast", false},
	{"am_imp_exp", false},
	{"am_joyrider", false},
	{"am_kill_list", false},
	{"am_king_of_the_castle", false},
	{"am_launcher", false},
	{"am_lester_cut", false},
	{"am_lowrider_int", false},
	{"am_mission_launch", false},
	{"am_mp_carwash_launch", false},
	{"am_mp_garage_control", false},
	{"am_mp_property_ext", false},
	{"am_mp_property_int", false},
	{"am_mp_yacht", false},
	{"am_npc_invites", false},
	{"am_pass_the_parcel", false},
	{"am_penned_in", false},
	{"am_pi_menu", false},
	{"am_plane_takedown", false},
	{"am_prison", false},
	{"am_prostitute", false},
	{"am_rollercoaster", false},
	{"am_rontrevor_cut", false},
	{"am_taxi", false},
	{"am_vehicle_spawn", true},
	{"animal_controller", false},
	{"appbroadcast", false},
	{"appcamera", false},
	{"appchecklist", false},
	{"appcontacts", false},
	{"appemail", false},
	{"appextraction", false},
	{"apphs_sleep", false},
	{"appinternet", false},
	{"appjipmp", false},
	{"appmedia", false},
	{"appmpbossagency", false},
	{"appmpemail", false},
	{"appmpjoblistnew", false},
	{"apporganiser", false},
	{"apprepeatplay", false},
	{"appsettings", false},
	{"appsidetask", false},
	{"apptextmessage", false},
	{"appdelegateify", false},
	{"appvlsi", false},
	{"appzit", false},
	{"armenian1", false},
	{"armenian2", false},
	{"armenian3", false},
	{"assassin_bus", false},
	{"assassin_construction", false},
	{"assassin_hooker", false},
	{"assassin_multi", false},
	{"assassin_rankup", false},
	{"assassin_valet", false},
	{"atm_trigger", false},
	{"audiotest", false},
	{"autosave_controller", false},
	{"bailbond1", false},
	{"bailbond2", false},
	{"bailbond3", false},
	{"bailbond4", false},
	{"bailbond_launcher", false},
	{"barry1", false},
	{"barry2", false},
	{"barry3", false},
	{"barry3a", false},
	{"barry3c", false},
	{"barry4", false},
	{"benchmark", false},
	{"bigwheel", false},
	{"bj", false},
	{"blimptest", true},
	{"blip_controller", true},
	{"bootycallhandler", false},
	{"bootycall_debug_controller", false},
	{"buddydeathresponse", false},
	{"bugstar_mission_export", false},
	{"buildingsiteambience", false},
	{"building_controller", false},
	{"cablecar", false},
	{"camera_test", false},
	{"cam_coord_sender", true},
	{"candidate_controller", false},
	{"carmod_shop", false},
	{"carsteal1", false},
	{"carsteal2", false},
	{"carsteal3", false},
	{"carsteal4", false},
	{"carwash1", false},
	{"carwash2", false},
	{"car_roof_test", false},
	{"celebrations", false},
	{"celebration_editor", false},
	{"cellphone_controller", false},
	{"cellphone_flashhand", false},
	{"charactergoals", false},
	{"charanimtest", false},
	{"cheat_controller", false},
	{"chinese1", false},
	{"chinese2", false},
	{"chop", false},
	{"clothes_shop_mp", false},
	{"clothes_shop_sp", false},
	{"code_controller", false},
	{"combat_test", false},
	{"comms_controller", false},
	{"completionpercentage_controller", false},
	{"component_checker", false},
	{"context_controller", false},
	{"controller_ambientarea", false},
	{"controller_races", false},
	{"controller_taxi", false},
	{"controller_towing", false},
	{"controller_trafficking", false},
	{"coordinate_recorder", false},
	{"country_race", false},
	{"country_race_controller", false},
	{"creation_startup", false},
	{"creator", false},
	{"custom_config", false},
	{"cutscenemetrics", false},
	{"cutscenesamples", false},
	{"cutscene_test", false},
	{"darts", false},
	{"debug", false},
	{"debug_app_select_screen", false},
	{"debug_launcher", false},
	{"density_test", false},
	{"dialogue_handler", false},
	{"director_mode", false},
	{"docks2asubhandler", false},
	{"docks_heista", false},
	{"docks_heistb", false},
	{"docks_prep1", false},
	{"docks_prep2b", false},
	{"docks_setup", false},
	{"dreyfuss1", false},
	{"drf1", false},
	{"drf2", false},
	{"drf3", false},
	{"drf4", false},
	{"drf5", false},
	{"drunk", false},
	{"drunk_controller", false},
	{"dynamixtest", false},
	{"email_controller", false},
	{"emergencycall", false},
	{"emergencycalllauncher", false},
	{"epscars", true}, // no clue what this is but ok
	{"epsdesert", false},
	{"epsilon1", false},
	{"epsilon2", false},
	{"epsilon3", false},
	{"epsilon4", false},
	{"epsilon5", false},
	{"epsilon6", false},
	{"epsilon7", false},
	{"epsilon8", false},
	{"epsilontract", false},
	{"epsrobes", false},
	{"event_controller", false},
	{"exile1", false},
	{"exile2", false},
	{"exile3", false},
	{"exile_city_denial", false},
	{"extreme1", false},
	{"extreme2", false},
	{"extreme3", false},
	{"extreme4", false},
	{"fairgroundhub", false},
	{"fake_interiors", false},
	{"fameorshame_eps", false},
	{"fameorshame_eps_1", false},
	{"fame_or_shame_set", false},
	{"family1", false},
	{"family1taxi", false},
	{"family2", false},
	{"family3", false},
	{"family4", false},
	{"family5", false},
	{"family6", false},
	{"family_scene_f0", false},
	{"family_scene_f1", false},
	{"family_scene_m", false},
	{"family_scene_t0", false},
	{"family_scene_t1", false},
	{"fanatic1", false},
	{"fanatic2", false},
	{"fanatic3", false},
	{"fbi1", false},
	{"fbi2", false},
	{"fbi3", false},
	{"fbi4", false},
	{"fbi4_intro", false},
	{"fbi4_prep1", false},
	{"fbi4_prep2", false},
	{"fbi4_prep3", false},
	{"fbi4_prep3amb", false},
	{"fbi4_prep4", false},
	{"fbi4_prep5", false},
	{"fbi5a", false},
	{"filenames.txt", false},
	{"finalea", false},
	{"finaleb", false},
	{"finalec1", false},
	{"finalec2", false},
	{"finale_choice", false},
	{"finale_credits", false},
	{"finale_endgame", false},
	{"finale_heist1", false},
	{"finale_heist2a", false},
	{"finale_heist2b", false},
	{"finale_heist2_intro", false},
	{"finale_heist_prepa", false},
	{"finale_heist_prepb", false},
	{"finale_heist_prepc", false},
	{"finale_heist_prepd", false},
	{"finale_heist_prepeamb", false},
	{"finale_intro", false},
	{"floating_help_controller", false},
	{"flowintrotitle", false},
	{"flowstartaccept", false},
	{"flow_autoplay", false},
	{"flow_controller", false},
	{"flow_help", false},
	{"flyunderbridges", false},
	{"fmmc_launcher", false},
	{"fmmc_playlist_controller", false},
	{"fm_bj_race_controler", false},
	{"fm_capture_creator", false},
	{"fm_deathmatch_controler", false},
	{"fm_deathmatch_creator", false},
	{"fm_hideout_controler", false},
	{"fm_hold_up_tut", false},
	{"fm_horde_controler", false},
	{"fm_impromptu_dm_controler", false},
	{"fm_intro", false},
	{"fm_intro_cut_dev", false},
	{"fm_lts_creator", false},
	{"fm_maintain_cloud_header_data", false},
	{"fm_maintain_transition_players", false},
	{"fm_main_menu", false},
	{"fm_mission_controller", false},
	{"fm_mission_creator", false},
	{"fm_race_controler", false},
	{"fm_race_creator", false},
	{"forsalesigns", false},
	{"fps_test", false},
	{"fps_test_mag", false},
	{"franklin0", false},
	{"franklin1", false},
	{"franklin2", false},
	{"freemode", false},
	{"freemode_init", false},
	{"friendactivity", false},
	{"friends_controller", false},
	{"friends_debug_controller", false},
	{"fullmap_test", true},
	{"fullmap_test_flow", true},
	{"game_server_test", false},
	{"gb_assault", false},
	{"gb_bellybeast", false},
	{"gb_carjacking", false},
	{"gb_collect_money", false},
	{"gb_deathmatch", false},
	{"gb_finderskeepers", false},
	{"gb_fivestar", false},
	{"gb_hunt_the_boss", false},
	{"gb_point_to_point", false},
	{"gb_rob_shop", false},
	{"gb_sightseer", false},
	{"gb_terminate", false},
	{"gb_yacht_rob", false},
	{"general_test", false},
	{"golf", false},
	{"golf_ai_foursome", false},
	{"golf_ai_foursome_putting", false},
	{"golf_mp", false},
	{"gpb_andymoon", false},
	{"gpb_baygor", false},
	{"gpb_billbinder", false},
	{"gpb_clinton", false},
	{"gpb_griff", false},
	{"gpb_jane", false},
	{"gpb_jerome", false},
	{"gpb_jesse", false},
	{"gpb_mani", false},
	{"gpb_mime", false},
	{"gpb_pameladrake", false},
	{"gpb_superhero", false},
	{"gpb_tonya", false},
	{"gpb_zombie", false},
	{"gtest_airplane", false},
	{"gtest_avoidance", false},
	{"gtest_boat", false},
	{"gtest_divingfromcar", false},
	{"gtest_divingfromcarwhilefleeing", false},
	{"gtest_helicopter", false},
	{"gtest_nearlymissedbycar", false},
	{"gunclub_shop", false},
	{"gunfighttest", false},
	{"hairdo_shop_mp", false},
	{"hairdo_shop_sp", false},
	{"hao1", false},
	{"headertest", false},
	{"heatmap_test", false},
	{"heatmap_test_flow", false},
	{"heist_ctrl_agency", false},
	{"heist_ctrl_docks", false},
	{"heist_ctrl_finale", false},
	{"heist_ctrl_jewel", false},
	{"heist_ctrl_rural", false},
	{"heli_gun", false},
	{"heli_streaming", true},
	{"hud_creator", true},
	{"hunting1", false},
	{"hunting2", false},
	{"hunting_ambient", false},
	{"idlewarper", false},
	{"ingamehud", true},
	{"initial", false},
	{"jewelry_heist", false},
	{"jewelry_prep1a", false},
	{"jewelry_prep1b", false},
	{"jewelry_prep2a", false},
	{"jewelry_setup1", false},
	{"josh1", false},
	{"josh2", false},
	{"josh3", false},
	{"josh4", false},
	{"lamar1", false},
	{"laptop_trigger", false},
	{"launcher_abigail", false},
	{"launcher_barry", false},
	{"launcher_basejumpheli", false},
	{"launcher_basejumppack", false},
	{"launcher_carwash", false},
	{"launcher_darts", false},
	{"launcher_dreyfuss", false},
	{"launcher_epsilon", false},
	{"launcher_extreme", false},
	{"launcher_fanatic", false},
	{"launcher_golf", false},
	{"launcher_hao", false},
	{"launcher_hunting", false},
	{"launcher_hunting_ambient", false},
	{"launcher_josh", false},
	{"launcher_maude", false},
	{"launcher_minute", false},
	{"launcher_mrsphilips", false},
	{"launcher_nigel", false},
	{"launcher_offroadracing", false},
	{"launcher_omega", false},
	{"launcher_paparazzo", false},
	{"launcher_pilotschool", false},
	{"launcher_racing", false},
	{"launcher_rampage", false},
	{"launcher_range", false},
	{"launcher_stunts", false},
	{"launcher_tennis", false},
	{"launcher_thelastone", false},
	{"launcher_tonya", false},
	{"launcher_triathlon", false},
	{"launcher_yoga", false},
	{"lester1", false},
	{"lesterhandler", false},
	{"letterscraps", false},
	{"line_activation_test", false},
	{"liverecorder", false},
	{"locates_tester", false},
	{"luxe_veh_activity", false},
	{"magdemo", false},
	{"magdemo2", false},
	{"main", false},
	{"maintransition", false},
	{"main_install", false},
	{"main_persistent", true},
	{"martin1", false},
	{"maude1", false},
	{"maude_postbailbond", false},
	{"me_amanda1", false},
	{"me_jimmy1", false},
	{"me_tracey1", false},
	{"mg_race_to_point", false},
	{"michael1", false},
	{"michael2", false},
	{"michael3", false},
	{"michael4", false},
	{"michael4leadout", false},
	{"minigame_ending_stinger", false},
	{"minigame_stats_delegateer", false},
	{"minute1", false},
	{"minute2", false},
	{"minute3", false},
	{"mission_race", false},
	{"mission_repeat_controller", false},
	{"mission_stat_alerter", false},
	{"mission_stat_watcher", false},
	{"mission_triggerer_a", false},
	{"mission_triggerer_b", false},
	{"mission_triggerer_c", false},
	{"mission_triggerer_d", false},
	{"mpstatsinit", false},
	{"mptestbed", false},
	{"mp_awards", false},
	{"mp_fm_registration", false},
	{"mp_menuped", false},
	{"mp_prop_global_block", false},
	{"mp_prop_special_global_block", false},
	{"mp_registration", false},
	{"mp_save_game_global_block", false},
	{"mp_unlocks", false},
	{"mp_weapons", false},
	{"mrsphilips1", false},
	{"mrsphilips2", false},
	{"murdermystery", false},
	{"navmeshtest", false},
	{"net_bot_brain", false},
	{"net_bot_simplebrain", false},
	{"net_cloud_mission_loader", false},
	{"net_combat_soaktest", false},
	{"net_jacking_soaktest", false},
	{"net_rank_tunable_loader", false},
	{"net_session_soaktest", false},
	{"net_tunable_check", false},
	{"nigel1", false},
	{"nigel1a", false},
	{"nigel1b", false},
	{"nigel1c", false},
	{"nigel1d", false},
	{"nigel2", false},
	{"nigel3", false},
	{"nodeviewer", false},
	{"ob_abatdoor", false},
	{"ob_abattoircut", false},
	{"ob_airdancer", false},
	{"ob_bong", false},
	{"ob_cashregister", false},
	{"ob_drinking_shots", false},
	{"ob_foundry_cauldron", false},
	{"ob_franklin_beer", false},
	{"ob_franklin_tv", false},
	{"ob_franklin_wine", false},
	{"ob_huffing_gas", false},
	{"ob_mp_bed_high", false},
	{"ob_mp_bed_low", false},
	{"ob_mp_bed_med", false},
	{"ob_mp_shower_med", false},
	{"ob_mp_stripper", false},
	{"ob_mr_raspberry_jam", false},
	{"ob_poledancer", false},
	{"ob_sofa_franklin", false},
	{"ob_sofa_michael", false},
	{"ob_telescope", false},
	{"ob_tv", false},
	{"ob_vend1", false},
	{"ob_vend2", false},
	{"ob_wheatgrass", false},
	{"offroad_races", false},
	{"omega1", false},
	{"omega2", false},
	{"paparazzo1", false},
	{"paparazzo2", false},
	{"paparazzo3", false},
	{"paparazzo3a", false},
	{"paparazzo3b", false},
	{"paparazzo4", false},
	{"paradise", false},
	{"paradise2", false},
	{"pausemenu", true},
	{"pausemenu_example", true},
	{"pausemenu_map", true},
	{"pausemenu_multiplayer", false},
	{"pausemenu_sp_repeat", true},
	{"pb_busker", false},
	{"pb_homeless", false},
	{"pb_preacher", false},
	{"pb_prostitute", false},
	{"photographymonkey", false},
	{"photographywildlife", false},
	{"physics_perf_test", false},
	{"physics_perf_test_launcher", false},
	{"pickuptest", false},
	{"pickupvehicles", true},
	{"pickup_controller", false},
	{"pilot_school", false},
	{"pilot_school_mp", false},
	{"pi_menu", false},
	{"placeholdermission", false},
	{"placementtest", false},
	{"planewarptest", false},
	{"player_controller", false},
	{"player_controller_b", false},
	{"player_scene_ft_franklin1", false},
	{"player_scene_f_lamgraff", false},
	{"player_scene_f_lamtaunt", false},
	{"player_scene_f_taxi", false},
	{"player_scene_mf_traffic", false},
	{"player_scene_m_cinema", false},
	{"player_scene_m_fbi2", false},
	{"player_scene_m_kids", false},
	{"player_scene_m_shopping", false},
	{"player_scene_t_bbfight", false},
	{"player_scene_t_chasecar", false},
	{"player_scene_t_insult", false},
	{"player_scene_t_park", false},
	{"player_scene_t_tie", false},
	{"player_timetable_scene", false},
	{"playthrough_builder", false},
	{"pm_defend", false},
	{"pm_delivery", false},
	{"pm_gang_attack", false},
	{"pm_plane_promotion", false},
	{"pm_recover_stolen", false},
	{"postkilled_bailbond2", false},
	{"postrc_barry1and2", false},
	{"postrc_barry4", false},
	{"postrc_epsilon4", false},
	{"postrc_nigel3", false},
	{"profiler_registration", false},
	{"prologue1", false},
	{"prop_drop", false},
	{"racetest", false},
	{"rampage1", false},
	{"rampage2", false},
	{"rampage3", false},
	{"rampage4", false},
	{"rampage5", false},
	{"rampage_controller", false},
	{"randomchar_controller", false},
	{"range_modern", false},
	{"range_modern_mp", false},
	{"replay_controller", true},
	{"rerecord_recording", false},
	{"respawn_controller", false},
	{"restrictedareas", false},
	{"re_abandonedcar", false},
	{"re_accident", false},
	{"re_armybase", false},
	{"re_arrests", false},
	{"re_atmrobbery", false},
	{"re_bikethief", false},
	{"re_border", false},
	{"re_burials", false},
	{"re_bus_tours", false},
	{"re_cartheft", false},
	{"re_chasethieves", false},
	{"re_crashrescue", false},
	{"re_cultshootout", false},
	{"re_dealgonewrong", false},
	{"re_domestic", false},
	{"re_drunkdriver", false},
	{"re_duel", false},
	{"re_gangfight", false},
	{"re_gang_intimidation", false},
	{"re_getaway_driver", false},
	{"re_hitch_lift", false},
	{"re_homeland_security", false},
	{"re_lossantosintl", false},
	{"re_lured", false},
	{"re_monkey", false},
	{"re_mountdance", false},
	{"re_muggings", false},
	{"re_paparazzi", false},
	{"re_prison", false},
	{"re_prisonerlift", false},
	{"re_prisonvanbreak", false},
	{"re_rescuehostage", false},
	{"re_seaplane", false},
	{"re_securityvan", false},
	{"re_shoprobbery", false},
	{"re_snatched", false},
	{"re_stag_do", false},
	{"re_yetarian", false},
	{"rollercoaster", false},
	{"rural_bank_heist", false},
	{"rural_bank_prep1", false},
	{"rural_bank_setup", false},
	{"savegame_bed", false},
	{"save_anywhere", false},
	{"scaleformgraphictest", false},
	{"scaleformminigametest", false},
	{"scaleformprofiling", false},
	{"scaleformtest", false},
	{"scene_builder", false},
	{"sclub_front_bouncer", false},
	{"scripted_cam_editor", false},
	{"scriptplayground", false},
	{"scripttest1", false},
	{"scripttest2", false},
	{"scripttest3", false},
	{"scripttest4", false},
	{"script_metrics", false},
	{"sctv", false},
	{"sc_lb_global_block", false},
	{"selector", true},
	{"selector_example", false},
	{"selling_short_1", false},
	{"selling_short_2", false},
	{"shooting_camera", false},
	{"shoprobberies", false},
	{"shop_controller", false},
	{"shot_bikejump", false},
	{"shrinkletter", false},
	{"sh_intro_f_hills", false},
	{"sh_intro_m_home", false},
	{"smoketest", false},
	{"social_controller", false},
	{"solomon1", false},
	{"solomon2", false},
	{"solomon3", false},
	{"spaceshipparts", false},
	{"spawn_activities", false},
	{"speech_reverb_delegateer", false},
	{"spmc_instancer", false},
	{"spmc_preloader", false},
	{"sp_dlc_registration", false},
	{"sp_editor_mission_instance", false},
	{"sp_menuped", false},
	{"sp_pilotschool_reg", false},
	{"standard_global_init", false},
	{"standard_global_reg", false},
	{"startup", false},
	{"startup_install", false},
	{"startup_locationtest", false},
	{"startup_positioning", false},
	{"startup_smoketest", false},
	{"stats_controller", false},
	{"stock_controller", false},
	{"streaming", false},
	{"stripclub", false},
	{"stripclub_drinking", false},
	{"stripclub_mp", false},
	{"stripperhome", false},
	{"stunt_plane_races", false},
	{"tasklist_1", false},
	{"tattoo_shop", false},
	{"taxilauncher", false},
	{"taxiservice", false},
	{"taxitutorial", false},
	{"taxi_clowncar", false},
	{"taxi_cutyouin", false},
	{"taxi_deadline", false},
	{"taxi_followcar", false},
	{"taxi_gotyounow", false},
	{"taxi_gotyourback", false},
	{"taxi_needexcitement", false},
	{"taxi_procedural", false},
	{"taxi_takeiteasy", false},
	{"taxi_taketobest", false},
	{"tempalpha", false},
	{"temptest", false},
	{"tennis", false},
	{"tennis_ambient", false},
	{"tennis_family", false},
	{"tennis_network_mp", false},
	{"test_startup", false},
	{"thelastone", false},
	{"timershud", true},
	{"title_update_registration", false},
	{"tonya1", false},
	{"tonya2", false},
	{"tonya3", false},
	{"tonya4", false},
	{"tonya5", false},
	{"towing", false},
	{"traffickingsettings", false},
	{"traffickingteleport", false},
	{"traffick_air", false},
	{"traffick_ground", false},
	{"train_create_widget", false},
	{"train_tester", false},
	{"trevor1", false},
	{"trevor2", false},
	{"trevor3", false},
	{"trevor4", false},
	{"triathlonsp", false},
	{"tunables_registration", false},
	{"tuneables_processing", false},
	{"ufo", false},
	{"ugc_global_registration", false},
	{"underwaterpickups", false},
	{"utvc", false},
	{"vehicle_ai_test", false},
	{"vehicle_force_widget", true},
	{"vehicle_gen_controller", false},
	{"vehicle_plate", true},
	{"veh_play_widget", false},
	{"walking_ped", false},
	{"wardrobe_mp", false},
	{"wardrobe_sp", false},
	{"weapon_audio_widget", false},
	{"wp_partyboombox", false},
	{"xml_menus", false},
	{"yoga", false}};

void terminate_unimportant_scripts() {
	for (auto &si : _script_infos) {
		if (!si.essential) {
			ntv::PLAYER::FORCE_CLEANUP_FOR_ALL_THREADS_WITH_THIS_NAME(
				si.name, 8); // Cleanup first
			ntv::GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(
				si.name); // Terminate
		}
	}
	ntv::PLAYER::FORCE_CLEANUP(8);
	ntv::PLAYER::FORCE_CLEANUP(64);
}

} // namespace nob
