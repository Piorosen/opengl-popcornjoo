#include <iostream>
#include <gl/glut.h>

using namespace std;

#include "application.h"
#include "display.h"

static graphics::size displaySize;
static graphics::point mouseCursorPosition;

void graphics::keyboardEvent(unsigned char key, int x, int y) {

}

void graphics::renderEvent() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); 

	

	glutSwapBuffers();
}

void graphics::reshapeEvent(int x, int y) {


}

void timerTest(int value) {
	auto m = graphics::global::getMousePosition();
	cout << m.x << " " << m.y << endl;
	auto pm = graphics::info::primaryMonitor();

	double rad = (double)m.x / 180.0 * 3.141592;
	graphics::info::setPosition(graphics::point{
		m.x,
		(int)(sin(rad) * pm.size.height / 2 + pm.size.height / 2)
		});

	glutTimerFunc(10, timerTest, value);
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
	// Test
	glutTimerFunc(50, timerTest, 0);
	// 키보드 이벤트 등록
	glutKeyboardFunc(graphics::keyboardEvent);

	glutMainLoop();
}

// 싄나는 나의 개발 시간>< 얏호오>< 넘무 신나아앙