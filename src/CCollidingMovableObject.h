#pragma once

#include "CMovableObject.h"

/// @brief Class that implements movement with collision.
///        If this object detects a collision with environment, it will not move.
class CCollidingMovableObject : public CMovableObject {
public:
    
    /// Constructor of CCollidingMovableObject.
    /// @param[in] position Starting position of the object.
    /// @param[in] maxHeathPoints Maximum health points of the object.
    ///                           Actual health points are set to this number as well.
    /// @param[in] sprite Looks of the object.
    /// @param[in] canBeSteppedOn Whether entities can step on this object or not;
    CCollidingMovableObject(const CPosition& position, int maxHeathPoints, const CVisualBlock& sprite,
                            bool canBeSteppedOn);
    
    /// Constructor of CMovableObject.
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
    /// @throws std::invalid_argument when the length of sprites list is not 1,2,3 or 6.
    CCollidingMovableObject(const CPosition& position, int maxHeathPoints, const std::list<CVisualBlock>& sprites,
                            bool canBeSteppedOn);
    
    /// @return A pointer to a new instance of CCollidingMovableObject.
    [[nodiscard]] std::shared_ptr<CMovableObject> clone_as_movable() const override;
    
    /// @return A pointer to a new instance of CCollidingMovableObject.
    [[nodiscard]] std::shared_ptr<CObject> clone() const override;
    
    /// Method used for moving the object.
    /// @param[in] move Direction that the object should move into.
    /// @param[in, out] collidableMap Map that is checked using 'can_be_stepped_on()' method.
    ///                               If there is no object at position the object goes to that returns
    ///                               true, movement will be made.
    /// @param[in, out] forbiddenMap Works in the same way as collidable map except there cannot be any object present.
    ///                              (meaning the map is checked using 'is_empty_at()' and no 'can_be_stepped_on()').
    void try_to_move(Direction::EDirection move, const CMapJoin& collidableMap, const CMapJoin& forbiddenMap) override;
};
