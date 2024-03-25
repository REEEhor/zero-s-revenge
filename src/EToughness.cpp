#include "EToughness.h"

using namespace Toughness;

std::istream& operator>>(std::istream& is, EToughness& toughness) {
    // Static so the map does not get regenerated every time we
    // call this function.
    static const std::unordered_map<std::string, EToughness> STR_TO_TOUGHNESS = {
            {"NONE",   NONE},
            {"LOW",    LOW},
            {"MIDDLE", MIDDLE},
            {"HIGH",   HIGH}
    };
    
    std::string str;
    is >> str;
    auto it = STR_TO_TOUGHNESS.find(str);
    if (it == STR_TO_TOUGHNESS.end()) {
        is.setstate(std::ios_base::failbit);
    } else {
        toughness = it->second;
    }
    return is;
}
