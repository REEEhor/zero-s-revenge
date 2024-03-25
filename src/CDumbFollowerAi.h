#pragma once

#include "CFollowerAi.h"

/// @brief Class extending CFollowerAi by trying to move in strait to the
///        player. Ignoring obstacles.
class CDumbFollowerAi : public CFollowerAi {
public:
    /// @return A pointer to a new instance of CDumbFollowerAi.
    [[nodiscard]] std::shared_ptr<CEnemyAi> clone() const override;
    
    /// @return A pointer to a new instance of CDumbFollowerAi.
    [[nodiscard]] std::shared_ptr<CFollowerAi> clone_as_follower() const override;

protected:
    
    /// Internal method that is called in 'decide_action()' used for determining the
    /// direction the ai should move in. This AI tries to walk straight to the player.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible (gets ignored by this AI).
    Direction::EDirection decide_direction(const CPosition& startPosition,
                                           const CPosition& targetPosition,
                                           const CMapJoin& toAvoid) override;
};
