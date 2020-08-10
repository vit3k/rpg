//
// Created by Pawel Witkowski on 10/08/2020.
//

#ifndef RPG_TRANSFORMCOMPONENT_H
#define RPG_TRANSFORMCOMPONENT_H

#include "../EntitySystem/Component.h"
#include "../Vector2.h"

class TransformComponent : public EntitySystem::Component {
public:
    Vector2 position;
    explicit TransformComponent(Vector2 position) : position(position) {}
};

typedef std::shared_ptr<TransformComponent> TransformComponentSp;

#endif //RPG_TRANSFORMCOMPONENT_H
