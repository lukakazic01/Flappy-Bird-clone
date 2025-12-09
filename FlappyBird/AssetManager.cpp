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

    sf::Texture& AssetManager::GetTexture(std::string name) {
         return _textures[name];
     };

    sf::Font& AssetManager::GetFont(std::string name) {
        return _fonts[name];
    };
}
