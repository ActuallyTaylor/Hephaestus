/*
    AudioEngine.hpp
    Zachary lineman
    1/20/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_AUDIOENGINE_HPP
#define OLYMPUS_AUDIOENGINE_HPP
#include <iostream>
#include <string>
#include "../Library/irrKlang/include/irrKlang.h"

class AudioEngine {
private:

public:
    AudioEngine();
    ~AudioEngine();
    irrklang::ISoundEngine* source = irrklang::createIrrKlangDevice();

    void play2D(std::string path);
};


#endif //OLYMPUS_AUDIOENGINE_HPP
