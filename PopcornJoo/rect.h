#pragma once
#include "point.h"
#include "size.h"

namespace grc
{
    struct rect
    {
        grc::point location;
        grc::size size;

        rect(double left, double top, double right, double bottom) {
            location.x = left;
            location.y = top;
            size.width = right - left;
            size.height = bottom - top;
        }

        rect(const rect& lvalue) {
            location = lvalue.location;
            size = lvalue.size;
        }
        rect() {
            location = { 0, 0 };
            size = { 0,0 };
        }

        grc::point center() const
        {
            return { location.x + (size.width / 2), location.y + (size.height / 2) };
        }

        bool exists(grc::point pt) const {
            if (location.x < pt.x && pt.x < location.x + size.width &&
                location.y < pt.y && pt.y < location.y + size.height) {
                return true;
            }
            else {
                return false;
            }
        }
    };

}