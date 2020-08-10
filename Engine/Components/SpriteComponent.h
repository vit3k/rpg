#pragma once
#include "../Vector2.h"
#include "../EntitySystem/Component.h"
#include "../EntitySystem/Time.h"
#include <SFML/Graphics.hpp>
#include <utility>

class Spritesheet {
public:
    sf::Texture texture;
    int spritesCount;
    Vector2 spriteSize;
    std::string texturePath;

    Spritesheet(int spritesCount, const Vector2 &spriteSize, const std::string &texturePath) : spritesCount(
            spritesCount), spriteSize(spriteSize), texturePath(texturePath) {
        texture.loadFromFile(texturePath);
    }

    Spritesheet() = default;

    sf::IntRect getRectForSprite(int spriteIndex, bool flipY);
};

class SpriteComponent : public EntitySystem::Component {
public:
    std::map<std::string, std::shared_ptr<Spritesheet>> spriteSheets;
    std::string currentSpriteSheet;
    int currentSprite;
    sf::Sprite sprite;
    bool flipY = false;
    explicit SpriteComponent(std::map<std::string, std::shared_ptr<Spritesheet>> spriteSheets);
    void setCurrentSprite(int currentSprite);
    void setCurrentSpritesheet(std::string& spritesheet);
};

