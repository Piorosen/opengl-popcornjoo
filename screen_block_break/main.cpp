#include <iostream>
#include <gl/glut.h>

#include "application.h"

void InitCallbackFunc() {
    // 창 크기 이벤트 등록
    glutReshapeFunc(graphics::ReshapeEvent);

    // 렌더링 이벤트 등록
    glutDisplayFunc(graphics::RenderEvent);

    // 키보드 이벤트 등록
    glutKeyboardFunc(graphics::KeyboardEvent);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutCreateWindow("개발! 와! 시작");
    
    InitCallbackFunc();
    glutMainLoop();
}