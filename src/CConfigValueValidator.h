#pragma once

#include <functional>
#include <string>
#include <utility>

/// @brief Class for storing a validator function of some data type and
///        error message that should be displayed when this validator returns false
///        (meaning the value of the data type is invalid in some way).
template<typename T>
class CConfigValueValidator {
public:
    
    /// Constructor of CConfigValueValidator.
    /// @param[in] validator Function that determines if a const reference to the templated
    ///                      value is valid or not by returning true or false
    ///                      (true = value is valid, false = value is invalid).
    /// @param[in] errorMessage String that should somehow correspond to the validator function,
    ///                         telling which criteria has been broken that makes the value invalid.
    CConfigValueValidator(std::function<bool(const T&)> validator, std::string errorMessage)
            : m_Validator(validator), m_ErrorMessage(std::move(errorMessage)) {}
    
    /// Validator function - determines the validity of a templated data type.
    std::function<bool(const T&)> m_Validator;
    
    /// String that should somehow correspond to the validator function,
    /// telling which criteria has been broken that makes the value invalid.
    std::string m_ErrorMessage;
};
