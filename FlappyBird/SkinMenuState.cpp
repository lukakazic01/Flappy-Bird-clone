#include "SkinMenuState.h"
#include "DEFINITIONS.h"

namespace LukaGame {
    SkinMenuState::SkinMenuState(GameDataRef data): _data(data) {};

    void SkinMenuState::Init() {
        _data->assets.LoadTexture("Skin Table", SKIN_TABLE_FILEPATH);
        _data->assets.LoadTexture("Skin Table Container", SKIN_TABLE_CONTAINER_FILEPATH);
        _skinTable.emplace(_data->assets.GetTexture("Skin Table"));
        _skinTableContainer.emplace(_data->assets.GetTexture("Skin Table Container"));
        _background.emplace(_data->assets.GetTexture("Splash State Background"));
    };

    void SkinMenuState::Draw(float dt) {
        _data->window.clear();
        _data->window.draw(*_background);
        _data->window.draw(*_skinTable);
        _data->window.draw(*_skinTableContainer);
        _data->window.display();
    };

    void SkinMenuState::Update(float dt) {
        
    };

    void SkinMenuState::HandleInput() {
        
    };

    SkinMenuState::~SkinMenuState() {
        
    }
}
