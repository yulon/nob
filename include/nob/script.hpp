#pragma once

#include <tmd/coro_pool.hpp>
#include <tmd/chan.hpp>

#include <functional>
#include <thread>

namespace nob {
	namespace this_script {
		extern std::thread::id thread_id;
		extern bool asi_mode;
	} /* this_script */

	void wait(size_t ms);
	inline void wait_next_frame() { wait(0); }
	void wait(const std::function<bool()> &cond);
	inline void wait_cond(const std::function<bool()> &cond) { wait(cond); }

	class task {
		public:
			task(std::nullptr_t np = nullptr) : _cp_tsk(np) {}

			task(const std::function<void()> &handler, int life_duration = -1);

			operator bool() const;

			void del();

		private:
			tmd::coro_pool::task _cp_tsk;
	};

	task go(const std::function<void()> &handler);

	bool in_task();
	void del_this_task();

	class initer {
		public:
			initer(const std::function<void()> &);
			initer(const std::function<void(initer)> &);
	};

	template <typename T>
	class chan : public tmd::chan<T> {
		public:
			chan() : tmd::chan<T>({{
				in_task,
				wait_next_frame,
				static_cast<void (*)(const std::function<bool()> &)>(wait)
			}}) {}
	};
} /* nob */
