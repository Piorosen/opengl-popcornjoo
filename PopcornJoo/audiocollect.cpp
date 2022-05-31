#include "audiocollect.h"

std::unique_ptr<grc::audiocollect> grc::audiocollect::shared = std::make_unique<grc::audiocollect>();

std::optional<FMOD::Sound*> grc::audiocollect::get(std::string file)
{
    if (audioId.find(file) != audioId.end())
    {
        return audioId[file];
    }
    else
    {
        return std::nullopt;
    }
}

grc::audioresult grc::audiocollect::add(std::string file, audiomode mode)
{
    FMOD::Sound* sound;
    auto result = this->pSystem->createSound(file.c_str(), (int)mode, NULL, &sound);
    audioId[file] = sound;
    if (result == FMOD_OK) {
        spdlog::info("audio load success \"{}\", [ {} ]", file, result);
    }
    else {
        spdlog::info("audio load fail \"{}\", [ {} ]", file, result);
    }

    return (grc::audioresult)result;
}

grc::audioresult grc::audiocollect::play(std::string audio, FMOD::Channel** output)
{
    auto result = pSystem->playSound(audioId[audio], NULL, 0, output);
    return (grc::audioresult)result;
}

