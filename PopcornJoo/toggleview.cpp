#include "toggleview.h"

#include <spdlog/spdlog.h>

grc::toggleview::toggleview(grc::rect f, int on, int off) : view(f, off)
{
	onImage = on;
	offImage = off;
}

bool grc::toggleview::render(long long tick)
{
	if (!getHidden()) {
		if (this->toggle) {
			view::drawImage(this->frame, onImage);
		}
		else {
			view::drawImage(this->frame, offImage);
		}

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


grc::mouseclick grc::toggleview::click(int state, int x, int y)
{
	spdlog::info("toggleview - click : [{}, {}, {}]", state, x, y);
	mouseclick value = view::click(state, x, y);
	if (value == mouseclick::ownLevel) {
		this->toggle = !this->toggle;
		if (toggleEvent) {
			toggleEvent(this, this->toggle);
		}
	}
	return value;
}
