#pragma once

#include "rect.h"
#include "color.h"

#include <string>
#include <vector>
#include <memory>
#include <optional>

namespace grc
{
    class view
    {
    private:
    public:
        view(grc::rect f, grc::color b)
        {
            frame = f;
            background = b;
        }

        view(grc::rect f, int backgroundImage) {
            frame = f;
            this->backgroundImage = backgroundImage;
        }

        std::vector<std::shared_ptr<grc::view>> controls;
        std::optional<int> backgroundImage;
        grc::rect frame;
        grc::color background;

        void setHidden(bool value);
        bool getHidden() const;

        virtual bool render() const;
        virtual int click(int state, int x, int y);

    protected:
        bool isHidden = false;
    /*    int borderSize = 0;
        grc::color borderColor = grc::color(0xffffffff);*/

        void drawRect(grc::rect size, grc::color color) const;
        void drawCircle(grc::point pt, float radius, grc::color color) const;
        void drawLine(grc::point x, grc::point y, float thin, grc::color color) const;
        void drawImage(grc::rect size, unsigned int imageId) const;
        void drawBitmapText(std::string text, grc::point pos) const;
    };
}