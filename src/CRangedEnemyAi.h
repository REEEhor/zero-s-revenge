#pragma once

#include "CFollowerAi.h"
#include <algorithm>

/// @brief Class extending CEnemyAi by implementing decision to shoot when player is in direct line of the enemy.
class CRangedEnemyAi : public CEnemyAi {
public:
    
    /// Constructor of CRangedEnemyAi.
    /// @param[in] distanceToLookInto Distance to which the AI should look into when searching for enemy.
    /// @param[in] navigationAi Navigation Ai that decides movement if
    ///                         the attack is not possible.
    CRangedEnemyAi(int distanceToLookInto, const CFollowerAi& navigationAi);
    
    /// Method deciding which action to take based on given arguments.
    /// If the player (targetPosition) is in direct line with the enemy (startPosition), it will return Action::ATTACK.
    /// If not, it will let the CFollowerAi decide how to move.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible (with movement, this AI also tries to shoot through walls).
    /// @param[in] facingDirection Direction that the enemy is currently facing.
    Action::EAction decide_action(const CPosition& startPosition, const CPosition& targetPosition,
                                  const CMapJoin& toAvoid, Direction::EDirection facingDirection) override;
    
    /// @return A new pointer to instance of a CRangedEnemyAi.
    [[nodiscard]] std::shared_ptr<CEnemyAi> clone() const override;
    
    /// Copy constructor since this class has a pointer to an object.
    CRangedEnemyAi(const CRangedEnemyAi& other);
    
    /// Copy operator= since this class has a pointer to an object.
    CRangedEnemyAi& operator=(const CRangedEnemyAi& other);

protected:
    /// Distance to which the AI should look into when searching for enemy.
    int m_DistanceToLookInto;
    
    /// Pointer to navigation AI that tells which direction to go to
    /// if the player is not close enough for an attack.
    std::shared_ptr<CFollowerAi> m_NavigationAi;
};
