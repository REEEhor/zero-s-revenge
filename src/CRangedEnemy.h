#pragma once

#include "CEnemy.h"
#include "CGun.h"

/// @brief Class extending CEnemy by implementing enemy can shoot using CGun.
/// @warning Since CNonStaticEntity does not implement copy semantics (since it would be
///          an unnecessary overhead of copying) this class also does not copy the contents
///          of the pointer to the gun that the enemy has.
class CRangedEnemy : public CEnemy {
public:
    
    /// Constructor of CRangedEnemy.
    /// @param[in] object Object that represents physical state of the enemy in game.
    /// @param[in] ai Artificial intelligence of the CEnemy that will determine how the CRangedEnemy behaves.
    /// @param[in] tickUpdatePeriod How often should the enemy should do an action (move/attack).
    /// @param[in] toughness Represents how difficult this enemy is to beat.
    ///                      This is not determined in game but rather in a configuration file.
    ///                      This value is later used to determine how good should be the bonus
    ///                      that drops from this enemy when it gets killed.
    /// @param[in] gun Gun that the enemy should shoot with.
    CRangedEnemy(const std::shared_ptr<CMovableObject>& object, const CEnemyAi& ai, int tickUpdatePeriod,
                 Toughness::EToughness toughness, const CGun& gun);
    
    /// Custom copy constructor since this class contains a pointer to an object.
    CRangedEnemy(const CRangedEnemy& other);
    
    /// Custom operator= since this since this class contains a pointer to an object.
    CRangedEnemy& operator=(const CRangedEnemy& other);

protected:
    
    /// Implemented method for update the state of the enemy.
    /// @param[in] action Action decided by the ai.
    /// @param[int, out] player Needs player for getting his/her position and potentially dealing damage.
    /// @param[in, out] mapContainingObject CMap that contains object that this enemy controls.
    ///                                     Necessary for keeping mapping between object and position up to date.
    ///                                     This method also deletes object from this CMap, if it is destroyed.
    /// @param[in, out] environment CMap of objects that can interact with enemy's object.
    /// @param[out] bullets List of bullets so this enemy can add bullets into the game.
    /// @param[out] bulletMap Map containing bullet objects so this enemy can add bullets into the game.
    bool inner_update(Action::EAction action, CObject& player, const std::shared_ptr<CMap>& mapContainingObject,
                      const CMapJoin& environment, std::list<CBullet>& bullets,
                      const std::shared_ptr<CMap>& bulletMap) override;
    
    /// Pointer to the gun this enemy uses to shoot.
    std::shared_ptr<CGun> m_Gun;
};
