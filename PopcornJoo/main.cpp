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
int i = 0;

std::shared_ptr<grc::scene> getMainPage() {
	auto data = std::make_shared<grc::scene>();
	for (int i = 0; i < 8; i++) {
		std::string title = "tile00" + std::to_string(i) + ".png";
		int value = grc::imagecollect::shared->add(title);
		auto v = std::make_shared<grc::view>(grc::rect{
			0, 0, 100, 100
			}, value);
		v->setHidden(true);

		data->view.push_back(v);
	}

	data->keyboard = [](grc::scene* self, int button, int x, int y) {
		self->view[i % 8]->setHidden(true);
		i += 1;
		self->view[i % 8]->setHidden(false);
	};

	return data;
}

int main(int argc, char** argv) {
	grc::application::shared->initialize(grc::size{ 500, 500 }, "차차의 모험기");
	grc::application::shared->setScene(getMainPage());

	grc::application::shared->run();
}