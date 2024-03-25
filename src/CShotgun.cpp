#include "CShotgun.h"

#include <utility>

CShotgun::CShotgun(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
                   bool infiniteAmmo, bool doubleBullets)
        : CGun(std::move(name), bulletBuilder, maxAmmo, fireRatePeriod, infiniteAmmo, doubleBullets) {}

std::shared_ptr<CGun> CShotgun::clone() const {
    return std::make_shared<CShotgun>(*this);
}

void CShotgun::shoot(std::list<CBullet>& bulletControllers, const std::shared_ptr<CMap>& bulletMap,
                     const CPosition& positionOfShooting, const CMapJoin& environment,
                     VOrientation::EVOrientation vOrientation, HOrientation::EHOrientation hOrientation) {
    if (!can_shoot()) return;
    
    Direction::EDirection facingDirection = CUtilities::direction_from_vh_orientations(vOrientation, hOrientation);
    CPosition middlePosition = positionOfShooting + facingDirection;
    CPosition positions[3] = {middlePosition, middlePosition, middlePosition};
    
    switch (facingDirection) {
        case Direction::UP:
        case Direction::DOWN:
            positions[1] += Direction::RIGHT;
            positions[2] += Direction::LEFT;
            break;
        case Direction::LEFT:
        case Direction::RIGHT:
            positions[1] += Direction::UP;
            positions[2] += Direction::DOWN;
            break;
        default:
            break;
    }
    
    for (auto position: positions) {
        spawn_bullet(bulletControllers, bulletMap, position, environment, vOrientation, hOrientation);
    }
    
    decrement_ammo(3);
    m_FireRateTicks.reset();
}
