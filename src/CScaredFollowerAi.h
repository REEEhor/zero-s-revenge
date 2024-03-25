#pragma once

#include "CFollowerAi.h"

/// @brief This class extends CFollowerAi by trying to get from the player as far as possible.
class CScaredFollowerAi : public CFollowerAi {
public:
    
    /// @return A pointer to a new instance of CScaredFollowerAi.
    [[nodiscard]] std::shared_ptr<CEnemyAi> clone() const override;
    
    /// @return A pointer to a new instance of CScaredFollowerAi.
    [[nodiscard]] std::shared_ptr<CFollowerAi> clone_as_follower() const override;
protected:
    
    /// Internal method that is called in 'decide_action()' used for determining the
    /// direction the ai should move in. This AI tries to walk straight from the player.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible (gets ignored by this AI).
    Direction::EDirection decide_direction(const CPosition& startPosition,
                                           const CPosition& targetPosition,
                                           const CMapJoin& toAvoid) override;
};
