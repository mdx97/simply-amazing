#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include "SDL.h"

namespace EventSystem {
    extern bool exit;
    void Process();
    bool IsKeyDown(SDL_Scancode scancode);
};

#endif
