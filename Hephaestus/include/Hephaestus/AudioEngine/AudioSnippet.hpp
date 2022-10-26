/*
    AudioSnippet.hpp
    Zachary lineman
    2/23/22
    
    =================
    DESCRIPTION
    =================
*/

#ifndef OLYMPUS_AUDIOSNIPPET_HPP
#define OLYMPUS_AUDIOSNIPPET_HPP
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <thread>
#include <glm/glm.hpp>

#if __linux__
#include <AL/al.h>
#elif __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#endif

class AudioSnippet {
public:
    struct AudioFile {
        int chan, sampleRate, bitsPerSample, dataSize;
        unsigned int format;
        char* data;

        AudioFile();
        AudioFile(int chan, int sampleRate, int bitsPerSample, int dataSize, unsigned  int format, char* data);
    };

    AudioSnippet(AudioFile audio, ALCdevice *device, ALCcontext *context);
    void play();
    void pause();
    void close();

    void changePosition(glm::vec3 position);
private:
    std::map<std::string, AudioFile> *loadedAudioData { };

    ALuint sourceID { 0 };
    ALuint bufferID { 0 };

    int chan, sampleRate, bitsPerSample, dataSize;
    unsigned int format;
    char* data;

    ALCdevice *device;
    ALCcontext *context;

    bool isPaused { false };
    bool hasBeenCreated { false };

    static bool checkOpenALError(std::string caller);
};


#endif //OLYMPUS_AUDIOSNIPPET_HPP
