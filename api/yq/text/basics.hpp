////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>
#include <cstring>

namespace yq {
    const char*         strany(std::string_view haystack, std::string_view needle);

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
}
