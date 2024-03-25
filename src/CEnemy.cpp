#include "CEnemy.h"

CEnemy::CEnemy(const std::shared_ptr<CMovableObject>& object, const CEnemyAi& ai, int tickUpdatePeriod,
               Toughness::EToughness toughness)
        : CNonStaticEntity(object), m_Toughness(toughness), m_Ai(ai.clone()),
          m_Ticks(tickUpdatePeriod) {}

bool CEnemy::update(CObject& player, const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment,
                    std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap) {
    if (m_Ticks.decrement()) {
        Direction::EDirection facingDirection = CUtilities::direction_from_vh_orientations(
                m_Object->get_v_orientation(), m_Object->get_h_orientation());
        
        Action::EAction action = m_Ai->decide_action(m_Object->get_position(),
                                                     player.get_position(),
                                                     environment, facingDirection);
        
        return inner_update(action, player, mapContainingObject, environment, bullets, bulletMap);
    } else {
        return CNonStaticEntity::update(mapContainingObject, environment, Direction::NONE);
    }
}

CEnemy::CEnemy(const CEnemy& other)
        : CNonStaticEntity(other), m_Toughness(other.m_Toughness),
          m_Ai(other.m_Ai->clone()), m_Ticks(other.m_Ticks) {}

CEnemy& CEnemy::operator=(const CEnemy& other) {
    if (this == &other) return *this;
    m_Toughness = other.m_Toughness;
    m_Ai = other.m_Ai->clone();
    m_Ticks = other.m_Ticks;
    return *this;
}
