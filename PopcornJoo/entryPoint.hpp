#pragma once

#include "mainScene.hpp"
#include "ingameScene.hpp"
#include "helpScene.hpp"
#include "clearScene.hpp"
#include "stageScene.h"

std::shared_ptr<grc::scene> help;
std::shared_ptr<grc::scene> ingame;
std::shared_ptr<grc::scene> mainView;
std::shared_ptr<grc::scene> clearView;
std::shared_ptr<grc::scene> stageScene;

std::shared_ptr<grc::scene> entryPoint() {
	stageScene = getStageScene([]() {
		grc::application::shared->setScene(mainView);
		}, [](std::string file) {
			INGAME_RUN_GAME_LOAD_FILE = file;
			ingame->view.clear();
			grc::application::shared->setScene(ingame);
		});

	clearView = getEndgame([]() {
		grc::application::shared->setScene(stageScene);
		});

	ingame = getIngameScene([]() {
		grc::application::shared->setScene(stageScene);
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
			grc::application::shared->setScene(stageScene);
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