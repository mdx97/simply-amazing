#include "Entity.h"
#include "Utility.h"

const float PI = 3.14159265358979323846;

// Sets the given rect to be centered in the middle of the destination surface.
void Utility::CenterEntity(Entity *entity, SDL_Surface *container, int width, int height)
{
    entity->x = (container->w - width) / 2;
    entity->y = (container->h - height) / 2;
}

float Utility::DegreesToRadians(float degrees)
{
    return degrees * PI / 180.0;
}
