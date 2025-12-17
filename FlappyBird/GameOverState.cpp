#include <sstream>
#include <iostream>
#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"

namespace LukaGame {
    GameOverState::GameOverState(GameDataRef ref): _data(ref) {}

    void GameOverState::Init() {
        _data->assets.LoadTexture("Game Over Background", GAME_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
        _data->assets.LoadTexture("Game Over Container", GAME_OVER_BODY_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Game Over Background"));
        _gameOverTitle.emplace(_data->assets.GetTexture("Game Over Title"));
        _gameOverContainer.emplace(_data->assets.GetTexture("Game Over Container"));
        _retryButton.emplace(_data->assets.GetTexture("Play Button Background"));
        
        float xPositionTitle = _data->window.getSize().x / 2 - _gameOverTitle.value().getGlobalBounds().size.x / 2;
        float yPositionTitle = _data->window.getSize().y / 10;
        _gameOverTitle.value().setPosition({ xPositionTitle, yPositionTitle });

        float xPositionContainer = _data->window.getSize().x / 2 - _gameOverContainer.value().getGlobalBounds().size.x / 2;
        float yPositionContainer = _data->window.getSize().y / 2 - _gameOverContainer.value().getGlobalBounds().size.y / 2;
        _gameOverContainer.value().setPosition({ xPositionContainer, yPositionContainer });
        
        float xPositionRetryButton = _data->window.getSize().x / 2 - _retryButton.value().getGlobalBounds().size.x / 2;
        _retryButton.value().setPosition({ xPositionRetryButton, yPositionContainer + 300.0f });
    }

    void GameOverState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            if (_data->input.isSpriteClicked(*_retryButton, sf::Mouse::Button::Left, _data->window)) {
                _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
            }
        }
    }

    void GameOverState::Update(float dt) {
        
    }

    void GameOverState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(*_background);
        _data->window.draw(*_gameOverContainer);
        _data->window.draw(*_gameOverTitle);
        _data->window.draw(*_retryButton);
        _data->window.display();
    }
}
