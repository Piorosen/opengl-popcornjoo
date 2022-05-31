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

    public:
        // 전체를 렌더링 할 시간 루프 시간.
        wallview(grc::rect rect, grc::color backgroundColor = grc::color(0x00ff00ff));

        std::shared_ptr<phy::object> getPhysical() const;

        std::function<void(wallview*)> mouseEvent;

        virtual bool render(long long tick) override;

    protected:
    };
}