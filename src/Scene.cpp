#include <algorithm>
#include "Scene.h"

// Adds a new entity to the scene.
void Scene::AddEntity(Entity *entity)
{
    entities.push_back(entity);
}

// Deletes and removes an entity from the scene.
void Scene::RemoveEntity(Entity *entity)
{
    auto iter = std::find(entities.begin(), entities.end(), entity);
    
    if (iter != entities.end()) {
        delete *iter;
        entities.erase(iter);
    }
}
