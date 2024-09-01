////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "counts32.hpp"
#include <yq/text/chars32.hpp>

namespace yq {

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
}
