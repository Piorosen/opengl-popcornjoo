#pragma once
#include <memory>
#include <spdlog/spdlog.h>

#include "scene.h"

#include "audiocollect.h"
#include "imagecollect.h"
#include "spriteview.h"
#include "buttonview.h"

int tutorialImageIndex = 0;
std::shared_ptr<grc::scene> getHelpScene(std::function<void()> close) {
	auto data = std::make_shared<grc::scene>();
	std::vector<int> tutorial;
	for (int i = 0; i < 2; i++) {
		tutorial.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\00" + std::to_string(i) + ".png"));
	}

	grc::audiocollect::shared->add(".\\resources\\audio\\button.mp3");
	int nextImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\next.png");
	int homeImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\home.png");

	auto background = std::make_shared<grc::view>(grc::rect{
		0,0, 1280, 800
		}, tutorial[0]);

	auto nextButton = std::make_shared<grc::buttonview>(grc::rect(1180, 700, 1180 + 68, 700 + 61), nextImage, nextImage, nextImage);
	auto homeButton = std::make_shared<grc::buttonview>(grc::rect(990, 697, 990 + 252, 697 + 73), homeImage, homeImage, homeImage);

	nextButton->mouseEvent = [background, tutorial, homeButton](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			grc::audiocollect::shared->play(".\\resources\\audio\\button.mp3");
			tutorialImageIndex += 1;

			self->setHidden(true);
			homeButton->setHidden(false);

			background->backgroundImage = tutorial[tutorialImageIndex % tutorial.size()];
		}
	};

	homeButton->mouseEvent = [background, tutorial](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			grc::audiocollect::shared->play(".\\resources\\audio\\button.mp3");
		}
	};

	int backImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\back.png");
	auto backButton = std::make_shared<grc::buttonview>(grc::rect(30, 45, 30 + 144, 45 + 74), backImage, backImage, backImage);
	backButton->mouseEvent = [close](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			grc::audiocollect::shared->play(".\\resources\\audio\\button.mp3");
			if (close) {
				close();
			}
		}
	};

	data->view.push_back(background);
	data->view.push_back(backButton);

	data->view.push_back(nextButton);
	data->view.push_back(homeButton);

	data->openEvent = [](std::weak_ptr<grc::scene> data) {
		tutorialImageIndex = 0;
		auto weakData = data.lock();
		weakData->view[2]->setHidden(false);
		weakData->view[3]->setHidden(true);

		grc::application::shared->setSize(grc::size{ 1280, 800 });
		grc::application::shared->setTitle("차차의 모험기 : 사용법");
	};

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			if (close) {
				close();
			}
		}
	};
	
	return data;
}