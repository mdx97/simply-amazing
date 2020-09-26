#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
    SDL_Surface *surface = nullptr;
    int x, y;
    float w, h;
    
    SpriteComponent(const std::string &image_path);
    SpriteComponent(const std::string &image_path, int x, int y, float w, float h);
    ~SpriteComponent();

    void Update(float elapsed) { }
    float PixelHeight();
    float PixelWidth();
};

#endif
