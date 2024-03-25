#include "CRangedEnemyAi.h"

std::shared_ptr<CEnemyAi> CRangedEnemyAi::clone() const {
    return std::make_shared<CRangedEnemyAi>(*this);
}

Action::EAction CRangedEnemyAi::decide_action(const CPosition& startPosition, const CPosition& targetPosition,
                                              const CMapJoin& toAvoid, Direction::EDirection facingDirection) {
    
    using namespace Direction;
    CPosition positions[] = {startPosition, startPosition, startPosition, startPosition};
    EDirection directions[] = {UP, DOWN, LEFT, RIGHT};
    
    for (int d = 1; d <= m_DistanceToLookInto; ++d) {
        for (int i = 0; i < 4; ++i) {
            
            positions[i] += directions[i];
            if (positions[i] == targetPosition) {
                if (directions[i] == facingDirection) {
                    return Action::ATTACK;
                }
                return CUtilities::action_from_direction(directions[i]);
            }
            
        }
    }
    
    return m_NavigationAi->decide_action(startPosition, targetPosition, toAvoid, facingDirection);
}

CRangedEnemyAi::CRangedEnemyAi(int distanceToLookInto, const CFollowerAi& navigationAi)
        : m_DistanceToLookInto(distanceToLookInto), m_NavigationAi(navigationAi.clone_as_follower()) {}

CRangedEnemyAi::CRangedEnemyAi(const CRangedEnemyAi& other)
        : CEnemyAi(other), m_DistanceToLookInto(other.m_DistanceToLookInto),
          m_NavigationAi(other.m_NavigationAi->clone_as_follower()) {}

CRangedEnemyAi& CRangedEnemyAi::operator=(const CRangedEnemyAi& other) {
    if (this == &other) return *this;
    CEnemyAi::operator=(other);
    m_DistanceToLookInto = other.m_DistanceToLookInto;
    m_NavigationAi = other.m_NavigationAi->clone_as_follower();
    return *this;
}
