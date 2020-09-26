#include <chrono>
#include <iostream>
#include <vector>
#include "Entity.h"
#include "SceneSystem.h"

// This vector stores entities that exist regardless of scene changes.
std::vector<Entity *> SceneSystem::persistent_entities;

Scene *SceneSystem::current = nullptr;
Scene *next = nullptr;

std::chrono::system_clock::time_point last_clock = std::chrono::system_clock::now();

void SceneSystem::Load(Scene *scene)
{
    // Note: mid-frame scene changes won't take effect until the next frame.
    next = scene;
}

void SceneSystem::Tick()
{
    if (next != nullptr) {
        if (current != nullptr) {
            current->OnUnload();
            delete current;
        }
        current = next;
        current->OnLoad();
        next = nullptr;
    }

    if (current == nullptr) return;

    auto clock = std::chrono::system_clock::now();
    std::chrono::duration<float> diff = clock - last_clock;
    last_clock = clock;

    float elapsed = diff.count();

    current->Update(elapsed);

    for (auto *entity : GetAllEntities()) {
        for (auto *component : entity->components) {
            component->Update(elapsed);
        }
    }
}

void SceneSystem::AddPersistentEntity(Entity *entity)
{
    persistent_entities.push_back(entity);
}

std::vector<Entity *> SceneSystem::GetAllEntities()
{
    std::vector<Entity *> entities;
    entities.insert(entities.end(), persistent_entities.begin(), persistent_entities.end());

    if (current != nullptr)
        entities.insert(entities.end(), current->entities.begin(), current->entities.end());
        
    return entities;
}
