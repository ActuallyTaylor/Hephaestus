/*
    AudioEngine.cpp
    Zachary lineman
    1/20/22
    
    =================
    DESCRIPTION
    =================
*/

#include <Hephaestus/AudioEngine/AudioEngine.hpp>

/*
 * Checks to see if the machine is a big endian machine or little endian.
 * This is done be checking whether the first byte of the int a is either a 0 or a 1.
 * This is done because in a big endian machine the 1 will be at the very end whereas in a little endian machine 0 will be in the beginning
 * This is because in a little endian machine is a reversed byte order.
 */
bool isBigEndian() {
    int a= 1;
    return !((char*) &a)[0]; // Cast to a char array
}

int convertToInt(char* buffer, int len) {
    int a = 0;
    if (!isBigEndian()) {
        for (int i = 0; i < len; i++) {
            ((char *) &a)[i] = buffer[i];
        }
    } else {
        for (int i = 0; i<len; i++) {
            ((char*)&a)[3 - i] = buffer[i];
        }
    }
    return a;
}

AudioEngine::AudioEngine() {
    device = alcOpenDevice(NULL);
    if (!device) {
        printf("Error Opening AL Device\n");
    } else {
        printf("Opened AL Device\n");
    }
    context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context)) {
        printf("Error Opening AL Context\n");
    }
    checkOpenALError("AL create context");
}

AudioEngine::~AudioEngine() { }

AudioSnippet AudioEngine::createAudioSnippet(std::string path) {
    if (loadedAudioData.count(path) > 0) {
        std::cout << "Using cached audio data" << std::endl;
        AudioSnippet::AudioFile audio = loadedAudioData.at(path);
        return { audio, device, context };
    } else {
        std::cout << "Loading Audio File" << std::endl;
        int chan, sampleRate, bitsPerSample, dataSize;
        unsigned int format;
        char* data;

        data = loadWaveFile(path, chan, sampleRate, bitsPerSample, dataSize, format);
        AudioSnippet::AudioFile audio = AudioSnippet::AudioFile(chan, sampleRate, bitsPerSample, dataSize, format, data);
        loadedAudioData.insert(std::pair<std::string, AudioSnippet::AudioFile>(path, audio));
        return { audio, device, context };
    }
}

bool AudioEngine::checkOpenALError(std::string caller) {
    // Check for an error
    ALenum error = alGetError();
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

char *AudioEngine::loadWaveFile(std::string path, int& chan, int& sampleRate, int& bitsPerSample, int& dataSize, unsigned int& format) {
    char buffer[4];
    std::ifstream fileStream {path.c_str(), std::ios::binary};

    // Read the first four bytes to the buffer
    fileStream.read(buffer, 4); // RIFF
    if (strncmp(buffer, "RIFF", 4) != 0) {
        std::cout << "Invalid WAVE file: NO RIFF" << std::endl;
        return NULL;
    } else {
        std::cout << "Valid WAVE file: RIFF" << std::endl;
    }

    fileStream.read(buffer, 4); // Chunk Size
    fileStream.read(buffer, 4); // Format
    if (strncmp(buffer, "WAVE", 4) != 0) {
        std::cout << "Invalid WAVE file: NO WAVE" << std::endl;
        return NULL;
    } else {
        std::cout << "Valid WAVE file: WAVE" << std::endl;
    }

    fileStream.read(buffer, 4); // Subchunk1ID: fmt
    if (strncmp(buffer, "fmt", 3) != 0) {
        std::cout << "Invalid WAVE file: fmt - " << buffer << std::endl;
        return NULL;
    } else {
        std::cout << "Valid WAVE file: fmt" << std::endl;
    }

    fileStream.read(buffer, 4); // SubChunk1Size: 16
    fileStream.read(buffer, 2); // AudioFormat: Should be 1, if not it is compressed
    if (convertToInt(buffer, 2) != 1) {
        std::cout << "Invalid WAVE file: AudioFormat, audio is compressed - " << buffer << std::endl;
        return NULL;
    } else {
        std::cout << "Valid WAVE file: AudioFormat " << convertToInt(buffer, 2) << std::endl;
    }

    fileStream.read(buffer, 2); // NumChannels: Mono = 1, Stereo = 2, etc.
    chan = convertToInt(buffer, 2); // Send back the number of channels

    if (chan == 1) {
        if (bitsPerSample == 8) {
            format = AL_FORMAT_MONO8;
            std::cout << "Valid WAVE file: Mono 8" << std::endl;
        } else {
            format = AL_FORMAT_MONO16;
            std::cout << "Valid WAVE file: Mono 16" << std::endl;
        }
    } else {
        if (bitsPerSample == 8) {
            format = AL_FORMAT_STEREO8;
            std::cout << "Valid WAVE file: Stereo 8" << std::endl;
        } else {
            format = AL_FORMAT_STEREO16;
            std::cout << "Valid WAVE file: Stereo 16" << std::endl;
        }
    }

    fileStream.read(buffer, 4); // SampleRate: 8000, 44100, etc
    sampleRate = convertToInt(buffer, 4); // Send back the Sample Rate

    fileStream.read(buffer, 4); // ByteRate
    fileStream.read(buffer, 2); // BlockAlign

    fileStream.read(buffer, 2); // BitsPerSample: 8 bits = 8, 16 bits = 16, etc.
    bitsPerSample = convertToInt(buffer, 2); // Send back the Bits Per Sample

    fileStream.read(buffer, 4); // Should Be: SubChunk2ID: data
    if (strncmp(buffer, "data", 4) != 0) {
        if (strncmp(buffer, "fact", 4) != 0) {
            std::cout << "Unknown next chunk |" << buffer << "|" << std::endl;
            return nullptr;
        } else {
            fileStream.read(buffer, 4); // NumberOfSamples
            fileStream.read(buffer, 4); // Data
        }

        fileStream.read(buffer, 4); // Should Be: Subchunk2ID: data
        // TODO: Read more possible chunks
        // https://uttori.github.io/uttori-audio-wave/

        if (strncmp(buffer, "data", 4) != 0) {
            std::cout << "Invalid WAVE file: data |" << buffer << "|" << std::endl;
            return nullptr;
        } else {
            std::cout << "Valid WAVE file: data" << std::endl;
        }
    } else {
        std::cout << "Valid WAVE file: data" << std::endl;
    }

    fileStream.read(buffer, 4); // SubChunk2Size: Size of the data chunk
    dataSize = convertToInt(buffer, 4);
    std::cout << "Data Size: " << dataSize << std::endl;

    char* data = new char[dataSize];
    fileStream.read(data, dataSize);

    char* restOfFile = new char[1];
    while (!fileStream.eof()) {
        fileStream.read(restOfFile, 1);
        std::cout << restOfFile;
    }
    std::cout << std::endl;


    std::cout << "Finished Reading WAVE file - size: " << dataSize << std::endl;

    return data;
}

void AudioEngine::removeAudioFile(std::string path) {
    loadedAudioData.erase(path);
}

void AudioEngine::loadAudioFile(std::string path) {
    int chan, sampleRate, bitsPerSample, dataSize;
    unsigned int format;
    char* data = loadWaveFile(path, chan, sampleRate, bitsPerSample, dataSize, format);

    AudioSnippet::AudioFile audio = AudioSnippet::AudioFile(chan, sampleRate, bitsPerSample, dataSize, format, data);
    loadedAudioData.insert(std::pair<std::string, AudioSnippet::AudioFile>(path, audio));
}

