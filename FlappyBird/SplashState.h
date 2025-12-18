#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace LukaGame {
    class SplashState : public State {
        public:
            SplashState(GameDataRef);
            ~SplashState() {};
            
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _background;
            sf::Clock _clock;
    };
}
