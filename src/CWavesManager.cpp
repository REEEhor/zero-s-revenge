#include "CWavesManager.h"

void CWavesManager::register_spawn_position(const CPosition& position) {
    m_SpawnPositions.emplace_back(position);
}

void CWavesManager::load(std::istream& stream, const CConfig& config,
                         const std::shared_ptr<const CEntityFactory>& factory) {
    std::string line;
    // Read lines from the %stream and try to parse them into enemy waves.
    while (std::getline(stream, line) && !line.empty()) {
        std::istringstream lineStream(line);
        m_Waves.emplace_back(lineStream, config, factory);
    }
    
    if (m_Waves.empty()) {
        throw std::invalid_argument("no enemy waves loaded");
    }
}

bool CWavesManager::update(std::list<std::shared_ptr<CEnemy>>& enemies, CMap& entityMap) {
    
    /// The waves manager currently tries to spawn enemies.
    if (m_Spawning) {
        // Pop the wave from the list if it has spawned all of its enemies.
        if (!m_Waves.front().spawn(m_SpawnPositions, enemies, entityMap)) {
            m_Waves.pop_front();
            m_Spawning = false;
        }
        return true;
    }
    
    if (!m_Waves.empty() && enemies.empty()) {
        m_Spawning = true;
        return true;
    }
    
    // The game ends in a win if there are no
    // more waves of enemies and all enemies are killed.
    return !m_Waves.empty() || !enemies.empty();
}

CWavesManager::CWavesManager()
        : m_Spawning(true) {}

bool CWavesManager::is_valid() const {
    return !m_SpawnPositions.empty();
}

