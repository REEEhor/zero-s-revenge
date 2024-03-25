#pragma once

#include "CConfig.h"
#include "CWaveSegment.h"
#include "CEntityFactory.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/// @brief Class for management of one wave of enemies.
///        It consists of wave segments which it uses to spawn enemies
///        at one of the available spawn positions.
class CWave {
public:
    
    /// Constructor of CWave.
    /// @param[in, out] stream The stream to load the enemy wave from.
    /// @param[in] config Config containing configurable values since the format of the waves
    ///                   is partially set decided by the config file.
    /// @param[in] factory Pointer to a factory that can create entities so the individual wave
    ///                    segments can spawn enemies.
    CWave(std::istream& stream, const CConfig& config, const std::shared_ptr<const CEntityFactory>& factory);
    
    /// Maybes spawns an enemy at one of the %spawnPositions using wave segments
    /// depending if there is an empty space at one of the spawn position.
    /// @param[in] spawnPositions Vector of positions where the enemies can spawn.
    /// @param[out] enemies If the method decides to spawn an enemy, it puts it into the
    ///                      game's container of enemies.
    /// @param[in, out] entityMap Map that contains entities so the method can see if there is an empty
    ///                           place at the spawn position and to put a new enemy object in there
    ///                           if it gets created.
    /// @return Whether the wave has spawned all of the enemies.
    ///         False means it is no longer active and should be erased.
    [[nodiscard]] bool spawn(const std::vector<CPosition>& spawnPositions,
                             std::list<std::shared_ptr<CEnemy>>& enemies, CMap& entityMap);
private:
    /// Individual wave segments of the wave that are used to spawn the enemies.
    std::list<CWaveSegment> m_WaveSegments;
};
