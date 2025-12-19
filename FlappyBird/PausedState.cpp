#include "PausedState.h"
#include "DEFINITIONS.h"

namespace LukaGame {
    PausedState::PausedState(GameDataRef data): _data(data) {};

    void PausedState::Init() {
        _data->assets.LoadTexture("Resume button", RESUME_BUTTON_FILEPATH);
        if (_backgroundTexture.resize(_data->window.getSize())) {
            _backgroundTexture.update(_data->window);
            _background.emplace(_backgroundTexture);
        }
        _resumeButton.emplace(_data->assets.GetTexture("Resume button"));
        SetResumeButtonPosition();
    }

    void PausedState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(*_background);
        _data->window.draw(*_resumeButton);
        _data->window.display();
    }

    void PausedState::Update(float dt) {
        
    }

    void PausedState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            
            if (_data->input.isSpriteClicked(*_resumeButton, sf::Mouse::Button::Left, _data->window)) {
                _data->machine.RemoveState();
            }
        }
    }

    void PausedState::SetResumeButtonPosition() {
        _resumeButton.value().setPosition({ 50.0f, 50.0f });
    }
}
