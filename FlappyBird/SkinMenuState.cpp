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
        _data->assets.LoadTexture("Lock", LOCK_FILEPATH);
        _homeButton.emplace(_data->assets.GetTexture("Home Button"));
        _background.emplace(_data->assets.GetTexture("Splash State Background"));
        _skinTable.emplace(_data->assets.GetTexture("Skin Table"));
        sf::Sprite skinTableContainer(_data->assets.GetTexture("Skin Table Container"));
        sf::Sprite lock(_data->assets.GetTexture("Lock"));
        sf::Sprite classicBird(_data->assets.GetTexture("Classic Bird"));
        sf::Sprite blueBird(_data->assets.GetTexture("Blue Bird"));
        sf::Sprite redBird(_data->assets.GetTexture("Red Bird"));
        sf::Sprite orangeBird(_data->assets.GetTexture("Orange Bird"));
        _highScore = GetHighScore();
        _skinTableContainers["Classic"] = SkinData{
            sf::Sprite(_data->assets.GetTexture("Skin Table Container")),
            sf::Sprite(_data->assets.GetTexture("Classic Bird")),
            sf::Sprite(_data->assets.GetTexture("Lock")),
            0
        };

        _skinTableContainers["Blue"] = SkinData{
            sf::Sprite(_data->assets.GetTexture("Skin Table Container")),
            sf::Sprite(_data->assets.GetTexture("Blue Bird")),
            sf::Sprite(_data->assets.GetTexture("Lock")),
            BLUE_BIRD_UNLOCK_QUOTA
        };

        _skinTableContainers["Orange"] = SkinData{
            sf::Sprite(_data->assets.GetTexture("Skin Table Container")),
            sf::Sprite(_data->assets.GetTexture("Orange Bird")),
            sf::Sprite(_data->assets.GetTexture("Lock")),
            ORANGE_BIRD_UNLOCK_QUOTA
        };

        _skinTableContainers["Red"] = SkinData{
            sf::Sprite(_data->assets.GetTexture("Skin Table Container")),
            sf::Sprite(_data->assets.GetTexture("Red Bird")),
            sf::Sprite(_data->assets.GetTexture("Lock")),
            RED_BIRD_UNLOCK_QUOTA
        };
        SetSkinTablePosition();
        SetSkinTableContainers();
        SetHomeButtonPosition();
        ReadBirdFile();
    };

    void SkinMenuState::Update(float dt) {
    };

    void SkinMenuState::HandleInput() {
        while(const std::optional event = _data->window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                _data->window.close();
            }
            for (auto& [key, skin] : _skinTableContainers) {
               if (_data->input.isSpriteClicked(*skin.containerSprite, sf::Mouse::Button::Left, _data->window)) {
                   if (_highScore >= skin.unlockScore) {
                       WriteBirdToFile(key);
                       SetBorderForSelectedBird(*skin.containerSprite);
                   }
               }
           }
            if (_data->input.isSpriteClicked(*_homeButton, sf::Mouse::Button::Left, _data->window)) {
                _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
            }
        }
    };

    void SkinMenuState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(*_background);
        _data->window.draw(*_skinTable);
        _data->window.draw(*_homeButton);
        for (auto& [key, skin] : _skinTableContainers) {
            _data->window.draw(*skin.containerSprite);
            _data->window.draw(*skin.birdSprite);
            if (skin.unlockScore >= _highScore) {
                _data->window.draw(*skin.lockSprite);
            }
       }
        _data->window.draw(_selectedBirdBorder);
        _data->window.display();
    };
    
    int SkinMenuState::GetHighScore(){
        std::ifstream file("Highscore.txt");
        int highScore;
        file >> highScore;
        return highScore;
    }

    void SkinMenuState::SetBorderForSelectedBird(sf::Sprite& birdContainerSprite) {
        _selectedBirdBorder.setSize(birdContainerSprite.getGlobalBounds().size);
        _selectedBirdBorder.setPosition(birdContainerSprite.getGlobalBounds().position);
        _selectedBirdBorder.setFillColor(sf::Color::Transparent);
        _selectedBirdBorder.setOutlineColor(sf::Color::Yellow);
        _selectedBirdBorder.setOutlineThickness(5.0f);
    }

    void SkinMenuState::WriteBirdToFile(std::string value) {
        std::ofstream file("Bird.txt");
        if (file.is_open()) {
            file << value;
            file.close();
        }
    }

    void SkinMenuState::ReadBirdFile() {
        std::ifstream file("Bird.txt");
        if (file.is_open()) {
            std::string selectedBird;
            file >> selectedBird;
            SetBorderForSelectedBird(*_skinTableContainers[selectedBird].containerSprite);
            file.close();
        }
    }

    void SkinMenuState::SetHomeButtonPosition() {
        _homeButton.value().setPosition({ 50.0f, 50.0f });
    }

    void SkinMenuState::SetSkinTablePosition() {
        float x = _data->window.getSize().x / 2 - _skinTable.value().getGlobalBounds().size.x / 2;
        float y = _data->window.getSize().y / 2 - _skinTable.value().getGlobalBounds().size.y / 2;
        _skinTable.value().setPosition({ x, y });
    }

    void SkinMenuState::SetSkinTableContainers() {
        auto [classicBirdContainer, classicBirdSprite, classicBirdLock] = _skinTableContainers["Classic"].asTuple();
        auto [blueBirdContainer, blueBirdSprite, blueBirdLock] = _skinTableContainers["Blue"].asTuple();
        auto [orangeBirdContainer, orangeBirdSprite, orangeBirdLock] = _skinTableContainers["Orange"].asTuple();
        auto [redBirdContainer, redBirdSprite, redBirdLock] = _skinTableContainers["Red"].asTuple();

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
        (*orangeBirdContainer).setPosition({ upperX, lowerY });
        (*redBirdContainer).setPosition({ lowerX, lowerY });
        
        (*classicBirdLock).setPosition((*classicBirdContainer).getGlobalBounds().position);
        (*blueBirdLock).setPosition((*blueBirdContainer).getGlobalBounds().position);
        (*orangeBirdLock).setPosition((*orangeBirdContainer).getGlobalBounds().position);
        (*redBirdLock).setPosition((*redBirdContainer).getGlobalBounds().position);
        
        (*classicBirdSprite).setPosition({ upperX + halfX - halfWidthClassicBird, upperY + halfY - halfHeightClassicBird});
        (*blueBirdSprite).setPosition({ lowerX + halfX - halfWidthOtherSkin, upperY + halfY - halfHeightOtherSkin });
        (*orangeBirdSprite).setPosition({ upperX + halfX - halfWidthOtherSkin, lowerY + halfY - halfHeightOtherSkin });
        (*redBirdSprite).setPosition({ lowerX + halfX - halfWidthOtherSkin, lowerY + halfY - halfHeightOtherSkin });
    }
    
    sf::Vector2f SkinMenuState::GetCenterCoordsForContainer() {
        sf::Sprite& classicBirdContainer = _skinTableContainers["Classic"].containerSprite.value();
        float centerX = _data->window.getSize().x / 2;
        float centerY = _data->window.getSize().y / 2;
        float skinContainerWidth = classicBirdContainer.getGlobalBounds().size.x;
        float skinContainerHeight = classicBirdContainer.getGlobalBounds().size.y;
        return { centerX - skinContainerWidth / 2, centerY - skinContainerHeight / 2 };
    }

    sf::Vector2f SkinMenuState::GetHalfOfSkinContainerSize() {
        sf::Sprite skinContainer = _skinTableContainers["Classic"].containerSprite.value();
        return { skinContainer.getGlobalBounds().size.x / 2, skinContainer.getGlobalBounds().size.y / 2 };
    }

    SkinMenuState::~SkinMenuState() {
        
    }
}
