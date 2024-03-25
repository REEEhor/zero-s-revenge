#pragma once

#include "CEnemyAi.h"
#include "CMapJoin.h"
#include <climits>
#include "CMapJoin.h"
#include <climits>
#include <optional>

/// @brief Abstract class extending CEnemyAi. This class only returns actions corresponding to movement.
///        It can be still passed to enemies as ai, for example charged enemies do not need (and ignore)
///        any action that is not movement. Other AIs use this class to get closer to the player when
///        they cannot do anything else.
class CFollowerAi : public CEnemyAi {
public:
    
    /// Overloaded method 'decide_action()'. It calls the internal method 'decide_direction()'
    /// to determine the direction and returns its conversion to action.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible.
    /// @param[in] facingDirection Direction that the enemy is currently facing (ignored).
    Action::EAction decide_action(const CPosition& startPosition,
                                  const CPosition& targetPosition,
                                  const CMapJoin& toAvoid,
                                  Direction::EDirection facingDirection) override;
    
    /// @return A new pointer to instance of a non-abstract child of CFollowerAi.
    [[nodiscard]] virtual std::shared_ptr<CFollowerAi> clone_as_follower() const = 0;

private:
    
    /// Internal method that is called in 'decide_action()' used for determining the
    /// direction the ai should move in.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible.
    virtual Direction::EDirection decide_direction(const CPosition& startPosition,
                                                   const CPosition& targetPosition,
                                                   const CMapJoin& toAvoid) = 0;
};
