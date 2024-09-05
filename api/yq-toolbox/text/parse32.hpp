////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <yq-toolbox/typedef/expected.hpp>

namespace yq {

    /*! \brief Decodes the given u32string into a boolean
    
    
        This trims whitespace from both ends & decodes the non-whitespace text.  
        For false, it accepts 0, n, no, f, false.
        For true, it accepts 1, y, yes, t, true.
        All other inputs incur an invalid result (false/false).
        
        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    boolean_x  to_boolean(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a boolean
    
        For false, it accepts 0, n, no, f, false.
        For true, it accepts 1, y, yes, t, true.
        All other inputs incur an invalid result.
        All other inputs incur an invalid result (false/false).
        
        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return The result
    */
    boolean_x  to_boolean(std::u32string_view s);

    /*! \brief Decodes the given u32string into a dobule
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        \return The result
    */
    double_x  to_double(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a dobule
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return The result
    */
    double_x  to_double(std::u32string_view s);

    /*! \brief Decodes the given u32string into a float
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        \return The result
    */
    float_x   to_float(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a float
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    float_x   to_float(std::u32string_view);


    /*! \brief Decodes the given hex u32string into an unsigned
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        \return The result
    */
    unsigned_x to_hex(const char32_t*s, size_t n);

    /*! \brief Decodes the given hex u32string into an unsigned
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return The result
    */
    unsigned_x to_hex(std::u32string_view s);

    /*! \brief Decodes the given hex u32string into an unsigned 8-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        \return The result
    */
    uint8_x  to_hex8(const char32_t*s, size_t n);

    /*! \brief Decodes the given hex u32string into an unsigned 8-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return The result
    */
    uint8_x  to_hex8(std::u32string_view s);

    /*! \brief Decodes the given hex u32string into an unsigned 16-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        \return The result
    */
    uint16_x  to_hex16(const char32_t*s, size_t n);

    /*! \brief Decodes the given hex u32string into an unsigned 16-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return The result
    */
    uint16_x  to_hex16(std::u32string_view s);

    /*! \brief Decodes the given hex u32string into an unsigned 32-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        \return The result
    */
    uint32_x  to_hex32(const char32_t*s, size_t n);

    /*! \brief Decodes the given hex u32string into an unsigned 32-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return The result
    */
    uint32_x  to_hex32(std::u32string_view s);

    /*! \brief Decodes the given hex u32string into an unsigned 64-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        \return The result
    */
    uint64_x  to_hex64(const char32_t*s, size_t n);

    /*! \brief Decodes the given hex u32string into an unsigned 64-bit intetger
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        \return The result
    */
    uint64_x  to_hex64(std::u32string_view s);
    
        /*! \brief Decodes the given u32string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    integer_x   to_int(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    integer_x  to_int(std::u32string_view s);

    /*! \brief Decodes the given u32string into an 8-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    int8_x  to_int8(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into an 8-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    int8_x to_int8(std::u32string_view s);

    /*! \brief Decodes the given u32string into a 16-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    int16_x  to_int16(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a 16-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    int16_x  to_int16(std::u32string_view s);

    /*! \brief Decodes the given u32string into a 32-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    int32_x  to_int32(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a 32-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    int32_x  to_int32(std::u32string_view s);

    /*! \brief Decodes the given u32string into a 64-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    int64_x  to_int64(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a 64-bit integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    int64_x  to_int64(std::u32string_view s);

    /*! \brief Decodes the given u32string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    integer_x  to_integer(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into an integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    integer_x  to_integer(std::u32string_view s);


    uint8_x   to_octal8(const char32_t*s, size_t n);
    uint8_x   to_octal8(std::u32string_view s);

    uint16_x  to_octal16(const char32_t*s, size_t n);
    uint16_x  to_octal16(std::u32string_view s);

    uint32_x  to_octal32(const char32_t*s, size_t n);
    uint32_x  to_octal32(std::u32string_view s);

    uint64_x  to_octal64(const char32_t*s, size_t n);
    uint64_x  to_octal64(std::u32string_view s);

    /*! \brief Decodes the given u32string into a short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    short_x  to_short(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    short_x  to_short(std::u32string_view s);


    /*! \brief Decodes the given u32string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    unsigned_x  to_uint(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    unsigned_x  to_uint(std::u32string_view s);

    /*! \brief Decodes the given u32string into an 8-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    uint8_x  to_uint8(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into an 8-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    uint8_x  to_uint8(std::u32string_view s);

    /*! \brief Decodes the given u32string into a 16-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    uint16_x  to_uint16(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a 16-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    uint16_x  to_uint16(std::u32string_view s); 

    /*! \brief Decodes the given u32string into a 32-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    uint32_x  to_uint32(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a 32-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    uint32_x  to_uint32(std::u32string_view s);

    /*! \brief Decodes the given u32string into a 64-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    uint64_x  to_uint64(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into a 64-bit unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    uint64_x  to_uint64(std::u32string_view s);

    /*! \brief Decodes the given u32string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    unsigned_x  to_uinteger(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    unsigned_x  to_uinteger(std::u32string_view s);

    /*! \brief Decodes the given u32string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    unsigned_x  to_unsigned(const char32_t*s, size_t n);

    /*! \brief Decodes the given u32string into an unsigned integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    unsigned_x  to_unsigned(std::u32string_view s);


    /*! \brief Decodes the given u32string into an unsigned short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    pointer to char32_t u32string
        \param[in] n    number of characters
        
        \return The result
    */
    ushort_x  to_ushort(const char32_t*s, size_t n);
    
    /*! \brief Decodes the given u32string into an unsigned short integer
    
        This trims whitespace from both ends & decodes the non-whitespace text.

        \param[in] s    String view (which is auto-gen from std::u32string if need be.
        
        \return The result
    */
    ushort_x  to_ushort(std::u32string_view s);
}
