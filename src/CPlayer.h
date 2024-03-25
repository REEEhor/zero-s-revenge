#pragma once

#include "CNonStaticEntity.h"
#include "CActionsInputRecorder.h"
#include "CDamagingMovableObject.h"
#include "CBullet.h"
#include "CUtilities.h"
#include "CGun.h"
#include <memory>
#include <map>
#include <vector>

/// @brief Class extending CNonStaticEntity used for representing the player in the game.
/// @warning When copying this class the pointer to CActionsInputRecorder gets copied as well.
///          This means both players will be dependent on the same inputs
///          (This is actually a wanted behaviour since there is only one player in the game
///          and when it gets constructed using copy semantics, we want to copy the pointer to
///          to the keyboard input as well).
///          Since copying this class is used for creating a single player object, copying the
///          the vector of guns and not the pointers would be an unnecessary overhead so it
///          it not implemented either.
class CPlayer : public CNonStaticEntity {
public:
    /// Default constructor of CPlayer.
    CPlayer();
    
    /// Constructor of CPlayer.
    /// @param[in] object Object that represents physical state of the entity in the game.
    /// @param[in] inputRecorder Keyboard input of the player.
    CPlayer(const std::shared_ptr<CMovableObject>& object, const std::shared_ptr<CActionsInputRecorder>& inputRecorder);
    
    /// Updates internal state of the player based on the %m_Input.
    /// @param[in, out] mapContainingObject CMap that contains object that this enemy controls.
    ///                                     Necessary for keeping mapping between object and position up to date.
    ///                                     This method also deletes object from this CMap, if it is destroyed.
    /// @param[in, out] environment CMap of objects that can interact with enemy's object.
    /// @param[out] bullets List of bullets so that the player can shoot.
    /// @param[out] bulletMap Map containing bullet objects so that player can shoot.
    /// @return Whether player has died or not.
    /// @warning This method should not be called until player has not been initialised with object and actions input recorder.
    bool update(const std::shared_ptr<CMap>& mapContainingObject, const CMapJoin& environment,
                std::list<CBullet>& bullets, const std::shared_ptr<CMap>& bulletMap);
    
    /// @return Pointer to player's current selected gun.
    [[nodiscard]] std::shared_ptr<CGun> current_gun() const;
    
    /// Adds gun to the vector of guns the player can shoot with.
    /// @param newGun Gun that should be added.
    void add_gun(const CGun& newGun);

private:
    /// @return The number of guns that the player currently has.
    [[nodiscard]] int number_of_guns() const;
    
    /// Sets a gun from the %m_Guns as selected (meaning the player will shoot using that gun) based on the index.
    /// This method also does bounds checking - if the index is not valid it will cap it into the correct range.
    /// @param[in] gunId Index of the gun in %m_Guns.
    void select_gun(int gunId);
    
    /// Keyboard input determining the actions of the player.
    std::shared_ptr<CActionsInputRecorder> m_Input;
    
    /// Index of currently selected guns in %m_Guns.
    int m_CurrentGunId;
    
    /// Vector of guns that the player can shoot with.
    std::vector<std::shared_ptr<CGun>> m_Guns;
};
