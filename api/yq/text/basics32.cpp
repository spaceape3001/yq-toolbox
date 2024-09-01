////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include "basics32.hpp"

#include <yq/text/chars32.hpp>

namespace yq {
    const char32_t*         strany(std::u32string_view haystack, std::u32string_view needle)
    {
        for(const char32_t* z = haystack.begin(); z != haystack.end(); ++z){
            if(strnchr(needle, *z))
                return z;
        }
        return nullptr;
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
}
