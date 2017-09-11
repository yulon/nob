#include <nob.hpp>

#include <list>
#include <forward_list>
#include <mutex>

namespace nob {
	struct _ftask {
		std::function<void()> handler;
		bool sleeping;
		bool pre_delete;
		struct {
			_ftask *ftask;
			PVOID fiber;
		} deleter;
	};
	std::list<_ftask *> _ftasks;
	std::list<_ftask *>::iterator _ftasks_it;
	std::list<_ftask *>::iterator _cur_ftask_it;

	uintptr_t add_frame_task(const std::function<void()> &handler) {
		auto ftask = new _ftask{handler, false, false, {NULL, NULL}};
		_ftasks.push_back(ftask);
		if (_ftasks_it == _ftasks.end()) {
			--_ftasks_it;
		}
		return (uintptr_t)ftask;
	}

	size_t _cur_tick;

	std::thread::id main_thread_id;

	PVOID _main_fiber;
	PVOID _cur_fiber;
	std::forward_list<PVOID> _idle_fibers;

	struct _sleeping {
		PVOID fiber;
		_ftask *ftask;
		size_t start_tick;
		size_t duration;
		std::function<bool()> cond;
	};
	std::list<_sleeping> _sleepings;

	static inline void _switch_fiber(PVOID fiber) {
		_cur_fiber = fiber;
		SwitchToFiber(fiber);
	}

	static inline void _wakeup_fiber(PVOID fiber) {
		_idle_fibers.push_front(_cur_fiber);
		_switch_fiber(fiber);
	}

	static inline void _handle_ftasks() {
		while (_ftasks_it != _ftasks.end()) {
			_cur_ftask_it = _ftasks_it++;
			(*_cur_ftask_it)->handler();
		}

		_cur_ftask_it = _ftasks.end();

		for (auto it = _sleepings.begin(); it != _sleepings.end(); ++it) {
			// if (_cur_tick < it->start_tick) then current,
			// if (_cur_tick == it->start_tick) then next.
			if (_cur_tick == it->start_tick) {
				continue;
			}
			if (it->cond) {
				if (!it->cond()) {
					continue;
				}
			} else if (_cur_tick < it->start_tick + it->duration) {
				continue;
			}

			if (it->ftask) {
				it->ftask->sleeping = false;

				if (it->ftask->pre_delete) {
					if (it->ftask->deleter.fiber) {
						_sleepings.push_back({it->ftask->deleter.fiber, it->ftask->deleter.ftask, 0, 0, nullptr});
					}
					delete it->ftask;
				} else {
					_ftasks.push_back(it->ftask);
					_cur_ftask_it = --_ftasks.end();
				}
			}

			auto fiber = it->fiber;
			_sleepings.erase(it);
			_wakeup_fiber(fiber);
			return;
		}

		_wakeup_fiber(_main_fiber);
	}

	VOID WINAPI _handle_ftasks_loop(PVOID p) {
		for (;;) {
			_handle_ftasks();
		}
	}

	static inline void _switch_idle_fiber() {
		PVOID fiber;
		if (_idle_fibers.empty()) {
			fiber = CreateFiber(0, (LPFIBER_START_ROUTINE)&_handle_ftasks_loop, NULL);
		} else {
			fiber = _idle_fibers.front();
			_idle_fibers.pop_front();
		}
		_switch_fiber(fiber);
	}

	static inline void _wait(_sleeping &&s) {
		if (_cur_ftask_it != _ftasks.end()) {
			s.ftask = *_cur_ftask_it;
			s.ftask->sleeping = true;
			_ftasks.erase(_cur_ftask_it);
		}
		s.start_tick = _cur_tick;
		_sleepings.push_back(s);
		_switch_idle_fiber();
	}

	void wait(size_t ms) {
		if (std::this_thread::get_id() != main_thread_id) {
			Sleep(!ms ? ms = 1 : ms);
			return;
		}
		_wait({_cur_fiber, nullptr, 0, ms, nullptr});
	}

	void wait(const std::function<bool()> &cond) {
		if (std::this_thread::get_id() != main_thread_id) {
			do {
				Sleep(1);
			} while (!cond);
			return;
		}
		_wait({_cur_fiber, nullptr, 0, 0, cond});
	}

	uintptr_t call_onmt(const std::function<uintptr_t()> &func) {
		if (std::this_thread::get_id() != main_thread_id) {
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

	void del_frame_task(uintptr_t id, bool wait_ran) {
		auto ftask = (_ftask *)id;

		if (ftask->sleeping) {
			ftask->pre_delete = true;

			if (wait_ran) {
				ftask->deleter.fiber = _cur_fiber;
				if (_cur_ftask_it != _ftasks.end()) {
					(*_cur_ftask_it)->sleeping = true;
					ftask->deleter.ftask = *_cur_ftask_it;
					_ftasks.erase(_cur_ftask_it);
				}
				_switch_idle_fiber();
			}
			return;
		}

		if (_cur_ftask_it != _ftasks.end() && ftask == *_cur_ftask_it) {
			_ftasks.erase(_cur_ftask_it);
			_cur_ftask_it = _ftasks.end();
			delete ftask;
			return;
		}

		for (auto it = _ftasks.begin(); it != _ftasks.end(); ++it) {
			if (*it == ftask) {
				_ftasks.erase(it);
				delete ftask;
				break;
			}
		}
	}

	bool has_frame_task(uintptr_t id) {
		auto ftask = (_ftask *)id;
		for (auto it = _ftasks.begin(); it != _ftasks.end(); ++it) {
			if (*it == ftask) {
				return true;
			}
		}
		for (auto it = _sleepings.begin(); it != _sleepings.end(); ++it) {
			if (it->ftask == ftask) {
				return true;
			}
		}
		return false;
	}

	namespace player {
		ntv::Player ntv_player;
	} /* player */

	uintptr_t _first_ftask;

	void _main() {
		main_thread_id = std::this_thread::get_id();

		for (auto it = _ftasks.begin(); it != _ftasks.end(); ) {
			delete *it;
			it = _ftasks.erase(it);
		}

		for (auto it = _sleepings.begin(); it != _sleepings.end(); ) {
			if (it->ftask->deleter.ftask) {
				delete it->ftask->deleter.ftask;
			}
			if (it->ftask->deleter.fiber) {
				DeleteFiber(it->ftask->deleter.fiber);
			}
			delete it->ftask;
			DeleteFiber(it->fiber);
			it = _sleepings.erase(it);
		}

		_main_fiber = _cur_fiber = GetCurrentFiber();

		player::ntv_player = ntv::PLAYER::PLAYER_ID();

		_cur_tick = GetTickCount();
		_ftasks_it = _ftasks.end();

		_first_ftask = add_frame_task([]() {
			main();
			del_frame_task(_first_ftask);
		});

		for (;;) {
			_switch_idle_fiber();

			shv::WAIT(0);
			_cur_tick = GetTickCount();
			_ftasks_it = _ftasks.begin();
		}
	}
} /* nob */
