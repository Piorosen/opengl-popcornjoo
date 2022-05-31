#pragma once
#include <vector>

namespace phy {
	enum class collidetype {
		circleTocircle,
		circleToRect,
		RectToRect
	};
	enum class collisionPos {
		none,
		top,
		left,
		right,
		bottom
	};
	struct collisioninfo {
		collidetype type;

		std::vector<collisionPos> own;
		std::vector<collisionPos> other;
	};
}