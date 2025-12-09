#include "Land.h"
#include "DEFINITIONS.h"

namespace LukaGame {
    Land::Land(GameDataRef data): _data(data) {
        sf::Texture& landTexture = _data->assets.GetTexture("Land");
        float y = _data->window.getSize().y - landTexture.getSize().y;
        _landSprites.emplace_back(landTexture);
        _landSprites.emplace_back(landTexture);
        _landSprites[0].setPosition({0.f, y});
        _landSprites[1].setPosition({_landSprites[0].getGlobalBounds().size.x, y});    };

    void Land::MoveLand(float dt) {
        for (unsigned short int i = 0; i < _landSprites.size(); i++) {
            float movement = PIPE_MOVEMENT_SPEED * dt;
            sf::Sprite& sprite = _landSprites.at(i);
            sprite.move({ -movement, 0.0f });
            if (sprite.getPosition().x < -sprite.getGlobalBounds().size.x) {
                sf::Vector2f position(_data->window.getSize().x, sprite.getPosition().y);
                sprite.setPosition(position);
            }
        }
    }
    void Land::DrawLand() {
        for (unsigned short int i = 0; i < _landSprites.size(); i++) {
            sf::Sprite& sprite = _landSprites.at(i);
            _data->window.draw(sprite);
        }
    }
}
