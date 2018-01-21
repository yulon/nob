#pragma once

#include <initializer_list>
#include <cmath>
#include <string>

namespace nob {
	struct vector2_i {
		int x, y;
	};

	struct vector2 {
		float x, y;
	};

	#ifndef _NOB_NTV_VEC3
		#define _NOB_NTV_VEC3
		namespace ntv {
			struct Vector3 {
				alignas(uintptr_t) float x, y, z;
			};
		}
	#endif

	struct vector3 {
		float x, y, z;

		vector3() = default;

		constexpr vector3(float x_val, float y_val, float z_val = 0) : x(x_val), y(y_val), z(z_val) {}

		constexpr vector3(std::initializer_list<float> vals) : x(*vals.begin()), y(vals.begin()[1]), z(vals.begin()[2]) {}

		constexpr vector3(const ntv::Vector3 &nv3) : x(nv3.x), y(nv3.y), z(nv3.z) {}

		constexpr operator ntv::Vector3() const {
			return {x, y, z};
		}

		vector3 rot_to_dir() const {
			float radians_z = z * 0.0174532924f;
			float radians_x = x * 0.0174532924f;
			float num = std::abs((float)std::cos((double)radians_x));

			vector3 dir;
			dir.x = (float)((double)((float)(-(float)std::sin((double)radians_z))) * (double)num);
			dir.y = (float)((double)((float)std::cos((double)radians_z)) * (double)num);
			dir.z = (float)std::sin((double)radians_x);
			return dir;
		}

		vector3 operator*(float x) const {
			vector3 result = *this;

			result.x *= x;
			result.y *= x;
			result.z *= x;

			return result;
		}

		vector3 operator+(const vector3 &v3) const {
			vector3 result = *this;

			result.x += v3.x;
			result.y += v3.y;
			result.z += v3.z;

			return result;
		}

		vector3 offset(const vector3 &rot, float distance = 10.0f) const {
			return *this + (rot.rot_to_dir() * distance);
		}

		std::string str() const {
			std::stringstream ss;
			ss << "X: " << x << ", Y: " << y << ", Z: " << z;
			return ss.str();
		}
	};

	struct vector4 {
		float x, y, z, w;
	};
} /* nob */
