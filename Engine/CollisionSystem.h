#pragma once
#include "EntitySystem/System.h"
#include "Collider.h"
#include "../Event.h"
#include "Logger.h"
#include "EntitySystem/Entity.h"
#include "Components/TransformComponent.h"
#include "Components/CollisionComponent.h"
#include <memory>

typedef std::pair<ShapeType, ShapeType> ColliderType;

class CollisionSystem : public EntitySystem::System<TransformComponent, CollisionComponent>
{
	std::map<ColliderType, std::shared_ptr<Collider>> colliders;
protected:
	virtual std::string getName() { return "CollisionSystem"; }
public:
	virtual void Process(EntitySystem::Time delta);
	CollisionSystem();
	~CollisionSystem();
};

class CollisionEvent : public EntitySystem::Event<CollisionEvent>
{
public:
	Collision collision;
	EntitySystem::EntitySp entity1;
	EntitySystem::EntitySp entity2;
	CollisionEvent(Collision collision, EntitySystem::EntitySp entity1, EntitySystem::EntitySp entity2) : collision(collision), entity1(entity1), entity2(entity2) {

	}
};

typedef std::shared_ptr<CollisionEvent> CollisionEventSp;