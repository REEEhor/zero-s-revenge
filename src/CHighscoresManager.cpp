#include "CHighscoresManager.h"

bool CHighscoresManager::load(const std::string& pathToFile) {
    // Try to open the file.
    std::ifstream file(pathToFile);
    if (!file) return false;
    
    // Loading new file -> clear everything that could be
    // stored in internal representation.
    m_Highscores.clear();
    
    // Read each line in the line and try to register the highscores.
    std::string line;
    while (std::getline(file, line) && !line.empty()) {
        std::istringstream stream(line);
        
        std::string name;
        size_t millis;
        if (!(stream >> name) || !(stream >> millis) || !register_score(name, millis)) {
            
            // File could not be loaded properly -> return false.
            m_Highscores.clear(); // Clear internal state to get rid of artefacts.
            return false;
        }
    }
    
    // Report if file is empty or not.
    return !m_Highscores.empty();
}

std::ostream& operator<<(std::ostream& stream, const CHighscoresManager& highscoresManager) {
    int i = 1;
    // Go through all stored highscores and print_stored_value them.
    for (const auto& score: highscoresManager.m_Highscores) {
        stream << std::setw(3) << i++ << ". " << std::setw(10) << score.m_PlayerName << " | "
               << CUtilities::millis_to_minutes_and_seconds(score.m_TimeInMilliseconds) << std::endl;
    }
    return stream;
}

bool CHighscoresManager::register_score(const std::string& playerName, size_t timeInMillis) {
    // Name cannot contain whitespace.
    for (char c: playerName) {
        if (std::isspace(c)) {
            return false;
        }
    }
    
    // Insert new highscore so the %m_Highscores stays sorted.
    CHighscore highscore(playerName, timeInMillis);
    auto it = std::lower_bound(m_Highscores.begin(), m_Highscores.end(), highscore);
    
    m_Highscores.insert(it, highscore);
    return true;
}

bool CHighscoresManager::save(const std::string& pathToFile) {
    // Try to open the file.
    std::ofstream file(pathToFile, std::ofstream::trunc);
    if (!file) return false;
    
    // Go through all highscores and print_stored_value them in a simple format.
    for (const auto& score: m_Highscores) {
        file << score.m_PlayerName << " " << score.m_TimeInMilliseconds << std::endl;
    }
    return true;
}

