#include "CollisionSystem.h"
#include "Collider.h"
#include "EntitySystem/EventDispatcher.h"

CollisionSystem::CollisionSystem() {
	colliders[ColliderType(Rectangle, Rectangle)] = std::make_shared<BoxBoxCollider>();
	colliders[ColliderType(Rectangle, Circle)] = std::make_shared<BoxCircleCollider>();
}

CollisionSystem::~CollisionSystem() {
	/*for (auto elem : colliders)
	{
		delete elem.second;
	}*/
	colliders.clear();
}

void CollisionSystem::Process(EntitySystem::Time delta)
{
	for (auto entity1i = entities.begin(); entity1i != entities.end(); entity1i++)
	{
		auto entity1 = entity1i->second;
		auto collisionComponent1 = entity1->get<CollisionComponent>();
		for (auto entity2i = entity1i; entity2i != entities.end(); entity2i++)
		{
			auto entity2 = entity2i->second;
			if (entity1 == entity2)
			{
				continue;
			}
			auto collisionComponent2 = entity2->get<CollisionComponent>();

			auto type1 = collisionComponent1->shape->getType();
			auto type2 = collisionComponent2->shape->getType();
			auto collider = colliders[ColliderType(type1, type2)];

			Collision collision;

			if (collider != NULL)
			{
				collision = collider->collide(entity1, entity2);
				if (collision.occured)
				{
					logger.log("COLLISION");
					EntitySystem::EventDispatcher::get().emitNow<CollisionEvent>(collision, entity1, entity2);
				}
			}
			else
			{
				collider = colliders[std::pair<ShapeType, ShapeType>(collisionComponent2->shape->getType(), collisionComponent1->shape->getType())];

				if (collider != NULL) {
					collision = collider->collide(entity2, entity1);
					if (collision.occured)
					{
						logger.log("COLLISION");
						EntitySystem::EventDispatcher::get().emitNow<CollisionEvent>(collision, entity2, entity1);
					}
				}
				else {
					logger.log("No matching collider");
				}
			}


		}
	}
}
