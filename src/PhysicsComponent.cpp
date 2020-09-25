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
}
