#pragma once

#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

namespace LukaGame {
    class SkinMenuState : public State {
        public:
            SkinMenuState(GameDataRef data);
            ~SkinMenuState();
            void Init();
            void Update(float dt);
            void Draw(float dt);
            void HandleInput();
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _background;
            std::optional<sf::Sprite> _skinTable;
            std::optional<sf::Sprite> _skinTableContainer;
    };
}
