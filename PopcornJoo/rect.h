#pragma once
#include "point.h"
#include "size.h"

namespace grc
{
    struct rect
    {
        grc::point location;
        grc::size size;

        grc::point center() const
        {
            return { location.x + (size.width / 2), location.y + (size.height / 2) };
        }
    };

}