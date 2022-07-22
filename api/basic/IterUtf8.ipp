////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

//#pragma once
#include "IterUtf8.hpp"

namespace yq {
    int utf8_decode(char32_t&ch, const char*z, size_t n)
    {
        if(!z)
            return -1;
        if(!*z)
            return 0;
        if(!n)
            return 0;
        
            //  one byte character
        if(!(*z&0x80)) [[likely]] {
            ch  = (char32_t) *z;
            return 1;
        }
        
        size_t cnt = 1;
        
        if(!(*z & 0x40)){           // SURPRISE, it's a code-point byte... disallowed
            return -1;
        } else if(!(*z & 0x20)){    // two bytes
            ch  = *z & 0x1F;
            cnt = 2;
        } else if(!(*z & 0x10)){   // three bytes
            ch  = *z & 0xF;
            cnt = 3;
        } else if(!(*z & 0x08)){    // four bytes
            ch  = *z & 0x7;
            cnt = 4;
        } else if(!(*z & 0x04)){    // five bytes
                // technically 5+ isn't in the standard, however, I see the pattern
            ch  = *z & 0x3;
            cnt = 5;
        } else if(!(*z & 0x02)){    // six bytes
            ch  = *z & 0x1;
            cnt = 6;
        } else if(!(*z & 0x01)){    // seven bytes
            ch  = 0;
            cnt = 7;
        } else {
            return -1;
        };
        
        if(n<cnt)   // insufficient bytes, error....
            return -1;
            
        for(size_t j=1;j<cnt;++j){
            if((z[j]&0xC0) != 0x80)     // not a UTF code-point byte, bye!
                return -1;
            ch <<= 6;
            ch |= 0x3F & z[j];
        }
        
        return cnt;
    }
}
