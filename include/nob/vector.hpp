#pragma once

#include <initializer_list>
#include <cmath>
#include <string>
#include <sstream>
#include <cstring>
#include <cmath>

namespace nob {
	struct vector2_i {
		int x, y;
	};

	struct vector2 {
		float x, y;

		vector2() = default;

		constexpr vector2(float x_val, float y_val = 0.0f) : x(x_val), y(y_val) {}

		/*vector2(std::initializer_list<float> vals) {
			if (vals.size()) {
				memcpy(&x, vals.begin(), vals.size() * sizeof(float));
			}
			if (vals.size() < 2) {
				memset(&x + vals.size(), 0, (2 - vals.size()) * sizeof(float));
			}
		}*/

		float distance(const vector2 &v2) const {
			return std::sqrt(
				std::pow((double)x - (double)v2.x, 2) +
				std::pow((double)y - (double)v2.y, 2)
			);
		}
	};

	struct vector3_wf {
		alignas(uintptr_t) float x, y, z;
	};

	inline float fix_angle(float a) {
		if (a > 180.f) {
			return -180.f + fmod(a - 180.f, 180.f);
		} else if (a < -180.f) {
			return 180.f - fmod(-180.f - a, 180.f);
		}
		return a;
	}

	struct vector3 : public vector2 {
		float z;

		vector3() = default;

		constexpr vector3(float x_val, float y_val = 0.0f, float z_val = 0.0f) : vector2(x_val, y_val), z(z_val) {}

		constexpr vector3(const vector2 &v2, float z_val = 0.0f) : vector2(v2), z(z_val) {}

		vector3(std::initializer_list<float> vals) {
			if (vals.size()) {
				memcpy(&x, vals.begin(), vals.size() * sizeof(float));
			}
			if (vals.size() < 3) {
				memset(&x + vals.size(), 0, (3 - vals.size()) * sizeof(float));
			}
		}

		constexpr vector3(const vector3_wf &nv3) : vector3(nv3.x, nv3.y, nv3.z) {}

		constexpr operator vector3_wf() const {
			return {x, y, z};
		}

		vector3 rotation_to_direction() const {
			float radians_z = z * 0.0174532924f;
			float radians_x = x * 0.0174532924f;
			float num = std::abs((float)std::cos((double)radians_x));

			return {
				(float)((double)((float)(-(float)std::sin((double)radians_z))) * (double)num),
				(float)((double)((float)std::cos((double)radians_z)) * (double)num),
				(float)std::sin((double)radians_x)
			};
		}

		vector3 rotation() const {
			return {
				fix_angle(x),
				fix_angle(y),
				fix_angle(z)
			};
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

	static inline vector3 operator*(const vector3 &a, const vector3 &b) {
		return {a.x * b.x, a.y * b.y, a.z * b.z};
	}

	static inline vector3 operator*(const vector3 &v3, float n) {
		return {v3.x * n, v3.y * n, v3.z * n};
	}

	static inline vector3 operator*(float n, const vector3 &v3) {
		return {v3.x * n, v3.y * n, v3.z * n};
	}

	static inline vector3 operator/(const vector3 &a, const vector3 &b) {
		return {a.x / b.x, a.y / b.y, a.z / b.z};
	}

	static inline vector3 operator/(const vector3 &v3, float n) {
		return {v3.x / n, v3.y / n, v3.z / n};
	}

	static inline vector3 operator/(float n, const vector3 &v3) {
		return {n / v3.x, n / v3.y, n / v3.z};
	}

	static inline vector3 operator+(const vector3 &a, const vector3 &b) {
		return {a.x + b.x, a.y + b.y, a.z + b.z};
	}

	static inline vector3 operator+(const vector3 &v3, float n) {
		return {v3.x + n, v3.y + n, v3.z + n};
	}

	static inline vector3 operator+(float n, const vector3 &v3) {
		return {v3.x + n, v3.y + n, v3.z + n};
	}

	static inline vector3 operator-(const vector3 &a, const vector3 &b) {
		return {a.x - b.x, a.y - b.y, a.z - b.z};
	}

	static inline vector3 operator-(const vector3 &v3, float n) {
		return {v3.x - n, v3.y - n, v3.z - n};
	}

	static inline vector3 operator-(float n, const vector3 &v3) {
		return {n - v3.x, n - v3.y, n - v3.z};
	}

	struct vector4 {
		float x, y, z, w;
	};
} /* nob */
