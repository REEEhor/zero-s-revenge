#include "CRenderer.h"

CRenderer::CRenderer(int screenWidth, int screenHeight, const CConfig& config)
        : m_CurrentBufferId(0), m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight),
          m_DefaultVisualBlock("  ", Color::BLACK, config.m_Color["BACKGROUND_COLOR"]),
          m_InitialRender(true) {}

void CRenderer::put_sprite_at(const CVisualBlock& sprite, const CPosition& position) {
    /// Check if the sprite position is in the set range.
    if (CUtilities::is_in_range(position.m_X, 0, m_ScreenWidth - 1)
        && CUtilities::is_in_range(position.m_Y, 0, m_ScreenHeight - 1)) {
        current_buffer()[position] = sprite;
    }
}

CRenderer::Buffer& CRenderer::current_buffer() {
    return m_Buffers[m_CurrentBufferId];
}

CRenderer::Buffer& CRenderer::previous_buffer() {
    return m_Buffers[!m_CurrentBufferId];
}

void CRenderer::render_differences(std::ostream& os) {
    if (m_InitialRender) {
        m_InitialRender = false;
        do_initial_render(os);
    }
    
    // Loop through all possible coordinates and render differences.
    for (int y = 0; y < m_ScreenHeight; ++y) {
        for (int x = 0; x < m_ScreenWidth; ++x) {
            CPosition currentPos(x, y);
            
            auto blockIt = current_buffer().find(currentPos);
            bool blockExists = blockIt != current_buffer().end();
            //
            auto prevBlockIt = previous_buffer().find(currentPos);
            bool blockExisted = prevBlockIt != previous_buffer().end();
            
            if (blockExists && !blockExisted) {
                // Sprite now exits but did not exist during the previous frame
                // -> render it.
                render_sprite_at(blockIt->second, currentPos, os);
                
            } else if (!blockExists && blockExisted) {
                // Visual block no longer exists
                // -> render the default one.
                render_sprite_at(m_DefaultVisualBlock, currentPos, os);
                
            } else if (blockExists && blockExisted
                       && (blockIt->second != prevBlockIt->second)) {
                // Some sprite exists in the current and previous buffer
                // and they differ.
                // -> render the current one.
                render_sprite_at(blockIt->second, currentPos, os);
                
            }
        }
    }
}

void CRenderer::render_sprite(const CVisualBlock& sprite, std::ostream& os) {
    os << CTerminal::set_color(sprite.m_ForegroundColor);
    os << CTerminal::set_background_color(sprite.m_BackgroundColor);
    os << sprite.m_Content << std::flush;
}

void CRenderer::render_sprite_at(const CVisualBlock& sprite, const CPosition& position, std::ostream& os) {
    os << CTerminal::move_cursor_to(position);
    render_sprite(sprite, os);
}

void CRenderer::switch_active_buffer() {
    m_CurrentBufferId = !m_CurrentBufferId;
}

void CRenderer::clear_active_buffer() {
    current_buffer().clear();
}

void CRenderer::prepare_to_render(const CObject& objectToRender) {
    put_sprite_at(objectToRender.get_sprite(), objectToRender.get_position());
}

void CRenderer::reset() {
    m_Buffers[0].clear();
    m_Buffers[1].clear();
    m_InitialRender = true;
}

void CRenderer::do_initial_render(std::ostream& os) const {
    
    // Go through all possible positions and render default sprite.
    for (int y = 0; y < m_ScreenHeight; ++y) {
        for (int x = 0; x < m_ScreenWidth; ++x) {
            CPosition currentPos(x, y);
            render_sprite_at(m_DefaultVisualBlock, currentPos, os);
        }
    }
}
