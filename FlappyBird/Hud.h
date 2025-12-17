#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"

namespace LukaGame {
    class Hud {
        public:
            Hud(GameDataRef data);
            void Draw();
            void UpdateScore(int score);
        private:
            GameDataRef _data;
            std::optional<sf::Text> _scoreText;
    };
}
