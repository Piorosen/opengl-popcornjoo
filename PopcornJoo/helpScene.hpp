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
	for (int i = 1; i < 5; i++) {
		tutorial.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\00" + std::to_string(i) + ".png"));
	}
	
	grc::audiocollect::shared->add(".\\resources\\audio\\button.mp3");

	int rde = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\left_default.png");
	int rdwn = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\left_down.png");
	int rh = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\left_hover.png");

	int lde = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\right_default.png");
	int ldwn = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\right_down.png");
	int lh = grc::imagecollect::shared->add(".\\resources\\imaegs\\tutorial\\right_hover.png");

	auto background = std::make_shared<grc::view>(grc::rect{
		0,0, 1280, 800
		}, tutorial[0]);

	auto leftButton = std::make_shared<grc::buttonview>(grc::rect(200, 650, 300, 750), lde, ldwn, lh);
	auto rightButton = std::make_shared<grc::buttonview>(grc::rect(1280 - 300 - 100, 650, 1280 - 200 - 100, 750), rde, rdwn, rh);

	leftButton->mouseEvent = [background, tutorial](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			tutorialImageIndex -= 1;
			background->backgroundImage = tutorial[tutorialImageIndex % tutorial.size()];
			grc::audiocollect::shared->play(".\\resources\\audio\\button.mp3", NULL);
		}
	};

	rightButton->mouseEvent = [background, tutorial](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			tutorialImageIndex += 1;
			background->backgroundImage = tutorial[tutorialImageIndex % tutorial.size()];
			grc::audiocollect::shared->play(".\\resources\\audio\\button.mp3", NULL);
		}
	};



	data->view.push_back(background);
	data->view.push_back(leftButton);
	data->view.push_back(rightButton);

	data->openEvent = [](std::weak_ptr<grc::scene> data) {
		grc::application::shared->setSize(grc::size{ 1280, 800 });
		grc::application::shared->setTitle("차차의 모험기 : 사용법");
	};

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			close();
		}
	};
	
	return data;
}