#include "CPistol.h"

CPistol::CPistol(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
                 bool infiniteAmmo, bool doubleBullets)
        : CGun(std::move(name), bulletBuilder, maxAmmo, fireRatePeriod, infiniteAmmo, doubleBullets) {}

void CPistol::shoot(std::list<CBullet>& bulletControllers, const std::shared_ptr<CMap>& bulletMap,
                    const CPosition& positionOfShooting, const CMapJoin& environment,
                    VOrientation::EVOrientation vOrientation,
                    HOrientation::EHOrientation hOrientation) {
    if (!can_shoot()) return;
    
    // Get the direction the bullet should fly in and use internal 'CGun::spawn_bullet()' to shoot.
    Direction::EDirection facingDirection = CUtilities::direction_from_vh_orientations(vOrientation, hOrientation);
    spawn_bullet(bulletControllers, bulletMap, positionOfShooting + facingDirection,
                 environment, vOrientation, hOrientation);
    
    decrement_ammo();
    m_FireRateTicks.reset();
}

std::shared_ptr<CGun> CPistol::clone() const {
    return std::make_shared<CPistol>(*this);
}

