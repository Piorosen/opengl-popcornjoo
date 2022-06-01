#include "wallview.h"

#include <spdlog/spdlog.h>

grc::wallview::wallview(grc::rect rect, bool iswall, grc::color backgroundColor) : view(rect, backgroundColor)
{
	setIsWall(iswall);
	auto center = rect.center();
	physical = std::make_shared<phy::object>();
	physical->setTransform(phy::vector2d{
		(double)center.x,
		(double)center.y
		});
	physical->collisionevent = [this](std::weak_ptr<phy::object> own, std::weak_ptr<phy::object> others, phy::collisioninfo info, long long tick) {
		if (!this->getIsWall()) {
			auto ownP = own.lock();
			ownP->setHidden(true);
			this->setHidden(true);
			if (brokenBlock) {
				brokenBlock(this);
			}
			spdlog::info("remove");
		}
	};
	physical->setType(grc::rect(-rect.size.width / 2.0, -rect.size.height / 2.0,
								 rect.size.width / 2.0,  rect.size.height / 2.0));
	physical->gravity = 0;
	physical->mesh = INT_MAX;
}

void grc::wallview::setIsWall(bool iswall)
{
	this->isWall = iswall;
}

bool grc::wallview::getIsWall() const
{
	return isWall;
}

void grc::wallview::setScore(int iswall)
{
	score = iswall;
}

int grc::wallview::getScore() const
{
	return score;
}


std::shared_ptr<phy::object> grc::wallview::getPhysical() const
{
	return physical;
}

bool grc::wallview::render(long long tick)
{
	if (!getHidden()) {
		view::drawRect(frame, 0x000000ff);
		view::drawRect(grc::rect(frame.location.x + 2, frame.location.y + 2,
								 frame.location.x + frame.size.width - 2, frame.location.y + frame.size.height - 2), background);
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

