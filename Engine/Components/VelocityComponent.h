//
// Created by Pawel Witkowski on 10/08/2020.
//

#ifndef RPG_VELOCITYCOMPONENT_H
#define RPG_VELOCITYCOMPONENT_H

#include "../EntitySystem/Component.h"
#include "../Vector2.h"

class VelocityComponent : public EntitySystem::Component {
public:
    Vector2 velocity;
    float bounciness;
    VelocityComponent(Vector2 velocity, float bounciness) : velocity(velocity), bounciness(bounciness) {}
};
#endif //RPG_VELOCITYCOMPONENT_H
