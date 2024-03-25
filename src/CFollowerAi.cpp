#include "CFollowerAi.h"


Action::EAction CFollowerAi::decide_action(const CPosition& startPosition, const CPosition& targetPosition,
                                           const CMapJoin& toAvoid,
                                           Direction::EDirection facingDirection) {
    
    return CUtilities::action_from_direction(decide_direction(startPosition, targetPosition, toAvoid));
}

