#include "CCollidingMovableObject.h"

void CCollidingMovableObject::try_to_move(Direction::EDirection move, const CMapJoin& collidableMap,
                                          const CMapJoin& forbiddenMap) {
    update_sprite(move);
    
    // Get new position and check for collisions.
    CPosition newPosition = m_Position + move;
    if (forbiddenMap.is_empty_at(newPosition) && collidableMap.can_be_stepped_on(newPosition)) {
        m_Position = newPosition; // It is ok to move into %newPosition -> set new position.
    }
}

CCollidingMovableObject::CCollidingMovableObject(const CPosition& position, int maxHeathPoints,
                                                 const CVisualBlock& sprite,
                                                 bool canBeSteppedOn)
        : CMovableObject(position, maxHeathPoints, sprite, canBeSteppedOn) {}

CCollidingMovableObject::CCollidingMovableObject(const CPosition& position, int maxHeathPoints,
                                                 const std::list<CVisualBlock>& sprites,
                                                 bool canBeSteppedOn) : CMovableObject(
        position, maxHeathPoints, sprites, canBeSteppedOn) {}

std::shared_ptr<CObject> CCollidingMovableObject::clone() const {
    return std::make_shared<CCollidingMovableObject>(*this);
}

std::shared_ptr<CMovableObject> CCollidingMovableObject::clone_as_movable() const {
    return std::make_shared<CCollidingMovableObject>(*this);
}

