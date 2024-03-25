#pragma once

/// @brief Class used for registering periods of time.
///        For example when we want to do some action every N game ticks,
///        we can use this class to get notified when N ticks have passed.
class CTimeTicks {
public:
    
    /// Constructor of CTimeTicks.
    /// @param[in] period How long should be the periods between notifications.
    explicit CTimeTicks(int period);
    
    /// Method used for simple periodic notifications.
    /// Each time this method gets called, interval variable %m_CurrentCount
    /// decrements by one and if it is lower or equal to zero, it notifies the caller.
    /// @return If the time has run out. If it did, the internal timer gets reset to %m_Period.
    bool decrement();
    
    /// Const method that does not change internal timer of this class,
    /// just returns whether the internal time variable is lower or equal to zero.
    /// This method can be used together with 'void update()'.
    /// @return Whether %m_Period is lower of equal to zero.
    [[nodiscard]] bool time_ran_out() const;
    
    /// Decrements internal timer by one.
    void update();
    
    /// Resets the internal timer.
    /// (meaning %m_CurrentCount will be set to %m_Period)
    void reset();

private:
    
    /// Internal timer that can be decremented by various methods
    /// and compared to zero.
    int m_Period;
    
    /// The time (amount of game ticks) between each notifications.
    int m_CurrentCount;
};
