#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <fstream>

#include "scene.h"
#include "physics.h"
#include "ballview.h"
#include "wallview.h"

void createIngameUI(std::shared_ptr<grc::scene> data) {
	auto background = std::make_shared<grc::view>(grc::rect(0, 0, 1280, 800), grc::color(0xffffffff));
	auto outBoard = std::make_shared<grc::view>(grc::rect(25, 25, 1280 - 25, 25 + 150), grc::color(0xff0000ff));
	auto inBoard = std::make_shared<grc::view>(grc::rect(25 + 8, 25 + 8, 1280 - 25 - 8, 25 + 150 - 8), grc::color(0x00ffffff));
	auto outScore = std::make_shared<grc::view>(grc::rect(25, 200, 380, 775), grc::color(0xff0000ff));
	auto inScore = std::make_shared<grc::view>(grc::rect(25 + 8, 200 + 8, 380 - 8, 775 - 8), grc::color(0x00ffffff));

	auto outGame = std::make_shared<grc::view>(grc::rect(405, 200, 1255, 775), grc::color(0xff0000ff));
	auto inGame = std::make_shared<grc::view>(grc::rect(405 + 8, 200 + 8, 1255 - 8, 775 - 8), grc::color(0x00ffffff));

	data->view.push_back(background);
	data->view.push_back(outBoard);
	data->view.push_back(inBoard);
	data->view.push_back(outScore);
	data->view.push_back(inScore);
	data->view.push_back(outGame);
	data->view.push_back(inGame);
}

struct gameElement
{
	int x, y, w, h;
	// 0 : 볼
	// 1 : 블럭
	// 2 : 벽
	int type;
	// 블록에 관한 점수
	int score;
};

struct gameData {
	int tryCount;
	int clearScore;
	std::vector<gameElement> element;
};

gameData loadGame(std::string file) {
	std::ifstream read(file);
	gameData d;
	int count;
	read >> d.tryCount >> d.clearScore >> count;
	for (int i = 0; i < count; i++) {
		gameElement elem;
		read >> elem.type;
		switch (elem.type) {
		case 0:
			read >> elem.x >> elem.y;
			break;
		case 1:
			read >> elem.x >> elem.y >> elem.w >> elem.h >> elem.score;
			break;
		case 2:
			read >> elem.x >> elem.y >> elem.w >> elem.h;
			break;
		}
		d.element.push_back(elem);
	}
	read.close();

	return d;
}

std::shared_ptr<grc::scene> getIngameScene(std::function<void()> close) {
	auto data = std::make_shared<grc::scene>();
	grc::audiocollect::shared->add(".\\resources\\audio\\ingame.mp3", grc::audiomode::LOOP_NORMAL);
	createIngameUI(data);

	// left
	auto wall1 = std::make_shared<grc::wallview>(grc::rect(0, 0, 405 + 8, 800));
	// top
	auto wall2 = std::make_shared<grc::wallview>(grc::rect(0, 0, 1280, 208));
	// bottom
	auto wall3 = std::make_shared<grc::wallview>(grc::rect(0, 775 - 8, 1280, 1200));
	// right
	auto wall4 = std::make_shared<grc::wallview>(grc::rect(1255 - 8, 0, 2000, 1200));

	//auto ball = std::make_shared<grc::ballview>(grc::point{ (1255 + 413) / 2, 750 - 8 }, 10, grc::color(0xfff000ff));
	//data->view.push_back(ball);
	
	auto game = loadGame(".\\resources\\map\\002.m");
	std::vector<std::shared_ptr<grc::wallview>> wallList;
	std::vector<std::shared_ptr<grc::ballview>> ballList;

	for (auto& elem : game.element) {
		if (elem.type == 0) {
			auto p = std::make_shared<grc::ballview>(grc::point{
				413 + elem.x,
				208 + elem.y
				}, 10, 0xfff000ff);
			p->ballDeadEvent = [](grc::ballview* self) {
				self->reset();
			};
			ballList.push_back(p);
		}
		else if (elem.type == 1) {
			auto blockTest = std::make_shared<grc::wallview>(grc::rect(413 + elem.x, 208 + elem.y, 413 + elem.x + elem.w, 208 + elem.y + elem.h), false, 0xffccc0ff);
			blockTest->setScore(elem.score);
			wallList.push_back(blockTest);
		}
		else {
			wallList.push_back(std::make_shared<grc::wallview>(grc::rect(413 + elem.x, 208 + elem.y, 413 + elem.x + elem.w, 208 + elem.y + elem.h), 0xc0c00cff));
		}
	}
	for (auto& elem : wallList) {
		data->view.push_back(elem);
	}
	for (auto& elem : ballList) {
		data->view.push_back(elem);
	}

	data->openEvent = [=](std::weak_ptr<grc::scene> scene) {
		auto data = grc::audiocollect::shared->set(".\\resources\\audio\\main_logo.mp3", true);
		grc::audiocollect::shared->set(".\\resources\\audio\\ingame.mp3", false);
		phy::physicsEngine::shared->ClearObject();

		phy::physicsEngine::shared->AddWall(wall1->getPhysical());
		phy::physicsEngine::shared->AddWall(wall2->getPhysical());
		phy::physicsEngine::shared->AddWall(wall3->getPhysical());
		phy::physicsEngine::shared->AddWall(wall4->getPhysical());


		for (auto& elem : ballList) {
			phy::physicsEngine::shared->AddTarget(elem->getPhysical());
		}

		for (auto& elem : wallList) {
			phy::physicsEngine::shared->AddWall(elem->getPhysical());
		}
		//phy::physicsEngine::shared->AddWall(wall5->getPhysical());
	};

	data->closeEvent = [](std::weak_ptr<grc::scene> scene) {
		phy::physicsEngine::shared->ClearObject();
		grc::audiocollect::shared->set(".\\resources\\audio\\ingame.mp3", true);
	};

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			close();
		}
	};

	return data;
}