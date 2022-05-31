#include "wallview.h"

#include <spdlog/spdlog.h>

grc::wallview::wallview(grc::rect rect, grc::color backgroundColor) : view(rect, backgroundColor)
{
	auto center = rect.center();

	physical = std::make_shared<phy::object>();
	physical->setTransform(phy::vector2d{
		(double)center.x,
		(double)center.y
		});
	physical->setType(grc::rect(-rect.size.width / 2.0, -rect.size.height / 2.0,
								 rect.size.width / 2.0,  rect.size.height / 2.0));
	physical->gravity = 0;
	physical->mesh = INT_MAX;
}


std::shared_ptr<phy::object> grc::wallview::getPhysical() const
{
	return physical;
}

bool grc::wallview::render(long long tick)
{
	if (!getHidden()) {
		view::drawRect(frame, background);
		for (auto& v : controls)
		{
			v->render(tick);
		}
		return true;
	}
	else {
		return false;
	}
}

