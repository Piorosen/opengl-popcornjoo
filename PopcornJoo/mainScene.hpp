#pragma once
#include <memory>
#include <spdlog/spdlog.h>

#include "scene.h"


#include "imagecollect.h"
#include "spriteview.h"
#include "buttonview.h"



std::vector<int> arrayData;
int i = 0;
std::shared_ptr<grc::scene> mainScene() {

	auto data = std::make_shared<grc::scene>();
	std::vector<int> im;
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\004.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\003.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\002.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\001.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\000.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\001.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\002.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\003.png"));
	im.push_back(grc::imagecollect::shared->add(".\\resources\\imaegs\\main\\logo\\004.png"));

	auto v = std::make_shared<grc::spriteview>(grc::rect{
			150, 100, 200, 100
		}, im);
	v->durationMS = 500;


	//b->mouseEvent += [](grc::buttonview* self, grc::buttonstate state) {
	//	spdlog::info("Occur Event!!");
	//};
	data->openEvent += [](std::weak_ptr<grc::scene> self) {
		grc::application::shared->setTitle("차차의 모험기 : 메인화면");
		grc::application::shared->setSize(grc::size{
			500, 500 });
	};

	v->play();

	data->view.push_back(v);


	return data;
}