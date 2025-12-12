#include "Collision.h"

namespace LukaGame {
    Collision::Collision() {};
    bool Collision::CheckSpriteCollsion(sf::Sprite& s1, sf::Sprite& s2) {
        sf::FloatRect rect1 = s1.getGlobalBounds();
        sf::FloatRect rect2 = s2.getGlobalBounds();
        
        if (rect1.findIntersection(rect2)) {
            return true;
        }
        return false;
    }
}

