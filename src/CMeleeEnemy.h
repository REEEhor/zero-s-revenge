#pragma once

#include "CEnemy.h"

/// @brief Class extending CEnemy by implementing enemy that tries to get close to the player
///        and then hit him (which it only can if it is close enough).
class CMeleeEnemy : public CEnemy {
public:
    
    /// Constructor of CMeleeEnemy.
    /// @param[in] object Object that represents physical state of the enemy in game.
    /// @param[in] ai Artificial intelligence of the CEnemy that will determine how the CMeleeEnemy behaves.
    /// @param[in] tickUpdatePeriod How often should the enemy should do an action (move/attack).
    /// @param[in] toughness Represents how difficult this enemy is to beat.
    ///                      This is not determined in game but rather in a configuration file.
    ///                      This value is later used to determine how good should be the bonus
    ///                      that drops from this enemy when it gets killed.
    /// @param[in] damage The amount of damage this enemy should deal to the player when it hits him.
    CMeleeEnemy(const std::shared_ptr<CMovableObject>& object, const CEnemyAi& ai, int tickUpdatePeriod,
                Toughness::EToughness toughness, int damage);
    
protected:
    
    /// Implemented method for update the state of the enemy.
    /// @param[in] action Action decided by the ai.
    /// @param [int, out] player Needs player for getting his/her position and potentially dealing damage.
    /// @param[in, out] mapContainingObject CMap that contains object that this enemy controls.
    ///                                     Necessary for keeping mapping between object and position up to date.
    ///                                     This method also deletes object from this CMap, if it is destroyed.
    /// @param[in, out] environment CMap of objects that can interact with enemy's object.
    /// @param[out] bullets List of bullets so that shooting enemies can add bullets into the game
    ///                     (not relevant to this type of enemy).
    /// @param[out] bulletMap Map containing bullet objects so that shooting enemies can add bullets into the game.
    ///                     (not relevant to this type of enemy).
    bool inner_update(Action::EAction action, CObject& player, const std::shared_ptr<CMap>& mapContainingObject,
                      const CMapJoin& environment, std::list<CBullet>& bullets,
                      const std::shared_ptr<CMap>& bulletMap) override;
    int m_Damage;
};
