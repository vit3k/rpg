//
// Created by Pawel Witkowski on 09/08/2020.
//

#ifndef RPG_ANIMATIONSYSTEM_H
#define RPG_ANIMATIONSYSTEM_H


#include "Components/SpriteComponent.h"

#include "EntitySystem/System.h"
#include "Components/AnimationComponent.h"

class AnimationSystem : public EntitySystem::System<AnimationComponent, SpriteComponent>{
    Logger logger = Logger::get("AnimationSystem");
public:
    void ProcessEntity(EntitySystem::EntitySp entity, EntitySystem::Time deltaTime);

protected:
    std::string getName() override;
};

#endif //RPG_ANIMATIONSYSTEM_H
