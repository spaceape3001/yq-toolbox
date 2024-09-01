////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <string_view>

namespace yq {
    /*! \brief Formats the given number as hexadecimal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!
    
        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_hex32(uint8_t n, char32_t f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_hex32(uint16_t n, char32_t f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_hex32(uint32_t n, char32_t f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_hex32(uint64_t n, char32_t f='0');
    
    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint8_t n);

    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint16_t n);

    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint32_t n);

    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint64_t n);

    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint8_t n, char32_t f);

    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint16_t n, char32_t f);

    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint32_t n, char32_t f);

    /*! \brief Formats the given number as octal
    
        \note u32string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted u32string
    */
    std::u32string_view  fmt_octal32(uint64_t n, char32_t f);

#if 0
    //  CURRENTLY UNIMPLEMENTED
    
    /*! \brief Formats the given number in scientifica notation
        
        \param[in] v        Value to format
        \param[in] digits   Prescision
        \result Formatted u32string
    */
    std::u32string  fmt_scientific32(double v, int digits=-1);

    /*! \brief Formats the given number in scientifica notation
        
        \param[in] v        Value to format
        \param[in] digits   Prescision
        \result Formatted u32string
    */
    std::u32string  fmt_scientific32(float v, int digits=-1);
#endif

    /*! \brief Returns the boolean as a u32string (view)
    */
    inline std::u32string_view     to_u32string_view(bool f, std::u32string_view kFalse = U"false", std::u32string_view kTrue= U"true")
    {
        return f ? kTrue : kFalse;
    }

    /*! \brief Returns the character as a u32string.
    
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view  to_u32string_view(char32_t ch);

    /*! \brief Returns the character as a u32string.
    
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view  to_u32string_view(char8_t ch);
    
    /*! \brief Returns the character as a u32string.
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view  to_u32string_view(char32_t);

    /*! \brief Formats the double into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view   to_u32string_view(double);

    /*! \brief Formats the float into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view   to_u32string_view(float);

    /*! \brief Formats the integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view   to_u32string_view(int8_t);

    /*! \brief Formats the integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view   to_u32string_view(int16_t);

    /*! \brief Formats the integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view   to_u32string_view(int32_t);

    /*! \brief Formats the integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view  to_u32string_view(int64_t);
    

    /*! \brief Formats the unsigned integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view    to_u32string_view(uint8_t);

    /*! \brief Formats the unsigned integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view    to_u32string_view(uint16_t);

    /*! \brief Formats the unsigned integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view    to_u32string_view(uint32_t);

    /*! \brief Formats the unsigned integer into a u32string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::u32string_view    to_u32string_view(uint64_t);
}
