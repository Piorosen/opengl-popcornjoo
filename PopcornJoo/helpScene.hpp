#pragma once
#include <memory>
#include <spdlog/spdlog.h>

#include "scene.h"


#include "imagecollect.h"
#include "spriteview.h"
#include "buttonview.h"

std::shared_ptr<grc::scene> getHelpScene(std::function<void()> close) {
	auto data = std::make_shared<grc::scene>();

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			close();
		}
	};
	
	return data;
}