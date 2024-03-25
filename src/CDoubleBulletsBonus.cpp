#include "CDoubleBulletsBonus.h"

CDoubleBulletsBonus::CDoubleBulletsBonus(int probability, CVisualBlock sprite, int durationOfEffect)
        : CBonus(probability, std::move(sprite), durationOfEffect) {}

void CDoubleBulletsBonus::on_start(CPlayer& player) {
    m_EffectedGun = player.current_gun();
}

bool CDoubleBulletsBonus::during(CPlayer& player) {
    // We need to apply this continuously, since
    // there can be another instance of this bonus that runs
    // out and sets this %m_DoubleBullets to false.
    m_EffectedGun->m_DoubleBullets = true;
    return CBonus::has_time_run_out();
}

void CDoubleBulletsBonus::on_end(CPlayer& player) {
    m_EffectedGun->m_DoubleBullets = false;
}

std::shared_ptr<CBonus> CDoubleBulletsBonus::clone() const {
    return std::make_shared<CDoubleBulletsBonus>(*this);
}
