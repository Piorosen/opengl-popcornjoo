#pragma once
#include "data_structure.h"

namespace graphics {
	namespace info {
		rect primaryMonitor();
		// 좌 상단 기준.
		void setPosition(const graphics::point&);
		graphics::point getPosition();
	}
	
}
