#pragma once

#include "CBonus.h"

/// @brief Class extending CBonus. This bonus raises player's health points by given amount.
///        This bonus effects the player only when it gets picked up.
class CHealBonus : public CBonus {
public:
    
    /// Constructor of CHealBonus.
    /// @param[in] probability Number representing percentage of this bonus dropping from an enemy.
    ///                        It will be compared to random int in range 0 - 99 and if the %probability is higher,
    ///                        the bonus would be treated as it dropped from the enemy.
    /// @param[in] sprite Symbol representing the bonus. It is also used when rendering dropped bonuses in game.
    ///                   Also could be used for an interface showing active bonuses (this feature is not implemented).
    /// @param[in] healAmount The amount of health points the player should get from this bonus.
    explicit CHealBonus(int probability, CVisualBlock sprite, int healAmount);
    
    /// Method that should be called when bonus gets taken.
    /// It calls player 'heal()' method.
    /// @param[in] player Player that should be effected by this bonus.
    void on_start(CPlayer& player) override;
    
    /// Method that should be called during the time this bonus if active.
    /// @param[in] player Player that should be effected by this bonus.
    /// @return Whether the time the bonus is active for has run out.
    /// (which is always false - this bonus only applies at the moment player picks up the bonus).
    bool during(CPlayer& player) override;
    
    /// Method that should be called when bonus runs out.
    /// @param[in] player Player that should be effected by this bonus.
    void on_end(CPlayer& player) override;
    
    /// Method to call when we want to do polymorphic copying.
    /// @return std::shared_ptr to a new instance of CHealBonus.
    [[nodiscard]] std::shared_ptr<CBonus> clone() const override;
private:
    
    /// The amount of health points the player should get from this bonus.
    int m_HealAmount;
};
