#include "CClaymore.h"


CClaymore::CClaymore(std::string name, const CBulletObjectBuilder& bulletBuilder, int maxAmmo, int fireRatePeriod,
                     CVisualBlock claymoreSprite, bool infiniteAmmo, bool doubleBullets)
        : CGun(std::move(name), bulletBuilder, maxAmmo, fireRatePeriod, infiniteAmmo, doubleBullets),
          m_Claymore(nullptr),
          m_ClaymoreSprite(std::move(claymoreSprite)), m_Place(true) {}


void CClaymore::shoot(std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap,
                      const CPosition& positionOfShooting, const CMapJoin& environment,
                      VOrientation::EVOrientation vOrientation, HOrientation::EHOrientation hOrientation) {
    if (!CGun::can_shoot()) return;
    
    // Check if claymore should be placed or if the stored one is destroyed.
    // If so, place a new one.
    if (m_Place || m_Claymore == nullptr || m_Claymore->is_destroyed()) {
        Direction::EDirection facingDirection = CUtilities::direction_from_vh_orientations(vOrientation, hOrientation);
        CPosition placement = positionOfShooting + facingDirection;
        
        if (!bulletMap->is_empty_at(placement)) return;
        if (!environment.is_empty_at(placement)) return;
        m_Place = false;
        m_Claymore = std::make_shared<CObject>(placement,
                                               1,
                                               m_ClaymoreSprite,
                                               true);
        bulletMap->add_object(m_Claymore);
        decrement_ammo();
        return;
    }
    
    explode_claymore(bullets, bulletMap, environment);
}


std::shared_ptr<CGun> CClaymore::clone() const {
    return std::make_shared<CClaymore>(*this);
}

CClaymore::CClaymore(const CClaymore& other)
        : CGun(other), m_Claymore(nullptr), m_ClaymoreSprite(other.m_ClaymoreSprite), m_Place(false) {}

CClaymore& CClaymore::operator=(const CClaymore& other) {
    if (this == &other) return *this;
    m_Place = false;
    m_ClaymoreSprite = other.m_ClaymoreSprite;
    m_Claymore = nullptr;
    return *this;
}

void CClaymore::explode_claymore(std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap,
                                 const CMapJoin& environment) {
    if (m_Claymore == nullptr) return;
    
    // Erase claymore object from map of bullets.
    bulletMap->erase_object(m_Claymore);
    m_Place = true;
    
    // Shoot in all directions around claymore.
    CGun::spawn_bullet(bullets, bulletMap,
                       m_Claymore->get_position() + Direction::RIGHT,
                       environment,
                       VOrientation::MIDDLE,
                       HOrientation::RIGHT);
    CGun::spawn_bullet(bullets, bulletMap,
                       m_Claymore->get_position() + Direction::UP,
                       environment,
                       VOrientation::UP,
                       HOrientation::RIGHT);
    CGun::spawn_bullet(bullets, bulletMap,
                       m_Claymore->get_position() + Direction::DOWN,
                       environment,
                       VOrientation::DOWN,
                       HOrientation::LEFT);
    CGun::spawn_bullet(bullets, bulletMap,
                       m_Claymore->get_position() + Direction::LEFT,
                       environment,
                       VOrientation::MIDDLE,
                       HOrientation::LEFT);
    m_FireRateTicks.reset();
}


