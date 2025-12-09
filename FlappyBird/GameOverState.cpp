#include <sstream>
#include <iostream>
#include "GameOverState.h"
#include "DEFINITIONS.h"

namespace LukaGame {
    GameOverState::GameOverState(GameDataRef ref): _data(ref) {}

    void GameOverState::Init() {
        _data->assets.LoadTexture("Game Over Background", GAME_BACKGROUND_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Game Over Background"));
    }

    void GameOverState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
        }
    }

    void GameOverState::Update(float dt) {
        
    }

    void GameOverState::Draw(float dt) {
        _data->window.clear();
        if (_background.has_value()) {
            _data->window.draw(*_background);
        }
        _data->window.display();
    }
}
