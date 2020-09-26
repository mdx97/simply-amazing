#include <algorithm>
#include "Scene.h"

void Scene::AddEntity(Entity *entity)
{
    entities.push_back(entity);
}

void Scene::RemoveEntity(Entity *entity)
{
    auto iter = std::find(entities.begin(), entities.end(), entity);
    
    if (iter != entities.end()) {
        delete *iter;
        entities.erase(iter);
    }
}
