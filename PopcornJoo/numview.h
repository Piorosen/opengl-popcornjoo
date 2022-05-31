#pragma once
#include <vector>
#include <functional>
#include "view.h"

#include "buttonview.h"
    
namespace grc
{
    class numview : public view
    {
    private:
        std::vector<int> numListImage;
        int num = 0;

    public:
        // 전체를 렌더링 할 시간 루프 시간.
        numview(grc::rect f, std::vector<int> numList, int defaultNum = 0);

        void setNum(int num) {
            this->num = num;
        }

        virtual bool render(long long tick) override;

    protected:
    };


}