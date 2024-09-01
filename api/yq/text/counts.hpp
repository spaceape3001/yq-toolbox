////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>

namespace yq {

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

}
