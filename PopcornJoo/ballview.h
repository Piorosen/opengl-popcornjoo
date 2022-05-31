#pragma once
#include <vector>
#include <functional>

#include "view.h"
#include "object.h"

namespace grc
{
    class ballview : public view
    {
    private:
        std::shared_ptr<phy::object> physical;
        int radius;
        grc::point initCenter;


    public:
        // 전체를 렌더링 할 시간 루프 시간.
        ballview(grc::point center, int radius, grc::color ballColor = grc::color(0xff00ffff));

        std::shared_ptr<phy::object> getPhysical() const;
        std::function<void(ballview*)> mouseEvent;

        void reset();
        void shot(grc::point clickPos);

        virtual bool render(long long tick) override;
        virtual mouseclick click(int state, int x, int y) override;
        virtual int mouse(int x, int y) override;

        int getRadius() const {
            return radius;
        }

    protected:
    };
}