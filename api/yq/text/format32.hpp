////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <yq/typedef/string_sets.hpp>

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

    std::u32string      to_u32string(std::string_view);

    /*! Converts the u32string view to u32string u32string view
    
        Yes, there's a constructor, however, this is for the template (below);  Copy 
    */
    inline std::u32string  to_u32string(std::u32string_view s)
    {
        return std::u32string(s);
    }

    /*! No-op u32string to u32string, for templates
    
        Yes, there's a constructor, however, this is for the template (below);
    */
    inline const std::u32string&  to_u32string(const std::u32string& s)
    {
        return s;
    }

    /*! \brief Concatenates vector of T to std::u32string
    */
    template <typename T>
    auto  to_u32string(const std::vector<T>& input)
    {
        using ret_t  = decltype(to_u32string(T()));
        std::vector<ret_t>   ret;
        ret.reserve(input.size());
        for(auto& i : input)
            ret.psuh_back(to_u32string(i));
        return ret;
    }



    /*! \brief Returns the character-array as a u32string.
    */
    inline std::u32string_view  to_u32string_view(const char32_t*z)
    {
        return std::u32string_view(z);
    }


    std::u32string      to_u32string(std::u32string_view);


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


    //! Simple to-string-view for a u32string
    //!
    //! Yes, it's defined on the class, however, this allows for templated "T" expectations to work
    inline std::u32string_view to_u32string_view( const std::u32string& sv)
    {
        return sv;
    }

    //! Simple to-string-view for a u32string_view
    //!
    //! Yes, it's a noop, however, this allows for templated "T" expectations to work
    inline std::u32string_view to_u32string_view( std::u32string_view sv)
    {
        return sv;
    }
    
    /*! \brief Converts to std::u32string_view
    */
    std::u32string_view    to_u32string_view(const std::u8string_view&s);

    
    /*! \brief Converts the u32string set to a u32string view set
        \note Contents of the return set are REFERENCES to the original set data
    */
    u32string_view_set_t   to_u32string_view_set(const u32string_set_t&);

    template <typename T>
    static constexpr const bool     has_to_u32string_view_v    = std::is_same_v<std::u32string_view, decltype(to_u32string_view(T()))>;

    template <typename T>
    static constexpr const bool     has_to_u32string_v    = std::is_same_v<std::u32string, decltype(to_u32string(T()))>;

    /*! \brief Tou32string when we have a to-string-view function
    */
    template <typename T>
    //requires has_to_u32string_view_v<T>
    std::u32string    to_u32string(const T& v)
    {
        return std::u32string(to_u32string_view(v));
    }
}
