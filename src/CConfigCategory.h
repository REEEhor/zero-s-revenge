#pragma once

#include "CConfigValueValidator.h"
#include "CParseError.h"
#include <string>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <iostream>
#include <set>

/// @brief Class for registering a data type that can be loaded from file
///        and assigned to some string key.
///        This class also stores the information whether the loaded value
///        is valid or not.
template<typename T>
class CConfigCategory {
public:
    
    /// Registers value that should be loaded at some point.
    /// @param[in] identifier String key of the value that we want to register.
    /// @param[in] validator Function that says, whether the loaded value is
    ///                      valid or not.
    /// @param[in] errorMessage String that corresponds to the %validator by
    ///                         saying which criteria of the loaded value was not met
    ///                         that makes the value invalid.
    /// @param[in] uniqueId Value that if set to a different number than 0 gets internally stored
    ///                     and all identifiers loaded with that number are checked for uniqueness
    ///                     (meaning all values with the same %uniqueId must be different by their operator!=).
    /// @throws std::invalid_argument if the identifier has already been registered.
    void register_value(const std::string& identifier,
                        std::function<bool(const T&)> validator = [](const T&) { return true; },
                        std::string errorMessage = "", int uniqueId = 0);
    
    /// Registers value that should be loaded at some point.
    /// @param[in] identifier String key of the value that we want to register.
    /// @param[in] validator Validator object that stores a function validating a value
    ///                      and error message describing which criteria the value breaks if
    ///                      it is considered invalid.
    /// @param[in] uniqueId Value that if set to a different number than 0 gets internally stored
    ///                     and all identifiers loaded with that number are checked for uniqueness
    ///                     (meaning all values with the same %uniqueId must be different by their operator!=).
    /// @throws std::invalid_argument if the identifier has already been registered.
    void register_value(const std::string& identifier, const CConfigValueValidator<T>& validator, int uniqueId = 0);
    
    /// Tries to load the value with identifier %identifier from stream and checks whether it is valid.
    /// @param[in] identifier String key of the value to try to load.
    /// @param[in, out] is Input stream to load the value from.
    /// @throws CParseError if the value could not be read from the stream.
    /// @throws std::invalid_argument if the value was loaded but is not valid.
    /// @throws std::invalid_argument if the identifier is not registered.
    /// @throws std::invalid_argument if a value with the identifier has already been loaded.
    /// @throws std::invalid_argument if the loaded value was registered to be unique but is not.
    void load_value(const std::string& identifier, std::istream& is);
    
    /// Tries to load the value with identifier %identifier directly from %value.
    /// @param[in] identifier String key of the value to try to load.
    /// @param[in] value Value that should be assigned to the %identifier key.
    /// @throws CParseError if the value could not be read from the stream.
    /// @throws std::invalid_argument if the value was loaded but is not valid.
    /// @throws std::invalid_argument if the identifier is not registered.
    /// @throws std::invalid_argument if a value with the identifier has already been loaded.
    /// @throws std::invalid_argument if the loaded value was registered to be unique but is not.
    void load_value(const std::string& identifier, const T& value);
    
    /// Looks up stored value by its identifier.
    /// @param[in] identifier Key of the value we want to look up.
    /// @return const reference to the looked up value.
    /// @throws std::invalid_argument if the identifier is not registered.
    /// @throws std::invalid_argument if the identifier has not been loaded yet.
    [[nodiscard]] const T& operator[](const std::string& identifier) const;
    
    /// Returns identifiers and their validators that have not been loaded yet.
    /// @return Map of identifiers and their validators that have not been loaded yet.
    const std::unordered_map<std::string, CConfigValueValidator<T>>& remaining_identifiers() const;

private:
    
    /// Checks whether an identifier has been registered.
    /// @param[in] identifier Identifier we want to see if it is registered.
    /// @return True if the identifier has been registered or false if not.
    [[nodiscard]] bool is_identifier_registered(const std::string& identifier) const;
    
    /// Checks whether an identifier been loaded and validated.
    /// @param[in] identifier Identifier of a value we want to see if it is loaded and validated.
    /// @return True if the identifier has been loaded and validated or false if not.
    [[nodiscard]] bool is_identifier_loaded(const std::string& identifier) const;
    
    /// Internal method that is called when a value is loaded but not stored and validated yet.
    /// @param[in] identifier Identifier of the value to validate and store.
    /// @param[in] value Value to validate and store.
    /// @throws std::invalid_argument if the identifier is not registered.
    /// @throws std::invalid_argument if the value is invalid.
    /// @throws std::invalid_argument if some value with the same identifier has already been stored.
    void validate_and_store(const std::string& identifier, const T& value);
    
    /// Internal method for checking if a value with %identifier can be loaded.
    /// @param[in] identifier Identifier that we want to check.
    /// @throws std::invalid_argument if identifier has not been registered.
    /// @throws std::invalid_argument if a value with that identifier has already been loaded and validated.
    void check_for_collisions(const std::string& identifier);
    
    /// Internal method that handles registering uniqueness of values.
    /// It assigns uniqueId to the identifier.
    /// @param[in] identifier Identifier that we want to assign the %uniqueId to.
    /// @param[in] uniqueId Number that if not set to zero gets assigned to identifier and
    ///                     can be looked up later by identifier.
    void register_unique(const std::string& identifier, int uniqueId);
    
    /// Looks up the %uniqueId of %identifier and checks whether %value is
    /// unique by the %uniqueId. If it is unique, it gets stored
    /// so its uniqueness can be compared against other values.
    /// The check is only done if the %uniqueId assigned to the identifier is nonzero.
    /// @param[in] identifier Identifier of the value that we want to check.
    /// @param[in] value That we want to check if it is valid.
    /// @return Whether the %value is unique or not when compared to already loaded values.
    [[nodiscard]] bool check_unique(const std::string& identifier, const T& value);
    
    /// Map of identifiers and their validators that should be loaded.
    /// When a identifier gets registered, it is stored here.
    /// When value gets loaded, the validator from this map gets removed.
    std::unordered_map<std::string, CConfigValueValidator<T>> m_ValuesToLoad;
    
    /// Map of identifiers and their values that have been successfully loaded and validated.
    std::unordered_map<std::string, T> m_LoadedValues;
    
    /// Map that assigns uniqueId to identifiers.
    std::unordered_map<std::string, int> m_GetUniqueId;
    
    /// Map that looks up sets of values by their uniqueId.
    /// The set container is useful since it is easy to check
    /// whether a new value is unique (by trying to put it into the set container).
    std::unordered_map<int, std::set<T>> m_SetsOfUniqueValues;
};

template<typename T>
bool CConfigCategory<T>::check_unique(const std::string& identifier, const T& value) {
    // Get identifier uniqueId.
    auto it = m_GetUniqueId.find(identifier);
    
    if (it == m_GetUniqueId.end())
        return true; // No uniqueId assigned to the identifier -> no need for unique check.
    
    // Try to store the value in the set of unique values set
    // and return whether the insert was successful.
    int uniqueId = it->second;
    return m_SetsOfUniqueValues[uniqueId].insert(value).second;
}

template<typename T>
void CConfigCategory<T>::register_unique(const std::string& identifier, int uniqueId) {
    if (uniqueId != 0) {
        m_GetUniqueId.insert({identifier, uniqueId});
    }
}

template<typename T>
void CConfigCategory<T>::register_value(const std::string& identifier,
                                        const CConfigValueValidator<T>& validator, int uniqueId) {
    using namespace std::string_literals;
    if (is_identifier_registered(identifier)) {
        throw std::invalid_argument("trying to register >"s + identifier + "< multiple times"s);
    }
    m_ValuesToLoad.emplace(identifier, validator);
    register_unique(identifier, uniqueId);
}

template<typename T>
const std::unordered_map<std::string, CConfigValueValidator<T>>& CConfigCategory<T>::remaining_identifiers() const {
    return m_ValuesToLoad;
}

template<typename T>
void CConfigCategory<T>::load_value(const std::string& identifier, const T& value) {
    check_for_collisions(identifier);
    validate_and_store(identifier, value);
}

template<typename T>
void CConfigCategory<T>::check_for_collisions(const std::string& identifier) {
    using namespace std::string_literals;
    if (!is_identifier_registered(identifier)) {
        throw std::invalid_argument("identifier >"s + identifier + "< is not registered"s);
    }
    if (is_identifier_loaded(identifier)) {
        throw std::invalid_argument("identifier >"s + identifier + "< has already been loaded"s);
    }
}

template<typename T>
void CConfigCategory<T>::validate_and_store(const std::string& identifier, const T& value) {
    using namespace std::string_literals;
    auto it = m_ValuesToLoad.find(identifier);
    auto& validator = it->second;
    if (!validator.m_Validator(value)) {
        throw std::invalid_argument("invalid value ("s + validator.m_ErrorMessage + ")"s);
    }
    
    if (!check_unique(identifier, value)) {
        throw std::invalid_argument("value is not unique but is registered to be");
    }
    m_ValuesToLoad.erase(it);
    m_LoadedValues.emplace(identifier, value);
}

template<typename T>
bool CConfigCategory<T>::is_identifier_loaded(const std::string& identifier) const {
    return m_LoadedValues.find(identifier) != m_LoadedValues.end();
}

template<typename T>
bool CConfigCategory<T>::is_identifier_registered(const std::string& identifier) const {
    return m_ValuesToLoad.find(identifier) != m_ValuesToLoad.end()
           || m_LoadedValues.find(identifier) != m_LoadedValues.end();
}

template<typename T>
void CConfigCategory<T>::register_value(const std::string& identifier,
                                        std::function<bool(const T&)> validator,
                                        std::string errorMessage, int uniqueId) {
    
    using namespace std::string_literals;
    if (is_identifier_registered(identifier)) {
        throw std::invalid_argument("trying to register >"s + identifier + "< multiple times"s);
    }
    m_ValuesToLoad.emplace(identifier, CConfigValueValidator<T>(validator, std::move(errorMessage)));
    register_unique(identifier, uniqueId);
}

template<typename T>
void CConfigCategory<T>::load_value(const std::string& identifier, std::istream& is) {
    check_for_collisions(identifier);
    
    using namespace std::string_literals;
    T value;
    std::string remainderCheck;
    std::string errorMessage = "could not parse text in quotes";
    if (!(is >> std::noskipws >> value)) {
        throw CParseError(errorMessage);
    }
    
    getline(is, remainderCheck);
    if (!remainderCheck.empty()) {
        throw CParseError(errorMessage);
    }
    
    validate_and_store(identifier, value);
}

template<typename T>
const T& CConfigCategory<T>::operator[](const std::string& identifier) const {
    using namespace std::string_literals;
    auto it = m_LoadedValues.find(identifier);
    if (it == m_LoadedValues.end()) {
        auto it2 = m_ValuesToLoad.find(identifier);
        if (it2 == m_ValuesToLoad.end())
            throw std::invalid_argument("value >"s + identifier + "< is not registered");
        else
            throw std::invalid_argument("value >"s + identifier + "< is not loaded");
    }
    return it->second;
}

