#include "audio.hpp"

#include <iostream>


MiniaudioEngine::MiniaudioEngine()
{
    result_ = ma_engine_init(NULL, &engine_);
    if (result_ != MA_SUCCESS) {
        std::cerr << "Miniaudio engine not initiailzed error!\n";
    }
}

MiniaudioEngine::~MiniaudioEngine()
{
    ma_engine_uninit(&engine_);
}

void MiniaudioEngine::Play(std::string audio_file_name)
{
    ma_engine_play_sound(&engine_, audio_file_name.c_str(), 0);
}
