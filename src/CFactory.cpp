#include "CFactory.h"
#include "CConfigRegister.h"

CFactory::CFactory(const std::shared_ptr<const CConfig>& config)
        : m_BonusFactory(std::make_shared<CBonusFactory>(config)),
          m_EntityFactory(std::make_shared<CEntityFactory>(config)) {}
