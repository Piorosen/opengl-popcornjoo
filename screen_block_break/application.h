#pragma once
#include <string>

#include "data_structure.h"
#include "display.h"

namespace graphics {
	void keyboardEvent(unsigned char key, int x, int y);

	void renderEvent();

	void reshapeEvent(int x, int y);

	void initDisplay(int* argc, char** argv, 
					 size display, std::string title);

	namespace global {
		size getDisplaySize();
		point getDisplayPosition();
	}
}