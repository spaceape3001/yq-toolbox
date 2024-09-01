////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "parse.hpp"
#include "chars.hpp"
#include <charconv>
#include <yq/errors.hpp>

namespace yq {
    template <typename T>
    Expect<T>   int_from_chars(const char*s, size_t n, int base=10)
    {
        T    res = 0;
        auto [p,ec] = std::from_chars(s, s+n, res, base);
        if(ec != std::errc())
            return std::unexpected( std::make_error_code(ec));
        return res;
    }

    //! Trims a string's leading/trailing whitespace by altering parameters
    void    trim_ws(const char*& s, size_t& n)
    {
        while(s && *s && isspace(*s) && n)
            ++s, --n;
        while(s && n && isspace(s[n-1]))
            --n;
    }


    unsigned_x  to_hex(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned int>(s, n, 16);
    }


    unsigned_x  to_hex(std::string_view s)
    {
        return to_hex(s.data(), s.size());
    }



    uint8_x  to_hex8(const char*s, size_t n)
    {
        if(!s)  
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint8_t>(s, n, 16);
    }

    uint8_x  to_hex8(std::string_view s)
    {
        return to_hex8(s.data(), s.size());
    }

    uint16_x  to_hex16(const char*s, size_t n)
    {
        if(!s)  
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint16_t>(s, n, 16);
    }

    uint16_x  to_hex16(std::string_view s)
    {
        return to_hex16(s.data(), s.size());
    }

    uint32_x  to_hex32(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint32_t>(s, n, 16);
    }

    uint32_x  to_hex32(std::string_view s)
    {
        return to_hex32(s.data(), s.size());
    }

    uint64_x  to_hex64(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint64_t>(s, n, 16);
    }

    uint64_x  to_hex64(std::string_view s)
    {
        return to_hex64(s.data(), s.size());
    }
    
    integer_x  to_int(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int>(s,n);
    }

    integer_x   to_int(std::string_view s)
    {
        return to_int(s.data(), s.size());
    }

    int8_x  to_int8(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int8_t>(s,n);
    }

    int8_x  to_int8(std::string_view s)
    {
        return to_int8(s.data(), s.size());
    }


    int16_x  to_int16(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int16_t>(s,n);
    }

    int16_x  to_int16(std::string_view s)
    {
        return to_int16(s.data(), s.size());
    }

    int32_x  to_int32(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int32_t>(s,n);
    }

    int32_x  to_int32(std::string_view s)
    {
        return to_int32(s.data(), s.size());
    }


    int64_x  to_int64(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int64_t>(s,n);
    }

    int64_x  to_int64(std::string_view s)
    {
        return to_int64(s.data(), s.size());
    }

    integer_x  to_integer(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int>(s,n);
    }

    integer_x  to_integer(std::string_view s)
    {
        return to_integer(s.data(), s.size());
    }

    
    uint8_x  to_octal8(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint8_t>(s,n,8);
    }
    
    uint8_x  to_octal8(std::string_view s)
    {
        return to_octal8(s.data(), s.size());
    }

    uint16_x  to_octal16(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint16_t>(s,n,8);
    }
    
    uint16_x  to_octal16(std::string_view s)
    {
        return to_octal16(s.data(), s.size());
    }

    uint32_x  to_octal32(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint32_t>(s,n,8);
    }
    
    uint32_x  to_octal32(std::string_view s)
    {
        return to_octal32(s.data(), s.size());
    }

    uint64_x  to_octal64(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint64_t>(s,n,8);
    }

    uint64_x  to_octal64(std::string_view s)
    {
        return to_octal64(s.data(), s.size());
    }
    
    Expect<short>  to_short(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<short>(s,n);
    }

    Expect<short>  to_short(std::string_view s)
    {
        return to_short(s.data(), s.size());
    }

    unsigned_x  to_uint(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned>(s,n);
    }

    unsigned_x  to_uint(std::string_view s)
    {
        return to_uint(s.data(), s.size());
    }

    uint8_x     to_uint8(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint8_t>(s,n);
    }

    uint8_x     to_uint8(std::string_view s)
    {
        return to_uint8(s.data(), s.size());
    }

    uint16_x    to_uint16(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint16_t>(s,n);
    }

    uint16_x    to_uint16(std::string_view s)
    {
        return to_uint16(s.data(), s.size());
    }

    uint32_x    to_uint32(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint32_t>(s,n);
    }

    uint32_x    to_uint32(std::string_view s)
    {
        return to_uint32(s.data(), s.size());
    }

    uint64_x    to_uint64(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint64_t>(s,n);
    }

    uint64_x    to_uint64(std::string_view s)
    {
        return to_uint64(s.data(), s.size());
    }

    unsigned_x  to_uinteger(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned int>(s,n);
    }

    unsigned_x  to_uinteger(std::string_view s)
    {
        return to_uinteger(s.data(), s.size());
    }

    unsigned_x  to_unsigned(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned int>(s,n);
    }

    unsigned_x  to_unsigned(std::string_view s)
    {
        return to_unsigned(s.data(), s.size());
    }


    ushort_x    to_ushort(const char*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned short>(s,n);
    }


    ushort_x    to_ushort(std::string_view s)
    {
        return to_ushort(s.data(), s.size());
    }
    }
