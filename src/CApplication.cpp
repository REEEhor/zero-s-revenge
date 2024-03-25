#include "CApplication.h"

CApplication::CApplication(const std::string& pathToConfig)
// Setup config with all variables that necessary to run this application.
        : m_Config(CConfigRegister::get_config_with_registered_values()) {
    
    // Load configuration from a file and check if it was loaded correctly.
    m_Config->load_values(pathToConfig);
    std::ostringstream error;
    if (!m_Config->are_all_identifiers_loaded(error)) {
        throw std::invalid_argument(error.str());
    }
}

void CApplication::run() {
    // Application cannot run correctly if output of the program is not a terminal.
    if (!CTerminal::is_output_to_terminal()) {
        throw std::runtime_error("output of the game is not to a terminal!");
    }
    
    // Main loop of the application
    while (true) {
        CGame game(m_Config);
        
        bool exit;
        std::string level;
        main_menu(exit, level);
        if (exit) {
            new_page();
            return;
        }
        
        // Try running the selected level
        try {
            auto startTime = std::chrono::steady_clock::now();
            bool success = game.run(level); // success is set to true if player has beaten the level
            auto endTime = std::chrono::steady_clock::now();
            
            if (success) {
                size_t milliseconds =
                        std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
                register_new_score(level, milliseconds);
            } else {
                new_page();
                std::cout << "You did not survive :(" << std::endl;
                wait_for_enter();
            }
            
        } catch (std::invalid_argument& e) {
            new_page();
            std::cout << "Sorry, this level cannot be loaded (" << e.what() << ")" << std::endl;
            wait_for_enter();
        }
    }
}

void CApplication::register_new_score(const std::string& level, size_t milliseconds) {
    const std::string SCORES_FILE = level + "." + m_Config->m_String["HIGH_SCORES_FILE_EXTENSION"];
    CHighscoresManager highscoresManager;
    new_page();
    
    // Print info to player about state of the application.
    CTerminal::print_in_color("YOU WON!\n", Color::GREEN, std::cout);
    std::cout << "Your time: ";
    CTerminal::print_in_color(CUtilities::millis_to_minutes_and_seconds(milliseconds) + "\n", Color::GREEN, std::cout);
    
    // Try to load highscores.
    if (!highscoresManager.load(SCORES_FILE)) {
        std::cout << "No records of highscores (file does not exists or is corrupted)" << std::endl;
    } else {
        // Highscores loaded properly -> show them to the player.
        std::cout << "Recorded highscores:" << std::endl
                  << highscoresManager << std::endl;
    }
    
    // Wait for player to type their name, so it could be registered in highscores.
    std::cout << "Enter your player name (spaces will be skipped): " << std::endl;
    std::string name;
    while (true) {
        std::cout << "> " << std::flush;
        std::string tmp;
        std::getline(std::cin, tmp);
        std::istringstream stream(tmp);
        stream >> name;
        validate_stream(std::cin);
        
        // Break if player has entered a name that is valid and can be registered.
        if (!name.empty() && highscoresManager.register_score(name, milliseconds)) {
            break;
        }
        
        std::cout << "Please enter a valid name :)" << std::endl;
    }
    
    // Show player updated highscores.
    if (!highscoresManager.save(SCORES_FILE)) {
        new_page();
        std::cout << "Could not save highscore" << std::endl;
    } else {
        highscoresManager.load(SCORES_FILE);
        new_page();
        std::cout << "Updated scores:" << std::endl;
        std::cout << highscoresManager << std::endl;
    }
    
    wait_for_enter();
}

void CApplication::main_menu(bool& exit, std::string& pathToLevel) {
    using namespace std::string_literals;
    std::vector<std::string> levels = get_level_paths_in_directory(m_Config->m_String["PATH_TO_LEVEL_DIRECTORY"]);
    
    // Inform player about the state of the program and the options he/she has.
    new_page();
    std::cout << "Select level to play or quit game: " << std::endl;
    
    // Print options.
    int i = 1;
    print_option(i++, "Quit game");
    for (const auto& level: levels) {
        print_option(i++, "Play level: "s + level);
    }
    
    // Wait for player to enter a valid option.
    size_t answer = levels.size() + 2;
    while (true) {
        // Read a line and try to parse into an answer.
        std::cout << "> " << std::flush;
        std::string tmp;
        std::getline(std::cin, tmp);
        std::istringstream stream(tmp);
        stream >> answer;
        validate_stream(std::cin);
        
        // Break if player has entered a valid option.
        if (CUtilities::is_in_range(answer, 1UL, levels.size() + 1)) {
            break;
        }
        std::cout << "Please enter a valid number :)" << std::endl;
    }
    
    if (answer == 1) {
        exit = true;
        return;
    }
    
    pathToLevel = levels[answer - 2];
    exit = false;
}

std::vector<std::string> CApplication::get_level_paths_in_directory(const std::string& pathToDirectory) const {
    using namespace std::filesystem;
    // Directory that can contain advanced.
    const std::filesystem::path directory(pathToDirectory);
    std::vector<std::string> pathsToLevels;
    
    // Validate directory.
    using namespace std::string_literals;
    if (!std::filesystem::is_directory(directory)) {
        throw std::invalid_argument("entered path to advanced ("s + directory.string() + ") is not a directory"s);
    }
    
    // Check if file could be a level - file extension must match and
    // the file has to be std::regular_file.
    std::string levelExtension = "."s + m_Config->m_String["LEVEL_FILE_EXTENSION"];
    for (auto& file: directory_iterator(directory)) {
        std::string fileExtension = file.path().extension().string();
        if (fileExtension == levelExtension && file.is_regular_file()) {
            
            // Path can be a valid level => add it to the result vector.
            pathsToLevels.emplace_back(file.path().string());
        }
    }
    
    return pathsToLevels;
}

void CApplication::print_option(int id, const std::string& option) {
    std::ostringstream stream;
    stream << " [" << id << "] " << option << std::endl;
    CTerminal::print_in_color(stream.str(), Color::GREEN, std::cout);
}

void CApplication::new_page() {
    std::cout << CTerminal::erase_entire_screen() << CTerminal::move_cursor_to(0, 0) << std::flush;
}

void CApplication::validate_stream(const std::istream& stream) {
    if (stream.eof()) {
        throw std::runtime_error("stream used for input has been closed by eof");
    }
}

void CApplication::wait_for_enter() {
    CTerminal::print_in_color(" Press [enter] to continue", Color::GREEN, std::cout);
    std::string tmp;
    getline(std::cin, tmp);
    validate_stream(std::cin);
}



