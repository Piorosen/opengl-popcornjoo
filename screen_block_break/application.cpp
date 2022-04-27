#include <iostream>
#include <gl/glut.h>

using namespace std;

#include "application.h"
#include "display.h"

static graphics::size displaySize;
static graphics::point mouseCursorPosition;

void graphics::keyboardEvent(unsigned char key, int x, int y) {

}

int velX = 20;
int velY = 20;


void graphics::timerEvent(int value) {
	auto dPost = graphics::global::getDisplayPosition();
	auto dMPost = graphics::global::getMousePosition();
	auto dSize = graphics::global::getDisplaySize();
	auto mRect = graphics::info::primaryMonitor();

	// 오른쪽 충돌
	if (dPost.x + dSize.width + velX > mRect.size.width) {
		velX *= -1;
	}
	if (dPost.x + velX < mRect.point.x) {
		velX *= -1;
	}
	if (dPost.y + dSize.height + velX > mRect.size.height) {
		velY *= -1;
	}
	if (dPost.y + velX < mRect.point.y) {
		velY *= -1;
	}

	graphics::info::setMousePosition(point{
		dMPost.x,
		mRect.size.height - 100
		});

	if (dPost.x < dMPost.x && dMPost.x < dPost.x + dSize.width &&
		dPost.y < dMPost.y && dMPost.y < dPost.y + dSize.height) {
		velX *= -1;
		velY = -20;
	}

	graphics::info::setPosition(graphics::point{
		dPost.x + velX,
		dPost.y + velY
		});

	glutTimerFunc(25, graphics::timerEvent, 0);
}


void graphics::renderEvent() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); 

	

	glutSwapBuffers();
}

void graphics::reshapeEvent(int x, int y) {


}


graphics::size graphics::global::getDisplaySize() {
	return displaySize;
}

graphics::point graphics::global::getDisplayPosition() {
	return graphics::info::getPosition();
}

graphics::point graphics::global::getMousePosition() {
	return graphics::info::getMousePosition();
}


void graphics::initDisplay(int* argc, char** argv, 
						   size display, std::string title) {
	displaySize = display;
	glutInit(argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow(title.c_str());

	glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
	auto pMonitor = graphics::info::primaryMonitor();
	graphics::info::setPosition(graphics::point{
		pMonitor.size.width / 2 - display.width / 2,
		pMonitor.size.height / 2 - display.height / 2
	});

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, display.width, display.height, 0);

	// 창 크기 이벤트 등록
	glutReshapeFunc(graphics::reshapeEvent);
	// 렌더링 이벤트 등록
	glutDisplayFunc(graphics::renderEvent);
	// 키보드 이벤트 등록
	glutKeyboardFunc(graphics::keyboardEvent);

	glutTimerFunc(50, graphics::timerEvent, 0);

	glutMainLoop();
}

// 싄나는 나의 개발 시간>< 얏호오>< 넘무 신나아앙