#ifndef AUDIO_MODULE_IMPORTED
#define AUDIO_MODULE_IMPORTED

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <string>


class MiniaudioEngine
{
public:

    MiniaudioEngine();
    ~MiniaudioEngine();

    void Play(std::string audio_file_name);

private:
    ma_result result_;
    ma_engine engine_;
};

#endif