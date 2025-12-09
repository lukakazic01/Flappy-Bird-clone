#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"

namespace LukaGame {
    class GameState : public State {
        public:
            GameState(GameDataRef);
            ~GameState();
            
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _background;
            Pipe *pipe;
            Land *land;
            sf::Clock _clock;
    };
}
