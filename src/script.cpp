#include <nob/script.hpp>
#include <nob/ntv.hpp>
#include <nob/model.hpp>

#include <nob/shv/main.hpp>

#include <windows.h>

#include <queue>
#include <iostream>

namespace nob {
	namespace this_script {
		std::thread::id thread_id;
		bool asi_mode = false;

		static inline void _wait(size_t ms) {
			if (asi_mode) {
				shv::WAIT(ms);
			} else {
				ntv::SYSTEM::WAIT(ms);
			}
		}
	} /* this_script */

	tmd::coro_pool _cp;

	bool in_task() {
		return _cp.in_task();
	}

	void del_this_task() {
		_cp.del_this_task();
	}

	task::task(const std::function<void()> &handler, int life_duration) :
		_cp_tsk(_cp.add_task(handler, life_duration))
	{}

	task go(const std::function<void()> &handler) {
		return task(handler, 0);
	}

	void wait(size_t ms) {
		_cp.wait(ms);
	}

	void wait(const std::function<bool()> &cond) {
		_cp.wait(cond);
	}

	void task::del() {
		_cp.del_task(_cp_tsk);
		_cp_tsk.reset();
	}

	task::operator bool() const {
		return _cp_tsk && _cp.has_task(_cp_tsk);
	}

	std::vector<std::function<void()>> _initers;

	initer::initer(const std::function<void()> &handler) {
		_initers.push_back(handler);
	}

	namespace window {
		void _hook_proc();
	} /* window */

	std::queue<std::function<void()>> _input_events;

	namespace this_script {
		void _main() {
			window::_hook_proc();

			for (auto &handler : _initers) {
				go(handler);
			}

			model::banned_vehicles.resize(0);

			while (_input_events.size()) {
				_input_events.pop();
			}

			_cp.handle_tasks([]() {
				_wait(0);

				while (_input_events.size()) {
					go(_input_events.front());
					_input_events.pop();
				}
			});
		}
	} /* this_script */
} /* nob */
