#pragma once

#include "CFollowerAi.h"
#include "CUtilities.h"

/// @brief Class extending CFollowerAi.
///        It generates movement that will not result in the enemy colliding with environment.
///        If the ai finds out, that it has been stuck at the same position for multiple iterations
///        it will try moving in a random direction.
class CSimpleFollowerAi : public CFollowerAi {
public:
    
    /// Default constructor of CSimpleFollowerAi
    CSimpleFollowerAi();
    
    /// @return A new pointer to instance of CSimpleFollowerAi.
    [[nodiscard]] std::shared_ptr<CEnemyAi> clone() const override;
    
    /// @return A new pointer to instance of CSimpleFollowerAi.
    [[nodiscard]] std::shared_ptr<CFollowerAi> clone_as_follower() const override;

protected:
    
    /// Internal method that is called in 'decide_action()' used for determining the
    /// direction the ai should move in. The ai tries to move in some direction that
    /// would result in being closer to the player.
    /// If the %m_SamePositionCounter is high, it is going to pick a random direction.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position).
    /// @param[in] toAvoid Map of objects that should be avoided if possible.
    Direction::EDirection decide_direction(const CPosition& startPosition,
                                           const CPosition& targetPosition,
                                           const CMapJoin& toAvoid) override;
    
    
    /// For how many iterations the ai was in the same place.
    int m_SamePositionCounter;
    
    /// Previous startPosition. This is used to update %m_SamePositionCounter.
    std::optional<CPosition> m_PreviousPosition;
};
