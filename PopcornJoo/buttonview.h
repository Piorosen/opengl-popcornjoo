#pragma once
#include <vector>

#include "view.h"

namespace grc
{
    enum class buttonstate {
        /*leave,
        hover,*/
        mouseDown = 0,
        mouseUp = 1,
        mouseHover = 2,
        mouseLeave = 3,
    };

    class buttonview : public view
    {
    private:
        int timer = 0;
        bool playTimer = false;
        buttonstate state = buttonstate::mouseLeave;

        int defaultImage;
        int downImage;
        int hoverImage;

    public:
        // 전체를 렌더링 할 시간 루프 시간.
        buttonview(grc::rect f, int defaultImage = -1, int downImage = -1, int hoverImage = -1);
        
        std::function<void(buttonview*, buttonstate)> mouseEvent;

        virtual bool render(long long tick) override;
        virtual mouseclick click(int state, int x, int y) override;
        virtual int keyboard(unsigned char key, int x, int y) override;
        virtual int mouse(int x, int y) override;

    protected:
        int mouseDownTiming = 100;
    };


}