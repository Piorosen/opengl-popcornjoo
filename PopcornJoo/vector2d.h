#pragma once
#include <cmath>

namespace phy {
	struct vector2d {
		double x, y;

		vector2d operator-(const vector2d& other) const {
			return vector2d{ x - other.x, y - other.y };
		}
		vector2d operator+(const vector2d& other) const {
			return vector2d{ x - other.x, y - other.y };
		}
		vector2d operator/(const double& other) const {
			return vector2d{ x / other, y / other };
		}
		vector2d operator*(const double& other) const {
			return vector2d{ x * other, y * other };
		}
		double magnitude() const {
			return sqrt(pow(x, 2) + 
						   pow(y, 2));
		}
		vector2d normalization() const {
			return (*this) / magnitude();
		}

	};
}