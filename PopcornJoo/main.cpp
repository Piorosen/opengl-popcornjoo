#include "application.h"
#include "entryPoint.hpp"

int main(int argc, char** argv) {
	spdlog::info("Build Time : [{}, {}]", __DATE__, __TIME__);
	grc::application::shared->initialize(grc::size{ 1280, 800 }, "차차의 모험기");
	grc::application::shared->setRenderSpeed(1);
	grc::application::shared->setScene(entryPoint());

	grc::application::shared->run();
}