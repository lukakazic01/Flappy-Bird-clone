#include "Bird.h"
#include <iostream>
namespace LukaGame {
    Bird::Bird(GameDataRef data): _data(data) {
        _animationFrames[0] = _data->assets.GetTexture("Bird Frame 1");
        _animationFrames[1] = _data->assets.GetTexture("Bird Frame 2");
        _animationFrames[2] = _data->assets.GetTexture("Bird Frame 3");
        _animationFrames[3] = _data->assets.GetTexture("Bird Frame 4");
        _birdSprite.emplace(_animationFrames.at(0));
        _birdSprite.value().setPosition({ SCREEN_WIDTH / 4, SCREEN_WIDTH / 2 });
        _birdState = BIRD_STATE_STILL;
        sf::FloatRect bounds = _birdSprite.value().getGlobalBounds();
        _birdSprite.value().setOrigin({ bounds.size.x / 2, bounds.size.y / 2 });
        float hitboxWidth = _birdSprite.value().getGlobalBounds().size.x;
        float hitboxHeight = _birdSprite.value().getGlobalBounds().size.y;
        _birdHitbox.SetHitbox({ hitboxWidth, hitboxHeight }, { 0.3f, 0.7f });
    }

    void Bird::Draw() {
        _data->window.draw(*_birdSprite);
        _data->window.draw(_birdHitbox.GetHitbox());
    }

    void Bird::Animate(float dt) {
        if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / _animationFrames.size() ) {
            _birdSprite.value().setTexture(_animationFrames.at(0));
            std::rotate(_animationFrames.begin(), _animationFrames.begin() + 1, _animationFrames.end());
            _clock.restart();
        }
    }

    void Bird::Update(float dt) {
        float elapsed = _movementClock.getElapsedTime().asSeconds();
        if (_birdState == BIRD_STATE_FALLING) {
            _rotation += dt * ROTATION_SPEED;
            if (_rotation > 50.0f) {
                _rotation = 50.0f;
            }
            _birdSprite.value().move({0, GRAVITY * dt });
            _birdSprite.value().setRotation(sf::degrees(_rotation));
        } else if (_birdState == BIRD_STATE_FLYING) {
            float progress = elapsed / FLYING_DURATION;
            _rotation = -35.0f + (35.0f * progress);;
            _birdSprite.value().move({ 0, -(FLYING_SPEED * dt) });
            _birdSprite.value().setRotation(sf::degrees(_rotation));
        }
        _birdHitbox.UpdateHitbox(_birdSprite.value());
        if (elapsed > FLYING_DURATION) {
            _birdState = BIRD_STATE_FALLING;
            _movementClock.restart();
        }
    }

    void Bird::Tap() {
        _movementClock.restart();
        _rotation = -35.0f;
        _birdState = BIRD_STATE_FLYING;
    }

    sf::Sprite& Bird::GetSprite() {
        return _birdSprite.value();
    }

    sf::RectangleShape& Bird::GetHitbox() {
        return _birdHitbox.GetHitbox();
    }
}
