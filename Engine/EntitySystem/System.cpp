#include "System.h"

namespace EntitySystem {
	void BaseSystem::ProcessEntity(EntitySp entity, Time deltaTime)
	{

	}

	void BaseSystem::OnEntityAdded(EventSp event)
	{
		auto entityCreatedEvent = std::dynamic_pointer_cast<EntityCreatedEvent>(event);

		auto entity = entityCreatedEvent->entity;
		if (entity->hasComponents(components)) {
			logger.log(getName() + ": entity added");
			entities[entity->id] = entity;
		}
	}

	void BaseSystem::OnComponentAttached(EventSp event) {
		auto entityCreatedEvent = std::dynamic_pointer_cast<ComponentAttachedEvent>(event);
		auto entity = entityCreatedEvent->entity;

		if (entity->hasComponents(components)) {
			logger.log(getName() + ": entity added");
			entities[entity->id] = entity;
		}

	}

	void BaseSystem::OnEntityRemoved(EventSp event) {
		auto entityRemovedEvent = std::dynamic_pointer_cast<EntityRemovedEvent>(event);
		auto entity = entityRemovedEvent->entity;
		//if (entities.)
		logger.log(getName() + ": entity removed " + std::to_string(entity->id));
		if (entities.find(entity->id) != entities.end())
		{
			entities.erase(entity->id);
		}

	}
	void BaseSystem::Process(Time deltaTime)
	{
		for (auto entity : entities)
		{
			ProcessEntity(entity.second, deltaTime);
		}
	}

	void ScriptSystem::Process(EntitySystem::Time deltaTime)
	{
		if (script["process"].valid())
		{
			script["process"](deltaTime);
		}
		else if (script["processEntity"].valid())
		{
			for (auto entity : entities)
			{
				script["processEntity"](script, entity.second, deltaTime);
			}
		}
	}

	void ScriptSystem::OnScriptComponentAttached(EventSp event)
	{
		auto componentAttachedEvent = std::dynamic_pointer_cast<ScriptComponentAttachedEvent>(event);
		auto entity = componentAttachedEvent->entity;

		if (entity->hasComponents(components)) {
			logger.log(getName() + ": entity added");
			entities[entity->id] = entity;
		}
	}

	void ScriptSystem::OnScriptComponentDetached(EventSp event)
	{
		auto componentDetachedEvent = std::dynamic_pointer_cast<ScriptComponentDetachedEvent>(event);
		auto entity = componentDetachedEvent->entity;

		if (!entity->hasComponents(components)) {
			logger.log(getName() + ": entity removed");
			entities[entity->id] = entity;
			entities.erase(entity->id);
		}
	}
}
