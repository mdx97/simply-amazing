#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Entity.h"

class Scene {
public:
    std::vector<Entity *> entities;

    ~Scene();
    
    virtual void OnLoad() = 0;
    virtual void OnUnload() = 0;
    virtual void Update(float elapsed) = 0;

    void AddEntity(Entity *entity);
    void RemoveEntity(Entity *entity);
};

#endif
