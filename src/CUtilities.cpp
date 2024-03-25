#include "CUtilities.h"

std::unordered_map<Direction::EDirection, Action::EAction> CUtilities::m_ActionFromDirection = {
        {Direction::UP,    Action::MOVE_UP},
        {Direction::LEFT,  Action::MOVE_LEFT},
        {Direction::RIGHT, Action::MOVE_RIGHT},
        {Direction::DOWN,  Action::MOVE_DOWN},
};

std::unordered_map<Action::EAction, Direction::EDirection> CUtilities::m_DirectionFromAction = {
        {Action::MOVE_UP,    Direction::UP},
        {Action::MOVE_DOWN,  Direction::DOWN},
        {Action::MOVE_RIGHT, Direction::RIGHT},
        {Action::MOVE_LEFT,  Direction::LEFT}
};

Action::EAction CUtilities::action_from_direction(Direction::EDirection direction) {
    auto candidate = m_ActionFromDirection.find(direction);
    if (candidate == m_ActionFromDirection.end())
        return Action::NO_ACTION;
    return candidate->second;
}

Direction::EDirection CUtilities::direction_from_action(Action::EAction action) {
    auto candidate = m_DirectionFromAction.find(action);
    if (candidate == m_DirectionFromAction.end())
        return Direction::NONE;
    return candidate->second;
}

Direction::EDirection CUtilities::direction_from_vh_orientations(VOrientation::EVOrientation vOrientation,
                                                                 HOrientation::EHOrientation hOrientation) {
    using namespace VOrientation;
    using namespace HOrientation;
    if (vOrientation == MIDDLE) {
        switch (hOrientation) {
            case LEFT:
                return Direction::LEFT;
            case RIGHT:
                return Direction::RIGHT;
            default:
                return Direction::NONE;
        }
    } else {
        switch (vOrientation) {
            case UP:
                return Direction::UP;
            case DOWN:
                return Direction::DOWN;
            default:
                return Direction::NONE;
        }
    }
}

int CUtilities::get_nth_gun_from_action(Action::EAction action) {
    switch (action) {
        case Action::SELECT_FIRST_GUN:
            return 1;
        case Action::SELECT_SECOND_GUN:
            return 2;
        case Action::SELECT_THIRD_GUN:
            return 3;
        case Action::SELECT_FOURTH_GUN:
            return 4;
        case Action::SELECT_FIFTH_GUN:
            return 5;
        case Action::SELECT_SIXTH_GUN:
            return 6;
        case Action::SELECT_SEVENTH_GUN:
            return 7;
        case Action::SELECT_EIGHT_GUN:
            return 8;
        case Action::SELECT_NINTH_GUN:
            return 9;
        default:
            return 0;
    }
}

std::string CUtilities::millis_to_minutes_and_seconds(size_t millis) {
    std::ostringstream stream;
    size_t minutes = (millis / 1000) / 60;
    size_t seconds = (millis / 1000) % 60;
    size_t ms = millis % 1000;
    
    stream << minutes << "m " << seconds << "." << std::setw(3) << std::setfill('0') << ms << "s";
    return stream.str();
}

Direction::EDirection CUtilities::random_direction() {
    return static_cast<Direction::EDirection>(rand() % Direction::EDirection::DIRECTION_COUNT);
}
