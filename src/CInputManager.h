#pragma once

#include <list>
#include <memory>
#include "CInputRecorder.h"
#include "CTerminal.h"

/// @brief Class for getting input from keyboard. Recorded keys are then sent to
///        instances of CInputRecorder that decide, if they want to store that input or not.
///        It is helpful to have multiple CInputRecorders - for instance deviding keyboard input
///        into player controls and ui controls (pause or quit).
class CInputManager {
public:
    
    /// Constructor of CInputManager.
    /// @param [in] recorderList List of pointers of recorders that should receive updates
    ///                          from this CInputManager.
    CInputManager(std::initializer_list<std::shared_ptr<CInputRecorder>> recorderList);
    
    /// Gets input from keyboard and distributes it into managed CInputRecorders.
    void update();
private:
    
    /// List of recorders that should receive updates about keyboard input.
    std::list<std::shared_ptr<CInputRecorder>> m_ManagedRecorders;
};
