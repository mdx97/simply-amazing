#include "Engine.h"
#include "RenderSystem.h"
#include "SceneSystem.h"
#include "SpriteComponent.h"

SDL_Surface *RenderSystem::background = nullptr;

// Renders the sprites (if they exist) of the given list of entities.
void DrawEntities(const std::vector<Entity *> &entities)
{
    for (auto *entity : entities) {
        SpriteComponent *sprite = entity->GetComponent<SpriteComponent>();

        if (sprite != nullptr) {
            SDL_Rect rect = { 
                entity->x + sprite->x,
                entity->y + sprite->y,
                static_cast<int>(sprite->surface->w * sprite->w),
                static_cast<int>(sprite->surface->h * sprite->h)
            };
            SDL_BlitScaled(sprite->surface, nullptr, RenderSystem::background, &rect);
        }
    }
}

// Renders every entity onto the background surface.
void RenderSystem::Draw()
{
    SDL_FillRect(background, nullptr, SDL_MapRGB(background->format, 0, 0, 0));
    
    DrawEntities(SceneSystem::persistent_entities);
    
    if (SceneSystem::current != nullptr) {
        DrawEntities(SceneSystem::current->entities);
    }
    
    SDL_UpdateWindowSurface(Engine::window);
}
