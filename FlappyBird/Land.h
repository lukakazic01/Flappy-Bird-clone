#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

namespace LukaGame {
    class Land {
        public:
            Land(GameDataRef data);
            void MoveLand(float dt);
            void DrawLand();
        private:
            GameDataRef _data;
            std::vector<sf::Sprite> _landSprites;
    };
}
