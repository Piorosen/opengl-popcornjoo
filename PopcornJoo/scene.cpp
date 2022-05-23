#include "scene.h"

void grc::scene::mouseEvent(int button, int state, int x, int y)
{
    if (mouse != nullptr) {
        mouse(this, button, state, x, y);
    }
    if (button == 0)
    {
        for (auto& v : view)
        {
            v->click(state, x, y);
        }
    }
}

void grc::scene::keyboardEvent(unsigned char key, int x, int y)
{
    if (keyboard != nullptr) {
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