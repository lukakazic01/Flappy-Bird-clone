#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "DEFINITIONS.h"
#include "Game.h"
#include "Hitbox.h"

namespace LukaGame {
    class Bird {
        public:
            Bird(GameDataRef data);
            void Draw();
            void Animate(float dt);
            sf::Sprite& GetSprite();
            sf::RectangleShape& GetHitbox();
            void Update(float dt);
            void Tap();
        private:
            GameDataRef _data;
            Hitbox _birdHitbox;
            std::optional<sf::Sprite> _birdSprite;
            std::array<sf::Texture, 4> _animationFrames;
            sf::Clock _clock;
            sf::Clock _movementClock;
            int _birdState;
            float _rotation;
            bool _justFlapped;
    };
}
