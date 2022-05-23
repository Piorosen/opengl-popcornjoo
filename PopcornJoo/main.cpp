#include <gl/glut.h>
#include <vector>
#include <string>

#include "application.h"

#include "imagecollect.h"

//void reshape(int w, int h)
//{
//	glViewport(0, 0, w, h);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glOrtho(-5.0, 5.0, -5.0, 5.0, -5.0, 15.0);
//	gluPerspective(60.0, 1.0, 1.0, 20.0);
//}

std::vector<int> arrayData;

void keyboard(unsigned char key, int x, int y) {
	if (key == 'a') {
		arrayData.clear();
		for (int i = 0; i < 8; i++) {
			std::string title = "title00" + std::to_string(i) + ".png";
			arrayData.push_back(grc::imagecollect::shared->add(title));
		}
	}
}

int main(int argc, char** argv) {
	grc::application::shared->initialize(grc::size{ 500, 500 }, "차차의 모험기");

	grc::application::shared->run();
}