#pragma once

#include "CGun.h"

/// @brief Class extending CGun by implementing a gun that places stationary mines that hurt entities when they walk on it.
class CMinePlacer : public CGun {
public:
    
    /// Constructor of CMinePlacer.
    /// @param[in] name Name of the gun that should be displayed when player has this gun selected.
    /// @param[in] bulletBuilder Builder object that creates bullets this gun shoots.
    /// @param[in] maxAmmo Maximum number of bullets this gun can have.
    /// @param[in] fireRatePeriod Minimal time between each shot of the gun.
    /// @param[in] infiniteAmmo If set to true, the gun can always shoot.
    /// @param[in] doubleBullets Whether the gun should shoot double bullets.
    CMinePlacer(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
                bool infiniteAmmo = false, bool doubleBullets = false);
    
    /// Places mine (stationary bullet).
    /// @param[in, out] bullets List of bullets in the game so the mine placer can add the mine into in.
    /// @param[in, out] bulletMap CMap containing bullet objects in the game so the mine placer can add the mine into in.
    /// @param[in, out] positionOfShooting Position where the entity holding the mine placer currently is.
    /// @param[in, out] vOrientation VERTICAL orientation of entity holding the mine placer.
    /// @param[in, out] hOrientation HORIZONTAL orientation of entity holding the mine placer.
    void shoot(std::list<CBullet>& bulletControllers, const std::shared_ptr<CMap>& bulletMap,
               const CPosition& positionOfShooting, const CMapJoin& environment,
               VOrientation::EVOrientation vOrientation, HOrientation::EHOrientation hOrientation) override;
    
    /// @return A new pointer to instance of CMinePlacer.
    [[nodiscard]] std::shared_ptr<CGun> clone() const override;
};
