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
#include "audiocollect.h"

std::shared_ptr<grc::scene> getEndgame(std::function<void()> close) {
	std::shared_ptr<grc::scene> data = std::make_shared<grc::scene>();
	grc::audiocollect::shared->add(".\\resources\\audio\\game_finish.mp3", grc::audiomode::DEFAULT);
	
	int clearbackImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\gameclear_back.png");
	int clearImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\gameclear.png");

	int failbackImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\gamefail_back.png");
	int failImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\gamefail.png");

	auto clearView = std::make_shared<grc::view>(grc::rect(0, 0, 1280, 800), clearImage);
	auto clearBackView = std::make_shared<grc::buttonview>(grc::rect(880, 660, 880 + 348, 660 + 95), clearbackImage, clearbackImage, clearbackImage);

	auto failView = std::make_shared<grc::view>(grc::rect(0, 0, 1280, 800), failImage);
	auto failBackView = std::make_shared<grc::buttonview>(grc::rect(880, 660, 880 + 348, 660 + 95), failbackImage, failbackImage, failbackImage);

	data->view.push_back(clearView);
	data->view.push_back(clearBackView);

	data->view.push_back(failView);
	data->view.push_back(failBackView);

	clearBackView->mouseEvent = [close](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			grc::audiocollect::shared->play(".\\resources\\audio\\button.mp3");
			auto d = grc::audiocollect::shared->get(".\\resources\\audio\\game_finish.mp3");
			if (d.has_value()) {
				d.value()->stop();
			}
			else {
				spdlog::info("audio fail");
			}
			close();
		}
	};

	failBackView->mouseEvent = [close](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			grc::audiocollect::shared->play(".\\resources\\audio\\button.mp3");
			auto d = grc::audiocollect::shared->get(".\\resources\\audio\\game_finish.mp3");
			if (d.has_value()) {
				d.value()->stop();
			}
			else {
				spdlog::info("audio fail");
			}
			close();
		}
	};
	
	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			if (close) {
				auto d = grc::audiocollect::shared->get(".\\resources\\audio\\game_finish.mp3");
				if (d.has_value()) {
					d.value()->stop();
				}
				else {
					spdlog::info("audio fail");
				}
				close();
			}
		}
	};

	data->openEvent = [](std::weak_ptr<grc::scene> self) {
		grc::audiocollect::shared->play(".\\resources\\audio\\game_finish.mp3");
		auto l = self.lock();
			spdlog::info("{}", l->view.size());
		for (int i = 0; i < 4; i++) {
			l->view[i]->setHidden(true);
		}
		
		if (gameClearStatus) {
			l->view[0]->setHidden(false);
			l->view[1]->setHidden(false);
		}
		else {
			l->view[2]->setHidden(false);
			l->view[3]->setHidden(false);
		}
		grc::application::shared->setTitle("차차의 모험기 : 스테이지 끝");
	};

	return data;
}