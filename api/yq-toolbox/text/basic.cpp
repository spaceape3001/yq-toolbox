////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "basic.hpp"
#include <yq-toolbox/text/chars.hpp>
#include <yq-toolbox/text/chars32.hpp>
#include <yq-toolbox/text/IterUtf8.hpp>
#include <cstdint>

namespace yq {
    const char*         strany(std::string_view haystack, std::string_view needle)
    {
        for(const char* z = haystack.begin(); z != haystack.end(); ++z){
            if(strnchr(needle, *z))
                return z;
        }
        return nullptr;
    }

    const char*  strnchr(const char*s, size_t n, char ch)
    {
        if(!s || !n)
            return nullptr;
        for(;*s && n; ++s, --n)
            if(*s == ch)
                return s;
        return nullptr;
    }

    const char*  strnchr(const char*s, size_t n, char32_t ch)
    {
        return iter_utf8_find(s, n, [&](char32_t c) -> bool {
            return ch == c;
        });
    }

    const char*  strnchr(std::string_view s, char ch)
    {
        return strnchr(s.data(), s.size(), ch);
    }

    const char*  strnchr_igCase(const char*s, size_t n, char ch)
    {
        ch      = to_lower(ch);
        if(!s || !n)
            return nullptr;
        for(;*s && n; ++s, --n)
            if(to_lower(*s) == ch)
                return s;
        return nullptr;
    }
    
    const char*  strnchr_igCase(const char*s, size_t n, char32_t ch)
    {   
        ch  = to_lower(ch);
        return iter_utf8_find(s, n, [&](char32_t c) -> bool {
            return ch == to_lower(c);
        });
    }

    const char*  strnstr(const char* haystack, size_t nHay, const char* needle, size_t nNeedle)
    {
        //  weed outs
        if(!haystack || !needle || !nHay || (nHay < nNeedle)) 
            return nullptr;

        if(nNeedle == 1)    
            return strnchr(haystack, nHay, *needle);

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
        }
        return nullptr;
    }

    const char*  strnstr_igCase(const char* haystack, size_t nHay, const char* needle, size_t nNeedle)
    {
        //  weed outs
        if(!haystack || !needle || !nHay || (nHay < nNeedle)) 
            return nullptr;

        if(nNeedle == 1)    
            return strnchr_igCase(haystack, nHay, *needle);

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
        }
        return nullptr;
    }
}
