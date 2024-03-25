#pragma once

#include "CNonStaticEntity.h"
#include "CBullet.h"
#include "CEnemyAi.h"
#include "CTimeTicks.h"
#include "EToughness.h"

/// @brief Class inheriting from CNonStaticEntity used for management of actions of enemies.
///        Has a pointer to polymorphic AI that tells it what to do via EAction enum.
class CEnemy : public CNonStaticEntity {
public:
    
    /// Constructor of CEnemy.
    /// @param[in] object Object that represents physical state of the enemy in game.
    /// @param[in] ai Artificial intelligence of the CEnemy that will determine how the CEnemy behaves.
    /// @param[in] tickUpdatePeriod How often should the enemy should do an action (move/attack).
    /// @param[in] toughness Represents how difficult this enemy is to beat.
    ///                      This is not determined in game but rather in a configuration file.
    ///                      This value is later used to determine how good should be the bonus
    ///                      that drops from this enemy when it gets killed.
    CEnemy(const std::shared_ptr<CMovableObject>& object, const CEnemyAi& ai, int tickUpdatePeriod,
           Toughness::EToughness toughness);
    
    /// Custom copy constructor since this class contains a pointer to an object.
    CEnemy(const CEnemy& other);
    
    /// Custom operator= since this class contains a pointer to an object.
    /// @return A reference to this.
    CEnemy& operator=(const CEnemy& other);
    
    /// Updates internal state of the enemy. If it time to do an action (this is determined by %m_Ticks),
    /// the class gets an action from ai and passes it into virtual method 'inner_update()'.
    /// @param player[int, out] Needs player for getting his/her position and potentially dealing damage.
    /// @param[in, out] mapContainingObject CMap that contains object that this enemy controls.
    ///                                     Necessary for keeping mapping between object and position up to date.
    ///                                     This method also deletes object from this CMap, if it is destroyed.
    /// @param[in, out] environment CMap of objects that can interact with enemy's object.
    /// @param[out] bullets List of bullets so that shooting enemies can add bullets into the game.
    /// @param[out] bulletMap Map containing bullet objects so that shooting enemies can add bullets into the game.
    /// @return Whether enemy should by treated as not destroyed after the update or not (false means destroyed).
    bool update(CObject& player, const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment,
                std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap);
    
    /// Represents how difficult this enemy is to beat.
    /// This is not determined in game but rather in a configuration file.
    /// This value is later used to determine how good should be the bonus
    /// that drops from this enemy when it gets killed.
    Toughness::EToughness m_Toughness;

protected:
    /// Artificial intelligence of the CEnemy that will determine how the CEnemy behaves.
    std::shared_ptr<CEnemyAi> m_Ai;
    
    /// Instance of CTimeTicks for determining the time period between enemy doing actions.
    CTimeTicks m_Ticks;
    
    /// Virtual method that is called in children of this class.
    /// @param[in] action Action decided by the ai. Implementation of this method decided how to interpret it.
    /// @param player[int, out] Needs player for getting his/her position and potentially dealing damage.
    /// @param[in, out] mapContainingObject CMap that contains object that this enemy controls.
    ///                                     Necessary for keeping mapping between object and position up to date.
    ///                                     This method also deletes object from this CMap, if it is destroyed.
    /// @param[in, out] environment CMap of objects that can interact with enemy's object.
    /// @param[out] bullets List of bullets so that shooting enemies can add bullets into the game.
    /// @param[out] bulletMap Map containing bullet objects so that shooting enemies can add bullets into the game.
    virtual bool
    inner_update(Action::EAction action, CObject& player, const std::shared_ptr<CMap>& mapContainingObject,
                 const CMapJoin& environment, std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap) = 0;
};
