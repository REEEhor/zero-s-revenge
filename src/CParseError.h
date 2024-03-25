#pragma once

#include <stdexcept>

/// @brief Class extending std::invalid_argument for
///        describing that a value could not be properly read from the file
class CParseError : public std::invalid_argument {
public:
    explicit CParseError(const std::string& arg);
};
