#pragma once

#include <string>
#include <map>
#include <optional>
#include <memory>

namespace graphics
{
    class imagecollect
    {
    private:
        std::map<std::string, unsigned int> textureId;

    public:
        static std::unique_ptr<graphics::imagecollect> shared;

        std::optional<int> get(std::string file);
        int add(std::string file);

    protected:
    };
}