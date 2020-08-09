#pragma once
#include "../Engine/Vector2.h"
#include "../Engine/EntitySystem//Component.h"
#include "../Engine/EntitySystem/Time.h"
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

    sf::IntRect getRectForSprite(int spriteIndex)
    {
        auto x = (spriteIndex * (int)spriteSize.x) % texture.getSize().x;
        auto y = (int)spriteSize.y * ((spriteIndex * (int)spriteSize.x) / texture.getSize().x);
        return sf::IntRect (x, y, spriteSize.x, spriteSize.y);
    }
};

class SpriteComponent : public EntitySystem::Component {
public:
    std::map<std::string, std::shared_ptr<Spritesheet>> spriteSheets;
    std::string currentSpriteSheet;
    int currentSprite;
    sf::Sprite sprite;
    explicit SpriteComponent(std::map<std::string, std::shared_ptr<Spritesheet>> spriteSheets) {
        this->spriteSheets = spriteSheets;
        currentSprite = 0;
        currentSpriteSheet = spriteSheets.begin()->first;
        auto spritesheet = spriteSheets[currentSpriteSheet];
        sprite.setTexture(spritesheet->texture);
        sprite.setTextureRect(spritesheet->getRectForSprite(currentSprite));
    }

    void setCurrentSprite(int currentSprite) {
        this->currentSprite = currentSprite;
        auto spritesheet = spriteSheets[currentSpriteSheet];
        sprite.setTextureRect(spritesheet->getRectForSprite(currentSprite));
    }
};

class Animation {
public:
    std::string spriteSheetName;
    int fps;
    std::vector<int> frames;
    bool loop;
    int currentFrame;
    EntitySystem::Time frameTime;

    Animation(const std::string &spriteSheetName, int fps, const std::vector<int> &frames, bool loop) : spriteSheetName(
            spriteSheetName), fps(fps), frames(frames), loop(loop) {
        frameTime = EntitySystem::Time::fromSeconds(1.f / (float)fps);
        currentFrame = 0;
    }
};

class AnimationComponent : public EntitySystem::Component {
public:
    std::map<std::string, std::shared_ptr<Animation>> animations;
    std::string currentAnimation;

    void play(const std::string &currentAnimation) {
        if (animations.find(currentAnimation) != animations.end())
            this->currentAnimation = currentAnimation;
    }

    EntitySystem::Time lastFrameTime;

    AnimationComponent(const std::map<std::string, std::shared_ptr<Animation>>& animations) : animations(animations) {}
    AnimationComponent(const std::map<std::string, std::shared_ptr<Animation>>& animations, std::string currentAnimation)
        : animations(animations), currentAnimation(currentAnimation) {}
};