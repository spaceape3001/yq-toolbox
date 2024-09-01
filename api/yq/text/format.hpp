////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <string_view>
#include <ctime>

namespace yq {

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!
    
        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint8_t n, char f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint16_t n, char f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint32_t n, char f='0');

    /*! \brief Formats the given number as hexadecimal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_hex(uint64_t n, char f='0');
    
    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint8_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint16_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint32_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \result Formatted string
    */
    std::string_view  fmt_octal(uint64_t n);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint8_t n, char f);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint16_t n, char f);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint32_t n, char f);

    /*! \brief Formats the given number as octal
    
        \note string_view points to internal (thread-local) buffer, it'll be overwritten on next call!

        \param[in] n    Value to format
        \param[in] f    Fill character for leading characters
        \result Formatted string
    */
    std::string_view  fmt_octal(uint64_t n, char f);

#if 0
    // Currently appear unimplemented
    
    /*! \brief Formats the given number in scientifica notation
        
        \param[in] v        Value to format
        \param[in] digits   Prescision
        \result Formatted string
    */
    std::string  fmt_scientific(double v, int digits=-1);

    /*! \brief Formats the given number in scientifica notation
        
        \param[in] v        Value to format
        \param[in] digits   Prescision
        \result Formatted string
    */
    std::string  fmt_scientific(float v, int digits=-1);
#endif    
    

    /*! \brief Returns the boolean as a string (view)
    */
    inline std::string_view     to_string_view(bool f, std::string_view kFalse = "false", std::string_view kTrue="true")
    {
        return f ? kTrue : kFalse;
    }

    /*! \brief Returns the character as a string.
    
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(char ch);

    /*! \brief Returns the character as a string.
    
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(char8_t ch);
    
    /*! \brief Returns the character as a string.
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(char32_t);

    
    /*! \brief Formats the double into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(double);

    /*! \brief Formats the float into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(float);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(int8_t);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(int16_t);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view   to_string_view(int32_t);

    /*! \brief Formats the integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view  to_string_view(int64_t);
    
    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint8_t);

    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint16_t);

    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint32_t);

    /*! \brief Formats the unsigned integer into a string
        \note Returns a REFERENCE to a thread-local buffer, copy off before next call, if retention is important.
    */
    std::string_view    to_string_view(uint64_t);
    
    /*! \brief Formats a time to a string
    */
    std::string_view    to_time_string(std::time_t, const char* fmt="yyyy-MM-dd HH:mm:ss");
}
