#include <nob/ntv/base.hpp>
#include <nob/ntv/fhtt.hpp>

#include <rua/process.hpp>

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <experimental/filesystem>

std::unordered_set<uint64_t> old_hashs, new_hashs;

std::unordered_map<std::string, std::vector<uintptr_t>> old_ysc_hashs_map, new_ysc_hashs_map;

const std::unordered_map<uint64_t, uint64_t> *old_fhtt;
std::unordered_map<uint64_t, std::map<size_t, uint64_t>> new_fhtt;

namespace fs = std::experimental::filesystem;

void load_yscs(std::string dir, std::unordered_set<uint64_t> &hashs, std::unordered_map<std::string, std::vector<uintptr_t>> &ysc_hashs_map) {
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

		auto &ysc_hashs = ysc_hashs_map[name];

		for (size_t i = 0; i < ysc.using_func_count; ++i) {
			hashs.emplace(ysc.using_funcs[i]);
			ysc_hashs.emplace_back(ysc.using_funcs[i]);
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

	std::cout << "reading '" + bin_dir_path + "ysc\\{" << old_ver << "," << new_ver << "}\\*' ysc files" << std::endl;

	load_yscs(bin_dir_path + "ysc\\" + std::to_string(old_ver), old_hashs, old_ysc_hashs_map);
	load_yscs(bin_dir_path + "ysc\\" + std::to_string(new_ver), new_hashs, new_ysc_hashs_map);

	std::cout << "old_hashs: " << old_hashs.size() << std::endl;
	std::cout << "new_hashs: " << new_hashs.size() << std::endl;

	std::cout << "coverting hashs" << std::endl;

	std::cout << std::hex << std::uppercase;

	for (auto &new_hash : new_hashs) {
		struct point_t {
			std::string ysc_name;
			size_t ix;
		};

		std::vector<point_t> points;

		for (auto &pr : new_ysc_hashs_map) {
			for (size_t i = 0; i < pr.second.size(); ++i) {
				if (pr.second[i] == new_hash) {
					points.emplace_back(point_t{ pr.first, i });
				}
			}
		}

		std::unordered_map<uintptr_t, size_t> old_hash_ballot;

		for (auto &pt : points) {
			auto &old_ysc_hashs = old_ysc_hashs_map[pt.ysc_name];
			auto &new_ysc_hashs = new_ysc_hashs_map[pt.ysc_name];

			int ix = pt.ix;

			if (pt.ix >= old_ysc_hashs.size()) {
				ix = old_ysc_hashs.size() - 1;
			}

			auto &vc = ++old_hash_ballot[old_ysc_hashs[ix]];

			if (new_ysc_hashs.size() > old_ysc_hashs.size()) {
				int n = new_ysc_hashs.size() - old_ysc_hashs.size();
				if (pt.ix >= old_ysc_hashs.size()) {
					n -= pt.ix - (old_ysc_hashs.size() - 1);
				}
				for (int i = ix - 1; i > ix - n - 1 && i >= 0; --i) {
					++old_hash_ballot[old_ysc_hashs[i]];
				}
			} else if (new_ysc_hashs.size() < old_ysc_hashs.size()) {
				int n = old_ysc_hashs.size() - new_ysc_hashs.size();
				for (int i = ix + 1; i < ix + n && i < (int)old_ysc_hashs.size(); ++i) {
					++old_hash_ballot[old_ysc_hashs[i]];
				}
			} else {
				if (vc == 1) {
					++vc;
				}
			}
		}

		size_t old_hash_votes = 0;
		uintptr_t old_hash = 0;

		for (auto &votes : old_hash_ballot) {
			if (votes.second > old_hash_votes) {
				old_hash_votes = votes.second;
				old_hash = votes.first;
			}
		}

		if (!old_hash) {
			std::cout << "!old_hash " << new_hash << std::endl;
			new_fhtt[new_hash].emplace(1, new_hash);
			continue;
		}

		for (auto &hash_pr : *old_fhtt) {
			if (hash_pr.second == old_hash) {
				auto &map = new_fhtt[hash_pr.first];
				auto it = map.find(old_hash_votes);
				if (it == map.end()) {
					map.emplace(old_hash_votes, new_hash);
				}
				break;
			}
		}
	}

	std::cout << std::dec;

	std::cout << "new_fhtt: " << new_fhtt.size() << std::endl;

	auto new_fhtt_path = bin_dir_path + "..\\src\\ntv\\fhtt\\" + std::to_string(new_ver) + ".auto.inc";

	std::cout << "writing '" << new_fhtt_path << "'" << std::endl;

	std::fstream fhtt_f(new_fhtt_path, std::ios_base::binary | std::ios_base::trunc | std::ios_base::out);
	if (!fhtt_f.is_open()) {
		std::cout << "failed to open" << std::endl;
	}

	fhtt_f << std::hex << std::uppercase;

	bool first = true;

	for (auto &pr : new_fhtt) {
		if (first) {
			first = false;
		} else {
			fhtt_f << "," << std::endl;
		}
		fhtt_f << "{ 0x" << std::setw(16) << std::setfill('0') << pr.first << ", 0x" << std::setw(16) << std::setfill('0') << pr.second.rbegin()->second << " }";
	}

	fhtt_f << std::endl;

	std::cout << "done!!!" << std::endl;
}
