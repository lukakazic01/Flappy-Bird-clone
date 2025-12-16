#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINITIONS.h"

namespace LukaGame {
    class Flash{
        public:
            Flash(GameDataRef data);
            void Show(float dt);
            void Draw();
        private:
            GameDataRef _data;
            sf::RectangleShape _shape;
            enum class FlashState {
                Off,
                FadeIn,
                FadeOut
            };
            FlashState _flashState = FlashState::Off;
        };
}
