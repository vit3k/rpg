#pragma once
#include "../Engine/Vector2.h"
#include "../EntityW/Component.h"
#include <SFML/Graphics.hpp>

class SpriteComponent : public EntitySystem::Component {
public:
	sf::Texture texture;
	sf::Sprite sprite;
    int spritesCount;
    Vector2 spriteSize;

	SpriteComponent(sf::Texture texture): texture(texture), spritesCount(1)
    {
        spriteSize = Vector2(texture.getSize().x, texture.getSize().y);
    };

	SpriteComponent(sf::Texture texture, int spritesCount, Vector2 spriteSize)
	    : texture(texture), spritesCount(spritesCount), spriteSize(spriteSize) {}
};

class Animation {
public:
    std::string name;
    int fps;
    std::vector<int> frames;
};

class AnimationComponent : public EntitySystem::Component {
public:
    std::map<std::string, Animation> animations;
};