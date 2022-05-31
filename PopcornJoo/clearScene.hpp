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

	data->keyboard = [close](grc::scene* self, unsigned char key, int x, int y) {
		if (key == 27) {
			if (close) {
				close();
			}
		}
	};
	return data;
}