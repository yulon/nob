#pragma once

#include <functional>
#include <thread>

namespace nob {
	namespace this_script {
		extern std::thread::id thread_id;
		extern bool running;
		extern bool asi_mode;
	} /* this_script */

	void wait(size_t ms);
	inline void wait_next_frame() { wait(0); }
	void wait(const std::function<bool()> &cond);

	void wait_s(size_t ms);
	inline void wait_next_frame_s() { wait_s(0); }
	void wait_s(const std::function<bool()> &cond);

	class task {
		public:
			task(const std::function<void()> &);

			task(const std::function<void(task)> &);

			operator bool() const;

			void del();

			////////////////////////////////////////////////////////////////////

			struct _info; _info *_inf; constexpr task(_info *p = nullptr) : _inf(p) {}
	};

	task this_task();

	class initer {
		public:
			initer(const std::function<void()> &);
			initer(const std::function<void(initer)> &);
	};

	// Call on non-main thread
	uintptr_t call_onmt(const std::function<uintptr_t()> &);
} /* nob */
