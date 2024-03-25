#include "CBulletObjectBuilder.h"

CBulletObjectBuilder::CBulletObjectBuilder(int damage, Color::EColor fgColor, Color::EColor bgColor, int movePeriod,
                                           int healthPoints,
                                           char upSymbol, char downSymbol, char leftSymbol, char rightSymbol)
        : m_Damage(damage),
          m_FgColor(fgColor),
          m_BgColor(bgColor),
          m_HealthPoints(healthPoints),
          m_MovePeriod(movePeriod),
          m_UpSymbol(upSymbol),
          m_DownSymbol(downSymbol),
          m_LeftSymbol(leftSymbol),
          m_RightSymbol(rightSymbol) {}

CBulletObjectBuilder::CBulletObjectBuilder(int damage, Color::EColor fgColor, Color::EColor bgColor, int movePeriod,
                                           int healthPoints,
                                           char symbol)
        : m_Damage(damage),
          m_FgColor(fgColor),
          m_BgColor(bgColor),
          m_HealthPoints(healthPoints),
          m_MovePeriod(movePeriod),
          m_UpSymbol(symbol),
          m_DownSymbol(symbol),
          m_LeftSymbol(symbol),
          m_RightSymbol(symbol) {}

std::shared_ptr<CMovableObject> CBulletObjectBuilder::build_bullet(
        const CPosition& position, VOrientation::EVOrientation vOrientation,
        HOrientation::EHOrientation hOrientation, bool doubleBullet) const {
    // First we determine the looks of object depending on the orientations in parameters.
    
    // Pick symbol using the orientation.
    char symbol;
    switch (CUtilities::direction_from_vh_orientations(vOrientation, hOrientation)) {
        case Direction::UP:
            symbol = m_UpSymbol;
            break;
        case Direction::DOWN:
            symbol = m_DownSymbol;
            break;
        case Direction::LEFT:
            symbol = m_LeftSymbol;
            break;
        case Direction::RIGHT:
            symbol = m_RightSymbol;
            break;
        default:
            symbol = m_UpSymbol; // Should not happen.
            break;
    }
    
    // Sprite of the bullet is two characters.
    // The first one is determined by previously picked %symbol.
    // The other one is either blank or the same symbol again, when %doubleBullets == true.
    char filler = (doubleBullet ? symbol : ' ');
    std::string content; // The text part of the sprite of the bullet that is going to be shot.
    if (hOrientation == HOrientation::RIGHT) {
        content.push_back(filler);
        content.push_back(symbol);
    } else {
        content.push_back(symbol);
        content.push_back(filler);
    }
    
    // Double bullets deal double damage.
    int damage = m_Damage * (doubleBullet ? 2 : 1);
    
    // Return constructed object.
    return std::make_shared<CDamagingMovableObject>(
            position,
            m_HealthPoints,
            CVisualBlock(std::move(content), m_FgColor, m_BgColor),
            damage,
            false);
}

int CBulletObjectBuilder::get_move_period() const {
    return m_MovePeriod;
}
