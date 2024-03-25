#pragma once

#include <memory>
#include <vector>
#include "CConfig.h"
#include "CUtilities.h"
#include "CConfigValueValidator.h"

/// @brief Static clas that generates requirements in CConfig that are needed for
///        CApplication class to work properly.
class CConfigRegister {
public:
    
    /// This class is static, so constructor is deleted.
    CConfigRegister() = delete;
    
    /// Method for generating the config.
    /// @return Pointer to config that is loaded with requirements (registered identifiers of wanted values).
    [[nodiscard]] static std::shared_ptr<CConfig> get_config_with_registered_values();

private:
    /// Validator for checking if an int represents probability - number from 0 to 100 (including).
    static const CConfigValueValidator<int> PROBABILITY;
    /// Validator for checking if an int is positive.
    static const CConfigValueValidator<int> POSITIVE_INT;
    /// Validator for checking if an int is not negative.
    static const CConfigValueValidator<int> NON_NEGATIVE_INT;
    /// Validator for checking if a string correctly represent bullet visuals (its length has to be 4).
    static const CConfigValueValidator<std::string> BULLET_VISUALS;
    /// Validator for checking if an int can be a valid number of
    /// sprites of CMovableObject (its value has to be 1, 2, 3 or 6).
    static const CConfigValueValidator<int> NUM_OF_SPRITES;
    /// Validator that always returns true.
    static const CConfigValueValidator<char> ALWAYS_CORRECT;
    /// Validator that checks if a char is not a whitespace.
    static const CConfigValueValidator<char> NON_WHITESPACE;
    /// Validator that checks if a string is not an empty string.
    static const CConfigValueValidator<std::string> NON_EMPTY_STRING;
    
    /// Registers identifiers that correspond to level loading.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_level_loading(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that correspond to static objects (walls, boxes, ...).
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_static_objects(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that correspond to player configuration.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_player(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that correspond to keyboard input.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_inputs(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that correspond to the stats of enemies.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_enemies(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that correspond to guns of the player.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_guns(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that correspond to user interface.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_ui(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that correspond to bonuses.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_bonuses(const std::shared_ptr<CConfig>& config, int& uniqueId);
    
    /// Registers identifiers that do not really fit into any categories listed above.
    /// @param[in] config Config to register the identifiers into.
    /// @param[in, out] uniqueId UniqueId that gets incremented if a gets used
    ///                          as a uniqueId for config identifiers.
    ///                          This ensures that if the uniqueId is passed between calls
    ///                          of the function it will have a unique value.
    static void register_misc(const std::shared_ptr<CConfig>& config, int& uniqueId);
};
