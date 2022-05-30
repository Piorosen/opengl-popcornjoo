#pragma once
#include <memory>
#include <spdlog/spdlog.h>

#include "scene.h"


#include "imagecollect.h"
#include "spriteview.h"
#include "buttonview.h"

std::shared_ptr<grc::scene> getHelpScene(std::function<void()> close) {
	auto data = std::make_shared<grc::scene>();

	data->view.push_back(std::make_shared<grc::view>(grc::rect(0, 0, 500, 500), grc::color(0xff000000)));
	data->openEvent = [](std::weak_ptr<grc::scene> data) {
		
	};

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			close();
		}
	};
	
	return data;
}