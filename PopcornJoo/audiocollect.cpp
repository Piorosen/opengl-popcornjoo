#include "audiocollect.h"

std::unique_ptr<grc::audiocollect> grc::audiocollect::shared = std::make_unique<grc::audiocollect>();

std::optional<FMOD::Channel*> grc::audiocollect::get(std::string file)
{
    if (playLists.find(file) != playLists.end())
    {
        return playLists[file];
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
        spdlog::error("audio load fail \"{}\", [ {} ]", file, result);
    }

    return (grc::audioresult)result;
}

grc::audioresult grc::audiocollect::play(std::string audio)
{
	FMOD::Channel* output;
	auto result = pSystem->playSound(audioId[audio], NULL, 0, &output);
	this->playLists[audio] = output;
	if (result == FMOD_OK) {
		spdlog::info("audio play success \"{}\", [ {} ]", audio, result);
	}
	else {
		spdlog::error("audio play fail \"{}\", [ {} ]", audio, result);
	}

	return (grc::audioresult)result;
}

grc::audioresult grc::audiocollect::set(std::string audio, bool paused)
{
    auto data = get(audio);
    if (data.has_value()) {
        data.value()->setPaused(paused);
        spdlog::info("오디오가 중지 성공. [{}]", audio);
        return audioresult::OK;
    }
    else {
        if (!paused) {
            play(audio);
        }
        else {
            spdlog::error("오디오가 없습니다. [{}]", audio);
        }
        return audioresult::ERR_NOTREADY;
    }
}

