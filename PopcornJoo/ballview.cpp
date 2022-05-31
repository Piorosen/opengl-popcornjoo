#include <spdlog/spdlog.h>
#include "ballview.h"


grc::ballview::ballview(grc::point center, int radius, grc::color ballColor) 
	: view(grc::rect(center.x - (radius / 2),
					 center.y - (radius / 2),
					 center.x + (radius / 2),
					 center.y + (radius / 2)), ballColor)
{
	physical = std::make_shared<phy::object>();
	physical->collisionevent = [](std::weak_ptr<phy::object> self, std::weak_ptr<phy::object> other) {
		auto obj = self.lock();
		auto oobj = other.lock();
		obj->velocity.y = -300;

		double r = 0;
		grc::rect rc;
		grc::rect rc2;
		oobj->getType(r, rc2);
		obj->getType(r, rc);

		//double ballBottom = obj->transform.y + r;
		//double wallTop = oobj->transform.y + rc2.location.y;

		//obj->transform.y -= ballBottom - wallTop + r;
		obj->transformchanged(obj->transform);
		spdlog::info("COLLISION");
	};
	physical->transform = phy::vector2d{
		(double)center.x,
		(double)center.y
	};
	physical->transformchanged = [this](phy::vector2d location) {
		auto radius = this->frame.size.width / 2.0;
		this->frame = grc::rect(location.x - radius, location.y - radius,
								location.x + radius, location.y + radius);
	};
	physical->setType(radius);
	physical->gravity = -10;
	physical->mesh = 0.05;
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
