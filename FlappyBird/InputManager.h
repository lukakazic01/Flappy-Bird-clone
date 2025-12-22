#pragma once

#include <SFML/Graphics.hpp>

namespace LukaGame {
    class InputManager {
        public:
            InputManager() {};
            ~InputManager() {};
            
            bool isSpriteClicked (sf::Sprite& object,  sf::Mouse::Button button, sf::RenderWindow& window);
            bool isKeyPressed (sf::Keyboard::Key key, const std::optional<sf::Event>& event);
            sf::Vector2i GetMousePosition(sf::RenderWindow& window);
        };
}
