#include <nob.hpp>

#include <vector>

namespace nob {
	struct task {
		std::function<void()> handler;
		size_t dead_line;
		bool running;
	};
	std::vector<task> tasks;
	size_t cur_task_ix;

	void add_frame_task(const std::function<void()> &handler, int duration) {
		tasks.push_back({handler, duration > 0 ? GetTickCount() + duration : (duration == 0 ? 0 : 1), false});
	}

	void wait_next_frame() {
		while(cur_task_ix < tasks.size()) {
			if (!tasks[cur_task_ix].running) {
				switch (tasks[cur_task_ix].dead_line) {
					default:
						if (GetTickCount() > tasks[cur_task_ix].dead_line) {
							tasks.erase(tasks.begin() + cur_task_ix);
							continue;
						}
					case 1: {
						auto ix = cur_task_ix;
						++cur_task_ix;
						tasks[ix].running = true;
						tasks[ix].handler();
						tasks[ix].running = false;
						continue;
					}
					case 0: {
						auto handler = tasks[cur_task_ix].handler;
						tasks.erase(tasks.begin() + cur_task_ix);
						handler();
					}
				}
			} else {
				++cur_task_ix;
			}
		}
		cur_task_ix = 0;

		shv::WAIT(1);
	}

	void wait(size_t ms) {
		size_t dead_line = GetTickCount() + ms;
		for (;;) {
			wait_next_frame();
			if (GetTickCount() > dead_line) break;
		}
	}

	void _entry_point() {
		cur_task_ix = 0;

		main();

		for (;;) {
			wait_next_frame();
		}
	}
} /* nob */
