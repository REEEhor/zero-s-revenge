#pragma once

#include "CObject.h"
#include "CPosition.h"
#include "CRenderer.h"
#include <map>
#include <memory>

/// @brief Class for looking up objects by their positions.
///        This class is then used mostly for collision detection.
class CMap {
public:
    
    /// Default constructor of CMap.
    CMap();
    
    /// Constructor that registers list of objects by their position.
    /// The constructor uses method 'add_object()' method.
    /// @param[in] objects Objects to be added.
    CMap(std::initializer_list<std::shared_ptr<CObject>> objects);
    
    /// Registers new object using its position.
    /// @param[in] object Object to be added.
    /// @return Reference to '*this' for chaining calls of this method.
    /// @warning If there is already an object at that position, it will get overwritten by the new object.
    CMap& add_object(const std::shared_ptr<CObject>& object);
    
    /// Method for checking if there is an object at some position and
    /// if there is, its 'can_be_stepped_on()' method will be called.
    /// @param[in] position Position we want to check.
    /// @return True if there is no object at %position or if the found object return true
    ///         when the 'can_be_stepped_on()' method is called. Otherwise false.
    [[nodiscard]] bool can_be_stepped_on(const CPosition& position) const;
    
    /// Method for checking if there is any object at %position.
    /// @return True if there was an object found at %position. Otherwise false.
    [[nodiscard]] bool is_empty_at(const CPosition& position) const;
    
    /// Tries dealing damage to object at some position.
    /// If there is no object at that position, nothing will happen.
    /// @param[in] damagePoints Amount of damage points that should be dealt to an object if found.
    /// @param[in] position Position where there should be an attempt of dealing damage.
    /// @param[in] exception Pointer to an object that we do not want to deal damage to.
    /// @return Whether damage was dealt (meaning some object was at %position).
    bool try_dealing_damage_at(int damagePoints, const CPosition& position, const CObject* exception = nullptr);
    
    /// Method that checks if there is an object at some position and if the object's position
    /// does not match with its key, it will get remapped.
    /// @param [in] position Position where could be out of date object.
    /// @warning This method uses 'add_object()' method, so if there is an object
    ///          at the new object position, it will get overwritten.
    void update_position_of_object_at(const CPosition& position);
    
    /// Erases object at position, if found.
    /// @return Whether any object was erased or not.
    bool erase_object_at(const CPosition& position);
    
    /// Erases object by looking up its position and checking if the pointers match.
    void erase_object(const std::shared_ptr<CObject>& object);
    
    /// Puts all contained objects into renderer to be rendered later.
    void push_objects_to_render(CRenderer& renderer) const;
    
    /// Calls 'update_looks()' method on all object in this container.
    void update_looks_all_objects();

private:
    
    /// Internal representation of CMap - map of positions and shared pointers.
    std::map<CPosition, std::shared_ptr<CObject>> m_Map;
};
