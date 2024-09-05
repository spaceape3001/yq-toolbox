////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <string_view>

namespace yq {

    /*! \brief Splits the u32string up into the specified equal number of chunks
    
        This routine will split the incoming u32string into the given number of
        chunks as evenly as possible.  (ie, adjacent items might be +- 1 in size)
        
        \note This returns REFERENCES to the original u32string, so it must live.
        \note If n<number, some of the returned entries will be empty.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] number   Number of entries
    */
    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, size_t number); 

    /*! \brief Splits the u32string up into the specified equal number of chunks
    
        This routine will split the incoming u32string into the given number of
        chunks as evenly as possible.  (ie, adjacent items might be +- 1 in size)

        \note This returns REFERENCES to the original u32string, so it must live.
        \note If s.size()<number, some of the returned entries will be empty.

        \param[in] s        String view
        \param[in] number   Number of entries
    */
    std::vector<std::u32string_view>  split(std::u32string_view s, size_t number); 

    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split(const char32_t*s, size_t n, char32_t ch); 

    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch); 

    /*! \brief Splits the u32string, up to number entries
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.
        
        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, char32_t ch, size_t number); 

    /*! \brief Splits the u32string, up to number entries
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.
        
        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch, size_t number); 

    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split(const char32_t*s , size_t n, char32_t ch); 

    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch); 
    
    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, char32_t cn, size_t number); 

    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified character.
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        String view
        \param[in] ch       Character being split on
        \param[in] number   MAXIMUM Number of entries, more are treated as part of the last entry
    */
    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch, size_t number); 

    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified u32string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] p        pointer to pattern u32string
        \param[in] pn       length of the pattern u32string
    */
    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, const char32_t* p, size_t pn);

    /*! \brief Splits the u32string
    
        This routine splits the incoming u32string at the specified u32string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        String view
        \param[in] p        pattern u32string
    */
    std::vector<std::u32string_view>  split(std::u32string_view s, std::u32string_view p);

    /*! \brief Splits the u32string ignoring case
    
        This routine splits the incoming u32string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split_igCase(const char32_t*s , size_t n, char32_t ch); 

    /*! \brief Splits the u32string ignoring case
    
        This routine splits the incoming u32string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        u32string
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split_igCase(std::u32string_view s, char32_t ch); 

    /*! \brief Splits the u32string ignoring case
    
        This routine splits the incoming u32string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split_igCase(const char32_t* s, size_t n, char32_t ch); 

    /*! \brief Splits the u32string ignoring case
    
        This routine splits the incoming u32string at the specified character (case insensitive).
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        u32string
        \param[in] ch       Character being split on
    */
    std::vector<std::u32string_view>  split_igCase(std::u32string_view s, char32_t ch); 
    
    /*! \brief Splits the u32string ignoring case
    
        This routine splits the incoming u32string at the specified u32string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        pointer to u32string
        \param[in] n        length of the u32string
        \param[in] p        pointer to pattern u32string
        \param[in] pn       length of the pattern u32string
    */
    std::vector<std::u32string_view>  split_igCase(const char32_t*s, size_t n, const char32_t* p, size_t pn);

    /*! \brief Splits the u32string ignoring case
    
        This routine splits the incoming u32string at the specified u32string
        Repeated instances of the character will result in empty entries in 
        the result.

        \note This returns REFERENCES to the original u32string, so it must live.

        \param[in] s        String view
        \param[in] p        pattern u32string
    */
    std::vector<std::u32string_view>  split_igCase(std::u32string_view s, std::u32string_view p);
}
