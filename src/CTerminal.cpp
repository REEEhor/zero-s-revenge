#include "CTerminal.h"

bool CTerminal::is_output_to_terminal() {
    return isatty(STDOUT_FILENO);
}

void CTerminal::reset_terminal() {
    non_blocking_input_off();
    std::cout << reset_graphics()
              << erase_entire_screen()
              << move_cursor_to(0, 0)
              << show_cursor()
              << std::flush;
}

std::string CTerminal::reset_graphics() {
    return ansi_command("0m");
}

void CTerminal::non_blocking_input_on() {
    
    // Source: https://gitlab.fit.cvut.cz/matouj10/pa2-2022-lab/-/tree/master/sw-tips/21-non-blocking-input.
    
    // Get terminal settings and turn off echo and wait-for-enter (ICANON).
    termios settings;
    tcgetattr(STDOUT_FILENO, &settings);
    
    settings.c_lflag &= ~(ECHO | ICANON);
    settings.c_cc[VMIN] = 0;
    settings.c_cc[VTIME] = 0;
    tcsetattr(STDOUT_FILENO, TCSANOW, &settings);
}

void CTerminal::non_blocking_input_off() {
    
    // Get terminal settings and turn on echo and wait-for-enter (ICANON).
    termios settings;
    tcgetattr(STDOUT_FILENO, &settings);
    settings.c_lflag |= (ECHO | ICANON);
    tcsetattr(STDOUT_FILENO, TCSANOW, &settings);
}

std::string CTerminal::move_cursor_to(int x, int y) {
    std::ostringstream oss;
    oss << (y + 1) << ";" << (x + 1) << "H";
    return ansi_command(oss.str());
}

std::string CTerminal::hide_cursor() {
    return ansi_command("?25l");
}

std::string CTerminal::show_cursor() {
    return ansi_command("?25h");
}

std::string CTerminal::erase_entire_screen() {
    return ansi_command("2J");
}

std::string CTerminal::ansi_command(const std::string& command) {
    std::ostringstream oss;
    oss << ESCAPE << command;
    return oss.str();
}

std::string CTerminal::set_color(Color::EColor color) {
    std::ostringstream oss;
    oss << color << "m";
    return ansi_command(oss.str());
}

char CTerminal::get_non_blocking_input() {
    char result = no_input();
    // Read one character from standard input using read()
    // since normal methods (like operator>>) do not work.
    ssize_t tmp = read(fileno(stdin), &result, 1);
    
    // read() returns a value. This way we do not get a warning
    // for unused variable.
    static_cast<void> (tmp);
    return result;
}

void CTerminal::game_mode_on() {
    std::cout << hide_cursor()
              << set_color(Color::DEFAULT)
              << erase_entire_screen();
    non_blocking_input_on();
}

std::string CTerminal::set_background_color(Color::EColor color) {
    std::ostringstream oss;
    // To get the background code from the color code
    // we just need to add 10 to it.
    oss << (static_cast<int>(color) + 10) << "m";
    return ansi_command(oss.str());
}

std::string CTerminal::move_cursor_to(const CPosition& position) {
    return move_cursor_to(position.m_X * 2, position.m_Y);
}

char CTerminal::no_input() {
    return '\0';
}

void CTerminal::wait_for_terminal_size(int width, int height) {
    winsize size{};
    
    // Get terminal size and check its dimensions.
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    bool wasSmall = false;
    if (width > size.ws_col || height > size.ws_row) {
        wasSmall = true;
        std::cout << erase_entire_screen()
                  << move_cursor_to(0, 0)
                  << "Please make your terminal bigger (smallest possible size: "
                  << width << " x " << height
                  << ")" << std::flush;
    }
    while (width > size.ws_col || height > size.ws_row) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    }
    
    if (wasSmall) {
        // The resizing can mess up rendering of characters in the terminal.
        // This is here to try to prevent that.
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void CTerminal::print_in_color(const std::string& str, Color::EColor color, std::ostream& stream) {
    stream << set_color(color) << str << reset_graphics();
}


