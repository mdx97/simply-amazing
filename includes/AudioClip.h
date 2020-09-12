#ifndef AUDIOCLIP_H
#define AUDIOCLIP_H

#include "SDL.h"
#include <string>

class AudioClip
{
public:
    AudioClip(const std::string &filepath);
    ~AudioClip();
    virtual void Callback(void *userdata, Uint8 *stream, int len);
    void Reset();
    bool Good();
    
protected:
    SDL_AudioSpec audio_spec;
    Uint8 *buffer = nullptr;
    Uint8 *pointer = nullptr;
    Uint32 length;
};

class LoopedAudioClip : public AudioClip
{
public:
    using AudioClip::AudioClip;
    void Callback(void *userdata, Uint8 *stream, int len) override;
    
};

#endif
