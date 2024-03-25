#include "CScaredFollowerAi.h"

std::shared_ptr<CEnemyAi> CScaredFollowerAi::clone() const {
    return std::make_shared<CScaredFollowerAi>(*this);
}

std::shared_ptr<CFollowerAi> CScaredFollowerAi::clone_as_follower() const {
    return std::make_shared<CScaredFollowerAi>(*this);
}

Direction::EDirection
CScaredFollowerAi::decide_direction(const CPosition& startPosition, const CPosition& targetPosition,
                                    const CMapJoin& toAvoid) {
    int maximumDistance = INT_MIN;
    Direction::EDirection bestDirection = Direction::NONE;
    // Loop through all possible directions and find the one
    // that results in the biggest distance between targetPosition and startPosition.
    for (int i = 0; i < Direction::DIRECTION_COUNT; i++) {
        auto potentialDirection = static_cast<Direction::EDirection>(i);
        CPosition potentialPosition = startPosition + potentialDirection;
        
        // Calculate the distance to the targetPosition.
        int candidateDistance = manhattan_distance(potentialPosition, targetPosition);
        
        // Update bestDirection if it resulted in bigger or the same distance (in that case we decide randomly).
        if (candidateDistance > maximumDistance || (candidateDistance == maximumDistance && rand() % 2)) {
            maximumDistance = candidateDistance;
            bestDirection = potentialDirection;
        }
    }
    return bestDirection;
}
