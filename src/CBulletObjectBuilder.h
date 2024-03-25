#pragma once

#include "CDamagingMovableObject.h"
#include <memory>

/// @brief Class that can builds CMovableObject representing the psychical state of the bullet in the game.
///        Also works as a wrapper since it also stores bullet's move period that is then used to
///        determining the speed of the bullet.
class CBulletObjectBuilder {
public:
    
    /// Constructor of CBulletObjectBuilder.
    /// @param[in] damage The amount of damage the bullet should deal on impact with other object.
    /// @param[in] fgColor Color of the bullet that this builder creates.
    /// @param[in] bgColor Color of the background behind the bullet that this builder creates.
    /// @param[in] movePeriod For how many ticks the objects stays in the same place when it moves.
    ///                       See CBullet's attribute m_Ticks for more info.
    /// @param[in] healthPoints Amount of health points the bullet has.
    /// @param[in] upSymbol Char used to display bullet's visuals when shot upwards.
    /// @param[in] downSymbol Char used to display bullet's visuals when shot downwards.
    /// @param[in] leftSymbol Char used to display bullet's visuals when shot to the left.
    /// @param[in] rightSymbol Char used to display bullet's visuals when shot to the right.
    /// @note This class does not use CVisualBlock to store the bullet's looks since every bullet
    ///       is represented by only one symbol. This is useful since the bullet can be visually "doubled" when shot.
    CBulletObjectBuilder(int damage, Color::EColor fgColor, Color::EColor bgColor, int movePeriod, int healthPoints,
                         char upSymbol, char downSymbol, char leftSymbol, char rightSymbol);
    
    /// Constructor of CBulletObjectBuilder.
    /// @param[in] damage The amount of damage the bullet should deal on impact with other object.
    /// @param[in] fgColor Color of the bullet that this builder creates.
    /// @param[in] bgColor Color of the background behind the bullet that this builder creates.
    /// @param[in] movePeriod For how many ticks the objects stays in the same place when it moves.
    ///                       See CBullet's attribute m_Ticks for more info.
    /// @param[in] healthPoints Amount of health points the bullet has.
    /// @param[in] symbol Char used to display bullet's visuals when shot.
    /// @note This class does not use CVisualBlock to store the bullet's looks since every bullet
    ///       is represented by only one symbol. This is useful since the bullet can be visually "doubled" when shot.
    CBulletObjectBuilder(int damage, Color::EColor fgColor, Color::EColor bgColor, int movePeriod, int healthPoints,
                         char symbol);
    
    /// Builds the bullet based on internal settings of the builder that have been passed in constructor.
    /// @param[in] position Position where the bullet should be built.
    /// @param[in] vOrientation VERTICAL orientation of the entity that shot this bullet.
    ///                         This is needed so it looks like the entity shot the bullet from the gun it's holding.
    /// @param[in] hOrientation HORIZONTAL orientation of the entity that shot this bullet.
    ///                         This is needed so it looks like the entity shot the bullet from the gun it's holding.
    /// @param[in] doubleBullet Whether bullet should be doubled. Visually it means the symbol for the bullet is going
    ///                         to be rendered twice and the bullet is going to deal double damage then normal.
    [[nodiscard]] std::shared_ptr<CMovableObject> build_bullet(const CPosition& position,
                                                               VOrientation::EVOrientation vOrientation,
                                                               HOrientation::EHOrientation hOrientation,
                                                               bool doubleBullet) const;
    
    /// @return Supposed move period - between movements of the bullet this builder creates.
    [[nodiscard]] int get_move_period() const;

private:
    /// Constructor of CBulletObjectBuilder.
    /// @param[in] damage The amount of damage the bullet should deal on impact with other object.
    
    /// The amount of damage the bullet should deal on impact with other object.
    int m_Damage;
    
    /// Color of the bullet that this builder creates.
    Color::EColor m_FgColor;
    
    /// Color of the background behind the bullet that this builder creates.
    Color::EColor m_BgColor;
    
    /// Amount of health points the bullet has.
    int m_HealthPoints;
    
    /// For how many ticks the objects stays in the same place when it moves.
    /// See CBullet's attribute m_Ticks for more info.
    int m_MovePeriod;
    
    /// Char used to display bullet's visuals when shot upwards.
    char m_UpSymbol;
    /// Char used to display bullet's visuals when shot downwards.
    char m_DownSymbol;
    /// Char used to display bullet's visuals when shot to the left.
    char m_LeftSymbol;
    /// Char used to display bullet's visuals when shot to the right.
    char m_RightSymbol;
};
