#pragma once

namespace display { 
    struct point
    {
        int x, y;
    };
    struct size { 
        int width, height;
    };
    struct rect
    {
        point point;
        size size;
    };

    struct monitor { 
        rect rect;
        int refreshRate;
    };
}
