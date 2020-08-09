#include "ScriptManager.h"
#include "Components.h"
#include "../Event.h"
#include "CollisionSystem.h"
#include "EntitySystem/ClassTypeId.h"
#include <algorithm>
#include "Input.h"

ScriptManager::ScriptManager()
{
}


ScriptManager::~ScriptManager()
{
}

EntitySystem::TypeId ScriptManager::registerComponent(sol::table table, std::string name)
{
	auto id = EntitySystem::ScriptComponentTypeId();
	logger.log("Registering component " + name + " with id " + std::to_string(id));
	name[0] = toupper(name[0]);
	table[name] = id;
	scriptComponentsMap[name] = id;
	return id;

}

EntitySystem::TypeId ScriptManager::registerEvent(sol::table table, std::string name)
{
	auto id = EntitySystem::ScriptEventTypeId();
	logger.log("Registering event " + name + " with id " + std::to_string(id));
	name[0] = toupper(name[0]);
	table[name] = id;
	return id;
}

void ScriptManager::subscribe(EntitySystem::TypeId eventTypeId, sol::function listener)
{
	logger.log("Subscribe to " + std::to_string(eventTypeId));
	EntitySystem::EventDispatcher::get().scriptSubscribe(eventTypeId, listener);
}


void ScriptManager::subscribe(EntitySystem::TypeId eventTypeId, sol::function listener, sol::table self)
{
	logger.log("Subscribe to " + std::to_string(eventTypeId) + " with object");
	EntitySystem::EventDispatcher::get().scriptSubscribe(eventTypeId, listener, self);
}

EntitySystem::EntitySp ScriptManager::createEntity(sol::table entityData)
{
	auto entity = EntitySystem::Entity::create();
	entityData.for_each([entity, this](sol::object key, sol::object value) {
		auto componentName = key.as<std::string>();
		if (componentName == "transform")
		{
			auto position = value.as<sol::table>();
			entity->attach<TransformComponent>(Vector2(position["x"], position["y"]));
		}
		else if (componentName == "text")
		{
			entity->attach<TextComponent>(value.as<std::string>());
		}
		else if (componentName == "render")
		{
			auto shapeTable = value.as<sol::table>()["shape"];
			if (shapeTable["type"] == Rectangle)
			{
				auto shape = std::make_shared<sf::RectangleShape>(sf::Vector2f(shapeTable["width"], shapeTable["height"]));
				shape->setFillColor(shapeTable["color"]);
				entity->attach<RenderComponent>(std::static_pointer_cast<sf::Shape>(shape));
			}
			if (shapeTable["type"] == Circle)
			{
				float radius = shapeTable["radius"];
				auto shape = std::make_shared<sf::CircleShape>(radius);
				shape->setFillColor(shapeTable["color"]);
				entity->attach<RenderComponent>(std::static_pointer_cast<sf::Shape>(shape));
			}
		}
		else if (componentName == "velocity")
		{
			auto table = value.as<sol::table>();
			entity->attach<VelocityComponent>(Vector2(table["velocity"]["x"], table["velocity"]["y"]), table.get<float>("bounciness"));
		}
		else if (componentName == "collision")
		{
			auto shapeTable = value.as<sol::table>()["shape"];
			if (shapeTable["type"] == Rectangle)
			{
				auto shape = std::make_shared<RectCollisionShape>(shapeTable["width"], shapeTable["height"]);
				entity->attach<CollisionComponent>(std::static_pointer_cast<CollisionShape>(shape));
			}
			if (shapeTable["type"] == Circle)
			{
				float radius = shapeTable["radius"];
				auto shape = std::make_shared<CircleCollisionShape>(radius);
				entity->attach<CollisionComponent>(std::static_pointer_cast<CollisionShape>(shape));
			}
		}
		else if (componentName == "physics")
		{
			auto table = value.as<sol::table>();
			entity->attach<PhysicsComponent>(table["bounciness"], table["mass"], Vector2(table["constraints"]["x"], table["constraints"]["y"]));
		}
		else
		{
			auto componentNameCase = componentName;
			componentNameCase[0] = toupper(componentNameCase[0]);
			if (scriptComponentsMap.find(componentNameCase) == scriptComponentsMap.end())
			{
				registerComponent(lua["Components"], componentNameCase);
			}
			entity->scriptAttach(scriptComponentsMap[componentNameCase], value.as<sol::object>());
		}
	});
	entity->commit();
	return entity;
}

void ScriptManager::init()
{
	lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
	lua.script("print('LUA online')");
	lua.new_usertype<Vector2>("Vector2",
		sol::constructors<Vector2(double, double)>(),
		"x", &Vector2::x,
		"y", &Vector2::y
		);

	lua.new_usertype<EntitySystem::Component>("Component");

	lua.new_usertype<TransformComponent>("TransformComponent",
		sol::constructors<TransformComponent(Vector2)>(),
		"position", &TransformComponent::position,
		sol::base_classes, sol::bases<EntitySystem::Component>()
		);

	lua.new_usertype<EntitySystem::Entity>("Entity",
                                           sol::constructors<EntitySystem::Entity()>(),
                                           "id", &EntitySystem::Entity::id,
                                           "get", &EntitySystem::Entity::scriptGet,
                                           "has", &EntitySystem::Entity::scriptHas,
                                           "attach", &EntitySystem::Entity::scriptAttach,
                                           "detach", &EntitySystem::Entity::scriptDetach
		);

	lua.new_usertype<TextComponent>("TextComponent",
		sol::constructors<TextComponent(std::string)>(),
		"text", &TextComponent::text,
		sol::base_classes, sol::bases<EntitySystem::Component>()
		);

	lua.new_usertype<Collision>("Collision",
		sol::constructors<Collision()>(),
		"occured", &Collision::occured,
		"depth", &Collision::depth,
		"normal", &Collision::normal
		);

	lua.new_usertype<CollisionEvent>("CollisionEvent",
		sol::constructors<CollisionEvent(Collision, EntitySystem::EntitySp, EntitySystem::EntitySp)>(),
		"entity1", &CollisionEvent::entity1,
		"entity2", &CollisionEvent::entity2,
		"collision", &CollisionEvent::collision
		);

	lua.new_usertype<sf::Vector2f>("Vector2f",
		sol::constructors < sf::Vector2f(float, float) >()
		);

	lua.new_usertype<sf::Shape>("Shape",
		"setFillColor", &sf::RectangleShape::setFillColor
		);

	lua.new_usertype<sf::RectangleShape>("RectangleShape",
		sol::constructors<sf::RectangleShape(sf::Vector2f)>(),
		"setFillColor", &sf::RectangleShape::setFillColor,
		sol::base_classes, sol::base_list<sf::Shape>()
		);

	lua.new_usertype<sf::CircleShape>("CircleShape",
		sol::constructors<sf::CircleShape(float)>(),
		sol::base_classes, sol::base_list<sf::Shape>()
		);

	lua.new_usertype<RenderComponent>("RenderComponent",
		sol::constructors<RenderComponent(std::shared_ptr<sf::Shape>)>(),
		sol::base_classes, sol::bases<EntitySystem::Component>()

		);

	lua.new_usertype<VelocityComponent>("VelocityComponent",
		sol::constructors<VelocityComponent(Vector2, float)>(),
		"velocity", &VelocityComponent::velocity,
		"bounciness", &VelocityComponent::bounciness,
		sol::base_classes, sol::bases<EntitySystem::Component>()
		);

	lua.new_usertype<CollisionShape>("CollisionShape");

	lua.new_usertype<RectCollisionShape>("RectCollisionShape",
		sol::constructors<RectCollisionShape(float, float)>(),
		"width", &RectCollisionShape::width,
		"height", &RectCollisionShape::height,
		sol::base_classes, sol::bases<CollisionShape>()
		);

	lua.new_usertype<CircleCollisionShape>("CircleCollisionShape",
		sol::constructors<CircleCollisionShape(float)>(),
		"center", &CircleCollisionShape::center,
		sol::base_classes, sol::bases<CollisionShape>()
		);

	lua.new_usertype<CollisionComponent>("CollisionComponent",
		sol::constructors<CollisionComponent(std::shared_ptr<CollisionShape>)>(),
		"shape", &CollisionComponent::shape,
		sol::base_classes, sol::bases<EntitySystem::Component>()
		);

	lua.new_usertype<PhysicsComponent>("PhysicsComponent",
		sol::constructors<PhysicsComponent(float, float, Vector2)>(),
		"constraints", &PhysicsComponent::constraints,
		"bounciness", &PhysicsComponent::bounciness,
		"mass", &PhysicsComponent::mass,
		"invertedMass", &PhysicsComponent::invertedMass,
		sol::base_classes, sol::bases<EntitySystem::Component>()
		);

	lua.new_usertype<Input>("Input",
        "isActionPressed", Input::isActionPressed);

	lua.new_enum("sfColor",
		"Green", sf::Color::Green,
		"Red", sf::Color::Red,
		"White", sf::Color::White
	);
	lua.new_enum("Shapes",
		"Rectangle", ShapeType::Rectangle,
		"Circle", ShapeType::Circle
	);

	lua.new_usertype<EntitySystem::TypeId>("TypeId");

	lua["Events"] = lua.create_table_with(
            "Collision", EntitySystem::EventTypeId<CollisionEvent>()
	);

	auto eventsMetatable = lua.create_table();
	eventsMetatable.set_function(sol::meta_function::index, &ScriptManager::registerEvent, this);
	lua["Events"][sol::metatable_key] = eventsMetatable;

	lua["Components"] = lua.create_table_with(
            "Transform", EntitySystem::ComponentTypeId<TransformComponent>(),
            "Text", EntitySystem::ComponentTypeId<TextComponent>(),
            "Render", EntitySystem::ComponentTypeId<RenderComponent>(),
            "Collision", EntitySystem::ComponentTypeId<CollisionComponent>(),
            "Physics", EntitySystem::ComponentTypeId<PhysicsComponent>(),
            "Velocity", EntitySystem::ComponentTypeId<VelocityComponent>()
	);

	auto metatable = lua.create_table();
	metatable.set_function(sol::meta_function::index, &ScriptManager::registerComponent, this);
	lua["Components"][sol::metatable_key] = metatable;

	lua.new_usertype<EntitySystem::Time>("Time",
                                         "asSeconds", &EntitySystem::Time::asSeconds
		);
	/*lua.new_usertype<Input>("Input",
		"isKeyPressed", &Input::isKeyPressed
	);*/
	lua.new_enum("Key",
		"Up", sf::Keyboard::Key::Up,
		"Down", sf::Keyboard::Key::Down,
		"W", sf::Keyboard::Key::W,
		"S", sf::Keyboard::Key::S);

	sol::table glmTable = lua.create_named_table("glm");
	glmTable.set_function("normalize", &ScriptManager::glmNormalize, this);

	glmTable.set_function("clamp", [] (double input, double min, double max) {
		return glm::clamp(input, min, max);
	});

	lua.set_function("createEntity", &ScriptManager::createEntity, this);
	/*lua.set_function("subscribe",
		sol::overload(
			sol::resolve<void(EntitySystem::TypeId, sol::function)>(&ScriptManager::subscribe),
			sol::resolve<void(EntitySystem::TypeId, sol::function, sol::table)>(&ScriptManager::subscribe)
		), this);
		*/
	lua.set_function("subscribe", sol::resolve<void(EntitySystem::TypeId, sol::function)>(&ScriptManager::subscribe), this);
	lua.set_function("subscribeForObject", sol::resolve<void(EntitySystem::TypeId, sol::function, sol::table)>(&ScriptManager::subscribe), this);
	lua.set_function("registerSystem", &ScriptManager::registerSystem, this);
	lua.set_function("import", &ScriptManager::importModule, this);
	lua.set_function("emit", &ScriptManager::emit, this);
	lua.set_function("clearWorld", &ScriptManager::clearWorld, this);
	lua.new_usertype<EntitySystem::ScriptSystem>("System",
                                                 sol::constructors<EntitySystem::ScriptSystem(sol::table)>()
	);

	lua.new_usertype<StartedEvent>("StartedEvent");
}

void ScriptManager::run(std::string name)
{
	lua.script_file(name);
}

Vector2 ScriptManager::glmNormalize(Vector2 vec)
{
	return glm::normalize(vec);
}

sol::table ScriptManager::registerSystem(sol::table script)
{
	auto system = std::make_shared<EntitySystem::ScriptSystem>(script);
	systems.push_back(system);
	return script;
}

void ScriptManager::process(EntitySystem::Time deltaTime)
{
	for (auto system : systems)
	{
		system->Process(deltaTime);
	}
}

sol::object ScriptManager::importModule(std::string modulePath)
{
	return lua.require_file(modulePath, "scripts/" + modulePath + ".lua", false);
}

void ScriptManager::clearWorld()
{
	EntitySystem::EventDispatcher::get().scriptClear();
	EntitySystem::Entity::clear();
	systems.clear();
}

void ScriptManager::emit(EntitySystem::TypeId type, sol::object data)
{
	EntitySystem::EventDispatcher::get().scriptEmit(type, data);
}

void ScriptManager::close()
{
//	lua.release();
}