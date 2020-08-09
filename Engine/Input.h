#pragma once
#include <SFML/Window.hpp>
#include <map>

class Controller {

};
class Input {
    static std::map<std::string, sf::Keyboard::Key> keyMap;
    public:
        static bool isActionPressed(std::string actionName);
        static void init();
};