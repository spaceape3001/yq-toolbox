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
    bool  is_alnum(char ch);
    
    /*! \brief Tests for an alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_alpha(char ch);

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
    bool  is_blank(char ch);

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
    bool  is_control(char ch);
    
    /*! \brief Tests for numeric digit
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_digit(char ch);
    

    /*! \brief Tests for graphical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_graph(char ch);
    

    /*! \brief Tests for lower-case alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_lower(char ch);

    /*! \brief Tests for new line character
    */
    bool         is_newline(char);

    /*! \brief Tests for printable character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool        is_print(char);
    
    /*! \brief Tests for punctuation character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool        is_punct(char ch);

    /*! \brief Tests for white-space character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool        is_space(char ch);
    
    /*! \brief Tests for white-space characters
        \return TRUE if ALL characters in the string view are white space
    */
    bool        is_space(std::string_view);
    
    /*! \brief Tests for upper-case alphabetical character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_upper(char ch);
    
    /*! \brief Tests for hexadecimal digit character
        \note   This is here for reasons of better spelling and to harmonize with overloads.
    */
    bool  is_xdigit(char ch);

    /*! \brief Converts to lower case
    
        Harmonized overload (for name consistency) to convert a character to lower case. 
        (If it's not upper case, then the input argument is returned.)
    */
    char  to_lower(char ch);
    
    /*! \brief Converts to lower case
    
        Converts the given string to lowercase (as unicode characters)
    */
    std::string  to_lower(std::string_view s);


    /*! \brief Converts to upper case
    
        Converts the given character to upper case
    */
    char  to_upper(char ch);
    
    /*! \brief Converts to upper case
    
        Converts the given string to upper case (as unicode characters)
    */
    std::string  to_upper(std::string_view);

}
