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
    //! Checks to see if ANY u32string in the left starts with the right
    bool    any_starts(const std::vector<std::u32string>&haystack, std::u32string_view pattern);
    
    //! Checks to see if ANY u32string in the left starts with the right
    bool    any_starts(const std::vector<std::u32string_view>&haystack, std::u32string_view pattern);
    
    //! Checks to see if ANY u32string in the left starts with the right
    bool    any_starts(const std::initializer_list<std::u32string_view>&haystack, std::u32string_view pattern);

    //! Checks to see if ANY u32string in the left starts with the right
    bool    any_starts_igCase(const std::vector<std::u32string>&haystack, std::u32string_view pattern);
    
    //! Checks to see if ANY u32string in the left starts with the right
    bool    any_starts_igCase(const std::vector<std::u32string_view>&haystack, std::u32string_view pattern);
    
    //! Checks to see if ANY u32string in the left starts with the right
    bool    any_starts_igCase(std::initializer_list<std::u32string_view> haystack, std::u32string_view pattern);

    /*! \brief Checks the start of u32string
    
        This checks to see if the start of the given u32string matches the given pattern.
    */
    bool  starts(const char32_t* s, size_t n, const char32_t* pat, size_t nPath);

    /*! \brief Checks the start of u32string
    
        This checks to see if the start of the given u32string matches the given pattern.
    */
    bool  starts(std::u32string_view s, std::u32string_view pat);

    /*! \brief Checks the start of u32string
    
        This checks to see if the start of the given u32string matches the given pattern, ignoring case.
    */
    bool  starts_igCase(const char32_t* s, size_t n, const char32_t* pat, size_t nPath);

    /*! \brief Checks the start of u32string
    
        This checks to see if the start of the given u32string matches the given pattern, ignoring case.
    */
    bool  starts_igCase(std::u32string_view s, std::u32string_view pat);
}
