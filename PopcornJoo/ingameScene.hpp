#pragma once
#include <memory>
#include <spdlog/spdlog.h>

#include "scene.h"
#include "physics.h"
#include "ballview.h"
#include "wallview.h"

std::shared_ptr<grc::scene> getIngameScene(std::function<void()> close) {
	auto data = std::make_shared<grc::scene>();

	auto ball = std::make_shared<grc::ballview>(grc::point{ 250, 250 }, 10, grc::color(0xff0000ff));
	
	int think = 10;
	// top
	auto wall1 = std::make_shared<grc::wallview>(grc::rect(50, 50, 450, 50 + think));
	// left
	auto wall2 = std::make_shared<grc::wallview>(grc::rect(50, 50, 50 + think, 450));
	// bottom
	auto wall3 = std::make_shared<grc::wallview>(grc::rect(50, 450 - think, 450, 450));
	// right
	auto wall4 = std::make_shared<grc::wallview>(grc::rect(450 - think, 50, 450, 450));
	
	data->view.push_back(wall1);
	data->view.push_back(wall2);
	data->view.push_back(wall3);
	data->view.push_back(wall4);
	data->view.push_back(ball);

	data->openEvent = [=](std::weak_ptr<grc::scene> scene) {
		phy::physicsEngine::shared->ClearObject();
		phy::physicsEngine::shared->AddTarget(ball->getPhysical());
		
		phy::physicsEngine::shared->AddWall(wall1->getPhysical());
		phy::physicsEngine::shared->AddWall(wall2->getPhysical());
		phy::physicsEngine::shared->AddWall(wall3->getPhysical());
		phy::physicsEngine::shared->AddWall(wall4->getPhysical());
	};

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			close();
		}
	};

	return data;
}