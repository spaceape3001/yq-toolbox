////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <initializer_list>
#include <string_view>
#include <vector>

namespace yq {
    //! Checks to see if ANY string in the left starts with the right
    bool    any_starts(const std::vector<std::string>&haystack, std::string_view pattern);
    
    //! Checks to see if ANY string in the left starts with the right
    bool    any_starts(const std::vector<std::string_view>&haystack, std::string_view pattern);
    
    //! Checks to see if ANY string in the left starts with the right
    bool    any_starts(const std::initializer_list<std::string_view>&haystack, std::string_view pattern);

    //! Checks to see if ANY string in the left starts with the right
    bool    any_starts_igCase(const std::vector<std::string>&haystack, std::string_view pattern);
    
    //! Checks to see if ANY string in the left starts with the right
    bool    any_starts_igCase(const std::vector<std::string_view>&haystack, std::string_view pattern);
    
    //! Checks to see if ANY string in the left starts with the right
    bool    any_starts_igCase(std::initializer_list<std::string_view> haystack, std::string_view pattern);

    /*! \brief Checks the start of string
    
        This checks to see if the start of the given string matches the given pattern.
    */
    bool  starts(const char* s, size_t n, const char* pat, size_t nPath);

    /*! \brief Checks the start of string
    
        This checks to see if the start of the given string matches the given pattern.
    */
    bool  starts(std::string_view s, std::string_view pat);

    /*! \brief Checks the start of string
    
        This checks to see if the start of the given string matches the given pattern, ignoring case.
    */
    bool  starts_igCase(const char* s, size_t n, const char* pat, size_t nPath);

    /*! \brief Checks the start of string
    
        This checks to see if the start of the given string matches the given pattern, ignoring case.
    */
    bool  starts_igCase(std::string_view s, std::string_view pat);
}
