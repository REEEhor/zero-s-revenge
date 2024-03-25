#pragma once

#include <unordered_set>
#include <vector>
#include <memory>

/// @brief Stores inputs from keyboard by having a set o available keys,
///        that this class considers to be pressed (other keys get ignored).
///        This class is then managed by CInputManager, that has a pointer
///        to an instance of this class and puts recorded keys into it.
class CInputRecorder {
public:
    
    /// CInputRecorder default constructor.
    CInputRecorder();
    
    /// Virtual destructor since CActionsInputRecorder inherits from this class
    /// and is used polymorphically.
    virtual ~CInputRecorder();
    
    /// Constructor with list of inputs that this instance should register
    CInputRecorder(std::initializer_list<char> recordableInputs);
    
    /// Registers one input. This method is mostly used by CInputManager
    /// @param[in] input Key that was pressed. The key is checked first if
    ///                  it is in set of recordable inputs and then added.
    void record_input(char input);
    
    /// Add one key that this class should register.
    /// @param[in] newInput Key that we want to detect.
    CInputRecorder& add_recordable_input(char newInput);
    
    /// @return Vector of pressed keys that are registered.
    ///         Internal vector of stored pressed keys is then emptied.
    std::vector<char> pop_recorded_inputs();
private:
    /// Vector of inputs that have been recorded by this instance.
    std::vector<char> m_RecordedInputs;
    /// Set of keys that this instance should register.
    std::unordered_set<char> m_RecordableInputs;
};
