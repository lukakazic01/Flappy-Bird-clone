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
        _hitbox.setRotation(s.getRotation());
        _hitbox.setScale({ s.getScale().x - 0.3f, s.getScale().y }); // TODO: Not good, this is only for bird case
    }

    void Hitbox::SetHitbox(const sf::Vector2f& size) {
        _hitbox.setSize(size);
        _hitbox.setFillColor(sf::Color::White);
    }
};
