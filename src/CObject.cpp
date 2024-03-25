#include "CObject.h"


CObject::CObject(const CPosition& position, int maxHeathPoints, CVisualBlock sprite, bool canBeSteppedOn)
        : m_Position(position),
          m_Sprite(std::move(sprite)),
          m_MaxHealthPoints(maxHeathPoints),
          m_HealthPoints(m_MaxHealthPoints),
          m_CanBeSteppedOn(canBeSteppedOn),
          m_DamageTicks(10),
          m_IsHurt(false) {}

CPosition CObject::get_position() const {
    return m_Position;
}

bool CObject::deal_damage(int damagePoints) {
    m_IsHurt = true;
    m_DamageTicks.reset();
    m_HealthPoints -= damagePoints;
    return is_destroyed();
}

CVisualBlock CObject::get_sprite() const {
    if (!m_IsHurt)
        return m_Sprite;
    
    CVisualBlock damagedSprite = m_Sprite;
    damagedSprite.m_BackgroundColor = Color::RED;
    return damagedSprite;
}

bool CObject::is_destroyed() const {
    return m_HealthPoints <= 0;
}

void CObject::destroy_itself() {
    m_HealthPoints = 0;
}

void CObject::update_looks() {
    if (m_DamageTicks.decrement())
        m_IsHurt = false;
}

int CObject::get_health() const {
    return m_HealthPoints;
}

void CObject::heal_object(int healthPoints) {
    m_HealthPoints += healthPoints;
    CUtilities::cap_value_max(m_HealthPoints, m_MaxHealthPoints);
}

bool CObject::can_be_stepped_on() const {
    return m_CanBeSteppedOn;
}

std::shared_ptr<CObject> CObject::clone() const {
    return std::make_shared<CObject>(*this);
}

CObject::~CObject() = default;

