#include <nob/g2d.hpp>
#include <nob/program.hpp>

#include <thread>

namespace nob {
	namespace g2d {
		int texture_dict::register_from_file(const std::string &path) {
			static uint32_t *(*fptr)(int *, const char *, bool, const char *, bool);
			static bool finding = false, finded = false;
			if (finding) {
				while (!finded) {
					yield();
				}
			} else {
				finding = true;
				chan<rua::any_ptr> ch;
				std::thread([ch]() mutable {
					auto mr = game_code.match({
						// Reference from https://www.unknowncheats.me/forum/grand-theft-auto-v/144028-gta-reversal-thread-124.html#post2146746
						0x48, 0x89, 0x5C, 0x24, 1111, 0x48, 0x89, 0x6C, 0x24, 1111, 0x48, 0x89, 0x7C,
						0x24, 1111, 0x41, 0x54, 0x41, 0x56, 0x41, 0x57, 0x48, 0x83, 0xEC, 0x50, 0x48,
						0x8B, 0xEA, 0x4C, 0x8B, 0xFA, 0x48, 0x8B, 0xD9, 0x4D, 0x85, 0xC9
					});
					if (!mr) {
						log("nob::g2d::texture_dict::register_from_file::fptr: not found!");
						ch << nullptr;
						return;
					}
				}).detach();
				fptr = ch.get();
				finded = true;
			}
			if (!fptr) {
				return 0;
			}

			std::string name;
			for (int i = static_cast<int>(path.length() - 1); i > 0; --i) {
				if (path[i] == '\\' || path[i] == '/') {
					name = path.substr(static_cast<size_t>(i) + 1);
				}
			}
			int id;
			fptr(&id, path.c_str(), true, name.c_str(), false);
			return id;
		}
	}
}
