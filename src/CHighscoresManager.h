#pragma once

#include "CUtilities.h"
#include "CHighscore.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>

/// @brief Class that manages highscores. Can load a file that contains highscores, display it and
///        register a new highscore.
class CHighscoresManager {
public:
    
    /// Loads highscores from file to their internal representation in the class.
    /// @param[in] pathToFile Path to the file that contains highscores.
    /// @return True or false whether the file was valid and could be loaded.
    ///         If the parsing of the file was not successful, no highscores are
    ///         internally registered.
    bool load(const std::string& pathToFile);
    
    /// Saves internal representation of loaded highscores to a file in a
    /// format that can be loaded by 'load()' method.
    /// @param[in] pathToFile Path to the file that we want to override so it contains
    ///                       the highscores stored in this class.
    /// @return Whether the writing to the file was successful.
    bool save(const std::string& pathToFile);
    
    /// Register a new highscore of a player to its internal representation of highscores.
    /// @param[in] playerName Name of the player we want to register.
    /// @param[in] timeInMillis Time in milliseconds that took the player to beat the level.
    bool register_score(const std::string& playerName, size_t timeInMillis);
    
    /// Operator used for formatted output to the stream.
    /// @param[in, out] stream Stream to write the formatted output to.
    /// @param[in] highscoresManager HighscoresManager that we want to print_stored_value out.
    friend std::ostream& operator<<(std::ostream& stream, const CHighscoresManager& highscoresManager);
private:
    
    /// Vector of sorted registered highscores. Adding to this vector should be
    /// done using 'register_highscore()' method to, since it keeps this vector sorted.
    std::vector<CHighscore> m_Highscores;
};
