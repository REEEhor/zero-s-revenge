#include "CApplication.h"
#include "CHighscoresManager.h"

int main(int argc, char** args) {
    const std::string pathToConfig = (argc > 1 ? args[1] : "examples/default/default.cnfg");
    std::srand(time(nullptr));
    
    try {
        
        CApplication app(pathToConfig);
        app.run();
        
    } catch (std::invalid_argument& e) {
        std::cerr << "Error reading config file: ";
        CTerminal::print_in_color(e.what(), Color::RED, std::cerr);
        std::cerr << std::endl;
        
        return EXIT_FAILURE;
        
    } catch (std::exception& e) {
        CTerminal::reset_terminal();
        std::cerr << "Unexpected error occurred: ";
        CTerminal::print_in_color(e.what(), Color::RED, std::cerr);
        std::cerr << std::endl;
        CTerminal::non_blocking_input_off();
        
        return EXIT_FAILURE;
    }
    
    
    return EXIT_SUCCESS;
    
    
}