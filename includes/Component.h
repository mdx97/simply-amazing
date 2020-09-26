#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:
    // @TODO: Destructor should remove itself from the entity's component list?
    virtual void Update(float elapsed) = 0;
    Entity *entity = nullptr;
};

#include "Entity.h"

#endif
