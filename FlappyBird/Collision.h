#pragma once

#include <SFML/Graphics.hpp>
#include <variant>

namespace LukaGame {
    class Collision {
        public:
            Collision();
            bool CheckSpriteCollsion(
                std::variant<sf::RectangleShape, sf::Sprite>& s1,
                std::variant<sf::RectangleShape, sf::Sprite>& s2
            );
    };
}
