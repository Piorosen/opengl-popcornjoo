#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <string>
#include <fstream>

#include "scene.h"
#include "physics.h"
#include "ballview.h"
#include "wallview.h"
#include "toggleview.h"
#include "numview.h"

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

void createIngameUI(std::shared_ptr<grc::scene> data, std::function<void()> close, gameData game) {
	auto background = std::make_shared<grc::view>(grc::rect(0, 0, 1280, 800), grc::color(0xffffffff));
	// 위

	int upframe = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\upframe.png");
	int leftframe = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\leftframe.png");
	
	int chahca0 = grc::imagecollect::shared->add(".\\resources\\imaegs\\character\\chacha000.png");
	int jinju0 = grc::imagecollect::shared->add(".\\resources\\imaegs\\character\\jinju000.png");

	auto outBoard = std::make_shared<grc::view>(grc::rect(25, 25, 1280 - 25, 175), grc::color(0x000000ff));
	auto inBoard = std::make_shared<grc::view>(grc::rect(25 + 4, 25 + 4, 1280 - 25 - 4, 175 - 4), grc::color(0x4fa6f0ff));
	auto boardChaCha = std::make_shared<grc::view>(grc::rect(33, 33, 167, 167), chahca0);
	auto boardJinju = std::make_shared<grc::view>(grc::rect(1251 - 134, 33, 1251, 167), jinju0);
	auto boardFrame = std::make_shared<grc::view>(grc::rect(25 + 4, 25 + 4, 1280 - 25 - 4, 175 - 4), upframe);

	// 1230
	// 150
	// start : 
	// 53, 228
	// end :
	// 319, 747
	// total length :
	
	// 355, 575
	// 왼쪽
	auto outScore = std::make_shared<grc::view>(grc::rect(25, 200, 380, 775), grc::color(0x000000ff));
	auto inScore = std::make_shared<grc::view>(grc::rect(25 + 4, 200 + 4, 380 - 4, 775 - 4), leftframe);

	std::vector<int> bNum;
	std::vector<int> gNum;
	std::vector<int> rNum;
	for (int i = 0; i < 10; i++) {
		bNum.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\blackNum\\" + std::to_string(i) + ".png"));
		gNum.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\greenNum\\" + std::to_string(i) + ".png"));
		rNum.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\redNum\\" + std::to_string(i) + ".png"));
	}

	auto playTimeImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\playTime.png");
	auto reMonsterImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\remainMonster.png");
	auto retryImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\remainTry.png");

	auto scorePos = inScore->frame;
	auto centerPos = scorePos.center();

	auto playTimeTitle = std::make_shared<grc::view>(grc::rect(centerPos.x - 150, scorePos.location.y + 110 - 55,
															   centerPos.x + 150, scorePos.location.y + 110), playTimeImage);
	auto remianTitle = std::make_shared<grc::view>(grc::rect(centerPos.x - 150, scorePos.location.y + 240 - 55,
															   centerPos.x + 150, scorePos.location.y + 240), reMonsterImage);
	auto retryTitle = std::make_shared<grc::view>(grc::rect(centerPos.x - 150, scorePos.location.y + 370 - 55,
															   centerPos.x + 150, scorePos.location.y + 370), retryImage);

	auto playTime = std::make_shared<grc::numview>(grc::rect(centerPos.x - 150, scorePos.location.y + 120,
															 centerPos.x + 150, scorePos.location.y + 170), bNum, 0);

	auto remainMonster = std::make_shared<grc::numview>(grc::rect(centerPos.x - 150, scorePos.location.y + 250,
																  centerPos.x + 150, scorePos.location.y + 300), rNum, game.totalScore);

	auto remainTry = std::make_shared<grc::numview>(grc::rect(centerPos.x - 150, scorePos.location.y + 380,
															  centerPos.x + 150, scorePos.location.y + 430), gNum, game.tryCount);

	int mute = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\mute.png");
	int unmute = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\unmute.png");
	int homeImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\home.png");
	int ingameImage = grc::imagecollect::shared->add(".\\resources\\imaegs\\game\\ingame.png");

	auto musicPlayer = std::make_shared<grc::toggleview>(grc::rect(75 + 30, 626, 175 + 30, 726), mute, unmute);
	auto backButton = std::make_shared<grc::buttonview>(grc::rect(219 + 30, 626, 319 + 30, 726), homeImage, homeImage, homeImage);

	musicPlayer->toggleEvent = [](grc::toggleview* self, bool toggle) {
		auto audio = grc::audiocollect::shared->get(".\\resources\\audio\\ingame.mp3");
		if (audio.has_value()) {
			grc::audiocollect::shared->set(".\\resources\\audio\\ingame.mp3", toggle);
		}
		else {
			spdlog::error("audio not found {}", ".\\resources\\audio\\ingame.mp3");
		}
	};

	backButton->mouseEvent = [close](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			close();
		}
	};

	// 오른쪽
	auto outGame = std::make_shared<grc::view>(grc::rect(405, 200, 1255, 775), grc::color(0x000000ff));
	auto inGame = std::make_shared<grc::view>(grc::rect(405 + 4, 200 + 4, 1255 - 4, 775 - 4), ingameImage);
	// 834
	// 559

	data->view.push_back(background);	// 0

	data->view.push_back(outBoard);		// 1
	data->view.push_back(inBoard);		// 2
	data->view.push_back(boardChaCha);	// 3
	data->view.push_back(boardJinju);	// 4	
	data->view.push_back(boardFrame);	// 5

	data->view.push_back(outScore);		// 6
	data->view.push_back(inScore);		// 7

	data->view.push_back(playTime);		// 8
	data->view.push_back(remainMonster);// 9
	data->view.push_back(remainTry);	// 10

	data->view.push_back(playTimeTitle);// 11
	data->view.push_back(remianTitle);	// 12
	data->view.push_back(retryTitle);	// 13

	data->view.push_back(musicPlayer);	// 14
	data->view.push_back(backButton);	// 15

	data->view.push_back(outGame);		// 16
	data->view.push_back(inGame);		// 17
}



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
long long sceneTicks = 0;

std::string INGAME_RUN_GAME_LOAD_FILE = "001";



std::shared_ptr<grc::scene> getIngameScene(std::function<void()> close, std::function<void(bool)> winCheck) {
	auto data = std::make_shared<grc::scene>();
	grc::audiocollect::shared->add(".\\resources\\audio\\block_broken.mp3");

	data->renderEvent = [](grc::scene* self, long long tick) {
		sceneTicks += tick;
		std::static_pointer_cast<grc::numview>(self->view[8])->setNum(sceneTicks / 10);
	};

	data->openEvent = [=](std::weak_ptr<grc::scene> scene){
		grc::application::shared->setTitle("차차의 모험기 : 진쥬를 구해줘!");
		grc::audiocollect::shared->add(".\\resources\\audio\\ingame.mp3", grc::audiomode::LOOP_NORMAL);
		auto game = loadGame(".\\resources\\map\\" + INGAME_RUN_GAME_LOAD_FILE + ".m");
		createIngameUI(data, close, game);

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

		for (auto& elem : game.element) {
			if (elem.type == 0) {
				auto p = std::make_shared<grc::ballview>(grc::point{
					413 + elem.x,
					208 + elem.y
					}, 10, 0xffffffff);
				p->clickRange = grc::rect(413, 208, 413 + 834, 208 + 559);

				auto retry = std::static_pointer_cast<grc::numview>(data->view[10]);
				p->ballDeadEvent = [game, winCheck, retry](grc::ballview* self) {
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
						retry->setNum(game.tryCount - tryCount);

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
				auto monster = std::static_pointer_cast<grc::numview>(data->view[9]);
				blockTest->brokenBlock = [chacha, winCheck, game, monster](grc::wallview* self) {
					// 벽돌 파괴!
					// 점수 증가
					gameScore += 1;
					grc::audiocollect::shared->play(".\\resources\\audio\\block_broken.mp3");

					monster->setNum(game.totalScore - gameScore);
					spdlog::info("gameScore : [{}, {}]", gameScore, game.totalScore);
					double characterLength = (1117.0 - 167) / blockList.size() * gameScore;
					chacha->frame = grc::rect(33 + characterLength, 33, 167 + characterLength, 167);
				};
				blockList.push_back(blockTest);
			}
			else {
				wallList.push_back(std::make_shared<grc::wallview>(grc::rect(413 + elem.x, 208 + elem.y, 413 + elem.x + elem.w, 208 + elem.y + elem.h), true, grc::color(0xccffccff)));
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
		sceneTicks = 0;
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