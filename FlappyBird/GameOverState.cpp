#include <iostream>
#include <fstream>

#include "GameOverState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"

namespace LukaGame {
    GameOverState::GameOverState(GameDataRef ref, int score): _data(ref), _score(score) {}

    void GameOverState::Init() {
        _data->assets.LoadTexture("Game Over Background", GAME_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
        _data->assets.LoadTexture("Game Over Container", GAME_OVER_BODY_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Game Over Background"));
        _gameOverTitle.emplace(_data->assets.GetTexture("Game Over Title"));
        _gameOverContainer.emplace(_data->assets.GetTexture("Game Over Container"));
        _retryButton.emplace(_data->assets.GetTexture("Play Button Background"));
        HandleSettingHighscore();
        SetScoreTextOptions();
        SetHighScoreTextOptions();
        SetContainerPosition();
        SetTitlePosition();
        SetRetryButtonPosition();
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
        _data->window.draw(*_scoreText);
        _data->window.draw(*_highScoreText);
        _data->window.display();
    }

    void GameOverState::HandleSettingHighscore() {
        _highScore = 0;
        std::ifstream readFile(HIGHSCORE_FILEPATH);
        if (readFile.is_open()) {
            readFile >> _highScore;
            readFile.close();
        }
        if (_score > _highScore) {
            _highScore = _score;
        }
        std::ofstream writeFile(HIGHSCORE_FILEPATH);
        if (writeFile.is_open()) {
            writeFile << _highScore;
            writeFile.close();
        }
    }


    int GameOverState::GetContainerYPosition() {
        return _data->window.getSize().y / 2 - _gameOverContainer.value().getGlobalBounds().size.y / 2;
    }

    int GameOverState::GetContainerHeight() {
        return _gameOverContainer.value().getGlobalBounds().size.y;
    }

    void GameOverState::SetContainerPosition() {
        float xPositionContainer = _data->window.getSize().x / 2 - _gameOverContainer.value().getGlobalBounds().size.x / 2;
        float yPositionContainer = _data->window.getSize().y / 2 - _gameOverContainer.value().getGlobalBounds().size.y / 2;
        _gameOverContainer.value().setPosition({ xPositionContainer, yPositionContainer });
    }

    void GameOverState::SetTitlePosition() {
        float xPositionTitle = _data->window.getSize().x / 2 - _gameOverTitle.value().getGlobalBounds().size.x / 2;
        float yPositionTitle = GetContainerYPosition() - _gameOverTitle.value().getGlobalBounds().size.y * 1.2f;
        _gameOverTitle.value().setPosition({ xPositionTitle, yPositionTitle });
    }

    void GameOverState::SetRetryButtonPosition() {
        
        float xPositionRetryButton = _data->window.getSize().x / 2 - _retryButton.value().getGlobalBounds().size.x / 2;
        float yPositionRetryButton = GetContainerYPosition() + GetContainerHeight() + _retryButton.value().getGlobalBounds().size.y * 0.2f;
        _retryButton.value().setPosition({ xPositionRetryButton, yPositionRetryButton });
    }


    void GameOverState::SetHighScoreTextOptions() {
        _highScoreText.emplace(_data->assets.GetFont("Flappy Font"));
        _highScoreText.value().setCharacterSize(50);
        _highScoreText.value().setString(std::to_string(_highScore));
        _highScoreText.value().setFillColor(sf::Color::Magenta);
        _highScoreText.value().setOrigin({ _highScoreText.value().getGlobalBounds().size.x / 2, _highScoreText.value().getGlobalBounds().size.y / 2 });
        _highScoreText.value().setPosition({
            ((float)_data->window.getSize().x / 2) * 1.5f,
            (float)_data->window.getSize().y / 2 + _highScoreText.value().getGlobalBounds().size.y * 1.5f
        });

    }

    void GameOverState::SetScoreTextOptions() {
        _scoreText.emplace(_data->assets.GetFont("Flappy Font"));
        _scoreText.value().setCharacterSize(50);
        _scoreText.value().setString(std::to_string(_score));
        _scoreText.value().setFillColor(sf::Color::White);
        _scoreText.value().setOrigin({ _scoreText.value().getGlobalBounds().size.x / 2, _scoreText.value().getGlobalBounds().size.y / 2 });
        _scoreText.value().setPosition({
            ((float)_data->window.getSize().x / 2) * 1.5f,
            ((float)_data->window.getSize().y / 2) - _scoreText.value().getGlobalBounds().size.y
        });
    }
}
