#include <nob/entity.hpp>
#include <nob/ntv.hpp>

#include <unordered_map>

namespace nob {
	const std::array<hasher, 696> characters {{
		// These data from ScriptHookV/NativeTrainer
		"player_zero", "player_one", "player_two", "a_c_boar", "a_c_chimp", "a_c_cow", "a_c_coyote", "a_c_deer", "a_c_fish", "a_c_hen",
		"a_c_cat_01", "a_c_chickenhawk", "a_c_cormorant", "a_c_crow", "a_c_dolphin", "a_c_humpback", "a_c_killerwhale", "a_c_pigeon", "a_c_seagull", "a_c_sharkhammer",
		"a_c_pig", "a_c_rat", "a_c_rhesus", "a_c_chop", "a_c_husky", "a_c_mtlion", "a_c_retriever", "a_c_sharktiger", "a_c_shepherd", "s_m_m_movalien_01",
		"a_f_m_beach_01", "a_f_m_bevhills_01", "a_f_m_bevhills_02", "a_f_m_bodybuild_01", "a_f_m_business_02", "a_f_m_downtown_01", "a_f_m_eastsa_01", "a_f_m_eastsa_02", "a_f_m_fatbla_01", "a_f_m_fatcult_01",
		"a_f_m_fatwhite_01", "a_f_m_ktown_01", "a_f_m_ktown_02", "a_f_m_prolhost_01", "a_f_m_salton_01", "a_f_m_skidrow_01", "a_f_m_soucentmc_01", "a_f_m_soucent_01", "a_f_m_soucent_02", "a_f_m_tourist_01",
		"a_f_m_trampbeac_01", "a_f_m_tramp_01", "a_f_o_genstreet_01", "a_f_o_indian_01", "a_f_o_ktown_01", "a_f_o_salton_01", "a_f_o_soucent_01", "a_f_o_soucent_02", "a_f_y_beach_01", "a_f_y_bevhills_01",
		"a_f_y_bevhills_02", "a_f_y_bevhills_03", "a_f_y_bevhills_04", "a_f_y_business_01", "a_f_y_business_02", "a_f_y_business_03", "a_f_y_business_04", "a_f_y_eastsa_01", "a_f_y_eastsa_02", "a_f_y_eastsa_03",
		"a_f_y_epsilon_01", "a_f_y_fitness_01", "a_f_y_fitness_02", "a_f_y_genhot_01", "a_f_y_golfer_01", "a_f_y_hiker_01", "a_f_y_hippie_01", "a_f_y_hipster_01", "a_f_y_hipster_02", "a_f_y_hipster_03",
		"a_f_y_hipster_04", "a_f_y_indian_01", "a_f_y_juggalo_01", "a_f_y_runner_01", "a_f_y_rurmeth_01", "a_f_y_scdressy_01", "a_f_y_skater_01", "a_f_y_soucent_01", "a_f_y_soucent_02", "a_f_y_soucent_03",
		"a_f_y_tennis_01", "a_f_y_topless_01", "a_f_y_tourist_01", "a_f_y_tourist_02", "a_f_y_vinewood_01", "a_f_y_vinewood_02", "a_f_y_vinewood_03", "a_f_y_vinewood_04", "a_f_y_yoga_01", "a_m_m_acult_01",
		"a_m_m_afriamer_01", "a_m_m_beach_01", "a_m_m_beach_02", "a_m_m_bevhills_01", "a_m_m_bevhills_02", "a_m_m_business_01", "a_m_m_eastsa_01", "a_m_m_eastsa_02", "a_m_m_farmer_01", "a_m_m_fatlatin_01",
		"a_m_m_genfat_01", "a_m_m_genfat_02", "a_m_m_golfer_01", "a_m_m_hasjew_01", "a_m_m_hillbilly_01", "a_m_m_hillbilly_02", "a_m_m_indian_01", "a_m_m_ktown_01", "a_m_m_malibu_01", "a_m_m_mexcntry_01",
		"a_m_m_mexlabor_01", "a_m_m_og_boss_01", "a_m_m_paparazzi_01", "a_m_m_polynesian_01", "a_m_m_prolhost_01", "a_m_m_rurmeth_01", "a_m_m_salton_01", "a_m_m_salton_02", "a_m_m_salton_03", "a_m_m_salton_04",
		"a_m_m_skater_01", "a_m_m_skidrow_01", "a_m_m_socenlat_01", "a_m_m_soucent_01", "a_m_m_soucent_02", "a_m_m_soucent_03", "a_m_m_soucent_04", "a_m_m_stlat_02", "a_m_m_tennis_01", "a_m_m_tourist_01",
		"a_m_m_trampbeac_01", "a_m_m_tramp_01", "a_m_m_tranvest_01", "a_m_m_tranvest_02", "a_m_o_acult_01", "a_m_o_acult_02", "a_m_o_beach_01", "a_m_o_genstreet_01", "a_m_o_ktown_01", "a_m_o_salton_01",
		"a_m_o_soucent_01", "a_m_o_soucent_02", "a_m_o_soucent_03", "a_m_o_tramp_01", "a_m_y_acult_01", "a_m_y_acult_02", "a_m_y_beachvesp_01", "a_m_y_beachvesp_02", "a_m_y_beach_01", "a_m_y_beach_02",
		"a_m_y_beach_03", "a_m_y_bevhills_01", "a_m_y_bevhills_02", "a_m_y_breakdance_01", "a_m_y_busicas_01", "a_m_y_business_01", "a_m_y_business_02", "a_m_y_business_03", "a_m_y_cyclist_01", "a_m_y_dhill_01",
		"a_m_y_downtown_01", "a_m_y_eastsa_01", "a_m_y_eastsa_02", "a_m_y_epsilon_01", "a_m_y_epsilon_02", "a_m_y_gay_01", "a_m_y_gay_02", "a_m_y_genstreet_01", "a_m_y_genstreet_02", "a_m_y_golfer_01",
		"a_m_y_hasjew_01", "a_m_y_hiker_01", "a_m_y_hippy_01", "a_m_y_hipster_01", "a_m_y_hipster_02", "a_m_y_hipster_03", "a_m_y_indian_01", "a_m_y_jetski_01", "a_m_y_juggalo_01", "a_m_y_ktown_01",
		"a_m_y_ktown_02", "a_m_y_latino_01", "a_m_y_methhead_01", "a_m_y_mexthug_01", "a_m_y_motox_01", "a_m_y_motox_02", "a_m_y_musclbeac_01", "a_m_y_musclbeac_02", "a_m_y_polynesian_01", "a_m_y_roadcyc_01",
		"a_m_y_runner_01", "a_m_y_runner_02", "a_m_y_salton_01", "a_m_y_skater_01", "a_m_y_skater_02", "a_m_y_soucent_01", "a_m_y_soucent_02", "a_m_y_soucent_03", "a_m_y_soucent_04", "a_m_y_stbla_01",
		"a_m_y_stbla_02", "a_m_y_stlat_01", "a_m_y_stwhi_01", "a_m_y_stwhi_02", "a_m_y_sunbathe_01", "a_m_y_surfer_01", "a_m_y_vindouche_01", "a_m_y_vinewood_01", "a_m_y_vinewood_02", "a_m_y_vinewood_03",
		"a_m_y_vinewood_04", "a_m_y_yoga_01", "u_m_y_proldriver_01", "u_m_y_rsranger_01", "u_m_y_sbike", "u_m_y_staggrm_01", "u_m_y_tattoo_01", "csb_abigail", "csb_anita", "csb_anton",
		"csb_ballasog", "csb_bride", "csb_burgerdrug", "csb_car3guy1", "csb_car3guy2", "csb_chef", "csb_chin_goon", "csb_cletus", "csb_cop", "csb_customer",
		"csb_denise_friend", "csb_fos_rep", "csb_g", "csb_groom", "csb_grove_str_dlr", "csb_hao", "csb_hugh", "csb_imran", "csb_janitor", "csb_maude",
		"csb_mweather", "csb_ortega", "csb_oscar", "csb_porndudes", "csb_porndudes_p", "csb_prologuedriver", "csb_prolsec", "csb_ramp_gang", "csb_ramp_hic", "csb_ramp_hipster",
		"csb_ramp_marine", "csb_ramp_mex", "csb_reporter", "csb_roccopelosi", "csb_screen_writer", "csb_stripper_01", "csb_stripper_02", "csb_tonya", "csb_trafficwarden", "cs_amandatownley",
		"cs_andreas", "cs_ashley", "cs_bankman", "cs_barry", "cs_barry_p", "cs_beverly", "cs_beverly_p", "cs_brad", "cs_bradcadaver", "cs_carbuyer",
		"cs_casey", "cs_chengsr", "cs_chrisformage", "cs_clay", "cs_dale", "cs_davenorton", "cs_debra", "cs_denise", "cs_devin", "cs_dom",
		"cs_dreyfuss", "cs_drfriedlander", "cs_fabien", "cs_fbisuit_01", "cs_floyd", "cs_guadalope", "cs_gurk", "cs_hunter", "cs_janet", "cs_jewelass",
		"cs_jimmyboston", "cs_jimmydisanto", "cs_joeminuteman", "cs_johnnyklebitz", "cs_josef", "cs_josh", "cs_lamardavis", "cs_lazlow", "cs_lestercrest", "cs_lifeinvad_01",
		"cs_magenta", "cs_manuel", "cs_marnie", "cs_martinmadrazo", "cs_maryann", "cs_michelle", "cs_milton", "cs_molly", "cs_movpremf_01", "cs_movpremmale",
		"cs_mrk", "cs_mrsphillips", "cs_mrs_thornhill", "cs_natalia", "cs_nervousron", "cs_nigel", "cs_old_man1a", "cs_old_man2", "cs_omega", "cs_orleans",
		"cs_paper", "cs_paper_p", "cs_patricia", "cs_priest", "cs_prolsec_02", "cs_russiandrunk", "cs_siemonyetarian", "cs_solomon", "cs_stevehains", "cs_stretch",
		"cs_tanisha", "cs_taocheng", "cs_taostranslator", "cs_tenniscoach", "cs_terry", "cs_tom", "cs_tomepsilon", "cs_tracydisanto", "cs_wade", "cs_zimbor",
		"g_f_y_ballas_01", "g_f_y_families_01", "g_f_y_lost_01", "g_f_y_vagos_01", "g_m_m_armboss_01", "g_m_m_armgoon_01", "g_m_m_armlieut_01", "g_m_m_chemwork_01", "g_m_m_chemwork_01_p", "g_m_m_chiboss_01",
		"g_m_m_chiboss_01_p", "g_m_m_chicold_01", "g_m_m_chicold_01_p", "g_m_m_chigoon_01", "g_m_m_chigoon_01_p", "g_m_m_chigoon_02", "g_m_m_korboss_01", "g_m_m_mexboss_01", "g_m_m_mexboss_02", "g_m_y_armgoon_02",
		"g_m_y_azteca_01", "g_m_y_ballaeast_01", "g_m_y_ballaorig_01", "g_m_y_ballasout_01", "g_m_y_famca_01", "g_m_y_famdnf_01", "g_m_y_famfor_01", "g_m_y_korean_01", "g_m_y_korean_02", "g_m_y_korlieut_01",
		"g_m_y_lost_01", "g_m_y_lost_02", "g_m_y_lost_03", "g_m_y_mexgang_01", "g_m_y_mexgoon_01", "g_m_y_mexgoon_02", "g_m_y_mexgoon_03", "g_m_y_mexgoon_03_p", "g_m_y_pologoon_01", "g_m_y_pologoon_01_p",
		"g_m_y_pologoon_02", "g_m_y_pologoon_02_p", "g_m_y_salvaboss_01", "g_m_y_salvagoon_01", "g_m_y_salvagoon_02", "g_m_y_salvagoon_03", "g_m_y_salvagoon_03_p", "g_m_y_strpunk_01", "g_m_y_strpunk_02", "hc_driver",
		"hc_gunman", "hc_hacker", "ig_abigail", "ig_amandatownley", "ig_andreas", "ig_ashley", "ig_ballasog", "ig_bankman", "ig_barry", "ig_barry_p",
		"ig_bestmen", "ig_beverly", "ig_beverly_p", "ig_brad", "ig_bride", "ig_car3guy1", "ig_car3guy2", "ig_casey", "ig_chef", "ig_chengsr",
		"ig_chrisformage", "ig_clay", "ig_claypain", "ig_cletus", "ig_dale", "ig_davenorton", "ig_denise", "ig_devin", "ig_dom", "ig_dreyfuss",
		"ig_drfriedlander", "ig_fabien", "ig_fbisuit_01", "ig_floyd", "ig_groom", "ig_hao", "ig_hunter", "ig_janet", "ig_jay_norris", "ig_jewelass",
		"ig_jimmyboston", "ig_jimmydisanto", "ig_joeminuteman", "ig_johnnyklebitz", "ig_josef", "ig_josh", "ig_kerrymcintosh", "ig_lamardavis", "ig_lazlow", "ig_lestercrest",
		"ig_lifeinvad_01", "ig_lifeinvad_02", "ig_magenta", "ig_manuel", "ig_marnie", "ig_maryann", "ig_maude", "ig_michelle", "ig_milton", "ig_molly",
		"ig_mrk", "ig_mrsphillips", "ig_mrs_thornhill", "ig_natalia", "ig_nervousron", "ig_nigel", "ig_old_man1a", "ig_old_man2", "ig_omega", "ig_oneil",
		"ig_orleans", "ig_ortega", "ig_paper", "ig_patricia", "ig_priest", "ig_prolsec_02", "ig_ramp_gang", "ig_ramp_hic", "ig_ramp_hipster", "ig_ramp_mex",
		"ig_roccopelosi", "ig_russiandrunk", "ig_screen_writer", "ig_siemonyetarian", "ig_solomon", "ig_stevehains", "ig_stretch", "ig_talina", "ig_tanisha", "ig_taocheng",
		"ig_taostranslator", "ig_taostranslator_p", "ig_tenniscoach", "ig_terry", "ig_tomepsilon", "ig_tonya", "ig_tracydisanto", "ig_trafficwarden", "ig_tylerdix", "ig_wade",
		"ig_zimbor", "mp_f_deadhooker", "mp_f_freemode_01", "mp_f_misty_01", "mp_f_stripperlite", "mp_g_m_pros_01", "mp_headtargets", "mp_m_claude_01", "mp_m_exarmy_01", "mp_m_famdd_01",
		"mp_m_fibsec_01", "mp_m_freemode_01", "mp_m_marston_01", "mp_m_niko_01", "mp_m_shopkeep_01", "mp_s_m_armoured_01", "", "", "", "",
		"", "s_f_m_fembarber", "s_f_m_maid_01", "s_f_m_shop_high", "s_f_m_sweatshop_01", "s_f_y_airhostess_01", "s_f_y_bartender_01", "s_f_y_baywatch_01", "s_f_y_cop_01", "s_f_y_factory_01",
		"s_f_y_hooker_01", "s_f_y_hooker_02", "s_f_y_hooker_03", "s_f_y_migrant_01", "s_f_y_movprem_01", "s_f_y_ranger_01", "s_f_y_scrubs_01", "s_f_y_sheriff_01", "s_f_y_shop_low", "s_f_y_shop_mid",
		"s_f_y_stripperlite", "s_f_y_stripper_01", "s_f_y_stripper_02", "s_f_y_sweatshop_01", "s_m_m_ammucountry", "s_m_m_armoured_01", "s_m_m_armoured_02", "s_m_m_autoshop_01", "s_m_m_autoshop_02", "s_m_m_bouncer_01",
		"s_m_m_chemsec_01", "s_m_m_ciasec_01", "s_m_m_cntrybar_01", "s_m_m_dockwork_01", "s_m_m_doctor_01", "s_m_m_fiboffice_01", "s_m_m_fiboffice_02", "s_m_m_gaffer_01", "s_m_m_gardener_01", "s_m_m_gentransport",
		"s_m_m_hairdress_01", "s_m_m_highsec_01", "s_m_m_highsec_02", "s_m_m_janitor", "s_m_m_lathandy_01", "s_m_m_lifeinvad_01", "s_m_m_linecook", "s_m_m_lsmetro_01", "s_m_m_mariachi_01", "s_m_m_marine_01",
		"s_m_m_marine_02", "s_m_m_migrant_01", "u_m_y_zombie_01", "s_m_m_movprem_01", "s_m_m_movspace_01", "s_m_m_paramedic_01", "s_m_m_pilot_01", "s_m_m_pilot_02", "s_m_m_postal_01", "s_m_m_postal_02",
		"s_m_m_prisguard_01", "s_m_m_scientist_01", "s_m_m_security_01", "s_m_m_snowcop_01", "s_m_m_strperf_01", "s_m_m_strpreach_01", "s_m_m_strvend_01", "s_m_m_trucker_01", "s_m_m_ups_01", "s_m_m_ups_02",
		"s_m_o_busker_01", "s_m_y_airworker", "s_m_y_ammucity_01", "s_m_y_armymech_01", "s_m_y_autopsy_01", "s_m_y_barman_01", "s_m_y_baywatch_01", "s_m_y_blackops_01", "s_m_y_blackops_02", "s_m_y_busboy_01",
		"s_m_y_chef_01", "s_m_y_clown_01", "s_m_y_construct_01", "s_m_y_construct_02", "s_m_y_cop_01", "s_m_y_dealer_01", "s_m_y_devinsec_01", "s_m_y_dockwork_01", "s_m_y_doorman_01", "s_m_y_dwservice_01",
		"s_m_y_dwservice_02", "s_m_y_factory_01", "s_m_y_fireman_01", "s_m_y_garbage", "s_m_y_grip_01", "s_m_y_hwaycop_01", "s_m_y_marine_01", "s_m_y_marine_02", "s_m_y_marine_03", "s_m_y_mime",
		"s_m_y_pestcont_01", "s_m_y_pilot_01", "s_m_y_prismuscl_01", "s_m_y_prisoner_01", "s_m_y_ranger_01", "s_m_y_robber_01", "s_m_y_sheriff_01", "s_m_y_shop_mask", "s_m_y_strvend_01", "s_m_y_swat_01",
		"s_m_y_uscg_01", "s_m_y_valet_01", "s_m_y_waiter_01", "s_m_y_winclean_01", "s_m_y_xmech_01", "s_m_y_xmech_02", "u_f_m_corpse_01", "u_f_m_miranda", "u_f_m_promourn_01", "u_f_o_moviestar",
		"u_f_o_prolhost_01", "u_f_y_bikerchic", "u_f_y_comjane", "u_f_y_corpse_01", "u_f_y_corpse_02", "u_f_y_hotposh_01", "u_f_y_jewelass_01", "u_f_y_mistress", "u_f_y_poppymich", "u_f_y_princess",
		"u_f_y_spyactress", "u_m_m_aldinapoli", "u_m_m_bankman", "u_m_m_bikehire_01", "u_m_m_fibarchitect", "u_m_m_filmdirector", "u_m_m_glenstank_01", "u_m_m_griff_01", "u_m_m_jesus_01", "u_m_m_jewelsec_01",
		"u_m_m_jewelthief", "u_m_m_markfost", "u_m_m_partytarget", "u_m_m_prolsec_01", "u_m_m_promourn_01", "u_m_m_rivalpap", "u_m_m_spyactor", "u_m_m_willyfist", "u_m_o_finguru_01", "u_m_o_taphillbilly",
		"u_m_o_tramp_01", "u_m_y_abner", "u_m_y_antonb", "u_m_y_babyd", "u_m_y_baygor", "u_m_y_burgerdrug_01", "u_m_y_chip", "u_m_y_cyclist_01", "u_m_y_fibmugger_01", "u_m_y_guido_01",
		"u_m_y_gunvend_01", "u_m_y_hippie_01", "u_m_y_imporage", "u_m_y_justin", "u_m_y_mani", "u_m_y_militarybum", "u_m_y_paparazzi", "u_m_y_party_01", "u_m_y_pogo_01", "u_m_y_prisoner_01",
		"ig_benny", "ig_g", "ig_vagspeak", "mp_m_g_vagfun_01", "mp_m_boatstaff_01", "mp_f_boatstaff_01"
	}};

	const std::array<const char *, 696> characters_desc {{
		// These data from ScriptHookV/NativeTrainer
		"MICHAEL", "FRANKLIN", "TREVOR", "BOAR", "CHIMP", "COW", "COYOTE", "DEER", "FISH", "HEN",
		"CAT", "HAWK", "CORMORANT", "CROW", "DOLPHIN", "HUMPBACK", "WHALE", "PIGEON", "SEAGULL", "SHARKHAMMER" ,
		"PIG", "RAT", "RHESUS", "CHOP", "HUSKY", "MTLION", "RETRIEVER", "SHARKTIGER", "SHEPHERD", "ALIEN",
		"BEACH", "BEVHILLS", "BEVHILLS", "BODYBUILD", "BUSINESS", "DOWNTOWN", "EASTSA", "EASTSA", "FATBLA", "FATCULT",
		"FATWHITE", "KTOWN", "KTOWN", "PROLHOST", "SALTON", "SKIDROW", "SOUCENTMC", "SOUCENT", "SOUCENT", "TOURIST",
		"TRAMPBEAC", "TRAMP", "GENSTREET", "INDIAN", "KTOWN", "SALTON", "SOUCENT", "SOUCENT", "BEACH", "BEVHILLS",
		"BEVHILLS", "BEVHILLS", "BEVHILLS", "BUSINESS", "BUSINESS", "BUSINESS", "BUSINESS", "EASTSA", "EASTSA", "EASTSA",
		"EPSILON", "FITNESS", "FITNESS", "GENHOT", "GOLFER", "HIKER", "HIPPIE", "HIPSTER", "HIPSTER", "HIPSTER",
		"HIPSTER", "INDIAN", "JUGGALO", "RUNNER", "RURMETH", "SCDRESSY", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT",
		"TENNIS", "TOPLESS", "TOURIST", "TOURIST", "VINEWOOD", "VINEWOOD", "VINEWOOD", "VINEWOOD", "YOGA", "ACULT",
		"AFRIAMER", "BEACH", "BEACH", "BEVHILLS", "BEVHILLS", "BUSINESS", "EASTSA", "EASTSA", "FARMER", "FATLATIN",
		"GENFAT", "GENFAT", "GOLFER", "HASJEW", "HILLBILLY", "HILLBILLY", "INDIAN", "KTOWN", "MALIBU", "MEXCNTRY",
		"MEXLABOR", "OG_BOSS", "PAPARAZZI", "POLYNESIAN", "PROLHOST", "RURMETH", "SALTON", "SALTON", "SALTON", "SALTON",
		"SKATER", "SKIDROW", "SOCENLAT", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STLAT", "TENNIS", "TOURIST",
		"TRAMPBEAC", "TRAMP", "TRANVEST", "TRANVEST", "ACULT", "ACULT", "BEACH", "GENSTREET", "KTOWN", "SALTON",
		"SOUCENT", "SOUCENT", "SOUCENT", "TRAMP", "ACULT", "ACULT", "BEACHVESP", "BEACHVESP", "BEACH", "BEACH",
		"BEACH", "BEVHILLS", "BEVHILLS", "BREAKDANCE", "BUSICAS", "BUSINESS", "BUSINESS", "BUSINESS", "CYCLIST", "DHILL",
		"DOWNTOWN", "EASTSA", "EASTSA", "EPSILON", "EPSILON", "GAY", "GAY", "GENSTREET", "GENSTREET", "GOLFER",
		"HASJEW", "HIKER", "HIPPY", "HIPSTER", "HIPSTER", "HIPSTER", "INDIAN", "JETSKI", "JUGGALO", "KTOWN",
		"KTOWN", "LATINO", "METHHEAD", "MEXTHUG", "MOTOX", "MOTOX", "MUSCLBEAC", "MUSCLBEAC", "POLYNESIAN", "ROADCYC",
		"RUNNER", "RUNNER", "SALTON", "SKATER", "SKATER", "SOUCENT", "SOUCENT", "SOUCENT", "SOUCENT", "STBLA",
		"STBLA", "STLAT", "STWHI", "STWHI", "SUNBATHE", "SURFER", "VINDOUCHE", "VINEWOOD", "VINEWOOD", "VINEWOOD",
		"VINEWOOD", "YOGA", "PROLDRIVER", "RSRANGER", "SBIKE", "STAGGRM", "TATTOO", "ABIGAIL", "ANITA", "ANTON",
		"BALLASOG", "BRIDE", "BURGERDRUG", "CAR3GUY1", "CAR3GUY2", "CHEF", "CHIN_GOON", "CLETUS", "COP", "CUSTOMER",
		"DENISE_FRIEND", "FOS_REP", "G", "GROOM", "DLR", "HAO", "HUGH", "IMRAN", "JANITOR", "MAUDE",
		"MWEATHER", "ORTEGA", "OSCAR", "PORNDUDES", "PORNDUDES_P", "PROLOGUEDRIVER", "PROLSEC", "GANG", "HIC", "HIPSTER",
		"MARINE", "MEX", "REPORTER", "ROCCOPELOSI", "SCREEN_WRITER", "STRIPPER", "STRIPPER", "TONYA", "TRAFFICWARDEN", "AMANDATOWNLEY",
		"ANDREAS", "ASHLEY", "BANKMAN", "BARRY", "BARRY_P", "BEVERLY", "BEVERLY_P", "BRAD", "BRADCADAVER", "CARBUYER",
		"CASEY", "CHENGSR", "CHRISFORMAGE", "CLAY", "DALE", "DAVENORTON", "DEBRA", "DENISE", "DEVIN", "DOM",
		"DREYFUSS", "DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GUADALOPE", "GURK", "HUNTER", "JANET", "JEWELASS",
		"JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST", "LIFEINVAD",
		"MAGENTA", "MANUEL", "MARNIE", "MARTINMADRAZO", "MARYANN", "MICHELLE", "MILTON", "MOLLY", "MOVPREMF", "MOVPREMMALE",
		"MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ORLEANS",
		"PAPER", "PAPER_P", "PATRICIA", "PRIEST", "PROLSEC", "RUSSIANDRUNK", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH",
		"TANISHA", "TAOCHENG", "TAOSTRANSLATOR", "TENNISCOACH", "TERRY", "TOM", "TOMEPSILON", "TRACYDISANTO", "WADE", "ZIMBOR",
		"BALLAS", "FAMILIES", "LOST", "VAGOS", "ARMBOSS", "ARMGOON", "ARMLIEUT", "CHEMWORK", "CHEMWORK_P", "CHIBOSS",
		"CHIBOSS_P", "CHICOLD", "CHICOLD_P", "CHIGOON", "CHIGOON_P", "CHIGOON", "KORBOSS", "MEXBOSS", "MEXBOSS", "ARMGOON",
		"AZTECA", "BALLAEAST", "BALLAORIG", "BALLASOUT", "FAMCA", "FAMDNF", "FAMFOR", "KOREAN", "KOREAN", "KORLIEUT",
		"LOST", "LOST", "LOST", "MEXGANG", "MEXGOON", "MEXGOON", "MEXGOON", "MEXGOON_P", "POLOGOON", "POLOGOON_P",
		"POLOGOON", "POLOGOON_P", "SALVABOSS", "SALVAGOON", "SALVAGOON", "SALVAGOON", "SALVAGOON_P", "STRPUNK", "STRPUNK", "HC_DRIVER",
		"HC_GUNMAN", "HC_HACKER", "ABIGAIL", "AMANDATOWNLEY", "ANDREAS", "ASHLEY", "BALLASOG", "BANKMAN", "BARRY", "BARRY_P",
		"BESTMEN", "BEVERLY", "BEVERLY_P", "BRAD", "BRIDE", "CAR3GUY1", "CAR3GUY2", "CASEY", "CHEF", "CHENGSR",
		"CHRISFORMAGE", "CLAY", "CLAYPAIN", "CLETUS", "DALE", "DAVENORTON", "DENISE", "DEVIN", "DOM", "DREYFUSS",
		"DRFRIEDLANDER", "FABIEN", "FBISUIT", "FLOYD", "GROOM", "HAO", "HUNTER", "JANET", "JAY_NORRIS", "JEWELASS",
		"JIMMYBOSTON", "JIMMYDISANTO", "JOEMINUTEMAN", "JOHNNYKLEBITZ", "JOSEF", "JOSH", "KERRYMCINTOSH", "LAMARDAVIS", "LAZLOW", "LESTERCREST",
		"LIFEINVAD", "LIFEINVAD", "MAGENTA", "MANUEL", "MARNIE", "MARYANN", "MAUDE", "MICHELLE", "MILTON", "MOLLY",
		"MRK", "MRSPHILLIPS", "MRS_THORNHILL", "NATALIA", "NERVOUSRON", "NIGEL", "OLD_MAN1A", "OLD_MAN2", "OMEGA", "ONEIL",
		"ORLEANS", "ORTEGA", "PAPER", "PATRICIA", "PRIEST", "PROLSEC", "GANG", "HIC", "HIPSTER", "MEX",
		"ROCCOPELOSI", "RUSSIANDRUNK", "SCREEN_WRITER", "SIEMONYETARIAN", "SOLOMON", "STEVEHAINS", "STRETCH", "TALINA", "TANISHA", "TAOCHENG",
		"TAOSTRANSLATOR", "TAOSTRANSLATOR_P", "TENNISCOACH", "TERRY", "TOMEPSILON", "TONYA", "TRACYDISANTO", "TRAFFICWARDEN", "TYLERDIX", "WADE",
		"ZIMBOR", "DEADHOOKER", "FREEMODE", "MISTY", "STRIPPERLITE", "PROS", "MP_HEADTARGETS", "CLAUDE", "EXARMY", "FAMDD",
		"FIBSEC", "FREEMODE", "MARSTON", "NIKO", "SHOPKEEP", "ARMOURED", "NONE", "NONE", "NONE", "NONE",
		"NONE", "FEMBARBER", "MAID", "SHOP_HIGH", "SWEATSHOP", "AIRHOSTESS", "BARTENDER", "BAYWATCH", "COP", "FACTORY",
		"HOOKER", "HOOKER", "HOOKER", "MIGRANT", "MOVPREM", "RANGER", "SCRUBS", "SHERIFF", "SHOP_LOW", "SHOP_MID",
		"STRIPPERLITE", "STRIPPER", "STRIPPER", "SWEATSHOP", "AMMUCOUNTRY", "ARMOURED", "ARMOURED", "AUTOSHOP", "AUTOSHOP", "BOUNCER",
		"CHEMSEC", "CIASEC", "CNTRYBAR", "DOCKWORK", "DOCTOR", "FIBOFFICE", "FIBOFFICE", "GAFFER", "GARDENER", "GENTRANSPORT",
		"HAIRDRESS", "HIGHSEC", "HIGHSEC", "JANITOR", "LATHANDY", "LIFEINVAD", "LINECOOK", "LSMETRO", "MARIACHI", "MARINE",
		"MARINE", "MIGRANT", "ZOMBIE", "MOVPREM", "MOVSPACE", "PARAMEDIC", "PILOT", "PILOT", "POSTAL", "POSTAL",
		"PRISGUARD", "SCIENTIST", "SECURITY", "SNOWCOP", "STRPERF", "STRPREACH", "STRVEND", "TRUCKER", "UPS", "UPS",
		"BUSKER", "AIRWORKER", "AMMUCITY", "ARMYMECH", "AUTOPSY", "BARMAN", "BAYWATCH", "BLACKOPS", "BLACKOPS", "BUSBOY",
		"CHEF", "CLOWN", "CONSTRUCT", "CONSTRUCT", "COP", "DEALER", "DEVINSEC", "DOCKWORK", "DOORMAN", "DWSERVICE",
		"DWSERVICE", "FACTORY", "FIREMAN", "GARBAGE", "GRIP", "HWAYCOP", "MARINE", "MARINE", "MARINE", "MIME",
		"PESTCONT", "PILOT", "PRISMUSCL", "PRISONER", "RANGER", "ROBBER", "SHERIFF", "SHOP_MASK", "STRVEND", "SWAT",
		"USCG", "VALET", "WAITER", "WINCLEAN", "XMECH", "XMECH", "CORPSE", "MIRANDA", "PROMOURN", "MOVIESTAR",
		"PROLHOST", "BIKERCHIC", "COMJANE", "CORPSE", "CORPSE", "HOTPOSH", "JEWELASS", "MISTRESS", "POPPYMICH", "PRINCESS",
		"SPYACTRESS", "ALDINAPOLI", "BANKMAN", "BIKEHIRE", "FIBARCHITECT", "FILMDIRECTOR", "GLENSTANK", "GRIFF", "JESUS", "JEWELSEC",
		"JEWELTHIEF", "MARKFOST", "PARTYTARGET", "PROLSEC", "PROMOURN", "RIVALPAP", "SPYACTOR", "WILLYFIST", "FINGURU", "TAPHILLBILLY",
		"TRAMP", "ABNER", "ANTONB", "BABYD", "BAYGOR", "BURGERDRUG", "CHIP", "CYCLIST", "FIBMUGGER", "GUIDO",
		"GUNVEND", "HIPPIE", "IMPORAGE", "JUSTIN", "MANI", "MILITARYBUM", "PAPARAZZI", "PARTY", "POGO", "PRISONER",
		"BENNY", "G", "VAGSPEAK", "VAGFUN", "BOATSTAFF", "FEMBOATSTAFF"
	}};

	struct _chr_data {
		entity fk_chute = 0;
		character::motion_state_t lst_mds = character::motion_state_t::null;
		bool going = false, aiming = false, shooting = false;
		float go_speed; vector3 go_dest;
		vector3 focus{0, 0, 0};
	};

	std::unordered_map<int, _chr_data> _chr_data_map;

	initer _chr_data_initer([]() {
		if (_chr_data_map.size()) {
			_chr_data_map.clear();
		}
	});

	void character::del() {
		gc::undelegate(*this);
		_chr_data_map.erase(_h);
		ntv::PED::DELETE_PED(&_h);
	}

	void character::free() {
		gc::undelegate(*this);
		_chr_data_map.erase(_h);
		ntv::ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&_h);
	}

	static bool _is_new_mds(int h, character::motion_state_t now) {
		auto &data = _chr_data_map[h];

		if (data.lst_mds == now) {
			return false;
		}

		switch (data.lst_mds) {
			case character::motion_state_t::walking:
			case character::motion_state_t::runing:
			case character::motion_state_t::sprinting:
				data.going = false;
				break;
			case character::motion_state_t::climbing_ladder:
			case character::motion_state_t::covering:
			case character::motion_state_t::paralysing:
				ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(h);
				break;
			case character::motion_state_t::parachuting:
				if (data.fk_chute) {
					data.fk_chute.del();
					data.fk_chute = 0;
				} else {
					ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(h);
				}
				break;
			default:
				break;
		}

		data.lst_mds = now;
		return true;
	}

	void character::stop_motion_command() {
		_is_new_mds(_h, character::motion_state_t::null);
		auto &data = _chr_data_map[_h];
		if (data.aiming) {
			data.aiming = false;
		}
		if (data.shooting) {
			data.shooting = false;
		}
		ntv::AI::CLEAR_PED_TASKS_IMMEDIATELY(_h);
	}

	void character::still() {
		if (!_is_new_mds(_h, character::motion_state_t::still)) {
			return;
		}
		ntv::AI::TASK_STAND_STILL(_h, -1);
	}

	void character::jump() {
		if (!_is_new_mds(_h, character::motion_state_t::jumping)) {
			return;
		}
		ntv::AI::TASK_JUMP(_h, false, false, false);
	}

	void character::climb() {
		_is_new_mds(_h, character::motion_state_t::climbing);
		ntv::AI::TASK_CLIMB(_h, false);
	}

	void character::climb_ladder() {
		if (!_is_new_mds(_h, character::motion_state_t::climbing_ladder)) {
			return;
		}
		ntv::AI::TASK_CLIMB_LADDER(_h, 0);
	}

	void character::cover() {
		if (!_is_new_mds(_h, character::motion_state_t::covering)) {
			return;
		}
		ntv::AI::TASK_STAY_IN_COVER(_h);
	}

	void character::paralysis() {
		if (!_is_new_mds(_h, character::motion_state_t::paralysing)) {
			return;
		}
		ntv::PED::SET_PED_TO_RAGDOLL(_h, -1, -1, 0, false, false, false);
	}

	void character::skydive() {
		if (!_is_new_mds(_h, character::motion_state_t::skydiving)) {
			return;
		}
		ntv::AI::TASK_SKY_DIVE(_h);
	}

	void character::go_to(const vector3 &dest, float speed) {
		auto &data = _chr_data_map[_h];

		if (data.going) {
			bool is_new;
			if (speed < character::speed_run) {
				is_new = _is_new_mds(_h, character::motion_state_t::walking);
			} else if (speed < character::speed_sprint) {
				is_new = _is_new_mds(_h, character::motion_state_t::runing);
			} else {
				is_new = _is_new_mds(_h, character::motion_state_t::sprinting);
			}
			if (
				!is_new &&
				speed == data.go_speed &&
				dest.x == data.go_dest.x && dest.y == data.go_dest.y && dest.z == data.go_dest.z
				) {
				return;
			}
		} else {
			data.going = true;
		}

		data.go_speed = speed;
		data.go_dest = dest;

		if (data.shooting) {
			return;
		}
		if (data.aiming) {
			aim();
			return;
		}
		ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
			_h,
			dest.x, dest.y, dest.z,
			speed,
			-1, 0, 0
		);
	}

	void character::look() {
		/*auto &data = _chr_data_map[_h];
		data.focus = coords;
		if (data.shooting) {
			shoot();
			return;
		}
		if (data.aiming) {
			aim();
			return;
		}
		ntv::AI::TASK_LOOK_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, -1, 0, 2);*/
	}

	void character::focus(const vector3 &coords) {
		_chr_data_map[_h].focus = coords;
	}

	void character::aim(bool toggle) {
		auto &data = _chr_data_map[_h];

		if (toggle) {
			data.aiming = true;
			if (data.shooting) {
				shoot();
				return;
			}
			if (is_in_vehicle()) {
				auto wpn_grp = arm::weapon_group(current_weapon());
				if (!wpn_grp || wpn_grp == "GROUP_UNARMED") {
					ntv::AI::TASK_VEHICLE_AIM_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z);
				}
				return;
			}
			if (data.going) {
				ntv::AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_COORD(
					_h,
					data.go_dest.x, data.go_dest.y, data.go_dest.z,
					data.focus.x, data.focus.y, data.focus.z,
					data.go_speed,
					false, 2.0f, 0.5f, true, 0, 0,
					hash("FIRING_PATTERN_FULL_AUTO")
				);
				return;
			}
			ntv::AI::TASK_AIM_GUN_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, -1, false, false);
		} else if (data.aiming) {
			data.aiming = false;
			if (data.shooting) {
				return;
			}
			if (data.going) {
				ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
					_h,
					data.go_dest.x, data.go_dest.y, data.go_dest.z,
					data.go_speed,
					-1, 0, 0
				);
				return;
			}
			ntv::AI::CLEAR_PED_TASKS(_h);
		}
	}

	void character::shoot(bool toggle) {
		auto &data = _chr_data_map[_h];

		if (toggle) {
			data.shooting = true;
			if (is_in_vehicle()) {
				/*if (!arm::weapon_group(current_weapon())) {
					ntv::VEHICLE::SET_VEHICLE_SHOOT_AT_TARGET(_h, ntv::PED::GET_VEHICLE_PED_IS_IN(_h, false), coords.x, coords.y, coords.z);
					return;
				}*/
				ntv::AI::TASK_VEHICLE_SHOOT_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, 1.0f);
				return;
			}
			ntv::AI::TASK_SHOOT_AT_COORD(_h, data.focus.x, data.focus.y, data.focus.z, -1, hash("FIRING_PATTERN_FULL_AUTO"));
		} else if (data.shooting) {
			data.shooting = false;
			if (data.aiming) {
				aim();
				return;
			}
			if (data.going) {
				ntv::AI::TASK_GO_STRAIGHT_TO_COORD(
					_h,
					data.go_dest.x, data.go_dest.y, data.go_dest.z,
					data.go_speed,
					-1, 0, 0
				);
				return;
			}
			ntv::AI::CLEAR_PED_TASKS(_h);
		}
	}

	void character::shoot_once() {
		/*vector3 dest;

		auto &data = _chr_data_map[_h];
		if (data.aiming) {
			dest = data.focus;
		} else {
			dest = pos({0, 1000, 0});
		}

		auto h = current_weapon().hash();

		if (!ntv::WEAPON::HAS_WEAPON_ASSET_LOADED(h)) {
			ntv::WEAPON::REQUEST_WEAPON_ASSET(h, 31, 0);
			sleep([h]()->bool {
				return ntv::STREAMING::HAS_MODEL_LOADED(h);
			});
		}

		auto chr_pos = pos();

		ntv::GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(
			chr_pos.x, chr_pos.y, chr_pos.z,
			dest.x, dest.y, dest.z, 0, false, h,
			_h, true, false, 1000.0f
		);*/
	}

	void character::open_parachute() {
		if (!_is_new_mds(_h, character::motion_state_t::parachuting)) {
			return;
		}
		add_parachute_pack();
		ntv::PED::FORCE_PED_TO_OPEN_PARACHUTE(_h);
	}

	void character::open_fake_parachute() {
		if (!_is_new_mds(_h, character::motion_state_t::parachuting)) {
			return;
		}
		auto &data = _chr_data_map[_h];
		if (data.fk_chute) {
			return;
		}
		auto cods = pos({0, 0, 2});
		data.fk_chute = entity(0x73268708, cods);
		ntv::ENTITY::SET_ENTITY_COLLISION(data.fk_chute, false, false);
		ntv::ENTITY::ATTACH_ENTITY_TO_ENTITY(
			data.fk_chute, _h,
			nob::ntv::PED::GET_PED_BONE_INDEX(_h, 0xE0FD),
			3.6, 0, 0, 0, 90.0f, 0, false, false, false, true, 0, true
		);
		ntv::AI::TASK_STAND_STILL(_h, -1);
	}

	void character::movement(const movement_t &mm) {
		entity::movement(mm);

		switch (mm.motion_state) {
			case motion_state_t::still:
				still();
				break;
			case motion_state_t::jumping:
				jump();
				break;
			case motion_state_t::walking:
				go(speed_walk);
				break;
			case motion_state_t::runing:
				go(speed_run);
				break;
			case motion_state_t::sprinting:
				go(speed_sprint);
				break;
			case motion_state_t::skydiving:
				skydive();
				break;
			case motion_state_t::climbing:
				climb();
				break;
			case motion_state_t::climbing_ladder:
				climb_ladder();
				break;
			case motion_state_t::parachuting:
				open_fake_parachute();
				break;
			case motion_state_t::covering:
				cover();
				break;
			default:
				break;
		}
	}
} /* nob */
