////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <yq-toolbox/text/chars.hpp>
#include <yq-toolbox/text/chars32.hpp>
#include <yq-toolbox/text/IterUtf8.hpp>
#include <cctype>

namespace yq {
    bool  is_alnum(char ch)
    {
        return ::isalnum(ch);
    }

    bool  is_alpha(char ch)
    {
        return ::isalpha(ch);
    }

    bool  is_alpha(const char*s, size_t n)
    {
        bool    ret = true;
        return iter_utf8_abort(s, n, [&](char32_t ch) -> bool {
            ret = ret &&  is_alpha(ch);
            return ret;
        });
        return ret;
    }
    
    bool  is_alpha(std::string_view s)
    {
        return is_alpha(s.data(), s.size());
    }

    bool  is_blank(char ch)
    {
        return ::isblank(ch);
    }
    
    bool  is_blank(const char*s, size_t n)
    {
        bool    ret = true;
        return iter_utf8_abort(s, n, [&](char32_t ch) -> bool {
            ret = ret &&  is_blank(ch);
            return ret;
        });
        return ret;
    }

    bool  is_blank(std::string_view s)
    {
        return is_blank(s.data(), s.size());
    }
    
    bool  is_control(char ch)
    {   
        return ::iscntrl(ch);
    }
    
    bool  is_digit(char ch)
    {
        return ::isdigit(ch);
    }
    
    bool  is_graph(char ch)
    {
        return ::isgraph(ch);
    }
    
    bool  is_lower(char ch)
    {
        return ::islower(ch);
    }

    bool    is_newline(char ch)
    {
        return (ch == '\r') || (ch == '\n');
    }

    bool  is_print(char ch)
    {
        return ::isprint(ch);
    }
    
    bool  is_punct(char ch)
    {
        return ::ispunct(ch);
    }

    bool  is_space(char ch)
    {
        return ::isspace(ch);
    }
    
    bool  is_space(std::string_view a)
    {
        bool    ret = true;
        return iter_utf8_abort(a, [&](char32_t ch) -> bool {
            ret = ret &&  is_space(ch);
            return ret;
        });
        return ret;
    }
    
    bool  is_upper(char ch)
    {
        return ::isupper(ch);
    }
    
    bool  is_xdigit(char ch)
    {
        return ::isxdigit(ch);
    }

    char  to_lower(char ch)
    {
        return ::tolower(ch);
    }
    
    std::string  to_lower(std::string_view s)
    {
        std::string ret;
        ret.reserve(s.size());
        iter_utf8(s, [&](char32_t ch){
            ret += to_lower(ch);
        });
        return ret;
    }

    char  to_upper(char ch)
    {
        return ::toupper(ch);
    }

    std::string  to_upper(std::string_view s)
    {
        std::string ret;
        ret.reserve(s.size());
        iter_utf8(s, [&](char32_t ch){
            ret += to_upper(ch);
        });
        return ret;
    }
}
