////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <initializer_list>
#include <string_view>
#include <vector>
#include <yq-toolbox/basic/Compare.hpp>
#include <yq-toolbox/typedef/string_pairs.hpp>
#include <yq-toolbox/typedef/string_sets.hpp>

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
    
    Compare compare(std::u32string_view  a, std::u32string_view  b);
    Compare compare_igCase(std::u32string_view  a, std::u32string_view  b);


    
    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(std::u32string_view haystack, std::u32string_view needle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(std::u32string_view haystack, std::u32string_view needle);

    bool    ends(std::u32string_view hay, std::u32string_view pat);

    /*! \brief First non-blank character
        This returns the first non-blank character seen, or NULL if none found
    */
    char32_t  first_non_blank_char32_t(std::u32string_view sv);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::u32string_view, std::u32string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::u32string_view, std::u32string_view, std::u32string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::u32string_view, std::u32string_view, std::u32string_view, std::u32string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::u32string_view  first_non_empty(std::initializer_list<std::u32string_view>);

    /*! \brief Tests for emptiness
    
        \return TRUE if BOTH first & second are empty
    */
    inline bool is_empty(const u32string_view_pair_t& p)
    {
        return p.first.empty() && p.second.empty();
    }

    bool        is_equal(std::u32string_view, std::u32string_view);

    /*! \brief Tests if b > a ignoring case
    
        This ignores case differences as it compares u32strings a & b.
    */
    bool  is_greater_igCase(std::u32string_view a, std::u32string_view b);
    

    /*! \brief Tests if b < a ignoring case
    
        This ignores case differences as it compares u32strings a & b.
    */
    bool  is_less_igCase(std::u32string_view a, std::u32string_view b);

    
    /*! \brief Test to see if u32string matches the pattern
    
        (this one is here so it signature matches the other
    */
    bool  is_in(std::u32string_view str, std::u32string_view pat);

    /*! \brief Test to see if u32string matches one of the patterns
    */
    bool  is_in(std::u32string_view str, std::initializer_list<std::u32string_view> pat);
    
    /*! \brief Test to see if u32string matches one of the patterns
    */
    bool  is_in(std::u32string_view str, const u32string_view_set_t& pat);

    /*! \brief Test to see if u32string matches one of the patterns
    */
    bool  is_in(std::u32string_view str, const std::vector<std::u32string_view>& pat);
    
    bool is_in(char32_t, std::u32string_view);
        
    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(char32_t, char32_t);

    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(std::u32string_view, std::u32string_view);


    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at(std::u32string_view haystack, size_t pos, std::u32string_view pattern);

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at_igCase(std::u32string_view haystack, size_t pos, std::u32string_view pattern);
    
    
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
