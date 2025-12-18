#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace LukaGame {
    class AssetManager {
        public:
            AssetManager() {};
            ~AssetManager() {};
            
            void LoadTexture(std::string name, std::string fileName);
            sf::Texture& GetTexture(std::string name);
        
            void LoadSound(std::string name, std::string fileName);
            sf::SoundBuffer& GetSound(std::string name);
        
            void LoadMusic(std::string name, std::string fileName);
            sf::Music& GetMusic(std::string name);

            
            void LoadFont(std::string name, std::string fileName);
            sf::Font& GetFont(std::string name);
            
        private:
            std::unordered_map<std::string, sf::Texture> _textures;
            std::unordered_map<std::string, sf::Font> _fonts;
            std::unordered_map<std::string, sf::SoundBuffer> _sounds;
            std::unordered_map<std::string, sf::Music> _music;
    };
}
