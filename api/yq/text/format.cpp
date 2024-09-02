////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "format.hpp"
#include <yq/config/string.hpp>
#include <yq/text/basic32.hpp>
#include <yq/text/IgCase.hpp>
#include <charconv>
#include <cuchar>

namespace yq {
    std::string     cvt_u32string(const char32_t *z, size_t n)
    {
        std::string ret;
        ret.resize((std::max<size_t>(64, n*4)));    // approx guess
        std::mbstate_t  state{};
        size_t          m   = 0;
        for(size_t i=0;i<n;++i){
            if(ret.size() - m < 6)
                ret.resize(ret.size() * 2);
            m += c32rtomb(ret.data()+m, z[i], &state);
        }
        ret.resize(m);
        return ret;
    }

    std::string     cvt_wstring(const wchar_t *z, size_t n)
    {
        std::string ret;
        ret.resize((std::max<size_t>(64, n*4)));    // approx guess
        std::mbstate_t  state{};
        size_t          m   = 0;
        for(size_t i=0;i<n;++i){
            if(ret.size() - m < 6)
                ret.resize(ret.size() * 2);
            m += wcrtomb(ret.data()+m, z[i], &state);
        }
        ret.resize(m);
        return ret;
    }

    std::string_view fmt_hex(uint8_t n, char f)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = f;
        auto [p,ec] = std::to_chars(buf+2, buf+kMaxFormattingBuffer, n, 16);
        return std::string_view(p-2,2);
    }

    std::string_view fmt_hex(uint16_t n, char f)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = buf[2] = buf[3] = f;
        auto [p,ec] = std::to_chars(buf+4, buf+kMaxFormattingBuffer, n, 16);
        return std::string_view(p-4,4);
    }

    std::string_view fmt_hex(uint32_t n, char f)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = f;
        auto [p,ec] = std::to_chars(buf+8, buf+kMaxFormattingBuffer, n, 16);
        return std::string_view(p-8,8);
    }

    std::string_view fmt_hex(uint64_t n, char f)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = buf[8] = buf[9] = buf[10] = 
            buf[11] = buf[12] = buf[13] = buf[14] = buf[15] = f;
        auto [p,ec] = std::to_chars(buf+16, buf+kMaxFormattingBuffer, n, 16);
        return std::string_view(p-16,16);
    }
    
    template <typename T>
    std::string_view  as_octal(T n)
    {
        static constexpr const size_t   K = (sizeof(T)*8 / 3) + 1;
        static thread_local char buf[K+1];

        buf[K]      = '\0';
        size_t k    = K-1;
        if(n){
            for(;n;n>>=3, --k)
                buf[k]  = '0' + (n&7);
        } else
            buf[k]  = '0';
        return std::string_view(buf+k, K-k);
    }
    

    std::string_view  fmt_octal(uint8_t n)
    {
        return as_octal(n);
    }
    
    std::string_view  fmt_octal(uint16_t n)
    {
        return as_octal(n);
    }
    
    std::string_view  fmt_octal(uint32_t n)
    {
        return as_octal(n);
    }
    
    std::string_view  fmt_octal(uint64_t n)
    {
        return as_octal(n);
    }

    template <typename T>
    std::string_view  as_octal(T n, char ch)
    {
        static constexpr const size_t   K = (sizeof(T)*8 / 3) + 1;
        static thread_local char buf[K+1];

        buf[K]      = '\0';
        size_t k    = K-1;
        if(n){
            for(;n;n>>=3, --k)
                buf[k]  = '0' + (n&7);
        } else
            buf[k]  = 0;
        while(k>0)
            buf[--k]    = ch;
        return std::string_view(buf,K);
    }
    

    std::string_view  fmt_octal(uint8_t n, char f)
    {
        return as_octal(n,f);
    }
    
    std::string_view  fmt_octal(uint16_t n, char f)
    {
        return as_octal(n,f);
    }
    
    std::string_view  fmt_octal(uint32_t n, char f)
    {
        return as_octal(n,f);
    }
    
    std::string_view  fmt_octal(uint64_t n, char f)
    {
        return as_octal(n,f);
    }


    std::string   to_string(const char32_t*z)
    {
        if(!z)
            return std::string();
        return cvt_u32string(z, strnlen(z, kMaxNullTermString));
    }

    std::string to_string(const std::u32string&s)
    {
        return cvt_u32string(s.data(), s.size());
    }
    

    std::string to_string(const std::u32string_view&s)
    {
        return cvt_u32string(s.data(), s.size());
    }

    std::string to_string(const std::wstring&s)
    {
        return cvt_wstring(s.data(), s.size());
    }


    std::string to_string(const std::wstring_view&s)
    {
        return cvt_wstring(s.data(), s.size());
    }


    std::string_view  to_string_view(const std::u8string_view&s)
    {
        return std::string_view((const char*) s.data(), s.size());
    }

    string_view_set_t  to_string_view_set(const string_set_t& vals)
    {
        string_view_set_t  ret;
        for(const std::string& v : vals)
            ret.insert(v);
        return ret;
    }
    
    std::string_view  to_string_view(char ch)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        buf[0] = ch;
        return std::string_view(buf, 1);
    }
    
    std::string_view  to_string_view(char8_t ch)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        buf[0] = (char) ch;
        return std::string_view(buf, 1);
    }

    std::string_view   to_string_view(char32_t ch)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        std::mbstate_t  state{};
        int len = (int) c32rtomb(buf, ch, &state);
        return std::string_view(buf, len);
    }
    
    std::string_view   to_string_view(double v)
    {
        //  std::to_chars would be GREAT, if GCC implemented it.....
        static thread_local char    buf[kMaxFormattingBuffer+1];
        #if FP_CHARCONV
        int n  = snprintf(buf, kMaxFormattingBuffer, "%lg", v);
        return std::string_view(buf, n);
        #else
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
        #endif
    }
    
    std::string_view   to_string_view(float v)
    {
        //  std::to_chars would be GREAT, if GCC implemented it.....
        static thread_local char    buf[kMaxFormattingBuffer+1];
        #if FP_CHARCONV
        int n  = snprintf(buf, kMaxFormattingBuffer, "%lg", v);
        return std::string_view(buf, n);
        #else
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
        #endif
    }

    std::string_view   to_string_view(int8_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, (int) v);
        return std::string_view(buf, (p-buf));
    }
    
    std::string_view   to_string_view(int16_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
    }
    
    std::string_view   to_string_view(int32_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
    }

    std::string_view   to_string_view(int64_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
    }
    

    std::string_view   to_string_view(uint8_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
    }
    
    std::string_view   to_string_view(uint16_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
    }
    
    std::string_view   to_string_view(uint32_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
    }

    std::string_view   to_string_view(uint64_t v)
    {
        static thread_local char    buf[kMaxFormattingBuffer+1];
        auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
        return std::string_view(buf, (p-buf));
    }

    std::string_view    to_time_string(std::time_t ct, const char* fmt)
    {
        std::tm     gt;
        gmtime_r(&ct, &gt);
        char    buffer[256];
        strftime(buffer, sizeof(buffer), fmt, &gt);
        return std::string_view(buffer);
    }

}
