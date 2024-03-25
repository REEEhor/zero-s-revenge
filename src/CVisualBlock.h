#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include "CTerminal.h"
#include "EColor.h"

/// @brief Two characters with colors that can be rendered.
///        Two characters because it roughly correspond to a square on
///        most terminals.
class CVisualBlock {
public:
    
    /// Constructor of CVisualBlock.
    /// @param[in] content String of characters that the CVisualBlock is made out of.
    /// @param[in] fgColor Foreground color - color of the characters in %m_Content.
    /// @param[in] bgColor Background color - color of the characters in %m_Content.
    explicit CVisualBlock(std::string content = "  ", Color::EColor fgColor = Color::BLACK,
                          Color::EColor bgColor = Color::BLACK);
    
    /// Operator== for comparing two CVisualBlocks.
    /// @param[in] other Rhs of the comparison.
    /// @return Whether the CVisualBlocks match in all their attributes
    ///         (match in characters, foreground color and background color).
    bool operator==(const CVisualBlock& other) const;
    
    /// Operator!= for comparing two CVisualBlocks.
    /// @param[in] other Rhs of the comparison.
    /// @return Whether the CVisualBlocks differ at least in one of their attributes
    ///         (match in characters, foreground color and background color).
    bool operator!=(const CVisualBlock& other) const;
    
    /// Operator< for comparing two CVisualBlocks and implementing total ordering on them
    /// so they can be used in ordered associative containers.
    /// @param[in] other Rhs of the comparison.
    /// @return Comparison is done using std::tie on %m_Content, %m_ForegroundColor and %m_BackgroundColor.
    bool operator<(const CVisualBlock& other) const;
    
    /// Function for reading the CVisualBlock from a stream.
    /// Accepts format: "{[2 characters]|[foreground color]|[background color]}" (separated by '|')
    /// See EColor for more info about reading color from stream.
    /// @param[in] is Input stream that the CVisualBlock should be read from.
    /// @param[in] visualBlock CVisualBlock that the result of reading the stream should be stored into.
    friend std::istream& operator>>(std::istream& is, CVisualBlock& visualBlock);
    
    /// String of characters that the CVisualBlock is made out of.
    std::string m_Content;
    
    /// Foreground color - color of the characters in %m_Content.
    Color::EColor m_ForegroundColor;
    
    /// Background color - color of the characters in %m_Content.
    Color::EColor m_BackgroundColor;
};
