////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace yq {
    
    /*! \brief Blanks all C++ comments in the given u32string 
    
        This goes over the u32string, all C++ comments are turned into spaces
    */
    void  blank_cpp_comments(std::u32string&);
    
    /*! \brief Capitalizes each word
    
        This capitalizes each word in the u32string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
    */
    std::u32string  capitalize(const char32_t*s, size_t n);

    /*! \brief Capitalizes each word
    
        This capitalizes each word in the u32string, the first character going to upper case, the rest 
        converted to lower case.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
    */
    std::u32string  capitalize(std::u32string_view s);


    /*! \brief Conctenates two u32strings
    
        Concatenates two u32strings together.
        
        \param[in] a    First u32string
        \param[in] b    Second u32string
        \return new u32string of the concatenation
    */
    std::u32string concat(std::u32string_view a, std::u32string_view b);


    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s pointer to u32string
        \param[in] n length of the u32string
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::u32string_view>  hard_wrap(const char32_t*s, size_t n, size_t width);
    
    /*! \brief Hard wrap at the given size
    
        A hard wrap will break mid-word as necessary, and is based on the number of UTF-8 
        character code points.  (ie, entries might have different byte counts, but the character
        counts will remain identical until the last one.)
    
        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \param[in] width    number of characters to wrap at.
    */
    std::vector<std::u32string_view>  hard_wrap(std::u32string_view s, size_t width);

    /*! \brief Left pads the result until the character count is met */
    std::u32string     pad_left(std::u32string_view data, size_t minSize, char32_t ch=U' ');
    
    /*! \brief Right pads the result until the character count is met */
    std::u32string     pad_right(std::u32string_view data, size_t minSize, char32_t ch=U' ');
    
    //! Will *attempt* to make a plural form, won't be perfect
    std::u32string     pluralize(std::u32string_view);
    
    /*! \brief Replaces all instances of old character with new character */
    size_t          replace_all(std::u32string&, char32_t what, char32_t with);
    
    /*! \brief Replaces all instances of old character with new character ignoring case */
    size_t          replace_all_igCase(std::u32string&, char32_t what, char32_t with);


    /*! \brief Simplifies the given u32string
    
        Simplifying a u32string removes start & end whitespace, replaces interior spaces with a single space character.
    */
    std::u32string     simplify(const char32_t*s, size_t n, char32_t sp=' ');

    /*! \brief Simplifies the given u32string
    */
    std::u32string     simplify(std::u32string_view, char32_t sp=' ');


    /*! \brief Strips the LAST extension
    
        This returns the input MINUS the last extension, call repeatedly to remove more than one.
    */
    std::u32string_view    strip_extension(std::u32string_view);

    /*! \brief Strips ALL spaces from the input
    */
    std::u32string  strip_spaces(const char32_t* s, size_t n);

    /*! \brief Strips ALL spaces from the input
    */
    std::u32string  strip_spaces(std::u32string_view);
    

    /*! \brief String not starting/ending with spaces
    */
    std::u32string_view    trimmed(std::u32string_view);
    
    /*! \brief String not starting/ending with specified character
    
    */
    std::u32string_view    trimmed(std::u32string_view, char32_t);

    /*! \brief String not ending with whitespaces
    */
    std::u32string_view    trimmed_end(std::u32string_view);
    
    /*! \brief String not ending with whitespaces specified character
    */
    std::u32string_view    trimmed_end(std::u32string_view, char32_t);

    /*! \brief String not starting with whitespace
    */
    std::u32string_view    trimmed_start(std::u32string_view);
    
    /*! \brief String not starting with whitespace specified character
    */
    std::u32string_view    trimmed_start(std::u32string_view, char32_t);
}
