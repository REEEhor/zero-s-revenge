#include "CBonusObject.h"

CBonusObject::CBonusObject(const CPosition& position, int maxHeathPoints, const CBonus& bonus)
        : CObject(position, maxHeathPoints, bonus.m_Sprite, true), m_Bonus(bonus.clone()) {}

CBonusObject& CBonusObject::operator=(const CBonusObject& other) {
    if (this == &other) return *this;
    CObject::operator=(other);
    m_Bonus = other.m_Bonus->clone();
    return *this;
}

CBonusObject::CBonusObject(const CBonusObject& other)
        : CObject(other), m_Bonus(other.m_Bonus->clone()) {}

std::shared_ptr<CObject> CBonusObject::clone() const {
    return std::make_shared<CBonusObject>(*this);
}

