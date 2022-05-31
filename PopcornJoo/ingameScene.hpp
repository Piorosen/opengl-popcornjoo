#pragma once
#include <memory>
#include <spdlog/spdlog.h>

#include "scene.h"
#include "physics.hpp"
#include "ballview.h"

std::shared_ptr<grc::scene> getIngameScene(std::function<void()> close) {
	auto data = std::make_shared<grc::scene>();

	auto ball = std::make_shared<grc::ballview>(grc::point{250, 250}, 10, grc::color(0xff000000));
	data->view.push_back(ball);

	data->openEvent = [=](std::weak_ptr<grc::scene> scene) {
		phy::physicsEngine::shared->ClearObject();
		phy::physicsEngine::shared->AddTarget(ball->getPhysical());

	};

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			close();
		}
	};

	return data;
}