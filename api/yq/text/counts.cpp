////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "counts.hpp"
#include <yq/text/chars.hpp>
#include <yq/text/chars32.hpp>
#include <yq/text/IterUtf8.hpp>

namespace yq {

    size_t  count_characters(const char* s, size_t n)
    {
        size_t  ret = 0;
        if(s && n){
            iter_utf8(s, n, [&](char32_t){ ++ret; });
        }
        return ret;
    }
    
    size_t  count_characters(std::string_view s)
    {
        return count_characters(s.data(), s.size());
    }
    
    size_t  count_characters(const char* s, size_t n, char ch)
    {
        size_t ret =0;
        if(s && n){
            for(size_t i=0;i<n;++i)
                if(s[i] == ch)
                    ++ret;
        }
        return ret;
    }
    
    size_t  count_characters(std::string_view s, char ch)
    {
        return count_characters(s.data(), s.size(), ch);
    }
    
    size_t  count_characters(const char* s, size_t n, char32_t ch)
    {
        size_t ret=0;
        if(s && n){
            iter_utf8(s, n, [&](char32_t c){ 
                if(c == ch) 
                    ++ret; 
            });
        }
        return ret;
    }
    
    size_t  count_characters(std::string_view s, char32_t ch)
    {
        return count_characters(s.data(), s.size(), ch);
    }


    size_t  count_characters_igCase(const char* s, size_t n, char ch)
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
    

    size_t  count_characters_igCase(std::string_view s, char ch)
    {
        return count_characters_igCase(s.data(), s.size(), ch);
    }
    
    size_t  count_characters_igCase(const char* s, size_t n, char32_t ch)
    {
        size_t  ret = 0;
        if(s && n){
            ch  = to_lower(ch);
            iter_utf8(s, n, [&](char32_t c){
                if(to_lower(c) == ch)
                    ++ret;
            });
        }
        return ret;
    }
    
    size_t  count_characters_igCase(std::string_view s, char32_t ch)
    {
        return count_characters_igCase(s.data(), s.size(), ch);
    }

    size_t  count_start_spaces(std::string_view a)
    {
        size_t  ret   = 0;
        iter_utf8_abort(a, [&](char32_t ch) -> bool {
            if(is_space(ch)){
                ++ret;
                return true;
            } else
                return false;
        });
        return ret;
    }

    
    size_t  count_starts(std::string_view s, char ch)
    {
        size_t  n = 0;
        for(; (n<s.size()) && (s[n] == ch); ++n)
            ;
        return n;
    }
}
