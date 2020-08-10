//
// Created by Pawel Witkowski on 10/08/2020.
//

#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::map<std::string, std::shared_ptr<Spritesheet>> spriteSheets) {
    this->spriteSheets = spriteSheets;
    currentSprite = 0;
    currentSpriteSheet = spriteSheets.begin()->first;

}

void SpriteComponent::setCurrentSprite(int currentSprite) {
    this->currentSprite = currentSprite;

}

void SpriteComponent::setCurrentSpritesheet(std::string& spritesheet) {
    currentSpriteSheet = spritesheet;
}

sf::IntRect Spritesheet::getRectForSprite(int spriteIndex, bool flipY)
{
    auto x = (spriteIndex * (int)spriteSize.x) % texture.getSize().x;
    if (flipY)
        x += spriteSize.x;

    auto y = (int)spriteSize.y * ((spriteIndex * (int)spriteSize.x) / texture.getSize().x);
    return sf::IntRect (x, y, flipY ? -spriteSize.x : spriteSize.x, spriteSize.y);
}