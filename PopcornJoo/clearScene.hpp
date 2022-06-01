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

std::shared_ptr<grc::scene> getEndgame(std::function<void()> close) {
	std::shared_ptr<grc::scene> data = std::make_shared<grc::scene>();

	auto backButton = std::make_shared<grc::buttonview>(grc::rect(1280 - 25 - 200, 800 - 25 - 100, 1280 - 25, 800 - 25), 20, 20, 20);
	backButton->mouseEvent = [close](grc::buttonview* self, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			close();
		}
	};
		
	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			if (close) {
				close();
			}
		}
	};

	data->view.push_back(backButton);
	return data;
}