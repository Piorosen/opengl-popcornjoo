#include <spdlog/spdlog.h>

#include "colorbuttonview.h"


grc::colorbuttonview::colorbuttonview(grc::rect f, grc::color defaultColor, grc::color downColor, grc::color hoverColor) : view(f, defaultColor)
{
	this->defaultColor = defaultColor;
	this->downColor = downColor;
	this->hoverColor = hoverColor;
}

bool grc::colorbuttonview::render(long long tick)
{
	if (!getHidden()) {
		switch (state)
		{
		case grc::buttonstate::mouseDown:
			view::drawRect(this->frame, downColor);
			break;
		case grc::buttonstate::mouseUp:
			view::drawRect(this->frame, hoverColor);
			break;
		case grc::buttonstate::mouseHover:
			view::drawRect(this->frame, hoverColor);
			break;
		case grc::buttonstate::mouseLeave:
			view::drawRect(this->frame, defaultColor);
			break;
		default:
			spdlog::error("buttonview : 잘못된 클릭 데이터 접근");
			view::drawRect(this->frame, defaultColor);
			break;
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

grc::mouseclick grc::colorbuttonview::click(int state, int x, int y)
{
	spdlog::info("colorbuttonview - click : [{}, {}, {}]", state, x, y);
	mouseclick value = view::click(state, x, y);
	if (value == mouseclick::ownLevel) {
		this->state = (buttonstate)state;
		mouseEvent.Invoke(this, (buttonstate)state);
	}
	return value;
}

int grc::colorbuttonview::keyboard(unsigned char key, int x, int y)
{
	return view::keyboard(key, x, y);
}

int grc::colorbuttonview::mouse(int x, int y)
{
	int value = view::mouse(x, y);
	if (this->frame.exists(grc::point{ x, y })) {
		if (this->state == grc::buttonstate::mouseLeave) {
			spdlog::info("hover");
			mouseEvent.Invoke(this, grc::buttonstate::mouseHover);
			this->state = grc::buttonstate::mouseHover;
		}
	}
	else {
		if (this->state == grc::buttonstate::mouseHover) {
			spdlog::info("leave");
			mouseEvent.Invoke(this, grc::buttonstate::mouseLeave);
			this->state = grc::buttonstate::mouseLeave;
		}
	}
	return value;
}
