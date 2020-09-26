#include <algorithm>
#include <vector>
#include "AudioSystem.h"
#include "Logger.h"

std::vector<AudioClip *> playing;
SDL_AudioDeviceID device_id = 0;

// Gather all audio streams from currently playing clips and merges them into one.
void AudioCallback(void *userdata, Uint8 *stream, int len)
{
    std::vector<Uint8 *> streams;
    
    for (int i = 0; i < playing.size(); i++) {
        Uint8 *streamptr = new Uint8[len];
        streams.push_back(streamptr);
        playing[i]->Callback(userdata, streamptr, len);
    }

    for (int i = 0; i < len; i++) {
        int total = 0;
        for (auto istream : streams) {
            total += istream[i];
        }
        
        stream[i] = total;
    }

    for (auto istream : streams) {
        delete istream;
    }
}

void Initialize()
{
    // @TODO: handle errors.
    const char *device = SDL_GetAudioDeviceName(0, 0);

    // @TODO: pull this stuff out into constants.
    SDL_AudioSpec want, have;
    SDL_zero(want);
    want.freq = 44100;
    want.format = AUDIO_S16;
    want.channels = 2;
    want.samples = 4096;
    want.callback = &AudioCallback;

    // @TODO: handle errors.
    device_id = SDL_OpenAudioDevice(device, 0, &want, &have, 0);
    SDL_PauseAudioDevice(device_id, 0);
}

void AudioSystem::PlayClip(AudioClip *clip)
{
    if (!clip->Good()) {
        Logger::Write("Skipping queueing up uninitialized AudioClip...");
        return;
    }

    if (playing.size() == 0) {
        Initialize();
    }

    playing.push_back(clip);
}

void AudioSystem::FreeClip(AudioClip *clip)
{
    auto element = std::find(playing.begin(), playing.end(), clip);

    if (element != playing.end()) {
        playing.erase(element);
    }
}

void AudioSystem::ToggleSound(bool on)
{
    SDL_PauseAudioDevice(device_id, static_cast<int>(!on));
}
