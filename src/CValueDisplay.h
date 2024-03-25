#pragma once

#include "CTerminal.h"
#include <iostream>
#include <string>

/// @brief Class used for displaying a value with a potential name of the value next to it.
///        This class re-renders the value only if it changes.
template<typename T>
class CValueDisplay {
public:
    
    /// Constructor of CValueDisplay.
    /// @param[in] length The number of characters that should be erased when the value changes.
    /// @param[in] nameOfValue Text that will be displayed next to value.
    /// @param[in] valueColor Color that the value should be displayed in.
    explicit CValueDisplay(int length, std::string nameOfValue = "", Color::EColor valueColor = Color::WHITE)
            : m_X(0), m_Y(0), m_Length(length), m_PreviousValue(), m_ValueName(std::move(nameOfValue)),
              m_ValueColor(valueColor) {}
    
    /// Constructor of CValueDisplay.
    /// @param[in] x The X coordinate of where this UI element should be on the screen.
    /// @param[in] y The Y coordinate of where this UI element should be on the screen.
    /// @param[in] length The number of characters that should be erased when the value changes.
    /// @param[in] nameOfValue Text that will be displayed next to value.
    /// @param[in] valueColor Color that the value should be displayed in.
    CValueDisplay(int x, int y, int length, std::string nameOfValue = "", Color::EColor valueColor = Color::WHITE)
            : m_X(x), m_Y(y), m_Length(length), m_PreviousValue(), m_ValueName(std::move(nameOfValue)),
              m_ValueColor(valueColor) {}
    
    /// Sets the element's position on the screen.
    /// @param[in] x The X coordinate of where this UI element should be on the screen.
    /// @param[in] y The Y coordinate of where this UI element should be on the screen.
    void set_position(int x, int y);
    
    /// Initial render that displays the name of the value,
    /// since it does not need to be updated later.
    /// @param[in, out] outputStream Stream that the UI element should be rendered into.
    void first_render(std::ostream& outputStream) const;
    
    /// Renders %newValue if is different to the previous call of this method.
    /// @param[in] newValue New value that should be rendered. It gets stored so
    ///                     it could be compared later if it has changed or not.
    /// @param[in, out] outputStream Stream that the UI element should be rendered into.
    void update(const T& newValue, std::ostream& outputStream);
    
    /// Renders internal state of of this UI element.
    /// This is useful when the rendering breaks in some way - after clearing the screen
    /// we can call this method to draw what was previously there.
    /// @param[in, out] outputStream Stream that the UI element should be rendered into.
    void re_render(std::ostream& outputStream) const;

private:
    
    /// Renders stored value of type T into the outputStream.
    /// @param[in, out] outputStream Stream that the stored internal value (%m_PreviousValue) should be rendered into.
    void print_stored_value(std::ostream& outputStream) const;
    
    /// The X coordinate of where this UI element should be on the screen.
    int m_X;
    
    /// The Y coordinate of where this UI element should be on the screen.
    int m_Y;
    
    /// The number of characters that should be erased when the value changes.
    int m_Length;
    
    /// Internally stored displayed value. It is used for comparison
    /// with a new value, so it it re-rendered only if it changes.
    T m_PreviousValue;
    
    /// Text that will be displayed next to value.
    std::string m_ValueName;
    
    /// Color that the value should be displayed in.
    Color::EColor m_ValueColor;
};

template<typename T>
void CValueDisplay<T>::print_stored_value(std::ostream& outputStream) const {
    
    // Move cursor to the position where the value is displayed and overwrite it with spaces.
    outputStream << CTerminal::reset_graphics() << CTerminal::move_cursor_to(m_X + m_ValueName.length(), m_Y);
    for (int i = 0; i < m_Length; ++i)
        outputStream << " ";
    
    // The old value is now erased. Print the new one over it.
    outputStream << CTerminal::move_cursor_to(m_X + m_ValueName.length(), m_Y);
    outputStream << CTerminal::set_color(m_ValueColor) << m_PreviousValue;
}

template<typename T>
void CValueDisplay<T>::re_render(std::ostream& outputStream) const {
    first_render(outputStream);
    print_stored_value(outputStream);
}

template<typename T>
void CValueDisplay<T>::set_position(int x, int y) {
    m_X = x;
    m_Y = y;
}

template<typename T>
void CValueDisplay<T>::first_render(std::ostream& outputStream) const {
    outputStream << CTerminal::reset_graphics() << CTerminal::move_cursor_to(m_X, m_Y)
                 << m_ValueName;
}

template<typename T>
void CValueDisplay<T>::update(const T& newValue, std::ostream& outputStream) {
    if (m_PreviousValue != newValue) {
        m_PreviousValue = newValue;
        print_stored_value(outputStream);
    }
}

