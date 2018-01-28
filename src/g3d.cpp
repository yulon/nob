#include <nob/g3d.hpp>
#include <nob/ntv.hpp>

namespace nob {
	namespace g3d {
		void cylinder::color(const rgba<int> &clr) {
			_data->clr = clr;
			if (clr.a) {
				if (_data->draw_tsk) {
					return;
				}
				const auto &d = _data;
				_data->draw_tsk = task([d]() {
					size_t petal_count = static_cast<size_t>(d->r * 0.1);
					float ang_off = 360.0f / petal_count;
					float ang_off_half = ang_off / 2.0f;
					for (size_t i = 0; i < petal_count; ++i) {
						vector3 rot{0, 0, i * ang_off};
						auto top = d->ctr.forward(rot, d->r);

						rot.z += ang_off_half;
						auto ll = d->ctr.forward(rot, d->r);

						rot.z -= ang_off;
						auto lr = d->ctr.forward(rot, d->r);

						ntv::GRAPHICS::DRAW_POLY(
							top.x, top.y, d->h,
							ll.x, ll.y, d->ctr.z,
							lr.x, lr.y, d->ctr.z,
							d->clr.r, d->clr.g, d->clr.b, d->clr.a
						);

						ntv::GRAPHICS::DRAW_POLY(
							top.x, top.y, d->h,
							lr.x, lr.y, d->ctr.z,
							ll.x, ll.y, d->ctr.z,
							d->clr.r, d->clr.g, d->clr.b, d->clr.a
						);

						rot.z -= ang_off_half;
						ll = d->ctr.forward(rot, d->r);

						ntv::GRAPHICS::DRAW_POLY(
							top.x, top.y, d->h,
							lr.x, lr.y, d->ctr.z,
							ll.x, ll.y, d->h,
							d->clr.r, d->clr.g, d->clr.b, d->clr.a
						);

						ntv::GRAPHICS::DRAW_POLY(
							top.x, top.y, d->h,
							ll.x, ll.y, d->h,
							lr.x, lr.y, d->ctr.z,
							d->clr.r, d->clr.g, d->clr.b, d->clr.a
						);

						if (d->cap) {
							ntv::GRAPHICS::DRAW_POLY(
								d->ctr.x, d->ctr.y, d->h,
								top.x, top.y, d->h,
								ll.x, ll.y, d->h,
								d->clr.r, d->clr.g, d->clr.b, d->clr.a
							);

							ntv::GRAPHICS::DRAW_POLY(
								d->ctr.x, d->ctr.y, d->h,
								ll.x, ll.y, d->h,
								top.x, top.y, d->h,
								d->clr.r, d->clr.g, d->clr.b, d->clr.a
							);

							ntv::GRAPHICS::DRAW_POLY(
								d->ctr.x, d->ctr.y, d->ctr.z,
								ll.x, ll.y, d->ctr.z,
								top.x, top.y, d->ctr.z,
								d->clr.r, d->clr.g, d->clr.b, d->clr.a
							);

							ntv::GRAPHICS::DRAW_POLY(
								d->ctr.x, d->ctr.y, d->ctr.z,
								top.x, top.y, d->ctr.z,
								ll.x, ll.y, d->ctr.z,
								d->clr.r, d->clr.g, d->clr.b, d->clr.a
							);
						}
					}
				});
			} else if (_data->draw_tsk) {
				_data->draw_tsk.del();
			}
		}
	} /* g3d */
} /* nob */
