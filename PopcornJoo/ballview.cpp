#include "ballview.h"


grc::ballview::ballview(grc::point center, int radius, grc::color ballColor) 
	: view(grc::rect(center.x - (radius / 2),
					 center.y - (radius / 2),
					 center.x + (radius / 2),
					 center.y + (radius / 2)), ballColor)
{
	physical = std::make_shared<phy::object>();
	physical->transform = phy::vector2d{
		(double)center.x,
		(double)center.y
	};
	physical->setType(radius);
	physical->gravity = 1.0;
	physical->mesh = 10;
}

std::shared_ptr<phy::object> grc::ballview::getPhysical() const
{
	return physical;
}

bool grc::ballview::render(long long tick)
{
	if (!getHidden()) {
		view::drawCircle(frame.center(), frame.size.width / 2.0, background);
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

grc::mouseclick grc::ballview::click(int state, int x, int y)
{
	return view::click(state, x, y);
}

int grc::ballview::mouse(int x, int y)
{
	return view::mouse(x, y);
}
