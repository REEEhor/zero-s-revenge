#pragma once

#include "CBonus.h"

/// @brief Class extending CBonus. When player picks up this bonus, his/her current gun shoots double bullets.
class CDoubleBulletsBonus : public CBonus {
public:
    
    /// Constructor of CDoubleBulletsBonus.
    /// @param[in] probability Number representing percentage of this bonus dropping from an enemy.
    ///                        It will be compared to random int in range 0 - 99 and if the %probability is higher,
    ///                        the bonus would be treated as it dropped from the enemy.
    /// @param[in] sprite Symbol representing the bonus. It is also used when rendering dropped bonuses in game.
    ///                   Also could be used for an interface showing active bonuses (this feature is not implemented).
    /// @param[in] durationOfEffect For how many ticks the effect of this bonus should last for.
    explicit CDoubleBulletsBonus(int probability, CVisualBlock sprite, int durationOfEffect);
    
    /// Method that should be called when bonus gets taken.
    /// It stores a pointer to player's current gun.
    /// @param[in] player Player that should be effected by this bonus.
    void on_start(CPlayer& player) override;
    
    /// Method that should be called during the time this bonus if active.
    /// It sets 'bool %m_DoubleBullets' attribute in stored gun.
    /// @param[in] player Player that should be effected by this bonus.
    /// @return Whether the time the bonus is active for has run out.
    bool during(CPlayer& player) override;
    
    /// Method that should be called when bonus runs out.
    /// @param[in] player Player that should be effected by this bonus.
    void on_end(CPlayer& player) override;
    
    /// Method to call when we want to do polymorphic copying.
    /// @return std::shared_ptr to a new instance of CDoubleBulletsBonus.
    [[nodiscard]] std::shared_ptr<CBonus> clone() const override;
private:
    
    /// Pointer to player's current gun at the time of picking up this bonus.
    std::shared_ptr<CGun> m_EffectedGun;
};
