#pragma once

#include "CConfigCategory.h"
#include "EColor.h"
#include "EToughness.h"
#include "CVisualBlock.h"
#include <fstream>
#include <sstream>
#include <list>

/// @brief Class that loads values from a configuration file and
///        makes them possible to look up by their identifiers.
///        The format is in the form of ' data_type_specifier   value_identifier  "value" '.
class CConfig {
public:
    
    /// Set of bools that can be registered, stored and looked up.
    CConfigCategory<bool> m_Bool;
    /// Set of ints that can be registered, stored and looked up.
    CConfigCategory<int> m_Int;
    /// Set of doubles that can be registered, stored and looked up.
    CConfigCategory<double> m_Double;
    /// Set of chars that can be registered, stored and looked up.
    CConfigCategory<char> m_Char;
    /// Set of std::strings that can be registered, stored and looked up.
    CConfigCategory<std::string> m_String;
    /// Set of enum EColor that can be registered, stored and looked up.
    CConfigCategory<Color::EColor> m_Color;
    /// Set of enum EToughness that can be registered, stored and looked up.
    CConfigCategory<Toughness::EToughness> m_Toughness;
    /// Set of instances of CVisualBlock that can be registered, stored and looked up.
    CConfigCategory<CVisualBlock> m_CVisualBlock;
    
    /// Loads all values from the file and throws error if any of them are found.
    /// @param[in] pathToConfig Path to the configuration file that the values should be loaded from.
    /// @throws std::invalid_argument when the config file could not be opened.
    /// @throws std::invalid_argument if the line in the config line does no have a type specifier.
    /// @throws std::invalid_argument if the identifier could not be loaded (which means it probably does not exist).
    /// @throws std::invalid_argument if there are not two quotes present on the line.
    /// @throws CParseError if the value could not be be parsed correctly (it is invalid or could not be read from the stream).
    void load_values(const std::string& pathToConfig);
    
    /// Checks if all registered identifiers have a value assigned to them.
    /// If any value is missing it can be written to the stream.
    /// @param[out] errorStream Stream which should be used to list the identifiers with no value.
    /// @param[in] limit Maximum number of identifiers that can be listed.
    /// @return Whether all identifiers have a value assigned to them.
    bool are_all_identifiers_loaded(std::ostream& errorStream, int limit = 10) const;
    
    /// Helper method for getting a list of sprites of CMovableObject since it there are up to seven individual
    /// variables that have to be loaded.
    /// @param[in] prefix Prefix of the sprites to get.
    /// @return list of loaded sprites.
    [[nodiscard]] std::list<CVisualBlock> get_sprites_of(const std::string& prefix) const;
private:
    
    /// Helper method for formatting an error found on a line in configuration file.
    /// @param[in] errorMessage Error message associated with the line to be displayed.
    /// @param[in] lineNumber Number of the line that the error happened on.
    /// @param[in] line The entire line so the error can display the context how the invalid line looks.
    static std::string line_error(const std::string& errorMessage, int lineNumber, const std::string& line);
    
    /// Tries to load one value from configuration file.
    /// @param[in] type Character representing which data type the value is.
    /// @param[in] identifier Identifier of the value.
    /// @param[in] strToParse String that should the value be parsed from.
    /// @throws CParseError if the type is not a valid data type specifier.
    /// @throws CParseError if the value could not be read from the stream.
    /// @throws std::invalid_argument if the value was loaded but is not valid.
    /// @throws std::invalid_argument if the identifier is not registered.
    /// @throws std::invalid_argument if a value with the identifier has already been loaded.
    /// @throws std::invalid_argument if the loaded value was registered to be unique but is not.
    void load_value(char type, const std::string& identifier, const std::string& strToParse);
    
    /// Prints identifiers that have no assigned value to them.
    /// @param[out] os Output stream to print_stored_value the identifiers into.
    /// @param[in, out] limit Maximum number of identifiers to print_stored_value. The value gets decremented by
    ///                       the number of identifiers printed.
    /// @param[in] category Config category to get the remaining identifiers from.
    /// @param[in] nameOfType String naming the data type ("string", "int", "bool", ...).
    template<typename T>
    void print_remaining_identifiers(std::ostream& os, int& limit, const CConfigCategory<T>& category,
                                     const std::string& nameOfType) const;
};

template<typename T>
void CConfig::print_remaining_identifiers(std::ostream& os, int& limit, const CConfigCategory<T>& category,
                                          const std::string& nameOfType) const {
    for (auto& [key, value]: category.remaining_identifiers()) {
        if (--limit <= 0) break;
        os << "missing " << nameOfType << " with identifier >" << key << "<\n";
    }
}
