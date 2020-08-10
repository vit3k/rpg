#pragma once
#include "Components.h"
#include "EntitySystem/System.h"
#include "Components/SpriteComponent.h"

class RenderSystem : public EntitySystem::System<SpriteComponent, TransformComponent> {
	sf::RenderWindow* renderWindow;
protected:
	virtual std::string getName() { return "RenderSystem"; }
public:
	void virtual Process(EntitySystem::Time deltaTime);
	RenderSystem(sf::RenderWindow* renderWindow) : renderWindow(renderWindow) {};
};