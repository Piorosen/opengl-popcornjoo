#include <spdlog/spdlog.h>
#include "ballview.h"
#include "buttonview.h"

grc::ballview::ballview(grc::point center, int radius, grc::color ballColor) 
	: view(grc::rect(center.x - radius,
					 center.y - radius,
					 center.x + radius,
					 center.y + radius), ballColor)
{
	this->radius = radius;
	this->initCenter = center;
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
			obj->velocity.y = -obj->velocity.y;
		}
		else if (info.other == phy::collisionPos::left || info.other == phy::collisionPos::right) {
			obj->setTransform(phy::vector2d{ t.x - obj->velocity.x * (tick / 1000.0), t.y });
			obj->velocity.x *= -1;
		}
		else {
			obj->setTransform(phy::vector2d{ t.x, t.y - obj->velocity.y * (tick / 1000.0) });
			obj->velocity.y = -obj->velocity.y;
		}
		obj->velocity = obj->velocity * 0.9;

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
	};
	physical->setTransform(phy::vector2d{
		(double)center.x,
		(double)center.y
		});
	physical->transformchanged = [this](phy::vector2d location) {
		auto radius = this->getRadius();
		auto speed = this->getPhysical()->velocity.magnitude();
		if (this->getPhysical()->getHidden()) {
			return;
		}
		spdlog::info("ball speed {}", speed);
		if (speed < 100 || speed > 5000) {
			if (ballDeadEvent) {
				ballDeadEvent(this);
			}
		}
		else {
			this->frame = grc::rect(location.x - radius, location.y - radius,
									location.x + radius, location.y + radius);
		}
	};
	physical->setType(radius);
	physical->gravity = -200;
	physical->mesh = 10;
	physical->setHidden(true);
}

std::shared_ptr<phy::object> grc::ballview::getPhysical() const
{
	return physical;
}

void grc::ballview::reset()
{
	physical->setHidden(true);
	auto center = this->initCenter;

	this->frame = grc::rect(center.x - radius,
		center.y - radius,
		center.x + radius,
		center.y + radius);

	physical->velocity = phy::vector2d {
		0,0
	};
	physical->setTransform(phy::vector2d{
		(double)center.x,
		(double)center.y
		});

}

void grc::ballview::shot(grc::point click)
{
	spdlog::info("SHOT!");
	phy::vector2d pos{
		(double)click.x,
		(double)click.y
	};

	auto power = (pos - physical->getTransform()).normalization() * 2000;
	physical->velocity.x = power.x;
	physical->velocity.y = power.y;
	physical->setHidden(false);
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
	auto p = view::click(state, x, y);
	auto pp = (grc::buttonstate)state;
	if (pp == grc::buttonstate::mouseUp) {
		auto pos = grc::point{ x, y };
		if (this->clickRange.exists(pos)) {
			shot(pos);
		}
	}
	return p;
}

int grc::ballview::mouse(int x, int y)
{
	return view::mouse(x, y);
}
