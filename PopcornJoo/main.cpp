#include <gl/glut.h>
#include <vector>
#include <string>
#include <spdlog/spdlog.h>

#include "application.h"
#include "imagecollect.h"
#include "spriteview.h"
#include "buttonview.h"

std::vector<int> arrayData;
int i = 0;

std::shared_ptr<grc::scene> getMainPage() {
	auto data = std::make_shared<grc::scene>();
	std::vector<int> im;
	for (int i = 0; i < 8; i++) {
		std::string title = "tile00" + std::to_string(i) + ".png";
		int value = grc::imagecollect::shared->add(title);
		im.push_back(value);
	}

	auto v = std::make_shared<grc::spriteview>(grc::rect{
			0, 0, 100, 100
		}, im);
	v->durationMS = 1000;

	auto v1 = std::make_shared<grc::spriteview>(grc::rect{
		100, 0, 100, 100
		}, im);
	v1->durationMS = 500;

	auto v2 = std::make_shared<grc::spriteview>(grc::rect{
		200, 0, 100, 100
		}, im);
	v2->durationMS = 250;

	auto b = std::make_shared<grc::buttonview>(grc::rect{
		0, 100, 300, 100
		});
	
	b->mouseEvent += [](grc::buttonview* self, grc::buttonstate state) {
		spdlog::info("Occur Event!!");
	};

	v->play();
	v1->play();
	v2->play();

	data->view.push_back(b);
	data->view.push_back(v);
	data->view.push_back(v1);
	data->view.push_back(v2);

	return data;
}

int main(int argc, char** argv) {
	grc::application::shared->initialize(grc::size{ 500, 500 }, "차차의 모험기");
	grc::application::shared->setScene(getMainPage());

	grc::application::shared->run();
}