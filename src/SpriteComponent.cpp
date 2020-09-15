#include "SpriteComponent.h"
#include "SDL.h"

SpriteComponent::SpriteComponent(const std::string &image_path)
{
    surface = SDL_LoadBMP(image_path.c_str());
    x = 0;
    y = 0;
    w = 1.0f;
    h = 1.0f;
}

SpriteComponent::SpriteComponent(const std::string &image_path, int x, int y, float w, float h)
{
    surface = SDL_LoadBMP(image_path.c_str());
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

SpriteComponent::~SpriteComponent()
{
    SDL_FreeSurface(surface);
}
