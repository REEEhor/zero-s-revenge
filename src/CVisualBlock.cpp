#include "CVisualBlock.h"


CVisualBlock::CVisualBlock(std::string content, Color::EColor fgColor, Color::EColor bgColor)
        : m_Content(std::move(content)), m_ForegroundColor(fgColor), m_BackgroundColor(bgColor) {}

bool CVisualBlock::operator==(const CVisualBlock& other) const {
    return std::tie(m_ForegroundColor, m_BackgroundColor, m_Content)
           == std::tie(other.m_ForegroundColor, other.m_BackgroundColor, other.m_Content);
}

bool CVisualBlock::operator!=(const CVisualBlock& other) const {
    return !(*this == other);
}

std::istream& operator>>(std::istream& is, CVisualBlock& visualBlock) {
    std::string buffer;
    std::getline(is, buffer, '}');
    
    // Shortest string in buffer is: "{--|-|-" => 7 characters.
    if (buffer.size() < 7
        || buffer[0] != '{'
        || buffer[3] != '|') {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    
    // Check for separators.
    std::string content = {buffer[1], buffer[2]};
    std::string colorString = (buffer.substr(4));
    bool wasSeparatorFound = false;
    for (char& c: colorString) {
        if (c == '|') {
            wasSeparatorFound = true;
            c = ' ';
        }
    }
    
    if (!wasSeparatorFound) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    
    // Load colors.
    std::istringstream colorStream(colorString);
    Color::EColor foreground;
    Color::EColor background;
    if (!(colorStream >> foreground) || !(colorStream >> background)) {
        is.setstate(std::ios_base::failbit);
        return is;
    }
    
    visualBlock = CVisualBlock(content, foreground, background);
    return is;
}

bool CVisualBlock::operator<(const CVisualBlock& other) const {
    return std::tie(m_Content, m_ForegroundColor, m_BackgroundColor)
           < std::tie(other.m_Content, other.m_ForegroundColor, other.m_BackgroundColor);
}

