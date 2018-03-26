#include <nob/ntv/base.hpp>
#include <nob/ntv/fhtt.hpp>

#include <rua/process.hpp>

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <experimental/filesystem>

std::unordered_set<uint64_t> old_hashs, new_hashs;

std::unordered_map<std::string, std::pair<size_t, std::vector<uintptr_t>>> old_ysc_map, new_ysc_map;

const std::unordered_map<uint64_t, uint64_t> *old_fhtt;
std::unordered_map<uint64_t, std::map<size_t, uint64_t>> new_fhtt;

namespace fs = std::experimental::filesystem;

void load_yscs(std::string dir, std::unordered_set<uint64_t> &hashs, std::unordered_map<std::string, std::pair<size_t, std::vector<uintptr_t>>> &ysc_map) {
	for (auto &de: std::experimental::filesystem::directory_iterator(dir)) {
		auto path = de.path().string();
		auto name = de.path().filename().string();

		std::fstream ysc_f(path, std::ios_base::binary | std::ios_base::in);
		if (!ysc_f.is_open()) {
			std::cout << "failed to open " << name << std::endl;
			continue;
		}
		std::vector<char> buf(fs::file_size(path));
		ysc_f.read(buf.data(), buf.size());
		ysc_f.close();

		auto &ysc = *reinterpret_cast<nob::ntv::ysc_header_t *>(buf.data());

		ysc.redirect();

		auto &ysc_inf = ysc_map[name];

		ysc_inf.first = ysc.code_size;

		for (size_t i = 0; i < ysc.using_func_count; ++i) {
			hashs.emplace(ysc.using_funcs[i]);
			ysc_inf.second.emplace_back(ysc.using_funcs[i]);
		}
	}
}

int main() {
	size_t old_ver = 1290;
	size_t new_ver = 1365;

	old_fhtt = &nob::ntv::fhtt_map.find(old_ver)->second;
	if (!old_fhtt) {
		std::cout << "!old_fhtt" << std::endl;
		return 0;
	}

	auto bin_dir_path = fs::path(rua::process::from_this().file_path()).remove_filename().string();

	std::cout << "reading ysc files from '" + bin_dir_path + "ysc\\{" << old_ver << "," << new_ver << "}\\*'" << std::endl;

	load_yscs(bin_dir_path + "ysc\\" + std::to_string(old_ver), old_hashs, old_ysc_map);
	load_yscs(bin_dir_path + "ysc\\" + std::to_string(new_ver), new_hashs, new_ysc_map);

	std::cout << "old_hashs: " << old_hashs.size() << std::endl;
	std::cout << "new_hashs: " << new_hashs.size() << std::endl;

	std::cout << "converting hashs" << std::endl;

	size_t loss_old_hash_c = 0;

	for (auto &new_hash : new_hashs) {
		struct point_t {
			std::string ysc_name;
			size_t ix;
		};

		std::vector<point_t> points;

		for (auto &pr : new_ysc_map) {
			for (size_t i = 0; i < pr.second.second.size(); ++i) {
				if (pr.second.second[i] == new_hash) {
					points.emplace_back(point_t{ pr.first, i });
				}
			}
		}

		std::unordered_map<uintptr_t, size_t> old_hash_ballot;

		for (auto &pt : points) {
			auto &old_ysc = old_ysc_map[pt.ysc_name];
			auto &new_ysc = new_ysc_map[pt.ysc_name];

			int ix = pt.ix;

			if (pt.ix >= old_ysc.second.size()) {
				ix = old_ysc.second.size() - 1;
			}

			auto &vc = ++old_hash_ballot[old_ysc.second[ix]];

			if (new_ysc.second.size() > old_ysc.second.size()) {
				int n = new_ysc.second.size() - old_ysc.second.size();
				if (pt.ix >= old_ysc.second.size()) {
					n -= pt.ix - (old_ysc.second.size() - 1);
				}
				for (int i = ix - 1; i > ix - n - 1 && i >= 0; --i) {
					++old_hash_ballot[old_ysc.second[i]];
				}
			} else if (new_ysc.second.size() < old_ysc.second.size()) {
				int n = old_ysc.second.size() - new_ysc.second.size();
				for (int i = ix + 1; i < ix + n && i < (int)old_ysc.second.size(); ++i) {
					++old_hash_ballot[old_ysc.second[i]];
				}
			} else {
				if (new_ysc.first == old_ysc.first && vc == 1) {
					vc += 100000;
				}
			}
		}

		if (old_hash_ballot.empty()) {
			++loss_old_hash_c;
			new_fhtt[new_hash].emplace(1, new_hash);
			continue;
		}

		for (auto &hash_pr : *old_fhtt) {
			auto &map = new_fhtt[hash_pr.first];

			for (auto &votes : old_hash_ballot) {
				if (votes.first == hash_pr.second) {
					auto it = map.find(votes.second);
					if (it == map.end()) {
						map.emplace(votes.second, new_hash);
					}
				}
			}
		}

		Sleep(1);
	}

	std::cout << "loss_old_hash_c: " << loss_old_hash_c << std::endl;

	std::cout << "new_fhtt: " << new_fhtt.size() << std::endl;

	auto new_fhtt_path = bin_dir_path + "..\\src\\ntv\\fhtt\\" + std::to_string(new_ver) + ".unsafe.inc";

	std::cout << "writing new_fhtt to '" << new_fhtt_path << "'" << std::endl;

	std::fstream fhtt_f(new_fhtt_path, std::ios_base::binary | std::ios_base::trunc | std::ios_base::out);
	if (!fhtt_f.is_open()) {
		std::cout << "failed to open" << std::endl;
	}

	fhtt_f << std::hex << std::uppercase;

	size_t miti_new_hash_c = 0;

	bool first = true;

	for (auto &pr : new_fhtt) {
		if (pr.second.empty()) {
			continue;
		}

		if (first) {
			first = false;
		} else {
			fhtt_f << "," << std::endl;
		}

		fhtt_f << "{ 0x" << std::setw(16) << std::setfill('0') << pr.first << ", 0x" << std::setw(16) << std::setfill('0') << pr.second.rbegin()->second << " }";

		if (pr.second.size() > 1) {
			++miti_new_hash_c;
		}
	}

	fhtt_f << std::endl;

	std::cout << "miti_new_hash_c: " << miti_new_hash_c << std::endl;

	std::cout << "done!!!" << std::endl;
}
