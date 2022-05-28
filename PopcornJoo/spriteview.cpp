#include <spdlog/spdlog.h>
#include <vector>

#include "spriteview.h"

grc::spriteview::spriteview(grc::rect f, std::vector<int> images) : view(f, grc::color())
{
	frame = f;
	this->images = images;
}

void grc::spriteview::play()
{
	this->playTimer = true;
}

void grc::spriteview::stop()
{
	this->playTimer = false;
}

void grc::spriteview::reset()
{
	this->timer = 0;
}

bool grc::spriteview::render(long long tick) {
	if (this->playTimer) {
		this->timer += tick;
	}

	if (!getHidden()) {
		int idx = (timer / (durationMS / images.size())) % images.size();
		view::drawImage(this->frame, images[idx]);
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
