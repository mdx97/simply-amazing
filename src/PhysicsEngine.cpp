#include <iostream>
#include "CollisionComponent.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "PhysicsEngine.h"
#include "SceneSystem.h"
#include "Utility.h"

void Flip(PhysicsComponent *phys)
{
    phys->direction -= 180;
    if (phys->direction < 0)
        phys->direction += 360;
}

void PhysicsEngine::Tick()
{
    auto entities = SceneSystem::GetAllEntities();

    for (int i = 0; i < entities.size(); i++) {
        auto *collider = entities[i]->GetComponent<CollisionComponent>();
        
        if (collider != nullptr) {
            for (int j = i + 1; j < entities.size(); j++) {
                auto *other = entities[j]->GetComponent<CollisionComponent>();
                
                if (other != nullptr) {
                    if (Utility::Collides(entities[i], collider, entities[j], other)) {
                        std::cout << "Collision detected!" << std::endl;
                        auto *iPhys = entities[i]->GetComponent<PhysicsComponent>();
                        auto *jPhys = entities[j]->GetComponent<PhysicsComponent>();

                        if (iPhys != nullptr)
                            Flip(iPhys);

                        if (jPhys != nullptr)
                            Flip(jPhys);
                    }
                }
            }
        }
    }
}
