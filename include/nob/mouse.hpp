#pragma once

#include "vector.hpp"

#include <functional>
#include <list>
#include <memory>

namespace nob {
	namespace mouse {
		class listener {
			public:
				listener();

				listener(std::function<bool(int button, bool down)>);

				listener(listener &&);

				listener &operator=(listener &&);

				~listener() {
					del();
				}

				void del();

				operator bool() const;

			private:
				std::list<std::shared_ptr<std::function<bool(int, bool)>>>::iterator _it;
		};

		vector2 coords();

		bool is_down(int button);
	} /* mouse */
} /* nob */
