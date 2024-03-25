#include "CRangedEnemy.h"

CRangedEnemy::CRangedEnemy(const std::shared_ptr<CMovableObject>& object, const CEnemyAi& ai, int tickUpdatePeriod,
                           Toughness::EToughness toughness, const CGun& gun)
        : CEnemy(object, ai, tickUpdatePeriod, toughness), m_Gun(gun.clone()) {}

bool
CRangedEnemy::inner_update(Action::EAction action, CObject& player, const std::shared_ptr<CMap>& mapContainingObject,
                           const CMapJoin& environment, std::list<CBullet>& bullets,
                           const std::shared_ptr<CMap>& bulletMap) {
    
    // Update the internal state of the gun.
    m_Gun->update();
    
    // If the decided action was attack, the enemy shoots.
    if (action == Action::ATTACK) {
        m_Gun->shoot(bullets, bulletMap, m_Object->get_position(), environment,
                     m_Object->get_v_orientation(), m_Object->get_h_orientation());
    }
    
    // Call internal method for update.
    Direction::EDirection direction = CUtilities::direction_from_action(action);
    return CNonStaticEntity::update(mapContainingObject, environment, direction);
}

CRangedEnemy::CRangedEnemy(const CRangedEnemy& other)
        : CEnemy(other), m_Gun(other.m_Gun->clone()) {}

CRangedEnemy& CRangedEnemy::operator=(const CRangedEnemy& other) {
    if (this == &other) return *this;
    m_Gun = other.m_Gun->clone();
    return *this;
}
