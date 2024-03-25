#include "CPosition.h"

CPosition::CPosition(int x, int y)
        : m_X(x), m_Y(y) {}

bool CPosition::operator==(const CPosition& other) const {
    return m_X == other.m_X && m_Y == other.m_Y;
}

bool CPosition::operator<(const CPosition& other) const {
    return std::tie(m_X, m_Y) < std::tie(other.m_X, other.m_Y);
}

CPosition& CPosition::operator+=(Direction::EDirection direction) {
    switch (direction) {
        case Direction::UP:
            this->m_Y--;
            break;
        case Direction::DOWN:
            this->m_Y++;
            break;
        case Direction::LEFT:
            this->m_X--;
            break;
        case Direction::RIGHT:
            this->m_X++;
            break;
        default:
            break;
    }
    return *this;
}

CPosition CPosition::operator+(Direction::EDirection direction) const {
    CPosition result = *this;
    result += direction;
    return result;
}

bool CPosition::operator!=(const CPosition& other) const {
    return !(*this == other);
}

int manhattan_distance(const CPosition& lhs, const CPosition& rhs) {
    return abs(lhs.m_X - rhs.m_X) + abs(lhs.m_Y - rhs.m_Y);
}


