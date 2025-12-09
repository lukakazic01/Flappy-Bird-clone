#include "InputManager.h"
#include <iostream>
namespace LukaGame {

    bool InputManager::isSpriteClicked(sf::Sprite& object,  sf::Mouse::Button button, sf::RenderWindow& window) {
        if ( sf::Mouse::isButtonPressed(button)) {
            sf::Vector2f mousePosF = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::FloatRect tempRect = object.getGlobalBounds();
            if (tempRect.contains(mousePosF)) {
                return true;
            }
        };
        return false;
    };

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window) {
        return sf::Mouse::getPosition(window);
    };
}
