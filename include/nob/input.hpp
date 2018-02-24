#pragma once

#include "ntv/consts.hpp"
#include "vector.hpp"

#include <functional>
#include <list>
#include <initializer_list>
#include <vector>
#include <memory>

namespace nob {
	class key_listener {
		public:
			key_listener();

			key_listener(std::function<bool(int code, bool down)>);

			key_listener(key_listener &&);

			key_listener &operator=(key_listener &&);

			~key_listener() {
				del();
			}

			void del();

			operator bool() const;

		private:
			std::list<std::shared_ptr<std::function<bool(int, bool)>>>::iterator _it;
	};

	bool is_key_down(int code);

	using hotkey_t = ntv::eControl;

	class hotkey_blocker {
		public:
			hotkey_blocker() = default;

			hotkey_blocker(hotkey_t);

			hotkey_blocker(std::initializer_list<hotkey_t>);

			hotkey_blocker(hotkey_blocker &&);

			hotkey_blocker &operator=(hotkey_blocker &&);

			~hotkey_blocker() {
				del();
			}

			void del();

			operator bool() const;

		private:
			std::vector<int> _hks;
	};

	vector2 mouse_pos();

	vector2_i mouse_pos_i();

	const char *key_code_to_str(int code);
} /* nob */
