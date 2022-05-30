#pragma once

#include "mainScene.hpp"
#include "ingame.hpp"

std::shared_ptr<grc::scene> entryPoint() {
	return getMainScene([](grc::colorbuttonview* view, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			spdlog::info("Start 이벤트 발생");
		}
		// Start 이벤트
	}, [](grc::colorbuttonview* view, grc::buttonstate state) {
		// End 이벤트
		if (state == grc::buttonstate::mouseUp) {
			spdlog::info("End 이벤트 발생");
		}
	});

}