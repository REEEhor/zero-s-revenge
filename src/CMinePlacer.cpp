#include "CMinePlacer.h"

#include <utility>

CMinePlacer::CMinePlacer(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
                         bool infiniteAmmo, bool doubleBullets)
        : CGun(std::move(name), bulletBuilder, maxAmmo, fireRatePeriod, infiniteAmmo, doubleBullets) {}

void CMinePlacer::shoot(std::list<CBullet>& bulletControllers, const std::shared_ptr<CMap>& bulletMap,
                        const CPosition& positionOfShooting, const CMapJoin& environment,
                        VOrientation::EVOrientation vOrientation, HOrientation::EHOrientation hOrientation) {
    if (!can_shoot()) return;
    
    // This class does not use 'CGun::spawn_bullet()' method because it has to check if the place at the new position
    // is empty. This is different to 'CGun::spawn_bullet()' where it tries to damage the environment.
    
    // Generate position where the mine should be placed.
    CPosition minePosition =
            positionOfShooting + CUtilities::direction_from_vh_orientations(vOrientation, hOrientation);
    
    // Check if the supposed mine placement is empty.
    if (!bulletMap->is_empty_at(minePosition)) return;
    if (!environment.can_be_stepped_on(minePosition)) return;
    
    // Add mine to game containers.
    auto bullet =
            m_BulletBuilder.build_bullet(minePosition, vOrientation, hOrientation, m_DoubleBullets);
    bulletMap->add_object(bullet);
    bulletControllers.emplace_back(bullet, Direction::NONE, -1);
    
    decrement_ammo();
    m_FireRateTicks.reset();
}

std::shared_ptr<CGun> CMinePlacer::clone() const {
    return std::make_shared<CMinePlacer>(*this);
}
