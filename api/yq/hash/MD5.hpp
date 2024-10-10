//  While part of the YQ Toolbox, no banner as it's derivative work (see MD5.cpp)

#pragma once

#include <cstdint>
#include <cstddef>
#include <yq/core/128-bit.hpp>

namespace yq {
    class MD5_Calculator {
        union {
            uint32_t    state  [ 4 ];
            uint128_t   value_128;
        };
        uint32_t    count  [ 2 ];
        uint8_t     buffer [ 64 ];
     public:
        MD5_Calculator();
        ~MD5_Calculator();

        void        clear();
        void        add(const unsigned char*, unsigned int);
        void        finalize();
        
        const uint128_t&  value() const { return value_128; }
    };
    
    uint128_t   md5_checksum(const void*, size_t);
}
