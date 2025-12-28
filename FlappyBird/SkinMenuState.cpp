#include "SkinMenuState.h"
#include "MainMenuState.h"
#include "DEFINITIONS.h"
#include <fstream>

namespace LukaGame {
    SkinMenuState::SkinMenuState(GameDataRef data): _data(data) {};

    void SkinMenuState::Init() {
        _data->assets.LoadTexture("Skin Table", SKIN_TABLE_FILEPATH);
        _data->assets.LoadTexture("Skin Table Container", SKIN_TABLE_CONTAINER_FILEPATH);
        _data->assets.LoadTexture("Classic Bird", BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Blue Bird", BLUE_BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Orange Bird", ORANGE_BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Red Bird", RED_BIRD_FRAME_1_FILEPATH);
        _data->assets.LoadTexture("Home Button", HOME_BUTTON_FILEPATH);
        _homeButton.emplace(_data->assets.GetTexture("Home Button"));
        _background.emplace(_data->assets.GetTexture("Splash State Background"));
        _skinTable.emplace(_data->assets.GetTexture("Skin Table"));
        sf::Sprite sprite(_data->assets.GetTexture("Skin Table Container"));
        sf::Sprite classicBird(_data->assets.GetTexture("Classic Bird"));
        sf::Sprite blueBird(_data->assets.GetTexture("Blue Bird"));
        sf::Sprite redBird(_data->assets.GetTexture("Red Bird"));
        sf::Sprite orangeBird(_data->assets.GetTexture("Orange Bird"));
        
        _skinTableContainers.emplace("Classic Bird data", std::array<std::optional<sf::Sprite>, 2>{ sprite, classicBird });
        _skinTableContainers.emplace("Blue Bird data", std::array<std::optional<sf::Sprite>, 2>{ sprite, blueBird });
        _skinTableContainers.emplace("Orange Bird data", std::array<std::optional<sf::Sprite>, 2>{ sprite, orangeBird });
        _skinTableContainers.emplace("Red Bird data", std::array<std::optional<sf::Sprite>, 2>{ sprite, redBird });
        SetSkinTablePosition();
        SetSkinTableContainers();
        SetHomeButtonPosition();
    };

    void SkinMenuState::Update(float dt) {
        while(const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            if (_data->input.isSpriteClicked(*_skinTableContainers["Classic Bird data"][0], sf::Mouse::Button::Left, _data->window)) {
                writeBirdToFile("Classic");
            }
            if (_data->input.isSpriteClicked(*_skinTableContainers["Blue Bird data"][0], sf::Mouse::Button::Left, _data->window)) {
                writeBirdToFile("Blue");
            }
            if (_data->input.isSpriteClicked(*_skinTableContainers["Orange Bird data"][0], sf::Mouse::Button::Left, _data->window)) {
                writeBirdToFile("Orange");
            }
            if (_data->input.isSpriteClicked(*_skinTableContainers["Red Bird data"][0], sf::Mouse::Button::Left, _data->window)) {
                writeBirdToFile("Red");
            }
            if (_data->input.isSpriteClicked(*_homeButton, sf::Mouse::Button::Left, _data->window)) {
                _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
            }
        }
    };

    void SkinMenuState::writeBirdToFile(std::string value) {
        std::ofstream file("Bird.txt");
        if (file.is_open()) {
            file << value;
            file.close();
        }
    }

    void SkinMenuState::HandleInput() {
        
    };

    void SkinMenuState::Draw(float dt) {
        auto& [classicBirdContainer, classicBirdSprite] = _skinTableContainers["Classic Bird data"];
        auto& [blueBirdContainer, blueBirdSprite] = _skinTableContainers["Blue Bird data"];
        auto& [orangeBirdContainer, orangeBirdSprite] = _skinTableContainers["Orange Bird data"];
        auto& [redBirdContainer, redBirdSprite] = _skinTableContainers["Red Bird data"];
        _data->window.clear();
        _data->window.draw(*_background);
        _data->window.draw(*_skinTable);
        _data->window.draw(*_homeButton);
        _data->window.draw(*classicBirdContainer);
        _data->window.draw(*classicBirdSprite);
        _data->window.draw(*blueBirdContainer);
        _data->window.draw(*blueBirdSprite);
        _data->window.draw(*orangeBirdContainer);
        _data->window.draw(*orangeBirdSprite);
        _data->window.draw(*redBirdContainer);
        _data->window.draw(*redBirdSprite);
        _data->window.display();
    };

    void SkinMenuState::SetHomeButtonPosition() {
        _homeButton.value().setPosition({ 50.0f, 50.0f });
    }

    void SkinMenuState::SetSkinTablePosition() {
        float x = _data->window.getSize().x / 2 - _skinTable.value().getGlobalBounds().size.x / 2;
        float y = _data->window.getSize().y / 2 - _skinTable.value().getGlobalBounds().size.y / 2;
        _skinTable.value().setPosition({ x, y });
    }

    void SkinMenuState::SetSkinTableContainers() {
        auto& [classicBirdContainer, classicBirdSprite] = _skinTableContainers["Classic Bird data"];
        auto& [blueBirdContainer, blueBirdSprite] = _skinTableContainers["Blue Bird data"];
        auto& [orangeBirdContainer, orangeBirdSprite] = _skinTableContainers["Orange Bird data"];
        auto& [redBirdContainer, redBirdSprite] = _skinTableContainers["Red Bird data"];
        
        auto&& [centerX, centerY] = GetCenterCoordsForContainer();
        float tableHeight = _skinTable.value().getGlobalBounds().size.y;
        float tableWidth = _skinTable.value().getGlobalBounds().size.x;
        const auto& [halfX, halfY] = GetHalfOfSkinContainerSize();
    
        float upperX = (float)(centerX - tableWidth * 0.25);
        float upperY = (float)(centerY - (tableHeight * 0.2));
        
        float lowerX = (centerX + tableWidth * 0.25);
        float lowerY = (float)(centerY + (tableHeight * 0.2));
        
        float halfWidthClassicBird = (*classicBirdSprite).getGlobalBounds().size.x / 2;
        float halfHeightClassicBird = (*classicBirdSprite).getGlobalBounds().size.y / 2;
        float halfWidthOtherSkin = (*redBirdSprite).getGlobalBounds().size.x / 2;
        float halfHeightOtherSkin = (*redBirdSprite).getGlobalBounds().size.y / 2;
        
        (*classicBirdContainer).setPosition({ upperX, upperY });
        (*blueBirdContainer).setPosition({ lowerX, upperY });
        (*orangeBirdContainer).setPosition({ lowerX, lowerY });
        (*redBirdContainer).setPosition({ upperX, lowerY });
        
        (*classicBirdSprite).setPosition({ upperX + halfX - halfWidthClassicBird, upperY + halfY - halfHeightClassicBird});
        (*blueBirdSprite).setPosition({ lowerX + halfX - halfWidthOtherSkin, upperY + halfY - halfHeightOtherSkin });
        (*orangeBirdSprite).setPosition({ lowerX + halfX - halfWidthOtherSkin, lowerY + halfY - halfHeightOtherSkin });
        (*redBirdSprite).setPosition({ upperX + halfX - halfWidthOtherSkin, lowerY + halfY - halfHeightOtherSkin });
    }
    
    sf::Vector2f SkinMenuState::GetCenterCoordsForContainer() {
        sf::Sprite& classicBirdContainer = _skinTableContainers["Classic Bird data"][0].value();
        float centerX = _data->window.getSize().x / 2;
        float centerY = _data->window.getSize().y / 2;
        float skinContainerWidth = classicBirdContainer.getGlobalBounds().size.x;
        float skinContainerHeight = classicBirdContainer.getGlobalBounds().size.y;
        return { centerX - skinContainerWidth / 2, centerY - skinContainerHeight / 2 };
    }

    sf::Vector2f SkinMenuState::GetHalfOfSkinContainerSize() {
        sf::Sprite skinContainer = _skinTableContainers["Classic Bird data"][0].value();
        return { skinContainer.getGlobalBounds().size.x / 2, skinContainer.getGlobalBounds().size.y / 2 };
    }

    SkinMenuState::~SkinMenuState() {
        
    }
}
