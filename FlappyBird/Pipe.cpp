#include "Pipe.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <random>

namespace LukaGame {
    Pipe::Pipe(GameDataRef data): _data(data) {
        _landHeight = sf::Sprite(_data->assets.GetTexture("Land")).getGlobalBounds().size.y;
    }

    void Pipe::DrawPipes() {
        for (unsigned short int i = 0; i < _pipeSprites.size(); i++) {
            _data->window.draw(_pipeSprites.at(i));
        }
    }

    void Pipe::SpawnBottomPipe() {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));
        float y = _data->window.getSize().y - sprite.getGlobalBounds().size.y - _pipeSpawnOffset;
        sprite.setPosition({ (float)_data->window.getSize().x, y });
        _pipeSprites.push_back(sprite);
    }

    void Pipe::SpawnTopPipe() {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));
        float y = _pipeSpawnOffset ? -_pipeSpawnOffset : 0.0f;
        sprite.setPosition({ (float)_data->window.getSize().x, y });
        _pipeSprites.push_back(sprite);
    }

    void Pipe::MovePipes(float dt) {
        for(unsigned short int i = 0; i < _pipeSprites.size(); i++) {
            sf::Sprite& pipe = _pipeSprites.at(i);
            if (pipe.getPosition().x < -pipe.getGlobalBounds().size.x) {
                _pipeSprites.erase(_pipeSprites.begin() + i);
            }
            float movement = PIPE_MOVEMENT_SPEED * dt;
            pipe.move({ -movement, 0 });
        }
    }

    void Pipe::SpawnScoringPipe() {
        sf::RectangleShape shape({ _pipeSprites.at(0).getLocalBounds().size.x, (float)_data->window.getSize().y });
        shape.setFillColor(sf::Color::Transparent);
        shape.setPosition(sf::Vector2f({ (float)_data->window.getSize().x, 0 }));
        _scoringPipes.push_back(shape);
    }

    void Pipe::MoveScoringPipes(float dt) {
        for(unsigned short int i = 0; i < _scoringPipes.size(); i++) {
            sf::RectangleShape& pipe = _scoringPipes.at(i);
            float movement = PIPE_MOVEMENT_SPEED * dt;
            pipe.move({ -movement, 0 });
        }
    }

    void Pipe::GeneratePosition() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, _landHeight);
        _pipeSpawnOffset = dist(gen);
    }

    std::vector<sf::Sprite>& Pipe::GetSprites() {
        return _pipeSprites;
    }

    std::vector<sf::RectangleShape>& Pipe::GetScoringPipes() {
        return _scoringPipes;
    }
}
