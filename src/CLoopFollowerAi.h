#pragma once

#include "CFollowerAi.h"

/// @brief Class extending from CFollowerAi by implementing walking in a
///        square - predetermined pattern.
///        The Ai tries to walk into one direction and when it hits a wall
///        or gets stuck, it turns to its right.
class CLoopFollowerAi : public CFollowerAi {
public:
    
    /// Default constructor of CLoopFollowerAi.
    CLoopFollowerAi();
    
    /// @return A pointer to a new instance of CLoopFollowerAi.
    [[nodiscard]] std::shared_ptr<CEnemyAi> clone() const override;
    
    /// @return A pointer to a new instance of CLoopFollowerAi.
    [[nodiscard]] std::shared_ptr<CFollowerAi> clone_as_follower() const override;

protected:
    
    /// Internal method that is called in 'decide_action()' used for determining the
    /// direction the AI should move in. The AI tries to walk in a straight line
    /// and if it realises it cannot, it turns right.
    /// @param[in] startPosition The position that the enemy currently is.
    /// @param[in] targetPosition Position that is supposed to be reached (presumably player's position - gets ignored).
    /// @param[in] toAvoid Map of objects that should be avoided if possible.
    Direction::EDirection
    decide_direction(const CPosition& startPosition, const CPosition& targetPosition, const CMapJoin& toAvoid) override;
    
private:
    
    /// Rotates %m_CurrentWalkingDirection by 90° to the right.
    void turn_right();
    
    /// The direction the loop AI currently tries to walk in.
    Direction::EDirection m_CurrentWalkingDirection;
    
    /// Previous position of the enemy.
    /// This is used for detecting if the enemy got stuck.
    CPosition m_PreviousPosition;
};
