#pragma once

#include "State.h"
#include "Game.h"

namespace LukaGame {
    class PausedState : public State {
        public:
            PausedState(GameDataRef data);
            void Init();
            void Update(float dt);
            void HandleInput();
            void Draw(float dt);
        private:
            GameDataRef _data;
    };
}
