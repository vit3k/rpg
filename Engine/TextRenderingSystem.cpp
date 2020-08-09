#include "TextRenderingSystem.h"

void TextRenderingSystem::ProcessEntity(EntitySystem::EntitySp entity, EntitySystem::Time deltaTime)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setString(entity->get<TextComponent>()->text);
	text.setFillColor(sf::Color::White);
	auto transform = entity->get<TransformComponent>();
	auto projectedPosition = Vector2((transform->position.x + 10) * 80, (transform->position.y + 7.5) * 80);
	text.setPosition(projectedPosition.x, projectedPosition.y);

	text.setPosition(projectedPosition.x, projectedPosition.y);
	renderTarget->draw(text);
}
