#include "CLoopFollowerAi.h"

std::shared_ptr<CEnemyAi> CLoopFollowerAi::clone() const {
    return std::make_shared<CLoopFollowerAi>(*this);
}

std::shared_ptr<CFollowerAi> CLoopFollowerAi::clone_as_follower() const {
    return std::make_shared<CLoopFollowerAi>(*this);
}

Direction::EDirection CLoopFollowerAi::decide_direction(const CPosition& startPosition, const CPosition& targetPosition,
                                                        const CMapJoin& toAvoid) {
    // Try to go straight.
    CPosition newPosition = startPosition + m_CurrentWalkingDirection;
    
    // Detect if it is possible to go straight or if
    // the enemy got stuck (%m_PreviousPosition is the same as %startPosition).
    if (!toAvoid.can_be_stepped_on(newPosition)
        || m_PreviousPosition == startPosition) {
        
        // Enemy is stuck -> turn right.
        turn_right();
    }
    m_PreviousPosition = startPosition;
    return m_CurrentWalkingDirection;
}

CLoopFollowerAi::CLoopFollowerAi()
        : m_CurrentWalkingDirection(Direction::UP) {}

void CLoopFollowerAi::turn_right() {
    switch (m_CurrentWalkingDirection) {
        case Direction::UP:
            m_CurrentWalkingDirection = Direction::RIGHT;
            break;
        case Direction::DOWN:
            m_CurrentWalkingDirection = Direction::LEFT;
            break;
        case Direction::LEFT:
            m_CurrentWalkingDirection = Direction::UP;
            break;
        case Direction::RIGHT:
            m_CurrentWalkingDirection = Direction::DOWN;
            break;
        default:
            break;
    }
}
