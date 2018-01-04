#pragma once

#ifdef DEBUG

#include "window.hpp"

#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <cstring>

#endif

namespace nob {
	class log_t {
		public:
			template <typename... T>
			void operator()(T&&... vals) {
				#ifdef DEBUG
					std::scoped_lock<std::mutex> lock(_mtx);

					_out(_buf, std::forward<T>(vals)...);
					_buf << std::endl;

					if (_con) {
						_out(std::cout, std::forward<T>(vals)...);
						std::cout << std::endl;
					} else if (!_ac_td) {
						_ac_td = true;
						std::thread([this]() {
							auto wnd = window::native_handle();
							while (!wnd) {
								std::this_thread::sleep_for(std::chrono::seconds(1));
								wnd = window::native_handle();
							}

							AllocConsole();
							freopen("conout$", "w+t", stdout);
							freopen("conout$", "w+t", stderr);
							freopen("conin$", "r+t", stdin);

							{
								std::scoped_lock<std::mutex> lock(_mtx);

								_con = true;
								auto str = _buf.str();
								if (str.length()) {
									std::cout << str;
									std::cout.flush();
								}
							}
						}).detach();
					}
				#endif
			}

		#ifdef DEBUG
			static const char *const endl;

			private:
				bool _con = false;
				bool _ac_td = false;
				std::stringstream _buf;
				std::mutex _mtx;

				template<typename T>
				static void _out(T &) {}

				template<typename T, typename V, typename... OV>
				static void _out(T &o, V &&v, OV&&... ov) {
					o << std::forward<V>(v);
					_out<T, OV...>(o, std::forward<OV>(ov)...);
				}
		#endif
	};

	extern log_t log;
}
