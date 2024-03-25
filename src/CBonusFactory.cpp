#include "CBonusFactory.h"

CBonusFactory::CBonusFactory(const std::shared_ptr<const CConfig>& config)
        : m_Config(config) { load_bonuses(); }

void CBonusFactory::load_bonuses() {
    std::string bonusName;
    
    // Load all heal bonuses.
    bonusName = "HEAL";
    load_bonus(bonusName, create_heal_bonus(bonusName));
    bonusName = "HEAL_PLUS";
    
    // Load all ammo bonuses.
    load_bonus(bonusName, create_heal_bonus(bonusName));
    bonusName = "AMMO";
    
    // Load all double bullets bonuses.
    load_bonus(bonusName, create_ammo_bonus(bonusName));
    bonusName = "DOUBLE_BULLETS";
    load_bonus(bonusName, create_double_bullets_bonus(bonusName));
}

void CBonusFactory::load_bonus(const std::string& bonusName, const std::shared_ptr<CBonus>& bonus) {
    using namespace Toughness;
    EToughness bonusToughness = get_bonus_toughness(bonusName);
    if (bonusToughness != NONE) {
        m_Bonuses[bonusToughness].emplace_back(bonus->clone());
    }
}

std::shared_ptr<CBonus> CBonusFactory::create_heal_bonus(const std::string& bonusName) const {
    int healAmount = m_Config->m_Int[bonusName + "_BONUS_HP_AMOUNT"];
    int probability = get_bonus_probability(bonusName);
    CVisualBlock sprite = get_bonus_sprite(bonusName);
    return std::make_shared<CHealBonus>(probability, sprite, healAmount);
}

std::shared_ptr<CBonus> CBonusFactory::create_double_bullets_bonus(const std::string& bonusName) const {
    int duration = m_Config->m_Int[bonusName + "_BONUS_DURATION"];
    int probability = get_bonus_probability(bonusName);
    CVisualBlock sprite = get_bonus_sprite(bonusName);
    return std::make_shared<CDoubleBulletsBonus>(probability, sprite, duration);
}

std::shared_ptr<CBonus> CBonusFactory::create_ammo_bonus(const std::string& bonusName) const {
    int probability = get_bonus_probability(bonusName);
    CVisualBlock sprite = get_bonus_sprite(bonusName);
    return std::make_shared<CAmmoBonus>(probability, sprite);
}

Toughness::EToughness CBonusFactory::get_bonus_toughness(const std::string& bonusName) const {
    return m_Config->m_Toughness[bonusName + "_BONUS_TOUGHNESS"];
}

CVisualBlock CBonusFactory::get_bonus_sprite(const std::string& bonusName) const {
    return m_Config->m_CVisualBlock[bonusName + "_BONUS_SPRITE"];
}

int CBonusFactory::get_bonus_probability(const std::string& bonusName) const {
    return m_Config->m_Int[bonusName + "_BONUS_PROBABILITY"];
}

std::optional<CBonusObject> CBonusFactory::bonus_from_toughness_at(Toughness::EToughness toughness,
                                                                   const CPosition& position) const {
    using namespace Toughness;
    
    // If the toughness is NONE, no bonus will be dropped.
    if (toughness == NONE) {
        return {};
    }
    
    // Find which category (toughness) we are dealing with.
    auto it = m_Bonuses.find(toughness);
    if (it == m_Bonuses.end() || it->second.empty()) {
        return {}; // No bonus is assigned to %toughness.
    }
    
    // Randomly determine which bonus should be picked.
    std::vector<std::shared_ptr<CBonus>> bonuses = it->second;
    std::shared_ptr<CBonus> bonus = bonuses[rand() % bonuses.size()];
    
    // See if it gets generated.
    if (bonus->m_Probability <= rand() % 100) {
        return {};
    }
    
    return {CBonusObject(position, 1, *bonus)};
}

