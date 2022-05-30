#pragma once
#include <vector>

#include "buttonview.h"

namespace grc
{
    class colorbuttonview : public view
    {
    private:
        int timer = 0;
        bool playTimer = false;
        buttonstate state = buttonstate::mouseLeave;

        grc::color defaultColor;
        grc::color downColor;
        grc::color hoverColor;

    public:
        // 전체를 렌더링 할 시간 루프 시간.
        colorbuttonview(grc::rect f, grc::color defaultColor = grc::color(0xfcfcfc),
                                     grc::color downColor = grc::color(0xcccccc),
                                     grc::color hoverColor = grc::color(0xdddddd));

        std::function<void(colorbuttonview*, buttonstate)> mouseEvent;

        virtual bool render(long long tick) override;
        virtual mouseclick click(int state, int x, int y) override;
        virtual int keyboard(unsigned char key, int x, int y) override;
        virtual int mouse(int x, int y) override;

    protected:
    };


}