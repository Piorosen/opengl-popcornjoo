#include <spdlog/spdlog.h>
#include "buttonview.h"

grc::buttonview::buttonview(grc::rect f, int defaultImage, int downImage, int hoverImage) : view(f, defaultImage)
{
}

bool grc::buttonview::render(long long tick)
{
	
	return false;
}

int grc::buttonview::click(int state, int x, int y)
{
	
	spdlog::info("buttonview - click : [{}, {}, {}]", state, x, y);
	if (this->frame.exists({ x, y })) {
		mouseEvent.Invoke(this, (buttonstate)state);
	}
	return 0;
}

int grc::buttonview::keyboard(unsigned char key, int x, int y)
{
	return 0;
}
