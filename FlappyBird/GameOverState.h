#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace LukaGame {
    class GameOverState : public State {
        public:
            GameOverState(GameDataRef, int score);
            ~GameOverState();
            
            void Init();
            void HandleInput();
            void Update(float dt);
            void Draw(float dt);
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _background;
            std::optional<sf::Sprite> _gameOverTitle;
            std::optional<sf::Sprite> _gameOverContainer;
            std::optional<sf::Sprite> _retryButton;
            std::optional<sf::Text> _scoreText;
            std::optional<sf::Text> _highScoreText;
            int _score;
            int _highScore;
    };
}
