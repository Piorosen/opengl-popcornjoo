#pragma once
#define GL_SILENCE_DEPRECATION

#include <string>
#include <memory>

#include "color.h"
#include "rect.h"

namespace grc
{
    class render
    {
    private:
    public:
        static std::unique_ptr<grc::render> shared;

        

    protected:
    };
}

std::unique_ptr<grc::render> grc::render::shared = std::make_unique<grc::render>();
