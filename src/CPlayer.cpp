#include "CPlayer.h"

CPlayer::CPlayer()
        : CNonStaticEntity(nullptr), m_CurrentGunId(0) {}

CPlayer::CPlayer(const std::shared_ptr<CMovableObject>& object,
                 const std::shared_ptr<CActionsInputRecorder>& inputRecorder)
        : CNonStaticEntity(object), m_Input(inputRecorder), m_CurrentGunId(0) {}

bool CPlayer::update(const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment,
                     std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap) {
    
    // Update the guns internal state.
    if (number_of_guns() != 0) {
        current_gun()->update();
    }
    
    // Get actions from %m_Input and update the player based on them.
    auto actions = m_Input->pop_actions();
    auto action = Action::NO_ACTION;
    if (!actions.empty()) action = actions[0]; // Only register first input otherwise player could do more actions in one tick.
    
    // Try shooting or selecting different gun.
    if (action == Action::ATTACK && number_of_guns() != 0) {
        current_gun()->shoot(bullets, bulletMap,
                             m_Object->get_position(),
                             environment,
                             m_Object->get_v_orientation(),
                             m_Object->get_h_orientation());
    } else {
        int newSelectedGunId = CUtilities::get_nth_gun_from_action(action);
        if (newSelectedGunId != 0) {
            select_gun(newSelectedGunId - 1);
        }
    }
    
    // Get movement from action and call internal update method.
    Direction::EDirection move = CUtilities::direction_from_action(action);
    return CNonStaticEntity::update(mapContainingObject, environment, move);
}

std::shared_ptr<CGun> CPlayer::current_gun() const {
    return m_Guns[m_CurrentGunId];
}

void CPlayer::add_gun(const CGun& newGun) {
    m_Guns.emplace_back(newGun.clone());
}

void CPlayer::select_gun(int gunId) {
    CUtilities::cap_value(m_CurrentGunId = gunId, 0, number_of_guns() - 1);
}

int CPlayer::number_of_guns() const {
    return static_cast<int>(m_Guns.size());
}
