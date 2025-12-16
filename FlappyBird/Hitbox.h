#pragma once
#include <SFML/Graphics.hpp>

namespace LukaGame {
    class Hitbox {
        public:
            Hitbox();
            ~Hitbox();
            sf::RectangleShape& GetHitbox();
            void UpdateHitbox(const sf::Sprite& s);
            void SetHitbox(const sf::Vector2f& size);
        private:
            sf::RectangleShape _hitbox;
    };
}
