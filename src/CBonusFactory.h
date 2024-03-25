#pragma once

#include "CBonusObject.h"
#include "CHealBonus.h"
#include "CDoubleBulletsBonus.h"
#include "CAmmoBonus.h"
#include "CConfig.h"
#include <string>
#include <unordered_map>
#include <optional>

/// @brief Class for creating bonuses that are configured using config file.
class CBonusFactory {
public:
    /// Constructor of CBonusFactory.
    /// @param config Pointer to config that the factory is going to use the bonuses.
    explicit CBonusFactory(const std::shared_ptr<const CConfig>& config);
    
    /// Generates with optional CBonusObject from toughness.
    /// This method should is supposed to be called when an enemy dies and its position and toughness gets
    /// passed into this method. Depending on the configuration the method will return random CBonusObject
    /// that corresponds to the %toughness.
    /// @param[in] toughness Toughness of the killed enemy.
    /// @param[in] position Position where the bonus should be dropped (supposedly the position the enemy died at).
    /// @return If the bonus was decided to be generated, the std::optional will contain an instance of CBonusObject.
    ///         If the bonus was not generated, an empty instance of std::optional<> will be returned.
    [[nodiscard]] std::optional<CBonusObject> bonus_from_toughness_at(Toughness::EToughness toughness,
                                                                      const CPosition& position) const;
private:
    /// Internal method that assign bonuses their toughness in the %m_Bonuses variable.
    void load_bonuses();
    
    /// Creates a pointer to any healing bonus that was loaded in %m_Config.
    /// @param[in] bonusName Name of the healing bonus.
    /// @return Pointer to the created instance of healing bonus.
    std::shared_ptr<CBonus> create_heal_bonus(const std::string& bonusName) const;
    
    /// Creates a pointer to any double bullets bonus that was loaded in %m_Config.
    /// @param[in] bonusName Name of the healing bonus.
    /// @return Pointer to the created instance of double bullets bonus.
    std::shared_ptr<CBonus> create_double_bullets_bonus(const std::string& bonusName) const;
    
    /// Creates a pointer to any ammo bonus that was loaded in %m_Config.
    /// @param[in] bonusName Name of the ammo bonus.
    /// @return Pointer to the created instance of ammo bonus.
    std::shared_ptr<CBonus> create_ammo_bonus(const std::string& bonusName) const;
    
    /// Method for lookup of toughness that is assigned to bonus from %m_Config.
    /// @param[in] bonusName Name of the bonus to lookup.
    /// @return Toughness that is assigned to the bonus.
    Toughness::EToughness get_bonus_toughness(const std::string& bonusName) const;
    
    /// Method for lookup visuals (sprite) of a bonus from %m_Config.
    /// @param[in] bonusName Name of the bonus to lookup.
    /// @return Sprite of the bonus.
    CVisualBlock get_bonus_sprite(const std::string& bonusName) const;
    
    /// Method for lookup of probability that is assigned to bonus from %m_Config.
    /// @param[in] bonusName Name of the bonus to lookup.
    /// @return Probability (number in range from 0 to 100) that is assigned to the bonus.
    int get_bonus_probability(const std::string& bonusName) const;
    
    /// Stores created bonus into %m_Bonuses so they can be looked up by their toughness later.
    /// If the bonus' toughness is NONE, the bonus will not be stored.
    /// @param[in] bonusName Name of the bonus (so its toughness could be looked up).
    /// @param[in] bonus Pointer to a constructed bonus that we want to store.
    void load_bonus(const std::string& bonusName, const std::shared_ptr<CBonus>& bonus);
    
    /// Container where bonuses are stored in a groups (vectors) where each group has
    /// a Toughness assigned to it (meaning all bonuses in the corresponding vector are assigned to that toughness).
    std::unordered_map<Toughness::EToughness, std::vector<std::shared_ptr<CBonus>>> m_Bonuses;
    
    /// Class for getting values that are loaded form a configuration file.
    std::shared_ptr<const CConfig> m_Config;
};
