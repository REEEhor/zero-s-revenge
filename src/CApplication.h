#pragma once

#include "CHighscoresManager.h"
#include "CConfigRegister.h"
#include "CGame.h"
#include <filesystem>

/// @brief Class that implements the main program flow.
class CApplication {
public:
    /// Constructor of CApplication.
    /// @param pathToConfig Path to file that contains all application parameters.
    /// @throws std::invalid_argument When path to config is invalid or the file could not be opened.
    explicit CApplication(const std::string& pathToConfig);
    
    /// Runs application.
    /// @throw std::runtime_error When unexpected error occurs. For example standard input is closed by eof.
    void run();
    
    /// Copying this class is prohibited.
    CApplication(const CApplication& other) = delete;
    
    /// Copying this class is prohibited.
    CApplication& operator=(const CApplication& other) = delete;

private:
    
    /// Method that acts as a simple menu for the player (pick a level to play or exit the program).
    /// @param[out] exit Bool that is set to true, if player decides to exit the program, otherwise it is set to false.
    /// @param[out] pathToLevel String that will contain path to the level that player decided to play.
    ///                         If player decided to exit the program, the string does not get effected.
    void main_menu(bool& exit, std::string& pathToLevel);
    
    /// Static method used to erase terminal and set the cursor to 0,0 position.
    /// It is used when going between different parts of the running program.
    static void new_page();
    
    /// @return All strings in class that are considered to be a path to a level.
    ///         No parsing of the level is done, the only thing that gets check is the correct file extension
    ///         and if the path is to a file and not a directory.
    [[nodiscard]] std::vector<std::string> get_level_paths_in_directory(const std::string& pathToDirectory) const;
    
    /// Static method for printing formatted option in a list.
    /// @param[in] id Index of the option.
    /// @param[in] option Text of the option.
    static void print_option(int id, const std::string& option);
    
    /// Method that acts as a subprogram where player can see level highscores and save his own.
    /// Scores are in the form of time - the player that beat the level faster is considered better.
    /// @param level Path to the level that player just played.
    /// @param milliseconds Time that player needed for beating the level.
    void register_new_score(const std::string& level, size_t milliseconds);
    
    /// Static method that check if the stream has not been closed by eof since this breaks the rest of the application.
    /// @param stream Stream to check.
    /// @throws std::runtime_error Saying that stream has been closed by eof.
    static void validate_stream(const std::istream& stream);
    
    /// Static method that waits for player to press enter.
    /// It also displays a little prompt informing the player about this.
    static void wait_for_enter();
    
    /// Pointer to configuration of this application.
    std::shared_ptr<CConfig> m_Config;
};
