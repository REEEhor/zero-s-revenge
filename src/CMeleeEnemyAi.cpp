#include "CMeleeEnemyAi.h"

std::shared_ptr<CEnemyAi> CMeleeEnemyAi::clone() const {
    return std::make_shared<CMeleeEnemyAi>(*this);
}

Action::EAction CMeleeEnemyAi::decide_action(const CPosition& startPosition, const CPosition& targetPosition,
                                             const CMapJoin& toAvoid, Direction::EDirection facingDirection) {
    if (startPosition + facingDirection == targetPosition) {
        // Player is right in front of the enemy -> attack.
        return Action::ATTACK;
    }
    return m_NavigationAi->decide_action(startPosition, targetPosition, toAvoid, facingDirection);
}

CMeleeEnemyAi::CMeleeEnemyAi(const CFollowerAi& navigationAi)
        : m_NavigationAi(navigationAi.clone_as_follower()) {}

CMeleeEnemyAi::CMeleeEnemyAi(const CMeleeEnemyAi& other)
        : CEnemyAi(other), m_NavigationAi(other.m_NavigationAi->clone_as_follower()) {}

CMeleeEnemyAi& CMeleeEnemyAi::operator=(const CMeleeEnemyAi& other) {
    if (this == &other) return *this;
    CEnemyAi::operator=(other);
    m_NavigationAi = other.m_NavigationAi->clone_as_follower();
    return *this;
}

