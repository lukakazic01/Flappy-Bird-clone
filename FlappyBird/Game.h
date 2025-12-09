#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace LukaGame {

    struct GameData {
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
        StateMachine machine;
    };

    using GameDataRef = std::shared_ptr<GameData>;

    class Game {
        public:
            Game(unsigned int width, unsigned int height, std::string title);
        private:
            const float dt = 1.0f / 60.0f; // frame rate - 60 per second
            sf::Clock _clock;
            GameDataRef _data = std::make_shared<GameData>();
            void Run();
    };
};
