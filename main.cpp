#include <iostream>
#include <bitset>

#include "Engine/EntitySystem/Entity.h"
#include "Engine/RenderSystem.h"
#include "Engine/TextRenderingSystem.h"
#include "Engine/EntitySystem/EventDispatcher.h"
#include "Engine/CollisionSystem.h"
#include "Engine/PhysicsSystem.h"
#include <algorithm>
#include "Engine/ScriptManager.h"
#include "Engine/Input.h"
#include "Engine/AnimationSystem.h"
#include "Engine/Components/TextComponent.h"

int main()
{
    sf::Texture skeletonTexture;
    skeletonTexture.loadFromFile("Resources/Skeleton Idle.png");

	sf::RenderWindow window(sf::VideoMode(1600, 1200), "Pong");
	window.setFramerateLimit(60);

	std::shared_ptr<RenderSystem> renderSystem(new RenderSystem(&window));
	std::shared_ptr<TextRenderingSystem> textRenderingSystem(new TextRenderingSystem(&window));
	std::shared_ptr<AnimationSystem> animationSystem(new AnimationSystem());

	auto collisionSystem = std::make_shared<CollisionSystem>();
	auto physicsSystem = std::make_shared<PhysicsSystem>();

	ScriptManager scriptManager;
	scriptManager.init();
	scriptManager.run("scripts/rpg.lua");

	auto fpsText = EntitySystem::Entity::create();
	fpsText->attach<TransformComponent>(Vector2(-9.5, -7));
	fpsText->attach<TextComponent>("0");
	fpsText->commit();

	Input::init();
	EntitySystem::EventDispatcher::get().emitNow<StartedEvent>();

	sf::Clock timer;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		EntitySystem::Time delta(timer.restart().asMicroseconds());
		EntitySystem::Time::Elapsed += delta;
		auto fps = 1. / delta.asSeconds();
		fpsText->get<TextComponent>()->text = std::to_string(EntitySystem::Time::Elapsed.asSeconds());

		//event bus before scripts
		EntitySystem::EventDispatcher::get().process();

		// systems from lua
		scriptManager.process(delta);

		// event bus after scripts
		EntitySystem::EventDispatcher::get().process();

		collisionSystem->Process(delta);
		physicsSystem->Process(delta);

		animationSystem->Process(delta);

		//rendering pipeline
		window.clear();
		renderSystem->Process(delta);
		textRenderingSystem->Process(delta);
		window.display();

	}
	std::cout << "Exit" << std::endl;
	return 0;
}
