#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace LukaGame {
    class AssetManager {
        public:
            AssetManager() {};
            ~AssetManager() {};
            
            void LoadTexture(std::string name, std::string fileName);
            sf::Texture& GetTexture(std::string name);
            
            void LoadFont(std::string name, std::string fileName);
            sf::Font& GetFont(std::string name);
            
        private:
            std::unordered_map<std::string, sf::Texture> _textures;
            std::unordered_map<std::string, sf::Font> _fonts;
    };
}
