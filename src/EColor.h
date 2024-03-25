#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

/// @brief Enum of colors that can be rendered into the terminal.
namespace Color {
    enum EColor {
        BLACK = 30,
        RED = 31,
        GREEN = 32,
        YELLOW = 33,
        BLUE = 34,
        MAGENTA = 35,
        CYAN = 36,
        WHITE = 37,
        DEFAULT = 39,
    };
}

/// Accepts uppercase string of one of the values in enum
/// Also accepts dash "-" - meaning BLACK color
std::istream& operator>>(std::istream& is, Color::EColor& color);