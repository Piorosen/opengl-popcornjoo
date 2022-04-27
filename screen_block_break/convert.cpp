#include "convert.h"
#include "display.h"

namespace graphics {
	namespace convert {
		graphics::point screenToGraphic(const graphics::point& pt) {
			auto pos = graphics::info::getPosition();
			return graphics::point{
				pt.x - pos.x,
				pt.y - pos.y
			};
		}
	}
}

// 내가 좋아하는 개발개발~ 예수우우~ 오우예에에엥