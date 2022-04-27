#include <gl/glut.h>

#include "display.h"

static graphics::rect globalRectPrimaryMonitor;

// ��ȣ �ų��� OPENGL!!!! ����������
graphics::rect graphics::info::primaryMonitor() {
	if (globalRectPrimaryMonitor.size.width == 0) {
		globalRectPrimaryMonitor.point.x = 0;
		globalRectPrimaryMonitor.point.y = 0;
		globalRectPrimaryMonitor.size.width = glutGet(GLUT_SCREEN_WIDTH);
		globalRectPrimaryMonitor.size.height = glutGet(GLUT_SCREEN_HEIGHT);
	}

	return globalRectPrimaryMonitor;
}

static graphics::point displayPosition;
void graphics::info::setPosition(const graphics::point& pt) {
	displayPosition = pt;
	glutPositionWindow(pt.x, pt.y);
}

graphics::point graphics::info::getPosition() {
	return displayPosition;
}

void graphics::info::setMousePosition(const graphics::point& pt) {
	SetCursorPos(pt.x, pt.y);
}

graphics::point graphics::info::getMousePosition() {
	POINT pt = POINT();
	GetCursorPos(&pt);
	return graphics::point{
		pt.x,
		pt.y
	};
}