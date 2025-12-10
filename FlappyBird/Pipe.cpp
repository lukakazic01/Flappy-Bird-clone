#include "Pipe.h"
#include "DEFINITIONS.h"
#include <iostream>
#include <random>

namespace LukaGame {
    Pipe::Pipe(GameDataRef data): _data(data) {
        _landHeight = sf::Sprite(_data->assets.GetTexture("Land")).getGlobalBounds().size.y;
    }

    void Pipe::DrawPipes() {
        for (unsigned short int i = 0; i < pipeSprites.size(); i++) {
            _data->window.draw(pipeSprites.at(i));
        }
    }
    void Pipe::SpawnBottomPipe() {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));
        float y = _data->window.getSize().y - sprite.getGlobalBounds().size.y - _pipeSpawnOffset;
        sprite.setPosition({ (float)_data->window.getSize().x, y });
        pipeSprites.push_back(sprite);
    }
    void Pipe::SpawnTopPipe() {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));
        float y = _pipeSpawnOffset ? -_pipeSpawnOffset : 0.0f;
        sprite.setPosition({ (float)_data->window.getSize().x, y });
        pipeSprites.push_back(sprite);
    }
    void Pipe::MovePipes(float dt) {
        for(unsigned short int i = 0; i < pipeSprites.size(); i++) {
            sf::Sprite& pipe = pipeSprites.at(i);
            if (pipe.getPosition().x < -pipe.getGlobalBounds().size.x) {
                pipeSprites.erase(pipeSprites.begin() + i);
            }
            float movement = PIPE_MOVEMENT_SPEED * dt;
            pipe.move({ -movement, 0 });
        }
    }
    void Pipe::GenerateRandomNumber() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, _landHeight);
        _pipeSpawnOffset = dist(gen);
    }
}
