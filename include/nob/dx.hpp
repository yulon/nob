#pragma once

#include <dxgi.h>

#include <list>
#include <functional>

namespace nob {
	namespace dx {
		class on_render {
			public:
				on_render() : _it(handler_list().end()) {}

				on_render(std::function<void(IDXGISwapChain *)> handler) {
					handler_list().emplace_back(std::move(handler));
					_it = --handler_list().end();
				}

				~on_render() {
					del();
				}

				void del() {
					auto &li = handler_list();
					if (_it == li.end()) {
						return;
					}
					li.erase(_it);
					_it = li.end();
				}

				////////////////////////////////////////////////////////////////////

				using handler_list_t = std::list<std::function<void(IDXGISwapChain *)>>;

				static handler_list_t &handler_list() {
					static handler_list_t inst;
					return inst;
				}

			private:
				handler_list_t::iterator _it;
		};
	}
}
