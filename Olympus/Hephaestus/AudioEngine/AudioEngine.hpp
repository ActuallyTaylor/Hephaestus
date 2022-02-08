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

class AudioEngine {
private:

public:
    AudioEngine();
    ~AudioEngine();

    void play2D(std::string path);
};


#endif //OLYMPUS_AUDIOENGINE_HPP
