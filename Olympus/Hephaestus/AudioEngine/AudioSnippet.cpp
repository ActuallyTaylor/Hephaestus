/*
    AudioSnippet.cpp
    Zachary lineman
    2/23/22
    
    =================
    DESCRIPTION
    =================
*/

#include "AudioSnippet.hpp"

AudioSnippet::AudioFile::AudioFile(int chan, int sampleRate, int bitsPerSample, int dataSize, unsigned int format, char *data) {
    this->chan = chan;
    this->sampleRate = sampleRate;
    this->bitsPerSample = bitsPerSample;
    this-> dataSize = dataSize;
    this->format = format;
    this->data = data;
}

AudioSnippet::AudioFile::AudioFile() { }


AudioSnippet::AudioSnippet(AudioFile audio, ALCdevice *device, ALCcontext *context) {
    chan = audio.chan;
    sampleRate = audio.sampleRate;
    bitsPerSample = audio.bitsPerSample;
    dataSize = audio.dataSize;
    format = audio.format;
    data = audio.data;

    this->device = device;
    this->context = context;
    this->isPaused = false;
};

void AudioSnippet::play() {
    if (isPaused && hasBeenCreated) {
        alSourcePlay(sourceID);
        checkOpenALError("alSourcePlay_fromPaused");
    } else {
        hasBeenCreated = true;
        alGenSources((ALuint)1, &sourceID);
        checkOpenALError("AL_GenSources");

        alSourcef(sourceID, AL_PITCH, 1);
        checkOpenALError("AL_Pitch");

        alSourcef(sourceID, AL_GAIN, 1);
        checkOpenALError("AL_Gain");

        alSource3f(sourceID, AL_POSITION, 0, 0, 0);
        checkOpenALError("AL_Position");

        alSource3f(sourceID, AL_VELOCITY, 0, 0, 0);
        checkOpenALError("AL_Velocity");

        alSourcei(sourceID, AL_LOOPING, AL_FALSE);
        checkOpenALError("alSourcei");

        alGenBuffers((ALuint)1, &bufferID);
        checkOpenALError("alGenBuffers");

        alBufferData(bufferID, format, data, dataSize, sampleRate);
        checkOpenALError("alBufferData");

        alSourcei(sourceID, AL_BUFFER, bufferID);
        checkOpenALError("alSourcei");

        alSourcePlay(sourceID);
        checkOpenALError("alSourcePlay");
    }
}


void AudioSnippet::pause() {
    isPaused = true;
    alSourcePause(sourceID);
    checkOpenALError("alSourcePause");
}

void AudioSnippet::close() {
    alDeleteSources(1, &sourceID);
    alDeleteBuffers(1, &bufferID);

    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);

//    // Dispatch a thread that will delete the audio once it is done playing
//    std::thread audioStateThread { [=](){
//        std::cout << "Open Thread" << std::endl;
//        int sourceState {};
//
//        alGetSourcei(sourceID, AL_SOURCE_STATE, &sourceState);
////        while (sourceState == AL_PLAYING) {
////            alGetSourcei(sourceState, AL_SOURCE_STATE, &sourceState);
////        }
//
//        std::cout << "Worker Thread Completed" << std::endl;
//
//    }};
//
//    audioStateThread.detach();

}

bool AudioSnippet::checkOpenALError(std::string caller) {
    // Check for an error
    ALCenum error = alGetError();
    if(error != AL_NO_ERROR) {
        std::cerr << caller << " ";
        switch(error) {
            case AL_INVALID_NAME:
                std::cerr << "AL_INVALID_NAME: a bad name (ID) was passed to an OpenAL function";
                break;
            case AL_INVALID_ENUM:
                std::cerr << "AL_INVALID_ENUM: an invalid enum value was passed to an OpenAL function";
                break;
            case AL_INVALID_VALUE:
                std::cerr << "AL_INVALID_VALUE: an invalid value was passed to an OpenAL function";
                break;
            case AL_INVALID_OPERATION:
                std::cerr << "AL_INVALID_OPERATION: the requested operation is not valid";
                break;
            case AL_OUT_OF_MEMORY:
                std::cerr << "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory";
                break;
            default:
                std::cerr << "UNKNOWN AL ERROR: " << error;
                break;
        }
        std::cerr << std::endl;
        return false;
    }
    // Clear the error stack
    alGetError();
    return true;
}

