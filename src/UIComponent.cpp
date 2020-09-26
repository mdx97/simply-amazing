#include "Mouse.h"
#include "SpriteComponent.h"
#include "UIComponent.h"

void UIComponent::Update(float elapsed)
{
    auto *sprite = entity->GetComponent<SpriteComponent>();
    
    if (sprite != nullptr) {
        SDL_Rect rect = { 
            static_cast<int>(entity->x) + sprite->x,
            static_cast<int>(entity->y) + sprite->y,
            sprite->surface->w, 
            sprite->surface->h 
        };

        if (SDL_PointInRect(&Mouse::position, &rect)) {
            Hover(sprite);
            HandleClick();
        } else {
            Unhover(sprite);
        }
    }
}

void UIComponent::HandleClick()
{
    if (Mouse::left_click && click != nullptr) {
        click(entity);
    }
}

void UIComponent::Hover(SpriteComponent *sprite)
{
    if (hover_surface != nullptr && sprite->surface != hover_surface) {
        if (original_surface == nullptr) {
            original_surface = sprite->surface;
        }
        sprite->surface = hover_surface;
    }
}

void UIComponent::Unhover(SpriteComponent *sprite)
{
    if (original_surface != nullptr && sprite->surface != original_surface) {
        sprite->surface = original_surface;
    }
}
