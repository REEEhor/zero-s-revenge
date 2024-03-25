#pragma once

#include "CMap.h"
#include <memory>
#include <list>

/// @brief Class that enables joining multiple instances CMap pointers to one and
///        calling some methods on all of them at once.
class CMapJoin {
public:
    
    /// Constructor of CMapJoin.
    /// @param[in] maps List of CMaps that we are supposed to be stored in CMapJoin.
    CMapJoin(std::initializer_list<std::shared_ptr<CMap>> maps);
    
    /// Method for calling 'can_be_stepped_on()' on all CMaps.
    /// @return True if any of the maps return true to their 'can_be_stepped_on()' method.
    ///         Otherwise false.
    [[nodiscard]] bool can_be_stepped_on(const CPosition& position) const;
    
    /// Method for calling 'is_empty_at()' on all CMaps.
    /// @return True if any of the maps return true to their 'is_empty_at()' method.
    ///         Otherwise false.
    [[nodiscard]] bool is_empty_at(const CPosition& position) const;
    
    /// Method for calling 'try_dealing_damage_at()' on all CMaps.
    /// @return True if any of the maps return true to their 'try_dealing_damage_at()' method.
    ///         Otherwise false.
    bool try_dealing_damage_at(int damagePoints, const CPosition& position, const CObject* exception = nullptr) const;

private:
    
    /// List of pointers to CMaps stored in this CMapJoin.
    std::list<std::shared_ptr<CMap>> m_Maps;
};
