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

std::shared_ptr<grc::scene> getMainScene(std::function<void(grc::buttonview*, grc::buttonstate)> startEvent,
									     std::function<void(grc::buttonview*, grc::buttonstate)> helpEvent) {
	std::shared_ptr<grc::scene> data = std::make_shared<grc::scene>();

	grc::audiocollect::shared->add(".\\resources\\audio\\main_logo.mp3", grc::audiomode::LOOP_NORMAL);

	int help_default = grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\helpbutton_default.png");
	int help_down = grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\helpbutton_default.png");

	int mainPage = grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\main.png");

	int start_default = grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\startbutton_default.png");
	int start_down = grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\startbutton_default.png");

	auto startButton = std::make_shared<grc::buttonview>(grc::rect(880, 530, 880 + 348, 530 + 95), start_default, start_down, start_default);
	auto helpButton = std::make_shared<grc::buttonview>(grc::rect(880, 630, 880 + 348, 630 + 95), help_default, help_down, help_default);
	auto mainPageView = std::make_shared<grc::view>(grc::rect(0, 0, 1280, 800), mainPage);

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


	data->view.push_back(mainPageView);
	data->view.push_back(startButton);
	data->view.push_back(helpButton);

	return data;
}