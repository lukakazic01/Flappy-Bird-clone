#include "GameState.h"
#include "Pipe.h"
#include "DEFINITIONS.h"
#include "Collision.h"
#include "GameOverState.h"

#include <iostream>

namespace LukaGame {
    GameState::GameState(GameDataRef ref): _data(ref) {}

    void GameState::Init() {
        if (!_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH)) {
            std::cout << "Error loading Hit sound effect" << std::endl;
        }
        if (!_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH)) {
            std::cout << "Error loading Wing sound effect" << std::endl;
        }
        if (!_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH)) {
            std::cout << "Error loading Point sound effect" << std::endl;
        }
        _hitSound.emplace(_hitSoundBuffer);
        _wingSound.emplace(_wingSoundBuffer);
        _pointSound.emplace(_pointSoundBuffer);
        _data->assets.LoadTexture("Land", LAND_FILEPATH);
        _data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        _data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
        _data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Game Background"));
        _gameState = GameStates::eReady;
        pipe = new Pipe(_data);
        land = new Land(_data);
        bird = new Bird(_data);
        flash = new Flash(_data);
        hud = new Hud(_data);
        _score = 0;
        hud->UpdateScore(_score);
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
                    _wingSound.value().play();
                }
            }
        }
    }

    void GameState::Update(float dt) {
        if (GameStates::eGameOver == _gameState) {
            flash->Show(dt);
            if (_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS) {
                _data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
            }
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
                pipe->SpawnScoringPipe();
                _clock.restart();
            }
            pipe->MovePipes(dt);
            pipe->MoveScoringPipes(dt);
            bird->Update(dt);
            CheckCollisionWithLand();
            CheckCollisionWithPipe();
            CheckCollisionWithScoringPipe();
        }
    }

    void GameState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(*_background);
        pipe->DrawPipes();
        land->DrawLand();
        bird->Draw();
        hud->Draw();
        if (GameStates::eGameOver == _gameState) flash->Draw();
        _data->window.display();
    }

    void GameState::CheckCollisionWithPipe() {
        std::vector<sf::Sprite>& pipeSprites = pipe->GetSprites();
        for(unsigned short int i = 0; i < pipeSprites.size(); i++) {
            std::variant<sf::RectangleShape, sf::Sprite> birdHitbox = bird->GetHitbox();
            std::variant<sf::RectangleShape, sf::Sprite> pipeSprite = pipeSprites.at(i);
            if (collision.CheckSpriteCollsion(birdHitbox, pipeSprite)) {
                _gameState = GameStates::eGameOver;
                _clock.restart();
                _hitSound.value().play();
            }
        }
    }

    void GameState::CheckCollisionWithLand() {
        std::vector<sf::Sprite>& landSprites = land->GetSprites();
        for(unsigned short int i = 0; i < landSprites.size(); i++) {
            std::variant<sf::RectangleShape, sf::Sprite> birdHitbox = bird->GetHitbox();
            std::variant<sf::RectangleShape, sf::Sprite> landSprite = landSprites.at(i);
            if (collision.CheckSpriteCollsion(birdHitbox, landSprite)) {
                _gameState = GameStates::eGameOver;
                _clock.restart();
                _hitSound.value().play();
            }
        }
    }

    void GameState::CheckCollisionWithScoringPipe() {
        std::vector<sf::RectangleShape>& scoringPipes = pipe->GetScoringPipes();
        for(unsigned short int i = 0; i < scoringPipes.size(); i++) {
            std::variant<sf::RectangleShape, sf::Sprite> birdHitbox = bird->GetHitbox();
            std::variant<sf::RectangleShape, sf::Sprite> pipeSprite = scoringPipes.at(i);
            if (collision.CheckSpriteCollsion(birdHitbox, pipeSprite)) {
                _score++;
                hud->UpdateScore(_score);
                scoringPipes.erase(scoringPipes.begin() + i);
                _pointSound.value().play();
            }
        }
    }

    GameState::~GameState() {
        delete pipe;
        delete bird;
        delete land;
        delete flash;
    }
}
