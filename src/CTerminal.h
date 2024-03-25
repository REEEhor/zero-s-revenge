#pragma once


#include <termios.h>
#include <thread>
#include <sys/ioctl.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include "EColor.h"
#include "CPosition.h"

/// @brief Static class containing helper methods for terminal (setting colors, no echo, ...)
/// @author Almost every method here was taken from Jan Matoušek sw-tips:
///         Non blocking input/echo:
///         https://gitlab.fit.cvut.cz/matouj10/pa2-2022-lab/-/tree/master/sw-tips/21-non-blocking-input.
///         Colors in terminal:
///         https://gitlab.fit.cvut.cz/matouj10/pa2-2022-lab/-/tree/master/sw-tips/22-colors-etc.
class CTerminal {
public:
    /// This class is static so the constructor is deleted.
    CTerminal() = delete;
    
    /// Sets the the terminal into 'game_mode'.
    /// Meaning it clears the terminal and sets non blocking input on
    /// for continuous keyboard input.
    static void game_mode_on();
    
    /// Turns on non-blocking input.
    /// Meaning no echo and no waiting for enter.
    static void non_blocking_input_on();
    
    /// Turns on echo and waiting for enter.
    static void non_blocking_input_off();
    
    /// Resets everything in the terminal.
    /// Meaning setting echo and waiting for enter on.
    /// Also clears terminal and moves cursor to the basic position.
    static void reset_terminal();
    
    /// Checks whether the input of the program is stdin,
    /// since it is necessary for the game to work properly.
    static bool is_output_to_terminal();
    
    /// Returns a character read from stdin when the non blocking input is on.
    static char get_non_blocking_input();
    
    /// Returns character that is returned by 'get_non_blocking_input()' when
    /// no key has been pressed.
    static char no_input();
    
    /// Checks the size of the terminal size and if it is smaller then required
    /// this method acts as a little subprogram that waits for the user to
    /// make the terminal bigger while displaying a simple prompt.
    /// @param[in] width Minimal width of the terminal required.
    /// @param[in] height Minimal height of the terminal required.
    static void wait_for_terminal_size(int width, int height);
    
    /// Prints to an output stream a string in color and then resetting the formatting of the stream.
    /// @param[in] str String to print_stored_value to the stream.
    /// @param[in] color Color that the string should be printed in.
    /// @param[in] stream Stream that the string should be printed to.
    static void print_in_color(const std::string& str, Color::EColor color, std::ostream& stream);
    
    /// Moves the cursor to a certain position using ANSI code.
    /// @param x X Coordinate of position we want to move the cursor to.
    /// @param y Y Coordinate of position we want to move the cursor to.
    /// @return String that when sent to an output stream moves the cursor.
    [[nodiscard]] static std::string move_cursor_to(int x, int y);
    
    /// Moves the cursor to a certain CPosition using ANSI code.
    /// @param position Position that we want to move the cursor to.
    ///                 Note that the position is interpreted as 'in game coordinate'
    ///                 which are two characters wide. This method is supposed to be used
    ///                 when rendering objects in the game.
    /// @return String that when sent to an output stream moves the cursor.
    [[nodiscard]] static std::string move_cursor_to(const CPosition& position);
    
    /// Erases the entire screen using ANSI code.
    /// @return String that when sent to an output stream erases the terminal.
    [[nodiscard]] static std::string erase_entire_screen();
    
    /// Hides cursor in the terminal using ANSI code.
    /// @return String that when sent to an output stream hides the cursor.
    [[nodiscard]] static std::string hide_cursor();
    
    /// Shows cursor in the terminal using ANSI code.
    /// @return String that when sent to an output stream shows the cursor.
    [[nodiscard]] static std::string show_cursor();
    
    /// Resets all formatting (colors, boldness, ...) of the terminal using ANSI code.
    /// @return String that when sent to an output stream resets formatting.
    [[nodiscard]] static std::string reset_graphics();
    
    /// Can be used to set the color of characters in the terminal using ANSI code.
    /// @param[in] color Instance of enum EColor - color that should be set.
    /// @return String that when sent to an output stream changes the color of the characters
    ///         sent to the stream later.
    [[nodiscard]] static std::string set_color(Color::EColor color);
    
    /// Can be used to set the color of background in the terminal using ANSI code.
    /// @param[in] color Instance of enum EColor - color that should be set.
    /// @return String that when sent to an output stream changes the color of the background
    ///         of characters set to the stream later.
    [[nodiscard]] static std::string set_background_color(Color::EColor color);
private:
    
    /// Helper method for creating a general ANSI code.
    /// @param[in] command The code of the ANSI command (without the escape symbol and '['
    ///                    - that is added by this method).
    static std::string ansi_command(const std::string& command);
    
    /// Const variable for the escape code - escape + char '['.
    constexpr static char ESCAPE[] = "\033[";
};
