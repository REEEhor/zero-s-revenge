#pragma once

#include "CGun.h"
#include "CVisualBlock.h"
#include <utility>

/// @brief Class extending CGun by implementing a system, where entity places a 'claymore', that
///        will explode (shoot bullets in all directions) when the entity tries to shoot.
class CClaymore : public CGun {
public:
    
    /// Constructor of CClaymore.
    /// @param[in] name Name of the gun that should be displayed when player has this gun selected.
    /// @param[in] bulletBuilder Builder object that creates bullets this gun shoots.
    /// @param[in] maxAmmo Maximum number of bullets this gun can have.
    /// @param[in] claymoreSprite How the sprite of placed down claymore should look like.
    /// @param[in] fireRatePeriod Minimal time between each shot of the gun.
    /// @param[in] infiniteAmmo If set to true, the gun can always shoot.
    /// @param[in] doubleBullets Whether the gun should shoot double bullets.
    CClaymore(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
              CVisualBlock claymoreSprite, bool infiniteAmmo = false, bool doubleBullets = false);
    
    /// If the CClaymore does not have a registered claymore, it will place one.
    /// Otherwise it will make the registered claymore explode.
    /// @param[in, out] bullets List of bullets in the game so the gun can add a bullet into in.
    /// @param[in, out] bulletMap CMap containing bullet objects in the game so the gun can add a bullet into in.
    /// @param[in, out] positionOfShooting Position where the entity holding the gun currently is.
    /// @param[in, out] vOrientation VERTICAL orientation of entity holding the gun.
    /// @param[in, out] hOrientation HORIZONTAL orientation of entity holding the gun.
    void shoot(std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap,
               const CPosition& positionOfShooting, const CMapJoin& environment,
               VOrientation::EVOrientation vOrientation, HOrientation::EHOrientation hOrientation) override;
    
    /// @return A pointer to a new instance of CPistol.
    [[nodiscard]] std::shared_ptr<CGun> clone() const override;
    
    /// Copy constructor since this class has a pointer to an object.
    CClaymore(const CClaymore& other);
    
    /// Copy operator= since this class has a pointer to an object.
    CClaymore& operator=(const CClaymore& other);

private:
    
    /// Internal method that explodes current claymore at its position.
    /// @param[out] bullets List of bullets in the game so the gun can add bullets into it.
    /// @param[out] bulletMap Map of bullet object in the game so the gun can add bullet objects into it.
    /// @param[in, out] environment Map of objects that bullets can interact with.
    void explode_claymore(std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap,
                          const CMapJoin& environment);
    
    
    /// Pointer to a placed claymore.
    std::shared_ptr<CObject> m_Claymore;
    
    /// Visual looks of the placed down claymore.
    CVisualBlock m_ClaymoreSprite;
    
    /// Whether a new claymore should be place or not.
    bool m_Place;
};
