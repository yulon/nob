#pragma once

#include <rua/co_pool.hpp>
#include <rua/chan.hpp>

#include <functional>
#include <thread>
#include <atomic>
#include <memory>

namespace nob {
	namespace this_script {
		extern HMODULE os_module_handle;

		enum class mode_t {
			invalid,
			shv,
			ysc,
			main_thread,
			sub_thread
		};

		extern mode_t mode;
		extern std::thread::id id;
		extern std::atomic<size_t> gameplay_id;
		extern std::atomic<bool> exiting;
	} /* this_script */

	extern std::unique_ptr<rua::co_pool> tasks;

	using duration = rua::co_pool::duration;

	class task {
		public:
			task(std::nullptr_t np = nullptr) : _cp_tsk(np) {}

			task(const std::function<void()> &handler, duration timeout = duration::forever) {
				if (!tasks) {
					tasks.reset(new rua::co_pool);
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

			void reset_dol(duration timeout = duration::disposable) {
				tasks->reset_dol(_cp_tsk, timeout);
			}

		private:
			rua::co_pool::task _cp_tsk;
	};

	inline task go(const std::function<void()> &handler) {
		return task(handler, duration::disposable);
	}

	inline bool in_task() {
		return tasks->this_caller_in_task();
	}

	namespace this_task {
		inline void del() {
			tasks->erase();
		}

		inline void reset_dol(duration timeout) {
			tasks->reset_dol(timeout);
		}

		inline void sleep(duration timeout) {
			tasks->sleep(timeout);
		}

		inline void yield() {
			tasks->yield();
		}
	}

	inline void sleep(duration timeout) {
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
	class chan : public rua::chan<T> {
		public:
			chan() : rua::chan<T>({ tasks->get_scheduler() }) {}
	};

	void terminate_unimportant_scripts();
} /* nob */
