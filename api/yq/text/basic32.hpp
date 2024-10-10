////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>
#include <cstring>

namespace yq {
    const char32_t*         strany(std::u32string_view haystack, std::u32string_view needle);


    size_t strlen(const char32_t* s);
    
    int     strncasecmp(const char32_t*, const char32_t*, size_t);

    /*! \brief Finds the next character 
    
        \param[in] s    Pointer to u32string
        \param[in] n    Number of bytes to the u32string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char32_t*  strnchr(const char32_t*s, size_t n, char32_t ch);

    /*! \brief Finds the next character 
    
        \param[in] s    std::u32string view
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char32_t*  strnchr(std::u32string_view s, char32_t ch);

    /*! \brief Finds the next character 
    
        \param[in] s    Pointer to u32string
        \param[in] n    Number of bytes to the u32string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char32_t*  strnchr(const char32_t*s, size_t n, char32_t ch);

    /*! \brief Finds the next character (ignoring case)
    
        \param[in] s    Pointer to u32string
        \param[in] n    Number of bytes to the u32string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char32_t*  strnchr_igCase(const char32_t*s, size_t n, char32_t ch);

    /*! \brief Finds the next character (ignoring case)
    
        \param[in] s    Pointer to u32string
        \param[in] n    Number of bytes to the u32string.
        \param[in] ch   Character being searched for
        \return pointer to character if found, NULL if not.
    */
    const char32_t*  strnchr_igCase(const char32_t*s, size_t n, char32_t ch);


    #ifdef WIN32
            //  until MSVC decides to grow up and get with the times....
    inline size_t  strnlen(const char32_t* z, size_t cb)
    {
        return strlen_s(z, cb);
    }
    #else
    using ::strnlen;
    #endif
    
    size_t          strnlen(const char32_t* z, size_t cb);
    
    
    /*! \brief Finds the first needle
    
        \param[in]  haystack    The bigger u32string
        \param[in]  nHay        Size of the haystack
        \param[in]  needle      The search term
        \param[in]  nNeedle     Size of the needle
        
        \return pointer to char32_tacte rif ound, nullptr otherwise
    */
    const char32_t* strnstr(const char32_t* haystack, size_t nHay, const char32_t* needle, size_t nNeedle);

    /*! \brief Finds the first needle (ignoring case)
    
        \param[in]  haystack    The bigger u32string
        \param[in]  nHay        Size of the haystack
        \param[in]  needle      The search term
        \param[in]  nNeedle     Size of the needle
        
        \return pointer to char32_tacte rif ound, nullptr otherwise
    */
    const char32_t* strnstr_igCase(const char32_t* haystack, size_t nHay, const char32_t* needle, size_t nNeedle);
}
