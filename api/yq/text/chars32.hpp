////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>

namespace yq {

    /*! \brief Tests for an alphanumeric character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_alnum(char32_t ch);

    /*! \brief Tests for an alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_alpha(char32_t ch);

    /*! \brief Tests entire u32string for alpha
    
        \param[in] s pointer to u32string
        \param[in] n length of the u32string
        \return TRUE if the ENTIRE u32string is alpha characters
    */
    bool is_alpha(const char32_t*s, size_t n);
    
    /*! \brief Tests entire u32string for alpha
    
        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return TRUE if the ENTIRE u32string is alpha characters
    */
    bool is_alpha(std::u32string_view);


    /*! \brief Tests for blank character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_blank(char32_t ch);

    /*! \brief Tests for blank u32string
        \param[in] s pointer to u32string
        \param[in] n length of the u32string
    */
    bool  is_blank(const char32_t*s, size_t n);

    /*! \brief Tests for blank u32string
        \param[in] s    String view (which is auto-gen from std::u32string if need be.
    */
    bool  is_blank(std::u32string_view s);
    
    /*! \brief Tests for control character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_control(char32_t ch);
    
    /*! \brief Tests for numeric digit
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_digit(char32_t ch);
    
    /*! \brief Tests for graphical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_graph(char32_t ch);

    /*! \brief Tests for lower-case alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_lower(char32_t ch);


    /*! \brief Tests for new line character
    */
    bool  is_newline(char32_t);

    /*! \brief Tests for printable character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_print(char32_t ch);
    
    /*! \brief Tests for punctuation character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_punct(char32_t ch);

    /*! \brief Tests for white-space character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_space(char32_t ch);

    bool  is_space(const char32_t*, size_t);
    
    /*! \brief Tests for white-space characters
        \return TRUE if ALL characters in the u32string view are white space
    */
    bool  is_space(std::u32string_view);
    

    /*! \brief Tests for upper-case alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_upper(char32_t ch);
    
    /*! \brief Tests for hexadecimal digit character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_xdigit(char32_t ch);
    
    /*! \brief Converts to lower case
    
        Harmonized overload (for name consistency) to convert a character to lower case. 
        (If it's not upper case, then the input argument is returned.)
    */
    char32_t  to_lower(char32_t ch);
    
    /*! \brief Converts to lower case
        Converts the given u32string to lowercase.
    */
    std::u32string  to_lower(const std::u32string_view&s);

    /*! \brief Converts to upper case
    
        Converts the given character to upper case
    */
    char32_t  to_upper(char32_t ch);
    
    /*! \brief Converts to upper case
    
        Converts the given u32string to upper case (as unicode characters)
    */
    std::u32string  to_upper(std::u32string_view);
    
}
