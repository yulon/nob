#pragma once

#include <rua/macros.hpp>

#include <sstream>
#include <mutex>

#ifdef DEBUG
	#include <windows.h>

	#include <iostream>
	#include <thread>
	#include <cstring>
#endif

namespace nob {
	class log_t {
		public:
			template <typename... T>
			void operator()(T&&... vals) {
				std::scoped_lock<std::mutex> lock(_mtx);

				_out(_buf, std::forward<T>(vals)...);
				_buf << std::endl;

				#ifdef DEBUG
					if (_con) {
						_out(std::cout, std::forward<T>(vals)...);
						std::cout << std::endl;
					}
				#endif
			}

			void alloc_console() {
				#ifdef DEBUG
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
				#endif
			}

			std::string str() {
				std::scoped_lock<std::mutex> lock(_mtx);

				return _buf.str();
			}

		private:
			#ifdef DEBUG
				bool _con = false;
			#endif

			std::stringstream _buf;
			std::mutex _mtx;

			template<typename T>
			static void _out(T &) {}

			template<typename T, typename V, typename... OV>
			static void _out(T &o, V &&v, OV&&... ov) {
				o << std::forward<V>(v);
				_out<T, OV...>(o, std::forward<OV>(ov)...);
			}
	};

	RUA_INLINE_VAR_S(log_t, log, );
}
