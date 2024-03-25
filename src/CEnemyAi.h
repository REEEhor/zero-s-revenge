#pragma once

#include "EAction.h"
#include "EDirection.h"
#include "CUtilities.h"
#include "CMap.h"
#include "CMapJoin.h"
#include <memory>

/// @brief Abstract class for deciding actions of enemies.
class CEnemyAi {
public:
    /// Method deciding which action to take based on given arguments
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible.
    /// @param[in] facingDirection Direction that the enemy is currently facing.
    [[nodiscard]] virtual Action::EAction
    decide_action(const CPosition& startPosition, const CPosition& targetPosition, const CMapJoin& toAvoid,
                  Direction::EDirection facingDirection) = 0;
    
    
    /// @return A new pointer to instance of a non-abstract child of CEnemyAi.
    [[nodiscard]] virtual std::shared_ptr<CEnemyAi> clone() const = 0;
};
