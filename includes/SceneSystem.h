#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include <vector>
#include "Scene.h"

namespace SceneSystem {
    extern Scene *current;
    extern std::vector<Entity *> persistent_entities;
    
    void Load(Scene *scene);
    void Tick();
    void AddPersistentEntity(Entity *entity);
    std::vector<Entity *> GetAllEntities();
};

#endif
