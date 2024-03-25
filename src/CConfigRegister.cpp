#include "CConfigRegister.h"

std::shared_ptr<CConfig> CConfigRegister::get_config_with_registered_values() {
    auto config = std::make_shared<CConfig>();
    int uniqueId = 0;
    
    register_level_loading(config, uniqueId);
    register_static_objects(config, uniqueId);
    register_player(config, uniqueId);
    register_inputs(config, uniqueId);
    register_enemies(config, uniqueId);
    register_guns(config, uniqueId);
    register_ui(config, uniqueId);
    register_bonuses(config, uniqueId);
    register_misc(config, uniqueId);
    
    return config;
}

const CConfigValueValidator<int> CConfigRegister::POSITIVE_INT
        ([](int val) { return val > 0; }, "non-positive value");

const CConfigValueValidator<int> CConfigRegister::PROBABILITY
        ([](int val) { return CUtilities::is_in_range(val, 0, 100); }, "value must be a percentage in <0,100>");

const CConfigValueValidator<int> CConfigRegister::NON_NEGATIVE_INT
        ([](int val) { return val >= 0; }, "cannot be negative");

const CConfigValueValidator<std::string> CConfigRegister::BULLET_VISUALS
        ([](const std::string& str) { return str.size() == 4; },
         "bullet visuals need 4 characters");

const CConfigValueValidator<int> CConfigRegister::NUM_OF_SPRITES
        ([](int val) { return val == 1 || val == 2 || val == 3 || val == 6; }, "invalid number of sprites");

const CConfigValueValidator<char> CConfigRegister::ALWAYS_CORRECT
        ([](char) { return true; }, "");

const CConfigValueValidator<char> CConfigRegister::NON_WHITESPACE
        ([](char c) { return !isspace(c); }, "cannot be whitespace");

const CConfigValueValidator<std::string> CConfigRegister::NON_EMPTY_STRING
        ([](const std::string& str) { return !str.empty(); },
         "string cannot be empty");

void CConfigRegister::register_level_loading(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    uniqueId++;
    config->m_Color.register_value("BACKGROUND_COLOR");
    
    const std::vector<std::string> SYMBOLS = {"ENEMY_SPAWNER", "PLAYER_STARTING_POSITION",
                                              "BOX_LEVEL_SYMBOL", "WALL_LEVEL_SYMBOL", "IND_WALL_LEVEL_SYMBOL"};
    for (const auto& symbol: SYMBOLS) {
        config->m_Char.register_value(symbol, NON_WHITESPACE, uniqueId);
    }
    config->m_String.register_value("START_OF_WAVES_SEPARATOR", NON_EMPTY_STRING);
    config->m_Char.register_value("WAVE_SEGMENT_SEPARATOR", NON_WHITESPACE);
}

void CConfigRegister::register_static_objects(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    config->m_Int.register_value("BOX_HEALTH", POSITIVE_INT);
    config->m_CVisualBlock.register_value("BOX_SPRITE");
    
    config->m_Int.register_value("WALL_HEALTH", POSITIVE_INT);
    config->m_CVisualBlock.register_value("WALL_SPRITE");
    
    config->m_CVisualBlock.register_value("IND_WALL_SPRITE");
}

void CConfigRegister::register_player(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    config->m_Int.register_value("P_MAX_HEALTH", POSITIVE_INT);
    config->m_Int.register_value("P_NUM_OF_SPRITES", NUM_OF_SPRITES);
    config->m_CVisualBlock.register_value("P_SPRITE");
    for (int i = 1; i <= 6; ++i) {
        std::ostringstream spriteStream;
        spriteStream << "P_SPRITE_" << i;
        config->m_CVisualBlock.register_value(spriteStream.str());
    }
}

void CConfigRegister::register_inputs(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    uniqueId++;
    const std::vector<std::string> inputs = {
            "UP", "DOWN", "LEFT", "RIGHT", "SHOOT", "SELECT_FIRST_GUN", "SELECT_SECOND_GUN",
            "SELECT_THIRD_GUN", "SELECT_FOURTH_GUN", "SELECT_FIFTH_GUN", "SELECT_SIXTH_GUN",
            "SELECT_SEVENTH_GUN", "SELECT_EIGHT_GUN", "SELECT_NINTH_GUN", "PAUSE", "QUIT", "ENTER"
    };
    for (auto& input: inputs) {
        config->m_Char.register_value(input, ALWAYS_CORRECT, uniqueId);
    }
}

void CConfigRegister::register_enemies(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    uniqueId++;
    // Register attributes of charged enemies.
    config->m_Color.register_value("CHARGED_FG");
    config->m_Color.register_value("CHARGED_BG");
    config->m_Int.register_value("CHARGED_UPDATE_PERIOD", NON_NEGATIVE_INT);
    config->m_Int.register_value("CHARGED_AI_LEVEL");
    
    // Register attributes of melee and ranged enemies (represented by 'M' and 'R' at the start of the identifier).
    for (char type: {'M', 'R'}) {
        
        // Number of melee and ranged enemies is different.
        int max = (type == 'M' ? 6 : 3);
        for (int i = 1; i <= max; ++i) {
            std::ostringstream stream;
            stream << type << "_ENEMY_" << i;
            std::string identifier = stream.str();
            
            // Identifier that is used when loading a level.
            config->m_Char.register_value(identifier, ALWAYS_CORRECT, uniqueId);
            identifier += "_";
            config->m_Int.register_value(identifier + "NUM_OF_SPRITES", NUM_OF_SPRITES);
            
            config->m_CVisualBlock.register_value(identifier + "SPRITE");
            for (int j = 1; j <= 6; ++j) {
                std::ostringstream spriteStream;
                spriteStream << "SPRITE_" << j;
                config->m_CVisualBlock.register_value(identifier + spriteStream.str());
            }
            config->m_Int.register_value(identifier + "HEALTH", POSITIVE_INT);
            config->m_Int.register_value(identifier + "AI_LEVEL");
            config->m_Int.register_value(identifier + "UPDATE_PERIOD");
            config->m_Toughness.register_value(identifier + "TOUGHNESS");
            if (type == 'M') {
                // Melee enemies have a attribute DAMAGE.
                config->m_Int.register_value(identifier + "DAMAGE");
            } else {
                // Ranged enemies have attributes for their guns.
                config->m_Int.register_value(identifier + "SIGHT", POSITIVE_INT);
                identifier += "PISTOL_";
                config->m_Int.register_value(identifier + "FIRE_RATE_PERIOD");
                identifier += "BULLET_";
                config->m_Int.register_value(identifier + "DAMAGE");
                config->m_Color.register_value(identifier + "FG");
                config->m_Color.register_value(identifier + "BG");
                config->m_Int.register_value(identifier + "MOVE_PERIOD");
                config->m_Int.register_value(identifier + "HEALTH");
                config->m_String.register_value(identifier + "VISUALS", BULLET_VISUALS);
            }
        }
    }
}

void CConfigRegister::register_guns(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    const int NUM_OF_GUNS = 6;
    const std::array<std::string, NUM_OF_GUNS> GUN_IDS = {"LAME_GUN", "UZI", "AK-0", "SHOTGUN",
                                                          "CLAYMORE", "MINE_PLACER"};
    for (int i = 0; i < NUM_OF_GUNS; ++i) {
        std::string identifier = GUN_IDS[i] + "_";
        config->m_String.register_value(identifier + "NAME");
        config->m_Int.register_value(identifier + "FIRE_RATE_PERIOD", NON_NEGATIVE_INT);
        config->m_Int.register_value(identifier + "MAX_AMMO");
        
        identifier += "BULLET_";
        config->m_Int.register_value(identifier + "DAMAGE");
        config->m_Int.register_value(identifier + "MOVE_PERIOD");
        config->m_Color.register_value(identifier + "FG");
        config->m_Color.register_value(identifier + "BG");
        config->m_Int.register_value(identifier + "HEALTH", POSITIVE_INT);
        config->m_String.register_value(identifier + "VISUALS", BULLET_VISUALS);
    }
    config->m_CVisualBlock.register_value("CLAYMORE_CLAYMORE_SPRITE");
}

void CConfigRegister::register_ui(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    const std::vector<std::string> elements = {
            "HEALTH", "AMMO", "GUN"
    };
    
    for (const auto& element: elements) {
        config->m_String.register_value(element + "_TEXT");
        config->m_Color.register_value(element + "_COLOR");
        config->m_Int.register_value(element + "_MAX_LENGTH", NON_NEGATIVE_INT);
    }
}

void CConfigRegister::register_misc(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    uniqueId++;
    config->m_Int.register_value("MINIMUM_MILLISECONDS_PER_TICK", POSITIVE_INT);
    config->m_String.register_value("PATH_TO_LEVEL_DIRECTORY");
    config->m_String.register_value("LEVEL_FILE_EXTENSION", NON_EMPTY_STRING, uniqueId);
    config->m_String.register_value("HIGH_SCORES_FILE_EXTENSION", NON_EMPTY_STRING, uniqueId);
}

void CConfigRegister::register_bonuses(const std::shared_ptr<CConfig>& config, int& uniqueId) {
    std::vector<std::string> bonuses = {"HEAL", "HEAL_PLUS", "DOUBLE_BULLETS", "AMMO"};
    
    for (auto& bonus: bonuses) {
        bonus += "_BONUS_";
        config->m_CVisualBlock.register_value(bonus + "SPRITE");
        config->m_Toughness.register_value(bonus + "TOUGHNESS");
        config->m_Int.register_value(bonus + "PROBABILITY", PROBABILITY);
    }
    
    config->m_Int.register_value("HEAL_BONUS_HP_AMOUNT", NON_NEGATIVE_INT);
    config->m_Int.register_value("HEAL_PLUS_BONUS_HP_AMOUNT", NON_NEGATIVE_INT);
    config->m_Int.register_value("DOUBLE_BULLETS_BONUS_DURATION", NON_NEGATIVE_INT);
}




