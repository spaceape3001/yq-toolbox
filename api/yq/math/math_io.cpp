////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "math_io.hpp"
#include <yq/core/StreamOps.hpp>
#include <yq/text/parse.hpp>
#include <yq/text/split.hpp>
#include <cstdio>

namespace yq::math_io {
    //////////////////////////////////////////////////////////////////////////////

    std::string_view     format_n(const double*vals, uint8_t N, int kMaxDigits)
    {
        if(!vals || !N)
            return {};
            
        static thread_local char    buffer[256*32];
        
        if(kMaxDigits < 0)
            kMaxDigits  = 0;
        if(kMaxDigits > 20)
            kMaxDigits  = 20;
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%.*lg", kMaxDigits, vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }
    
    std::string_view     format_n(const float*vals, uint8_t N, int kMaxDigits)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*16];
        
        if(kMaxDigits < 0)
            kMaxDigits  = 0;
        if(kMaxDigits > 10)
            kMaxDigits  = 10;
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%.*g", kMaxDigits, vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const int8_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*8];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%d", (int) vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const int16_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*8];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%d", (int) vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const int32_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*16];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%d", vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const int64_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*20];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%ld", vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const uint8_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};
        
        static thread_local char    buffer[256*8];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%u", (uint) vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const uint16_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*8];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%u", (uint) vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const uint32_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*16];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%u", vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }

    std::string_view     format_n(const uint64_t*vals, uint8_t N)
    {
        if(!vals || !N)
            return {};

        static thread_local char    buffer[256*20];
        
        size_t      idx = 0;
        for(uint8_t n=0; n<N; ++n){
            if(n)
                buffer[idx++]   = ',';
            idx += snprintf(buffer+idx, sizeof(buffer)-idx, "%lu", vals[n]);
        }
        if(idx >= sizeof(buffer))
            idx = sizeof(buffer) - 1;
        buffer[idx] = '\0';
        return std::string_view(buffer, idx);
    }


        ////////////////////////////////////////////

    bool    parse_n(double* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;
    
        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_double(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }
    
    bool    parse_n(float* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_float(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }

    bool    parse_n(int8_t* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_int8(bits[n]);
            if(!x)
                return false;
            if(*x < -128)
                return false;
            if(*x > 127)
                return false;
            dst[n]  = *x;
        }
        return true;
    }

    bool    parse_n(int16_t* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_int16(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }

    bool    parse_n(int32_t* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_int32(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }
    
    bool    parse_n(int64_t* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_int64(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }

    bool    parse_n(uint16_t* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_uint16(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }
    
    bool    parse_n(uint32_t* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_uint32(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }

    bool    parse_n(uint64_t* dst, uint8_t N, std::string_view txt)
    {
        if(!dst)
            return false;
        if(!N)
            return true;
        if(txt.empty())
            return false;

        auto bits = split(txt, ',');
        if(bits.size() != N)
            return false;
        for(uint8_t n=0;n<N;++n){
            auto x  = to_uint64(bits[n]);
            if(!x)
                return false;
            dst[n]  = *x;
        }
        return true;
    }

    //////////////////////////////////////////////////////////////////////////////
    
    void print_n(Stream& str, const double* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }
    

    void print_n(Stream& str, const float* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }
        
    void print_n(Stream& str, const int8_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << (int) vals[n];
        } 
        str << ')';
    }


    void print_n(Stream& str, const int16_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }
        
    void print_n(Stream& str, const int32_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }

    void print_n(Stream& str, const int64_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }

    void print_n(Stream& str, const uint8_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << (uint) vals[n];
        } 
        str << ')';
        return;
    }


    void print_n(Stream& str, const uint16_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }
        
    void print_n(Stream& str, const uint32_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }

    void    print_n(Stream& str, const uint64_t* vals, uint8_t N)
    {
        if(!vals){
            str << "(nullptr)";
            return;
        }
        
        str << '(';
        for(uint8_t n=0;n<N;++n){
            if(n)
                str << ",";
            str << vals[n];
        } 
        str << ')';
    }
}
