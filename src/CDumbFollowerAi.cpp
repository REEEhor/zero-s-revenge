#include "CDumbFollowerAi.h"

std::shared_ptr<CEnemyAi> CDumbFollowerAi::clone() const {
    return std::make_shared<CDumbFollowerAi>(*this);
}

std::shared_ptr<CFollowerAi> CDumbFollowerAi::clone_as_follower() const {
    return std::make_shared<CDumbFollowerAi>(*this);
}

Direction::EDirection CDumbFollowerAi::decide_direction(const CPosition& startPosition, const CPosition& targetPosition,
                                                        const CMapJoin& toAvoid) {
    int shortestDistance = INT_MAX;
    Direction::EDirection bestDirection = Direction::NONE;
    // Loop through all possible directions and find the one
    // that results in the smallest distance between targetPosition and startPosition.
    for (int i = 0; i < Direction::DIRECTION_COUNT; i++) {
        auto potentialDirection = static_cast<Direction::EDirection>(i);
        CPosition potentialPosition = startPosition + potentialDirection;
        
        // Calculate the distance to the targetPosition.
        int candidateDistance = manhattan_distance(potentialPosition, targetPosition);
        
        // Update bestDirection if it resulted in smaller or the same distance (in that case we decide randomly).
        if (candidateDistance < shortestDistance || (candidateDistance == shortestDistance && rand() % 2)) {
            shortestDistance = candidateDistance;
            bestDirection = potentialDirection;
        }
    }
    return bestDirection;
}
