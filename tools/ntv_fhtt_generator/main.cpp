#include <nob/ntv/base.hpp>
#include <nob/ntv/fhtt.hpp>

#include <rua/os/process.hpp>
#include <rua/cp/chan.hpp>

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <experimental/filesystem>
#include <map>

std::unordered_set<uint64_t> old_hashs, new_hashs;

struct ysc_slice_t {
	size_t code_size;

	struct func_patten_t {
		rua::data before, after;
	};

	std::unordered_map<uint64_t, std::vector<func_patten_t>> funcs_pats;
};

std::unordered_map<std::string, ysc_slice_t> old_ysc_map, new_ysc_map;

const std::unordered_map<uint64_t, uint64_t> *old_fhtt;
std::unordered_map<uint64_t, std::pair<uint64_t, size_t>> new_fhtt_nn;

namespace fs = std::experimental::filesystem;

void load_yscs(std::string dir, std::unordered_set<uint64_t> &hashs, std::unordered_map<std::string, ysc_slice_t> &ysc_map) {
	auto dir_name = std::experimental::filesystem::path(dir).filename().string();

	size_t rd_c = 0;
	rua::cp::chan<bool> rd_done_ch;
	std::mutex mtx;

	for (auto &de: fs::directory_iterator(dir)) {
		auto path = de.path().string();
		auto name = de.path().filename().string();

		//if (name != "freemode.ysc.full") {
			//continue;
		//}

		++rd_c;

		std::thread([path, name, rd_done_ch, &dir_name, &mtx, &ysc_map, &hashs]() mutable {
			std::fstream ysc_f(path, std::ios_base::binary | std::ios_base::in);
			if (!ysc_f.is_open()) {
				std::cout << "error: failed to open " << path << std::endl;
				rd_done_ch << false;
				return;
			}

			std::cout << "read: " << dir_name << "/" << name << std::endl;

			std::vector<char> buf(fs::file_size(path));
			ysc_f.read(buf.data(), buf.size());
			ysc_f.close();

			auto &ysc = *reinterpret_cast<nob::ntv::ysc_header_t *>(buf.data());

			ysc.redirect();

			if (!ysc.code_size) {
				rd_done_ch << false;
				return;
			}

			mtx.lock();
			auto &ysc_slc = ysc_map[name];
			mtx.unlock();

			ysc_slc.code_size = ysc.code_size;

			std::unordered_map<uint64_t, std::vector<ysc_slice_t::func_patten_t>> funcs_pats;

			for (size_t i = 0; i < ysc.imp_func_count; ++i) {
				auto hash = ysc.imp_funcs[i];

				mtx.lock();

				auto it = hashs.find(hash);
				if (it == hashs.end()) {
					hashs.emplace(hash);
				}

				mtx.unlock();

				auto &pats = funcs_pats[hash];

				auto hash_ptr = rua::any_ptr(&ysc.imp_funcs[i]);

				for (size_t j = 0; j < ysc.code_page_count(); ++j) {
					auto code_page_base = rua::any_ptr(ysc.code_pages[j]);

					if (ysc.code_page_size(j) < 4) {
						continue;
					}

					for (size_t h = 0; h < ysc.code_page_size(j) - 4; ++h) {
						auto val_ptr = code_page_base + h;
						auto &val = *val_ptr.to<uint32_t *>();

						if (val == hash_ptr.to<intptr_t>() - val_ptr.to<intptr_t>()) {
							val = 0;

							pats.emplace_back();
							auto &pat = pats.back();
							if (h < 50) {
								pat.before = rua::data(code_page_base, h);
							} else {
								pat.before = rua::data(val_ptr - 50, 50);
							}
							auto after_begin = h + 4;
							if (after_begin + 50 > ysc.code_page_size(j)) {
								pat.after = rua::data(code_page_base + after_begin, ysc.code_page_size(j) - h);
							} else {
								pat.after = rua::data(code_page_base + after_begin, 50);
							}

							h += 3;
						}
					}
				}
			}

			ysc_slc.funcs_pats = funcs_pats;

			rd_done_ch << true;
		}).detach();

		//break;

		if (rd_c >= 4) {
			rd_done_ch.get();
			--rd_c;
		}
	}

	for (size_t i = 0; i < rd_c; ++i) {
		rd_done_ch.get();
	}
}

int main() {
	size_t old_ver = 1365;
	size_t new_ver = 1493;

	old_fhtt = &nob::ntv::fhtt_map.find(old_ver)->second;
	if (!old_fhtt) {
		std::cout << "!old_fhtt" << std::endl;
		return 0;
	}

	auto bin_dir_path = fs::path(rua::os::process::from_this().file_path()).remove_filename().string();

	std::cout << "reading ysc files from '" + bin_dir_path + "ysc\\{" << old_ver << "," << new_ver << "}\\*'" << std::endl;

	load_yscs(bin_dir_path + "ysc\\" + std::to_string(old_ver), old_hashs, old_ysc_map);
	load_yscs(bin_dir_path + "ysc\\" + std::to_string(new_ver), new_hashs, new_ysc_map);

	std::cout << "old_hashs: " << old_hashs.size() << std::endl;
	std::cout << "new_hashs: " << new_hashs.size() << std::endl;

	size_t loss_old_hash_c = 0;

	std::cout << std::hex << std::uppercase;

	for (auto &new_hash : new_hashs) {
		std::cout << "converting hash " << "0x" << std::setw(16) << std::setfill('0') << new_hash << std::endl;

		struct func_pattens_t {
			std::string from;
			std::vector<ysc_slice_t::func_patten_t> &data;
		};
		std::vector<func_pattens_t> new_pats_list;

		for (auto &pr : new_ysc_map) {
			auto it = pr.second.funcs_pats.find(new_hash);
			if (it != pr.second.funcs_pats.end()) {
				new_pats_list.emplace_back(func_pattens_t{pr.first, it->second});
			}
		}

		for (auto &new_pats : new_pats_list) {
			auto it = old_ysc_map.find(new_pats.from);
			if (it == old_ysc_map.end()) {
				continue;
			}
			auto &old_ysc = it->second;

			for (auto &new_pat : new_pats.data) {
				for (auto &old_funcs_pats_pr : old_ysc.funcs_pats) {
					auto old_hash = old_funcs_pats_pr.first;

					size_t sg = 0;

					for (auto &old_pat : old_funcs_pats_pr.second) {
						auto b_sz = new_pat.before.size() > old_pat.before.size() ? old_pat.before.size() : new_pat.before.size();
						size_t bs_sz = 0;
						for (int i = b_sz - 1; i >= 0; --i) {
							if (new_pat.before.get<uint8_t>(i) != old_pat.before.get<uint8_t>(i)) {
								bs_sz = b_sz - (i + 1);
								break;
							}
						}
						auto a_sz = new_pat.after.size() > old_pat.after.size() ? old_pat.after.size() : new_pat.after.size();
						size_t as_sz = 0;
						for (size_t i = 0; i < a_sz - 1; ++i) {
							if (new_pat.after.get<uint8_t>(i) != old_pat.after.get<uint8_t>(i)) {
								as_sz = i;
								break;
							}
						}
						auto s_sz = bs_sz + as_sz;
						if (s_sz > sg) {
							sg = s_sz;
						}
					}

					if (!sg) {
						continue;
					}

					for (auto &old_fhtt_pr : *old_fhtt) {
						if (old_fhtt_pr.second == old_hash) {
							auto it = new_fhtt_nn.find(old_fhtt_pr.first);
							if (it == new_fhtt_nn.end()) {
								new_fhtt_nn.emplace(old_fhtt_pr.first, std::make_pair(new_hash, sg));
							} else if (sg > it->second.second) {
								it->second.first = new_hash;
								it->second.second = sg;
							}
							break;
						}
					}
				}
			}
		}

		Sleep(1);
	}

	std::cout << "loss_old_hash_c: " << loss_old_hash_c << std::endl;

	auto new_fhtt_path = bin_dir_path + "..\\src\\ntv\\fhtt\\" + std::to_string(new_ver) + ".unsafe.inc";

	std::cout << "writing new_fhtt to '" << new_fhtt_path << "'" << std::endl;

	std::fstream new_fhtt_f(new_fhtt_path, std::ios_base::binary | std::ios_base::trunc | std::ios_base::out);
	if (!new_fhtt_f.is_open()) {
		std::cout << "failed to open" << std::endl;
	}

	new_fhtt_f << std::hex << std::uppercase;

	size_t new_fhtt_sz = 0;

	bool first = true;

	for (auto &pr : new_fhtt_nn) {
		if (first) {
			first = false;
		} else {
			new_fhtt_f << "," << std::endl;
		}

		new_fhtt_f << "{ 0x" << std::setw(16) << std::setfill('0') << pr.first << ", 0x" << std::setw(16) << std::setfill('0') << pr.second.first << " }";

		++new_fhtt_sz;

		auto it = new_hashs.find(pr.second.first);
		if (it != new_hashs.end()) {
			new_hashs.erase(it);
		}
	}

	for (auto &new_hash : new_hashs) {
		if (first) {
			first = false;
		} else {
			new_fhtt_f << "," << std::endl;
		}

		new_fhtt_f << "{ 0x" << std::setw(16) << std::setfill('0') << new_hash << ", 0x" << std::setw(16) << std::setfill('0') << new_hash << " }";

		++new_fhtt_sz;
	}

	new_fhtt_f << std::endl;

	std::cout << "new_fhtt_sz: " << new_fhtt_sz << std::endl;

	std::cout << "done!!!" << std::endl;
}
