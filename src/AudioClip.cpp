#include <sstream>
#include "AudioClip.h"
#include "AudioSystem.h"
#include "Logger.h"

AudioClip::AudioClip(const std::string &filepath)
{
    if (SDL_LoadWAV(filepath.c_str(), &audio_spec, &buffer, &length) == nullptr) {
        std::ostringstream stream;
        stream << "Error occured loading WAV file at path '" << filepath << "'! Zeroing AudioClip properties...";
        Logger::Write(stream.str());

        SDL_zero(audio_spec);
        buffer = nullptr;
        length = 0;
    }
    
    Reset();
}

AudioClip::~AudioClip()
{
    SDL_FreeWAV(buffer);
}

// Only works for a single traversal of the buffer.
void AudioClip::Callback(void *userdata, Uint8 *stream, int len)
{
    if (pointer >= buffer + length) {
        SDL_memset(stream, 0, len);
        AudioSystem::FreeClip(this);
        return;
    }

    for (int i = 0; i < len; i++) {
        stream[i] = (pointer < buffer + length) ? *pointer : 0;
        pointer++;
    }
}

void AudioClip::Reset()
{
    pointer = buffer;
}

bool AudioClip::Good()
{
    return buffer != nullptr;
}

void LoopedAudioClip::Callback(void *userdata, Uint8 *stream, int len)
{
    for (int i = 0; i < len; i++) {
        stream[i] = *pointer;
        pointer++;

        // Upon reaching the end, wrap around to the beginning of the buffer.
        if (pointer == buffer + length) {
            Reset();
        }
    }
}
