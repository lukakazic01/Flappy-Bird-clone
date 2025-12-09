#include <sstream>
#include <iostream>
#include "GameState.h"
#include "Pipe.h"
#include "DEFINITIONS.h"

namespace LukaGame {
    GameState::GameState(GameDataRef ref): _data(ref) {}

    void GameState::Init() {
        _data->assets.LoadTexture("Land", LAND_FILEPATH);
        _data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        _data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        pipe = new Pipe(_data);
        land = new Land(_data);
        _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Game Background"));
        pipe->SpawnTopPipe();
        pipe->SpawnBottomPipe();
    }

    void GameState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
        }
    }

    void GameState::Update(float dt) {
        if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) {
            pipe->SpawnTopPipe();
            pipe->SpawnBottomPipe();
            _clock.restart();
        }
        pipe->MovePipes(dt);
        land->MoveLand(dt);
    }

    void GameState::Draw(float dt) {
        _data->window.clear();
        if (_background.has_value()) {
            _data->window.draw(*_background);
            pipe->DrawPipes();
            land->DrawLand();
        }
        _data->window.display();
    }
}
