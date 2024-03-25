#include "CSimpleFollowerAi.h"

CSimpleFollowerAi::CSimpleFollowerAi()
        : m_SamePositionCounter(0), m_PreviousPosition() {}

Direction::EDirection
CSimpleFollowerAi::decide_direction(const CPosition& startPosition, const CPosition& targetPosition,
                                    const CMapJoin& toAvoid) {
    
    // Find the direction that results in the shortest distance between
    // startPosition + direction and targetPosition.
    int shortestDistance = INT_MAX;
    Direction::EDirection bestDirection = Direction::NONE;
    // Loop through all possible directions.
    for (int i = 0; i < Direction::DIRECTION_COUNT; i++) {
        
        auto potentialDirection = static_cast<Direction::EDirection>(i);
        CPosition potentialPosition = startPosition + potentialDirection;
        
        // If the enemy cannot go to the new position pick a different one.
        if (!toAvoid.can_be_stepped_on(potentialPosition))
            continue;
        
        // Calculate the distance to the targetPosition.
        int candidateDistance = manhattan_distance(potentialPosition, targetPosition);
        // Update bestDirection if it resulted in smaller or the same distance (in that case we decide randomly).
        if (candidateDistance < shortestDistance || (candidateDistance == shortestDistance && rand() % 2)) {
            shortestDistance = candidateDistance;
            bestDirection = potentialDirection;
        }
    }
    
    // Detect if AI tried to go to the same direction, but it resulted in not moving.
    if (m_PreviousPosition == startPosition + bestDirection) {
        m_SamePositionCounter++;
    } else {
        m_SamePositionCounter = 0;
    }
    
    if (m_SamePositionCounter > 2 && rand() % 3) {
        // AI is stuck -> pick a random direction that does not result in collisions with environment.
        Direction::EDirection randomDirection = CUtilities::random_direction();
        if (toAvoid.can_be_stepped_on(startPosition + randomDirection))
            bestDirection = randomDirection;
    }
    
    m_PreviousPosition = startPosition;
    return bestDirection;
}

std::shared_ptr<CEnemyAi> CSimpleFollowerAi::clone() const {
    return std::make_shared<CSimpleFollowerAi>(*this);
}

std::shared_ptr<CFollowerAi> CSimpleFollowerAi::clone_as_follower() const {
    return std::make_shared<CSimpleFollowerAi>(*this);
}
