#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include "EntitySystem/System.h"
#include "Components/TransformComponent.h"
#include "Components/TextComponent.h"

class TextRenderingSystem : public EntitySystem::System<TransformComponent, TextComponent>
{
	sf::RenderTarget* renderTarget;
	sf::Font font;
protected:
	virtual std::string getName() { return "TextRenderingSystem"; }
public:
	TextRenderingSystem(sf::RenderTarget* renderTarget) : renderTarget(renderTarget) {
		font.loadFromFile("Resources/cour.ttf");

	};
	virtual void ProcessEntity(EntitySystem::EntitySp entity, EntitySystem::Time deltaTime);
};

