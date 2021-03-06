#include <iostream>
#include "CollisionComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "PhysicsEngine.h"
#include "SceneSystem.h"

struct Rectangle {
    float x, y, w, h;
};

Rectangle EntityToWorldSpace(const CollisionComponent *collider)
{
    Rectangle rect;
    rect.x = collider->entity->x + collider->x;
    rect.y = collider->entity->y + collider->y;
    rect.w = collider->w;
    rect.h = collider->h;
    return rect;
}

bool Collides(const CollisionComponent *collider1, const CollisionComponent *collider2)
{
    // @PERFORMANCE: Maybe find a way to precompute these?
    // I mean it is a pretty simple computation, but with lots of elements it could be costly.
    Rectangle rect1 = EntityToWorldSpace(collider1);
    Rectangle rect2 = EntityToWorldSpace(collider2);

    return (rect1.x <= rect2.x + rect2.w) && 
           (rect1.x + rect1.w >= rect2.x) && 
           (rect1.y <= rect2.y + rect2.h) && 
           (rect1.y + rect1.h >= rect2.y);
}

// @TEMP: This entire function should be swapped out for angle of incidence calculation.
void Bounce(PhysicsComponent *phys)
{
    phys->direction = 180 - phys->direction;
    if (phys->direction < 0)
        phys->direction += 360;
}

void PhysicsEngine::Tick()
{
    auto entities = SceneSystem::GetAllEntities();

    for (int i = 0; i < entities.size(); i++) {
        if (auto *collider = entities[i]->GetComponent<CollisionComponent>(); collider != nullptr) {
            for (int j = i + 1; j < entities.size(); j++) {
                if (auto *other = entities[j]->GetComponent<CollisionComponent>(); other != nullptr) {
                    if (Collides(collider, other)) {
                        auto *iPhys = entities[i]->GetComponent<PhysicsComponent>();
                        auto *jPhys = entities[j]->GetComponent<PhysicsComponent>();

                        if (iPhys != nullptr)
                            Bounce(iPhys);

                        if (jPhys != nullptr)
                            Bounce(jPhys);
                    }
                }
            }
        }
    }
}
