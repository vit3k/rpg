//
// Created by Pawel Witkowski on 10/08/2020.
//

#ifndef RPG_TEXTCOMPONENT_H
#define RPG_TEXTCOMPONENT_H

#include <string>
#include "../EntitySystem/Component.h"

class TextComponent : public EntitySystem::Component {
public:
    std::string text;
    TextComponent(std::string text) : text(text) {};
};
#endif //RPG_TEXTCOMPONENT_H
