#include "RenderSystem.h"

void RenderSystem::Process(EntitySystem::Time deltaTime)
{
	for (auto pair : entities) {
		auto entity = pair.second;
		//auto render = entity->get<RenderComponent>();
		auto sprite = entity->get<SpriteComponent>();
		auto transform = entity->get<TransformComponent>();
		/*auto shape = render->shape;

		auto projectedPosition = Vector2((transform->position.x + 10) * 80, (transform->position.y + 7.5) * 80);
		shape->setPosition(projectedPosition.x, projectedPosition.y);
		shape->setScale(80, 80);
		renderWindow->draw(*shape);*/
		sprite->sprite.setPosition(transform->position.x, transform->position.y);
		sprite->sprite.setScale(10, 10);
		renderWindow->draw(sprite->sprite);
	}
}