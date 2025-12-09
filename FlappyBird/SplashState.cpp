#include <sstream>
#include <iostream>
#include "SplashState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"

namespace LukaGame {
    SplashState::SplashState(GameDataRef ref): _data(ref) {}

    void SplashState::Init() {
        _data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Splash State Background"));
    }

    void SplashState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
        }
    }

    void SplashState::Update(float dt) {
        if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME) {
            _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
        }
    }

    void SplashState::Draw(float dt) {
        _data->window.clear();
        if (_background.has_value()) {
            _data->window.draw(*_background);
        }
        _data->window.display();
    }
}
