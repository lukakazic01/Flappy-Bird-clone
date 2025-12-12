#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"

namespace LukaGame {
    class Pipe {
        public:
            Pipe(GameDataRef data);

            void SpawnBottomPipe();
            void SpawnTopPipe();
            void SpanwInvisiblePipe();
            void MovePipes(float dt);
            void DrawPipes();
            void GeneratePosition();
        private:
            GameDataRef _data;
            std::vector<sf::Sprite> pipeSprites;
            int _pipeSpawnOffset = 0;
            int _landHeight;
    };
}
