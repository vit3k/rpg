//
// Created by Pawel Witkowski on 10/08/2020.
//

#include <SFML/Graphics/RenderWindow.hpp>
#include "Engine.h"
#include "RenderSystem.h"
#include "TextRenderingSystem.h"
#include "AnimationSystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "ScriptManager.h"

void Engine::Run(const std::string& title, const std::string &script) {
    sf::RenderWindow window(sf::VideoMode(1600, 1200), title);
    window.setFramerateLimit(60);

    std::shared_ptr<RenderSystem> renderSystem(new RenderSystem(&window));
    std::shared_ptr<TextRenderingSystem> textRenderingSystem(new TextRenderingSystem(&window));
    std::shared_ptr<AnimationSystem> animationSystem(new AnimationSystem());

    auto collisionSystem = std::make_shared<CollisionSystem>();
    auto physicsSystem = std::make_shared<PhysicsSystem>();

    ScriptManager scriptManager;
    scriptManager.init();
    scriptManager.run(script);

    auto fpsText = EntitySystem::Entity::create();
    fpsText->attach<TransformComponent>(Vector2(-9.5, -7));
    fpsText->attach<TextComponent>("0");
    fpsText->commit();

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
        fpsText->get<TextComponent>()->text = std::to_string(fps);

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
}
