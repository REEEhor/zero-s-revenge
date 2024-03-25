#include "CMovableObject.h"

CMovableObject::CMovableObject(const CPosition& position, int maxHeathPoints, const CVisualBlock& sprite,
                               bool canBeSteppedOn)
        : CObject(position, maxHeathPoints, sprite, canBeSteppedOn),
          m_VOrientation(VOrientation::UP),
          m_HOrientation(HOrientation::LEFT),
          m_MultipleSprites(false) {}

void CMovableObject::update_sprite(Direction::EDirection move) {
    
    // Update object's orientation
    auto newVerticalDirection = m_VOrientation;
    auto newHorizontalDirection = m_HOrientation;
    switch (move) {
        case Direction::UP:
            newVerticalDirection = VOrientation::UP;
            break;
        case Direction::DOWN:
            newVerticalDirection = VOrientation::DOWN;
            break;
        case Direction::LEFT:
            newVerticalDirection = VOrientation::MIDDLE;
            newHorizontalDirection = HOrientation::LEFT;
            break;
        case Direction::RIGHT:
            newVerticalDirection = VOrientation::MIDDLE;
            newHorizontalDirection = HOrientation::RIGHT;
            break;
        default:
            break;
    }
    
    if (newVerticalDirection != m_VOrientation
        || newHorizontalDirection != m_HOrientation) {
        m_VOrientation = newVerticalDirection;
        m_HOrientation = newHorizontalDirection;
    }
    
    // In the case that object does not have distinct sprites for multiple
    // orientations, we do not need to update its sprite.
    // (The update of orientation is still necessary since other system depend on it.)
    if (m_MultipleSprites) {
        // Lookup correct sprite using enums.
        m_Sprite = m_Sprites[m_HOrientation][m_VOrientation];
    }
    
}

VOrientation::EVOrientation CMovableObject::get_v_orientation() const {
    return m_VOrientation;
}

HOrientation::EHOrientation CMovableObject::get_h_orientation() const {
    return m_HOrientation;
}

CMovableObject::CMovableObject(const CPosition& position, int maxHeathPoints, const std::list<CVisualBlock>& sprites,
                               bool canBeSteppedOn)
        
        : CObject(position, maxHeathPoints, CVisualBlock(), canBeSteppedOn),
          m_VOrientation(VOrientation::UP), m_HOrientation(HOrientation::LEFT),
          m_MultipleSprites(true) { setup_sprites(sprites); }

void CMovableObject::setup_sprites(const std::list<CVisualBlock>& sprites) {
    using namespace HOrientation;
    using namespace VOrientation;
    
    // %m_Sprites contains 6 sprites for different directions the object can move in.
    // After setup, we can look up objects sprites by %m_Sprites[HORIZONTAL_ORIENTATION][VERTICAL_ORIENTATION].
    // ( %m_Sprites essentially work like 2D map ).
    m_Sprites = std::vector<std::vector<CVisualBlock>>(HORIZONTAL_DIRECTION_COUNT, std::vector<CVisualBlock>());
    
    switch (sprites.size()) {
        case 1:
            m_Sprite = sprites.front();
            m_MultipleSprites = false;
            break;
            
            
            // Object has distinct sprites only in horizontal orientations.
            // This means duplicating each horizontal sprite into all vertical orientations.
        case HORIZONTAL_DIRECTION_COUNT: {
            int cnt = 0;
            for (int i = 0; i < VERTICAL_DIRECTION_COUNT; ++i) {
                for (auto& sprite: sprites) {
                    m_Sprites[cnt++ % HORIZONTAL_DIRECTION_COUNT].push_back(sprite);
                }
            }
            break;
        }
            
            // Object has distinct sprites only in vertical orientations.
            // This means duplicating each vertical sprite into all horizontal orientations.
        case VERTICAL_DIRECTION_COUNT: {
            int cnt = 0;
            for (int i = 0; i < HORIZONTAL_DIRECTION_COUNT; ++i) {
                for (auto& sprite: sprites) {
                    m_Sprites[cnt++ / VERTICAL_DIRECTION_COUNT].push_back(sprite);
                }
            }
            break;
        }
            
            // Object has sprite for every possible permutation of orientations.
            // We simply take each sprite and add it to %m_Sprites.
        case VERTICAL_DIRECTION_COUNT * HORIZONTAL_DIRECTION_COUNT: {
            int cnt = 0;
            for (auto& sprite: sprites) {
                m_Sprites[cnt++ % HORIZONTAL_DIRECTION_COUNT].push_back(sprite);
            }
            break;
        }
        
        default:
            throw std::invalid_argument("num of sprites");
    }
    m_Sprite = m_Sprites[m_HOrientation][m_VOrientation];
}
