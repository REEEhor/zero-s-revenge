#include "CMeleeEnemy.h"

CMeleeEnemy::CMeleeEnemy(const std::shared_ptr<CMovableObject>& object, const CEnemyAi& ai, int tickUpdatePeriod,
                         Toughness::EToughness toughness, int damage)
        : CEnemy(object, ai, tickUpdatePeriod, toughness), m_Damage(damage) {}

bool
CMeleeEnemy::inner_update(Action::EAction action, CObject& player, const std::shared_ptr<CMap>& mapContainingObject,
                          const CMapJoin& environment, std::list<CBullet>& bullets,
                          const std::shared_ptr<CMap>& bulletMap) {
    
    // If the %action is ATTACK, try to attack the player.
    if (action == Action::ATTACK) {
        
        // Check if player is right in front of the enemy.
        Direction::EDirection facingDirection = CUtilities::direction_from_vh_orientations(
                m_Object->get_v_orientation(), m_Object->get_h_orientation());
        CPosition supposedPlayerPosition = m_Object->get_position() + facingDirection;
        
        if (supposedPlayerPosition == player.get_position()) {
            // Player is in the direction the enemy is looking and close enough -> deal damage.
            player.deal_damage(m_Damage);
        }
    }
    
    // Call internal method for update.
    Direction::EDirection direction = CUtilities::direction_from_action(action);
    return CNonStaticEntity::update(mapContainingObject, environment, direction);
}
