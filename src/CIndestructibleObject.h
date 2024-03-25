#pragma once

#include "CObject.h"

/// @brief Class extending CObject by overriding 'deal_damage()' and 'is_destroyed()' method.
///        As the name implies, the object cannot be destroyed.
class CIndestructibleObject : public CObject {
public:
    
    /// Constructor of CIndestructibleObject.
    /// @param[in] position Starting position of the object.
    /// @param[in] sprite Looks of the object.
    /// @param[in] canBeSteppedOn Whether entities can step on this object or not;
    CIndestructibleObject(const CPosition& position, const CVisualBlock& sprite,
                          bool canBeSteppedOn);
    
    /// @return always false - instances of this class act as they do not get damaged or destroyed.
    [[nodiscard]] bool is_destroyed() const override;
    
    /// This method does nothing to instances of this class.
    /// @return always false (meaning the object was not destroyed).
    bool deal_damage(int damagePoints) override;
    
    /// @return A pointer to a new instance of CIndestructibleObject.
    [[nodiscard]] std::shared_ptr<CObject> clone() const override;
};
