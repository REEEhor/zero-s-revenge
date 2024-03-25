#pragma once

#include "CBonus.h"
#include "CHealBonus.h"
#include "CAmmoBonus.h"
#include "CBonusObject.h"
#include "CDoubleBulletsBonus.h"
#include "CMap.h"
#include "CPlayer.h"
#include "CConfig.h"
#include "EToughness.h"
#include "CBonusFactory.h"
#include <list>
#include <optional>


/// @brief Class managing the state of the bonuses in the game.
///        For example: registering if player has picked up a bonus or putting bonus object in the game when it drops from a killed enemy.
class CBonusManager {
public:
    
    /// Constructor of CBonusManger.
    /// @param[in] factory Pointer for factory object so it can create bonuses using the factory.
    explicit CBonusManager(const std::shared_ptr<const CBonusFactory>& factory);
    
    /// Method that should be called when an enemy dies.
    /// It checks the toughness of the killed enemy and uses it to determine the type of bonus that could be dropped.
    /// In case the bonus is dropped, its physical representation is put in %bonusObjectMap.
    /// @param[in] position Position that the enemy died at.
    /// @param[in] toughness Toughness of the killed enemy.
    /// @param[in, out] bonusObjectMap Map that the object can be added into.
    void maybe_generate_new_bonus_object(const CPosition& position,
                                         Toughness::EToughness toughness, CMap& bonusObjectMap);
    
    /// Updates the state of all bonuses. Meaning:
    /// - checks for collision of dropped bonuses with player.
    /// - updates all bonuses that are currently effecting player.
    /// @param [in, out] player Player that is supposed to be effected by bonuses.
    /// @param [in, out] bonusMap Map that contains bonus objects.
    void update(CPlayer& player, CMap& bonusMap);
private:
    
    /// Updates all bonuses that are currently effecting the player.
    /// @param [out] player Player that will get effected by active bonuses.
    void update_active_bonuses(CPlayer& player);
    
    /// List of all bonuses that are active - currently effecting the player.
    std::list<std::shared_ptr<CBonus>> m_Bonuses;
    
    // List of bonus objects that are dropped from enemies.
    std::list<std::shared_ptr<CBonusObject>> m_BonusObjects;
    
    // Factory for creating a bonuses.
    std::shared_ptr<const CBonusFactory> m_Factory;
};
