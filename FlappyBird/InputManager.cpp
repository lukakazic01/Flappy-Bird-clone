#include "InputManager.h"

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

    bool InputManager::isKeyPressed(sf::Keyboard::Key key, const std::optional<sf::Event>& event) {
        if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == key) {
                return true;
            }
        }
        return false;
    };

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window) {
        return sf::Mouse::getPosition(window);
    };
}
