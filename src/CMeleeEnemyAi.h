#pragma once

#include "CFollowerAi.h"
#include "CPosition.h"

/// @brief Class extending CEnemyAi by implementing decision to try to attack if the targetPosition is in reach.
class CMeleeEnemyAi : public CEnemyAi {
public:
    
    /// Constructor of CMeleeEnemyAi.
    /// @param[in] navigationAi Navigation Ai that decides movement if
    ///                         the attack is not possible.
    explicit CMeleeEnemyAi(const CFollowerAi& navigationAi);
    
    /// Method deciding which action to take based on given arguments.
    /// If the player is close enough, the AI will return Action::ATTACK.
    /// If not, it will let the CFollowerAi decide how to move.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible.
    /// @param[in] facingDirection Direction that the enemy is currently facing.
    [[nodiscard]] Action::EAction decide_action(const CPosition& startPosition, const CPosition& targetPosition,
                                                const CMapJoin& toAvoid,
                                                Direction::EDirection facingDirection) override;
    
    /// @return A new pointer to instance of a CMeleeEnemyAi.
    [[nodiscard]] std::shared_ptr<CEnemyAi> clone() const override;
    
    /// Copy constructor since this class has a pointer to an object.
    CMeleeEnemyAi(const CMeleeEnemyAi& other);
    
    /// Copy operator= since this class has a pointer to an object.
    CMeleeEnemyAi& operator=(const CMeleeEnemyAi& other);

protected:
    
    /// Pointer to navigation AI that tells which direction to go to
    /// if the player is not close enough for an attack.
    std::shared_ptr<CFollowerAi> m_NavigationAi;
};
