/*
    AudioSnippet.cpp
    Zachary lineman
    2/23/22
    
    =================
    DESCRIPTION
    =================
*/

#include <Hephaestus/AudioEngine/AudioSnippet.hpp>

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
        checkOpenALError("AL_LOOPING");

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
    if (hasBeenCreated) {
        isPaused = true;
        alSourcePause(sourceID);
        checkOpenALError("alSourcePause");
    }
}

void AudioSnippet::close() {
    alDeleteSources(1, &sourceID);
    alDeleteBuffers(1, &bufferID);

    device = alcGetContextsDevice(context);
    alcMakeContextCurrent(nullptr);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

bool AudioSnippet::checkOpenALError(std::string caller) {
    // Check for an error
    #if __linux__
    ALenum error = alGetError();
    #elif __APPLE__
    ALCenum error = alGetError();
    #endif
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

/*
 * Positive X: Right
 * Negative X: Left
 *
 * Positive Y: Forward
 * Negative Y: Backwards
 *
 * Positive Z: Above
 * Negative z: Below
 */
void AudioSnippet::changePosition(glm::vec3 position) {
    if (format != AL_FORMAT_MONO8 || format != AL_FORMAT_MONO16) {
        std::cerr << "Change position only works with Mono sound" << std::endl;
        return;
    }
    alSource3f(sourceID, AL_POSITION, position.x, position.y, position.z);
    checkOpenALError("AL_Position");
}

