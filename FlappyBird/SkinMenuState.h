#pragma once

#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <map>
#include <array>

namespace LukaGame {
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
            std::unordered_map<
                std::string,
                std::array<std::optional<sf::Sprite>, 2>
            > _skinTableContainers;
            std::optional<sf::Sprite> _homeButton;
            void SetSkinTablePosition();
            void SetSkinTableContainers();
            void WriteBirdToFile(std::string name);
            void ReadBirdFile();
            void SetHomeButtonPosition();
            void SetBorderForSelectedBird(sf::Sprite& sprite);
            sf::Vector2f GetHalfOfSkinContainerSize();
            sf::Vector2f GetCenterCoordsForContainer();
    };
}
