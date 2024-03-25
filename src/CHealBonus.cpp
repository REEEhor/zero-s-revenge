#include "CHealBonus.h"

void CHealBonus::on_start(CPlayer& player) {
    player.get_object()->heal_object(m_HealAmount);
}

CHealBonus::CHealBonus(int probability, CVisualBlock sprite, int healAmount)
        : CBonus(probability, std::move(sprite)), m_HealAmount(healAmount) {}

bool CHealBonus::during(CPlayer& player) {
    return false;
}

void CHealBonus::on_end(CPlayer& player) {}

std::shared_ptr<CBonus> CHealBonus::clone() const {
    return std::make_shared<CHealBonus>(*this);
}

