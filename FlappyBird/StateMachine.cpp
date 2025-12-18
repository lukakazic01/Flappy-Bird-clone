#include "StateMachine.h"

namespace LukaGame {
    void StateMachine::AddState(StateRef newState, bool isReplacing) {
        _isAdding = true;
        _isReplacing = isReplacing;
        _newState = std::move(newState);
    };

    void StateMachine::RemoveState() {
        _isRemoving = true;
    }

    void StateMachine::ProcessStateChanges() {
        if (_isRemoving && !_states.empty()) {
            _states.pop();
            
            if (!_states.empty()) {
                _states.top()->Resume();
            }
            
            _isRemoving = false;
        }
        
        if (_isAdding) {
            if (!_states.empty()) {
                if (!_isReplacing) {
                    _states.top()->Pause();
                } else {
                    _states.pop();
                }
            }
            _states.push(std::move(_newState));
            _states.top()->Init();
            _isAdding = false;
        }
    }

    StateRef& StateMachine::GetActiveState() {
        return this->_states.top();
    }
}
