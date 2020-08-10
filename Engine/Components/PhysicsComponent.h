//
// Created by Pawel Witkowski on 10/08/2020.
//

#ifndef RPG_PHYSICSCOMPONENT_H
#define RPG_PHYSICSCOMPONENT_H

#include "../EntitySystem/Component.h"
#include "../Vector2.h"

class PhysicsComponent : public EntitySystem::Component {
public:
    Vector2 constraints;
    float bounciness;
    float mass;
    float invertedMass;
    PhysicsComponent(float bounciness, float mass, Vector2 constraints) : bounciness(bounciness), mass(mass), constraints(constraints)
    {
        if (mass != 0) {
            invertedMass = 1 / mass;
        }
        else
        {
            invertedMass = 0;
        }
    }
};
#endif //RPG_PHYSICSCOMPONENT_H
