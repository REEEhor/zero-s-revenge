#include "CNonStaticEntity.h"

bool CNonStaticEntity::update(const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment,
                              Direction::EDirection move) {
    // Check if the object is destroyed
    if (m_Object->is_destroyed()) {
        // Erase it from the CMap if was not done from the outside
        // (meaning the object was destroyed by external factors, so it got erased automatically).
        mapContainingObject->erase_object(m_Object);
        return false;
    }
    
    // Give movement to object and update its position.
    CPosition prevPosition = m_Object->get_position();
    m_Object->try_to_move(move, environment, {mapContainingObject});
    mapContainingObject->update_position_of_object_at(prevPosition);
    return true;
}

CNonStaticEntity::CNonStaticEntity(const std::shared_ptr<CMovableObject>& object)
        : m_Object(object) {}

std::shared_ptr<CMovableObject> CNonStaticEntity::get_object() const {
    return m_Object;
}

CNonStaticEntity::CNonStaticEntity(const CNonStaticEntity& other)
        : m_Object(other.m_Object->clone_as_movable()) {}

CNonStaticEntity& CNonStaticEntity::operator=(const CNonStaticEntity& other) {
    if (this == &other) return *this;
    m_Object = other.m_Object;
    return *this;
}

CNonStaticEntity::~CNonStaticEntity() = default;


