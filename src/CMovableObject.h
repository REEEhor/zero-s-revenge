#pragma once

#include "CObject.h"
#include "EDirection.h"
#include "EVOrientation.h"
#include "EHOrientation.h"
#include "CMap.h"
#include "CMapJoin.h"
#include <list>
#include <memory>

/// @brief This class extends CObject by making it available to move the object.
///        It is abstract - children of this class interact differently when moving
///        through environment in the game (bullets / enemies / player).
class CMovableObject : public CObject {
public:
    /// Constructor of CMovableObject.
    /// @param[in] position Starting position of the object.
    /// @param[in] maxHeathPoints Maximum health points of the object.
    ///                           Actual health points are set to this number as well.
    /// @param[in] sprite Looks of the object.
    /// @param[in] canBeSteppedOn Whether entities can step on this object or not;
    CMovableObject(const CPosition& position, int maxHeathPoints, const CVisualBlock& sprite, bool canBeSteppedOn);
    
    
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
    CMovableObject(const CPosition& position, int maxHeathPoints, const std::list<CVisualBlock>& sprites,
                   bool canBeSteppedOn);
    
    /// Method used for moving the object.
    /// @param[in] move Direction that the object should try to move into.
    /// @param[in, out] collidableMap Map of other objects for detecting collisions.
    ///                               Depending on implementation of child, this map can be modified
    ///                               if CMovableObject decides to damage some object in it.
    /// @param[in, out] forbiddenMap Object is prohibited to go to a position if this map contains already an
    ///                              object at that position.
    ///                              This is useful when object can collide with an object in the same CMap as it is in,
    ///                              since CMap prohibits having multiple objects at the same position at once.
    virtual void
    try_to_move(Direction::EDirection move, const CMapJoin& collidableMap, const CMapJoin& forbiddenMap) = 0;
    
    /// Method that should be called when object moves.
    /// The object updates it's sprite so it looks like it rotated into the direction it moved in.
    /// @param[in] move Direction that the object moved into.
    void update_sprite(Direction::EDirection move);
    
    /// @return Object's current VERTICAL orientation (up, down, to the side).
    [[nodiscard]] VOrientation::EVOrientation get_v_orientation() const;
    
    /// @return Object's current HORIZONTAL orientation (left, right).
    [[nodiscard]] HOrientation::EHOrientation get_h_orientation() const;
    
    /// @return A pointer to a non-abstract child of CMovableObject.
    [[nodiscard]] virtual std::shared_ptr<CMovableObject> clone_as_movable() const = 0;

protected:
    
    /// Preprocesses and stores sprites into %m_Sprites depending on the length of %sprites.
    /// @param[in] sprites List of sprites - if the object is moved, it can change it's looks
    ///                    to simulate changing it's 'orientation' by changing it's sprite.
    ///                    Possible lists:
    ///                        1 sprite  - Object does not change it's visual orientation when moved.
    ///                        2 sprites - Object has distinct looks when going left or right.
    ///                        3 sprites - Object has distinct looks when going up, down or to the side.
    ///                        6 sprites - Object has distinct looks for any direction.
    /// @throws std::invalid_argument when the length of sprites list is not 1,2,3 or 6.
    void setup_sprites(const std::list<CVisualBlock>& sprites);
    
    /// Object's current VERTICAL orientation (up, down, to the side).
    VOrientation::EVOrientation m_VOrientation;
    
    /// Object's current HORIZONTAL orientation (left or right).
    HOrientation::EHOrientation m_HOrientation;
    
    /// 2D vector of 6 sprites total for different orientations of the object.
    /// The lookup from this vector is done using %m_VOrientation and %m_HOrientation.
    std::vector<std::vector<CVisualBlock>> m_Sprites;
    
    /// Whether object has distinct sprites for moving into different directions or not.
    bool m_MultipleSprites;
};
