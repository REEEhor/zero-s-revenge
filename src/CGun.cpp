#include "CGun.h"

CGun::CGun(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
           bool infiniteAmmo, bool doubleBullets)
        : m_DoubleBullets(doubleBullets),
          m_InfiniteAmmo(infiniteAmmo),
          m_Ammo((infiniteAmmo ? -1 : 0)), // Ammo set to -1 indicates the gun has infinite ammo
          m_BulletBuilder(bulletBuilder),
          m_FireRateTicks(fireRatePeriod),
          m_Name(std::move(name)),
          m_MaxAmmo(maxAmmo) {}

void CGun::spawn_bullet(std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap,
                        const CPosition& positionOfShooting, const CMapJoin& environment,
                        VOrientation::EVOrientation vOrientation, HOrientation::EHOrientation hOrientation) const {
    
    // Create a bullet object.
    std::shared_ptr<CMovableObject> bullet =
            m_BulletBuilder.build_bullet(positionOfShooting, vOrientation, hOrientation, m_DoubleBullets);
    
    // Try how the bullet behaves if it was put into environment.
    bullet->try_to_move(Direction::NONE, {environment}, {bulletMap});
    if (!bullet->is_destroyed()) {
        
        // Bullet did not get destroyed -> add it to the bullets into containers.
        bullets.emplace_back(bullet,
                             CUtilities::direction_from_vh_orientations(vOrientation, hOrientation),
                             m_BulletBuilder.get_move_period());
        bulletMap->add_object(bullet);
    }
}

void CGun::reload() {
    m_Ammo = m_MaxAmmo;
}

bool CGun::can_shoot() const {
    // Gun can shoot only if it has available ammo and
    // if it was long enough from the previous shot.
    return (m_Ammo > 0 || m_InfiniteAmmo) && m_FireRateTicks.time_ran_out();
}

void CGun::update() {
    m_FireRateTicks.update();
}

void CGun::decrement_ammo(int howManyTimes) {
    // Gun has infinite ammo -> nothing to do.
    if (m_InfiniteAmmo) return;
    
    m_Ammo -= howManyTimes;
    CUtilities::cap_value_min(m_Ammo, 0);
}

const std::string& CGun::name() const {
    return m_Name;
}

CGun::~CGun() = default;
