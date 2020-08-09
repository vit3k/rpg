//
// Created by Pawel Witkowski on 09/08/2020.
//

#ifndef RPG_ANIMATIONSYSTEM_H
#define RPG_ANIMATIONSYSTEM_H


#include "../Components/SpriteComponent.h"
#include "EntitySystem/System.h"

class AnimationSystem : public EntitySystem::System<AnimationComponent, SpriteComponent>{
public:
    void ProcessEntity(EntitySystem::EntitySp entity, EntitySystem::Time deltaTime);
};

#endif //RPG_ANIMATIONSYSTEM_H
