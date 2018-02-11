#pragma once

#include <initializer_list>
#include <cmath>
#include <string>
#include <sstream>

namespace nob {
	struct vector2_i {
		int x, y;
	};

	struct vector2 {
		float x, y;

		vector2() = default;

		constexpr vector2(float x_val, float y_val) : x(x_val), y(y_val) {}

		constexpr vector2(std::initializer_list<float> vals) :
			x(vals.size() ? *vals.begin() : 0.0f),
			y(vals.size() >= 2 ? vals.begin()[1] : 0.0f)
		{}

		float distance(const vector2 &v2) const {
			return std::sqrt(
				std::pow((double)x - (double)v2.x, 2) +
				std::pow((double)y - (double)v2.y, 2)
			);
		}
	};

	#ifndef _NOB_NTV_VEC3
		#define _NOB_NTV_VEC3
		namespace ntv {
			struct Vector3 {
				alignas(uintptr_t) float x, y, z;
			};
		}
	#endif

	struct vector3 : public vector2 {
		float z;

		vector3() = default;

		constexpr vector3(float x_val, float y_val, float z_val = 0.0f) : vector2(x_val, y_val), z(z_val) {}

		constexpr vector3(const vector2 &v2, float z_val = 0.0f) : vector2(v2), z(z_val) {}

		constexpr vector3(std::initializer_list<float> vals) :
			vector2(vals),
			z(vals.size() >= 3 ? vals.begin()[2] : 0.0f)
		{}

		constexpr vector3(const ntv::Vector3 &nv3) : vector3(nv3.x, nv3.y, nv3.z) {}

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

		vector3 operator-(const vector3 &v3) const {
			vector3 result = *this;

			result.x -= v3.x;
			result.y -= v3.y;
			result.z -= v3.z;

			return result;
		}

		vector3 forward(const vector3 &rot, float distance = 10.0f) const {
			return *this + (rot.rot_to_dir() * distance);
		}

		float distance(const vector3 &v3) const {
			return std::sqrt(
				std::pow((double)x - (double)v3.x, 2) +
				std::pow((double)y - (double)v3.y, 2) +
				std::pow((double)z - (double)v3.z, 2)
			);
		}

		std::string str() const {
			std::stringstream ss;
			ss << "{ " << x << ", " << y << ", " << z << " }";
			return ss.str();
		}
	};

	struct vector4 {
		float x, y, z, w;
	};
} /* nob */
