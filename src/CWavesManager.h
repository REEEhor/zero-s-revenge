#pragma once

#include "CConfig.h"
#include "CWave.h"
#include "CEntityFactory.h"
#include <sstream>
#include <string>
#include <iostream>
#include <vector>

/// @brief Manager of waves of enemies.
///        In the game, the player must first defeat an entire wave
///        and only then a new one will appear.
class CWavesManager {
public:
    
    /// Default constructor of the CWavesManager.
    /// It initialises the %m_Spawning attribute to true.
    CWavesManager();
    
    /// Register a spawn position at which an enemy can spawn.
    /// @param[in] position Position to register.
    void register_spawn_position(const CPosition& position);
    
    /// Loads the waves from the level file that is in %stream.
    /// @param[in] stream Stream to load the waves from.
    /// @param[in] config Configuration of the game.
    /// @param[in] factory Factory that can create entities so the waves manager can spawn enemies.
    void load(std::istream& stream, const CConfig& config, const std::shared_ptr<const CEntityFactory>& factory);
    
    /// Updates the spawning of enemies and determines if the player has beaten the game
    /// by checking if there are no more waves of enemies to kill.
    /// @param[out] enemies Container used by the game to store enemies. This is needed if
    ///                     the waves manager decides to spawn an enemy.
    /// @param[out] entityMap Container used by the game to store entity objects. This is needed if
    ///                       the waves manager decides to spawn an enemy.
    /// @return False if there are no more waves of enemies to spawn and all enemies them are killed.
    ///         This mean a won game. Otherwise it returns true.
    bool update(std::list<std::shared_ptr<CEnemy>>& enemies, CMap& entityMap);
    
    /// Checks if the waves manager has been loaded properly
    /// - meaning there is nonzero number of potential spawn position for enemies.
    /// @return If the number of spawn position of enemies is not zero.
    [[nodiscard]] bool is_valid() const;
    
private:
    
    /// Potential positions where enemies can spawn.
    std::vector<CPosition> m_SpawnPositions;
    
    /// List of waves that waves manager uses to spawn enemies.
    std::list<CWave> m_Waves;
    
    /// If the waves manager is currently trying to spawn emeries.
    bool m_Spawning;
};
