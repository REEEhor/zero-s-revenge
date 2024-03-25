#pragma once

#include "EAction.h"
#include "EDirection.h"
#include "EHOrientation.h"
#include "EVOrientation.h"
#include <unordered_map>
#include <string>
#include <iomanip>
#include <sstream>

/// @brief Static class with small helper methods.
class CUtilities {
public:
    /// This is a static class so its constructor is deleted.
    CUtilities() = delete;
    
    /// Gets an action that means moving in %direction.
    /// @param[in] direction Direction that should be converted into corresponding action.
    /// @return Action converted from the direction.
    static Action::EAction action_from_direction(Direction::EDirection direction);
    
    /// Gets a direction if the %action is a movement in some direction.
    /// @param[in] action Action that should be converted into a direction.
    /// @return Action converted from the direction.
    static Direction::EDirection direction_from_action(Action::EAction action);
    
    /// Gets a direction from vertical and horizontal orientations.
    /// @param[in] vOrientation Vertical orientation that should be used for conversion.
    /// @param[in] hOrientation Horizontal orientation that should be used for conversion.
    /// @return Direction converted from the vertical and horizontal orientation.
    static Direction::EDirection direction_from_vh_orientations(VOrientation::EVOrientation vOrientation,
                                                                HOrientation::EHOrientation hOrientation);
    
    /// Gets the index that the action corresponds to.
    /// @param[in] action Action that might corresponds to selecting a gun.
    /// @return Index of the gun the action selects.
    ///         If the action is not a selection of a gun, 0 gets returned.
    static int get_nth_gun_from_action(Action::EAction action);
    
    /// Converts milliseconds to string where the milliseconds are
    /// shown as minutes, seconds a thousands of a second.
    /// @param[in] millis Milliseconds that should be converted.
    /// @return Formatted string that displays milliseconds as minutes, seconds
    ///         and thousands of a second.
    static std::string millis_to_minutes_and_seconds(size_t millis);
    
    /// Template method that checks if a number is in a given range using its 'operator<=()'.
    /// @param[in] value Value that ve want to check if it is in the given range.
    /// @param[in] min Minimal viable value that the %value can be.
    /// @param[in] max Maximal viable value that the %value can be.
    /// @return Whether the %value is same or higher than %min and
    ///         same or lower than %max.
    template<typename T>
    static bool is_in_range(const T& value, const T& min, const T& max);
    
    /// Caps the value to a given maximum.
    /// @param[out] value Value to be capped.
    /// @param[in] max The value the %value should be set to if it gets bigger than it.
    template<typename T>
    static void cap_value_max(T& value, const T& max);
    
    /// Caps the value to a given minimum.
    /// @param[out] value Value to be capped.
    /// @param[in] min The value the %value should be set to if it gets lower than it.
    template<typename T>
    static void cap_value_min(T& value, const T& min);
    
    /// Caps value in a given range.
    /// @param[out] value Value to be capped.
    /// @param[in] min The value the %value should be set to if it gets lower than it.
    /// @param[in] max The value the %value should be set to if it gets bigger than it.
    template<typename T>
    static void cap_value(T& value, const T& min, const T& max);
    
    /// @return a random direction.
    static Direction::EDirection random_direction();

private:
    /// A map for converting from direction to action.
    static std::unordered_map<Direction::EDirection, Action::EAction> m_ActionFromDirection;
    
    /// A map for converting from action to direction.
    static std::unordered_map<Action::EAction, Direction::EDirection> m_DirectionFromAction;
};

template<typename T>
void CUtilities::cap_value_max(T& value, const T& max) {
    if (value > max)
        value = max;
}

template<typename T>
void CUtilities::cap_value_min(T& value, const T& min) {
    if (value < min)
        value = min;
}

template<typename T>
void CUtilities::cap_value(T& value, const T& min, const T& max) {
    if (value < min) {
        value = min;
    } else if (value > max) {
        value = max;
    }
}

template<typename T>
bool CUtilities::is_in_range(const T& value, const T& min, const T& max) {
    return (min <= value && value <= max);
}

