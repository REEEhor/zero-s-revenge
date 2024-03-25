#include "CIndestructibleObject.h"

bool CIndestructibleObject::deal_damage(int damagePoints) {
    return false;
}

CIndestructibleObject::CIndestructibleObject(const CPosition& position, const CVisualBlock& sprite, bool canBeSteppedOn)
        : CObject(position, 1, sprite, canBeSteppedOn) {}

bool CIndestructibleObject::is_destroyed() const {
    return false;
}

std::shared_ptr<CObject> CIndestructibleObject::clone() const {
    return std::make_shared<CIndestructibleObject>(*this);
}
