#pragma once

#include "CGun.h"

/// @brief Class extending CGun by implementing shooting of three bullets next to each other at once
/// (simulating the behaviour of a shotgun).
class CShotgun : public CGun {
public:
    
    /// Constructor of CShotgun.
    /// @param[in] name Name of the gun that should be displayed when player has this gun selected.
    /// @param[in] bulletBuilder Builder object that creates bullets this gun shoots.
    /// @param[in] maxAmmo Maximum number of bullets this gun can have.
    /// @param[in] claymoreSprite How the sprite of placed down claymore should look like.
    /// @param[in] fireRatePeriod Minimal time between each shot of the gun.
    /// @param[in] infiniteAmmo If set to true, the gun can always shoot.
    /// @param[in] doubleBullets Whether the gun should shoot double bullets.
    CShotgun(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
             bool infiniteAmmo = false, bool doubleBullets = false);
    
    /// Shoots three bullet into the direction determined by arguments of this method.
    /// @param[in, out] bullets List of bullets in the game so the gun can add bullets into in.
    /// @param[in, out] bulletMap CMap containing bullet objects in the game so the gun can add bullets into in.
    /// @param[in, out] positionOfShooting Position where the entity holding the gun currently is.
    /// @param[in, out] vOrientation VERTICAL orientation of entity holding the gun.
    /// @param[in, out] hOrientation HORIZONTAL orientation of entity holding the gun.
    void shoot(std::list<CBullet>& bulletControllers, const std::shared_ptr<CMap>& bulletMap,
               const CPosition& positionOfShooting, const CMapJoin& environment,
               VOrientation::EVOrientation vOrientation, HOrientation::EHOrientation hOrientation) override;
    
    /// @return A pointer to a new instance of CShotgun.
    [[nodiscard]] std::shared_ptr<CGun> clone() const override;
};