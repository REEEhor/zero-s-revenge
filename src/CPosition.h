#pragma once

#include "EDirection.h"
#include <tuple>
#include <cmath>

/// @brief Class representing coordinates of objects in the game.
class CPosition {
public:
    
    /// X coordinate.
    int m_X;
    
    /// Y coordinate.
    int m_Y;
    
    /// Constructor of CPosition.
    /// @param[in] x Coordinate X of the CPosition.
    /// @param[in] y Coordinate Y of the CPosition.
    explicit CPosition(int x = 0, int y = 0);
    
    /// Operator == comparing both coordinates of CPosition.
    /// @param[in] other Rhs of comparison.
    /// @return True if both coordinates of CPositions match.
    ///         Otherwise false.
    bool operator==(const CPosition& other) const;
    
    /// Operator != comparing both coordinates of CPosition.
    /// @param[in] other Rhs of comparison.
    /// @return True if the CPositions differ in at least one coordinate.
    ///         It they match, false is returned.
    bool operator!=(const CPosition& other) const;
    
    /// Operator < comparing both coordinates of CPosition.
    /// This implements total ordering on the CPosition and is used in
    /// ordered containers for lookup.
    /// @param[in] other Rhs of comparison.
    /// @return Bool whether '*this' is smaller that other.
    ///         The comparison is firstly done using the X coordinate
    ///         and then Y.
    bool operator<(const CPosition& other) const;
    
    /// Operator += for 'moving' the CPosition in a direction.
    /// See 'CPosition operator+(Direction::EDirection direction)' for more info.
    /// @param[in] direction Direction to add to the CPosition.
    /// @return Reference to *this changed by %direction.
    CPosition& operator+=(Direction::EDirection direction);
    
    /// Operator + for 'moving' the CPosition in a direction.
    /// Depending on the %direction, one of the coordinates can
    /// be decreased / increased by one.
    /// @example CPos[4,-3] + UP = CPos[4,-2]
    /// @param[in] direction Direction to add to the CPosition.
    /// @return A copy of *this that is changed by %direction.
    CPosition operator+(Direction::EDirection direction) const;
    
    /// Since ale game objects only move strictly horizontally or diagonally,
    /// it is often useful to calculate manhattan distance between them.
    /// @param[in] lhs Lhs of the function.
    /// @param[in] rhs Rhs of the function.
    /// @return Manhattan distance between lhs and rhs, which is
    ///         sum of the absolute values of differences of their individual coordinates.
    friend int manhattan_distance(const CPosition& lhs, const CPosition& rhs);
};
