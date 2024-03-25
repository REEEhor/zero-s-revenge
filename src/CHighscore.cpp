#include "CHighscore.h"

CHighscore::CHighscore(std::string playerName, size_t timeInMillis)
        : m_PlayerName(std::move(playerName)), m_TimeInMilliseconds(timeInMillis) {}

bool CHighscore::operator<(const CHighscore& other) const {
    return std::tie(m_TimeInMilliseconds, m_PlayerName)
           < std::tie(other.m_TimeInMilliseconds, other.m_PlayerName);
}
