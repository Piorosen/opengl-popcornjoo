#include "application.h"
#include "entryPoint.hpp"

int main(int argc, char** argv) {
	grc::application::shared->initialize(grc::size{ 1280, 800 }, "차차의 모험기");
	grc::application::shared->setScene(entryPoint());

	grc::application::shared->run();
}