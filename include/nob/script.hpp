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
		extern std::thread::id id;
		extern std::atomic<size_t> first_frame_count;
	} /* this_script */

	extern rua::co_pool tasks;

	static constexpr size_t duration_forever = rua::co_pool::duration_forever;
	static constexpr size_t duration_disposable = rua::co_pool::duration_disposable;

	class task {
		public:
			task(std::nullptr_t np = nullptr) : _cp_tsk(np) {}

			task(const std::function<void()> &handler, size_t duration = duration_forever) :
				_cp_tsk(tasks.add(handler, duration))
			{}

			operator bool() const {
				return tasks.has(_cp_tsk);
			}

			void del() {
				tasks.erase(_cp_tsk);
				_cp_tsk.reset();
			}

			void reset_dol(size_t duration = -1) {
				tasks.reset_dol(_cp_tsk, duration);
			}

		private:
			rua::co_pool::task _cp_tsk;
	};

	inline task go(const std::function<void()> &handler) {
		return task(handler, duration_disposable);
	}

	inline void sleep(size_t duration) {
		tasks.sleep(duration);
	}

	inline void yield() { sleep(duration_disposable); }

	inline bool in_task() {
		return tasks.this_caller_in_task();
	}

	namespace this_task {
		inline void del() {
			tasks.erase();
		}
		inline void reset_dol(size_t duration_of_life) {
			tasks.reset_dol(duration_of_life);
		}
	}

	class initer {
		public:
			initer(const std::function<void()> &);
			initer(const std::function<void(initer)> &);
	};

	template <typename T>
	class chan : public rua::chan<T> {
		public:
			chan() : rua::chan<T>({ tasks.get_scheduler() }) {}
	};

	void terminate_unimportant_scripts();
} /* nob */
