#include "CChargeEnemy.h"

CChargeEnemy::CChargeEnemy(const std::shared_ptr<CMovableObject>& object, const CEnemyAi& ai, int tickUpdatePeriod,
                           Toughness::EToughness toughness)
        : CEnemy(object, ai, tickUpdatePeriod, toughness) {}

bool
CChargeEnemy::inner_update(Action::EAction action, CObject& player, const std::shared_ptr<CMap>& mapContainingObject,
                           const CMapJoin& environment, std::list<CBullet>& bullets,
                           const std::shared_ptr<CMap>& bulletMap) {
    
    // Just get the direction from action.
    // This enemy does not attack in any other way, just tries to collide with the player.
    Direction::EDirection direction = CUtilities::direction_from_action(action);
    return CNonStaticEntity::update(mapContainingObject, environment, direction);
}
