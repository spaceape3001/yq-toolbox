////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string_view>
#include <vector>

namespace yq {
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
}
