////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "format32.hpp"
#include <yq/config/string.hpp>
#include <charconv>

namespace yq {
    namespace {
        template <typename T>
        char32_t*  int_to_chars(T v, char32_t* s, size_t n, int base=10)
        {
            char    buf[kMaxFormattingBuffer+1]{};
            auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v, base);
            size_t  cnt = std::min<size_t>(p - buf, n);
            for(size_t i = 0;i<cnt; ++i)
                s[i]    = (char32_t) buf[i];
            return s+cnt;
        }

        template <typename T>
        char32_t*  float_to_chars(T v, char32_t* s, size_t n)
        {
            char    buf[kMaxFormattingBuffer+1]{};
            auto [p,ec] = std::to_chars(buf, buf+kMaxFormattingBuffer, v);
            size_t  cnt = std::min<size_t>(p - buf, n);
            for(size_t i = 0;i<cnt; ++i)
                s[i]    = (char32_t) buf[i];
            return s+cnt;
        }
    }
    
    std::u32string_view fmt_hex32(uint8_t n, char32_t f)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = f;
        char32_t*  p = int_to_chars(n, buf+2, kMaxFormattingBuffer-1, 16);
        return std::u32string_view(p-2,2);
    }

    std::u32string_view fmt_hex32(uint16_t n, char32_t f)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = buf[2] = buf[3] = f;
        char32_t*  p = int_to_chars(n, buf+4, kMaxFormattingBuffer-3, 16);
        return std::u32string_view(p-4,4);
    }

    std::u32string_view fmt_hex32(uint32_t n, char32_t f)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = f;
        char32_t*  p = int_to_chars(n, buf+8, kMaxFormattingBuffer-7, 16);
        return std::u32string_view(p-8,8);
    }

    std::u32string_view fmt_hex32(uint64_t n, char32_t f)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = buf[8] = buf[9] = buf[10] = 
            buf[11] = buf[12] = buf[13] = buf[14] = buf[15] = f;
        char32_t*  p = int_to_chars(n, buf+16, kMaxFormattingBuffer-15, 16);
        return std::u32string_view(p-16,16);
    }
    
    template <typename T>
    std::u32string_view  as_octal32(T n)
    {
        static constexpr const size_t   K = (sizeof(T)*8 / 3) + 1;
        static thread_local char32_t buf[K+1];

        buf[K]      = '\0';
        size_t k    = K-1;
        if(n){
            for(;n;n>>=3, --k)
                buf[k]  = '0' + (n&7);
        } else
            buf[k]  = '0';
        return std::u32string_view(buf+k, K-k);
    }
    

    std::u32string_view  fmt_octal32(uint8_t n)
    {
        return as_octal32(n);
    }
    
    std::u32string_view  fmt_octal32(uint16_t n)
    {
        return as_octal32(n);
    }
    
    std::u32string_view  fmt_octal32(uint32_t n)
    {
        return as_octal32(n);
    }
    
    std::u32string_view  fmt_octal32(uint64_t n)
    {
        return as_octal32(n);
    }

    template <typename T>
    std::u32string_view  as_octal32(T n, char32_t ch)
    {
        static constexpr const size_t   K = (sizeof(T)*8 / 3) + 1;
        static thread_local char32_t buf[K+1];

        buf[K]      = '\0';
        size_t k    = K-1;
        if(n){
            for(;n;n>>=3, --k)
                buf[k]  = '0' + (n&7);
        } else
            buf[k]  = 0;
        while(k>0)
            buf[--k]    = ch;
        return std::u32string_view(buf,K);
    }
    

    std::u32string_view  fmt_octal32(uint8_t n, char32_t f)
    {
        return as_octal32(n,f);
    }
    
    std::u32string_view  fmt_octal32(uint16_t n, char32_t f)
    {
        return as_octal32(n,f);
    }
    
    std::u32string_view  fmt_octal32(uint32_t n, char32_t f)
    {
        return as_octal32(n,f);
    }
    
    std::u32string_view  fmt_octal32(uint64_t n, char32_t f)
    {
        return as_octal32(n,f);
    }
    

    std::u32string_view  to_u32string_view(char8_t ch)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        buf[0] = (char32_t) ch;
        return std::u32string_view(buf, 1);
    }

    std::u32string_view  to_u32string_view(char32_t ch)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        buf[0] = ch;
        return std::u32string_view(buf, 1);
    }

    std::u32string_view   to_u32string_view(double v)
    {
        //  std::to_chars would be GREAT, if GCC implemented it.....
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = float_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(float v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = float_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }

    std::u32string_view   to_u32string_view(int8_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(int16_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(int32_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }

    std::u32string_view   to_u32string_view(int64_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(uint8_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(uint16_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(uint32_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }

    std::u32string_view   to_u32string_view(uint64_t v)
    {
        static thread_local char32_t    buf[kMaxFormattingBuffer+1];
        auto p = int_to_chars(v, buf, kMaxFormattingBuffer);
        return std::u32string_view(buf, (p-buf));
    }    
}
