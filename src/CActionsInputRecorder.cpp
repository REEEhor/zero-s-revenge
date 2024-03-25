#include "CActionsInputRecorder.h"

// Pops recorded keys and converts them into actions via conversion map.
std::vector<Action::EAction> CActionsInputRecorder::pop_actions() {
    std::vector<char> recordedInputs = CInputRecorder::pop_recorded_inputs();
    std::vector<Action::EAction> result;
    
    result.reserve(recordedInputs.size());
    for (const auto& inputAsChar: recordedInputs) {
        // Push back converted key as action.
        result.push_back(m_ActionsMap.at(inputAsChar));
    }
    return result;
}

CActionsInputRecorder::CActionsInputRecorder(char up, char down, char left, char right, char shoot, char firstGun,
                                             char secondGun, char thirdGun, char fourthGun, char fifthGun,
                                             char sixthGun, char seventhGun, char eightGun, char ninthGun) {
    
    const std::vector<char> inputs = {up, down, left, right, shoot, firstGun,
                               secondGun, thirdGun, fourthGun, fifthGun,
                               sixthGun, seventhGun, eightGun, ninthGun};
    
    // By this method (of putting inputs in a vector and using static_cast) it is easy to
    // add more actions in the future. The actions are tied to be declared in the same order
    // as are chars in %inputs.
    for (size_t i = 0; i < inputs.size(); ++i) {
        m_ActionsMap.insert({inputs[i], static_cast<Action::EAction>(i)});
    }
    
    // Detection of multiple actions corresponding to one key.
    if (m_ActionsMap.size() != Action::EAction::ACTION_COUNT - 1) // '-1' for NONE action
        throw std::invalid_argument("repeated input keys");
    
    for (char input : inputs) {
        CInputRecorder::add_recordable_input(input);
    }
}
