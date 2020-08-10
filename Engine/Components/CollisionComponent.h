//
// Created by Pawel Witkowski on 10/08/2020.
//

#ifndef RPG_COLLISIONCOMPONENT_H
#define RPG_COLLISIONCOMPONENT_H

#include <cmath>
#include <iostream>
#include "../Vector2.h"
#include "TransformComponent.h"
#include "../Collider.h"

enum ShapeType {
    Rectangle, Circle
};

struct Projection {
    float min, max;
    Projection(float min, float max) : min(min), max(max) {}
    float overlaps(Projection& other) {
        return fmax(0, fmin(max, other.max) - fmax(min, other.min));
    }
};

class CollisionShape
{
public:
    virtual ShapeType getType() = 0;
    virtual Vector2 center() = 0;
    virtual Projection project(TransformComponentSp transform, Vector2 axis) = 0;
};

class RectCollisionShape : public CollisionShape
{
public:
    float width, height;
    virtual ShapeType getType() { return Rectangle; }
    RectCollisionShape(float width, float height) : width(width), height(height) {}
    std::vector<Vector2> calculateVertices(TransformComponentSp transform) {
        std::vector<Vector2> vertices = { Vector2(transform->position.x, transform->position.y),
                                          Vector2(transform->position.x + width, transform->position.y),
                                          Vector2(transform->position.x + width, transform->position.y + height),
                                          Vector2(transform->position.x, transform->position.y + height) };

        return vertices;
    }
    virtual Vector2 center() {
        return Vector2(width / 2, height / 2);
    }
    virtual Projection project(TransformComponentSp transform, Vector2 axis) {

        auto vertices = calculateVertices(transform);

        float max = glm::dot(axis, vertices[0]);

        float min = max;

        for (int i = 1; i < 4; i++)
        {
            float p = glm::dot(axis, vertices[i]);
            if (p < min)
            {
                min = p;
            }
            else if (p > max)
            {
                max = p;
            }
        }
        return Projection(min, max);
    }

    ~RectCollisionShape()
    {
        std::cout << "RectCollisionShape destroyed" << std::endl;
    }
};

class CircleCollisionShape : public CollisionShape
{
public:
    float radius;
    virtual ShapeType getType() { return Circle; }
    CircleCollisionShape(float radius) : radius(radius) {}
    virtual Vector2 center() {
        return Vector2(radius, radius);
    }
    virtual Projection project(TransformComponentSp transform, Vector2 axis) {
        auto projected = glm::dot(axis, transform->position + center());
        return Projection(projected - radius, projected + radius);
    }
};

class CollisionComponent : public EntitySystem::Component {
public:
    Collision collision;
    std::shared_ptr<CollisionShape> shape;
    CollisionComponent(std::shared_ptr<CollisionShape> shape) : shape(shape) {}

};
#endif //RPG_COLLISIONCOMPONENT_H
