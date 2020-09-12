#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Entity.h"

class Scene {
public:
    virtual void OnLoad() = 0;
    virtual void OnUnload() = 0;
    virtual void Update(float elapsed) = 0;
    std::vector<Entity *> entities;
    void AddEntity(Entity *entity);
    void RemoveEntity(Entity *entity);
};

#endif
