////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/preamble.hpp>
#include <yq/trait/always_false.hpp>
#include <cstring>
#include <vector>

namespace yq {

    
    //! Concatenates the given 32-bit UTF character on to the string as UTF-8
    std::string&  operator+=(std::string&, char32_t);
    
    
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

    
    /*! \brief Blanks all C++ comments in the given string 
    
        This goes over the string, all C++ comments are turned into spaces
    */
    void  blank_cpp_comments(std::string&);
    
    /*! \brief Capitalizes each word
    
        This capitalizes each word in the string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
    */
    std::string  capitalize(const char*s, size_t n);

    /*! \brief Capitalizes each word
    
        This capitalizes each word in the string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    String view (which is auto-gen from std::string if need be.
    */
    std::string  capitalize(std::string_view s);
    
    /*! \brief Conctenates two strings
    
        Concatenates two strings together.
        
        \param[in] a    First string
        \param[in] b    Second string
        \return new string of the concatenation
    */
    std::string concat(std::string_view a, std::string_view b);

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

    /*! \brief Copies the string
    
        This doesn't return a reference, but actually makes a copy.
    */
    inline std::string  copy(std::string_view s)
    {
        return std::string(s);
    }
    
    string_set_t        copy(const string_view_set_t&);

    /*! \brief Copies the vector of string
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::string>  copy(const std::vector<std::string>&);

    /*! \brief Copies the vector of string-views
    
        This doesn't return a reference, but actually makes a copy.
    */
    std::vector<std::string>  copy(const std::vector<std::string_view>&);
    
    std::vector<std::string>  copy(std::initializer_list<std::string_view>);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(const char* s, size_t n);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(std::string_view s);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(const char* s, size_t n, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(std::string_view s, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(const char* s, size_t n, char32_t ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters(std::string_view s, char32_t ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(const char* s, size_t n, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(std::string_view s, char ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(const char* s, size_t n, char32_t ch);

    /* !\brief Counts the number of charcters
    */
    size_t  count_characters_igCase(std::string_view s, char32_t ch);

    /*! \brief Counts the opening number of space characters
    */
    size_t  count_start_spaces(std::string_view);
    
    /*! \brief Counts the number of the specified character that start the string
    */
    size_t  count_starts(std::string_view, char);

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

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!
    
        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint8_t n, char f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint16_t n, char f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint32_t n, char f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint64_t n, char f='0');
    
    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint8_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint16_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint32_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint64_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint8_t n, char f);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint16_t n, char f);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint32_t n, char f);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint64_t n, char f);


    
    /*! \brief Formats the given number in scientifica notation
        
        \param[in] v        Value to format
        \param[in] digits   Prescision
        \result Formatted string
    */
    std::string  fmt_scientific(double v, int digits=-1);

    /*! \brief Formats the given number in scientifica notation
        
        \param[in] v        Value to format
        \param[in] digits   Prescision
        \result Formatted string
    */
    std::string  fmt_scientific(float v, int digits=-1);
    
    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s pointer to string
        \param[in] n length of the string
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::string_view>  hard_wrap(const char*s, size_t n, size_t width);
    
    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::string_view>  hard_wrap(std::string_view s, size_t width);

    /*! \brief Tests for an alphanumeric character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_alnum(char ch)
    {
        return ::isalnum(ch);
    }
    
    /*! \brief Tests for an alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_alpha(char ch)
    {
        return ::isalpha(ch);
    }

    /*! \brief Tests entire string for alpha
    
        \param[in] s pointer to string
        \param[in] n length of the string
        \return TRUE if the ENTIRE string is alpha characters
    */
    bool is_alpha(const char*s, size_t n);
    
    /*! \brief Tests entire string for alpha
    
        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return TRUE if the ENTIRE string is alpha characters
    */
    bool is_alpha(std::string_view);

    /*! \brief Tests for blank character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_blank(char ch)
    {
        return ::isblank(ch);
    }

    /*! \brief Tests for blank string
        \param[in] s pointer to string
        \param[in] n length of the string
    */
    bool  is_blank(const char*s, size_t n);

    /*! \brief Tests for blank string
        \param[in] s    String view (which is auto-gen from std::string if need be.
    */
    bool  is_blank(std::string_view s);
    
    /*! \brief Tests for control character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_control(char ch)
    {   
        return ::iscntrl(ch);
    }
    
    /*! \brief Tests for numeric digit
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_digit(char ch)
    {
        return ::isdigit(ch);
    }
    
    /*! \brief Tests for emptiness
    
        \return TRUE if BOTH first & second are empty
    */
    inline bool is_empty(const string_view_pair_t& p)
    {
        return p.first.empty() && p.second.empty();
    }
    
    bool        is_equal(std::string_view, std::string_view);

    /*! \brief Tests for graphical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_graph(char ch)
    {
        return ::isgraph(ch);
    }
    
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

    /*! \brief Tests for lower-case alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_lower(char ch)
    {
        return ::islower(ch);
    }

    /*! \brief Tests for new line character
    */
    bool         is_newline(char);

    /*! \brief Tests for printable character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_print(char ch)
    {
        return ::isprint(ch);
    }
    
    /*! \brief Tests for punctuation character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_punct(char ch)
    {
        return ::ispunct(ch);
    }

    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(char, char);


    /*! \brief Tests for equality while ignoring case
    */
    bool  is_similar(std::string_view, std::string_view);

    /*! \brief Tests for white-space character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_space(char ch)
    {
        return ::isspace(ch);
    }
    
    /*! \brief Tests for white-space characters
        \return TRUE if ALL characters in the string view are white space
    */
    bool  is_space(std::string_view);
    
    /*! \brief Tests for upper-case alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_upper(char ch)
    {
        return ::isupper(ch);
    }
    
    /*! \brief Tests for a valid key
    
        Test for a valid key, one that can be a component of a full key.  Directory paths, 
        extensions, are not tolerated by this routine.  A valid key is one that starts with
        a letter or a number, and is followed by an unlimited number of letters, 
        numbers, "_", "+", or "-".
    */
    bool        is_valid_key(std::string_view);
    
    /*! \brief Tests for hexadecimal digit character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    inline bool  is_xdigit(char ch)
    {
        return ::isxdigit(ch);
    }
    

    /*! \brief Joins the collection into a string
        \param[in] collection  The collection
        \param[in] separator   The separator between elements.
        \return The joined string
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, std::string_view separator);
    
    /*! \brief Joins the collection into a string
        \param[in] collection  The collection
        \param[in] separator   The separator between elements.
        \return The joined string
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, char separator);

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at(std::string_view haystack, size_t pos, std::string_view pattern);

    /*! \brief Checks to see if the haystack matches the pattern at position
    
        \note Check will end at the length pattern, so "matches_at("foobar rocks", 3, "bar")" will be TRUE
    */
    bool        matches_at_igCase(std::string_view haystack, size_t pos, std::string_view pattern);
    
    /*! \brief Left pads the result until the character count is met */
    std::string     pad_left(std::string_view data, size_t minSize, char ch=' ');
    
    /*! \brief Left pads the result until the character count is met */
    std::string     pad_left(std::string_view data, size_t minSize, char32_t ch);

    /*! \brief Right pads the result until the character count is met */
    std::string     pad_right(std::string_view data, size_t minSize, char ch=' ');

    /*! \brief Right pads the result until the character count is met */
    std::string     pad_right(std::string_view data, size_t minSize, char32_t ch);
    
    //! Will *attempt* to make a plural form, won't be perfect
    std::string     pluralize(std::string_view);
    
    /*! \brief Replaces all instances of old character with new character */
    size_t          replace_all(std::string&, char what, char with);
    
    /*! \brief Replaces all instances of old character with new character ignoring case */
    size_t          replace_all_igCase(std::string&, char what, char with);

    /*! \brief Set left to right if left is empty OR override is true
    
        \note if B is empty, this is a NOP
    */
    std::string&    set_if_empty(std::string&, std::string_view, bool fOverride=false);
    
    /*! \brief Simplifies the given string
    
        Simplifying a string removes start & end whitespace, replaces interior spaces with a single space character.
    */
    std::string     simplify(const char*s, size_t n, char sp=' ');

    /*! \brief Simplifies the given string
    */
    std::string     simplify(std::string_view, char sp=' ');

    /*! \brief Splits the string up into the specified equal number of chunks
    
        This routine will split the incoming string into the given number of
        chunks as evenly as possible.  (ie, adjacent items might be +- 1 in size)
        
        \note This returns REFERENCES to the original string, so it must live.
        \note If n<number, some of the returned entries will be empty.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] number   Number of entries
    */
    std::vector<std::string_view>  split(const char* s, size_t n, size_t number); 

    /*! \brief Splits the string up into the specified equal number of chunks
    
        This routine will split the incoming string into the given number of
        chunks as evenly as possible.  (ie, adjacent items might be +- 1 in size)

        \note This returns REFERENCES to the original string, so it must live.
        \note If s.size()<number, some of the returned entries will be empty.

        \param[in] s        String view
        \param[in] number   Number of entries
    */
    std::vector<std::string_view>  split(std::string_view s, size_t number); 

    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split(const char*s, size_t n, char ch); 

    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split(std::string_view s, char ch); 

    /*! \brief Splits the string, up to number entries
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.
        
        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::string_view>  split(const char* s, size_t n, char ch, size_t number); 

    /*! \brief Splits the string, up to number entries
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.
        
        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::string_view>  split(std::string_view s, char ch, size_t number); 

    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split(const char*s , size_t n, char32_t ch); 

    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split(std::string_view s, char32_t ch); 
    
    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::string_view>  split(const char* s, size_t n, char32_t cn, size_t number); 

    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::string_view>  split(std::string_view s, char32_t ch, size_t number); 

    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] p        pointer to pattern string
        \param[in] pn       length of the pattern string
    */
    std::vector<std::string_view>  split(const char* s, size_t n, const char* p, size_t pn);

    /*! \brief Splits the string
    
        This routine splits the incoming string at the specified string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        String view
        \param[in] p        pattern string
    */
    std::vector<std::string_view>  split(std::string_view s, std::string_view p);

    /*! \brief Splits the string ignoring case
    
        This routine splits the incoming string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split_igCase(const char*s , size_t n, char ch); 

    /*! \brief Splits the string ignoring case
    
        This routine splits the incoming string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        string
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split_igCase(std::string_view s, char ch); 

    /*! \brief Splits the string ignoring case
    
        This routine splits the incoming string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split_igCase(const char* s, size_t n, char32_t ch); 

    /*! \brief Splits the string ignoring case
    
        This routine splits the incoming string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        string
        \param[in] ch       Character being split on
    */
    std::vector<std::string_view>  split_igCase(std::string_view s, char32_t ch); 
    
    /*! \brief Splits the string ignoring case
    
        This routine splits the incoming string at the specified string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        pointer to string
        \param[in] n        length of the string
        \param[in] p        pointer to pattern string
        \param[in] pn       length of the pattern string
    */
    std::vector<std::string_view>  split_igCase(const char*s, size_t n, const char* p, size_t pn);

    /*! \brief Splits the string ignoring case
    
        This routine splits the incoming string at the specified string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original string, so it must live.

        \param[in] s        String view
        \param[in] p        pattern string
    */
    std::vector<std::string_view>  split_igCase(std::string_view s, std::string_view p);

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

    const char*         strany(std::string_view haystack, std::string_view needle);

    /*! \brief Strips the LAST extension
    
        This returns the input MINUS the last extension, call repeatedly to remove more than one.
    */
    std::string_view    strip_extension(std::string_view);

    /*! \brief Strips ALL spaces from the input
    */
    std::string  strip_spaces(const char* s, size_t n);

    /*! \brief Strips ALL spaces from the input
    */
    std::string  strip_spaces(std::string_view);
    
    using ::strlen;

    /*! \brief Finds the next character 
    
        \param[in] s    Pointer to string
        \param[in] n    Number of bytes to the string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char*  strnchr(const char*s, size_t n, char ch);

    /*! \brief Finds the next character 
    
        \param[in] s    std::string view
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char*  strnchr(std::string_view s, char ch);

    /*! \brief Finds the next character 
    
        \param[in] s    Pointer to string
        \param[in] n    Number of bytes to the string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char*  strnchr(const char*s, size_t n, char32_t ch);

    /*! \brief Finds the next character (ignoring case)
    
        \param[in] s    Pointer to string
        \param[in] n    Number of bytes to the string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char*  strnchr_igCase(const char*s, size_t n, char ch);

    /*! \brief Finds the next character (ignoring case)
    
        \param[in] s    Pointer to string
        \param[in] n    Number of bytes to the string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char*  strnchr_igCase(const char*s, size_t n, char32_t ch);


    #ifdef WIN32
            //  until MSVC decides to grow up and get with the times....
    inline size_t  strnlen(const char* z, size_t cb)
    {
        return strlen_s(z, cb);
    }
    #else
    using ::strncasecmp;
    using ::strnlen;
    #endif
    
    
    /*! \brief Finds the first needle
    
        \param[in]  haystack    The bigger string
        \param[in]  nHay        Size of the haystack
        \param[in]  needle      The search term
        \param[in]  nNeedle     Size of the needle
        
        \return pointer to characte rif ound, nullptr otherwise
    */
    const char* strnstr(const char* haystack, size_t nHay, const char* needle, size_t nNeedle);

    /*! \brief Finds the first needle (ignoring case)
    
        \param[in]  haystack    The bigger string
        \param[in]  nHay        Size of the haystack
        \param[in]  needle      The search term
        \param[in]  nNeedle     Size of the needle
        
        \return pointer to characte rif ound, nullptr otherwise
    */
    const char* strnstr_igCase(const char* haystack, size_t nHay, const char* needle, size_t nNeedle);

    /*! \brief Decodes the given string into a boolean
    
    
        This trims whitespace from both ends & decodes the non-whitespace text.  
        For false, it accepts 0, n, no, f, false.
        For true, it accepts 1, y, yes, t, true.
        All other inputs incur an invalid result (false/false).
        
        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<bool>  to_boolean(const char*s, size_t n);

    /*! \brief Decodes the given string into a boolean
    
        For false, it accepts 0, n, no, f, false.
        For true, it accepts 1, y, yes, t, true.
        All other inputs incur an invalid result.
        All other inputs incur an invalid result (false/false).
        
        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return The result
    */
    Expect<bool>  to_boolean(std::string_view s);

    /*! \brief Decodes the given string into a dobule
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        \return The result
    */
    Expect<double>  to_double(const char*s, size_t n);

    /*! \brief Decodes the given string into a dobule
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return The result
    */
    Expect<double>  to_double(std::string_view s);

    /*! \brief Decodes the given string into a float
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        \return The result
    */
    Expect<float>   to_float(const char*s, size_t n);

    /*! \brief Decodes the given string into a float
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<float>   to_float(std::string_view);


    /*! \brief Decodes the given hex string into an unsigned
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        \return The result
    */
    Expect<unsigned> to_hex(const char*s, size_t n);

    /*! \brief Decodes the given hex string into an unsigned
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return The result
    */
    Expect<unsigned> to_hex(std::string_view s);

    /*! \brief Decodes the given hex string into an unsigned 8-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        \return The result
    */
    Expect<uint8_t>  to_hex8(const char*s, size_t n);

    /*! \brief Decodes the given hex string into an unsigned 8-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return The result
    */
    Expect<uint8_t>  to_hex8(std::string_view s);

    /*! \brief Decodes the given hex string into an unsigned 16-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        \return The result
    */
    Expect<uint16_t>  to_hex16(const char*s, size_t n);

    /*! \brief Decodes the given hex string into an unsigned 16-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return The result
    */
    Expect<uint16_t>  to_hex16(std::string_view s);

    /*! \brief Decodes the given hex string into an unsigned 32-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        \return The result
    */
    Expect<uint32_t>  to_hex32(const char*s, size_t n);

    /*! \brief Decodes the given hex string into an unsigned 32-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return The result
    */
    Expect<uint32_t>  to_hex32(std::string_view s);

    /*! \brief Decodes the given hex string into an unsigned 64-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        \return The result
    */
    Expect<uint64_t>  to_hex64(const char*s, size_t n);

    /*! \brief Decodes the given hex string into an unsigned 64-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        \return The result
    */
    Expect<uint64_t>  to_hex64(std::string_view s);
    
        /*! \brief Decodes the given string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<int>   to_int(const char*s, size_t n);

    /*! \brief Decodes the given string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<int>  to_int(std::string_view s);

    /*! \brief Decodes the given string into an 8-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<int8_t>  to_int8(const char*s, size_t n);

    /*! \brief Decodes the given string into an 8-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<int8_t> to_int8(std::string_view s);

    /*! \brief Decodes the given string into a 16-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<int16_t>  to_int16(const char*s, size_t n);

    /*! \brief Decodes the given string into a 16-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<int16_t>  to_int16(std::string_view s);

    /*! \brief Decodes the given string into a 32-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<int32_t>  to_int32(const char*s, size_t n);

    /*! \brief Decodes the given string into a 32-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<int32_t>  to_int32(std::string_view s);

    /*! \brief Decodes the given string into a 64-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<int64_t>  to_int64(const char*s, size_t n);

    /*! \brief Decodes the given string into a 64-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<int64_t>  to_int64(std::string_view s);

    /*! \brief Decodes the given string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<int>  to_integer(const char*s, size_t n);

    /*! \brief Decodes the given string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<int>  to_integer(std::string_view s);

    /*! \brief Converts to lower case
    
        Harmonized overload (for name consistency) to convert a character to lower case. 
        (If it's not upper case, then the input argument is returned.)
    */
    inline char  to_lower(char ch)
    {
        return ::tolower(ch);
    }
    
    /*! \brief Converts to lower case
    
        Converts the given string to lowercase (as unicode characters)
    */
    std::string  to_lower(std::string_view s);

    Expect<uint8_t>   to_octal8(const char*s, size_t n);
    Expect<uint8_t>   to_octal8(std::string_view s);

    Expect<uint16_t>  to_octal16(const char*s, size_t n);
    Expect<uint16_t>  to_octal16(std::string_view s);

    Expect<uint32_t>  to_octal32(const char*s, size_t n);
    Expect<uint32_t>  to_octal32(std::string_view s);

    Expect<uint64_t>  to_octal64(const char*s, size_t n);
    Expect<uint64_t>  to_octal64(std::string_view s);

    /*! \brief Decodes the given string into a short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<short>  to_short(const char*s, size_t n);

    /*! \brief Decodes the given string into a short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<short>  to_short(std::string_view s);


    
    /*! \brief Returns the character-array as a string.
    */
    std::string   to_string(const char32_t*);

    

    
    /*! Converts the string view to string string view
    
        Yes, there's a constructor, however, this is for the template (below);  Copy 
    */
    inline std::string_view  to_string(std::string_view s)
    {
        return s;
    }

    /*! No-op string to string, for templates
    
        Yes, there's a constructor, however, this is for the template (below);
    */
    inline const std::string&  to_string(const std::string& s)
    {
        return s;
    }

    /*! \brief Converts u32string to std::string
    */
    std::string         to_string(const std::u32string&s);
    
    /*! \brief Converts to std::string
    */
    std::string         to_string(const std::u32string_view&s);

    /*! \brief Converts wstring to std::string
    */
    std::string         to_string(const std::wstring&);

    /*! \brief Converts wstring_view to std::string
    */
    std::string         to_string(const std::wstring_view&);


    /*! \brief Concatenates vector of T to std::string
    */
    template <typename T>
    auto  to_string(const std::vector<T>& input)
    {
        using ret_t  = decltype(to_string(T()));
        Vector<ret_t>   ret;
        ret.reserve(input.size());
        for(auto& i : input)
            ret << to_string(i);
        return ret;
    }

    /*! \brief Returns the boolean as a string (view)
    */
    inline std::string_view     to_string_view(bool f, std::string_view kFalse = "false", std::string_view kTrue="true")
    {
        return f ? kTrue : kFalse;
    }

    /*! \brief Returns the character as a string.
    
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(char ch);

    /*! \brief Returns the character as a string.
    
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(char8_t ch);
    
    /*! \brief Returns the character as a string.
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(char32_t);

    /*! \brief Returns the character-array as a string.
    */
    inline std::string_view  to_string_view(const char*z)
    {
        return std::string_view(z);
    }

    
    /*! \brief Formats the double into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(double);

    /*! \brief Formats the float into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(float);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(int8_t);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(int16_t);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(int32_t);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(int64_t);

    //! Simple to-string-view for a string
    //!
    //! Yes, it's defined on the class, however, this allows for templated "T" expectations to work
    inline std::string_view to_string_view( const std::string& sv)
    {
        return sv;
    }

    //! Simple to-string-view for a string_view
    //!
    //! Yes, it's a noop, however, this allows for templated "T" expectations to work
    inline std::string_view to_string_view( std::string_view sv)
    {
        return sv;
    }
    
    /*! \brief Converts to std::string_view
    */
    std::string_view    to_string_view(const std::u8string_view&s);

    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint8_t);

    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint16_t);

    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint32_t);

    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint64_t);
    
    /*! \brief Converts the string set to a string view set
        \note Contents of the return set are REFERENCES to the original set data
    */
    string_view_set_t   to_string_view_set(const string_set_t&);

    /*! \brief Formats a time to a string
    */
    std::string         to_time_string(std::time_t, const char* fmt="yyyy-MM-dd HH:mm:ss");
    
    std::u32string      to_u32string(std::string_view);

    /*! \brief Decodes the given string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<unsigned>  to_uint(const char*s, size_t n);

    /*! \brief Decodes the given string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<unsigned>  to_uint(std::string_view s);

    /*! \brief Decodes the given string into an 8-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<uint8_t>  to_uint8(const char*s, size_t n);

    /*! \brief Decodes the given string into an 8-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<uint8_t>  to_uint8(std::string_view s);

    /*! \brief Decodes the given string into a 16-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<uint16_t>  to_uint16(const char*s, size_t n);

    /*! \brief Decodes the given string into a 16-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<uint16_t>  to_uint16(std::string_view s); 

    /*! \brief Decodes the given string into a 32-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<uint32_t>  to_uint32(const char*s, size_t n);

    /*! \brief Decodes the given string into a 32-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<uint32_t>  to_uint32(std::string_view s);

    /*! \brief Decodes the given string into a 64-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<uint64_t>  to_uint64(const char*s, size_t n);

    /*! \brief Decodes the given string into a 64-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<uint64_t>  to_uint64(std::string_view s);

    /*! \brief Decodes the given string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<unsigned>  to_uinteger(const char*s, size_t n);

    /*! \brief Decodes the given string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<unsigned>  to_uinteger(std::string_view s);

    /*! \brief Decodes the given string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<unsigned>  to_unsigned(const char*s, size_t n);

    /*! \brief Decodes the given string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<unsigned>  to_unsigned(std::string_view s);

    /*! \brief Converts to upper case
    
        Converts the given character to upper case
    */
    inline char  to_upper(char ch)
    {
        return ::toupper(ch);
    }
    
    /*! \brief Converts to upper case
    
        Converts the given string to upper case (as unicode characters)
    */
    std::string  to_upper(std::string_view);


    /*! \brief Decodes the given string into an unsigned short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char string
        \param[in] n    number of characters
        
        \return The result
    */
    Expect<unsigned short>  to_ushort(const char*s, size_t n);
    
    /*! \brief Decodes the given string into an unsigned short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::string if need be.
        
        \return The result
    */
    Expect<unsigned short>  to_ushort(std::string_view s);


    /*! \brief String not starting/ending with spaces
    */
    std::string_view    trimmed(std::string_view);
    
    /*! \brief String not starting/ending with specified character
    
    */
    std::string_view    trimmed(std::string_view, char);

    /*! \brief String not ending with whitespaces
    */
    std::string_view    trimmed_end(std::string_view);
    
    /*! \brief String not ending with whitespaces specified character
    */
    std::string_view    trimmed_end(std::string_view, char);

    /*! \brief String not starting with whitespace
    */
    std::string_view    trimmed_start(std::string_view);
    
    /*! \brief String not starting with whitespace specified character
    */
    std::string_view    trimmed_start(std::string_view, char);


    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    auto            vsplit(const char* s, size_t n, char ch, Pred pred)
    {
        using return_t  = decltype(pred(std::string_view()));
        if(s && n){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnchr(i, end-i, ch)); i = j+1){
                if constexpr (!std::is_same_v<return_t, void>){
                    return_t    t   = pred(std::string_view(i, j));
                    if(t != return_t())
                        return t;
                } else
                    pred(std::string_view(i,j));
            }
            return pred(std::string_view(i, end));
        }
        return return_t();
    }

    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    auto            vsplit(const char* s, char ch, Pred pred)
    {
        using return_t = decltype(vsplit(s, strlen(s), ch, pred));
        if(s)
            return vsplit(s, strlen(s), ch, pred);
        return return_t();
    }

    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    auto            vsplit(std::string_view s, char ch, Pred pred)
    {
        return vsplit(s.data(), s.size(), ch, pred);
    }
    
    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      p    Pattern to split on
        \param[in]      pn   Length of the pattern (in bytes)
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit(const char* s, size_t n, const char* p, size_t pn, Pred pred)
    {
        if(s && n && p && pn){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnstr(i, end-i, p, pn)); i = j+1)
                pred(std::string_view(i, j-i));
            pred(std::string_view(i, end-i));
        }
    }
    
    /*! \brief Split via visitor pattern
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      p    String view to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit(std::string_view s, std::string_view pattern, Pred pred)    
    {
        vsplit(s.data(), s.size(), pattern.data(), pattern.size(), pred);
    }
    
    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */

    template <typename Pred>
    void            vsplit_igCase(const char* s, size_t n, char ch, Pred pred)
    {
        if(s && n){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnchr_igCase(i, end-i, ch)); i = j+1)
                pred(std::string_view(i, j-i));
            pred(std::string_view(i, end-i));
        }
    }

    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      ch   Character to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(std::string_view s, char ch, Pred pred)
    {
        vsplit_igCase(s.data(), s.size(), pred);
    }

    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    Pointer to the string
        \param[in]      n    Length of the string (in bytes)
        \param[in]      p    Pattern to split on
        \param[in]      pn   Length of the pattern (in bytes)
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(const char* s, size_t n, const char* p, size_t pn, Pred pred)
    {
        if(s && n && p && pn){
            const char* end = s + n;
            const char* i   = nullptr;
            const char* j   = nullptr;
            for(i = s; (j = strnstr_igCase(i, end-i, p, pn)); i = j+1)
                pred(std::string_view(i, j-i));
            pred(std::string_view(i, end-i));
        }
    }
    
    /*! \brief Split via visitor pattern (ignoring case)
    
        This "splits" the string, but uses a lambda visitor instead of return vector.  Note, matched
        character will NOT be echoed.
        
        \param[in]      s    String view to operate on
        \param[in]      p    String view to split on
        \param[in,out]  pred Function-like object, taking a std::string_view.
    */
    template <typename Pred>
    void            vsplit_igCase(std::string_view s, std::string_view pattern, Pred pred)    
    {
        vsplit_igCase(s.data(), s.size(), pattern.data(), pattern.size(), pred);
    }
    
    /*! \brief Web decodes (with %) the string
    */
    std::string     web_decode(std::string_view);
    
    StringMultiMap  web_decode(StringViewMultiMap);
    
    /*! \brief Web encodes (with %) the string
    */
    std::string     web_encode(std::string_view);

    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //  IMPLEMENTATION
    //  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    
    
    template <typename T>
    static constexpr const bool     has_to_string_view_v    = std::is_same_v<std::string_view, decltype(to_string_view(T()))>;

    template <typename T>
    static constexpr const bool     has_to_string_v    = std::is_same_v<std::string, decltype(to_string(T()))>;
    

    //template <typename Ret, typename Sep, template <typename...> class Tmpl, typename ... T>
    //void     join_generic(Ret& ret, const Tmpl<T...>& collection, Sep sep, size_t nSep, bool is_string)
    //{
        
    //}
    

    /*! Joins a collection into a separator (no separator)
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection)
    {
        std::string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::string> || std::is_same_v<value_t, std::string_view>;
        
        if constexpr ( is_string ){
            size_t  n   = 0;
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        for(const auto&s : collection){
            if constexpr (is_string) {
                ret += s;
            } 
            if constexpr (!is_string){
                if constexpr ( has_to_string_view_v<value_t> ){
                    ret += to_string_view(s);
                } else if constexpr ( has_to_string_v<value_t> ){ 
                    ret += to_string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }
    
    /*! Concatenates string
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \return string with the result
    */
    template <typename T>
    std::string     concat(const std::initializer_list<T> collection)
    {
        return join(collection);
    }

    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, std::string_view separator)
    {
        std::string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::string> || std::is_same_v<value_t, std::string_view>;
        
        if constexpr ( is_string ){
            size_t  n   = collection.size() * separator.size();
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        bool    f   = true;
        for(const auto&s : collection){
            if(f){
                f   = false;
            } else {
                ret += separator;
            }
            
            if constexpr (is_string) {
                ret += s;
            } 
            if constexpr (!is_string){
                if constexpr ( has_to_string_view_v<value_t> ){
                    ret += to_string_view(s);
                } else if constexpr ( has_to_string_v<value_t> ){ 
                    ret += to_string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }
    
    /*! Joins a collection into a separator
    
        Joins a collection of whatever into a resulting string, so long as it has either a "to_string" or 
        a "to_string_view" function defined for it.
        
        \param[in] collection   The collection which must be iterable, and the type of the collection can be 
                                std::string, std::string_view, or have to_string/to_string_view defined for it.
        \param[in] separator    This goes between the elements of the collection
        \return string with the result
    */
    template <template <typename...> class Tmpl, typename... T>
    std::string     join(const Tmpl<T...>& collection, char separator)
    {
        std::string    ret;

        using value_t                       = typename Tmpl<T...>::value_type;
        static constexpr bool   is_string   = std::is_same_v<value_t, std::string> || std::is_same_v<value_t, std::string_view>;
        
        if constexpr ( is_string ){
            size_t  n   = collection.size();
            for(const auto& s : collection)
                n += s.size();
            ret.reserve(n);
        }
        
        bool    f   = true;
        for(const auto&s : collection){
            if(f){
                f   = false;
            } else {
                ret += separator;
            }
            
            if constexpr (is_string) {
                ret += s;
            } 
            if constexpr (!is_string){
                if constexpr ( has_to_string_view_v<value_t> ){
                    ret += to_string_view(s);
                } else if constexpr ( has_to_string_v<value_t> ){ 
                    ret += to_string(s);
                } else {
                    static_assert(always_false_v<value_t>, "Argument deduction failed");
                }
            }
        }
        return ret;
    }

    /*! \brief To string when we have a to-string-view function
    */
    template <typename T>
    //requires (std::is_same_v<std::string_view, to_string_view(T())>)
    std::string    to_string(const T& v)
    {
        return std::string(to_string_view(v));
    }
}


