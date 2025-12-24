#include "GameState.h"
#include "Pipe.h"
#include "DEFINITIONS.h"
#include "Collision.h"
#include "GameOverState.h"
#include "PausedState.h"
#include <fstream>

namespace LukaGame {
    GameState::GameState(GameDataRef ref): _data(ref) {}

    void GameState::Init() {
        std::array<std::string, 4> birdFrames = GetSelectedBirdFrames();
        _data->assets.LoadMusic("Background Music", BACKGROND_MUSIC_FILEPATH);
        _data->assets.LoadSound("Hit Sound", HIT_SOUND_FILEPATH);
        _data->assets.LoadSound("Wing Sound", WING_SOUND_FILEPATH);
        _data->assets.LoadSound("Point Sound", POINT_SOUND_FILEPATH);
        _data->assets.LoadTexture("Land", LAND_FILEPATH);
        _data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
        _data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
        _data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
        _data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
        _data->assets.LoadTexture("Bird Frame 1", birdFrames[0]);
        _data->assets.LoadTexture("Bird Frame 2", birdFrames[1]);
        _data->assets.LoadTexture("Bird Frame 3", birdFrames[2]);
        _data->assets.LoadTexture("Bird Frame 4", birdFrames[3]);
        _data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);
        _background.emplace(_data->assets.GetTexture("Game Background"));
        _hitSound.emplace(_data->assets.GetSound("Hit Sound"));
        _wingSound.emplace(_data->assets.GetSound("Wing Sound"));
        _pointSound.emplace(_data->assets.GetSound("Point Sound"));
        _pauseButton.emplace(_data->assets.GetTexture("Pause Button"));
        _backgroundMusic = std::move(_data->assets.GetMusic("Background Music"));
        _gameState = GameStates::eReady;
        pipe = new Pipe(_data);
        land = new Land(_data);
        bird = new Bird(_data);
        flash = new Flash(_data);
        hud = new Hud(_data);
        hud->UpdateScore(_score);
        SetPauseButtonPosition();
    }

    void GameState::Pause() {
        _gameState = GameStates::ePaused;
        _clock.stop();
    }

    void GameState::Resume() {
        _gameState = GameStates::ePlaying;
        _backgroundMusic.setVolume(100.0f);
        _clock.start();
    }

    void GameState::HandleInput() {
        while (const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            if (_data->input.isSpriteClicked(*_background, sf::Mouse::Button::Left, _data->window) ||
                _data->input.isKeyPressed(sf::Keyboard::Key::Space, event)) {
                if (GameStates::eGameOver != _gameState && GameStates::ePaused != _gameState) {
                    _gameState = GameStates::ePlaying;
                    bird->Tap();
                    _wingSound.value().play();
                    if(_backgroundMusic.getStatus() != sf::SoundSource::Status::Playing) {
                        _backgroundMusic.play();
                    }
                }
            }
            if (_data->input.isSpriteClicked(*_pauseButton, sf::Mouse::Button::Left, _data->window) || _data->input.isKeyPressed(sf::Keyboard::Key::P, event)) {
                SetPausedGameState();
            }
            
        }
    }

    void GameState::Update(float dt) {
        if (GameStates::eGameOver == _gameState) {
            flash->Show(dt);
            float volume = _backgroundMusic.getVolume();
            volume -= BACKGROUND_MUSIC_FADE_SPEED * dt;
            if (volume <= 0.f) {
                _backgroundMusic.stop();
                volume = 0.f;
            }

            _backgroundMusic.setVolume(volume);
            if (_clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS) {
                _data->machine.AddState(StateRef(new GameOverState(_data, _score)), true);
            }
        }
        if (GameStates::eGameOver != _gameState && GameStates::ePaused != _gameState) {
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
        _data->window.draw(*_pauseButton);
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

    void GameState::SetPauseButtonPosition() {
        _pauseButton.value().setPosition({ 50.0f, 50.0f });
    }

    void GameState::SetPausedGameState() {
        _backgroundMusic.setVolume(20.0f);
        _data->machine.AddState(StateRef(new PausedState(_data)), false);
    }

    std::array<std::string, 4> GameState::GetSelectedBirdFrames() {
        std::ifstream file("Bird.txt");
        std::string selectedBird;
        if(file.is_open()) {
            file >> selectedBird;
        }
        if (selectedBird == "Red") {
            return { RED_BIRD_FRAME_1_FILEPATH, RED_BIRD_FRAME_2_FILEPATH, RED_BIRD_FRAME_3_FILEPATH, RED_BIRD_FRAME_4_FILEPATH };
        } else if (selectedBird == "Blue") {
            return { BLUE_BIRD_FRAME_1_FILEPATH, BLUE_BIRD_FRAME_2_FILEPATH, BLUE_BIRD_FRAME_3_FILEPATH, BLUE_BIRD_FRAME_4_FILEPATH };
        } else if (selectedBird == "Orange") {
            return { ORANGE_BIRD_FRAME_1_FILEPATH, ORANGE_BIRD_FRAME_2_FILEPATH, ORANGE_BIRD_FRAME_3_FILEPATH, ORANGE_BIRD_FRAME_4_FILEPATH };
        } else {
            return { BIRD_FRAME_1_FILEPATH, BIRD_FRAME_2_FILEPATH, BIRD_FRAME_3_FILEPATH, BIRD_FRAME_4_FILEPATH };
        }
    }

    GameState::~GameState() {
        delete pipe;
        delete land;
        delete hud;
        delete flash;
        delete bird;
    }
}
