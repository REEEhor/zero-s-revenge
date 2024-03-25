#pragma once

#include "CEntityFactory.h"
#include "CBonusFactory.h"

/// @brief Class that stores both factories that can create objects with
///        configuration from file. This class works just as a wrapper
///        around the factories so it is easier to create them and store them.
class CFactory {
public:
    
    /// Constructor of CFactory.
    /// @param[in] config Pointer to config containing loaded values that are used by factories.
    explicit CFactory(const std::shared_ptr<const CConfig>& config);
    
    /// Factory that creates bonuses from config.
    std::shared_ptr<const CBonusFactory> m_BonusFactory;
    
    /// Factory that creates entities from config.
    std::shared_ptr<const CEntityFactory> m_EntityFactory;
    
};
