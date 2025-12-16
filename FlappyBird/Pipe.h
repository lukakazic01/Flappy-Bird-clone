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
            void SpawnScoringPipe();
            void MovePipes(float dt);
            void MoveScoringPipes(float dt);
            void DrawPipes();
            void GeneratePosition();
            std::vector<sf::Sprite>& GetSprites();
            std::vector<sf::RectangleShape>& GetScoringPipes();
        private:
            GameDataRef _data;
            std::vector<sf::Sprite> _pipeSprites;
            std::vector<sf::RectangleShape> _scoringPipes;
            int _pipeSpawnOffset = 0;
            int _landHeight;
    };
}
