#include <cmath>
#include <iostream>
#include "CollisionComponent.h"
#include "Entity.h"
#include "Utility.h"

struct Point {
    float x, y;
};

struct Rectangle {
    Point a, b, c, d;
    float w, h;
};

const float PI = 3.14159265358979323846;

// Sets the given rect to be centered in the middle of the destination surface.
void Utility::CenterEntity(Entity *entity, SDL_Surface *container, int width, int height)
{
    entity->x = (container->w - width) / 2;
    entity->y = (container->h - height) / 2;
}

float Utility::DegreesToRadians(float degrees)
{
    return degrees * PI / 180.0;
}

Rectangle ColliderToRectangle(const Entity *entity, const CollisionComponent *collider)
{
    Rectangle rect;
    rect.a = { entity->x + collider->x, entity->y + collider->y };
    rect.b = { rect.a.x + collider->w, rect.a.y };
    rect.c = { rect.b.x, rect.a.y + collider->h };
    rect.d = { rect.a.x, rect.c.y };
    rect.w = collider->w;
    rect.h = collider->h;
    return rect;
}

bool FloatsEqual(float float1, float float2)
{
    std::cout << float1 << " " << float2 << std::endl;
    return std::fabs(float1 - float2) < 0.001;
}

int TriangleArea(const Point a, const Point b, const Point c)
{
    return std::fabs(((a.x * (b.y - c.y)) + (b.x * (c.y - a.y)) + (c.x * (a.y - b.y))) / 2);
}

bool PointInsideRectangle(const Point point, const Rectangle rect)
{
    int total_area = TriangleArea(point, rect.a, rect.b) + TriangleArea(point, rect.b, rect.c) + TriangleArea(point, rect.c, rect.d) + TriangleArea(point, rect.d, rect.a);
    return FloatsEqual(total_area, rect.w * rect.h);
}

bool Utility::Collides(const Entity *entity1, const CollisionComponent *collider1, const Entity *entity2, const CollisionComponent *collider2)
{
    Rectangle rect1 = ColliderToRectangle(entity1, collider1);
    Rectangle rect2 = ColliderToRectangle(entity2, collider2);

    Point points[4] = { rect1.a, rect1.b, rect1.c, rect1.d };

    for (auto point : points) {
        if (PointInsideRectangle(point, rect2)) {
            return true;
        }
    }

    return false;
}
