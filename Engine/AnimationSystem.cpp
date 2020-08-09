//
// Created by Pawel Witkowski on 09/08/2020.
//

#include "AnimationSystem.h"


void AnimationSystem::ProcessEntity(EntitySystem::EntitySp entity, EntitySystem::Time deltaTime) {
    auto sprite = entity->get<SpriteComponent>();
    auto animation = entity->get<AnimationComponent>();
    if (!animation->currentAnimation.empty())
    {
        auto currentAnimation = animation->animations[animation->currentAnimation];
        sprite->currentSpriteSheet = currentAnimation->spriteSheetName;
        if (EntitySystem::Time::Elapsed >= (animation->lastFrameTime + currentAnimation->frameTime))
        {
            animation->lastFrameTime = EntitySystem::Time::Elapsed;
            currentAnimation->currentFrame++;
            if (currentAnimation->currentFrame > currentAnimation->frames.size()) {
                currentAnimation->currentFrame = 0;
            }
            sprite->setCurrentSprite(currentAnimation->frames[currentAnimation->currentFrame]);
        }
    }

}
