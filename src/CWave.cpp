#include "CWave.h"

CWave::CWave(std::istream& stream, const CConfig& config, const std::shared_ptr<const CEntityFactory>& factory) {
    std::string segment;
    // Split stream into segments and try to parse them into wave segments.
    while (std::getline(stream, segment, config.m_Char["WAVE_SEGMENT_SEPARATOR"])) {
        std::istringstream segmentStream(segment);
        m_WaveSegments.emplace_back(segmentStream, factory);
    }
    if (m_WaveSegments.empty()) {
        throw std::invalid_argument("number of wave segments cannot be zero");
    }
}

bool CWave::spawn(const std::vector<CPosition>& spawnPositions,
                  std::list<std::shared_ptr<CEnemy>>& enemies, CMap& entityMap) {
    if (spawnPositions.empty()) {
        return false;
    }
    
    // Pop a segment if it is inactive.
    if (!m_WaveSegments.front().is_active()) {
        m_WaveSegments.pop_front();
        return !m_WaveSegments.empty();
    }
    
    // Pick a random position from %spawnPositions.
    const CPosition& spawnPosition = spawnPositions[rand() % spawnPositions.size()];
    
    // Check if there is no other entity at that position.
    if (entityMap.is_empty_at(spawnPosition)) {
        
        // The spawn position is empty -> spawn an enemy.
        auto enemy = m_WaveSegments.front().spawn_at(spawnPosition);
        enemies.emplace_back(enemy);
        entityMap.add_object(enemies.back()->get_object());
    }
    
    return true;
}
