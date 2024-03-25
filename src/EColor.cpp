#include "EColor.h"

using namespace Color;

std::istream& operator>>(std::istream& is, EColor& color) {
    // Static is used so the map does not have to get regenerated
    // every time we call this function.
    static const std::unordered_map<std::string, Color::EColor> STR_TO_COLOR = {
            {"BLACK",       BLACK},
            {"RED",         RED},
            {"GREEN",       GREEN},
            {"YELLOW",      YELLOW},
            {"BLUE",        BLUE},
            {"MAGENTA",     MAGENTA},
            {"CYAN",        CYAN},
            {"WHITE",       WHITE},
            {"DEFAULT",     DEFAULT},
    };
    
    std::string str;
    is >> str;
    if (str == "-") {
        color = BLACK;
        return is;
    }
    
    auto it = STR_TO_COLOR.find(str);
    if (it == STR_TO_COLOR.end()) {
        is.setstate(std::ios_base::failbit);
    } else {
        color = it->second;
    }
    return is;
}
