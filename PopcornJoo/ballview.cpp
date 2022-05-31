#include <spdlog/spdlog.h>
#include "ballview.h"


grc::ballview::ballview(grc::point center, int radius, grc::color ballColor) 
	: view(grc::rect(center.x - radius,
					 center.y - radius,
					 center.x + radius,
					 center.y + radius), ballColor)
{
	this->radius = radius;
	physical = std::make_shared<phy::object>();
	physical->collisionevent = [](std::weak_ptr<phy::object> self, std::weak_ptr<phy::object> other, phy::collisioninfo info, long long tick) {
		auto obj = self.lock();
		auto oobj = other.lock();
		
		double r = 0;
		grc::rect rc;
		grc::rect rc2;
		oobj->getType(r, rc2);
		obj->getType(r, rc);

		auto t = obj->getTransform();
		// gravity ¿ª¹æÇâ
		if (info.other == phy::collisionPos::top) {
			double downSpeed = obj->gravity * obj->mesh * (tick / 1000.0);
			obj->setTransform(phy::vector2d{ t.x, t.y - obj->velocity.y * (tick / 1000.0) });
			obj->velocity.y += downSpeed;
			obj->velocity.y = -obj->velocity.y * 1.00;
		}
		else if (info.other == phy::collisionPos::left || info.other == phy::collisionPos::right) {
			obj->setTransform(phy::vector2d{ t.x - obj->velocity.x * (tick / 1000.0), t.y });
			obj->velocity.x *= -1;
		}
		else {
			obj->setTransform(phy::vector2d{ t.x, t.y - obj->velocity.y * (tick / 1000.0) });
			obj->velocity.y = -obj->velocity.y * 0.8;
		}
		switch (info.other) {
		case phy::collisionPos::none:
			spdlog::info("collision Pos : [NONE]");
			break;
		case phy::collisionPos::left:
			spdlog::info("collision Pos : [left]");
			break;
		case phy::collisionPos::top:
			spdlog::info("collision Pos : [top]");
			break;
		case phy::collisionPos::right:
			spdlog::info("collision Pos : [right]");
			break;
		case phy::collisionPos::bottom:
			spdlog::info("collision Pos : [bottom]");
			break;
		}

		//spdlog::info("poss [{}, {}]", dir.x, dir.y);

		/*if (abs(obj->velocity.y) < 300) {
			obj->velocity.y = 0;
		}*/
		
	};
	physical->setTransform(phy::vector2d{
		(double)center.x,
		(double)center.y
		});
	physical->transformchanged = [this](phy::vector2d location) {
		auto radius = this->getRadius();
		this->frame = grc::rect(location.x - radius, location.y - radius,
								location.x + radius, location.y + radius);
	};
	physical->setType(radius);
	physical->velocity.x = 200;
	physical->velocity.y = 1000;
	physical->gravity = -200;
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
