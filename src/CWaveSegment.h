#pragma once

#include "CConfig.h"
#include "CEntityFactory.h"
#include "CEnemy.h"

/// @brief Class representing a part of the wave of enemies.
///        When the level gets loaded, instances of this class get generated
///        - storing info about the type of enemy it should spawn and how many of them.
class CWaveSegment {
public:
    
    /// Constructor of CWaveSegment.
    /// @param[in] stream Stream to read the wave segment from.
    /// @param[in] factory Factory that can create entities so this class can spawn them.
    /// @note The format of the stream should be " number_of_enemies type_of_the_enemy "
    CWaveSegment(std::istream& stream, const std::shared_ptr<const CEntityFactory>& factory);
    
    /// Returns a pointer to a spawned enemy at %position.
    /// @param[in] position Position the enemy should spawn at.
    /// @return Pointer to the created enemy.
    [[nodiscard]] std::shared_ptr<CEnemy> spawn_at(const CPosition& position);
    
    /// Returns whether the number of enemies loaded in constructor has been spawned.
    /// @return If the CWaveSegment still should spawn enemies, this method returns true.
    ///         Otherwise false.
    [[nodiscard]] bool is_active() const;
    
private:
    /// Factory that can create entities so this class can spawn them.
    std::shared_ptr<const CEntityFactory> m_Factory;
    
    /// Strength of the charged enemy
    /// @warning Value may not be initialized if
    ///          the type of the enemy is not charged.
    int m_ChargedStrength;
    
    /// Bool determining whether this wave segment spawns charged enemies or not.
    bool m_ChargedEnemy;
    
    /// Number of enemies that this wave segment should spawn.
    /// This value gets decremented during calls of 'spawn_at()' and
    /// when it reaches zero, the segment is considered to be inactive.
    int m_NumberOfEnemies;
    
    /// Char representing the symbol of NonCharged enemy.
    /// @warning This value may not be properly initialised if the
    ///          the type of the enemy this segment spawn is charged.
    char m_NonChargedSymbol;
};
