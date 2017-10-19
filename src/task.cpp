#include <nob.hpp>
#include <nob/shv/main.hpp>

#include <windows.h>

#include <list>
#include <stack>
#include <mutex>
#include <memory>
#include <cassert>
#include <iostream>

namespace nob {
	namespace this_script {
		std::thread::id thread_id;
		bool running = false;

		static inline void _wait(size_t ms) {
			if (asi_mode) {
				shv::WAIT(ms);
			} else {
				ntv::SYSTEM::WAIT(ms);
			}
		}

		PVOID _main_fiber = nullptr;
		PVOID _cur_fiber;
	} /* this_script */

	struct task::_info {
		std::function<void()> handler;
		bool sleeping;
	};

	std::list<task> _tasks;
	std::list<task>::iterator _tasks_it;
	std::list<task>::iterator _cur_task_it;

	task this_task() {
		assert(std::this_thread::get_id() == this_script::thread_id && this_script::running && GetCurrentFiber() == this_script::_cur_fiber);

		return *_cur_task_it;
	}

	std::list<task> _pre_add_tasks;
	std::mutex _pre_add_tasks_mtx;

	task::task(const std::function<void()> &handler) {
		_inf = new task::_info{handler, false};

		if (std::this_thread::get_id() == this_script::thread_id) {
			_tasks.push_back(*this);
			if (_tasks_it == _tasks.end()) {
				--_tasks_it;
			}
		} else {
			_pre_add_tasks_mtx.lock();
			_pre_add_tasks.push_back(*this);
			_pre_add_tasks_mtx.unlock();
		}
	}

	task::task(const std::function<void(task)> &handler) : task([handler]() {
		handler(*_cur_task_it);
	}) {}

	size_t _cur_tick = 0;

	std::stack<PVOID> _idle_task_fibers;

	struct _sleeping_task {
		PVOID fiber;
		task task;
		size_t start_tick;
		size_t duration;
		std::function<bool()> cond;
	};

	std::list<_sleeping_task> _sleeping_tasks;

	static inline void _switch_fiber(PVOID fiber) {
		this_script::_cur_fiber = fiber;
		SwitchToFiber(fiber);
	}

	static inline void _wakeup_fiber(PVOID fiber) {
		_idle_task_fibers.push(this_script::_cur_fiber);
		_switch_fiber(fiber);
	}

	VOID WINAPI _handle_tasks_loop(PVOID) {
		for (;;) {
			while (_tasks_it != _tasks.end()) {
				_cur_task_it = _tasks_it++;
				_cur_task_it->_inf->handler();
			}
			_wakeup_fiber(this_script::_main_fiber);
		}
	}

	static inline void _start_new_task_fiber() {
		PVOID fiber;
		if (_idle_task_fibers.empty()) {
			fiber = CreateFiber(0, (LPFIBER_START_ROUTINE)&_handle_tasks_loop, nullptr);
		} else {
			fiber = _idle_task_fibers.top();
			_idle_task_fibers.pop();
		}
		_switch_fiber(fiber);
	}

	static inline void _sleep(_sleeping_task &&pre_st) {
		_tasks.erase(_cur_task_it);
		pre_st.task._inf->sleeping = true;
		_sleeping_tasks.push_front(std::move(pre_st));
		_start_new_task_fiber();
	}

	void wait(size_t ms) {
		assert(std::this_thread::get_id() == this_script::thread_id && this_script::running && GetCurrentFiber() == this_script::_cur_fiber);

		_sleep({this_script::_cur_fiber, *_cur_task_it, _cur_tick, ms, nullptr});
	}

	void wait(const std::function<bool()> &cond) {
		assert(std::this_thread::get_id() == this_script::thread_id && this_script::running && GetCurrentFiber() == this_script::_cur_fiber);

		_sleep({this_script::_cur_fiber, *_cur_task_it, _cur_tick, 0, cond});
	}

	void wait_s(size_t ms) {
		if (std::this_thread::get_id() != this_script::thread_id || !this_script::running) {
			Sleep(!ms ? ms = 1 : ms);
			return;
		}
		if (GetCurrentFiber() == this_script::_main_fiber) {
			this_script::_wait(ms);
			return;
		}
		_sleep({this_script::_cur_fiber, *_cur_task_it, _cur_tick, ms, nullptr});
	}

	void wait_s(const std::function<bool()> &cond) {
		if (std::this_thread::get_id() != this_script::thread_id || !this_script::running) {
			do {
				Sleep(1);
			} while (!cond);
			return;
		}
		if (GetCurrentFiber() == this_script::_main_fiber) {
			do {
				this_script::_wait(0);
			} while (!cond);
			return;
		}
		_sleep({this_script::_cur_fiber, *_cur_task_it, _cur_tick, 0, cond});
	}

	uintptr_t call_onmt(const std::function<uintptr_t()> &func) {
		if (std::this_thread::get_id() != this_script::thread_id) {
			return func();
		}

		auto mtx = new std::mutex;
		auto done = new bool(false);
		auto result = new uintptr_t;

		std::thread([mtx, done, result, func]() {
			mtx->lock();
			*result = func();
			*done = true;
			mtx->unlock();
		}).detach();

		wait([mtx, done]()->bool {
			if (mtx->try_lock()) {
				auto done_cp = *done;
				mtx->unlock();
				return done_cp;
			}
			return false;
		});

		auto r = *result;
		delete mtx;
		delete done;
		delete result;
		return r;
	}

	std::unique_ptr<task::_info> _task_info_ptr_trash;

	void task::del() {
		if (_inf) {
			if (_inf == _cur_task_it->_inf) {
				_tasks.erase(_cur_task_it);

				_task_info_ptr_trash.reset(_inf);
				_inf = nullptr;
				return;
			}

			if (_inf->sleeping) {
				for (auto it = _sleeping_tasks.begin(); it != _sleeping_tasks.end(); ++it) {
					if (it->task._inf == _inf) {
						_sleeping_tasks.erase(it);

						delete _inf;
						_inf = nullptr;
						return;
					}
				}
			}

			for (auto it = _tasks.begin(); it != _tasks.end(); ++it) {
				if (it->_inf == _inf) {
					if (it == _tasks_it) {
						_tasks_it = _tasks.erase(it);
					} else {
						_tasks.erase(it);
					}

					delete _inf;
					_inf = nullptr;
					return;
				}
			}

			_inf = nullptr;
		}
	}

	task::operator bool() const {
		if (_inf) {
			if (_inf == _cur_task_it->_inf) {
				return true;
			}

			if (_inf->sleeping) {
				for (auto it = _sleeping_tasks.begin(); it != _sleeping_tasks.end(); ++it) {
					if (it->task._inf == _inf) {
						return true;
					}
				}
			}

			for (auto it = _tasks.begin(); it != _tasks.end(); ++it) {
				if (it->_inf == _inf) {
					return true;
				}
			}
		}
		return false;
	}

	std::vector<std::function<void()>> _initers;

	initer::initer(const std::function<void()> &handler) {
		_initers.push_back(handler);
	}

	namespace player {
		ntv::Player ntv_player;
	} /* player */

	namespace window {
		void _hook_proc();
	} /* window */

	std::list<std::function<void()>> _input_events;

	namespace this_script {
		void _main() {
			player::ntv_player = ntv::PLAYER::PLAYER_ID();

			thread_id = std::this_thread::get_id();

			_cur_fiber = GetCurrentFiber();
			if (!_cur_fiber) {
				_main_fiber = _cur_fiber = ConvertThreadToFiber(nullptr);
			} else {
				_main_fiber = _cur_fiber;
			}

			_task_info_ptr_trash.reset(nullptr);

			window::_hook_proc();

			for (auto &handler : _initers) {
				task([&handler]() {
					handler();
					_cur_task_it->del();
				});
			}

			_tasks_it = _tasks.end();

			model::banned_vehicles.resize(0);

			_input_events.resize(0);

			for (;;) {
				running = true;
				_cur_tick = GetTickCount();

				for (auto it = _input_events.begin(); it != _input_events.end(); it = _input_events.erase(it)) {
					const auto &_input_event = *it;
					task([_input_event]() {
						_input_event();
						_cur_task_it->del();
					});
				}

				if (_pre_add_tasks_mtx.try_lock()) {
					for (auto it = _pre_add_tasks.begin(); it != _pre_add_tasks.end(); it = _pre_add_tasks.erase(it)) {
						_tasks.push_back(*it);
					}
					_pre_add_tasks_mtx.unlock();
				}

				for (auto it = _sleeping_tasks.begin(); it != _sleeping_tasks.end();) {
					if (it->cond) {
						if (!it->cond()) {
							++it;
							continue;
						}
					} else if (_cur_tick <= it->start_tick + it->duration) {
						++it;
						continue;
					}

					it->task._inf->sleeping = false;
					_tasks.push_back(it->task);
					_cur_task_it = --_tasks.end();

					auto fiber = it->fiber;
					it = _sleeping_tasks.erase(it);
					_wakeup_fiber(fiber);
				}

				_tasks_it = _tasks.begin();
				_start_new_task_fiber();

				running = false;
				_wait(0);
			}
		}
	} /* this_script */
} /* nob */
