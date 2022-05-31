#pragma once
#include <vector>
#include <functional>

#include "view.h"
#include "object.h"

namespace grc
{
    class wallview : public view
    {
    private:
        std::shared_ptr<phy::object> physical;
        int radius;
        bool isWall;

        int score;

    public:
        // 전체를 렌더링 할 시간 루프 시간.
        wallview(grc::rect rect, bool iswall = true, grc::color backgroundColor = grc::color(0x00ff00ff));

        void setIsWall(bool iswall);
        bool getIsWall() const;

        void setScore(int iswall);
        int getScore() const;

        std::function<void(wallview*)> brokenBlock;

        std::shared_ptr<phy::object> getPhysical() const;

        std::function<void(wallview*)> mouseEvent;

        virtual bool render(long long tick) override;

    protected:
    };
}