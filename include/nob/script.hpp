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
			unique_thread
		};

		extern mode_t mode;
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

	// Only for task and input listener.
	inline void sleep(dur_t timeout) {
		this_task::sleep(timeout);
	}

	// Only for task and input listener.
	inline void yield() {
		this_task::yield();
	}

	// used to non-game resources initialization.
	class on_load {
		public:
			on_load() : _it(_handler_list().end()) {}

			on_load(std::function<void()> handler) {
				if (!handler) {
					return;
				}
				_handler_list().emplace_back(std::move(handler));
				_it = --_handler_list().end();
			}

			~on_load() {
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

			static void handle() {
				for (auto &hdr : _handler_list()) {
					hdr();
				}
			}

		private:
			using _handler_list_t = std::list<std::function<void()>>;

			_handler_list_t::iterator _it;

			static _handler_list_t &_handler_list() {
				static _handler_list_t inst;
				return inst;
			}
	};

	// used to release game resources during a halfway exit.
	class on_unload {
		public:
			on_unload() : _it(_handler_list().end()) {}

			on_unload(std::function<void()> handler) {
				if (!handler) {
					return;
				}
				_handler_list().emplace_back(std::move(handler));
				_it = --_handler_list().end();
			}

			~on_unload() {
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

			static void handle() {
				auto &li = _handler_list();
				for (auto rit = li.rbegin(); rit != li.rend(); ++rit) {
					(*rit)();
				}
			}

		private:
			using _handler_list_t = std::list<std::function<void()>>;

			_handler_list_t::iterator _it;

			static _handler_list_t &_handler_list() {
				static _handler_list_t inst;
				return inst;
			}
	};

	class on_load_task {
		public:
			on_load_task() = default;

			on_load_task(const std::function<void()> &handler) : _ol(on_load([handler]() {
				go(handler);
			})) {}

			operator bool() const {
				return _ol;
			}

			void del() {
				_ol.del();
			}

		private:
			on_load _ol;
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
