#pragma once

#include "mainScene.hpp"
#include "ingameScene.hpp"
#include "helpScene.hpp"
#include "clearScene.hpp"

std::shared_ptr<grc::scene> help;
std::shared_ptr<grc::scene> ingame;
std::shared_ptr<grc::scene> mainView;
std::shared_ptr<grc::scene> clearView;

std::shared_ptr<grc::scene> entryPoint() {
	clearView = getEndgame([]() {
		grc::application::shared->setScene(mainView);
		});

	ingame = getIngameScene([]() {
		grc::application::shared->setScene(mainView);
		}, [](bool win) {
			spdlog::info("WIN CHECK!!! [{}]", win);
			grc::application::shared->setScene(clearView);
		});

	help = getHelpScene([]() {
		grc::application::shared->setScene(mainView);
		});

	mainView = getMainScene([](grc::colorbuttonview* view, grc::buttonstate state) {
		if (state == grc::buttonstate::mouseUp) {
			spdlog::info("Start 이벤트 발생");
			ingame->view.clear();
			grc::application::shared->setScene(ingame);
		}
		// Start 이벤트
		}, [](grc::colorbuttonview* view, grc::buttonstate state) {
			// End 이벤트
			if (state == grc::buttonstate::mouseUp) {
				grc::application::shared->setScene(help);
				spdlog::info("End 이벤트 발생");
			}
		});

	return mainView;
}