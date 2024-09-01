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

    /*! \brief Simplifies the given string
    
        Simplifying a string removes start & end whitespace, replaces interior spaces with a single space character.
    */
    std::string     simplify(const char*s, size_t n, char sp=' ');

    /*! \brief Simplifies the given string
    */
    std::string     simplify(std::string_view, char sp=' ');


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
}
