#pragma once

#include "CNonStaticEntity.h"
#include "CTimeTicks.h"

/// @brief Class extending CNonStaticEntity by implementing behaviour of a bullet.
class CBullet : public CNonStaticEntity {
public:
    
    /// Constructor of CBullet.
    /// @param[in] object Object that represents physical state of the bullet in the game.
    /// @param[in] flyingDirection Direction the bullet should move in.
    /// @param[in] ticksPeriod How often should the bullet move.
    CBullet(const std::shared_ptr<CMovableObject>& object, Direction::EDirection flyingDirection, int ticksPeriod);
    
    /// Updates internal state of the bullet by moving it in %m_FlyingDirection.
    /// @param[in, out] mapContainingObject CMap that contains object that this class controls.
    ///                                     Necessary for keeping mapping between object and position up to date.
    ///                                     This method also deletes object from this CMap, if it is destroyed.
    /// @param[in, out] environment CMap of objects that can interact with object.
    /// @return Whether bullet should by treated as not destroyed after the update or not (false means destroyed).
    bool update(const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment);
private:
    
    /// Direction the bullet should move in.
    Direction::EDirection m_FlyingDirection;
    
    /// Instance of CTimeTicks for determining how often should the bullet move.
    CTimeTicks m_Ticks;
};
