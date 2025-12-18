#include "Hitbox.h"
#include <iostream>
namespace LukaGame {

    Hitbox::Hitbox() {};

    Hitbox::~Hitbox() {};

    sf::RectangleShape& Hitbox::GetHitbox() {
        return _hitbox;
    }

    void Hitbox::UpdateHitbox(const sf::Sprite& s) {
        _hitbox.setOrigin(s.getOrigin());
        _hitbox.setPosition(s.getPosition());
    }

    void Hitbox::SetHitbox(const sf::Vector2f& size, const sf::Vector2f& scale) {
        _hitbox.setSize(size);
        _hitbox.setScale(scale);
        _hitbox.setFillColor(sf::Color::Red);
    }
};
