#pragma once

#include <nob/script.hpp>

#include <dxgi.h>

#include <list>
#include <functional>

namespace nob {
	namespace dx {
		class on_render {
			public:
				on_render() : _it(_handler_list().end()) {}

				on_render(std::function<void(IDXGISwapChain *)> handler) {
					if (!handler) {
						return;
					}

					_handler_list().emplace_back(std::move(handler));
					_it = --_handler_list().end();

					if (this_script::load_count) {
						_init();
					}
				}

				~on_render() {
					del();
				}

				operator bool() const {
					return _it != _handler_list().end();
				}

				void del() {
					auto &li = _handler_list();
					if (_it == li.end()) {
						return;
					}
					li.erase(_it);
					_it = li.end();
				}

				static size_t count() {
					return _handler_list().size();
				}

			private:
				using _handler_list_t = std::list<std::function<void(IDXGISwapChain *)>>;

				_handler_list_t::iterator _it;

				static _handler_list_t &_handler_list() {
					static _handler_list_t inst;
					return inst;
				}

				static void _handle(IDXGISwapChain *sc) {
					for (auto &hdr : _handler_list()) {
						hdr(sc);
					}
				}

			public:
				static void _init();
				static void _uninit();
		};
	}
}
