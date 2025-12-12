#pragma once

#include <SFML/Graphics.hpp>

namespace LukaGame {
    class Collision {
        public:
            Collision();
            bool CheckSpriteCollsion(sf::Sprite& s1, sf::Sprite& s2);
    };
}
