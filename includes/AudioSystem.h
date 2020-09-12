#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include "AudioClip.h"

namespace AudioSystem {
    void PlayClip(AudioClip *clip);
    void FreeClip(AudioClip *clip);
    void ToggleSound(bool on);
};

#endif
