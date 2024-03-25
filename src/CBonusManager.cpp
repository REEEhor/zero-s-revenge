#include "CBonusManager.h"

CBonusManager::CBonusManager(const std::shared_ptr<const CBonusFactory>& factory)
        : m_Factory(factory) {}

void CBonusManager::update(CPlayer& player, CMap& bonusMap) {
    
    // Update all bonus objects that have been dropped from enemies.
    for (auto it = m_BonusObjects.begin(); it != m_BonusObjects.end();) {
        
        if ((**it).is_destroyed()) {
            // If the object got somehow destroyed, we no longer need to store it.
            it = m_BonusObjects.erase(it);
            
        } else if ((**it).get_position() == player.get_object()->get_position()) {
            // The object is at the same position as player
            // Move bonus from bonus object into active bonuses.
            m_Bonuses.emplace_back((**it).m_Bonus);
            // Call its initial method.
            m_Bonuses.back()->on_start(player);
            
            // Erase the bonus object from the CMap and dropped bonus objects.
            bonusMap.erase_object(*it);
            it = m_BonusObjects.erase(it);
            
        } else {
            ++it;
        }
    }
    
    // Update all bonuses that are currently effecting the player.
    update_active_bonuses(player);
}

void CBonusManager::update_active_bonuses(CPlayer& player) {
    // Update all bonuses that are currently effecting the player and remove them
    // from the list of active bonuses if their effect has run out.
    for (auto it = m_Bonuses.begin(); it != m_Bonuses.end();) {
        if ((**it).during(player)) {
            ++it;
        } else {
            // Effect of the bonus has run out -> call its final method and erase it.
            (**it).on_end(player);
            it = m_Bonuses.erase(it);
        }
    }
}

void CBonusManager::maybe_generate_new_bonus_object(const CPosition& position,
                                                    Toughness::EToughness toughness,
                                                    CMap& bonusObjectMap) {
    // Check if an object can be put into position of killed enemy.
    if (!bonusObjectMap.is_empty_at(position)) return;
    
    // Get std::optional bonus object determined by the factory.
    auto bonus = m_Factory->bonus_from_toughness_at(toughness, position);
    
    // std::optional returns false means the object did not get generated (bad luck or the toughness was too low).
    if (!bonus) return;
    
    // Bonus has been generated -> create its physical form (%bonusObject)
    // and put it in corresponding containers.
    auto bonusObject = std::make_shared<CBonusObject>(bonus.value());
    m_BonusObjects.emplace_back(bonusObject);
    bonusObjectMap.add_object(m_BonusObjects.back());
}


