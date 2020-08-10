//
// Created by Pawel Witkowski on 10/08/2020.
//

#include "AnimationComponent.h"

void AnimationComponent::play(const std::string &animation) {
    if (animation != currentAnimation) {
        if (animations.find(animation) != animations.end()) {
            this->currentAnimation = animation;
            animations[animation]->currentFrame = 0;
        }
    }
}

void Animation::setSpeed(float speed) {
    frameTime = EntitySystem::Time::fromSeconds(1.f / (float)fps * speed);
}