#ifndef UTILITY_H
#define UTILITY_H

#include "SDL.h"
#include "CollisionComponent.h"

namespace Utility {
    void CenterEntity(Entity *entity, SDL_Surface *container, int width, int height);
    float DegreesToRadians(float degrees);
    bool Collides(const Entity *entity1, const CollisionComponent *collider1, const Entity *entity2, const CollisionComponent *collider2);
};

#endif
