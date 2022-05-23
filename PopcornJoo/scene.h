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
        virtual void keyboardEvent(unsigned char key, int x, int y);
        virtual void render() const;
        
        std::function<void(scene*, int button, int state, int x, int y)> mouse;
        std::function<void(scene*, unsigned char key, int x, int y)> keyboard;

        std::vector<std::shared_ptr<grc::view>> view;

    protected:
    };
}