#pragma once

#include "EAction.h"
#include "CInputRecorder.h"
#include <vector>
#include <stdexcept>
#include <unordered_map>

/// @brief This class extends from CInputRecorder by returning
/// instances of enum EAction that is then used later by CPlayer.
class CActionsInputRecorder : public CInputRecorder {
public:
    
    /// Constructor that registers keys for individual actions.
    ///@param[in] up        Key that we want to register as MOVE_UP.
    ///@param[in] down      Key that we want to register as MOVE_DOWN.
    ///@param[in] left      Key that we want to register as MOVE_LEFT.
    ///@param[in] right     Key that we want to register as MOVE_RIGHT.
    ///@param[in] shoot     Key that we want to register as ATTACK.
    ///@param[in] firstGun  Key that we want to register as SELECT_FIRST_GUN.
    ///@param[in] secondGun Key that we want to register as SELECT_SECOND_GUN.
    ///@param[in] thirdGun  Key that we want to register as SELECT_THIRD_GUN.
    CActionsInputRecorder(char up, char down, char left, char right, char shoot, char firstGun,
                          char secondGun, char thirdGun, char fourthGun, char fifthGun,
                          char sixthGun, char seventhGun, char eightGun, char ninthGun);
    /// Returns vector of actions that corresponds to keys entered in constructor.
    std::vector<Action::EAction> pop_actions();
private:
    /// Map for converting between inputted keys and actions.
    std::unordered_map<char, Action::EAction> m_ActionsMap;
};
