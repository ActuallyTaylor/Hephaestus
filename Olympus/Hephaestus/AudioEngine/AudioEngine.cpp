/*
    AudioEngine.cpp
    Zachary lineman
    1/20/22
    
    =================
    DESCRIPTION
    =================
*/

#include "AudioEngine.hpp"

AudioEngine::AudioEngine() {
    if (!source) {
        std::cout << "Error Initliazing Audio Engine" << std::endl;
    }
}

AudioEngine::~AudioEngine() {
    source->drop();
}

void AudioEngine::play2D(std::string path) {
    source->play2D(path.c_str());
}

