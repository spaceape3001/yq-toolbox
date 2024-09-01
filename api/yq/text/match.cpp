////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "match.hpp"
#include <yq/text/basics.hpp>
#include <yq/text/chars.hpp>
#include <yq/text/IgCase.hpp>
#include <yq/text/IterUtf8.hpp>
#include <yq/text/Iter32.hpp>
#include <string>

namespace yq {

    bool    any_starts(const std::vector<std::string>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts(const std::vector<std::string_view>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts(const std::initializer_list<std::string_view>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(const std::vector<std::string>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(const std::vector<std::string_view>&haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }
    
    bool    any_starts_igCase(std::initializer_list<std::string_view> haystack, std::string_view pat)
    {
        for(auto& s : haystack)
            if(starts_igCase(s, pat))
                return true;
        return false;
    }

    Compare compare(std::string_view a, std::string_view b)
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

    Compare compare_igCase(std::string_view sa, std::string_view sb)
    {
        IterUtf8  a(sa);
        IterUtf8  b(sb);
        
        for(;;){
            char32_t  ca  = a.next();
            char32_t  cb  = b.next();
            
            int64_t n   = (int64_t) to_lower(ca) - (int64_t) to_lower(cb);
            if(n<0)
                return Compare::LESSER;
            else if(n>0)
                return Compare::GREATER;
            if(!ca)
                return Compare::EQUAL;
        }
    }


    bool    contains(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle)
    {
        return strnstr(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains(std::string_view haystack, std::string_view needle)
    {
        return contains(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    bool    contains_igCase(const char* haystack, size_t nHaystack, const char* needle, size_t nNeedle)
    {
        return strnstr_igCase(haystack, nHaystack, needle, nNeedle) ? true : false;
    }

    bool    contains_igCase(std::string_view haystack, std::string_view needle)
    {
        return contains_igCase(haystack.data(), haystack.size(), needle.data(), needle.size());
    }

    bool    ends(std::string_view hay, std::string_view pat)
    {
        if(pat.size() > hay.size())
            return false;
        return hay.substr(hay.size()-pat.size()) == pat;
    }



    char32_t  first_non_blank_char(std::string_view a)
    {
        char32_t  ret   = 0;
        iter_utf8_abort(a, [&](char32_t ch) -> bool {
            if(!is_space(ch)){
                ret = ch;
                return false;
            }
            return true;
        });
        return ret;
    }

    std::string_view  first_non_empty(std::string_view a, std::string_view b)
    {
        return a.empty() ? b : a;
    }

    std::string_view  first_non_empty(std::string_view a, std::string_view b, std::string_view c)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        return c;
    }

    std::string_view  first_non_empty(std::string_view a, std::string_view b, std::string_view c, std::string_view d)
    {
        if(!a.empty())
            return a;
        if(!b.empty())
            return b;
        if(!c.empty())
            return c;
        return d;
    }

    std::string_view  first_non_empty(std::initializer_list<std::string_view> args)
    {
        for(std::string_view s : args)
            if(!s.empty())
                return s;
        return std::string_view();
    }
    
    bool  is_equal(std::string_view a, std::string_view b)
    {
        return is_equal(compare(a,b));
    }

    bool  is_greater_igCase(std::string_view a, std::string_view b)
    {
        return is_greater(compare_igCase(a,b));
    }


    bool  is_in(std::string_view str, std::string_view pat)
    {
        return is_similar(str, pat);
    }
    

    bool  is_in(std::string_view str, std::initializer_list<std::string_view> pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }
    
    bool  is_in(std::string_view str, const string_view_set_t& pat)
    {
        return pat.contains(str);
    }

    bool  is_in(std::string_view str, const std::vector<std::string_view>& pat)
    {
        for(auto& s : pat)
            if(is_similar(str, s))
                return true;
        return false;
    }

    bool  is_in(char32_t ch, std::string_view pat)
    {
        Iter32 them(pat);
        while(them.more()){
            if(is_similar(them.next(), ch))
                return true;
        }
        return false;
    }

    bool  is_less_igCase(std::string_view a, std::string_view b)
    {
        return is_less( compare_igCase(a,b));
    }

    bool  is_less_igCase_u8(std::string_view a, std::string_view b)
    {
        return is_less( compare_igCase(a,b));
    }

    bool  is_similar(char a, char b)
    {
        return to_lower(a) == to_lower(b);
    }

    bool  is_similar(std::string_view a, std::string_view b)
    {
        if(a.size() != b.size())
            return false;
        return is_equal( compare_igCase(a, b));
    }

    bool        is_valid_key(std::string_view k)
    {
        if(k.empty())
            return false;
        
        if(!is_alnum(k[0]))
            return false;
        for(size_t i=1;i<k.size();++i){
            if(is_alnum(k[i]))
                continue;
            switch(k[i]){
            case '-':
            case '_':
            case '+':
                continue;
            default:
                return false;
            }
        }
        return true;
    }
    
    bool        matches_at(std::string_view haystack, size_t pos, std::string_view pattern)
    {
        return starts(haystack.substr(pos), pattern);
    }
    
    bool        matches_at_igCase(std::string_view haystack, size_t pos, std::string_view pattern)
    {
        return starts_igCase(haystack.substr(pos), pattern);
    }

        
    bool  starts(const char* s, size_t n, const char* pat, size_t nPat)
    {
        if(s && n && pat && (nPat<=n)){
            for(size_t i=0;i<nPat;++i)
                if(s[i] != pat[i])
                    return false;
            return true;
        }
        
        return false;
    }
    
    bool  starts(std::string_view s, std::string_view pat)
    {
        return starts(s.data(), s.size(), pat.data(), pat.size());
    }
    
    bool  starts_igCase(const char* s, size_t n, const char* pat, size_t nPath)
    {
        if(s && n && pat && (nPath<=n)){
            for(size_t i=0;i<nPath;++i)
                if(to_lower(s[i]) != to_lower(pat[i]))
                    return false;
            return true;
        }
        
        return false;
    }
    
    bool  starts_igCase(std::string_view s, std::string_view pat)
    {
        return starts_igCase(s.data(), s.size(), pat.data(), pat.size());
    }

}
