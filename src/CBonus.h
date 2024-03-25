#pragma once

#include "CVisualBlock.h"
#include "CPlayer.h"
#include <memory>
#include <utility>

/// @brief Abstract class for bonuses the player can get.
class CBonus {
public:
    
    /// Constructor of CBonus.
    /// @param[in] probability Number representing percentage of this bonus dropping from an enemy.
    ///                        It will be compared to random int in range 0 - 99 and if the %probability is higher,
    ///                        the bonus would be treated as it dropped from the enemy.
    /// @param[in] sprite Symbol representing the bonus. It is also used when rendering dropped bonuses in game.
    ///                   Also could be used for an interface showing active bonuses (this feature is not implemented).
    /// @param[in] durationOfEffect For how many ticks the effect of this bonus should last for.
    CBonus(int probability, CVisualBlock sprite, int durationOfEffect = 0);
    
    /// Virtual destructor since this is a base class of polymorphic classes.
    virtual ~CBonus();
    
    /// Method that should be called when bonus gets taken.
    /// @param[in] player Player that should be effected by this bonus.
    virtual void on_start(CPlayer& player) = 0;
    
    /// Method that should be called during the time this bonus if active.
    /// @param[in] player Player that should be effected by this bonus.
    /// @return Whether the time the bonus is active for has run out.
    virtual bool during(CPlayer& player) = 0;
    
    /// Method that should be called when bonus runs out.
    /// @param[in] player Player that should be effected by this bonus.
    virtual void on_end(CPlayer& player) = 0;
    
    /// Method to call when we want to do polymorphic copying.
    /// @return std::shared_ptr to a new instance of CBonus.
    [[nodiscard]] virtual std::shared_ptr<CBonus> clone() const = 0;
    
    /// Number representing percentage of this bonus dropping from an enemy.
    int m_Probability;
    
    /// Symbol representing the bonus. It is also used when rendering dropped bonuses in game.
    CVisualBlock m_Sprite;
protected:
    
    /// Internal helper method that checks if the time of effect of the bonus has run out.
    /// @return Whether the time the bonus is active for has run out.
    [[nodiscard]] bool has_time_run_out();
    
    /// For how many ticks the effect of this bonus should last for.
    int m_DurationOfEffect;
};
