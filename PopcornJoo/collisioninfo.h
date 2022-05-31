#pragma once

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

		collisionPos own;
		collisionPos other;
	};
}