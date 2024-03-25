#include "CConfig.h"

using namespace std::string_literals;

void CConfig::load_values(const std::string& pathToConfig) {
    
    // Try to open the configuration file.
    std::ifstream file(pathToConfig);
    if (!file) {
        throw std::invalid_argument("could not open >"s + pathToConfig + "<"s);
    }
    
    // Read each line and try to parse the identifier with the value next to it.
    std::string line;
    int lineCnt = 0;
    while (std::getline(file >> std::ws, line)) {
        ++lineCnt;
        if (line.empty() || line[0] == '#') continue; // Empty line or line that is a comment.
        
        // Check if the line contains data specifier (char at the beginning of the line).
        if (line.size() >= 2 && !std::isspace(line[1])) {
            throw std::invalid_argument(
                    line_error("no type specifier", lineCnt, line));
        }
        
        char type;
        // Load the identifier of the value.
        std::string identifier;
        std::istringstream stream(line);
        stream >> type;
        if (!(stream >> identifier)) {
            throw std::invalid_argument(
                    line_error("could not load identifier", lineCnt, line));
        }
        
        // Find quotes that surround the value.
        size_t leftQuoteIndex = line.find('\"');
        size_t rightQuoteIndex = line.rfind('\"');
        if (leftQuoteIndex == std::string::npos) {
            throw CParseError(line_error("no quotes (\") found", lineCnt, line));
        }
        if (leftQuoteIndex == rightQuoteIndex) {
            throw CParseError(line_error("only single quote (\") found", lineCnt, line));
        }
        
        // Try loading the value represented by the string between the quotes.
        try {
            load_value(type, identifier, line.substr(leftQuoteIndex + 1, rightQuoteIndex - leftQuoteIndex - 1));
        } catch (std::invalid_argument& e) {
            throw CParseError(line_error(e.what(), lineCnt, line));
        }
        
    }
}

std::string CConfig::line_error(const std::string& errorMessage, int lineNumber, const std::string& line) {
    std::stringstream error;
    error << errorMessage << " on line " << lineNumber << ": >" << line << "<";
    return error.str();
}

void CConfig::load_value(char type, const std::string& identifier, const std::string& strToParse) {
    std::istringstream stream(strToParse);
    // Decide which config category should try to parse the string in stream.
    switch (type) {
        case 'b':
            m_Bool.load_value(identifier, stream);
            break;
        case 'i':
            m_Int.load_value(identifier, stream);
            break;
        case 'f':
            m_Double.load_value(identifier, stream);
            break;
        case 'c':
            m_Char.load_value(identifier, stream);
            break;
        case 'S':
            // Strings are loaded directly so no whitespaces will get skipped.
            m_String.load_value(identifier, strToParse);
            break;
        case 'C':
            m_Color.load_value(identifier, stream);
            break;
        case 'v':
            m_CVisualBlock.load_value(identifier, stream);
            break;
        case 't':
            m_Toughness.load_value(identifier, stream);
            break;
        default:
            throw CParseError(">"s + type + "< is an invalid type specifier"s);
    }
}

bool CConfig::are_all_identifiers_loaded(std::ostream& errorStream, int limit) const {
    int cnt = limit;
    
    // Go through all the config categories and print_stored_value their identifiers with no loaded value.
    print_remaining_identifiers(errorStream, cnt, m_Bool, "bool");
    if (cnt <= 0) return false;
    print_remaining_identifiers(errorStream, cnt, m_Int, "int");
    if (cnt <= 0) return false;
    print_remaining_identifiers(errorStream, cnt, m_Double, "double");
    if (cnt <= 0) return false;
    print_remaining_identifiers(errorStream, cnt, m_String, "string");
    if (cnt <= 0) return false;
    print_remaining_identifiers(errorStream, cnt, m_Char, "char");
    if (cnt <= 0) return false;
    print_remaining_identifiers(errorStream, cnt, m_Color, "color");
    if (cnt <= 0) return false;
    print_remaining_identifiers(errorStream, cnt, m_CVisualBlock, "visual block");
    if (cnt <= 0) return false;
    print_remaining_identifiers(errorStream, cnt, m_Toughness, "toughness");
    if (cnt <= 0) return false;
    
    return cnt == limit;
}

std::list<CVisualBlock> CConfig::get_sprites_of(const std::string& prefix) const {
    
    std::list<CVisualBlock> sprites;
    std::ostringstream numberStream;
    // Use the "_NUM_OF_SPRITES" to determine how many
    // sprites should be loaded for CMovableObject.
    numberStream << prefix << "_NUM_OF_SPRITES";
    int spriteCount = m_Int[numberStream.str()];
    switch (spriteCount) {
        // Number of sprites has to be 1, 2, 3, or 6.
        case 2:
        case 3:
        case 6:
            for (int i = 1; i <= spriteCount; ++i) {
                std::ostringstream stream;
                stream << prefix << "_SPRITE_" << i;
                sprites.emplace_back(m_CVisualBlock[stream.str()]);
            }
            break;
        default:
            sprites.emplace_back(m_CVisualBlock[prefix + "_SPRITE"]);
            break;
    }
    return sprites;
}


