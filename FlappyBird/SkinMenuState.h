#pragma once

#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <array>

namespace LukaGame {
    struct SkinData {
        std::optional<sf::Sprite> containerSprite;
        std::optional<sf::Sprite> birdSprite;
        std::optional<sf::Sprite> lockSprite;
        int unlockScore;
        auto asTuple() { return std::tie(containerSprite, birdSprite, lockSprite); }
    };

    class SkinMenuState : public State {
        public:
            SkinMenuState(GameDataRef data);
            ~SkinMenuState();
            void Init();
            void Update(float dt);
            void Draw(float dt);
            void HandleInput();
        private:
            GameDataRef _data;
            std::optional<sf::Sprite> _background;
            std::optional<sf::Sprite> _skinTable;
            sf::RectangleShape _selectedBirdBorder;
            std::unordered_map<std::string, SkinData> _skinTableContainers;
            std::optional<sf::Sprite> _homeButton;
            int _highScore;
            sf::Vector2f GetHalfOfSkinContainerSize();
            sf::Vector2f GetCenterCoordsForContainer();
            int GetHighScore();
            void SetSkinTablePosition();
            void SetSkinTableContainers();
            void WriteBirdToFile(std::string name);
            void ReadBirdFile();
            void SetHomeButtonPosition();
            void SetBorderForSelectedBird(sf::Sprite& sprite);
    };
}
