#pragma once

#include "CConfig.h"
#include "CVisualBlock.h"
#include "CObject.h"
#include "CTerminal.h"
#include "CUtilities.h"
#include "CPosition.h"
#include <map>

/// @brief Class that renders objects to the screen.
///        Each iteration of the game, objects are registered for rendering
///        and then rendered. Instance of this class stores how the
///        game looked on the previous frame and only renderers the differences
///        between the frames.
class CRenderer {
public:
    
    /// Constructor of CRenderer.
    /// @param[in] screenHeight Determines the maximum X position a object can be rendered.
    /// @param[in] screenHeight Determines the maximum Y position a object can be rendered.
    /// @param[in] config Configuration of the program. The renderer needs it so ti can determine
    ///                   the background - color for when there is no object present.
    CRenderer(int screenWidth, int screenHeight, const CConfig& config);
    
    /// Pushes a sprite into a buffer so it can be rendered later.
    /// @param[in] sprite Color and text in the sprite.
    /// @param[in] position Position where the %sprite should be rendered at.
    void put_sprite_at(const CVisualBlock& sprite, const CPosition& position);
    
    /// Pushes an object sprite into a buffer so it can be rendered later.
    /// It gets its looks by calling CObject::get_sprite() and its position by
    ///  CObject::get_position().
    /// See put_sprite_at() for more info.
    /// @param[in] objectToRender Object that should be registered for rendering later.
    void prepare_to_render(const CObject& objectToRender);
    
    /// Renderers the differences between the previous and current frame by
    /// comparing the two internal buffers.
    /// @param[in] os Stream to render the contents into.
    void render_differences(std::ostream& os);
    
    /// Clears the active buffer of the renderer.
    /// This method is supposed to be called before any objects are pushed
    /// to be rendered in the next frame.
    void clear_active_buffer();
    
    /// Switches which buffer is currently considered active.
    /// When sprites are pushed to render, they are stored in the active buffer.
    void switch_active_buffer();
    
    /// Clears contents of both buffers.
    /// This method can be called in the case the rendering somehow breaks,
    /// so everything will be rendered (not just the differences).
    void reset();

private:
    
    /// Static method for rendering sprite at some position.
    /// Calls render_sprite() method for the actual rendering.
    /// @param[in] sprite Sprite to be rendered.
    /// @param[in] position Position in which the sprite should be rendered in.
    /// @param[in] os Stream to render the sprite into.
    static void render_sprite_at(const CVisualBlock& sprite, const CPosition& position, std::ostream& os);
    
    /// Static method for rendering one sprite to an output stream.
    /// @param[in] sprite Sprite to be rendered.
    /// @param[in] os Stream to render the sprite into.
    static void render_sprite(const CVisualBlock& sprite, std::ostream& os);
    
    /// Renders the background so it does not need to be rendered during
    /// regular renders.
    /// @return os Stream to render the background into.
    void do_initial_render(std::ostream& os) const;
    
    /// Buffers are just a map where the key is CPosition of the corresponding sprite.
    typedef std::map<CPosition, CVisualBlock> Buffer;
    
    /// Used as index to determine which buffer is currently active.
    bool m_CurrentBufferId;
    
    /// Determines the maximum X position a object can be rendered.
    int m_ScreenWidth;
    
    /// Determines the maximum Y position a object can be rendered.
    int m_ScreenHeight;
    
    /// Sprite that is going to be rendered if there is no other object at some location.
    CVisualBlock m_DefaultVisualBlock;
    
    /// Double buffering - only changes are rendered each frame.
    Buffer m_Buffers[2];
    
    /// Whether initial render should happen or not.
    /// This bool is set to true in the constructor and then
    /// every time 'reset()' method gets called.
    bool m_InitialRender;
    
    /// @return One buffer from %m_Buffers indexed by %m_CurrentBufferId.
    Buffer& current_buffer();
    
    /// @return One buffer from %m_Buffers indexed by the negation of %m_CurrentBufferId.
    Buffer& previous_buffer();
};
