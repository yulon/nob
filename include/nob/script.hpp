#pragma once

#include <rua/fiber.hpp>
#include <rua/macros.hpp>
#include <rua/sched.hpp>
#include <rua/sync.hpp>
#include <rua/types.hpp>

#include <atomic>
#include <functional>
#include <memory>
#include <thread>

namespace nob {

namespace this_script {

enum class mode_t { not_loaded, shv, ysc, main_thread, unique_thread };

extern mode_t mode;
extern size_t load_count;
extern std::atomic<size_t> load_count_s;
extern std::atomic<std::thread::id> thread_id;
extern std::atomic<bool> is_exiting;

} // namespace this_script

using ms = rua::ms;

class task {
public:
	task(std::nullptr_t = nullptr) : _cp_tsk() {}

	task(std::function<void()> handler, ms duration = rua::duration_max()) {
		_cp_tsk = executor().execute(std::move(handler), duration);
	}

	operator bool() const {
		return static_cast<bool>(_cp_tsk);
	}

	void del() {
		_cp_tsk.stop();
	}

	void reset_lifetime(ms duration = 0) {
		_cp_tsk.reset_lifetime(duration);
	}

	static rua::fiber_executor &executor() {
		static rua::fiber_executor inst;
		return inst;
	}

private:
	rua::fiber _cp_tsk;
};

inline task go(const std::function<void()> &handler) {
	return task(handler, 0);
}

inline bool in_this_script() {
	return std::this_thread::get_id() == this_script::thread_id;
}

namespace this_task {

inline void del() {
	task::executor().executing().stop();
}

inline void reset_lifetime(ms duration) {
	task::executor().executing().reset_lifetime(duration);
}

} // namespace this_task

inline void sleep(ms duration) {
	rua::sleep(duration);
}

inline void yield() {
	rua::yield();
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

	on_load(const on_load &) = delete;

	on_load &operator=(const on_load &) = delete;

	on_load(on_load &&src) : _it(src._it) {
		auto &li = _handler_list();
		if (src._it != li.end()) {
			src._it = li.end();
		}
	}

	on_load &operator=(on_load &&src) {
		del();
		auto &li = _handler_list();
		if (src._it != li.end()) {
			_it = src._it;
			src._it = li.end();
		}
		return *this;
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

	on_unload(const on_unload &) = delete;

	on_unload &operator=(const on_unload &) = delete;

	on_unload(on_unload &&src) : _it(src._it) {
		auto &li = _handler_list();
		if (src._it != li.end()) {
			src._it = li.end();
		}
	}

	on_unload &operator=(on_unload &&src) {
		del();
		auto &li = _handler_list();
		if (src._it != li.end()) {
			_it = src._it;
			src._it = li.end();
		}
		return *this;
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

	on_load_task(const std::function<void()> &handler) :
		_ol(on_load([handler]() { go(handler); })) {}

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
using chan = rua::chan<T>;

void terminate_unimportant_scripts();
} // namespace nob
