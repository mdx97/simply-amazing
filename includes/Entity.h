#ifndef ENTITY_H
#define ENTITY_H

#include <algorithm>
#include <string>
#include <vector>
#include "Component.h"
#include "SDL.h"

class Entity;

class Composite
{
public:
    std::vector<Entity *> entities;
    const char *type;

    Composite();
    void AddEntity(Entity *entity);
    void RemoveEntity(Entity *entity);
};

class Entity
{
public:
    int x, y;
    const char *type;
    Composite *composite;
    std::vector<Component *> components;
    
    Entity();
    ~Entity();
    void AddComponent(Component *component);

    template <typename T>T* GetComponent()
    {
        T *casted = nullptr;

        for (auto *component : components) {
            if (component != nullptr) {
                casted = dynamic_cast<T *>(component);
                if (casted != nullptr) {
                    break;
                }
            }
        }

        return casted;
    }
};

#endif
