#ifndef ENGINE_H
#define ENGINE_H

#include <string>
#include "SDL.h"

struct EngineConfig {
    std::string title;
    int window_width;
    int window_height;
    std::string icon_path;
};

namespace Engine {
    extern SDL_Window *window;
    void Init(const EngineConfig &config);
    void Start();
    void End();
};

#endif
