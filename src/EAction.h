#pragma once


/// @brief Enum for different actions CNonStaticEntity can decide to do.
namespace Action {
    enum EAction {
        MOVE_UP = 0,
        MOVE_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        ATTACK,
        SELECT_FIRST_GUN,
        SELECT_SECOND_GUN,
        SELECT_THIRD_GUN,
        SELECT_FOURTH_GUN,
        SELECT_FIFTH_GUN,
        SELECT_SIXTH_GUN,
        SELECT_SEVENTH_GUN,
        SELECT_EIGHT_GUN,
        SELECT_NINTH_GUN,
        NO_ACTION,
        ACTION_COUNT
    };
}