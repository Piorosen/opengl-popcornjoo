#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <functional>

#include "rect.h"
#include "colorbuttonview.h"
#include "buttonview.h"
#include "spriteview.h"
#include "scene.h"
#include "audiocollect.h"
#include "imagecollect.h"

std::shared_ptr<grc::scene> getMainScene(std::function<void(grc::colorbuttonview*, grc::buttonstate)> startEvent,
									     std::function<void(grc::colorbuttonview*, grc::buttonstate)> helpEvent) {
	std::shared_ptr<grc::scene> data = std::make_shared<grc::scene>();

	grc::audiocollect::shared->add(".\\resources\\audio\\main_logo.mp3", grc::audiomode::LOOP_NORMAL);

	std::vector<int> im;
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\004.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\003.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\002.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\001.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\000.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\001.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\002.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\003.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\004.png"));
	
	auto v = std::make_shared<grc::spriteview>(grc::rect(150, 100, 350, 200), im);
	v->durationMS = 500;
	v->play();

	auto startButton = std::make_shared<grc::colorbuttonview>(grc::rect(350, 250, 550, 300));
	auto helpButton = std::make_shared<grc::colorbuttonview>(grc::rect(350, 350, 550, 400));


	startButton->mouseEvent = startEvent;
	helpButton->mouseEvent = helpEvent;

	data->openEvent = [](std::weak_ptr<grc::scene> self) {
		grc::application::shared->setTitle("차차의 모험기 : 메인화면");
		grc::application::shared->setSize(grc::size{
			1280, 800 });
		auto audio = grc::audiocollect::shared->get(".\\resources\\audio\\main_logo.mp3");
		if (audio.has_value()) {
			audio.value()->setPaused(false);
		}
		else {
			grc::audiocollect::shared->set(".\\resources\\audio\\main_logo.mp3", false);
		}
	};

	data->closeEvent = [](std::weak_ptr<grc::scene> self) {
	
	};


	data->view.push_back(v);
	data->view.push_back(startButton);
	data->view.push_back(helpButton);

	return data;
}