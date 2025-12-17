#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "Hud.h"

namespace LukaGame {
    class GameState : public State {
        public:
            GameState(GameDataRef);
            ~GameState();
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
            void CheckCollisionWithLand();
            void CheckCollisionWithPipe();
            void CheckCollisionWithScoringPipe();
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _background;
            Pipe *pipe;
            Land *land;
            Bird *bird;
            Flash *flash;
            Hud *hud;
            Collision collision;
            sf::Clock _clock;
            int _gameState;
            int _score;
    };
}
