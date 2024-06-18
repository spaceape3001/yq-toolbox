////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <0/basic/TextUtils32.hpp>

#include <0/basic/Compare.hpp>
#include <0/basic/Comma.hpp>
#include <0/basic/IterUtf8.hpp>
#include <0/basic/Iter32.hpp>
#include <0/basic/IterW.hpp>
#include <0/basic/List.hpp>
#include <0/basic/Logging.hpp>
#include <0/basic/Map.hpp>
#include <0/basic/MultiMap.hpp>
#include <0/basic/Set.hpp>
#include <0/basic/TextUtils.hpp>
#include <0/basic/errors.hpp>

#include <bitset>

    /*
        GCC v10 did not support to/from char32_ts on floating point types.  It's been enabled in v11.
        Therefore, we'll macro this portion. :(
    */
#if defined(MSVC)
    #define FP_CHARCONV 1
#elif defined(__GNUC__)
    #if __GNUC__ >= 11
        #define FP_CHARCONV 1
    #endif
#endif
#ifndef FP_CHARCONV
    #define FP_CHARCONV 0
#endif

namespace yq {

    namespace {

        //! Trims a string's leading/trailing whitespace by altering parameters
        void    trim_ws(const char32_t*& s, size_t& n)
        {
            while(s && *s && is_space(*s) && n)
                ++s, --n;
            while(s && n && is_space(s[n-1]))
                --n;
        }
        
        //const char32_t* nonspace(const char32_t* s, size_t n)
        //{
            //while(s && *s && isspace(*s) && n)
                //++s, --n;
            //return s;
        //}

        //! Checks for equality by assuming left may vary in case, the right will be lower case.
        bool    is_same(const char32_t*a, size_t n, const char32_t *b)
        {
            if(a && b){
                for(;*a && *b && n; ++a, ++b, --n){
                    if(to_lower(*a) != *b)
                        return false;
                }
                return !(*b || n);
            }
            return false;
        }
        
        
//        static constexpr const auto fFAIL     = float_r(false, NaNf);

        template <typename T>
        Expect<T>   int_from_chars(const char32_t*s, size_t n, int base=10)
        {
            char    buf[kStdTextBuf+1];
            size_t  k   = std::min(n,kStdTextBuf);
            for(size_t i=0;i<k;++i)
                buf[i]  = (char) std::min((char32_t) 127, s[i]);
            T    res = 0;
            auto [p,ec] = std::from_chars(buf, buf+k, res, base);
            if(ec != std::errc())
                return std::unexpected( std::make_error_code(ec));
            return res;
        }
        //  IF ever needed for wchar32_t_t, rename "c32rtomb" to "wcrtomb".
        
        template <typename T>
        char32_t*  int_to_chars(T v, char32_t* s, size_t n, int base=10)
        {
            char    buf[kStdTextBuf+1];
            auto [p,ec] = std::to_chars(buf, buf+kStdTextBuf, v, base);
            size_t  cnt = std::min<size_t>(p - buf, n);
            for(size_t i = 0;i<cnt; ++i)
                s[i]    = (char32_t) buf[i];
            return s+cnt;
        }

        template <typename T>
        char32_t*  float_to_chars(T v, char32_t* s, size_t n)
        {
            char    buf[kStdTextBuf+1];
            auto [p,ec] = std::to_chars(buf, buf+kStdTextBuf, v);
            size_t  cnt = std::min<size_t>(p - buf, n);
            for(size_t i = 0;i<cnt; ++i)
                s[i]    = (char32_t) buf[i];
            return s+cnt;
        }
    }

    
    bool    any_starts(const std::vector<std::u32string>&haystack, std::u32string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts(const std::vector<std::u32string_view>&haystack, std::u32string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts(const std::initializer_list<std::u32string_view>&haystack, std::u32string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(const std::vector<std::u32string>&haystack, std::u32string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(const std::vector<std::u32string_view>&haystack, std::u32string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(std::initializer_list<std::u32string_view> haystack, std::u32string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }

    void    blank_cpp_comments(std::u32string& s)
    {
        const size_t kSize = s.size();
        for(size_t i=0;i<kSize;++i){
            if((s.at(i) == '/') && (s.at(i+1) == '/')){
                for(; (i<kSize) && (s.at(i) != '\n'); ++i)
                    s.at(i)   = ' ';
            }
        }
    }

    std::u32string  capitalize(const char32_t*s, size_t n)
    {
        std::u32string ret;
        if(s && n){
            ret.reserve(n);
            bool        space = true;
            for(size_t i=0;i<n;++n){
                if(is_space(s[i])){
                    space   = true;
                    ret += s[i];
                } else {
                    if(is_alpha(s[i])){
                        if(space)
                            ret += to_upper(s[i]);
                        else
                            ret += to_lower(s[i]);
                    } else 
                        ret += s[i];
                    space   = false;
                }
            }
        }
        return ret;
    }
    
    std::u32string  capitalize(std::u32string_view s)
    {
        return capitalize(s.data(), s.size());
    }

    Compare compare(std::u32string_view a, std::u32string_view b)
    {
        size_t  c   = std::min(a.size(), b.size());
        for(size_t i=0;i<c;++i){
            if(a[i] < b[i])
                return Compare::LESSER;
            if(a[i] > b[i])
                return Compare::GREATER;
        }
        
        return compare(a.size(), b.size());
    }

    Compare compare_igCase(std::u32string_view sa, std::u32string_view sb)
    {
        size_t  n   = std::min(sa.size(), sb.size());
        for(size_t i=0;i<n;++i){
            char32_t  ca  = sa[i];
            char32_t  cb  = sb[i];
            
            int64_t n   = (int64_t) to_lower(ca) - (int64_t) to_lower(cb);
            if(n<0)
                return Compare::LESSER;
            else if(n>0)
                return Compare::GREATER;
        }
        if(sa.size() < sb.size())
            return Compare::LESSER;
        if(sb.size() < sa.size())
            return Compare::GREATER;
        return Compare::EQUAL;
    }

    std::u32string concat(std::u32string_view a, std::u32string_view b)
    {
        std::u32string ret;
        ret.reserve(a.size()+b.size()+1);
        ret = a;
        ret += b;
        return ret;
    }

    bool    contains(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle)
    {
        return strnstr(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains(std::u32string_view haystack, std::u32string_view needle)
    {
        return contains(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    bool    contains_igCase(const char32_t* haystack, size_t nHaystack, const char32_t* needle, size_t nNeedle)
    {
        return strnstr_igCase(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains_igCase(std::u32string_view haystack, std::u32string_view needle)
    {
        return contains_igCase(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    u32string_set_t        copy(const u32string_view_set_t&input)
    {
        u32string_set_t    ret;
        for(auto& s : input)
            ret.insert(copy(s));
        return ret;
    }

    std::vector<std::u32string>    copy(const std::vector<std::u32string>&input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(const std::u32string& s : input)
            ret.push_back(s);
        return ret;
    }
    
    std::vector<std::u32string>    copy(const std::vector<std::u32string_view>&input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(std::u32string_view s : input)
            ret.push_back(std::u32string(s));
        return ret;
    }

    std::vector<std::u32string>  copy(std::initializer_list<std::u32string_view> input)
    {
        std::vector<std::u32string>    ret;
        ret.reserve(input.size());
        for(std::u32string_view s : input)
            ret.push_back(std::u32string(s));
        return ret;
    }

    size_t  count_characters(const char32_t* s, size_t n)
    {
        return n;
    }
    
    size_t  count_characters(std::u32string_view s)
    {
        return count_characters(s.data(), s.size());
    }
    
    size_t  count_characters(const char32_t* s, size_t n, char32_t ch)
    {
        size_t ret =0;
        if(s && n){
            for(size_t i=0;i<n;++i)
                if(s[i] == ch)
                    ++ret;
        }
        return ret;
    }
    
    size_t  count_characters(std::u32string_view s, char32_t ch)
    {
        return count_characters(s.data(), s.size(), ch);
    }
    

    size_t  count_characters_igCase(const char32_t* s, size_t n, char32_t ch)
    {
        size_t  ret = 0;
        if(s && n){
            ch  = to_lower(ch);
            for(size_t i=0;i<n;++i){
                if(to_lower(s[i]) == ch)
                    ++ ret;
            }
        }
        return ret;
    }
    

    size_t  count_characters_igCase(std::u32string_view s, char32_t ch)
    {
        return count_characters_igCase(s.data(), s.size(), ch);
    }
    
    size_t  count_start_spaces(std::u32string_view a)
    {
        size_t  ret   = 0;
        for(char32_t ch : a){
            if(is_space(ch)){
                ++ret;
            } else 
                break;
        }
        return ret;
    }

    
    size_t  count_starts(std::u32string_view s, char32_t ch)
    {
        size_t  n = 0;
        for(; (n<s.size()) && (s[n] == ch); ++n)
            ;
        return n;
    }

    bool    ends(std::u32string_view hay, std::u32string_view pat)
    {
        if(pat.size() > hay.size())
            return false;
        return hay.substr(hay.size()-pat.size()) == pat;
    }

    char32_t  first_non_blank_char(std::u32string_view a)
    {
        for(char32_t ch : a){
            if(!is_space(ch))
                return ch;
        }
        return U'\0';
    }

    std::u32string_view  first_non_empty(std::u32string_view a, std::u32string_view b)
    {
        return a.empty() ? b : a;
    }

    std::u32string_view  first_non_empty(std::u32string_view a, std::u32string_view b, std::u32string_view c)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        return c;
    }

    std::u32string_view  first_non_empty(std::u32string_view a, std::u32string_view b, std::u32string_view c, std::u32string_view d)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        if(!c.empty())
            return c;
        return d;
    }

    std::u32string_view  first_non_empty(std::initializer_list<std::u32string_view> args)
    {
        for(std::u32string_view s : args)
            if(!s.empty())
                return s;
        return std::u32string_view();
    }

    std::u32string_view fmt_hex32(uint8_t n, char32_t f)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        buf[0] = buf[1] = f;
        char32_t*  p = int_to_chars(n, buf+2, kStdTextBuf-1, 16);
        return std::u32string_view(p-2,2);
    }

    std::u32string_view fmt_hex32(uint16_t n, char32_t f)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        buf[0] = buf[1] = buf[2] = buf[3] = f;
        char32_t*  p = int_to_chars(n, buf+4, kStdTextBuf-3, 16);
        return std::u32string_view(p-4,4);
    }

    std::u32string_view fmt_hex32(uint32_t n, char32_t f)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = f;
        char32_t*  p = int_to_chars(n, buf+8, kStdTextBuf-7, 16);
        return std::u32string_view(p-8,8);
    }

    std::u32string_view fmt_hex32(uint64_t n, char32_t f)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        buf[0] = buf[1] = buf[2] = buf[3] = buf[4] = buf[5] = buf[6] = buf[7] = buf[8] = buf[9] = buf[10] = 
            buf[11] = buf[12] = buf[13] = buf[14] = buf[15] = f;
        char32_t*  p = int_to_chars(n, buf+16, kStdTextBuf-15, 16);
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
    

    std::vector<std::u32string_view>  hard_wrap(const char32_t*s, size_t n, size_t width)
    {
        std::vector<std::u32string_view>   ret;
        size_t      cnt     = n / width;
        ret.reserve(cnt+1);
        for(size_t j=0;j<cnt;++j){
            ret.push_back(std::u32string_view(s + j*width, width));
        }
        size_t j = n % width;
        if(j){
            ret.push_back(std::u32string_view(s + cnt*width, j));
        }
        return ret;
    }
    
    std::vector<std::u32string_view>  hard_wrap(std::u32string_view s, size_t width)
    {
        return hard_wrap(s.data(), s.size(), width);
    }

    bool  is_alpha(const char32_t*s, size_t n)
    {
        if(!s)
            return false;
            
        for(size_t i=0;i<n;++i){
            if(!is_alpha(s[i]))
                return false;
        }
        
        return true;
    }
    
    bool  is_alpha(std::u32string_view s)
    {
        return is_alpha(s.data(), s.size());
    }
    
    bool  is_blank(const char32_t*s, size_t n)
    {
        if(!s)
            return false;
            
        for(size_t i=0;i<n;++i){
            if(!is_blank(s[i]))
                return false;
        }
        
        return true;
    }

    bool  is_blank(std::u32string_view s)
    {
        return is_blank(s.data(), s.size());
    }

    bool  is_equal(std::u32string_view a, std::u32string_view b)
    {
        return is_equal(compare(a,b));
    }

    bool  is_greater_igCase(std::u32string_view a, std::u32string_view b)
    {
        return is_greater(compare_igCase(a,b));
    }

    bool  is_in(std::u32string_view str, std::u32string_view pat)
    {
        return is_similar(str, pat);
    }
    

    bool  is_in(std::u32string_view str, std::initializer_list<std::u32string_view> pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }
    
    bool  is_in(std::u32string_view str, const u32string_view_set_t& pat)
    {
        return pat.contains(str);
    }

    bool  is_in(std::u32string_view str, const std::vector<std::u32string_view>& pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }

    bool is_in(char32_t ch, std::u32string_view pat)
    {
        for(char32_t c : pat){
            if(is_similar(c, ch))
                return true;
        }
        return false;
    }

    bool  is_less_igCase(std::u32string_view a, std::u32string_view b)
    {
        return is_less( compare_igCase(a,b));
    }

    bool    is_newline(char32_t ch)
    {
        return (ch == U'\r') || (ch == U'\n');
    }

    bool  is_similar(char32_t a, char32_t b)
    {
        return to_lower(a) == to_lower(b);
    }

    bool  is_similar(std::u32string_view a, std::u32string_view b)
    {
        if(a.size() != b.size())
            return false;
        return is_equal( compare_igCase(a, b));
    }

    bool  is_space(const char32_t*s, size_t n)
    {
        if(!s)
            return false;
            
        for(size_t i=0;i<n;++i){
            if(!is_space(s[i]))
                return false;
        }
        
        return true;
    }

    bool  is_space(std::u32string_view a)
    {
        return is_space(a.data(), a.size());
    }

    bool        matches_at(std::u32string_view haystack, size_t pos, std::u32string_view pattern)
    {
        return starts(haystack.substr(pos), pattern);
    }
    
    bool        matches_at_igCase(std::u32string_view haystack, size_t pos, std::u32string_view pattern)
    {
        return starts_igCase(haystack.substr(pos), pattern);
    }

    std::u32string     pad_left(std::u32string_view data, size_t minSize, char32_t ch)
    {
        size_t  ccount  = count_characters(data);
        if(ccount >= minSize)
            return std::u32string(data);
        std::u32string ret(minSize-ccount, ch);
        ret += data;
        return ret;
    }
    
    std::u32string  pad_right(std::u32string_view data, size_t minSize, char32_t ch)
    {
        size_t  ccount  = count_characters(data);
        std::u32string ret = copy(data);
        if(ccount < minSize)
            ret.append(minSize-ccount, ch);
        return ret;
    }

    std::u32string     pluralize(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string(sv);
        std::u32string     ret;
        switch(sv[sv.size()-1]){
        case 's':
        case 'S':
            ret = sv;
            ret += U"es";
            break;
        case 'y':
        case 'Y':
            if(sv.size() >= 2){
                ret += sv.substr(0,sv.size()-2);
                ret += U"ies";
                break;
            }
            //[[fallthrough]]
        default:
            ret     += sv;
            ret += U's';
            break;
        }
        return ret;
    }

    size_t  replace_all(std::u32string& data, char32_t what, char32_t with)
    {
        size_t  cnt = 0;
        for(char32_t& ch : data){
            if(ch == what){
                ch  = with;
                ++cnt;
            }
        }
        return cnt;
    }

    size_t  replace_all_igCase(std::u32string&data, char32_t what, char32_t with)
    {
        size_t  cnt = 0;
        what    = to_lower(what);
        for(char32_t& ch : data){
            if(to_lower(ch) == what){
                ch  = with;
                ++cnt;
            }
        }
        return cnt;
    }


    //  Need to keep this for future reference, though we'll need a less heap-destroying algorithm
    //QString         sanitize_path(const QString& path)
    //{
        //return sanitize_path(path.split('/')).join('/');
    //}

    //String          sanitize_path(const String& path)
    //{
        //return sanitize_path(path.qString());
    //}

    //QStringList     sanitize_path(const QStringList& path)
    //{
        //QStringList ret;
        //for(const QString& s : path){
            //if(s.isEmpty())
                //continue;
            //if(s == ".")
                //continue;
            //if(s == "..")
                //continue;
            //ret << s;
        //}
        //if(path.last().isEmpty())   // preserve the final empty for a "/"
            //ret << QString();
        //return ret;
    //}

    std::u32string&    set_if_empty(std::u32string&a, std::u32string_view b, bool fOverride)
    {
        if((a.empty() || fOverride) && !b.empty())
            a  = b;
        return a;
    }
    
    std::u32string     simplify(const char32_t*s, size_t n, char32_t sp)
    { 
        bool                first   = true;
        bool                space   = true;
        std::u32string     ret;
        
        if(s && n){
            ret.reserve(n);
            for(size_t i=0;i<n;++i){
                if(is_space(s[i])){
                    space   = true;
                } else {
                    if(first){
                        first   = false;
                    } else if(space){
                        ret.push_back(sp);
                        space   = false;
                    }
                    ret.push_back(s[i]);
                }
            }
        };
    
        return ret;
    }
    

    std::u32string     simplify(std::u32string_view sv, char32_t sp)
    {
        return simplify(sv.data(), sv.size(), sp);
    }

    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, size_t num)
    {
        std::vector<std::u32string_view>    ret;
        if(s && n){
            if(!num)
                ++num;
                
            ret.reserve(num);
            size_t  j0  =  0;
            size_t  j1;
            
            for(size_t i = 0; i<num; j0=j1, ++i){
                j1  = std::min(((i+1)*n)/num, n);
                ret.push_back(std::u32string_view(s+j0, j1-j0));
            }
        }
        return ret;
    }

    std::vector<std::u32string_view>  split(std::u32string_view s, size_t number)
    {
        return split(s.data(), s.size(), number);
    }

    std::vector<std::u32string_view>  split(const char32_t*s, size_t n, char32_t ch)
    {
        std::vector<std::u32string_view>  ret;
        vsplit(s, n, ch, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }

    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch)
    {
        return split(s.data(), s.size(), ch);
    }

    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, char32_t ch, size_t number)
    {
        std::vector<std::u32string_view>  ret;
        if(s && n){
            const char32_t* end = s + n;
            const char32_t* i   = nullptr;
            const char32_t* j   = nullptr;
            if(number){
                for(i = s; (j = strnchr(i, end-i, ch)) && --number; i = j)
                    ret.push_back(std::u32string_view(i, j-i));
            }
            ret.push_back(std::u32string_view(i, end-i));
        }
        return ret;
    }

    std::vector<std::u32string_view>  split(std::u32string_view s, char32_t ch, size_t number)
    {
        return split(s.data(), s.size(), ch, number);
    }

    std::vector<std::u32string_view>  split(const char32_t* s, size_t n, const char32_t* p, size_t pn)
    {
        std::vector<std::u32string_view>  ret;
        vsplit(s, n, p, pn, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::u32string_view>  split(std::u32string_view s, std::u32string_view p)
    {
        return split(s.data(), s.size(), p.data(), p.size());
    }

    std::vector<std::u32string_view>  split_igCase(const char32_t* s , size_t n, char32_t ch)
    {
        std::vector<std::u32string_view>  ret;
        vsplit_igCase(s, n, ch, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::u32string_view>  split_igCase(std::u32string_view s, char32_t ch)
    {
        return split_igCase(s.data(), s.size(), ch);
    }
    
    std::vector<std::u32string_view>  split_igCase(const char32_t* s, size_t n, const char32_t*p, size_t pn)
    {
        std::vector<std::u32string_view>  ret;
        vsplit_igCase(s, n, p, pn, [&](std::u32string_view token){
            ret.push_back(token);
        });
        return ret;
    }
    
    std::vector<std::u32string_view>  split_igCase(std::u32string_view s, std::u32string_view p)
    {
        return split_igCase(s.data(), s.size(), p.data(), p.size());
    }
    
    bool  starts(const char32_t* s, size_t n, const char32_t* pat, size_t nPat)
    {
        if(s && n && pat && (nPat<=n)){
            for(size_t i=0;i<nPat;++i)
                if(s[i] != pat[i])
                    return false;
            return true;
        }
        
        return false;
    }
    
    bool  starts(std::u32string_view s, std::u32string_view pat)
    {
        return starts(s.data(), s.size(), pat.data(), pat.size());
    }
    
    bool  starts_igCase(const char32_t* s, size_t n, const char32_t* pat, size_t nPath)
    {
        if(s && n && pat && (nPath<=n)){
            for(size_t i=0;i<nPath;++i)
                if(to_lower(s[i]) != to_lower(pat[i]))
                    return false;
            return true;
        }
        
        return false;
    }
    
    bool  starts_igCase(std::u32string_view s, std::u32string_view pat)
    {
        return starts_igCase(s.data(), s.size(), pat.data(), pat.size());
    }

    const char32_t*         strany(std::u32string_view haystack, std::u32string_view needle)
    {
        for(const char32_t* z = haystack.begin(); z != haystack.end(); ++z){
            if(strnchr(needle, *z))
                return z;
        }
        return nullptr;
    }

    std::u32string_view    strip_extension(std::u32string_view name)
    {
        ssize_t  x   = (ssize_t) name.find_last_of('.');
        ssize_t  s   = (ssize_t) name.find_last_of('/');
        if(x > s+1)
            return name.substr(0,x);
        return name;
    }

    std::u32string  strip_spaces(const char32_t* s, size_t n)
    {
        std::u32string  ret;
        ret.reserve(n);
        if(s && n){
            for(size_t i=0;i<n;++i){
                if(!is_space(s[i])){
                    ret += s[i];
                }
            }
        }
        return ret;
    }
    
    std::u32string  strip_spaces(std::u32string_view s)
    {
        return strip_spaces(s.data(), s.size());
    }

    size_t strlen(const char32_t* s)
    {
        if(!s)
            return 0;
        size_t  cnt = 0;
        for(;*s;++cnt)
            ;
        return cnt;
    }

    int     strncasecmp(const char32_t*a, const char32_t*b, size_t n)
    {
        if(!a && b)
            return -1;
        if(a && !b)
            return 1;
            
        for(size_t i=0;i<n;++i){
            if(!a[i]){
                if(!b[i]){
                    return 0;
                }
                return -1;
            } else if(!b[i]){
                return 1;
            }
        
            int d   = to_lower(a[i]) - to_lower(b[i]);
            if(d)
                return d;
        }
        return 0;
    }
    

    const char32_t*  strnchr(const char32_t*s, size_t n, char32_t ch)
    {
        if(!s || !n)
            return nullptr;
        for(;*s && n; ++s, --n)
            if(*s == ch)
                return s;
        return nullptr;
    }

    const char32_t*  strnchr(std::u32string_view s, char32_t ch)
    {
        return strnchr(s.data(), s.size(), ch);
    }

    const char32_t*  strnchr_igCase(const char32_t*s, size_t n, char32_t ch)
    {
        ch      = to_lower(ch);
        if(!s || !n)
            return nullptr;
        for(;*s && n; ++s, --n)
            if(to_lower(*s) == ch)
                return s;
        return nullptr;
    }
    
    size_t       strnlen(const char32_t* z, size_t cb)
    { 
        size_t  n   = 0;
        for(; z && *z && cb; --cb, ++z, ++n)
            ;
        return n;
    }

    const char32_t*  strnstr(const char32_t* haystack, size_t nHay, const char32_t* needle, size_t nNeedle)
    {
        //  weed outs
        if(!haystack || !needle || !nHay || (nHay < nNeedle)) 
            return nullptr;

        if(nNeedle == 1)    
            return strnchr(haystack, nHay, *needle);

        #if 0
            //  clever... but in the 8-bit realm
        if(nNeedle <= 8){
            uint64_t    mask    = 0ULL;
            uint64_t    pattern = 0ULL;
            uint64_t    mem     = 0ULL;
            size_t      i;
            
                //  build up the mask & pattern
            for(i=0;i<nNeedle;++i){
                mask        = 0xFF | (mask << 8);
                pattern     = needle[i] | (pattern << 8);
            }
            
                //  prime
            for(i=0;i<(nNeedle-1);++i)
                mem         = haystack[i] | (mem << 8);
            
                //  search
            for(++i;i<nHay;++i){
                mem         = haystack[i] | (mem << 8);
                if((mem & mask) == pattern)
                    return haystack + i - nNeedle;
            }
        } else {
        #endif
            size_t      i   = 0;
            size_t      j   = 0;
            for(i=0;i<nHay - nNeedle; ++i){
                if(haystack[i] == needle[0]){
                    bool    good    = true;
                    for(j=1;good && (j<nNeedle);++j){
                        if(haystack[i+j] != needle[j])
                            good    = false;
                    }
                    if(good)
                        return haystack+i;
                }
            }
        #if 0
        }
        #endif
        return nullptr;
    }

    const char32_t*  strnstr_igCase(const char32_t* haystack, size_t nHay, const char32_t* needle, size_t nNeedle)
    {
        //  weed outs
        if(!haystack || !needle || !nHay || (nHay < nNeedle)) 
            return nullptr;

        if(nNeedle == 1)    
            return strnchr_igCase(haystack, nHay, *needle);

        #if 0
        if(nNeedle <= 8){
            uint64_t    mask    = 0ULL;
            uint64_t    pattern = 0ULL;
            uint64_t    mem     = 0ULL;
            size_t      i;
            
                //  build up the mask & pattern
            for(i=0;i<nNeedle;++i){
                mask        = 0xFF | (mask << 8);
                pattern     = to_lower(needle[i]) | (pattern << 8);
            }
            
                //  prime
            for(i=0;i<(nNeedle-1);++i)
                mem         = to_lower(haystack[i]) | (mem << 8);
            
                //  search
            for(++i;i<nHay;++i){
                mem         = to_lower(haystack[i]) | (mem << 8);
                if((mem & mask) == pattern)
                    return haystack + i - nNeedle;
            }
        } else {
        #endif
            size_t      i   = 0;
            size_t      j   = 0;
            for(i=0;i<nHay - nNeedle; ++i){
                if(to_lower(haystack[i]) == to_lower(needle[0])){
                    bool    good    = true;
                    for(j=1;good && (j<nNeedle);++j){
                        if(to_lower(haystack[i+j]) != to_lower(needle[j]))
                            good    = false;
                    }
                    if(good)
                        return haystack+i;
                }
            }
        #if 0
        }
        #endif
        return nullptr;
    }
    
    Expect<bool>  to_boolean(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s, n);
        if(!n)
            return errors::empty_string();
        switch(*s){
        case '0':
            if(is_same(s,n,U"0"))
                return false;
            break;
        case '1':
            if(is_same(s, n, U"1"))
                return true;
            break;
        case 'y':
        case 'Y':
            if(n == 1)
                return true;
            if(is_same(s, n, U"yes"))
                return true;
            break;
        case 'n':
        case 'N':
            if(n == 1)
                return false;
            if(is_same(s, n, U"no"))
                return false;
            break;
        case 't':
        case 'T':
            if(n == 1)
                return true;
            if(is_same(s, n, U"true"))
                return true;
            break;
        case 'f':
        case 'F':
            if(n==1)
                return false;
            if(is_same(s, n, U"false"))
                return false;
            break;
        default:
            break;
        }
        
        return errors::bad_argument();
    }

    Expect<bool> to_boolean(std::u32string_view s)
    {
        return to_boolean(s.data(), s.size());
    }

    Expect<double>  to_double(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        return to_double(to_string(std::u32string_view(s,n)));

        #if 0
        trim_ws(s, n);
        switch(n){
        case 0:
            return 0.;
        case 3:
            if(strncasecmp(s, U"nan", 3) == 0)
                return NaN;
            if(strncasecmp(s, U"inf", 3) == 0)
                return INF;
            break;
        }
        

        double  result = NaN;
        auto [p,ec] = std::from_chars(s, s+n, result, std::chars_format::general);
        if(ec != std::errc())
            return std::unexpected(std::make_error_code(ec));
        return result;
        #endif
    }

    Expect<double>  to_double(std::u32string_view s)
    {
        return to_double(s.data(), s.size());
    }

    Expect<float>  to_float(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        return to_float(to_string(std::u32string_view(s,n)));

        #if 0
        trim_ws(s, n);

        switch(n){
        case 0:
            return 0.f;
        case 3:
            if(strncasecmp(s, "nan", 3) == 0)
                return NaNf;
            if(strncasecmp(s, "inf", 3) == 0)
                return INFf;
            break;
        }
        
        float  result = NaNf;
        auto [p,ec] = std::from_char32_ts(s, s+n, result, std::char32_ts_format::general);
        if(ec != std::errc())
            return std::unexpected(std::make_error_code(ec));
        return result;
        #endif
    }

    Expect<float>  to_float(std::u32string_view s)
    {
        return to_float(s.data(), s.size());
    }


    Expect<unsigned>  to_hex(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned int>(s, n, 16);
    }


    Expect<unsigned>  to_hex(std::u32string_view s)
    {
        return to_hex(s.data(), s.size());
    }

    Expect<uint8_t>  to_hex8(const char32_t*s, size_t n)
    {
        if(!s)  
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint8_t>(s, n, 16);
    }

    Expect<uint8_t>  to_hex8(std::u32string_view s)
    {
        return to_hex8(s.data(), s.size());
    }

    Expect<uint16_t>  to_hex16(const char32_t*s, size_t n)
    {
        if(!s)  
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint16_t>(s, n, 16);
    }

    Expect<uint16_t>  to_hex16(std::u32string_view s)
    {
        return to_hex16(s.data(), s.size());
    }

    Expect<uint32_t>  to_hex32(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint32_t>(s, n, 16);
    }

    Expect<uint32_t>  to_hex32(std::u32string_view s)
    {
        return to_hex32(s.data(), s.size());
    }

    Expect<uint64_t>  to_hex64(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint64_t>(s, n, 16);
    }

    Expect<uint64_t>  to_hex64(std::u32string_view s)
    {
        return to_hex64(s.data(), s.size());
    }
    
    Expect<int>  to_int(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int>(s,n);
    }

    Expect<int>   to_int(std::u32string_view s)
    {
        return to_int(s.data(), s.size());
    }

    Expect<int8_t>  to_int8(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int8_t>(s,n);
    }

    Expect<int8_t>  to_int8(std::u32string_view s)
    {
        return to_int8(s.data(), s.size());
    }


    Expect<int16_t>  to_int16(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int16_t>(s,n);
    }

    Expect<int16_t>  to_int16(std::u32string_view s)
    {
        return to_int16(s.data(), s.size());
    }

    Expect<int32_t>  to_int32(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int32_t>(s,n);
    }

    Expect<int32_t>  to_int32(std::u32string_view s)
    {
        return to_int32(s.data(), s.size());
    }


    Expect<int64_t>  to_int64(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int64_t>(s,n);
    }

    Expect<int64_t>  to_int64(std::u32string_view s)
    {
        return to_int64(s.data(), s.size());
    }

    Expect<int>  to_integer(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<int>(s,n);
    }

    Expect<int>  to_integer(std::u32string_view s)
    {
        return to_integer(s.data(), s.size());
    }
    
    std::u32string  to_lower(const std::u32string_view&s)
    {
        std::u32string ret;
        ret.reserve(s.size());
        for(char32_t ch : s)
            ret += to_lower(ch);
        return ret;
    }

    Expect<short>  to_short(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<short>(s,n);
    }

    Expect<short>  to_short(std::u32string_view s)
    {
        return to_short(s.data(), s.size());
    }

    std::u32string_view  to_u32string_view(char8_t ch)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        buf[0] = (char32_t) ch;
        return std::u32string_view(buf, 1);
    }

    std::u32string_view  to_u32string_view(char32_t ch)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        buf[0] = ch;
        return std::u32string_view(buf, 1);
    }

    std::u32string_view   to_u32string_view(double v)
    {
        //  std::to_chars would be GREAT, if GCC implemented it.....
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = float_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(float v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = float_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }

    std::u32string_view   to_u32string_view(int8_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(int16_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(int32_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }

    std::u32string_view   to_u32string_view(int64_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }


    std::u32string_view  to_u32string_view(const std::u8string_view&s)
    {
        return std::u32string_view((const char32_t*) s.data(), s.size());
    }

    std::u32string_view   to_u32string_view(uint8_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(uint16_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }
    
    std::u32string_view   to_u32string_view(uint32_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }

    std::u32string_view   to_u32string_view(uint64_t v)
    {
        static thread_local char32_t    buf[kStdTextBuf+1];
        auto p = int_to_chars(v, buf, kStdTextBuf);
        return std::u32string_view(buf, (p-buf));
    }

    u32string_view_set_t  to_u32string_view_set(const u32string_set_t& vals)
    {
        u32string_view_set_t  ret;
        for(const std::u32string& v : vals)
            ret.insert(v);
        return ret;
    }

    Expect<unsigned>  to_uint(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned>(s,n);
    }

    Expect<unsigned>  to_uint(std::u32string_view s)
    {
        return to_uint(s.data(), s.size());
    }

    Expect<uint8_t>     to_uint8(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint8_t>(s,n);
    }

    Expect<uint8_t>     to_uint8(std::u32string_view s)
    {
        return to_uint8(s.data(), s.size());
    }

    Expect<uint16_t>    to_uint16(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint16_t>(s,n);
    }

    Expect<uint16_t>    to_uint16(std::u32string_view s)
    {
        return to_uint16(s.data(), s.size());
    }

    Expect<uint32_t>    to_uint32(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint32_t>(s,n);
    }

    Expect<uint32_t>    to_uint32(std::u32string_view s)
    {
        return to_uint32(s.data(), s.size());
    }

    Expect<uint64_t>    to_uint64(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<uint64_t>(s,n);
    }

    Expect<uint64_t>    to_uint64(std::u32string_view s)
    {
        return to_uint64(s.data(), s.size());
    }

    Expect<unsigned>  to_uinteger(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned int>(s,n);
    }

    Expect<unsigned>  to_uinteger(std::u32string_view s)
    {
        return to_uinteger(s.data(), s.size());
    }

    Expect<unsigned>  to_unsigned(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned int>(s,n);
    }

    Expect<unsigned>  to_unsigned(std::u32string_view s)
    {
        return to_unsigned(s.data(), s.size());
    }

    std::u32string  to_upper(const std::u32string_view&s)
    {
        std::u32string ret;
        ret.reserve(s.size());
        for(char32_t ch : s)
            ret += to_upper(ch);
        return ret;
    }

    Expect<unsigned short>    to_ushort(const char32_t*s, size_t n)
    {
        if(!s)
            return errors::null_pointer();
        trim_ws(s,n);
        if(!n)
            return errors::empty_string();
        return int_from_chars<unsigned short>(s,n);
    }


    Expect<unsigned short>    to_ushort(std::u32string_view s)
    {
        return to_ushort(s.data(), s.size());
    }

    std::u32string_view    trimmed(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string_view();

        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        
        for(size_t i=0;i<sv.size();++i){
            char32_t    ch  = sv[i];
            if(!is_space(ch)){
                e   = &sv[i];
                if(!s)
                    s   = &sv[i];
            }
        }
        
        if(s && e){
            return std::u32string_view(s, e+1);
        } else
            return std::u32string_view();
    }
    
    std::u32string_view    trimmed(std::u32string_view sv, char32_t c)
    {
        if(sv.empty())
            return std::u32string_view();
            
        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (*s == c); ++s)
            ;
        for(; (s<e) && (e[-1] == c); --e)
            ;
        return std::u32string_view(s,e);
    }

    std::u32string_view    trimmed_end(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string_view();

        const char32_t* e   = nullptr;
        for(size_t i=0;i<sv.size();++i){
            char32_t    ch  = sv[i];
            if(!is_space(ch)){
                e   = &sv[i];
            }
        }
        
        if(e){
            return std::u32string_view(sv.data(), e+1);
        } else
            return std::u32string_view();
    }
    
    std::u32string_view    trimmed_end(std::u32string_view sv, char32_t c)
    {
        if(sv.empty())
            return std::u32string_view();
            
        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (e[-1] == c); --e)
            ;
        return std::u32string_view(s,e);
    }

    std::u32string_view    trimmed_start(std::u32string_view sv)
    {
        if(sv.empty())
            return std::u32string_view();

        const char32_t* s   = nullptr;
        for(size_t i=0;i<sv.size();++i){
            if(!is_space(sv[i])){
                s   = &sv[i];
                break;
            }
        }
        if(s)
            return std::u32string_view(s, sv.data()+sv.size());
        return sv;
    }
    
    std::u32string_view    trimmed_start(std::u32string_view sv, char32_t c)
    {
        if(sv.empty())
            return std::u32string_view();
            
        const char32_t* s   = nullptr;
        const char32_t* e   = nullptr;
        for(s=sv.data(), e=sv.data()+sv.size(); (s<e) && (*s == c); ++s)
            ;
        return std::u32string_view(s,e);
    }
}

namespace std {
    ostream& operator<<(ostream& out, u32string_view sv)
    {
        for(char32_t ch : sv)
            out << yq::to_string_view(ch);
        return out;
    }

    ostream& operator<<(ostream& out, const u32string& s)
    {
        return out << (u32string_view) s;
    }
}
