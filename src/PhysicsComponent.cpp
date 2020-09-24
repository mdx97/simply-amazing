#include <cmath>
#include <iostream>
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "SceneSystem.h"
#include "Utility.h"

void PhysicsComponent::Update(float elapsed)
{
    float distance = velocity * elapsed;
    float rad = Utility::DegreesToRadians(direction);
    this->entity->x += std::sin(rad) * distance;
    this->entity->y -= std::cos(rad) * distance;

    CollisionComponent *collider, *collides_with;
    collider = this->entity->GetComponent<CollisionComponent>();
    collides_with = nullptr;

    if (collider != nullptr) {
        for (auto *entity_ : SceneSystem::GetAllEntities()) {
            if (entity_ != this->entity) {
                auto *other = entity_->GetComponent<CollisionComponent>();
                
                if (other != nullptr) {
                    if (Utility::Collides(this->entity, collider, entity_, other)) {
                        collides_with = other;
                        break;
                    }
                }
            }
        }
    }

    // @TODO: May need to support multiple collisions at once?
    if (collides_with != nullptr) {
        // @TEMP: This needs to calculate angle of incidence with the other collider.
        direction -= 180;
        if (direction < 0) {
            direction += 360;
        }
    }
}
