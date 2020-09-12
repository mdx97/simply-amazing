#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "SDL.h"

namespace Engine {
    extern SDL_Window *window;
    void Start(const std::string &title, int width, int height);
    void Run();
    void End();
};

#endif
