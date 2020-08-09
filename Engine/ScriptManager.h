#pragma once
#include "EntitySystem/Entity.h"
#include <sol/sol.hpp>
#include "Vector2.h"
#include <memory>
#include "EntitySystem/System.h"
#include "EntitySystem/ClassTypeId.h"

class ScriptManager
{
private:
	std::map<std::string, EntitySystem::TypeId> scriptComponentsMap;
	sol::state lua;
	std::vector<std::shared_ptr<EntitySystem::ScriptSystem>> systems;
	Logger logger = Logger::get("ScriptManager");
public:
	ScriptManager();
	~ScriptManager();
	EntitySystem::TypeId registerComponent(sol::table table, std::string name);
	void subscribe(EntitySystem::TypeId eventTypeId, sol::function listener);
	void subscribe(EntitySystem::TypeId eventTypeId, sol::function listener, sol::table self);
	EntitySystem::EntitySp createEntity(sol::table entityData);
	void init();
	Vector2 glmNormalize(Vector2 vec);
	void run(std::string name);
	sol::table registerSystem(sol::table script);
	void process(EntitySystem::Time deltaTime);
	sol::object importModule(std::string modulePath);
	void clearWorld();
	EntitySystem::TypeId registerEvent(sol::table table, std::string name);
	void emit(EntitySystem::TypeId type, sol::object data);
	void close();
};
