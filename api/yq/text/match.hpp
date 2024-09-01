////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <initializer_list>
#include <string_view>
#include <vector>
#include <yq/basic/Compare.hpp>
#include <yq/typedef/string_pairs.hpp>
#include <yq/typedef/string_sets.hpp>

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

    Compare compare(std::string_view  a, std::string_view  b);
    Compare compare_igCase(std::string_view  a, std::string_view  b);

    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle
    */
    bool    contains(std::string_view haystack, std::string_view needle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle);

    /*! \brief Checks if the haystack has the needle (ignoring case)
    */
    bool    contains_igCase(std::string_view haystack, std::string_view needle);


    bool    ends(std::string_view hay, std::string_view pat);

    /*! \brief First non-blank character
        This returns the first non-blank character seen, or NULL if none found
    */
    char32_t  first_non_blank_char(std::string_view sv);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::string_view, std::string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::string_view, std::string_view, std::string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::string_view, std::string_view, std::string_view, std::string_view);

    /*! \brief First argument that isn't empty
    
        This returns the first argument that isn't empty.  If all area empty, a reference to the last one is returned
    */
    std::string_view  first_non_empty(std::initializer_list<std::string_view>);

    /*! \brief Tests for emptiness
    
        \return TRUE if BOTH first & second are empty
    */
    inline bool is_empty(const string_view_pair_t& p)
    {
        return p.first.empty() && p.second.empty();
    }

    bool        is_equal(std::string_view, std::string_view);

    /*! \brief Tests if b > a ignoring case
    
        This ignores case differences as it compares strings a & b.
    */
    bool  is_greater_igCase(std::string_view a, std::string_view b);
    
    /*! \brief Test to see if string matches the pattern
    
        (this one is here so it signature matches the other
    */
    bool  is_in(std::string_view str, std::string_view pat);

    /*! \brief Test to see if string matches one of the patterns
    */
    bool  is_in(std::string_view str, std::initializer_list<std::string_view> pat);
    
    /*! \brief Test to see if string matches one of the patterns
    */
    bool  is_in(std::string_view str, const string_view_set_t& pat);

    /*! \brief Test to see if string matches one of the patterns
    */
    bool  is_in(std::string_view str, const std::vector<std::string_view>& pat);
        
    /*! \brief Tests if b < a ignoring case
    
        This ignores case differences as it compares strings a & b.
    */
    bool  is_less_igCase(std::string_view a, std::string_view b);

    bool  is_less_igCase_u8(std::string_view a, std::string_view b);

    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(char, char);

    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(std::string_view, std::string_view);

    /*! \brief Tests for a valid key
    
        Test for a valid key, one that can be a component of a full key.  Directory paths, 
        extensions, are not tolerated by this routine.  A valid key is one that starts with
        a letter or a number, and is followed by an unlimited number of letters, 
        numbers, "_", "+", or "-".
    */
    bool        is_valid_key(std::string_view);

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at(std::string_view haystack, size_t pos, std::string_view pattern);

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at_igCase(std::string_view haystack, size_t pos, std::string_view pattern);
    
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
    bool  starts_igCase(std::string_view s, std::string_view pat);}
