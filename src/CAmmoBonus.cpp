#include "CAmmoBonus.h"

CAmmoBonus::CAmmoBonus(int probability, CVisualBlock sprite)
        : CBonus(probability, std::move(sprite)) {}
        
void CAmmoBonus::on_start(CPlayer& player) {
    player.current_gun()->reload();
}

bool CAmmoBonus::during(CPlayer& player) {
    // This method does nothing since everything happens
    // in method 'on_start()'
    return false;
}

void CAmmoBonus::on_end(CPlayer& player) {}

std::shared_ptr<CBonus> CAmmoBonus::clone() const {
    return std::make_shared<CAmmoBonus>(*this);
}


