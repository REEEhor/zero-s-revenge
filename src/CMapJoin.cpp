#include "CMapJoin.h"

CMapJoin::CMapJoin(std::initializer_list<std::shared_ptr<CMap>> maps)
        : m_Maps(maps) {}

bool CMapJoin::can_be_stepped_on(const CPosition& position) const {
    for (auto& map: m_Maps) {
        if (!map->can_be_stepped_on(position)) return false;
    }
    return true;
}

bool CMapJoin::is_empty_at(const CPosition& position) const {
    for (auto& map: m_Maps) {
        if (!map->is_empty_at(position)) return false;
    }
    return true;
}

bool CMapJoin::try_dealing_damage_at(int damagePoints, const CPosition& position, const CObject* exception) const {
    bool wasDamageDealt = false;
    for (auto& map: m_Maps) {
        if (map->try_dealing_damage_at(damagePoints, position, exception))
            wasDamageDealt = true;
    }
    return wasDamageDealt;
}

