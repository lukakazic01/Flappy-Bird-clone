#include "Collision.h"
#include <iostream>
namespace LukaGame {
    Collision::Collision() {};
    
    bool Collision::CheckSpriteCollsion(std::variant<sf::RectangleShape, sf::Sprite>& s1, std::variant<sf::RectangleShape, sf::Sprite>& s2) {
        sf::FloatRect rect1;
        sf::FloatRect rect2;
        std::visit([&](auto&& obj) { rect1 = obj.getGlobalBounds(); }, s1);
        std::visit([&](auto&& obj) { rect2 = obj.getGlobalBounds(); }, s2);
        if (rect1.findIntersection(rect2)) {
            return true;
        }
        return false;
    }
}

