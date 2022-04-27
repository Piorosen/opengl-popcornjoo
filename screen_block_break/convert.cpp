#include "convert.h"
#include "display.h"

namespace graphics {
	namespace convert {
		graphics::point screenToGraphic(graphics::point pt) {
			auto pos = graphics::info::getPosition();
			return graphics::point{
				pt.x - pos.x,
				pt.y - pos.y
			};
		}
	}
}