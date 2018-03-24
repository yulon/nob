#include <nob.hpp>

#include <rua/hook.hpp>
#include <rua/observer.hpp>

#include <cstring>
#include <cstdlib>

#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include <unordered_set>
#include <experimental/filesystem>
#include <fstream>
#include <thread>
#include <exception>

using namespace nob;

nob::first_task blk([]() {

	nob::log(std::hex);

	std::stringstream ss;
	ss << program::version;
	auto ver = ss.str();

	std::fstream f("D:\\Games\\GTA\\" + ver + "\\scr_ntv_addrs.inc", f.binary | f.trunc | f.in | f.out);
	if (!f.is_open()) {
		nob::log("failed to open ");
	}

	f << std::hex;

	std::unordered_set<std::string> scr_names, black_scr_names {
		"appsidetask"
	};

	for (auto& p: std::experimental::filesystem::directory_iterator("D:\\Games\\GTA\\1365\\scr")) {
		if (std::experimental::filesystem::file_size(p.path()) >= 157) {
			auto name = p.path().filename().string();
			name = name.substr(0, name.length() - 4);
			for (auto &black_scr_name : black_scr_names) {
				if (name == black_scr_name) {
					goto ctn;
				}
			}
			scr_names.emplace(name);
			ctn:;
		}
	}

	for (size_t i = 0; i < ntv::script_list->size; ++i) {
		auto &scr = ntv::script_list->scripts[i];

		if (!scr.hash) {
			nob::log("script hash is null");
			continue;
		}

		bool loading = false;

		/*if (ntv::SCRIPT::_DOES_SCRIPT_WITH_NAME_HASH_EXIST(scr.hash)) {
			if (!ntv::SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(scr.hash)) {
				nob::log("loading ", scr.hash);
				loading = true;
				ntv::SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(scr.hash);
				while (!ntv::SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(scr.hash)) {
					yield();
				}
			}
		} else {
			nob::log("no exist ", scr.hash);
		}

		for (auto &n : scr_names) {
			if (hash(n) == scr.hash) {
				nob::log("finded name ", n, " ", scr.hash);
				if (!ntv::SCRIPT::DOES_SCRIPT_EXIST(n.c_str())) {
					nob::log("no exist ", n, " ", scr.hash);
					break;
				}
				if (!ntv::SCRIPT::HAS_SCRIPT_LOADED(n.c_str())) {
					nob::log("loading ", n, " ", scr.hash);
					loading = true;
					ntv::SCRIPT::REQUEST_SCRIPT(n.c_str());
					while (!ntv::SCRIPT::HAS_SCRIPT_LOADED(n.c_str())) {
						yield();
					}
					break;
				}
				nob::log("loaded ", n, " ", scr.hash);
				break;
			}
		}*/

		if (!scr) {
			nob::log("not loaded ", scr.hash);
			continue;
		}

		auto &scr_inf = *scr.info;

		nob::log("out ", scr_inf.name, " ", scr.hash);
		nob::log("len ", scr_inf.name, " ", scr.info->code_length);

		f << "{ \"" << scr_inf.name << "\", {" << std::endl;

		for (size_t j = 0; j < scr_inf.native_count; ++j) {
			f << "0x" << std::setw(16) << std::setfill('0') << scr_inf.native_addrs[j];
			if (j < scr_inf.native_count - 1) {
				f << ",";
			}
			f << std::endl;
		}

		f << "}}";

		if (i < ntv::script_list->size - 1) {
			f << ",";
		}
		f << std::endl;

		if (loading) {
			ntv::SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(scr.hash);
			yield();
		}

		yield();
	}

	nob::log("scr_ntv_addrs end");
	yield();

	std::thread([ver]() {
		if (ntv::func_table) {
			std::fstream f2("D:\\Games\\GTA\\" + ver + "\\ntv_hash_addrs.inc", f2.binary | f2.trunc | f2.in | f2.out);
			if (!f2.is_open()) {
				nob::log("failed to open ");
			}
			f2 << std::hex;
			for (auto pr : *ntv::func_table) {
				f2 <<
					"{ 0x" << std::setw(16) << std::setfill('0') << pr.first << ", 0x" <<
					std::setw(16) << std::setfill('0') << reinterpret_cast<uintptr_t>(pr.second) << " }," << std::endl
				;
			}
		}
		nob::log("ntv_hash_addrs end");
	}).detach();
});
