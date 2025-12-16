#include "Flash.h"
#include <algorithm>

namespace LukaGame {
    
    Flash::Flash(GameDataRef data): _data(data) {
        _shape.setSize(sf::Vector2f(_data->window.getSize()));
        _shape.setFillColor(sf::Color(255, 255, 255, 0));
        _flashState = FlashState::FadeIn;
        
    };

    void Flash::Show(float dt) {
        if (_flashState == FlashState::Off) return;
        if (_flashState == FlashState::FadeIn) {
            int alphaColor = std::min(_shape.getFillColor().a + (dt * FLASH_SPEED), 255.0f);
            if (alphaColor >= 255.0f) {
                _flashState = FlashState::FadeOut;
            }
            _shape.setFillColor(sf::Color(255, 255, 255, alphaColor));
        } else {
            int alphaColor = std::max(_shape.getFillColor().a - (dt * FLASH_SPEED), 0.0f);
            if (alphaColor <= 0.0f) {
                _flashState = FlashState::Off;
            }
            _shape.setFillColor(sf::Color(255, 255, 255, alphaColor));
        }
    }

    void Flash::Draw() {
        _data->window.draw(_shape);
    }
}
