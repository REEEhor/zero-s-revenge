#include "CBullet.h"

CBullet::CBullet(const std::shared_ptr<CMovableObject>& object,
                 Direction::EDirection flyingDirection,
                 int ticksPeriod)
        : CNonStaticEntity(object), m_FlyingDirection(flyingDirection), m_Ticks(ticksPeriod) {}

bool CBullet::update(const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment) {
    
    // Check whether it is time to move the bullet and update it.
    if (m_Ticks.decrement()) {
        return CNonStaticEntity::update(mapContainingObject, environment, m_FlyingDirection);
    } else {
        return CNonStaticEntity::update(mapContainingObject, environment, Direction::NONE);
    }
}
