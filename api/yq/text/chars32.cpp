////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq/text/chars32.hpp>
#include <cwctype>
#include <string>

namespace yq {

    bool  is_alnum(char32_t ch)
    {
        return ::iswalnum(ch);
    }

    bool  is_alpha(char32_t ch)
    {
        return ::iswalpha(ch);
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
    
    bool  is_blank(char32_t ch)
    {
        return ::iswblank(ch);
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

    bool  is_control(char32_t ch)
    {
        return ::iswcntrl(ch);
    }
    
    bool  is_digit(char32_t ch)
    {
        return ::iswdigit(ch);
    }

    bool  is_graph(char32_t ch)
    {
        return ::iswgraph(ch);
    }

    bool  is_lower(char32_t ch)
    {
        return ::iswlower(ch);
    }
    
    bool    is_newline(char32_t ch)
    {
        return (ch == U'\r') || (ch == U'\n');
    }

    bool  is_print(char32_t ch)
    {
        return ::iswprint(ch);
    }
    
    bool  is_punct(char32_t ch)
    {
        return ::iswpunct(ch);
    }

    bool  is_space(char32_t ch)
    {
        return ::iswspace(ch);
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

    bool  is_upper(char32_t ch)
    {
        return ::iswupper(ch);
    }
    
    bool  is_xdigit(char32_t ch)
    {
        return ::iswxdigit(ch);
    }

    char32_t  to_lower(char32_t ch)
    {
        return ::towlower(ch);
    }

    std::u32string  to_lower(const std::u32string_view&s)
    {
        std::u32string ret;
        ret.reserve(s.size());
        for(char32_t ch : s)
            ret += to_lower(ch);
        return ret;
    }

    char32_t  to_upper(char32_t ch)
    {
        return ::towupper(ch);
    }

    std::u32string  to_upper(const std::u32string_view&s)
    {
        std::u32string ret;
        ret.reserve(s.size());
        for(char32_t ch : s)
            ret += to_upper(ch);
        return ret;
    }

}
