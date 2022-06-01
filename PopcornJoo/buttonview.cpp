#include <spdlog/spdlog.h>
#include "buttonview.h"

grc::buttonview::buttonview(grc::rect f, int defaultImage, int downImage, int hoverImage) : view(f, defaultImage)
{
	this->defaultImage = defaultImage;
	this->downImage = downImage;
	this->hoverImage = hoverImage;
}

bool grc::buttonview::render(long long tick)
{
	if (!getHidden()) {
		switch (state)
		{
		case grc::buttonstate::mouseDown:
			if (downImage != -1) {
				view::drawImage(this->frame, downImage);
			}
			break;
		case grc::buttonstate::mouseUp:
			if (hoverImage != -1) {
				view::drawImage(this->frame, hoverImage);
			}
			else if (defaultImage != -1) {
				view::drawImage(this->frame, defaultImage);
			}
			break;
		case grc::buttonstate::mouseHover:
			if (hoverImage != -1) {
				view::drawImage(this->frame, hoverImage);
			}
			break;
		case grc::buttonstate::mouseLeave:
			if (defaultImage != -1) {
				view::drawImage(this->frame, defaultImage);
			}
			break;
		default:
			if (defaultImage != -1) {
				spdlog::error("buttonview : 잘못된 클릭 데이터 접근");
				view::drawImage(this->frame, defaultImage);
			}
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

grc::mouseclick grc::buttonview::click(int state, int x, int y)
{
	//spdlog::info("buttonview - click : [{}, {}, {}]", state, x, y);
	mouseclick value =  view::click(state, x, y);
	if (value == mouseclick::ownLevel) {
		this->state = (buttonstate)state;
		if (mouseEvent) {
			mouseEvent(this, (buttonstate)state);
		}
	}
	return value;
}

int grc::buttonview::keyboard(unsigned char key, int x, int y)
{
	return view::keyboard(key, x, y);
}

int grc::buttonview::mouse(int x, int y)
{
	int value = view::mouse(x, y);
	if (this->frame.exists(grc::point{ x, y })) {
		if (mouseEvent) {
			mouseEvent(this, grc::buttonstate::mouseHover);
		}
		this->state = grc::buttonstate::mouseHover;
	}
	else {
		//if (this->state == grc::buttonstate::mouseHover) {
		if (mouseEvent) {
			mouseEvent(this, grc::buttonstate::mouseLeave);
		}
		this->state = grc::buttonstate::mouseLeave;
		//}
	}
	return value;
}
