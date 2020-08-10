#include "RenderSystem.h"

void RenderSystem::Process(EntitySystem::Time deltaTime)
{
	for (auto pair : entities) {
		auto entity = pair.second;
		//auto render = entity->get<RenderComponent>();
		auto sprite = entity->get<SpriteComponent>();
		auto transform = entity->get<TransformComponent>();
		sprite->sprite.setPosition(transform->position.x, transform->position.y);
		sprite->sprite.setScale(5, 5);

        auto spritesheet = sprite->spriteSheets[sprite->currentSpriteSheet];
        sprite->sprite.setTexture(spritesheet->texture);
        sprite->sprite.setTextureRect(spritesheet->getRectForSprite(sprite->currentSprite, sprite->flipY));

		auto rect = sprite->sprite.getTextureRect();

		sprite->sprite.setTextureRect(rect);
		renderWindow->draw(sprite->sprite);
	}
}