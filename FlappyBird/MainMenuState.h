#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace LukaGame {
    class MainMenuState : public State {
        public:
            MainMenuState(GameDataRef);
            ~MainMenuState();
            
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _background;
            std::optional<sf::Sprite> _title;
            std::optional<sf::Sprite> _playButton;
    };
}
