#include "Entity.h"
#include "Utility.h"

// Sets the given rect to be centered in the middle of the destination surface.
void Utility::CenterEntity(Entity *entity, SDL_Surface *container, int width, int height)
{
    entity->x = (container->w - width) / 2;
    entity->y = (container->h - height) / 2;
}
