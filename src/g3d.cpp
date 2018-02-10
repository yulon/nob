#include <nob/g3d.hpp>
#include <nob/ntv.hpp>

namespace nob {
	namespace g3d {
		void cylinder::draw() const {
			size_t petal_count = static_cast<size_t>(_data->r * 0.1f);
			float ang_off = 360.0f / petal_count;
			float ang_off_half = ang_off / 2.0f;
			for (size_t i = 0; i < petal_count; ++i) {
				vector3 rot{0, 0, i * ang_off};
				auto top = _data->ctr.forward(rot, _data->r);

				rot.z += ang_off_half;
				auto ll = _data->ctr.forward(rot, _data->r);

				rot.z -= ang_off;
				auto lr = _data->ctr.forward(rot, _data->r);

				ntv::GRAPHICS::DRAW_POLY(
					top.x, top.y, _data->h,
					ll.x, ll.y, _data->ctr.z,
					lr.x, lr.y, _data->ctr.z,
					_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
				);

				ntv::GRAPHICS::DRAW_POLY(
					top.x, top.y, _data->h,
					lr.x, lr.y, _data->ctr.z,
					ll.x, ll.y, _data->ctr.z,
					_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
				);

				rot.z -= ang_off_half;
				ll = _data->ctr.forward(rot, _data->r);

				ntv::GRAPHICS::DRAW_POLY(
					top.x, top.y, _data->h,
					lr.x, lr.y, _data->ctr.z,
					ll.x, ll.y, _data->h,
					_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
				);

				ntv::GRAPHICS::DRAW_POLY(
					top.x, top.y, _data->h,
					ll.x, ll.y, _data->h,
					lr.x, lr.y, _data->ctr.z,
					_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
				);

				if (_data->cap) {
					ntv::GRAPHICS::DRAW_POLY(
						_data->ctr.x, _data->ctr.y, _data->h,
						top.x, top.y, _data->h,
						ll.x, ll.y, _data->h,
						_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
					);

					ntv::GRAPHICS::DRAW_POLY(
						_data->ctr.x, _data->ctr.y, _data->h,
						ll.x, ll.y, _data->h,
						top.x, top.y, _data->h,
						_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
					);

					ntv::GRAPHICS::DRAW_POLY(
						_data->ctr.x, _data->ctr.y, _data->ctr.z,
						ll.x, ll.y, _data->ctr.z,
						top.x, top.y, _data->ctr.z,
						_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
					);

					ntv::GRAPHICS::DRAW_POLY(
						_data->ctr.x, _data->ctr.y, _data->ctr.z,
						top.x, top.y, _data->ctr.z,
						ll.x, ll.y, _data->ctr.z,
						_data->clr.r, _data->clr.g, _data->clr.b, _data->clr.a
					);
				}
			}
		}

		void cylinder::show(bool toggle) {
			if (toggle) {
				if (_data->draw_tsk) {
					return;
				}
				auto th1s = *this;
				_data->draw_tsk = task([th1s]() {
					th1s.draw();
				});
			} else if (_data->draw_tsk) {
				_data->draw_tsk.del();
			}
		}
	} /* g3d */
} /* nob */
