#pragma once
#include <functional>

#include "view.h"

namespace grc
{
    class scene
    {
    private:
    public:
        virtual void mouseEvent(int button, int state, int x, int y);
        virtual void mouseMotionEvent(int x, int y);
        virtual void keyboardEvent(unsigned char key, int x, int y);
        virtual void render(long long tick);
        
        std::function<void(scene*, int button, int state, int x, int y)> mouse;
        std::function<void(scene*, int x, int y)> mouseMotion;
        std::function<void(scene*, unsigned char key, int x, int y)> keyboard;
        std::function<void(scene*, long long tick)> renderEvent;

        std::vector<std::shared_ptr<grc::view>> view;

        std::function<void(std::weak_ptr<scene>)> closeEvent;
        std::function<void(std::weak_ptr<scene>)> openEvent;
    protected:
    };
}