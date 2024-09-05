////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "match32.hpp"
#include <yq-toolbox/text/basic32.hpp>
#include <yq-toolbox/text/chars32.hpp>
#include <yq-toolbox/text/IgCase.hpp>
#include <string>

namespace yq {
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


    bool  is_equal(std::u32string_view a, std::u32string_view b)
    {
        return is_equal(compare(a,b));
    }

    bool  is_greater_igCase(std::u32string_view a, std::u32string_view b)
    {
        return is_greater(compare_igCase(a,b));
    }

    bool  is_less_igCase(std::u32string_view a, std::u32string_view b)
    {
        return is_less( compare_igCase(a,b));
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

    bool        matches_at(std::u32string_view haystack, size_t pos, std::u32string_view pattern)
    {
        return starts(haystack.substr(pos), pattern);
    }
    
    bool        matches_at_igCase(std::u32string_view haystack, size_t pos, std::u32string_view pattern)
    {
        return starts_igCase(haystack.substr(pos), pattern);
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
}
