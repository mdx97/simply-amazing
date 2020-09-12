#ifndef COLLISIONCOMPONENT_H
#define COLLISIONCOMPONENT_H

#include "Component.h"

class CollisionComponent : public Component
{
public:
    int x, y, w, h;

    CollisionComponent(int w, int h)
    {
        x = 0;
        y = 0;
        this->w = w;
        this->h = h;
    }

    void Update(float elapsed) { }
};

#endif
