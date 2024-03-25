#include "CMap.h"

CMap::CMap() = default;

CMap::CMap(std::initializer_list<std::shared_ptr<CObject>> objects) {
    for (const auto& object: objects)
        add_object(object);
}

CMap& CMap::add_object(const std::shared_ptr<CObject>& object) {
    m_Map[object->get_position()] = object;
    return *this;
}

bool CMap::can_be_stepped_on(const CPosition& position) const {
    auto candidateIt = m_Map.find(position);
    return candidateIt == m_Map.end() || candidateIt->second->can_be_stepped_on();
}

void CMap::update_position_of_object_at(const CPosition& position) {
    std::shared_ptr<CObject> object = m_Map.at(position);
    if (object->get_position() != position) {
        m_Map.erase(position);
        add_object(object);
    }
}

bool CMap::erase_object_at(const CPosition& position) {
    return m_Map.erase(position);
}

void CMap::erase_object(const std::shared_ptr<CObject>& object) {
    auto it = m_Map.find(object->get_position());
    if (it != m_Map.end() && it->second == object) {
        erase_object_at(object->get_position());
    }
}

void CMap::push_objects_to_render(CRenderer& renderer) const {
    for (const auto& [key, object]: m_Map)
        renderer.prepare_to_render(*object);
}

bool CMap::is_empty_at(const CPosition& position) const {
    return m_Map.find(position) == m_Map.end();
}

bool CMap::try_dealing_damage_at(int damagePoints, const CPosition& position, const CObject* exception) {
    auto candidateIt = m_Map.find(position);
    if (candidateIt == m_Map.end() || candidateIt->second.get() == exception)
        return false;
    if (candidateIt->second->deal_damage(damagePoints))
        erase_object(candidateIt->second);
    return true;
}

void CMap::update_looks_all_objects() {
    for (auto& object : m_Map)
        object.second->update_looks();
}



