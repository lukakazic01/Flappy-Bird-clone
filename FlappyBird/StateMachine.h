#pragma once

#include <memory>
#include <stack>
#include "State.h"

namespace LukaGame {
    using StateRef = std::unique_ptr<State>;
    class StateMachine {
        public:
            StateMachine() {}
            ~StateMachine() {}
            
            void AddState(StateRef newState, bool isReplacing = true);
            void RemoveState();
            void ProcessStateChanges();
            StateRef& GetActiveState();
        private:
            std::stack<StateRef> _states;
            StateRef _newState;
            bool _isRemoving;
            bool _isAdding;
            bool _isReplacing;
    };
}
