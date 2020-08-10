#include "Input.h"

std::map<std::string, sf::Keyboard::Key> Input::keyMap;
bool Input::isActionPressed(std::string actionName) {
    if (keyMap.find(actionName) == keyMap.end())
        return false;

    return sf::Keyboard::isKeyPressed(keyMap[actionName]);
}

void Input::init() {
    /*keyMap["move_up"] = sf::Keyboard::Key::W;
    keyMap["move_down"] = sf::Keyboard::Key::S;
    keyMap["move_right"] = sf::Keyboard::Key::D;
    keyMap["move_left"] = sf::Keyboard::Key::A;*/
}

void Input::defineAction(const std::string &actionName, sf::Keyboard::Key key) {
    keyMap[actionName] = key;
}
