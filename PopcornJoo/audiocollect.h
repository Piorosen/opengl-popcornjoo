#pragma once
#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

#include <string>
#include <map>
#include <vector>
#include <optional>
#include <memory>
#include <spdlog/spdlog.h>

#include "audiomode.h"
#include "audioresult.h"

namespace grc
{
    class audiocollect
    {
    private:
        std::map<std::string, FMOD::Sound*> audioId;
        FMOD::System* pSystem;

    public:
        audiocollect() {
            auto d = FMOD::System_Create(&pSystem);
            pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
            if (d != FMOD_OK) {
                spdlog::error("audio driver fail!");
            }
            else {
                spdlog::info("audio driver success!");
            }
        }

        static std::unique_ptr<grc::audiocollect> shared;

        std::optional<FMOD::Sound*> get(std::string file);
        audioresult add(std::string file, audiomode mode = audiomode::DEFAULT);
        audioresult play(std::string audio, FMOD::Channel** output);


    protected:
    };
}


