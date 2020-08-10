//
// Created by Pawel Witkowski on 10/08/2020.
//

#ifndef RPG_ANIMATIONCOMPONENT_H
#define RPG_ANIMATIONCOMPONENT_H

#include <string>
#include <vector>
#include <map>
#include "../EntitySystem/Time.h"
#include "../EntitySystem/Component.h"

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
        setSpeed(1.f);
        currentFrame = 0;
    }

    void setSpeed(float speed);
};

class AnimationComponent : public EntitySystem::Component {
public:
    std::map<std::string, std::shared_ptr<Animation>> animations;
    std::string currentAnimation;

    void play(const std::string &animation);

    EntitySystem::Time lastFrameTime;

    AnimationComponent(const std::map<std::string, std::shared_ptr<Animation>>& animations) : animations(animations) {}
    AnimationComponent(const std::map<std::string, std::shared_ptr<Animation>>& animations, std::string currentAnimation)
            : animations(animations), currentAnimation(currentAnimation) {}
};
#endif //RPG_ANIMATIONCOMPONENT_H
