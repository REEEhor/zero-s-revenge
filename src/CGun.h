#pragma once

#include "CBullet.h"
#include "CDamagingMovableObject.h"
#include "CBulletObjectBuilder.h"
#include <utility>

/// @brief Abstract class representing a gun in the game.
///        Entities like player can have a pointer to this class and use it to shoot bullets.
class CGun {
public:
    
    /// Constructor of CGun.
    /// @param[in] name Name of the gun that should be displayed when player has this gun selected.
    /// @param[in] bulletBuilder Builder object that creates bullets this gun shoots.
    /// @param[in] maxAmmo Maximum number of bullets this gun can have.
    /// @param[in] fireRatePeriod Minimal time between each shot of the gun.
    /// @param[in] infiniteAmmo If set to true, the gun can always shoot.
    /// @param[in] doubleBullets Whether the gun should shoot double bullets.
    CGun(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
         bool infiniteAmmo = false, bool doubleBullets = false);
    
    /// Virtual destructor since this is a polymorphic base class.
    virtual ~CGun();
    
    /// @return A new pointer to instance of a non-abstract child of CGun.
    [[nodiscard]] virtual std::shared_ptr<CGun> clone() const = 0;
    
    /// Pure virtual method that children of this class implement in their own way so
    /// the different types of guns shoot in different way.
    /// @param[in, out] bullets List of bullets in the game so the gun can add a bullet into in.
    /// @param[in, out] bulletMap CMap containing bullet objects in the game so the gun can add a bullet into in.
    /// @param[in, out] positionOfShooting Position where the entity holding the gun currently is.
    /// @param[in, out] vOrientation VERTICAL orientation of entity holding the gun.
    /// @param[in, out] hOrientation HORIZONTAL orientation of entity holding the gun.
    virtual void shoot(std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap,
                       const CPosition& positionOfShooting, const CMapJoin& environment,
                       VOrientation::EVOrientation vOrientation,
                       HOrientation::EHOrientation hOrientation) = 0;
    
    /// Reloads gun - meaning its magazine will be set to maximum.
    void reload();
    
    /// Updates the internal state of the gun - whether it can shoot again or not.
    void update();
    
    /// @return Name of the gun.
    [[nodiscard]] const std::string& name() const;
    
    /// Whether gun should shoot double bullets.
    bool m_DoubleBullets;
    
    /// Whether gun has infinite ammo or not (meaning it can shoot indefinitely).
    bool m_InfiniteAmmo;
    
    /// Number of bullets in the guns magazine. Gets decremented with each shot.
    int m_Ammo;
protected:
    
    /// Helper method that handles whether gun can shoot or not.
    /// Checking: state of the magazine, if minimum time between each shot has passed
    /// or if the gun is set to have infinite ammo.
    [[nodiscard]] bool can_shoot() const;
    
    /// Helper method that creates a bullet and puts it into game containers if it was successful.
    /// For example if the new bullet collides with its environment right away, it will
    /// just collide with it and not get added to containers.
    /// @param[out] bullets List of bullets that this method can add a bullet into.
    /// @param[in] bulletMap Pointer to a map that contains bullet objects so it can be
    ///                      updated in the case the bullet gets spawned.
    /// @param[in] positionOfShooting Position where the bullet should spawn.
    /// @param[in, out] environment Map of objects that can be effected by the new spawned bullet.
    /// @param[in] vOrientation VERTICAL orientation that the spawned bullet should have.
    /// @param[in] hOrientation HORIZONTAL orientation that the spawned bullet should have.
    void spawn_bullet(std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap,
                      const CPosition& positionOfShooting, const CMapJoin& environment,
                      VOrientation::EVOrientation vOrientation,
                      HOrientation::EHOrientation hOrientation) const;
    
    /// Helper method that is supposed to be called whenever the gun wants to register shooting.
    /// It represents decrementing the amount of bullets in the magazine.
    /// @param[in] howManyTimes The number of bullets the gun has shot out.
    void decrement_ammo(int howManyTimes = 1);
    
    /// Builder that creates bullets this gun shoots.
    CBulletObjectBuilder m_BulletBuilder;
    
    /// CTimeTicks object for checking the fire rate of the gun.
    CTimeTicks m_FireRateTicks;
    
    /// Name of the gun.
    std::string m_Name;
    
    /// Gun's maximum ammo in the magazine.
    int m_MaxAmmo;
    
};
