#pragma once

#include "CBonus.h"
#include "CObject.h"
#include <memory>

/// @brief Class representing bonus (the object that can be picked up - not the bonus itself),
/// that can be dropped from killed enemies.
class CBonusObject : public CObject {
public:
    /// Constructor of CBonusObject.
    /// @param[in] position Starting position of the object.
    /// @param[in] maxHeathPoints Maximum health points of the object.
    ///                           Actual health points are set to this number as well.
    /// @param[in] bonus Bonus the player should gain when stepping on this object.
    CBonusObject(const CPosition& position, int maxHeathPoints, const CBonus& bonus);
    
    /// Bonus the player should gain when stepping on this object.
    std::shared_ptr<CBonus> m_Bonus;
    
    /// Operator= for CBonusObject. Uses CBonus::clone() method for copying the stored bonus.
    /// @return reference to %*this.
    CBonusObject& operator=(const CBonusObject& other);
    
    /// Copy constructor for CBonusObject. Uses CBonus::clone() method for copying stored bonus.
    CBonusObject (const CBonusObject& other);
    
    /// @return A pointer to a new instance of CBonusObject.
    [[nodiscard]] std::shared_ptr<CObject> clone() const override;
    
};
