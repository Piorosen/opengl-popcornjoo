#include <spdlog/spdlog.h>
#include "scene.h"

void grc::scene::mouseEvent(int button, int state, int x, int y)
{
    if (mouse) {
        mouse(this, button, state, x, y);
    }
    if (button == 0)
    {
        spdlog::info("{}, {}, {}, {}", button, state, x, y);
        for (auto& v : view)
        {
            if (v) {
                v->click(state, x, y);
            }
        }
    }
}

void grc::scene::mouseMotionEvent(int x, int y)
{
    if (mouseMotion) {
        mouseMotion(this, x, y);
    }
	for (auto& v : view)
	{
		v->mouse(x, y);
	}
}

void grc::scene::keyboardEvent(unsigned char key, int x, int y)
{
    if (keyboard) {
        this->keyboard(this, key, x, y);
    }
    for (auto& v : view)
    {
        v->keyboard(key, x, y);
    }
}

void grc::scene::render(long long tick) const
{
    for (auto& v : view)
    {
        v->render(tick);
    }
}