#pragma once
#include "EntitySystem/Component.h"
#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include <glm/glm.hpp>
#include "EntitySystem/Entity.h"
#include "Collider.h"

enum ShapeType {
	Rectangle, Circle
};

class TransformComponent : public EntitySystem::Component {
public:
	Vector2 position;
	explicit TransformComponent(Vector2 position) : position(position) {}
};

typedef std::shared_ptr<TransformComponent> TransformComponentSp;

class VelocityComponent : public EntitySystem::Component {
public:
	Vector2 velocity;
	float bounciness;
	VelocityComponent(Vector2 velocity, float bounciness) : velocity(velocity), bounciness(bounciness) {}
};

class RenderComponent : public EntitySystem::Component {
public:
	std::shared_ptr<sf::Shape> shape;
	RenderComponent(std::shared_ptr<sf::Shape> shape) : shape(shape) {};
};

class TextComponent : public EntitySystem::Component {
public:
	std::string text;
	TextComponent(std::string text) : text(text) {};
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

class PhysicsComponent : public EntitySystem::Component {
public:
	Vector2 constraints;
	float bounciness;
	float mass;
	float invertedMass;
	PhysicsComponent(float bounciness, float mass, Vector2 constraints) : bounciness(bounciness), mass(mass), constraints(constraints)
	{
		if (mass != 0) {
			invertedMass = 1 / mass;
		}
		else
		{
			invertedMass = 0;
		}
	}
};
