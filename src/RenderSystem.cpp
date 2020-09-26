#include "Engine.h"
#include "RenderSystem.h"
#include "SceneSystem.h"
#include "SpriteComponent.h"

SDL_Surface *RenderSystem::background = nullptr;

void DrawEntities(const std::vector<Entity *> &entities)
{
    for (auto *entity : entities) {
        SpriteComponent *sprite = entity->GetComponent<SpriteComponent>();

        if (sprite != nullptr) {
            SDL_Rect rect = { 
                static_cast<int>(entity->x) + sprite->x,
                static_cast<int>(entity->y) + sprite->y,
                static_cast<int>(sprite->surface->w * sprite->w),
                static_cast<int>(sprite->surface->h * sprite->h)
            };
            SDL_BlitScaled(sprite->surface, nullptr, RenderSystem::background, &rect);
        }
    }
}

void RenderSystem::Draw()
{
    SDL_FillRect(background, nullptr, SDL_MapRGB(background->format, 0, 0, 0));
    
    DrawEntities(SceneSystem::persistent_entities);
    
    if (SceneSystem::current != nullptr) {
        DrawEntities(SceneSystem::current->entities);
    }
    
    SDL_UpdateWindowSurface(Engine::window);
}
