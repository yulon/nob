#pragma once

#include "vector.hpp"
#include "color.hpp"
#include "script.hpp"

#include <memory>
#include <cassert>

namespace nob {
	namespace g3d {
		class cylinder {
			public:
				cylinder() : _data(std::make_shared<_data_t>()) {}

				void move(const vector3 &center) {
					_data->ctr = center;
				}

				void height(float h) {
					_data->h = h;
				}

				void radius(float r) {
					_data->r = r;
				}

				void cap(bool toggle) {
					_data->cap = toggle;
				}

				void color(const rgba<int> &clr) {
					_data->clr = clr;
				}

				void alpha(float a) {
					auto clr = _data->clr;
					clr.a = a;
					color(clr);
				}

				void show(bool toggle = true);

				void draw() const;

			private:
				struct _data_t {
					vector3 ctr;
					float h, r;
					rgba<int> clr;
					bool cap = true;
					task draw_tsk;

					~_data_t() {
						if (!this_script::is_exiting) {
							assert(in_this_script());
							if (draw_tsk) {
								draw_tsk.del();
							}
						}
					}
				};

				std::shared_ptr<_data_t> _data;
		};
	} /* g3d */
} /* nob */
