#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <fstream>

#include "scene.h"
#include "physics.h"
#include "ballview.h"
#include "wallview.h"

void createIngameUI(std::shared_ptr<grc::scene> data, std::function<void()> close) {
	auto background = std::make_shared<grc::view>(grc::rect(0, 0, 1280, 800), grc::color(0xffffffff));
	// 위

	int upframe = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\upframe.png");
	int chahca0 = grc::imagecollect::shared->add(".\\resources\\imaegs\\character\\chacha000.png");
	int jinju0 = grc::imagecollect::shared->add(".\\resources\\imaegs\\character\\jinju000.png");

	auto outBoard = std::make_shared<grc::view>(grc::rect(25, 25, 1280 - 25, 175), grc::color(0x62e3ffff));
	auto inBoard = std::make_shared<grc::view>(grc::rect(25 + 4, 25 + 4, 1280 - 25 - 4, 175 - 4), grc::color(0x4fa6f0ff));
	auto boardChaCha = std::make_shared<grc::view>(grc::rect(33, 33, 167, 167), chahca0);
	auto boardJinju = std::make_shared<grc::view>(grc::rect(1251 - 134, 33, 1251, 167), jinju0);
	auto boardFrame = std::make_shared<grc::view>(grc::rect(25 + 4, 25 + 4, 1280 - 25 - 4, 175 - 4), upframe);

	// 1230
	// 150

	// 왼쪽
	auto outScore = std::make_shared<grc::view>(grc::rect(25, 200, 380, 775), grc::color(0xff0000ff));
	auto inScore = std::make_shared<grc::view>(grc::rect(25 + 4, 200 + 4, 380 - 4, 775 - 4), grc::color(0x00ffffff));
	// start : 
	// 53, 228
	// end :
	// 319, 747
	// total length :
	
	// 355, 575
	auto clearScore = std::make_shared<grc::view>(grc::rect(53, 228, 347, 319), grc::color(0xff0000ff));
	auto nowScore = std::make_shared<grc::view>(grc::rect(53, 329, 347, 410), grc::color(0xff0000ff));
	auto remainTry = std::make_shared<grc::view>(grc::rect(53, 420, 347, 511), grc::color(0xff0000ff));
	auto musicPlayer = std::make_shared<grc::colorbuttonview>(grc::rect(53, 555, 347, 646), grc::color(0xff0000ff));
	auto backButton = std::make_shared<grc::colorbuttonview>(grc::rect(53, 656, 347, 747), grc::color(0xff0000ff));
	
	musicPlayer->mouseEvent = [](grc::colorbuttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			auto audio = grc::audiocollect::shared->get(".\\resources\\audio\\ingame.mp3");
			if (audio.has_value()) {
				bool result;
				audio.value()->getPaused(&result);
				grc::audiocollect::shared->set(".\\resources\\audio\\ingame.mp3", !result);
			}
			else {
				spdlog::error("audio not found {}", ".\\resources\\audio\\ingame.mp3");
			}
		}
	};

	backButton->mouseEvent = [close](grc::colorbuttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			close();
		}
	};

	// 오른쪽
	auto outGame = std::make_shared<grc::view>(grc::rect(405, 200, 1255, 775), grc::color(0xff0000ff));
	auto inGame = std::make_shared<grc::view>(grc::rect(405 + 4, 200 + 4, 1255 - 4, 775 - 4), grc::color(0x00ffffff));
	// 834
	// 559

	data->view.push_back(background);

	data->view.push_back(outBoard);
	data->view.push_back(inBoard);
	data->view.push_back(boardChaCha);
	data->view.push_back(boardJinju);
	data->view.push_back(boardFrame);

	data->view.push_back(outScore);
	data->view.push_back(inScore);

	data->view.push_back(clearScore);
	data->view.push_back(nowScore);
	data->view.push_back(remainTry);
	data->view.push_back(musicPlayer);
	data->view.push_back(backButton);


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
	int totalScore;
	std::vector<gameElement> element;
};

gameData loadGame(std::string file) {
	std::ifstream read(file);
	gameData d;
	d.totalScore = 0;
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
			d.totalScore += elem.score;
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

int gameScore = 0;
int deadCount = 0;
int tryCount = 0;
std::vector<std::shared_ptr<grc::wallview>> wallList;
std::vector<std::shared_ptr<grc::wallview>> blockList;
std::vector<std::shared_ptr<grc::ballview>> ballList;

std::shared_ptr<grc::scene> getIngameScene(std::function<void()> close, std::function<void(bool)> winCheck) {
	auto data = std::make_shared<grc::scene>();
	

	data->openEvent = [=](std::weak_ptr<grc::scene> scene) {
		grc::audiocollect::shared->add(".\\resources\\audio\\ingame.mp3", grc::audiomode::LOOP_NORMAL);
		createIngameUI(data, close);

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

		for (auto& elem : game.element) {
			if (elem.type == 0) {
				auto p = std::make_shared<grc::ballview>(grc::point{
					413 + elem.x,
					208 + elem.y
					}, 10, 0xfff000ff);
				p->clickRange = grc::rect(413, 208, 413 + 834, 208 + 559);

				p->ballDeadEvent = [game, winCheck](grc::ballview* self) {
					deadCount += 1;
					self->shotable(false);
					self->reset();
					spdlog::info("{}", deadCount);
					if (deadCount == ballList.size()) {
						deadCount = 0;
						tryCount += 1;
						for (auto& p : ballList) {
							p->shotable(true);
						}
						spdlog::info("tryCount : [{}, {}]", tryCount, game.tryCount);

						if (gameScore >= game.totalScore)
						{
							if (winCheck) {
								winCheck(true);
							}
						}
						else if (tryCount >= game.tryCount) {
							if (winCheck) {
								winCheck(false);
							}
						}
					}
				};
				ballList.push_back(p);
			}
			else if (elem.type == 1) {
				auto blockTest = std::make_shared<grc::wallview>(grc::rect(413 + elem.x, 208 + elem.y, 413 + elem.x + elem.w, 208 + elem.y + elem.h), false, 0xffccc0ff);
				blockTest->setScore(elem.score);
				auto chacha = data->view[3];
				blockTest->brokenBlock = [chacha, winCheck, game](grc::wallview* self) {
					// 벽돌 파괴!
					// 점수 증가
					gameScore += 1;
					spdlog::info("gameScore : [{}, {}]", gameScore, game.totalScore);
					double characterLength = (1117 - 167) / blockList.size() * gameScore;
					chacha->frame = grc::rect(33 + characterLength, 33, 167 + characterLength, 167);
				};
				blockList.push_back(blockTest);
			}
			else {
				wallList.push_back(std::make_shared<grc::wallview>(grc::rect(413 + elem.x, 208 + elem.y, 413 + elem.x + elem.w, 208 + elem.y + elem.h), 0xc0c00cff));
			}
		}
		for (auto& elem : wallList) {
			data->view.push_back(elem);
		}
		for (auto& elem : blockList) {
			data->view.push_back(elem);
		}
		for (auto& elem : ballList) {
			data->view.push_back(elem);
		}

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
		for (auto& elem : blockList) {
			phy::physicsEngine::shared->AddWall(elem->getPhysical());
		}
		
		//phy::physicsEngine::shared->AddWall(wall5->getPhysical());
	};

	data->closeEvent = [](std::weak_ptr<grc::scene> scene) {
		ballList.clear();
		wallList.clear();
		blockList.clear();
		tryCount = 0;
		gameScore = 0;
		deadCount = 0;
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