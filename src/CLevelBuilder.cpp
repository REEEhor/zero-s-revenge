#include "CLevelBuilder.h"

CLevelBuilder::CLevelBuilder(const std::shared_ptr<const CConfig>& config,
                             const std::shared_ptr<const CEntityFactory>& factory)
        : m_Config(config), m_Factory(factory) {}

void CLevelBuilder::load_level(const std::string& levelFilePath, CWavesManager& wavesManager,
                               std::shared_ptr<CMap>& environment, CPosition& playerPosition,
                               CPosition& dimensions) const {
    // Try opening file as std::ifstream.
    std::ifstream file(levelFilePath);
    if (!file) {
        throw std::invalid_argument("could not open level");
    }
    
    // Load static contents of the level.
    load_environment(file, wavesManager, environment, playerPosition, dimensions);
    
    // Load enemy waves in the level.
    wavesManager.load(file, *m_Config, m_Factory);
}

void
CLevelBuilder::load_environment(std::istream& stream, CWavesManager& wavesManager, std::shared_ptr<CMap>& environment,
                                CPosition& playerPosition, CPosition& dimensions) const {
    int numberOfPlayerStartingPositions = 0;
    // Get a map of functions that should be called when a given character is found in the level.
    auto actionsRepresentedBySymbol =
            generate_functions(wavesManager, environment, playerPosition, numberOfPlayerStartingPositions);
    
    std::string line;
    int y = 0; // Y position of character being interpreted and loaded.
    
    // Load file by lines and try to interpret each character.
    while (std::getline(stream, line)
           && line != m_Config->m_String["START_OF_WAVES_SEPARATOR"]) {
        
        int x = 0; // X position of character being interpreted and loaded.
        for (char c: line) {
            if (std::isspace(c)) { // Ignore whitespace characters
                x++;
                continue;
            }
            
            try {
                // Update the representation of the level by calling
                // a function at the corresponding character.
                actionsRepresentedBySymbol.at(c)(CPosition(x, y));
            } catch (std::out_of_range& e) {
                using namespace std::string_literals;
                throw std::invalid_argument("invalid symbol >"s + c + "< "s);
            }
            
            x++;
        }
        y++;
        
        if (x > dimensions.m_X) {
            dimensions.m_X = x;
        }
        if (y > dimensions.m_Y) {
            dimensions.m_Y = y;
        }
    }
    
    if (!wavesManager.is_valid()) {
        throw std::invalid_argument("level has invalid spawn positions of enemies");
    }
    
    if (numberOfPlayerStartingPositions != 1) {
        throw std::invalid_argument("level has invalid number of player starting positions");
    }
}

std::unordered_map<char, std::function<void(const CPosition&)>>
CLevelBuilder::generate_functions(CWavesManager& wavesManager, std::shared_ptr<CMap>& environment,
                                  CPosition& playerPosition, int& numberOfPlayerStartingPositions) const {
    // Generate a map where the key is a character that can be found in a level configuration
    // and the values in the map are functions that are the representation of the character.
    
    return {
            {m_Config->m_Char["ENEMY_SPAWNER"],            [&](const CPosition& position) {
                wavesManager.register_spawn_position(position);
            }},
            
            {m_Config->m_Char["PLAYER_STARTING_POSITION"], [&](const CPosition& position) {
                playerPosition = position;
                numberOfPlayerStartingPositions++;
            }},
            
            {m_Config->m_Char["BOX_LEVEL_SYMBOL"],         [&](const CPosition& position) {
                environment->add_object(m_Factory->create_box(position));
            }},
            
            {m_Config->m_Char["WALL_LEVEL_SYMBOL"],        [&](const CPosition& position) {
                environment->add_object(m_Factory->create_wall(position));
            }},
            
            {m_Config->m_Char["IND_WALL_LEVEL_SYMBOL"],    [&](const CPosition& position) {
                environment->add_object(m_Factory->create_indestructible_wall(position));
            }}
    };
}



