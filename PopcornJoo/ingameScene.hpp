#pragma once
#include <memory>
#include <spdlog/spdlog.h>

#include "scene.h"


#include "imagecollect.h"
#include "spriteview.h"
#include "buttonview.h"

std::shared_ptr<grc::scene> getIngameScene() {
	auto data = std::make_shared<grc::scene>();
	return data;
}