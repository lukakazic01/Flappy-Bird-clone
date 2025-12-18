#include "AssetManager.h"

namespace LukaGame {
    void AssetManager::LoadTexture(std::string name, std::string fileName) {
        sf::Texture texture;
        if (texture.loadFromFile(fileName)) {
            _textures[name] = std::move(texture);
        }
    };


    void AssetManager::LoadFont(std::string name, std::string fileName) {
        sf::Font font(fileName);
        _fonts[name] = std::move(font);
    };

    void AssetManager::LoadSound(std::string name, std::string fileName) {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(fileName)) {
            _sounds[name] = std::move(buffer);
        }
    }

    void AssetManager::LoadMusic(std::string name, std::string fileName) {
        sf::Music music;
        if (music.openFromFile(fileName)) {
            _music[name] = std::move(music);
        }
    }

    sf::Music& AssetManager::GetMusic(std::string name) {
        return _music[name];
    }

    sf::SoundBuffer& AssetManager::GetSound(std::string name) {
        return _sounds[name];
    }


    sf::Texture& AssetManager::GetTexture(std::string name) {
         return _textures[name];
     };

    sf::Font& AssetManager::GetFont(std::string name) {
        return _fonts[name];
    };
}
