#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "DEFINITIONS.h"
#include "Game.h"

namespace LukaGame {
    class Bird {
        public:
            Bird(GameDataRef data);
            void Draw();
            void Animate(float dt);
            sf::Sprite& GetSprite();
        void Update(float dt);
        void Tap();
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _birdSprite;
            std::array<sf::Texture, 4> _animationFrames;
            sf::Clock _clock;
            sf::Clock _movementClock;
            int _birdState;
            float _rotation;
            bool _justFlapped;
    };
}
