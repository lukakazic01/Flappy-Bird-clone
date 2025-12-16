#include <sstream>
#include <iostream>
#include "GameState.h"
#include "Pipe.h"
#include "DEFINITIONS.h"
#include "Collision.h"

namespace LukaGame {
    GameState::GameState(GameDataRef ref): _data(ref) {}

    void GameState::Init() {
        _data->assets.LoadTexture("Land", LAND_FILEPATH);
        _data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        _data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Game Background"));
        _gameState = GameStates::eReady;
        pipe = new Pipe(_data);
        land = new Land(_data);
        bird = new Bird(_data);
        flash = new Flash(_data);
    }

    void GameState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            if (_data->input.isSpriteClicked(*_background, sf::Mouse::Button::Left, _data->window)) {
                if (GameStates::eGameOver != _gameState) {
                    _gameState = GameStates::ePlaying;
                    bird->Tap();
                }
            }
        }
    }

    void GameState::Update(float dt) {
        if (GameStates::eGameOver == _gameState) {
            flash->Show(dt);
        }
        if (GameStates::eGameOver != _gameState) {
            bird->Animate(dt);
            land->MoveLand(dt);
        }
        if (GameStates::ePlaying == _gameState) {
            if (_clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY) {
                pipe->GeneratePosition();
                pipe->SpawnTopPipe();
                pipe->SpawnBottomPipe();
                _clock.restart();
            }
            pipe->MovePipes(dt);
            bird->Update(dt);
            for(unsigned short int i = 0; i < land->GetSprites().size(); i++) {
                std::variant<sf::RectangleShape, sf::Sprite> b = bird->GetHitbox();
                std::variant<sf::RectangleShape, sf::Sprite> l = land->GetSprites().at(i);
                if (collision.CheckSpriteCollsion(b, l)) {
                    _gameState = GameStates::eGameOver;
                }
            }
            for(unsigned short int i = 0; i < pipe->GetSprites().size(); i++) {
                std::variant<sf::RectangleShape, sf::Sprite> b = bird->GetHitbox();
                std::variant<sf::RectangleShape, sf::Sprite> p = pipe->GetSprites().at(i);
                if (collision.CheckSpriteCollsion(b, p)) {
                    _gameState = GameStates::eGameOver;
                }
            }
        }
    }

    void GameState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(*_background);
        pipe->DrawPipes();
        land->DrawLand();
        bird->Draw();
        if (GameStates::eGameOver == _gameState) flash->Draw();
        _data->window.display();
    }

    GameState::~GameState() {
        delete pipe;
        delete bird;
        delete land;
        delete flash;
    }
}
