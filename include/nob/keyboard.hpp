#pragma once

#include <functional>
#include <list>
#include <initializer_list>
#include <vector>

namespace nob {
	namespace keyboard {
		class listener {
			public:
				listener();

				listener(std::function<bool(int code, bool down)>);

				listener(listener &&);

				listener &operator=(listener &&);

				~listener() {
					del();
				}

				void del();

				operator bool() const;

			private:
				std::list<std::function<bool(int, bool)>>::iterator _it;
		};

		bool is_down(int code);

		enum class block_t : int {
			phone = 27,
			frontend_menu_pause = 199,
			frontend_menu_esc = 200,
			interaction_menu = 244
		};

		class blocker {
			public:
				blocker() = default;

				blocker(block_t);

				blocker(std::initializer_list<block_t>);

				blocker(blocker &&);

				blocker &operator=(blocker &&);

				~blocker() {
					del();
				}

				void del();

				operator bool() const;

			private:
				std::vector<int> _blks;
		};
	} /* keyboard */
} /* nob */
