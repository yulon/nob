#include <nob.hpp>

#include <rua/process.hpp>

#include "ntv_dump.pb.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <random>

#include <unordered_set>
#include <experimental/filesystem>
#include <fstream>
#include <thread>

namespace fs = std::experimental::filesystem;

nob::first_task blk([]() {

	nob::log(std::hex);

	std::stringstream ss;
	ss << nob::program::version;
	auto ver = ss.str();

	auto out_path = fs::path(rua::process::from_this().file_path(nob::this_script::os_module_handle)).replace_filename("ntv_dump\\" + ver + ".pb").string();

	std::fstream f(out_path, f.binary | f.trunc | f.in | f.out);
	if (!f.is_open()) {
		nob::log("failed to open");
		return;
	}

	nob::ntv_dump dump;

	std::unordered_set<std::string> scr_names {
		"freemode"
	};

	for (size_t i = 0; i < nob::ntv::script_list->size; ++i) {
		auto &scr = nob::ntv::script_list->scripts[i];

		if (!scr.hash) {
			nob::log("script hash is null");
			continue;
		}

		bool loading = false;

		for (auto &n : scr_names) {
			if (nob::hash(n) == scr.hash) {
				nob::log("finded name ", scr.hash);
				if (!nob::ntv::SCRIPT::_DOES_SCRIPT_WITH_NAME_HASH_EXIST(scr.hash)) {
					nob::log("no exist ", scr.hash);
					break;
				}
				if (!nob::ntv::SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(scr.hash)) {
					nob::log("loading ", scr.hash);
					loading = true;
					nob::ntv::SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(scr.hash);
					while (!nob::ntv::SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(scr.hash)) {
						nob::yield();
					}
					break;
				}
			}
		}

		if (!scr) {
			nob::log("not loaded ", scr.hash);
			continue;
		}

		auto &scr_inf = *scr.info;

		auto &funcs = (*dump.mutable_script_funcs())[scr_inf.name];

		for (size_t j = 0; j < scr_inf.native_count; ++j) {
			funcs.add_addr(scr_inf.native_addrs[j]);
		}

		if (loading) {
			nob::ntv::SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(scr.hash);
			nob::yield();
		}

		nob::yield();
	}

	nob::yield();

	if (nob::ntv::func_table) {
		for (auto pr : *nob::ntv::func_table) {
			(*dump.mutable_func_table())[pr.first] = reinterpret_cast<uint64_t>(pr.second);
		}
	}

	nob::log("out: " + out_path);

	dump.SerializeToOstream(&f);

	nob::log("done");
});
