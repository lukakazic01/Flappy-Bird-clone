#include "MainMenuState.h"
#include "GameState.h"
#include "SkinMenuState.h"
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"

namespace LukaGame {
    MainMenuState::MainMenuState(GameDataRef ref): _data(ref) {}

    void MainMenuState::Init() {
        _data->assets.LoadTexture("Game Title Background", GAME_TITLE_FILEPATH);
        _data->assets.LoadTexture("Play Button Background", PLAY_BUTTON_FILEPATH);
        _data->assets.LoadTexture("Splash State Background", MAIN_MENU_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Cosmetics Button", COSMETICS_BUTTON_FILEPATH);
        _title.emplace(_data->assets.GetTexture("Game Title Background"));
        _playButton.emplace(_data->assets.GetTexture("Play Button Background"));
        _background.emplace(_data->assets.GetTexture("Splash State Background"));
        _cosmeticsButton.emplace(_data->assets.GetTexture("Cosmetics Button"));
        
        float titleWidth = _title->getGlobalBounds().size.x;
        _title->setPosition({ (SCREEN_WIDTH / 2) - (titleWidth / 2), 20 });
        float playButtonWidth = _playButton->getGlobalBounds().size.x;
        float playButtonHeight = _playButton->getGlobalBounds().size.y;
        _playButton->setPosition({ (SCREEN_WIDTH / 2) - (playButtonWidth / 2), (SCREEN_HEIGHT / 2) - (playButtonHeight / 2)});
        float cosmeticsButtonWidth = _cosmeticsButton->getGlobalBounds().size.x;
        float cosmeticsButtonHeight = _cosmeticsButton->getGlobalBounds().size.y;
        _cosmeticsButton->setPosition({ (SCREEN_WIDTH / 2) - (cosmeticsButtonWidth / 2), (SCREEN_HEIGHT / 2) + ((cosmeticsButtonHeight * 2) / 2)});
    }

    void MainMenuState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            if (_data->input.isSpriteClicked(*_playButton, sf::Mouse::Button::Left, _data->window)) {
                _data->machine.AddState(StateRef(new GameState(_data)), true);
            }
            if (_data->input.isSpriteClicked(*_cosmeticsButton, sf::Mouse::Button::Left, _data->window)) {
                _data->machine.AddState(StateRef(new SkinMenuState(_data)), true);
            }
        }
    }

    void MainMenuState::Update(float dt) {
        
    }

    void MainMenuState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(*_background);
        _data->window.draw(*_title);
        _data->window.draw(*_playButton);
        _data->window.draw(*_cosmeticsButton);
        _data->window.display();
    }
}
