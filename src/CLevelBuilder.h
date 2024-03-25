#pragma once

#include "CConfig.h"
#include "CWavesManager.h"
#include "CMap.h"
#include <filesystem>

/// @brief Class that loads level from a file into containers used in the game.
class CLevelBuilder {
public:
    
    /// Constructor of CLevelBuilder.
    /// @param[in] config Configuration of the application. This is necessary since the
    ///                   the represented characters in a level file are configurable.
    /// @param[in] factory Factory that can create game objects.
    CLevelBuilder(const std::shared_ptr<const CConfig>& config, const std::shared_ptr<const CEntityFactory>& factory);
    
    /// Loads a level from file and stores its parsed contents into game containers.
    /// @param[in] levelFilePath Path to the file containing level.
    /// @param[out] wavesManager Waves manager to which we want to load the level enemy waves into.
    /// @param[out] environment Map that will be filled with static objects found in the level.
    /// @param[out] playerPosition Starting position of the player in loaded level.
    /// @param[out] dimensions Width and height of level.
    void load_level(const std::string& levelFilePath, CWavesManager& wavesManager,
                    std::shared_ptr<CMap>& environment, CPosition& playerPosition, CPosition& dimensions) const;

private:
    
    /// Loads just environment from the stream (meaning not the waves of the enemies).
    /// @param[in, out] stream Stream that we want to load the level from.
    /// @param[out] wavesManager WavesManager in which we want to register spawn positions of enemies in the level.
    /// @param[out] playerPosition Player starting position in the level.
    /// @param[out] dimensions Width and height of the level.
    void load_environment(std::istream& stream, CWavesManager& wavesManager, std::shared_ptr<CMap>& environment,
                          CPosition& playerPosition, CPosition& dimensions) const;
    
    /// Generates a map, where the key is a char found in the level that is being loaded
    /// and functions that should be called when given character is found (usually generating
    /// an object into some container).
    /// Returned value of this method (map of functions) is the used for parsing the file containing the level data.
    /// @param[out] wavesManager WavesManager in which we want to register spawn positions of enemies in the level.
    /// @param[out] environment CMap of static objects in the level (walls and boxes).
    /// @param[out] playerPosition Player starting position in the level.
    /// @param[out] numberOfPlayerStartingPositions How many times the player position has been found in the level.
    ///                                             This values should be exactly one.
    /// @return Map of characters that represent actions that are values in the map.
    std::unordered_map<char, std::function<void(const CPosition&)>>
    generate_functions(CWavesManager& wavesManager, std::shared_ptr<CMap>& environment,
                       CPosition& playerPosition, int& numberOfPlayerStartingPositions) const;
    
    /// Configuration of the application. This is necessary since the
    /// the represented characters in a level file are configurable.
    std::shared_ptr<const CConfig> m_Config;
    
    /// Factory that can create game objects.
    std::shared_ptr<const CEntityFactory> m_Factory;
};
