#pragma once

#include <rua/cp.hpp>

#include <functional>
#include <thread>
#include <atomic>
#include <memory>

namespace nob {
	namespace this_script {
		enum class mode_t {
			invalid,
			shv,
			ysc,
			main_thread,
			sub_thread
		};

		extern mode_t mode;
		extern std::thread::id id;
		extern size_t load_count;
		extern std::atomic<size_t> load_count_s;
		extern std::atomic<bool> exiting;
	} /* this_script */

	extern std::unique_ptr<rua::cp::coro_pool> tasks;

	using dur_t = rua::cp::coro_pool::dur_t;

	class task {
		public:
			task(std::nullptr_t np = nullptr) : _cp_tsk(np) {}

			task(const std::function<void()> &handler, dur_t timeout = dur_t::forever) {
				if (!tasks) {
					tasks.reset(new rua::cp::coro_pool);
					tasks->add_back([]() {
						tasks->exit();
					});
				}
				_cp_tsk = tasks->add(handler, timeout);
			}

			operator bool() const {
				return _cp_tsk && tasks && tasks->has(_cp_tsk);
			}

			void del() {
				if (*this) {
					tasks->erase(_cp_tsk);
					_cp_tsk.reset();
				}
			}

			void reset_dol(dur_t timeout = dur_t::disposable) {
				tasks->reset_dol(_cp_tsk, timeout);
			}

		private:
			rua::cp::coro_pool::task _cp_tsk;
	};

	inline task go(const std::function<void()> &handler) {
		return task(handler, dur_t::disposable);
	}

	inline bool in_task() {
		return tasks->this_caller_in_task();
	}

	namespace this_task {
		inline void del() {
			tasks->erase();
		}

		inline void reset_dol(dur_t timeout) {
			tasks->reset_dol(timeout);
		}

		inline void sleep(dur_t timeout) {
			tasks->sleep(timeout);
		}

		inline void yield() {
			tasks->yield();
		}
	}

	inline void sleep(dur_t timeout) {
		this_task::sleep(timeout);
	}

	inline void yield() {
		this_task::yield();
	}

	// used to non-game resources initialization.
	// can't use sleep/yield.
	class initer {
		public:
			initer(std::function<void()>);
	};

	// used to destroy game resources during a halfway exit.
	// can't use sleep/yield.
	class exiter {
		public:
			exiter(std::function<void()>);
	};

	class first_task {
		public:
			first_task(const std::function<void()> &handler) {
				initer([handler]() {
					go(handler);
				});
			}
	};

	class once_task {
		public:
			once_task(std::function<void()> handler) {
				go(std::move(handler));
			}
	};

	template <typename T>
	class chan : public rua::cp::chan<T> {
		public:
			chan() : rua::cp::chan<T>({ tasks->get_scheduler() }) {}
	};

	void terminate_unimportant_scripts();
} /* nob */
