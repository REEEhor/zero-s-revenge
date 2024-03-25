#pragma once

#include "CBonus.h"

/// @brief Class extending CBonus. It implements a bonus, that reloads player's current gun (sets its ammo to maximum).
class CAmmoBonus : public CBonus {
public:
    
    /// Constructor of CBonus.
    /// @param[in] probability Number representing percentage of this bonus dropping from an enemy.
    ///                        It will be compared to random int in range 0 - 99 and if the %probability is higher,
    ///                        the bonus would be treated as it dropped from the enemy.
    /// @param[in] sprite Symbol representing the bonus. It is also used when rendering dropped bonuses in game.
    ///                   Also could be used for an interface showing active bonuses (this feature is not implemented).
    explicit CAmmoBonus(int probability, CVisualBlock sprite);
    
    /// Method that should be called when bonus gets taken.
    /// It takes player's gun and reloads it.
    /// @param[in] player Player that should be effected by this bonus.
    void on_start(CPlayer& player) override;
    
    /// Method that should be called during the time this bonus if active.
    /// @param[in] player Player that should be effected by this bonus.
    /// @return Whether the time the bonus is active for has run out.
    bool during(CPlayer& player) override;
    
    /// Method that should be called when bonus runs out.
    /// @param[in] player Player that should be effected by this bonus.
    void on_end(CPlayer& player) override;
    
    /// Method to call when we want to do polymorphic copying.
    /// @return std::shared_ptr to a new instance of CAmmoBonus.
    [[nodiscard]] std::shared_ptr<CBonus> clone() const override;
};
