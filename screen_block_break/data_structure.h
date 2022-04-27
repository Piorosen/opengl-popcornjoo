#pragma once
#include <gl/glut.h>

namespace graphics {
	struct point {
		int x; 
		int y;
	};
	struct size {
		int width;
		int height;
	};
	struct rect {
		point point;
		size size;
	};
}