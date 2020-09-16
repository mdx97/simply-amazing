#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "Component.h"

class PhysicsComponent : public Component {
public:
    float velocity;
    float direction;

    PhysicsComponent()
    {
        velocity = 0.0;
        direction = 0.0;
    }

    void Update(float elapsed);
};

#endif
