#include "CWaveSegment.h"

CWaveSegment::CWaveSegment(std::istream& stream, const std::shared_ptr<const CEntityFactory>& factory)
        : m_Factory(factory), m_ChargedStrength(-1), m_ChargedEnemy(false) {
    
    // Try reading the number of enemies to spawn.
    if (!(stream >> m_NumberOfEnemies)) {
        throw std::invalid_argument("could not read number of enemies");
    }
    
    if (m_NumberOfEnemies <= 0) {
        throw std::invalid_argument("cannot have non-positive number of enemies");
    }
    
    // Try reading the enemy symbol
    std::string enemySymbol;
    if (!(stream >> enemySymbol)) {
        throw std::invalid_argument("could not read enemy symbol");
    }
    
    switch (enemySymbol.length()) {
        case 1:
            // Single char => non charged enemy.
            m_NonChargedSymbol = enemySymbol[0];
            if (!m_Factory->can_create_enemy_with_symbol(m_NonChargedSymbol)) {
                throw std::invalid_argument("invalid non-charged enemy symbol");
            }
            break;
        case 2:
            // Two digit number => charged enemy.
            m_ChargedStrength = std::stoi(enemySymbol);
            if (!CUtilities::is_in_range(m_ChargedStrength, 10, 99)) {
                throw std::invalid_argument("invalid charged enemy symbol");
            }
            m_ChargedEnemy = true;
            break;
        default:
            throw std::invalid_argument("invalid enemy symbol");
    }
}

std::shared_ptr<CEnemy> CWaveSegment::spawn_at(const CPosition& position) {
    m_NumberOfEnemies--;
    if (m_ChargedEnemy)
        return m_Factory->create_charged_enemy(position, m_ChargedStrength);
    else
        return m_Factory->create_enemy(position, m_NonChargedSymbol);
}

bool CWaveSegment::is_active() const {
    return (m_NumberOfEnemies > 0);
}
