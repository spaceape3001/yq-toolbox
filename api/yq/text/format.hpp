////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdint>
#include <string_view>
#include <ctime>
#include <vector>
#include <yq/typedef/string_sets.hpp>
#include <concepts>

namespace yq {

    static constexpr const int  kMaxDoubleDigits    = 19;
    static constexpr const int  kMaxFloatDigits     = 7;

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
    
    //! Generalized write format of double
    std::string_view    fmt_double(double, int digits=kMaxDoubleDigits);

    //! Generalized write format of float
    std::string_view    fmt_float(float, int digits=kMaxFloatDigits);
    
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
    

    
    /*! Converts the string view to string string view
    
        Yes, there's a constructor, however, this is for the template (below);  Copy 
    */
    inline std::string_view  to_string(std::string_view s)
    {
        return s;
    }

    /*! No-op string to string, for templates
    
        Yes, there's a constructor, however, this is for the template (below);
    */
    inline const std::string&  to_string(const std::string& s)
    {
        return s;
    }

    /*! \brief Converts u32string to std::string
    */
    std::string         to_string(const std::u32string&s);
    
    /*! \brief Converts to std::string
    */
    std::string         to_string(const std::u32string_view&s);

    /*! \brief Converts wstring to std::string
    */
    std::string         to_string(const std::wstring&);

    /*! \brief Converts wstring_view to std::string
    */
    std::string         to_string(const std::wstring_view&);


    /*! \brief Concatenates vector of T to std::string
    */
    template <typename T>
    auto  to_string(const std::vector<T>& input)
    {
        using ret_t  = decltype(to_string(T()));
        std::vector<ret_t>   ret;
        ret.reserve(input.size());
        for(auto& i : input)
            ret.push_back(to_string(i));
        return ret;
    }

    /*! \brief Returns the character-array as a string.
    */
    std::string   to_string(const char32_t*);


    /*! \brief Returns the character-array as a string.
    */
    inline std::string_view  to_string_view(const char*z)
    {
        return std::string_view(z);
    }


    //! Simple to-string-view for a string
    //!
    //! Yes, it's defined on the class, however, this allows for templated "T" expectations to work
    inline std::string_view to_string_view( const std::string& sv)
    {
        return sv;
    }

    //! Simple to-string-view for a string_view
    //!
    //! Yes, it's a noop, however, this allows for templated "T" expectations to work
    inline std::string_view to_string_view( std::string_view sv)
    {
        return sv;
    }
    
    /*! \brief Converts to std::string_view
    */
    std::string_view    to_string_view(const std::u8string_view&s);
    
    
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
    
    /*! \brief Converts the string set to a string view set
        \note Contents of the return set are REFERENCES to the original set data
    */
    string_view_set_t   to_string_view_set(const string_set_t&);

    
    /*! \brief Formats a time to a string
    */
    std::string_view    to_time_string(std::time_t, const char* fmt="yyyy-MM-dd HH:mm:ss");

    template <typename T>
    concept StringViewable      = std::same_as<std::string_view, decltype(to_string_view(T()))>;

    template <typename T>
    concept Stringable          = StringViewable<T> || std::same_as<std::string_view, decltype(to_string(T()))>;

    template <typename T>
    static constexpr const bool     has_to_string_view_v    = std::is_same_v<std::string_view, decltype(to_string_view(T()))>;

    template <typename T>
    static constexpr const bool     has_to_string_v         = std::is_same_v<std::string, decltype(to_string(T()))>;

    /*! \brief To string when we have a to-string-view function
    */
    template <typename T>
    //requires has_to_string_view_v<T> //(std::is_same_v<std::string_view, to_string_view(T())>)
    std::string    to_string(const T& v)
    {
        return std::string(to_string_view(v));
    }
}
