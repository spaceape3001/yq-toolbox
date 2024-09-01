////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>

namespace yq {

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(const char32_t* s, size_t n);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(std::u32string_view s);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(const char32_t* s, size_t n, char32_t ch);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters(std::u32string_view s, char32_t ch);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters_igCase(const char32_t* s, size_t n, char32_t ch);

    /*! \brief Counts the number of characters
    */
    size_t  count_characters_igCase(std::u32string_view s, char32_t ch);

    /*! \brief Counts the opening number of space characters
    */
    size_t  count_start_spaces(std::u32string_view);
    
    /*! \brief Counts the number of the specified character that start the u32string
    */
    size_t  count_starts(std::u32string_view, char32_t);
}
