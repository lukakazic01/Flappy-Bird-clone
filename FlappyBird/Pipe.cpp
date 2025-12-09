#include "Pipe.h"
#include "DEFINITIONS.h"
#include <iostream>

namespace LukaGame {
    Pipe::Pipe(GameDataRef data): _data(data) {}

    void Pipe::DrawPipes() {
        for (unsigned short int i = 0; i < pipeSprites.size(); i++) {
            _data->window.draw(pipeSprites.at(i));
        }
    }
    void Pipe::SpawnBottomPipe() {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));
        sprite.setPosition({ (float)_data->window.getSize().x, _data->window.getSize().y - sprite.getGlobalBounds().size.y });
        pipeSprites.push_back(sprite);
    }
    void Pipe::SpawnTopPipe() {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Up"));
        sprite.setPosition({ (float)_data->window.getSize().x, 0 });
        pipeSprites.push_back(sprite);
    }
    void Pipe::SpanwInvisiblePipe() {
        sf::Sprite sprite(_data->assets.GetTexture("Pipe Down"));
        sprite.setPosition({ (float)_data->window.getSize().x, _data->window.getSize().y - sprite.getGlobalBounds().size.y });
        sprite.setColor(sf::Color(0, 0, 0, 0));
        pipeSprites.push_back(sprite);
    }
    void Pipe::MovePipes(float dt) {
        for(unsigned short int i = 0; i < pipeSprites.size(); i++) {
            sf::Sprite& pipe = pipeSprites.at(i);
            if (pipe.getPosition().x < -pipe.getGlobalBounds().size.x) {
                pipeSprites.erase(pipeSprites.begin() + i);
                std::cout << pipeSprites.size() << std::endl;

            }
            float movement = PIPE_MOVEMENT_SPEED * dt;
            pipe.move({ -movement, 0 });
        }
    }
}
