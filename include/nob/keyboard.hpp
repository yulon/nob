#pragma once

#include <functional>
#include <list>

namespace nob {
	namespace keyboard {
		class listener {
			public:
				listener();

				listener(std::function<bool(int code, bool down)>);

				listener(listener &&);

				const listener &operator=(listener &&);

				~listener() {
					del();
				}

				void del();

			private:
				std::list<std::function<bool(int, bool)>>::iterator _it;
		};

		bool is_down(int code);
	} /* keyboard */
} /* nob */
