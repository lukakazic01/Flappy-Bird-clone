#include "Hud.h"

namespace LukaGame {

    Hud::Hud(GameDataRef data): _data(data) {
        _scoreText.emplace(_data->assets.GetFont("Flappy Font"));
        _scoreText.value().setString("0");
        _scoreText.value().setCharacterSize(50);
        _scoreText.value().setFillColor(sf::Color::White);
        _scoreText.value().setOrigin({_scoreText.value().getGlobalBounds().size.x / 2, _scoreText.value().getGlobalBounds().size.y / 2 });
        _scoreText.value().setPosition({ (float)_data->window.getSize().x / 2,(float)_data->window.getSize().y / 10 });
    }

    void Hud::Draw() {
        _data->window.draw(*_scoreText);
    }

    void Hud::UpdateScore(int score) {
        _scoreText.value().setString(std::to_string(score));
    }

}
