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
			std::list<std::shared_ptr<std::function<bool(int, bool)>>>::iterator _lnr_it;
	};

	bool is_key_down(int code);

	using hotkey_t = ntv::eControl;

	class hotkey_listener {
		public:
			hotkey_listener() = default;

			hotkey_listener(hotkey_t, std::function<bool(hotkey_t, bool)> lnr = nullptr);

			hotkey_listener(std::initializer_list<hotkey_t>, std::function<bool(hotkey_t, bool)> lnr = nullptr);

			hotkey_listener(hotkey_listener &&);

			hotkey_listener &operator=(hotkey_listener &&);

			~hotkey_listener() {
				del();
			}

			void del();

			operator bool() const;

		private:
			std::vector<int> _hks;
			std::vector<
				std::list<
					std::shared_ptr<
						std::function<bool(hotkey_t, bool)>
					>
				>::iterator
			> _lnr_its;
	};

	vector2 mouse_pos();

	vector2_i mouse_pos_i();

	const char *key_code_to_str(int code);
} /* nob */
