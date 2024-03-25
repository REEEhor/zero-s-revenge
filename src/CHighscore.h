#pragma once

#include <string>
#include <tuple>

/// @brief Small class that contains statistics about a highscore (name of the player and his/her score).
class CHighscore {
public:
    
    /// Constructor of CHighscore.
    /// @param[in] playerName Name of the player that this highscore belongs to.
    /// @param[in] timeInMillis Number of milliseconds that took the player to beat the level.
    CHighscore(std::string playerName, size_t timeInMillis);
    
    /// Operator implementing total ordering on CHighscore.
    /// It compares highscores by time and then by name, this is
    /// used to make canonical lists of highscores.
    /// @param[in] other Rhs of the comparison.
    bool operator<(const CHighscore& other) const;
    
    /// Name of the player that this highscore belongs to.
    std::string m_PlayerName;
    
    /// Number of milliseconds that took the player to beat the level.
    size_t m_TimeInMilliseconds;
};
