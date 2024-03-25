#pragma once

#include "CMovableObject.h"
#include "CMapJoin.h"
#include <memory>
#include <map>
#include <list>

/// @brief Class for managing one CMovableObject. It stores a pointer to it and
///        uses it as an physical representation of itself in the game.
///        This class uses EAction enum to interpret what to do and if some of them are movement,
///        they are sent to CMovableObject.
class CNonStaticEntity {
public:
    
    /// Constructor of CNonStaticEntity.
    /// @param[in] object Object that represents physical state of the entity in the game.
    explicit CNonStaticEntity(const std::shared_ptr<CMovableObject>& object);
    
    /// Custom copy constructor since this class has a pointer to an object.
    CNonStaticEntity(const CNonStaticEntity& other);
    
    /// Copy operator= since this class has a pointer to an object.
    /// @return A reference to *this.
    CNonStaticEntity& operator=(const CNonStaticEntity& other);
    
    /// Virtual destructor since this is a base class of polymorphic hierarchy.
    virtual ~CNonStaticEntity();
    
    /// Gets pointer to the object that represents physical state of the CNonStaticEntity.
    [[nodiscard]] std::shared_ptr<CMovableObject> get_object() const;

protected:
    /// Moves object and updates its representation in CMap that contains it
    /// (meaning the object will be still mapped to its position even after moving).
    /// This method is then used primarily by children of this class as an internal update.
    /// @param[in, out] mapContainingObject CMap that contains object that this class controls.
    ///                                     Necessary for keeping mapping between object and position up to date.
    ///                                     This method also deletes object from this CMap, if it is destroyed.
    /// @param[in, out] environment CMap of objects that can interact with object.
    /// @param[in] move Direction the object should move in.
    /// @return Whether entity should by treated as not destroyed after the update or not (false means destroyed).
    bool
    update(const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment, Direction::EDirection move);
    
    /// Object that represents physical state of the CNonStaticEntity.
    /// Pointer to this object is also in other containers where it gets effected by the
    /// other actions and entities.
    std::shared_ptr<CMovableObject> m_Object;
};
