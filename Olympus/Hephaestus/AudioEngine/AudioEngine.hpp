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
#include "../Library/AL/al.h"
#include "../Library/AL/alc.h"
#include "../Library/AudioFile.h"

// Currently, only allows for one audio stream playback at a time.
// Multiple buffers will be needed for multiple layer audio streaming.
class AudioEngine {
private:
    ALCdevice *device;
    ALCcontext *context;
    ALuint sourceID;
    ALuint bufferID;
    AudioFile<double> audioFile;

    static char* loadWaveFile(std::string path, int& chan, int& sampleRate, int& bps, int& dataSize, int format);
    bool checkOpenALError(std::string caller);

public:
    AudioEngine();
    ~AudioEngine();

    void play2D(std::string path);
};


#endif //OLYMPUS_AUDIOENGINE_HPP
