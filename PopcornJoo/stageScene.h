#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <filesystem>
#include <algorithm>

#include "scene.h"


std::shared_ptr<grc::scene> getStageScene(std::function<void()> close, std::function<void(std::string)> startMap) {
	auto data = std::make_shared<grc::scene>();
	
	auto iter = std::filesystem::directory_iterator(".\\resources\\map");
	std::vector<std::string> files;
	for (const auto& file : iter) {
		spdlog::info("file find [{}]", file.path().filename().stem().string());
		files.push_back(file.path().filename().stem().string());
	}
	
	int stageSelect = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\stageselect.png");
	int backImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\back.png");

	auto background = std::make_shared<grc::view>(grc::rect(0, 0, 1280, 800), stageSelect);
	auto backButton = std::make_shared<grc::buttonview>(grc::rect(30, 30, 30 + 144, 30 + 74), backImage, backImage, backImage);
	backButton->mouseEvent = [close](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			if (close) {
				close();
			}
		}
	};

	std::sort(files.begin(), files.end());
	std::vector<int> wNum;
	for (int i = 0; i < 10; i++) {
		wNum.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\whiteNum\\" + std::to_string(i) + ".png"));
	}

	std::vector<int> level;
	for (int i = 0; i < 4; i++) {
		level.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\stageLevel\\" + std::to_string(i) + ".png"));
	}

	data->openEvent = [](std::weak_ptr<grc::scene> self) {
		grc::audiocollect::shared->set(".\\resources\\audio\\main_logo.mp3", false);
		grc::application::shared->setTitle("차차의 모험기 : 스테이지 선택");
	};

	int maxY = 4;
	int maxX = 5;

	data->view.push_back(background);
	data->view.push_back(backButton);
	for (int idx = 0; idx < files.size(); idx++) {
		int capture = idx;
		int y = idx / maxX;
		int x = idx % maxX;
		int padding = 10;
		auto c = std::make_shared<grc::buttonview>(grc::rect(50 + 1180 / maxX * x + padding, 400 + (350 / maxY) * y + padding,
			50 + (1180 / maxX) * (x + 1) - padding, 400 + (350 / maxY) * (y + 1) - padding), level[y], level[y], level[y]);
		auto text = std::make_shared<grc::numview>(grc::rect(50 + 1180 / maxX * x , 400 + (350 / maxY) * y + (padding * 2),
			50 + (1180 / maxX) * (x + 1), 400 + (350 / maxY) * (y + 1) - +(padding * 2)), wNum, idx + 1);
		
		c->mouseEvent = [capture, startMap](grc::buttonview* self, grc::buttonstate state) {
			if (state == grc::buttonstate::mouseUp) {
				spdlog::info("Start Game : [{}]", capture + 1);
				char dataText[100];
				sprintf_s(dataText, "%03d", capture + 1);
				startMap(dataText);
			}
		};
		data->view.push_back(c);
		data->view.push_back(text);
	}


	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			if (close) {
				close();
			}
		}
	};

	return data;
}


