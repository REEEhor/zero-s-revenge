#pragma once

#include "CPosition.h"
#include "CVisualBlock.h"
#include "CTimeTicks.h"
#include "CUtilities.h"
#include <utility>
#include <map>
#include <vector>
#include <iterator>
#include <memory>

/// @brief Class representing any object that can be interacted with in some way.
///        Other classes like entities or bullets use this class as their representation in the game.
class CObject {
public:
    /// Constructor of CObject.
    /// @param[in] position Starting position of the object.
    /// @param[in] maxHeathPoints Maximum health points of the object.
    ///                           Actual health points are set to this number as well.
    /// @param[in] sprite Looks of the object.
    /// @param[in] canBeSteppedOn Whether entities can step on this object or not;
    CObject(const CPosition& position, int maxHeathPoints, CVisualBlock sprite, bool canBeSteppedOn);
    
    /// Virtual destructor since this class is used in polymorphic manner.
    virtual ~CObject();
    
    /// @return Current position of an object.
    [[nodiscard]] CPosition get_position() const;
    
    /// Deals damage to an object and reports, if the object has been destroyed.
    /// @param[in] damagePoints How many health points should be taken.
    /// @return Whether object was destroyed or not.
    virtual bool deal_damage(int damagePoints);
    
    /// @return Whether entities can step on this object or not;
    [[nodiscard]] virtual bool is_destroyed() const;
    
    /// @return Sprite of the object - it's looks.
    [[nodiscard]] virtual CVisualBlock get_sprite() const;
    
    /// @return Whether object can be stepped on or not;
    [[nodiscard]] virtual bool can_be_stepped_on() const;
    
    /// Sets object's health points to zero.
    /// This causes the object to be destroyed (see bool is_destroyed()).
    void destroy_itself();
    
    /// Updates object's visual state - meaning object's background color
    /// will be set to red, if the object has been recently damaged.
    virtual void update_looks();
    
    /// @return Health points of an object
    [[nodiscard]] int get_health() const;
    
    /// Adds health points to object but caps them to their maximum.
    /// @param healthPoints Amount of health points to be added.
    void heal_object(int healthPoints);
    
    /// @return A pointer to a new instance of CObject.
    [[nodiscard]] virtual std::shared_ptr<CObject> clone() const;

protected:
    /// Current position of an object.
    CPosition m_Position;
    
    /// Looks of an object that can be rendered.
    CVisualBlock m_Sprite;
    
    /// Maximum health points that object can have (also starting amount of health).
    int m_MaxHealthPoints;
    
    /// Current amount of health points of an object.
    int m_HealthPoints;
    
    /// Whether object can be stepped on.
    bool m_CanBeSteppedOn;
    
    /// Time class for showing damage
    CTimeTicks m_DamageTicks;
    
    /// Bool indicating recent damage done to an object.
    /// This variable is automatically set to true when calling 'bool deal_damage()'.
    bool m_IsHurt;
};
