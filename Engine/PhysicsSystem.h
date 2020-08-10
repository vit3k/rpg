#pragma once
#include "EntitySystem/System.h"
#include "EntitySystem/Time.h"
#include "CollisionSystem.h"
#include "Components/PhysicsComponent.h"

class PhysicsSystem : public EntitySystem::System<TransformComponent, PhysicsComponent, CollisionComponent>
{
	std::vector<CollisionEventSp> collisions;
	void correctEntity(EntitySystem::EntitySp entity, Collision& collision, Vector2 prop, float multiplier);
	void bounceEntity(EntitySystem::EntitySp entity, Collision& collision, Vector2 prop, Vector2 otherVelocity);
	float getMass(EntitySystem::EntitySp entity);
	Vector2 getVelocity(EntitySystem::EntitySp entity);
	Vector2 calculatePropVector(EntitySystem::EntitySp entity, EntitySystem::EntitySp otherEntity, float massProp);
	Vector2 getConstraints(EntitySystem::EntitySp entity);
protected:
	virtual std::string getName() { return "PhysicsSystem"; }
public:
	virtual void Process(EntitySystem::Time deltaTime);
	void OnCollision(EntitySystem::EventSp e);
	PhysicsSystem();
};