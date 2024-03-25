#include "CDamagingMovableObject.h"

CDamagingMovableObject::CDamagingMovableObject(const CPosition& position, int maxHeathPoints,
                                               const CVisualBlock& sprite, int damage,
                                               bool canBeSteppedOn)
        : CMovableObject(position, maxHeathPoints, sprite, canBeSteppedOn), m_Damage(damage) {}

void CDamagingMovableObject::try_to_move(Direction::EDirection move, const CMapJoin& collidableMap,
                                         const CMapJoin& forbiddenMap) {
    update_sprite(move);
    CPosition newPosition = m_Position + move;
    
    // Try dealing damage into positions at newPosition.
    // We also have to check current position in %collidableMap in case any object stepped on %this.
    // We do not have to do for %forbiddenMap since no object from %forbiddenMap could step onto
    // the same place as %this is.
    if (forbiddenMap.try_dealing_damage_at(m_Damage, newPosition, this) ||
        collidableMap.try_dealing_damage_at(m_Damage, m_Position, this) ||
        collidableMap.try_dealing_damage_at(m_Damage, newPosition, this)) {
        destroy_itself();
        return;
    }
    
    // No collision happened -> move into the new position.
    m_Position = newPosition;
}

CDamagingMovableObject::CDamagingMovableObject(const CPosition& position, int maxHeathPoints,
                                               const std::list<CVisualBlock>& sprites,
                                               bool canBeSteppedOn, int damage)
        : CMovableObject(position, maxHeathPoints, sprites, canBeSteppedOn),
          m_Damage(damage) {}

std::shared_ptr<CObject> CDamagingMovableObject::clone() const {
    return std::make_shared<CDamagingMovableObject>(*this);
}

std::shared_ptr<CMovableObject> CDamagingMovableObject::clone_as_movable() const {
    return std::make_shared<CDamagingMovableObject>(*this);
}
