#include <sstream>
#include <iostream>
#include "MainMenuState.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"

namespace LukaGame {
    MainMenuState::MainMenuState(GameDataRef ref): _data(ref) {}

void MainMenuState::Init() {
    _data->assets.LoadTexture("Game Title Background", GAME_TITLE_FILEPATH);
    _title.emplace(_data->assets.GetTexture("Game Title Background"));
    _data->assets.LoadTexture("Play Button Background", PLAY_BUTTON_FILEPATH);
    _playButton.emplace(_data->assets.GetTexture("Play Button Background"));
    _data->assets.LoadTexture("Splash State Background", MAIN_MENU_BACKGROUND_FILEPATH);
    _background.emplace(_data->assets.GetTexture("Splash State Background"));
    
    if (_title.has_value()) {
        float titleWidth = _title->getGlobalBounds().size.x;
        _title->setPosition({ (SCREEN_WIDTH / 2) - (titleWidth / 2), 20 });
    }
    if (_playButton.has_value()) {
        float playButtonWidth = _playButton->getGlobalBounds().size.x;
        float playButtonHeight = _playButton->getGlobalBounds().size.y;
        _playButton->setPosition({ (SCREEN_WIDTH / 2) - (playButtonWidth / 2), (SCREEN_HEIGHT / 2) - (playButtonHeight / 2)});
        }
    }

    void MainMenuState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            if (_data->input.isSpriteClicked(*_playButton, sf::Mouse::Button::Left, _data->window)) {
                _data->machine.AddState(StateRef(new GameState(_data)), true);
            }
        }
    }

    void MainMenuState::Update(float dt) {
        
    }

    void MainMenuState::Draw(float dt) {
        _data->window.clear();
        if (_background.has_value()) {
            _data->window.draw(*_background);
        }
        if (_title.has_value()) {
            _data->window.draw(*_title);
        }
        if (_playButton.has_value()) {
            _data->window.draw(*_playButton);
        }
        _data->window.display();
    }
}
