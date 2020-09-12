#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    virtual void Update(float elapsed) = 0;
    Entity *entity = nullptr;

    // @TODO: Destructor should remove itself from the entity's component list?
};

#include "Entity.h"

#endif
