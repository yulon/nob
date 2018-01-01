#pragma once

#include <rua/co_pool.hpp>
#include <rua/chan.hpp>

#include <functional>
#include <thread>
#include <atomic>

namespace nob {
	namespace this_script {
		enum class mode_t {
			invalid,
			shv,
			ysc,
			exclusive
		};

		extern mode_t mode;
		extern std::thread::id thread_id;
		extern std::atomic<size_t> first_frame_count;
	} /* this_script */

	void wait(size_t ms);
	inline void wait_next_frame() { wait(0); }
	void wait(const std::function<bool()> &cond);
	inline void wait_cond(const std::function<bool()> &cond) { wait(cond); }

	class task {
		public:
			task(std::nullptr_t np = nullptr) : _cp_tsk(np) {}

			task(const std::function<void()> &handler, size_t duration_of_life = -1);

			operator bool() const;

			void del();

			void reset_dol(size_t duration_of_life = -1);

		private:
			rua::co_pool::task _cp_tsk;
	};

	inline void go(const std::function<void()> &handler) {
		task(handler, 0);
	}

	bool in_task();

	namespace this_task {
		void del();
		void reset_dol(int duration_of_life = -1);
	}

	class initer {
		public:
			initer(const std::function<void()> &);
			initer(const std::function<void(initer)> &);
	};

	template <typename T>
	class chan : public rua::chan<T> {
		public:
			chan() : rua::chan<T>({{
				in_task,
				wait_next_frame,
				static_cast<void (*)(const std::function<bool()> &)>(wait)
			}}) {}
	};

	void terminate_unimportant_scripts();
} /* nob */
