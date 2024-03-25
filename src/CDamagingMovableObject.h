#pragma once

#include "CMovableObject.h"

/// @brief Class extending CMovableObject by implementing movement that destroys environment.
///        When instance of this class collides with an object, it will damage it and then get destroyed.
///        This is used for bullets of charged enemies that die on impact.
class CDamagingMovableObject : public CMovableObject {
public:
    
    /// Constructor of CDamagingMovableObject.
    /// @param[in] position Starting position of the object.
    /// @param[in] maxHeathPoints Maximum health points of the object.
    ///                           Actual health points are set to this number as well.
    /// @param[in] sprite Looks of the object.
    /// @param[in] damage Amount of damage (number of health points) the object should deal when colliding with
    ///                   another object.
    /// @param[in] canBeSteppedOn Whether entities can step on this object or not.
    CDamagingMovableObject(const CPosition& position, int maxHeathPoints, const CVisualBlock& sprite, int damage,
                           bool canBeSteppedOn);
    
    /// Constructor of CDamagingMovableObject.
    /// @param[in] position Starting position of the object.
    /// @param[in] maxHeathPoints Maximum health points of the object.
    ///                           Actual health points are set to this number as well.
    /// @param[in] sprites List of sprites - if the object is moved, it can change it's looks
    ///                    to simulate changing it's 'orientation' by changing it's sprite.
    ///                    Possible lists:
    ///                        1 sprite  - Object does not change it's visual orientation when moved.
    ///                        2 sprites - Object has distinct looks when going left or right.
    ///                        3 sprites - Object has distinct looks when going up, down or to the side.
    ///                        6 sprites - Object has distinct looks for any direction.
    /// @param[in] canBeSteppedOn Whether entities can step on this object or not.
    /// @param[in] damage Amount of damage (number of health points) the object should deal when colliding with
    ///                   another object.
    /// @throws std::invalid_argument when the length of sprites list is not 1,2,3 or 6.
    CDamagingMovableObject(const CPosition& position, int maxHeathPoints, const std::list<CVisualBlock>& sprites,
                           bool canBeSteppedOn, int damage);
    
    /// @return A pointer to a new instance of CDamagingMovableObject.
    [[nodiscard]] std::shared_ptr<CMovableObject> clone_as_movable() const override;
    
    /// @return A pointer to a new instance of CDamagingMovableObject.
    [[nodiscard]] std::shared_ptr<CObject> clone() const override;
    
    /// Method used for moving the object.
    /// @param[in] move List of directions that the object should move into (in order).
    /// @param[in, out] collidableMap Map that is checked using 'can_be_stepped_on()' method.
    ///                               If no object returns true at the new position, movement will be made.
    ///                               If there is an object, that returns true, it gets damaged and this
    ///                               movable object gets destroyed.
    /// @param[in, out] forbiddenMap Map of objects that cannot this movable object cannot move into
    ///                              if there is any object.
    ///                              (usually a CMap containing this movable object).
    void try_to_move(Direction::EDirection move, const CMapJoin& collidableMap, const CMapJoin& forbiddenMap) override;
private:
    
    /// Amount of damage (number of health points) the object should deal when colliding with another object.
    int m_Damage;
};
