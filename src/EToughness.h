#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

/// @brief Enum for representing how the enemies are difficult to beat.
///        This is also used to determine how good bonuses should the
///        enemies drop when killed.
namespace Toughness {
    enum EToughness {
        NONE, LOW, MIDDLE, HIGH
    };
}

/// Accepts uppercase string of one of the values in enum
std::istream& operator>>(std::istream& is, Toughness::EToughness& toughness);


